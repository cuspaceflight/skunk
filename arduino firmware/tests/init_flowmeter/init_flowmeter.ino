#include <SoftwareSerial.h>

SoftwareSerial mySerial(53, 9); // RX, TX

// Use node address 128 - flowmeter should ALWAYS listen to this

void setup()  
{

  mySerial.begin(38400); // Baud specified in flowmeter docs.
  // Apparently we have to do pinmodes manually:
  pinMode(53, INPUT);
  pinMode(9, OUTPUT);

  delay(5000); // Wait for the flowmeter to warm up
  mySerial.println(":050001000A49\r\n");
  mySerial.println(":050001000101\r\n");
  mySerial.println(":05000100027F\r\n");
  mySerial.println(":050001000302\r\n"); // TODO: check for
  mySerial.println(":050001000420\r\n"); // error response to
  mySerial.println(":050001000502\r\n"); // each of these
  mySerial.println(":050001000A52\r\n"); // RESET!
  delay(2000); // GIve it a chance to reset.
  
  // Must change setpoint controlmode, process 01 parameter 12
  // Set to 20 for "valve steering" or "18" for RS232 setpoint
  // 3 for close valve, 8 for open valve
  // 7  for 100%, 12 for 0%
  // All 1 byte sent as 2byte hex
  
  // :
  // length=5 = '05'
  // node=128 = '80'
  // cmd=02 = '02'
  // process = 01 = '01'
  // parameter 12 = '12'
  // value 20 = '20'
  char message[]=":058002011220\r\n";
  mySerial.print(message);
  delay(1000);

}


void loop() // run over and over
{
  char message[128];
  // Message format (each field is two characters, the ASCII hex repr of the numerical value)
  // :
  // length = 6 = '06'
  // node = 128 = '80'
  // cmd = 02 = '02'      (parameter set with no response)
  // process = 01 = '01' ???
  // parameter = 21 = '21' ???
  // setpoint1 = '00' or '7D'
  // setpoint2 = '00'
  // '\r'
  //  '\n'

  sprintf(message, ":06800201210000\r\n");
  mySerial.print(message);
  delay(1000);
  sprintf(message, ":06800201217D00\r\n");
  mySerial.print(message);
  delay(1000);
}
