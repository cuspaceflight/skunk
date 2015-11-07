#include "SkunkPinDefs.h"
#include "KnobDriver.h"

void knob_setup(){
  // Nothing here, but kept for consistency
}

unsigned int knob_get_raw_value(){
  return analogRead(PIN_KNOB);
}

unsigned int knob_get_percent(){
  unsigned int val = knob_get_raw_value();
  return (val*100.0)/1024.0;
}
