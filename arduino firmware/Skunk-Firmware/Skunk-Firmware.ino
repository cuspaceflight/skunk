#include <SoftwareSerial.h> // This has to be included here as Arduino won't give the library PATH to .h files, only .ino files

#include "SkunkPinDefs.h"
#include "KeypadDriver.h"
#include "KeySwitchDriver.h"
#include "PiezoDriver.h"
#include "KnobDriver.h"
#include "UserInterface.h"
#include "FlowmeterDriver.h"

void setup(){
  Serial.begin(38400);
  keypad_setup();
  keyswitch_setup();
  piezo_setup();
  knob_setup();

  ui_reset();
  showSplash();
  
  flowmeter_setup();
}


void loop() {
	// Main program loop
	stateMachine();
}






