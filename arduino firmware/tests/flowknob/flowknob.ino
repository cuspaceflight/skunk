// SparkFun Serial LCD example 1
// Clear the display and say "Hello World!"

// This sketch is for Arduino versions 1.0 and later
// If you're using an Arduino version older than 1.0, use
// the other example code available on the tutorial page.

// Use the softwareserial library to create a new "soft" serial port
// for the display.
#include <SoftwareSerial.h>

SoftwareSerial mySerial(3,7); // pin 7 = TX, pin 3 = RX (unused)

const int flowknob=A0;

void setup()
{
  mySerial.begin(9600); // set up serial port for 9600 baud
  delay(500); // wait for display to boot up
  
  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(128);

  mySerial.write("SKUNK FLOWKNOB  "); // clear display
  mySerial.write("TEST PROGRAM    ");
  delay(2000);
  mySerial.write("                "); // DIRTY HACK >:-D
  mySerial.write("                ");
}

void loop()
{
  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(128);
  mySerial.write("Flowknob value: ");
  mySerial.print(analogRead(flowknob));
  mySerial.write("    "); // Dirty hack :-)

  delay(100);
}

