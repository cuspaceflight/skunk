/*
	Note: Will fail if runs too long as a result of arduino timer resetting (approx 50 days)
	Very unlikey! (The battery should only last a couple of hours...)
	
	- Updates 3/11/2012:
		+ Followed some suggestions concerning defining arduino or PC at start of program, to allow certain parts to compile depending on situation - Many thanks to Adam and David.
		+ Added in serLCD libraries to same folder and interatctions in display function.
		+ Shortened all strings to only output max 16 chars, and added double checkeypadInputng on display, and at other places
		+ Some restructuring of various functions for display improvements (no redraws if not needed etc)
		+ Backlight setting added
		+ Arduino updateGlobalTimer now deals with the overflow of millis() with a minor pause, this could take 50 days to occur, and its unlikely that its gonna be left on that long, but better safe than sorry
	
	- Initial Code 1/11/2012
		+ Wrote main body of code, handled states, etc, written for a simulation on a PC
	
	------------------
	Arduino code completion:
		
		[/] display
		[/] updateGlobalTimer
		[/] getAccumulation
		[/] stopFlow
		
		[ ] startFlow
		[ ] getKeypadInput
		
	------------------
	[ ] = not done, [/] = written but untested, [X] = done
*/

// Alters whether to compile for an Arduino or a PC (simulation)
#define PC
//#define ARDUINO
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
#include <serLCD.h> // These are the libraries for the LCD, providing various standard functions.
#endif

#include <string>
#include <sstream>

using namespace std;

//============================== Global variables ================================

// Enum used for various states
enum mode{MAIN_MENU,SETTINGS,FILL,FILL_ENTER,FILL_CONFIRM,FILL_PROGRESS,FILL_DONE,BACKLIGHT_ENTER,BACKLIGHT_DONE};
mode state = MAIN_MENU; //Inital state is always the main menu

int keypadInput = -1; // KeypadInput value, set & reused later
int targetAmount = 0; // Target fill amount
float currentProgress = 0; // Current filling progress
unsigned long long globalTimer = 0; // Global timer variable - gets reset so used for timing from 0 to 1 for example
unsigned long long timerA = 0,timerB = 0; // Two time keeping variables - don't get reset, used to calculate time difference to update the global timer
bool displayed = false; // Boolean for whether or not the message has been displayed once - stops unessecary redraws, etc.
int backlightLevel = 30; // Variable for the backlight level of the LCD

#ifdef ARDUINO
serLCD lcd(2); // make an lcd object using the serLCD libraries on pin 2
#endif

//============================ Function Definitions ==============================
#ifdef PC
void setup(); // Not needed for arduino, as these are just used in main function
void loop(); 
#endif

//Various function prototypes 
void mainMenu(); 
void settings();

void fill();	//Filling functions
int fillEnter();
void fillConfirm();
void fillProgress();
void fillDone();

void backlightEnter(); // Backlight controls
void backlightDone();

void stopFlow(); // Controlling of flowmeter
void startFlow();
float getAccumulation();

void changeState(enum mode newstate); // Change state, also resets the timer - done so that screens don't look for input unless they've been up long enough! (0.5 Seconds?)
void display(string l1, string l2); // Display 2 lines on LCD (obviously needs more code than will have currently) (assumes 2 lines on LCD, maybe I can do 3??? - need to look at!!)
int getKeypadInput(); // Looks for input from the keypad and returns an integer based on input, returns -1 on no input found
void updateGlobalTimer(); // Updates the global timer


// ============================ Function Declarations ============================

#ifdef PC
int main() { 
	/*
	Arduino will run with setup then loop,
	so make main function run setup(), while(true) { loop() };
	*/
	setup(); 
	while(true){ 
		loop();
	}
	return 0; // 'Good' practice but never runs of course...
}
#endif

/*
	All the states the device can be in are:
	Main Menu (Display available options - settings, fill; check for keypad input; respond to keypad input)
	Settings (Display available settings - (unsure if needed!); check for kepad input; respond to keypad input)
	Fill (Display request to enter amount, check for keypad input, respond to keypad input)
	
	Can put into seperate functions which loop until input called for simplicity
		-  Fill Confirm (Display do you want to fill with xxxxx, check for keypad input, respond to keypad input)
		-  Fill Progress (Display current out of total fill, check for keypad input (to cancel), respond to keypad input, update fill progress)
*/

