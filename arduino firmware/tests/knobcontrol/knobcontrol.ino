#include <SoftwareSerial.h>

SoftwareSerial serLCD(3, 7); // 3=RX (unused), 7=TX

const int flowknob=A0;

float read2float(char buffer[]);
void lcdorigin();
void lcdclear();
void setvalve(int percentageopen);
float getaccumulation();

void setup()  
{
  Serial1.begin(38400); // Baud specified in flowmeter docs.
  serLCD.begin(9600);

  pinMode(53, INPUT); // High impedance - these clash with hardware UART 1
  pinMode(9, INPUT);
  
  pinMode(3, INPUT);   // LCD software serial pins
  pinMode(7, OUTPUT);

  delay(1000); // Wait for the LCD to wake up
  lcdclear();
  serLCD.write("SKUNK! TestProg:");
  serLCD.write("KnobControl ;-) ");

  delay(1000); // Wait for the flowmeter to wake up

  // Init stuff:
  Serial1.print(":050001000A49\r\n");
  Serial1.print(":050001000101\r\n");
  Serial1.print(":05000100027F\r\n");
  Serial1.print(":050001000302\r\n");
  Serial1.print(":050001000420\r\n");
  Serial1.print(":050001000502\r\n");
  
  Serial1.print(":050001000A52\r\n"); // RESET!
  delay(1000); // GIve it a chance to reset.
  
  // Must change setpoint controlmode
  // Process 01, parameter 04 type 'c'
  // Set to 20 for "valve steering"
  Serial1.print(":058002010414\r\n");

  // Need to set CntrMode to counting upwards continuously
  // process 104 = 0x68
  // parameter 8 type c = 0x08
  // Set to 1 = 0x01
  Serial1.print(":058002680801\r\n"); // Set controlmode to valve steering
  
  // Then reset counter to zero, i.e.
  // process 104 = 0x68
  // Parameter 1 type f = 0x01 + 0x40 = 0x41
  // set to 0.0 = 0x00000000 (4 byte float)
  Serial1.print(":088002684100000000\r\n");
  
  delay(2000); // Display the splash a bit more.
  // Blank out the LCD:
  lcdclear();
}


void loop()
{
  float accumulation=-1.0;
  int knob = analogRead(flowknob)*100.0/1024.0;
  char knobtext[4];

  sprintf(knobtext, "%03i", knob);

  setvalve(knob);
  lcdclear();
  serLCD.write("valve set ");
  serLCD.write(knobtext);
  serLCD.write("%  "); // Should take us to the end of the line

  accumulation = getaccumulation();

  if(accumulation >= 0.0)
    serLCD.print(accumulation);
  else // <0.0 means ERROR D:
    serLCD.write("Err reading acc ");

  delay(300);        
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

void setvalve(int percentageopen)
{
  char message[32];
  // Scale the open-ness from 0-100 to 0x0000-0x7D00
  int rescale = 0x7D00 * percentageopen/100;
  char setpoint[5];

  if(rescale > 0x7D00)
    rescale=0x0000; // Default closed;


  sprintf(message, ":0680020121%04X\r\n", rescale);
  Serial1.print(message);
}

float getaccumulation()
{
	char buffer[128];

	// First clear our read buffer, so we can read just the returned line.
	while(Serial1.read() != -1);

	// Send read counter command:       
        // Process 104 = 0x68
        // Parameter 1 type f = 0x01 + 0x40 = 0x41
        Serial1.print(":06800468416841\r\n");
        
        // Should receive :08??026841AABBCCDD\r\n
        // Where AABBCCDD are 4 bytes of float and ?? is flowmeter node number
        if(Serial1.readBytesUntil('\n', buffer, 128) >= 19)
           return read2float(buffer);
        else
	   return -13.37; // Fail!
}
  
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


