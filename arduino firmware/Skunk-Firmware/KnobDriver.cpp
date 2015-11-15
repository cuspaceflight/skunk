#include "SkunkPinDefs.h"
#include "KnobDriver.h"

void knob_setup() {
  // Nothing here, but kept for consistency
}

unsigned int knob_get_raw_value() {
  return analogRead(PIN_KNOB);
}

// return a value from 0-100 representing the position of the knob
// there is some fudging applied to deal with the deadzones at each end
// 0-40 is seen as 0, 40-984 is 0-100 range, then 984-1024 is seen as 100
unsigned int knob_get_percent() {
  unsigned int val = knob_get_raw_value();
  if (val < 40) val = 40; // bottom dead zone
  if (val > 984) val = 984; // top dead zone
  return ((val - 40) * 100.0) / 944.0;
}
