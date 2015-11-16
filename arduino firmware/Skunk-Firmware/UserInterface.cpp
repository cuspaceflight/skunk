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
#include "KeypadDriver.h"
#include "PiezoDriver.h"
#include "FlowmeterDriver.h"
#include "KnobDriver.h"
#include "serLCD.h"
#include <Arduino.h>


#define KEYPAD_CONFIRM '#'
#define KEYPAD_RETURN '*'

serLCD lcd(PIN_LCD);

state_mode_t state = SPLASH;

int keypadInput = -1; // KeypadInput value, set & reused later
long targetAmount = 0; // Target fill amount
float currentProgress = 0; // Current filling progress
unsigned long long globalTimer = 0; // Global timer variable - gets reset so used for timing from 0 to 1 for example
unsigned long long timerA = 0, timerB = 0; // Two time keeping variables - don't get reset, used to calculate time difference to update the global timer
bool displayed = false; // Boolean for whether or not the message has been displayed once - stops unessecary redraws, etc.
int backlightLevel = 30; // Variable for the backlight level of the LCD
boolean cancelPending = false; // Boolean for whether the operator wants to cancel the fill

void ui_reset() {
  pinMode(53, INPUT); // High impedance - these clash with hardware UART 1
  pinMode(9, INPUT);

  lcd.clear();
  //lcd.noCursor();
  //lcd.noBlink();
  //lcd.leftToRight();
  //lcd.home();
  lcd.setBrightness(backlightLevel);

  changeState(SPLASH);

}



