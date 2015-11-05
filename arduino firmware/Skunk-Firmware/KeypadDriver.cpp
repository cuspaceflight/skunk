#include "KeypadDriver.h"

#define R1  37
#define R2  35
#define R3  36
#define R4  34
#define C1  32
#define C2  33
#define C3  31

void keypad_setup(){
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  pinMode(C1, INPUT);
  pinMode(C2, INPUT); // C lines are pulled up externally
  pinMode(C3, INPUT);
}

char keypad_get_key_pressed(){
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
  digitalWrite(R3, HIGH);
  digitalWrite(R4, HIGH);
  if(digitalRead(C1) == LOW)
    return '1';
  if(digitalRead(C2) == LOW)
    return '2';
  if(digitalRead(C3) == LOW)
    return '3';

  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
  digitalWrite(R3, HIGH);
  digitalWrite(R4, HIGH);
  if(digitalRead(C1) == LOW)
    return '4';
  if(digitalRead(C2) == LOW)
    return '5';
  if(digitalRead(C3) == LOW)
    return '6';

  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(R3, LOW);
  digitalWrite(R4, HIGH);
  if(digitalRead(C1) == LOW)
    return '7';
  if(digitalRead(C2) == LOW)
    return '8';
  if(digitalRead(C3) == LOW)
    return '9';

  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(R3, HIGH);
  digitalWrite(R4, LOW);
  if(digitalRead(C1) == LOW)
    return '*';
  if(digitalRead(C2) == LOW)
    return '0';
  if(digitalRead(C3) == LOW)
    return '#';
  
  return -1;
}

