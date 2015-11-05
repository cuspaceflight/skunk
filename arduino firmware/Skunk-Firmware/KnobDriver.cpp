#include "KnobDriver.h"

#define KNOB  A0

void knob_setup(){
  // Nothing here
}

unsigned int knob_get_raw_value(){
  return analogRead(KNOB);
}

unsigned int knob_get_percent(){
  unsigned int val = knob_get_raw_value();
  return (val*100.0)/1024.0;
}
