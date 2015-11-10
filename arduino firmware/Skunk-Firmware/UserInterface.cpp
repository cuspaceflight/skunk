/*
//#define PC
#define ARDUINO
//#define LINUX 
// This is used to choose the system command cls (Windows) or clear (Linux/Bash) when running a simulation.

#ifdef PC
#ifdef ARDUINO
#undef ARDUINO // If both PC and ARDUINO have been defined by accident, compile for PC.
#endif
#endif

#ifdef PC
#include <iostream> 
#include <ctime>
#include <stdlib.h> 
#endif // Various headers not needed by the Arduino, which would waste space.

#ifdef ARDUINO
//#include <serLCD.h> // These are the libraries for the LCD, providing various standard functions.
#endif

*/


#include "SkunkPinDefs.h"
#include "UserInterface.h"
#include "KeyPadDriver.h"
#include "serLCD.h"
#include <Arduino.h>



#define KEYPAD_CONFIRM '#'
#define KEYPAD_RETURN '*'

serLCD lcd(PIN_LCD);

state_mode_t state = MAIN_MENU;

int keypadInput = -1; // KeypadInput value, set & reused later
int targetAmount = 0; // Target fill amount
float currentProgress = 0; // Current filling progress
unsigned long long globalTimer = 0; // Global timer variable - gets reset so used for timing from 0 to 1 for example
unsigned long long timerA = 0,timerB = 0; // Two time keeping variables - don't get reset, used to calculate time difference to update the global timer
bool displayed = false; // Boolean for whether or not the message has been displayed once - stops unessecary redraws, etc.
int backlightLevel = 30; // Variable for the backlight level of the LCD


void ui_reset(){
  state = MAIN_MENU;
  lcd.noCursor();
  lcd.noBlink();
  lcd.leftToRight();
  lcd.home();
  lcd.setBrightness(backlightLevel);
}



void stateMachine()
{
  // Main program loop
  switch(state) {
    case MAIN_MENU:
      mainMenu();
      break;
    case SETTINGS:
      settings();
      break;
    case FILL:
    //  fill();
      break;
    case FILL_ENTER:
    // fillEnter(); // Set target amount to fillEnter value
     break;
    case FILL_CONFIRM:
     // fillConfirm();
      break;
    case FILL_PROGRESS:
    //  fillProgress();
      break;
    case FILL_DONE:
     // fillDone();
      break;
    case BACKLIGHT_ENTER:
     // backlightEnter();
      break;
    case BACKLIGHT_DONE:
     // backlightDone();
      break;
    default:
      changeState(MAIN_MENU); // If for some reason state variable is unset (which should never ever happen) go back to MAIN_MENU!
      break;
  } 
}  
 
 


 

void mainMenu() 
{
if(globalTimer > 500) { // If been on screen for more that 0.5 s
		keypadInput = -1;
		keypadInput = keypad_get_key_pressed();
		if(keypadInput != -1) {
			switch(keypadInput) {
				case 1:
					changeState(FILL);
					break;
				case 2:
					changeState(SETTINGS);
					break;               
				default:
					if(!displayed) {
						display("Menu:","1-Fill 2-Options");
						displayed = true;
					}
					break;			
			}
		} else {
			if(!displayed) {
				display("Menu:","1-Fill 2-Options");
				displayed = true;
			}
		}
	} else {
		if(!displayed) {
			display("Menu ","1-Fill 2-Options");
			displayed = true;
		}
		updateGlobalTimer();
		keypadInput = -1;
	}
}


void settings() {
	if(globalTimer > 500) { // If been on screen for more that 0.5 s
	keypadInput = -1;
	keypadInput = keypad_get_key_pressed();
		if(keypadInput != -1) {
			switch(keypadInput) {
				case 1:
					changeState(MAIN_MENU);
					break;	
				case 2:
					changeState(BACKLIGHT_ENTER);
					break;
				default:
					if(!displayed) {
						display("Options:","1-BackLight");
						displayed = true;
					}
					break;
			}
		} else {
			if(!displayed) {
				display("Options:","1-BackLight");
				displayed = true;
			}
		}
	} else {
		if(!displayed) {
			display("Options:","1-BackLight");
			displayed = true;
		}
		updateGlobalTimer();
		keypadInput = -1; // Ensures it is set to -1 
	}
}

