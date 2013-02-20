#include <SoftwareSerial.h>

SoftwareSerial serLCD(3, 7); // 3=RX (unused), 7=TX

// Use node address 128 = 0x80 - flowmeter should ALWAYS listen to this

// Protip: http://www.h-schmidt.net/FloatConverter/IEEE754.html for 4byte IEC float<=>hex

// Protip2: Message lengths are number of bytes (i.e. half the number of characters,
// we send two characters of hex per byte) not including the length byte and not inc. \r\n

float read2float(char buffer[]);
void lcdorigin()
{
  serLCD.write(254); // move cursor to beginning of first line
  serLCD.write(128);
}

void lcdclear()
{
  lcdorigin();
  serLCD.write("                ");
  serLCD.write("                ");
}

void setup()  
{
  float accumulation=0.0;
  
  Serial1.begin(38400); // Baud specified in flowmeter docs.
  serLCD.begin(9600);

  // High impedance the two softwareserial pins
  pinMode(53, INPUT);
  pinMode(9, INPUT);
  
  // Setup LCD serial:
  pinMode(3, INPUT);
  pinMode(7, OUTPUT);

  delay(3000); // Wait for the flowmeter (and LCD) to warm up

  // Init stuff:
  // Note, using \r\n so print, not println
  Serial1.print(":050001000A49\r\n");
  Serial1.print(":050001000101\r\n");
  Serial1.print(":05000100027F\r\n");
  Serial1.print(":050001000302\r\n"); // TODO: check for
  Serial1.print(":050001000420\r\n"); // error response to
  Serial1.print(":050001000502\r\n"); // each of these
  
  Serial1.print(":050001000A52\r\n"); // RESET!
  delay(2000); // GIve it a chance to reset.
  
  // Must change setpoint controlmode, process 01 parameter 12
  // Set to 20 for "valve steering" which is what we want
  // :
  // length=5 = '05'
  // node=128 = '80'
  // cmd=02 = '02'
  // process = 01 = '01'
  // parameter 4, type 'c' = 0x04
  // value 20 = '14'
  Serial1.print(":058002010414\r\n"); // Set controlmode to valve steering

  // Need to set CntrMode to 1, counting upwards continuously
  // process 104 = 0x68
  // parameter 8 type c = 0x08
  // Set to 1 = 0x01
  Serial1.print(":058002680801\r\n"); // Set controlmode to valve steering
  
  // Then reset counter to zero, i.e.
  // process 104 = 0x68
  // Parameter 1 type f = 0x01 + 0x40 = 0x41
  // set to 0.0 = 0x00000000
  Serial1.print(":088002684100000000\r\n");
  
  // Blank out the LCD:
  lcdclear();


}


void loop() // run over and over
{
  char message[128];
  char buffer[128];

  sprintf(message, ":06800201210000\r\n"); // Valve close, 0x0000
  Serial1.print(message);
  lcdclear();
  serLCD.write("valve closed");
  delay(1000);
  
  
  sprintf(message, ":06800201217D00\r\n"); // Wide open, 0x7D00
  Serial1.print(message);
  for(int i=0; i<10; i++)
  {
        // Then to retrieve the accumulation:
        // First clear our read buffer:
        while(Serial1.read() != -1);
        
        // Process 104 = 0x68
        // Parameter 1 type f = 0x01 + 0x40 = 0x41
        Serial1.print(":06800468416841\r\n");
        
        // Should receive :08??026841AABBCCDD\r\n
        // Where AABBCCDD are 4 bytes of float and ?? is flowmeter node number
        if(Serial1.readBytesUntil('\n', buffer, 128) >= 19)
        {
           lcdclear();
           serLCD.write("valve open samp");
           serLCD.print(i);
           serLCD.print(read2float(buffer));
           delay(300);
        }
        else
        {
           lcdclear();
           serLCD.write("Reply too short");
           serLCD.print(i);
           serLCD.write(" :( :( :( :( :( ");
           delay(300);
        }
  }
        
}


float read2float(char buffer[])
{
  char onebyte[3];
  float accumulation=0.0;
  
  onebyte[0]='0';
  onebyte[1]='0';
  onebyte[2]='\0';
  
  onebyte[0]=buffer[11];
  onebyte[1]=buffer[12];
  ((byte*)&accumulation)[3]=byte(strtoul(onebyte, NULL, 16));
  onebyte[0]=buffer[13];
  onebyte[1]=buffer[14];
  ((byte*)&accumulation)[2]=byte(strtoul(onebyte, NULL, 16));
  onebyte[0]=buffer[15];
  onebyte[1]=buffer[16];
  ((byte*)&accumulation)[1]=byte(strtoul(onebyte, NULL, 16));
  onebyte[0]=buffer[17];
  onebyte[1]=buffer[18];
  ((byte*)&accumulation)[0]=byte(strtoul(onebyte, NULL, 16));
  
  return accumulation;
}
  