void stateMachine()
{
  // Main program loop
  switch (state) {
    case SPLASH:
      showSplash();
      break;
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
      fillEnter();
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
    case FLOW_ERROR:
      flowError();
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

void showSplash() {
  if (globalTimer > 2000) { // advance to main menu after 2 seconds
    changeState(MAIN_MENU);
  } else {
    if (!displayed) {
      display("   SKUNK 2.0    ", "   CUSF 2015    ");
      displayed = true;
    }
    updateGlobalTimer();
  }
}

void mainMenu()
{
  if (globalTimer > 500) { // If been on screen for more that 0.5 s
    keypadInput = -1;
    keypadInput = keypad_get_key_pressed();
    if (keypadInput != -1) {
      switch (keypadInput) {
        case '1':
          changeState(FILL);
          break;
        case '2':
          changeState(SETTINGS);
          break;
        default:
          if (!displayed) {
            display("Skunk 2.0 Menu:", "1-Fill 2-Options");
            displayed = true;
          }
          break;
      }
    } else {
      if (!displayed) {
        display("Skunk 2.0 Menu:", "1-Fill 2-Options");
        displayed = true;
      }
    }
  } else {
    if (!displayed) {
      display("Skunk 2.0 Menu ", "1-Fill 2-Options");
      displayed = true;
    }
    updateGlobalTimer();
    keypadInput = -1;
  }
}


void settings() {
  if (globalTimer > 500) { // If been on screen for more that 0.5 s
    keypadInput = -1;
    keypadInput = keypad_get_key_pressed();
    if (keypadInput != -1) {
      switch (keypadInput) {
        case '*':
          changeState(MAIN_MENU);
          break;
        case '1':
          changeState(BACKLIGHT_ENTER);
          break;
        default:
          if (!displayed) {
            display("Options:", "1-Backlight");
            displayed = true;
          }
          break;
      }
    } else {
      if (!displayed) {
        display("Options:", "1-Backlight");
        displayed = true;
      }
    }
  } else {
    if (!displayed) {
      display("Options:", "1-BackLight");
      displayed = true;
    }
    updateGlobalTimer();
    keypadInput = -1; // Ensures it is set to -1
  }
}

void fill() {
  if (globalTimer > 500) { // If been on screen for more that 0.5 s
    keypadInput = -1;
    keypadInput = keypad_get_key_pressed();
    if (keypadInput != -1) {
      switch (keypadInput) {
        case '*':
          changeState(MAIN_MENU);
          break;
        case '1':
          changeState(FILL_ENTER);
          break;
        default:
          if (!displayed) {
            display("Fill:", "1-Amount");
            displayed = true;
          }
          break;
      }
    } else {
      if (!displayed) {
        display("Fill:", "1-Amount");
        displayed = true;
      }
    }
  } else {
    updateGlobalTimer();
    keypadInput = -1; // Ensures it is set to -1
    if (!displayed) {
      display("Fill:", "1-Amount");
      displayed = true;
    }
  }
}

void fillConfirm() {
  char tmp[17];
  snprintf(tmp, 17, "Fill %d", targetAmount);
  if (globalTimer > 500) { // If been on screen for more that 0.5 s
    keypadInput = -1;
    keypadInput = keypad_get_key_pressed();
    if (keypadInput != -1) {
      switch (keypadInput) {
        case '*':
          changeState(MAIN_MENU);
          break;
        case '#':
          changeState(FILL_PROGRESS);
          break;
        default:
          if (!displayed) {
            display(String(tmp), "*-Return #-Yes");
            displayed = true;
          }
          break;
      }
    } else {
      if (!displayed) {
        display(String(tmp), "*-Return #-Yes");
        displayed = true;
      }
    }
  } else {
    updateGlobalTimer();
    keypadInput = -1; // Ensures it is set to -1
    if (!displayed) {
      display(String(tmp), "*-Return #-Yes");
      displayed = true;
    }
  }

}

void fillEnter() {
  long amount = 0;
  display("Fill amount:", String(amount, DEC));
  int i = 0;
  while (true) { // 10 means not a number from 1-9 => enter, etc
    i = keypad_get_key_pressed();
    if (i == '*') { // cancel
      changeState(FILL);
      return;
    } else if (i == '#') { // confirm
      break;
    } else if (i >= '0' && i <= '9') { // a digit
      amount *= 10;
      amount += (i - '0');
      display("Fill amount:", String(amount, DEC));
      while (keypad_get_key_pressed() != -1) { // Wait for key release
        ;
      }
    }
  }
  targetAmount = amount; // update the target amount
  changeState(FILL_CONFIRM);
}

void fillProgress() {
  char tmp[17];
  static boolean keyheld = false;
  static unsigned int flowrate = 0;
  float tmpProgress = 0.0;
  dtostrf(currentProgress, 4, 2, tmp);
  if (!displayed) {
    display("Fill " + String(tmp)  +"/" + String(targetAmount), "Rate 0%");
    displayed = true;
  }
  //flowmeter_start_flow();
  while (currentProgress < targetAmount) {
    tmpProgress = flowmeter_get_accumulation();
    if(tmpProgress < 0){ // there was an error
      //changeState(FLOW_ERROR);
      //flowmeter_stop_flow();
      //return;
    }else{
      currentProgress = tmpProgress;
    }
    if (currentProgress >= targetAmount) break; // stop as soon as possible if we're done

    flowrate = knob_get_percent(); // update the valve position to that of the control knob
    flowmeter_set_valve(flowrate);
    
    dtostrf(currentProgress, 4, 2, tmp); // render the current progress to a string
    
    keypadInput = keypad_get_key_pressed();
    if (keyheld) {
      if (keypadInput == -1) keyheld = false; // wait for the key to be released
    } else {
      if (keypadInput == '*') {
        if (cancelPending) {
          cancelPending = false; // cancel the pending cancel :^)
          displayed = false; // force a redraw
        } else {
          cancelPending = true; // mark that there is a cancel pending
        }
        keyheld = true;
      } else if (keypadInput == '#') {
        if (cancelPending) {
          break; // actually cancel
        }
      }
    }
    if (!displayed) {
      if (cancelPending) {
        display("REALLY CANCEL??", "*-NO #-YES");
      } else {
        display("Fill " + String(tmp) + "/" + String(targetAmount), "Rate " + String(flowrate) + "%");
      }
      displayed = true;
    }
    if (globalTimer >= 1000) { // redraw once per second
      globalTimer = 0;
      displayed = false;
    } else {
      updateGlobalTimer();
    }
  }
  flowmeter_stop_flow();
  changeState(FILL_DONE);
}

void fillDone() {
  //Display complete message for 5 seconds, then go back to main menu
  char fstr[10];
  char tmp[17];
  dtostrf(currentProgress, 4, 2, fstr);
  snprintf(tmp, 17, "Filled %s", fstr);
  display(String(tmp), "Have a nice day!");

  globalTimer = 0;
  while (globalTimer < 5000) {
    updateGlobalTimer();
  }
  changeState(MAIN_MENU);
}

void flowError(){
  //Display complete message for 5 seconds, then go back to main menu
  char fstr[10];
  char tmp[17];
  dtostrf(currentProgress, 4, 2, fstr);
  snprintf(tmp, 17, "Filled %s", fstr);
  display("FLOW ERROR!", String(tmp));

  globalTimer = 0;
  while (globalTimer < 5000) {
    updateGlobalTimer();
  }
  changeState(MAIN_MENU);
}

void backlightEnter() {
  int amount = 0;
  char tmp[17];
  snprintf(tmp, 17, "(%d) %d", backlightLevel, amount);
  display("Backlight 1-30", String(tmp));
  int i = 0;
  while (true) {
    i = keypad_get_key_pressed();
    if (i == '*') { // cancel
      changeState(SETTINGS);
      return;
    } else if (i == '#') { // confirm
      break;
    } else if (i >= '0' && i <= '9') { // a digit
      amount *= 10;
      amount += (i - '0');
      if (amount > 30) { // cap the level at 30
        amount = 30;
      }
      snprintf(tmp, 17, "(%d) %d", backlightLevel, amount);
      display("Backlight 1-30", String(tmp));
      while (keypad_get_key_pressed() != -1) { // Wait for key release
        ;
      }
    }
  }

  backlightLevel = amount;

  if (backlightLevel > 30) {
    backlightLevel = 30;
  }
  if (backlightLevel < 1) {
    backlightLevel = 1;
  }

  lcd.setBrightness(backlightLevel);
  changeState(BACKLIGHT_DONE);
}

void backlightDone() {
  //Display complete message for 5 seconds, then go back to main menu
  char tmp[17];
  snprintf(tmp, 17, "set to %d / 30", backlightLevel);
  display("Backlight level", String(tmp));
  globalTimer = 0;
  while (globalTimer < 5000) {
    if (globalTimer > 500 && keypad_get_key_pressed() != -1) { // after 500ms, press any key to skip to menu
      changeState(MAIN_MENU);
      return;
    }
    updateGlobalTimer();
  }
  changeState(MAIN_MENU);
}

void changeState(state_mode_t newstate) {
  state = newstate;
  updateGlobalTimer();
  globalTimer = 0; // Resets global timer on state change
  displayed = false; // Resets displayed variable
  piezo_beep(50); // short beep for feedback
}

void updateGlobalTimer() { // Return difference between current time and last time
  if (timerA >= timerB) {
    // so timerA is more recent time
    timerB = millis();
    globalTimer += (timerB - timerA);
  } else {
    timerA = millis();
    globalTimer += (timerA - timerB);
  }
}

void display(String l1, String l2) {
  // Needs to double check length of strings passed, so not too long
  // Prints out using serLCD libraries
  if (l1 != "") {
    lcd.clearLine(1);
    lcd.print(l1.substring(0, 16));
  }
  if (l2 != "") {
    lcd.clearLine(2);
    lcd.print(l2.substring(0, 16)); // Means if "" is passed, doesn't redraw line

  }
  lcd.selectLine(1);
}

serLCD *ui_lcd() {
  return &lcd;
}

