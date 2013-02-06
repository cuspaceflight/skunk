// SparkFun Serial LCD example 1
// Clear the display and say "Hello World!"

// This sketch is for Arduino versions 1.0 and later
// If you're using an Arduino version older than 1.0, use
// the other example code available on the tutorial page.

// Use the softwareserial library to create a new "soft" serial port
// for the display.
#include <SoftwareSerial.h>

SoftwareSerial mySerial(3,7); // pin 7 = TX, pin 3 = RX (unused)


void setup()
{
  mySerial.begin(9600); // set up serial port for 9600 baud
  delay(2000); // wait for display to boot up (actually more
  // like 500ms, but eh.
}

void loop()
{
  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(128);

  mySerial.write("                "); // clear display
  mySerial.write("                ");

  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(128);
 
  mySerial.write("Hello, world!   "); // Is probably a more elegant
  // way to change line than wrapping...
  mySerial.write("I'm a Skunk! :D ");

  while(1); // wait forever :(
}