void setup() {
	/*	Arduino pin setup goes here, not needed normally/breaks normal compile */
	
	#ifdef ARDUINO
	Serial1.begin(9600); // Connect to flowmeter
	
	//LCD
	lcd.noCursor();
	lcd.noBlink();
	lcd.leftToRight();
	lcd.home(); // Set no cursor, blink, left to right (should be default) and ensure in top left
	lcd.setBrightness(backlightLevel); // Full brightness
	// Probably dont need all of these commands, just ensures LCD is as we want
	// Also, read somewhere that if LCD is connected when Arduino is written to, there is a chance properties will change, so this should deal with that
	
	
	#endif
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
			targetAmount = fillEnter(); // Set target amount to fillEnter value
			changeState(FILL_CONFIRM); // Then change state
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

void mainMenu() {
	if(globalTimer > 500) { // If been on screen for more that 0.5 s
		keypadInput = -1;
		keypadInput = getKeypadInput();
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
						display("Options:","1-Menu 2-BL");
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

void backlightEnter() {
	// Should work for both arduino and standard :)
	int amount = 0;
	stringstream ss;
	ss << "(" << backlightLevel << ") " << amount;
	display("Backlight 1-30",ss.str().substr(0,16));
	int i = 0;
	while(true) { // 10 means not a number from 1-9 => enter, etc
		i = getKeypadInput();
		if(i > 9) {
			break;
		} else {
			amount *= 10;
			amount += i;
			ss.str("");
			ss << "(" << backlightLevel << ") " << amount;
			#ifdef ARDUINO
			display("",ss.str().substr(0,16));
			#else
			display("Backlight 1-30",ss.str().substr(0,16));
			#endif
		}
	}
	backlightLevel = amount;
	
	if(backlightLevel > 30) {
		backlightLevel = 30;
	}
	if(backlightLevel < 1){
		backlightLevel = 1;
	}
	
	#ifdef ARDUINO
	lcd.setBrightness(backlightLevel);
	#endif
	changeState(BACKLIGHT_DONE);
}

void backlightDone() {
	//Display complete message for 5 seconds, then go back to main menu
	stringstream ss;
	ss << backlightLevel;
	display("Backlight set to",ss.str().substr(0,16));
	globalTimer = 0;
	while(globalTimer < 5000) {
		updateGlobalTimer();
	}
	changeState(MAIN_MENU);
}

void fill() {
	if(globalTimer > 500) { // If been on screen for more that 0.5 s
		keypadInput = -1;
		keypadInput = getKeypadInput();
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
						display("Fill:","1-Menu 2-Amount");
						displayed = true;
					}
					break;
			}
		} else {
			if(!displayed) {
				display("Fill:","1-Menu 2-Amount");
				displayed = true;
			}
		}
	} else {
		updateGlobalTimer();
		keypadInput = -1; // Ensures it is set to -1 
		if(!displayed) {
			display("Fill:","1-Menu 2-Amount");
			displayed = true;
		}
	}

}

int fillEnter() {
	// Should work for both arduino and standard :)
	int amount = 0;
	stringstream ss;
	ss << amount;
	display("Fill amount:",ss.str().substr(0,16));
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

void fillConfirm() {
	stringstream ss;
	ss << "Fill " << targetAmount;
	string l1 = ss.str().substr(0,16);
	display(l1, "1-Menu 2-Yes");
	if(globalTimer > 500) { // If been on screen for more that 0.5 s
	keypadInput = -1;
	keypadInput = getKeypadInput();
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
						display(l1, "1-Menu 2-Yes");
						displayed = true;
					}
					break;
			}
		} else {
				if(!displayed) {
					display(l1, "1-Menu 2-Yes");
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

void fillProgress(){	
	string target = "";
	if(!displayed) {
		stringstream sa;
		sa << "Target " << targetAmount;
		#ifdef PC
		target = sa.str().substr(0,16);
		#endif
		display("Progress 0", sa.str().substr(0,16));	
		displayed = true;
	}
	startFlow();
	string l1,l2;
	while(currentProgress < targetAmount) {
			#ifdef PC
			currentProgress += 10;
			#endif
			#ifdef ARDUINO
			currentProgress = getAccumulation();
			#endif
			stringstream ss;
			ss << "Progress " << currentProgress;
			l1 = ss.str().substr(0,16);
			ss.str("");
			#ifdef ARDUINO
			display(l1,"");
			#else
			display(l1,target);		
			#endif
	}
	changeState(FILL_DONE);
}

void fillDone() {
	//Display complete message for 5 seconds, then go back to main menu
	stringstream ss;
	ss << "Filled " << currentProgress;
	display(ss.str().substr(0,16),"Have a nice day!");
	globalTimer = 0;
	while(globalTimer < 5000) {
		updateGlobalTimer();
	}
	changeState(MAIN_MENU);
}

void changeState(mode newstate){
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

int getKeypadInput() {
	// When running sim, type one number at a time from 0 - 9, > 9 = enter equivalent, that is, returns 10
	#ifdef PC
	int value = 0;
	cin >> value;
	if(value > 9) {
		value = 10;
	}
	return value;
	#endif
	
	// Arduino version:
	#ifdef ARDUINO
	
	// Not implemented yet - needs some lab time to do
	
	#endif	
}

void startFlow() {
	// How do you start the flow??????
	// Does nothing at the minute
	#ifdef ARDUINO
	
	#endif
}

float getAccumulation() {
	#ifdef ARDUINO // From prototype*/
	float result;
	int incomingmessage[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	Serial1.println(":06030468416841");
	if (Serial1.available()>11) { //check the whole string is there
		for (i=0; i<12; i=i+1)
		{
			incomingmessage[i]=Serial1.read();
		}
		if (incomingmessage[6]<128){
		//Code to turn four byte hex into float
		union u_tag {
			byte b[4];
			float fval;
		} 
		u;
		u.b[0] = incomingmessage[6];
		u.b[1] = incomingmessage[7];
		u.b[2] = incomingmessage[8];
		u.b[3] = incomingmessage[9];
		result = u.fval;
		}
	}
	return result; 
	#endif
	
	#ifdef PC
	return 0.0;
	#endif
}

void stopFlow() {
	#ifdef ARDUINO
		// From prototype
		Serial1.println(":06030101210000");
	#endif
}
