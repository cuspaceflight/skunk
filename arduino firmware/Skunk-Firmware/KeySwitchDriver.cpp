#include "SkunkPinDefs.h"
#include "KeySwitchDriver.h"

void keyswitch_setup(){
  pinMode(PIN_KEYSW, INPUT);
}

boolean keyswitch_on(){
  return digitalRead(PIN_KEYSW) == HIGH;
}
