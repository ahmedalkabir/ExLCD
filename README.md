# exLCD
exLCD it's extended LCD library to extend some functionality of LCD libraries
the reason of creating this library it's to improve the way of showing data
to lcd displays and provide a neat way of formating by including printf like functions

# How to use it 
Well, you need to instantiate from any LCD library you use as they all inherit from 
LCD class and pass the object to exLCD class and use the exLCD instead of old one because 
it has all same functionality that come with LCD libraries.

look at this snippet below 
In the code I used 16x2 I2C based LCD Display but you can use even the generic one without
any problem

Note: you should write the callback function as shown without it, the library will not able to function properly
      and pass it to begin method as shown in setup block.


```c++
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

  new_lcd.begin(16, 2, lcd_write_character);

  new_lcd.printf(0, 0, "exLCD");
}

void loop()
{
  // put your main code here, to run repeatedly:

}
```