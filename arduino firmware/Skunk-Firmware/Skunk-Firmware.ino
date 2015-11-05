#include "KeypadDriver.h"
#include "KeySwitchDriver.h"
#include "PiezoDriver.h"

void setup(){
  keypad_setup();
  keyswitch_setup();
  piezo_setup();
}

void loop(){
  keypad_get_key_pressed();
  piezo_set(keyswitch_on());
}

