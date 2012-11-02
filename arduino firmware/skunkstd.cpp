/*
	// Currently untested will be testing later this evening
	
	
	This version of this program is intended to simulate an arduino run for testing.
	Written by Peter Carey (Whippopotamus), 1/11/2012
	
	Will be a modified for arduino, but some parts are missing at the minute, 
	and current parts are commented out in favour of standard.
	
	Arduino will run with setup then loop,
	so make main function run setup(), while(true) { loop() };

*/


//*
#include <iostream> // Not needed for arduino, just used to simulate!
#include <ctime>
#include <stdlib.h> // For clear command
#include <sstream>
//*/

#include <string>

using namespace std;

#define A_MAIN_MENU 1
#define A_SETTINGS 2
#define A_FILL 3 
#define A_FILL_ENTER 4
#define A_FILL_CONFIRM 5
#define A_FILL_PROGRESS 6
#define A_FILL_DONE 7

// Done for passing of arguments meaning enum

//*
void setup(); // Not needed for arduino
void loop(); 
//*/

//Various function prototypes 
void mainMenu(); // Functions to simplify main menu loop
void settings();
void fill();
int fillEnter();
void fillConfirm();
void fillProgress();
void fillDone();

void stopFlow();
void startFlow();
float getAccumulation();

void changeState(int s); // Change state, also resets a tiemr - done so that screens don't look for input unless they've been up long enough! (0.5 Seconds?)
void display(string l1, string l2); // Display 2 lines on LCD (obviously needs more code than will have currently) (assumes 2 lines on LCD, maybe I can do 3??? - need to look at!!)
int getKeypadInput(); // Looks for input from the keypad and returns an integer based on input, returns -1 on no input found
void updateGlobalTimer(); // Updates the global timer, for the moment just adds 0.00001 to it, so time delay depends on how long you wait.
//*
int main() { // Not needed for arduino
	// Behave like an arduino would:
	setup(); 
	while(true){
		loop();
	}
	return 0; // Good practice but never runs of course...
}
//*/ Comment block - code not needed for arduino runs

/*
	All the states the device can be in are:
	Main Menu (Display available options - settings, fill; check for keypad input; respond to keypad input)
	Settings (Display available settings - (unsure if needed!); check for kepad input; respond to keypad input)
	Fill (Display request to enter amount, check for keypad input, respond to keypad input)
	
	Can put into seperate functions which loop until input called for simplicity
		-  Fill Confirm (Display do you want to fill with xxxxx, check for keypad input, respond to keypad input)
		-  Fill Progress (Display current out of total fill, check for keypad input (to cancel), respond to keypad input, update fill progress)
*/

	// Make a enumerated state variable, so we can easily track the state whilst in the loop
	// Mades code much more readable!
	enum mode{MAIN_MENU,SETTINGS,FILL,FILL_ENTER,FILL_CONFIRM,FILL_PROGRESS,FILL_DONE};
	mode state = MAIN_MENU; //Inital state is always the main menu
	int ki = -1; // KeypadInput value, set & reused later
	int targetAmount = 0;
	double globalTimer = 0;
	float cp = 0;


	// (Outside functions to ensure globally accessible, saves effort of passing around)

void setup() {
	/*	Arduino pin setup goes here, not needed normally/breaks normal compile 
	(I don't have an ardunio by my pc :( !!!)
	
	//From prototype
	Serial1.begin(9600); //connected to meter
	Serial2.begin(9600); //connected to screen
	 
	*/
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
			changeState(A_FILL_CONFIRM); // Then change state
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
		default:
			changeState(A_MAIN_MENU); // If for some reason state variable is unset (which should never ever happen) go back to MAIN_MENU!
			break;
	}
}

void mainMenu() {
	display("Menu:","1) Fill 2) Settings");
	if(globalTimer > 1) { // If been on screen for more that 0.5 s
		ki = -1;
		ki = getKeypadInput();
	} else {
		updateGlobalTimer();
		ki = -1; // Ensures it is set to -1
	}
	if(ki != -1) {
		switch(ki) {
			case 1:
				changeState(A_FILL);
				break;
			case 2:
				changeState(A_SETTINGS);
				break;
			default:
				display("Menu: ","1) Fill 2) Settings");
				break;			
		}
	} else {
		display("Menu:","1) Fill 2) Settings");
	}
}

void settings() {
	display("Settings:","1) Main Menu");
	if(globalTimer > 0.5) { // If been on screen for more that 0.5 s
	ki = -1;
	ki = getKeypadInput();
	} else {
		updateGlobalTimer();
		ki = -1; // Ensures it is set to -1 
	}
	if(ki != -1) {
		switch(ki) {
			case 1:
				changeState(A_MAIN_MENU);
				break;	
			default:
				display("Settings:","1) Main Menu");
				break;
		}
	} else {
		display("Settings:","1) Main Menu");
	}
}

