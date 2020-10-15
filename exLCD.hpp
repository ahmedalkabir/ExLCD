#ifndef _EX_LCD_H_
#define _EX_LCD_H_

#include <printf.h>

/*
    exLCD it's extended LCD library
*/

using callback_func = void (*)(char);
callback_func __cb = nullptr;

template <typename T>
class exLCD : public T
{
public:
    exLCD(T *lcd) : T(static_cast<LiquidCrystal_I2C &&>(*lcd))
    {
    }

    void begin_exLCD(int col, int row, callback_func cb)
    {
        _col = col;
        _row = row;
        T::begin(col, row);
        T::home();
        T::setCursor(col, row);
        __cb = cb;
    }

    template <typename U>
    void print(uint8_t col, uint8_t row, U &text)
    {
        T::setCursor(col, row);
        // T::print(v);
        uint8_t ending = strlen(text) + col;
        // lcd.setCursor(col, row);
        // start writing
        for (uint8_t i = 0; i < col; i++)
        {
            T::setCursor(i, row);
            T::print(" ");
        }
        T::setCursor(col, row);
        T::print(text);

        for (uint8_t i = ending; i < 20; i++)
        {
            T::setCursor(i, row);
            T::print(" ");
        }
    }

    template <typename U>
    void println(uint8_t col, uint8_t row, U &v)
    {
        T::setCursor(col, row);
        T::println(v);
    }

    void printf(uint8_t col, uint8_t row, const char *__fmt, ...)
    {
        va_list args;
        va_start(args, __fmt);
        T::setCursor(col, row);
        // vfprintf(&lcd_stream, __fmt, args);
        vprintf(__fmt, args);
        // let's clear the rest of row and the before string
        for (uint8_t i = col + 1; i < _col; i++)
        {
            T::write(' ');
        }
        T::setCursor(0, row);
        for (uint8_t i = 0; i < col; i++)
        {
            T::write(' ');
        }
    }

    // clear lcd based on the row number
    void clearLcd(uint8_t row)
    {
        for (uint8_t i = 0; i < _col; i++)
        {
            T::print(" ");
            T::setCursor(i, row);
        }
    }

private:
    uint8_t _col;
    uint8_t _row;
};

void _putchar(char c)
{
    __cb(c);
}

#endif