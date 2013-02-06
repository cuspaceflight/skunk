#include <SoftwareSerial.h>

SoftwareSerial mySerial(3,7); // pin 7 = TX, pin 3 = RX (unused)


const int keysw=5;
const int piezo=30;

void setup() {
  pinMode(piezo, OUTPUT);      
  pinMode(keysw, INPUT);     
  
  mySerial.begin(9600); // set up serial port for 9600 baud
  delay(500); // Wait for serLCD to boot
  
  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(128);
  mySerial.write("SKUNK KEYSW AND ");
  mySerial.write("PIEZO TEST      ");
  delay(2000);
  // Clear:
  mySerial.write("                ");
  mySerial.write("                ");
}

void loop(){
 
  if(digitalRead(keysw) == HIGH)
  {
    digitalWrite(piezo, HIGH);
    mySerial.write(254); // move cursor to beginning of first line
    mySerial.write(128);
    mySerial.write("Key is out      ");
    mySerial.write("BEEP!           ");    
  }
  else
  {
    digitalWrite(piezo, LOW);
    mySerial.write(254); // move cursor to beginning of first line
    mySerial.write(128);
    mySerial.write("Key is in       ");
    mySerial.write("No beep.        ");    
  }
  delay(500);
}
