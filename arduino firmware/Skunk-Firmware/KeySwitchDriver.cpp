#include "KeySwitchDriver.h"

#define KEYSW  5

void keyswitch_setup(){
  pinMode(KEYSW, INPUT);
}

boolean keyswitch_on(){
  return digitalRead(KEYSW) == HIGH;
}
