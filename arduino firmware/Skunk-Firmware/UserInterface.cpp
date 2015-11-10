#include "SkunkPindefs.h"
#include "UserInterface.h"
#include "KeyPadDriver.h"
#include "serLCD.h"

serLCD lcd(PIN_LCD);

int backlightLevel = 30; // Variable for the backlight level of the LCD
bool displayed = false;
char keypadInput = -1;


void ui_reset(){
    state_mode_t state = MAIN_MENU;
  lcd.noCursor();
  lcd.noBlink();
  lcd.leftToRight();
  lcd.home();
  lcd.setBrightness(backlightLevel);
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
	keypadInput = getKeypadInput();
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
				display("Options:","1-Menu 2-BL");
				displayed = true;
			}
		}
	} else {
		if(!displayed) {
			display("Options:","1-Menu 2-BL");
			displayed = true;
		}
		updateGlobalTimer();
		keypadInput = -1; // Ensures it is set to -1 
	}
}

    


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
		btimerB = millis();
		globalTimer += (timerB - timerA);
	} else {
		timerA = millis();
		globalTimer += (timerA - timerB);
	}
	#endif
}

void display(string l1, string l2){
	#ifdef LINUX
	system("clear");
	#else
	system("cls"); //  cls for windows, clear linux/bash, define is at top of file
	#endif

	#ifdef PC
	cout << "----------------" << endl;
	cout << l1.substr(0,16) << endl << l2.substr(0,16)  << endl;
	cout << "----------------" << endl;
	#endif
	
	#ifdef ARDUINO
	// Needs to double check length of strings passed, so not too long
	// Prints out using serLCD libraries
	if(l1 != "") {
		lcd.clearLine(1);
		lcd.print(l1.substr(0,16));
	}
	if(l2 != "") {
		lcd.clearLine(2);
		lcd.print(l2.substr(0,16)); // Means if "" is passed, doesn't redraw line
		
	}
	lcd.selectLine(1); 
	#endif
}

serLCD *ui_lcd(){
  return &lcd;
}

