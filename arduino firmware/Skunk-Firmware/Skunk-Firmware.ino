#include <SoftwareSerial.h> // This has to be included here as Arduino won't give the library PATH to .h files, only .ino files

#include "SkunkPinDefs.h"
#include "KeypadDriver.h"
#include "KeySwitchDriver.h"
#include "PiezoDriver.h"
#include "KnobDriver.h"
#include "UserInterface.h"
#include "FlowmeterDriver.h"

SoftwareSerial flowmeter(3, PIN_LCD); // pin 7 = TX, pin 3 = RX (unused)


void setup(){
  keypad_setup();
  keyswitch_setup();
  piezo_setup();
  knob_setup();
  initialiseFlowmeter(flowmeter);
  
  delay(1000); // Wait for LCD to boot up

  ui_reset();
}


void loop() {
	// Main program loop
	stateMachine();
}






