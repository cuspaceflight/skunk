#include <SoftwareSerial.h> // This has to be included here as Arduino won't give the libarary PATH to .h files, only .ino files

#include "KeypadDriver.h"
#include "KeySwitchDriver.h"
#include "PiezoDriver.h"
#include "KnobDriver.h"
#include "serLCD.h"

serLCD lcd(7);

void setup(){
  keypad_setup();
  keyswitch_setup();
  piezo_setup();
  knob_setup();
  
  lcd.clear();
  lcd.write("HELLO");
  lcd.selectLine(2);
  lcd.write("WORLD");
}

void loop(){
  char c = keypad_get_key_pressed();
  
  if(c>-1){
    lcd.setCursor(1,1);
    lcd.write(c);
  }
  
  if( keyswitch_on() || (knob_get_percent() > 50) || (c == '5') ){
    piezo_on();
  }else{
    piezo_off();
  }
}

