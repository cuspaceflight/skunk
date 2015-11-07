#include <SoftwareSerial.h> // This has to be included here as Arduino won't give the library PATH to .h files, only .ino files

#include "SkunkPindefs.h"

#include "KeypadDriver.h"
#include "KeySwitchDriver.h"
#include "PiezoDriver.h"
#include "KnobDriver.h"
#include "UserInterface.h"
#include "FlowmeterDriver.h"

void setup(){
  keypad_setup();
  keyswitch_setup();
  piezo_setup();
  knob_setup();
  flowmeter_setup();
  
  delay(1000); // Wait for LCD to boot up

  ui_reset();
}

void loop(){
  char c = keypad_get_key_pressed();
  
  if(c>-1){
    ui_lcd()->setCursor(1,1);
    ui_lcd()->write(c);
  }
  
  if( keyswitch_on() || (knob_get_percent() > 50) || (c == '5') ){
    piezo_on();
  }else{
    piezo_off();
  }
}

