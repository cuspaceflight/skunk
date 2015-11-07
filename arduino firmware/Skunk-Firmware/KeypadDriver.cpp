#include "SkunkPinDefs.h"
#include "KeypadDriver.h"

void keypad_setup(){
  pinMode(PIN_R1, OUTPUT);
  pinMode(PIN_R2, OUTPUT);
  pinMode(PIN_R3, OUTPUT);
  pinMode(PIN_R4, OUTPUT);
  pinMode(PIN_C1, INPUT);
  pinMode(PIN_C2, INPUT); // C lines are pulled up externally
  pinMode(PIN_C3, INPUT);
}

char keypad_get_key_pressed(){
  digitalWrite(PIN_R1, LOW);
  digitalWrite(PIN_R2, HIGH);
  digitalWrite(PIN_R3, HIGH);
  digitalWrite(PIN_R4, HIGH);
  if(digitalRead(PIN_C1) == LOW)
    return '1';
  if(digitalRead(PIN_C2) == LOW)
    return '2';
  if(digitalRead(PIN_C3) == LOW)
    return '3';

  digitalWrite(PIN_R1, HIGH);
  digitalWrite(PIN_R2, LOW);
  digitalWrite(PIN_R3, HIGH);
  digitalWrite(PIN_R4, HIGH);
  if(digitalRead(PIN_C1) == LOW)
    return '4';
  if(digitalRead(PIN_C2) == LOW)
    return '5';
  if(digitalRead(PIN_C3) == LOW)
    return '6';

  digitalWrite(PIN_R1, HIGH);
  digitalWrite(PIN_R2, HIGH);
  digitalWrite(PIN_R3, LOW);
  digitalWrite(PIN_R4, HIGH);
  if(digitalRead(PIN_C1) == LOW)
    return '7';
  if(digitalRead(PIN_C2) == LOW)
    return '8';
  if(digitalRead(PIN_C3) == LOW)
    return '9';

  digitalWrite(PIN_R1, HIGH);
  digitalWrite(PIN_R2, HIGH);
  digitalWrite(PIN_R3, HIGH);
  digitalWrite(PIN_R4, LOW);
  if(digitalRead(PIN_C1) == LOW)
    return '*';
  if(digitalRead(PIN_C2) == LOW)
    return '0';
  if(digitalRead(PIN_C3) == LOW)
    return '#';
  
  return -1;
}

