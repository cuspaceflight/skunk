#include "PiezoDriver.h"

#define PIEZO  30

void piezo_setup(){
  pinMode(PIEZO, OUTPUT);
}

void piezo_set(boolean bOn){
  digitalWrite(PIEZO, bOn);
}

void piezo_on(){
  piezo_set(true);
}

void piezo_off(){
  piezo_set(false);
}
