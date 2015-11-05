#ifndef KNOBDRIVER_H
#define KNOBDRIVER_H

#include "Arduino.h"

void knob_setup();

unsigned int knob_get_raw_value();

unsigned int knob_get_percent();

#endif
