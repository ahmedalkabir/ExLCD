#ifndef _EX_LCD_H_
#define _EX_LCD_H_

#include <printf.h>

/*
    exLCD it's extended LCD library to extend some functionality of LCD libraries
    the reason of creating this library it's to improve the way of showing data
    to lcd displays and provide a neat way of formating by including printf like functions
*/
// callback type
using callback_func = void (*)(char);
callback_func __cb = nullptr;

template <typename T>
class exLCD : public T
{
public:
    /*
        class constructor used for initialize the library by providing  
        an object of LCD or any library inherit from LCD Class
        or evne Print Class
    */
    exLCD(T *lcd) : T(static_cast<T &&>(*lcd))
    {
    }

    /*
        this a wrapper around begin method that used by 
        T class with additional argument which is callback of this class
        and must be provided by the user 

        example of callback should be like
        void lcd_callback(char c)
        {
            lcd_object.write(c);
        }

        the wrapper should be called inside setup() block

        col --- columnd of lcd display
        row --- row of lcd display
        cb --- callback function that works as bridge between lcd and the class
    */
    void begin(int col, int row, callback_func cb)
    {
        _lcd_col = col;
        _lcd_row = row;
        // Initialize the lcd and set the cursor at
        // the beginning
        T::begin(col, row);
        T::home();
        T::setCursor(0, 0);
        __cb = cb;
    }

    /*
        an imporved print method that can be print text 
        based on the location of the lcd provided by the user,
        and can replace the old buffer with any flickering  

        col --- columnd of lcd display
        row --- row of lcd display
        text --- text, and the text must be passed in c-like type string
    */
    void print(uint8_t col, uint8_t row, const char *text)
    {
        T::setCursor(col, row);
        uint8_t ending = strlen(text) + col;
        // clear the buffer
        for (uint8_t i = 0; i < col; i++)
        {
            T::setCursor(i, row);
            T::print(" ");
        }

        // write text to lcd
        T::setCursor(col, row);
        T::print(text);

        // also clear the buffer
        for (uint8_t i = ending; i < _lcd_col; i++)
        {
            T::setCursor(i, row);
            T::print(" ");
        }
    }

    /*
        same as print except add new line
    */
    void println(uint8_t col, uint8_t row, const char *text)
    {
        T::print(col, row, text);
        T::print("\n");
    }

    /*
        printf like method, it's same as printf except you must 
        add the location of text you want to send to lcd
        
        col --- columnd of lcd display
        row --- row of lcd display
        fmt --- format of text.

        this method is really like printf style look at this example below 
        lcd_object.printf(0, 0, "hey %d", 1);
        it will show
        hey 1
    */
    void printf(uint8_t col, uint8_t row, const char *__fmt, ...)
    {
        va_list args;
        va_start(args, __fmt);
        T::setCursor(col, row);
        // vfprintf(&lcd_stream, __fmt, args);
        vprintf(__fmt, args);
        // let's clear the rest of row and the before string
        for (uint8_t i = col + 1; i < _lcd_col; i++)
        {
            T::write(' ');
        }
        T::setCursor(0, row);
        for (uint8_t i = 0; i < col; i++)
        {
            T::write(' ');
        }
    }

    /*
        to clear the row of lcd display
    */
    void clear(uint8_t row)
    {
        for (uint8_t i = 0; i < _lcd_col; i++)
        {
            T::print(" ");
            T::setCursor(i, row);
        }
    }

private:
    uint8_t _lcd_col;
    uint8_t _lcd_row;
};

// internal callback of this library 
// don't touch it
void _putchar(char c)
{
    __cb(c);
}

#endif