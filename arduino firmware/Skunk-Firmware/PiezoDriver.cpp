#include "SkunkPinDefs.h"
#include "PiezoDriver.h"

void piezo_setup(){
  pinMode(PIN_PIEZO, OUTPUT);
}

void piezo_set(boolean bOn){
  digitalWrite(PIN_PIEZO, bOn);
}

void piezo_on(){
  piezo_set(true);
}

void piezo_off(){
  piezo_set(false);
}
