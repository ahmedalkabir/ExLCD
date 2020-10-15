#include <LiquidCrystal_I2C.h>
#include <exLCD.hpp>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
exLCD<LiquidCrystal_I2C> new_lcd(&lcd);
// callback function
void lcd_write_character(char c)
{
  new_lcd.write(c);
}

void setup()
{
  // put your setup code here, to run once

  // start with 16x2 LCD
  new_lcd.begin(16, 2, lcd_write_character);

  new_lcd.printf(0, 0, "%d + %d = %d", 1, 2, (1+2));
  
  // show float number in second row
  new_lcd.printf(0, 1, "%.1f + %.1f = %.1f", 1.2, 5.5, (1.2+5.5));
}

void loop()
{
  // put your main code here, to run repeatedly:

}