#include <SoftwareSerial.h> // This has to be included here as Arduino won't give the library PATH to .h files, only .ino files

#include "SkunkPinDefs.h"
#include "KeypadDriver.h"
#include "KeySwitchDriver.h"
#include "PiezoDriver.h"
#include "KnobDriver.h"
#include "UserInterface.h"
#include "FlowmeterDriver.h"

SoftwareSerial flowmeter(3, PIN_LCD); // pin 7 = TX, pin 3 = RX (unused)

int state;

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
	switch(state) {
		case MAIN_MENU:
			mainMenu();
			break;
		case SETTINGS:
			settings();
			break;
		case FILL:
			fill();
			break;
		case FILL_ENTER:
            fillEnter(); // Set target amount to fillEnter value
            break;
		case FILL_CONFIRM:
			fillConfirm();
			break;
		case FILL_PROGRESS:
			fillProgress();
			break;
		case FILL_DONE:
			fillDone();
			break;
		case BACKLIGHT_ENTER:
			backlightEnter();
			break;
		case BACKLIGHT_DONE:
			backlightDone();
			break;
		default:
			changeState(MAIN_MENU); // If for some reason state variable is unset (which should never ever happen) go back to MAIN_MENU!
			break;
	}
}






