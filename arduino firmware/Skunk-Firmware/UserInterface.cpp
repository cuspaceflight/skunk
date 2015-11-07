#include "SkunkPindefs.h"
#include "UserInterface.h"
#include "serLCD.h"

serLCD lcd(PIN_LCD);

int backlightLevel = 30; // Variable for the backlight level of the LCD

void ui_reset(){
  lcd.noCursor();
  lcd.noBlink();
  lcd.leftToRight();
  lcd.home();
  lcd.setBrightness(backlightLevel);
}

serLCD *ui_lcd(){
  return &lcd;
}

