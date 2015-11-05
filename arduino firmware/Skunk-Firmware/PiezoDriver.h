#ifndef PIEZODRIVER_H
#define PIEZODRIVER_H

#include "Arduino.h"

void piezo_setup();

void piezo_set(boolean bOn);
void piezo_on();
void piezo_off();

#endif
