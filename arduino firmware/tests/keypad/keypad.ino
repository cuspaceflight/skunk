// This sketch is for Arduino versions 1.0 and later
// If you're using an Arduino version older than 1.0, use
// the other example code available on the tutorial page.

// Use the softwareserial library to create a new "soft" serial port
// for the display.
#include <SoftwareSerial.h>

SoftwareSerial mySerial(3,7); // pin 7 = TX, pin 3 = RX (unused)

#define R1 37
#define R2 35
#define R3 36
#define R4 34
#define C1 32
#define C2 33
#define C3 31

char key[2];

void setup()
{
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  pinMode(C1, INPUT);
  pinMode(C2, INPUT); // C lines are pulled up externally
  pinMode(C3, INPUT);
  
  key[0]='-';
  key[1]='\0';
  
  mySerial.begin(9600); // set up serial port for 9600 baud
  delay(500); // wait for display to boot up (actually more
  // like 500ms, but eh.

  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(128);  

  // Splash screen
  mySerial.write("SKUNK KEYPAD    ");
  mySerial.write("TEST PROGRAM    ");
  delay(2000);
  
  // Clear:
  mySerial.write("                ");
  mySerial.write("                ");
}

void loop()
{
  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(128);

  // Figure out which key[0] is pressed:
  key[0]='-'; // Nothing pressed.
  
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
  digitalWrite(R3, HIGH);
  digitalWrite(R4, HIGH);
  if(digitalRead(C1) == LOW)
    key[0]='1';
  if(digitalRead(C2) == LOW)
    key[0]='2';
  if(digitalRead(C3) == LOW)
    key[0]='3';
    
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
  digitalWrite(R3, HIGH);
  digitalWrite(R4, HIGH);
  if(digitalRead(C1) == LOW)
    key[0]='4';
  if(digitalRead(C2) == LOW)
    key[0]='5';
  if(digitalRead(C3) == LOW)
    key[0]='6';
    
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(R3, LOW);
  digitalWrite(R4, HIGH);
  if(digitalRead(C1) == LOW)
    key[0]='7';
  if(digitalRead(C2) == LOW)
    key[0]='8';
  if(digitalRead(C3) == LOW)
    key[0]='9';
  
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(R3, HIGH);
  digitalWrite(R4, LOW);
  if(digitalRead(C1) == LOW)
    key[0]='*';
  if(digitalRead(C2) == LOW)
    key[0]='0';
  if(digitalRead(C3) == LOW)
    key[0]='#';
  
  mySerial.write("Key pressed: ");
  mySerial.write(key);
  
  delay(100);
  

}

