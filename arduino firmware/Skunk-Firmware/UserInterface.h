#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "serLCD.h"

enum state_mode_t{MAIN_MENU,SETTINGS,FILL, TEST, FILL_ENTER,FILL_CONFIRM,FILL_PROGRESS,FILL_DONE,BACKLIGHT_ENTER,BACKLIGHT_DONE};



void ui_reset();

serLCD *ui_lcd();


void stateMachine();
/* Functions depending on your current state*/
void mainMenu(); 
void settings();

void fill();	//Filling functions
int fillEnter();
void fillConfirm();
void fillProgress();
void fillDone();

void backlightEnter(); // Backlight controls
void backlightDone();

void changeState(state_mode_t newstate);

void display(String l1, String l2);
void updateGlobalTimer(); // Return difference between current time and last time


#endif