void fill() {
	if(globalTimer > 500) { // If been on screen for more that 0.5 s
		keypadInput = -1;
		keypadInput = keypad_get_key_pressed();
		if(keypadInput != -1) {
			switch(keypadInput) {
				case 1:
					changeState(MAIN_MENU);
					break;	
				case 2:
					changeState(FILL_ENTER);
					break;
				default:
					if(!displayed) {
						display("Fill:","1-Amount");
						displayed = true;
					}
					break;
			}
		} else {
			if(!displayed) {
				display("Fill:","1-Amount");
				displayed = true;
			}
		}
	} else {
		updateGlobalTimer();
		keypadInput = -1; // Ensures it is set to -1 
		if(!displayed) {
			display("Fill:","1-Amount");
			displayed = true;
		}
	}
}    

/*
void fillConfirm() {
//	stringstream ss;
//	ss << "Fill " << targetAmount;
	string l1 = ss.str().substring(0,16);
	display(l1, "*-Return #-Yes");
	if(globalTimer > 500) { // If been on screen for more that 0.5 s
	keypadInput = -1;
	keypadInput = keypad_get_key_pressed();
		if(keypadInput != -1) {
			switch(keypadInput) {
				case 1:
					changeState(MAIN_MENU);
					break;	
				case 2:
					changeState(FILL_PROGRESS);
					break;
				default:
					if(!displayed) {
						display(l1, "*-Return #-Yes");
						displayed = true;
					}
					break;
			}
		} else {
				if(!displayed) {
					display(l1, "*-Return #-Yes");
					displayed = true;
				}		
		}
	} else {
		updateGlobalTimer();
		keypadInput = -1; // Ensures it is set to -1 
		if(!displayed) {
			display(l1, "1-Menu 2-Yes");
			displayed = true;
		}
	}

}
*/


/*
int fillEnter() {
	// Should work for both arduino and standard :)
	int targetAmount = 0;
	//stringstream ss;
	//ss << amount;
	//display("Fill amount:",ss.str().substr(0,16));
	int i = 0;
	while(true) { // 10 means not a number from 1-9 => enter, etc
		i = getKeypadInput();
		if(i > 9) {
			break;
		} else {
			amount *= 10;
			amount += i;
			ss.str("");
			ss << amount;
			#ifdef ARDUINO
			display("",ss.str().substr(0,16));
			#else
			display("Fill amount:",ss.str().substr(0,16));
			#endif
		}
	}
	return amount;
}
*/



void changeState(state_mode_t newstate){
	state = newstate;
	globalTimer = 0; // Resets global timer on state change
	displayed = false; // Resets displayed variable
}

void updateGlobalTimer(){ // Return difference between current time and last time
	#ifdef PC
	if(timerA >= timerB) {
		// so timerA is more recent time
		timerB = (clock()/CLOCKS_PER_SEC)*1000;// So in milliseconds, like arduino
		globalTimer += (timerB - timerA);
	} else {
		timerA = (clock()/CLOCKS_PER_SEC)*1000; 
		globalTimer += (timerA - timerB);
	}	
	#endif
	#ifdef ARDUINO
	if(timerA >= timerB) {
		// so timerA is more recent time
		timerB = millis();
		globalTimer += (timerB - timerA);
	} else {
		timerA = millis();
		globalTimer += (timerA - timerB);
	}
	#endif
}

void display(String l1, String l2){
	#ifdef LINUX
	//system("clear");
	#else
	//system("cls"); //  cls for windows, clear linux/bash, define is at top of file
	#endif

	#ifdef PC
	cout << "----------------" << endl;
	cout << l1.substring(0,16) << endl << l2.substring(0,16)  << endl;
	cout << "----------------" << endl;
	#endif
	
	#ifdef ARDUINO
	// Needs to double check length of strings passed, so not too long
	// Prints out using serLCD libraries
	if(l1 != "") {
		lcd.clearLine(1);
		lcd.print(l1.substring(0,16));
	}
	if(l2 != "") {
		lcd.clearLine(2);
		lcd.print(l2.substring(0,16)); // Means if "" is passed, doesn't redraw line
		
	}
	lcd.selectLine(1); 
	#endif
}

serLCD *ui_lcd(){
  return &lcd;
}

