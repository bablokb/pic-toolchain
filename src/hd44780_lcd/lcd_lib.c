// --------------------------------------------------------------------------
// Sample project hd44780_lcd
//
// Write to LCD-display with a HD44780-controller (e.g. 2x16). The display
// is used in 4-bit mode. Between the PIC and the display the project
// uses a shift-register (74HCT595).
//
//  Storage register clock SRCLK is connected to shift register clock,
//  so the storage register is one bit behind of the shift register.
//  When writing 8 bits to the shift register, we fill only Q0-Q7 of
//  the storage register:
//    Q6-Q3 will hold b0-b3 (command/data)        -> connect to D4-D7
//    Q2    will hold b4    (data or cmd, 1 or 0) -> connect to RS
//  The rest is not connected.
//
// Author: Bernhard Bablok
// https://github.com/bablokb/pic-toolchain/src/hd44780_lcd
//
// --------------------------------------------------------------------------

#include <pic12f675.h>
#include "delay.h"
#include "lcd_lib.h"

// --------------------------------------------------------------------------
// we only need 5 bits, but always write 8 bits to keep the shift register
// in sync

static void lcd_write_byte(uint8_t byte) {
  uint8_t i = 0;

  // write data to shift-register
  for (i=0;i<8;i++) {
    PIN_DATA = ((byte>>i)&0x1);   // write bit value
    PIN_CLK  = 1;                 // toggle clock pin
    delay_10();
    PIN_CLK  = 0;
    delay_10();
  }

  // enable LCD-read
  PIN_ENABLE = 1;         // low->high triggers read
  delay_150();            // ...
  PIN_ENABLE = 0;         // set back to high
  delay_150();
}

// --------------------------------------------------------------------------
// Command has the RS-bit cleared

void lcd_write_cmd(uint8_t cmd) {
  lcd_write_byte((cmd&0xF0)>>4);  // write upper bits
  lcd_write_byte(cmd&0x0F);       // write lower bits
  delay_ms(40);
}

// --------------------------------------------------------------------------
// Data has the RS-bit set

void lcd_write_data(uint8_t data) {
  lcd_write_byte(((data&0xF0)>>4)|0x10);   // write upper bits
  lcd_write_byte((data&0x0F)|0x10);        // write lower bits
  delay_ms(40);
}

// --------------------------------------------------------------------------

void lcd_init(void) { 
  // Firstly make all pins output
  PIN_ENABLE_TRISIO = 0;
  PIN_DATA_TRISIO   = 0;
  PIN_CLK_TRISIO    = 0;
  PIN_ENABLE        = 0;
  PIN_DATA          = 0;
  PIN_CLK           = 0;

  delay_ms(50);           // initial delay (wait for power-up)
  lcd_write_byte(0x03);   // init-sequence (3x)
  delay_ms(5);
  lcd_write_byte(0x03);
  lcd_write_byte(0x03);
  lcd_write_byte(0x02);   // 4-bit mode
  lcd_write_cmd(0x28);    //function set
  lcd_write_cmd(0x0C);    //display on,cursor off,blink off
  lcd_write_cmd(0x06);    //entry mode, set increment
  lcd_write_cmd(0x01);    //clear display
}

// --------------------------------------------------------------------------
// Clear the Screen and return cursor to zero position

void lcd_clear(void) {  
  lcd_write_cmd(0x01);
}

// --------------------------------------------------------------------------
// set position (row,col) with row=1..2, col=1..16
// address is: 
//   first  line: 0x80 + 0x00 + column-1 
//   second line: 0x80 + 0x40 + column-1
// or short
//   addr = 0x80 + (row-1)*0x40 + col - 1
//        = 0x7F + (row==2 ? 0x40 : 0) + col

void lcd_pos(uint8_t row, uint8_t col) {
  unsigned short addr;
  addr = 0x7F + col;
  if (row == 2) {
    addr += 0x40;
  }
  lcd_write_cmd(addr);
}

// --------------------------------------------------------------------------

void lcd_print(const unsigned char* string) {
  for (const unsigned char *p = string; *p; p++) {
    lcd_write_data(*p);
  }
}