void fill() {
	display("Fill:","1) Main Menu 2) Enter Fill Amount");
	if(globalTimer > 0.5) { // If been on screen for more that 0.5 s
		ki = -1;
		ki = getKeypadInput();
	} else {
		updateGlobalTimer();
		ki = -1; // Ensures it is set to -1 
	}
	if(ki != -1) {
		switch(ki) {
			case 1:
				changeState(A_MAIN_MENU);
				break;	
			case 2:
				changeState(A_FILL_ENTER);
				break;
			default:
				display("Fill:","1) Main Menu 2) Enter Fill Amount");
				break;
		}
	} else {
		display("Fill:","1) Main Menu 2) Enter Fill Amount");
	}
}

int fillEnter() {
	// Should work for both arduino and standard :)
	int amount = 0;
	stringstream ss;
	ss << amount;
	display("Fill amount:",ss.str());
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
			display("Fill amount:",ss.str());
		}
	}
	return amount;
}

void fillConfirm() {
	stringstream ss;
	ss << "1)Menu 2)Continue (" << targetAmount << ")";
	string l2 = ss.str();
	display("Confirm Fill Amount:", l2);
	//if(globalTimer > 0.5) { // If been on screen for more that 0.5 s
	ki = -1;
	ki = getKeypadInput();
	//} else {
	//	updateGlobalTimer();
	//	ki = -1; // Ensures it is set to -1 }
	if(ki != -1) {
		switch(ki) {
			case 1:
				changeState(A_MAIN_MENU);
				break;	
			case 2:
				changeState(A_FILL_PROGRESS);
				break;
			default:
				display("Confirm Fill Amount:", l2);
				break;
		}
	} else {
				display("Confirm Fill Amount: ", l2);
	}
}


void fillProgress(){	
	startFlow();
	string l1,l2;
	while(cp < targetAmount) {
			cp += 10;
			// cp += getAccumulation();
			stringstream ss;
			ss << "Progress " << cp;
			l1 = ss.str();
			ss.str("");
			ss << "Target  " << targetAmount;
			l2 = ss.str();
			display(l1,l2);
	}
	changeState(A_FILL_DONE);
}

void fillDone() {
	//Display complete message for 5 seconds, then go back to main menu
	stringstream ss;
	ss << "Done (" << cp << ")";
	display(ss.str(),"Have a nice day!");
	globalTimer = 0;
	while(globalTimer < 18000) { //The way the timer is working is really odd, need to look into it - is it using real time? (probably not!!)
		updateGlobalTimer();
	}
	changeState(A_MAIN_MENU);
}

void changeState(int s) {
	// Switches the integer passed to it for a state change
	switch(s) {
		case 1: 
			state = MAIN_MENU;
			break;
		case 2:
			state = SETTINGS;
			break;
		case 3:
			state = FILL;
			break;
		case 4:
			state = FILL_ENTER;
			break;
		case 5:
			state = FILL_CONFIRM;
			break;
		case 6:
			state = FILL_PROGRESS;
			break;
		case 7:
			state = FILL_DONE;
			break;
		default:
			state = MAIN_MENU; //Defaults to MAIN_MENU if incorrect parameter is sent
			break;
	}
	globalTimer = 0; // Resets global timer on state change!
}

void display(string l1, string l2){
	system("cls"); //  cls for windows, clear linux/bash
	
	// Standard version, need different for arduino of course
	//*
	cout << "--------------------------------------" << endl;
	cout << l1 << endl << l2 << endl;
	cout << "--------------------------------------" << endl;
	//*/
	// Arduino version:
	// Needs to double check length of strings passed, so not too long
	/* code from 'brief untested prototype', modified
	char line1[16];
	char line2[16];
	sprintf(line1, "%s", l1.substr(0,16); // Print first 16 characters, just incase
	sprintf(line2, "%s", l2.substr(0,16)); // Dont know if can only print 16 chars!?
	Serial2.println(line1);
	Serial2.println(line2); 
	*/
}

int getKeypadInput() {
	// Standard version, need different for arduino of course
	//* WHEN USING HERE, SIMPLY TYPE ONE NUMBER AT A TIME, > 9 = enter equivalent
	int value = 0;
	cin >> value;
	return value;
	//*/
	// Arduino version:
	
}

void updateGlobalTimer(){
	// Standard Version - Use different for arduino of course
	//*
	globalTimer = clock();
	 // Update smallest to current time
	//*/
	// Arduino version:
}
void startFlow() {
	// How do you start the flow??????
	// Does nothing at the minute
}

float getAccumulation() {
  /*float result;
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
  return result; // From prototype*/
  return 0.0;
}

void stopFlow() {
	// From prototype
	//Serial1.println(":06030101210000");
}