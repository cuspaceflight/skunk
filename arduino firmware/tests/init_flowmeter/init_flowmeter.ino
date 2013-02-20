#include <SoftwareSerial.h>

//SoftwareSerial mySerial(53, 9); // RX, TX

// Use node address 128 - flowmeter should ALWAYS listen to this

void setup()  
{

  Serial1.begin(38400); // Baud specified in flowmeter docs.

  // High impedance the two softwareserial pins
  pinMode(53, INPUT);
  pinMode(9, INPUT);

  delay(5000); // Wait for the flowmeter to warm up

  // Init stuff:
  Serial1.println(":050001000A49\r\n");
  Serial1.println(":050001000101\r\n");
  Serial1.println(":05000100027F\r\n");
  Serial1.println(":050001000302\r\n"); // TODO: check for
  Serial1.println(":050001000420\r\n"); // error response to
  Serial1.println(":050001000502\r\n"); // each of these
  
  Serial1.println(":050001000A52\r\n"); // RESET!
  delay(2000); // GIve it a chance to reset.
  
  // Must change setpoint controlmode, process 01 parameter 12
  // Set to 20 for "valve steering" which is what we want
  // :
  // length=5 = '05'
  // node=128 = '80'
  // cmd=02 = '02'
  // process = 01 = '01'
  // parameter 12 = '12'
  // value 20 = '20'
  char message[]=":058002011220\r\n";
  Serial1.print(message);
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
  // process = 01 = '01' ??? Don't understand a lot of these but it seems to work
  // parameter = 21 = '21' ???
  // setpoint1 = '00' or '7D'
  // setpoint2 = '00'
  // '\r', '\n'

  sprintf(message, ":06800201210000\r\n"); // Valve close, 0x0000
  Serial1.print(message);
  delay(1000);
  sprintf(message, ":06800201217D00\r\n"); // Wide open, 0x7D00
  Serial1.print(message);
  delay(1000);
}
