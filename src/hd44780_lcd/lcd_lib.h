// --------------------------------------------------------------------------
// Sample project hd44780_lcd
//
// Author: Bernhard Bablok
// https://github.com/bablokb/pic-toolchain/src/hd44780_lcd
//
// --------------------------------------------------------------------------

#include <pic12f675.h>

#ifndef __LCD_H
#define __LCD_H

// Define Pins
#define PIN_ENABLE  GP0   // Enable pin for LCD
#define PIN_CLK     GP1   // Serial clock pin
#define PIN_DATA    GP2   // Serial data pin

// Define Pins direction registrers
#define PIN_ENABLE_TRISIO TRISIO0
#define PIN_CLK_TRISIO    TRISIO1
#define PIN_DATA_TRISIO   TRISIO2

// Function Declarations
void lcd_write_cmd(uint8_t cmd);
void lcd_write_data(uint8_t data);
void lcd_init(void);
void lcd_pos(uint8_t row, uint8_t col);
void lcd_print(const unsigned char* string);
#ifdef LCD_PRINT_I
void lcd_print_i(uint8_t value);
#endif
#ifdef LCD_PRINT_X
void lcd_print_x(uint8_t value);
#endif
#define lcd_clear() lcd_write_cmd(0x01)

#endif
