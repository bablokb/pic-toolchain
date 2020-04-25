// --------------------------------------------------------------------------
// Sample project sn74hc595_dbg
//
// Author: Bernhard Bablok
// https://github.com/bablokb/pic-toolchain/src/sn74hc595_dbg
//
// --------------------------------------------------------------------------

#include "shift_lib.h"

// --------------------------------------------------------------------------
// setup hardware for pins
void so_init() {
  PIN_DATA_TRISIO = 0;
  PIN_CLK_TRISIO  = 0;
  PIN_DATA        = 0;
  PIN_CLK         = 0;
}

// --------------------------------------------------------------------------
// Shift out 8+1 bits to shift-register IC

#ifdef SO_BYTE
void so_byte(uint8_t data) {
  uint8_t i = 0;

  // write data to shift-register
  for (i=0;i<8;i++) {
    PIN_DATA = ((data>>i)&0x1);   // write bit value
    PIN_CLK  = 1;                 // toggle clock pin
    PIN_CLK  = 0;
  }
  PIN_CLK  = 1;                   // toggle clock pin
  PIN_CLK  = 0;
}
#endif

// --------------------------------------------------------------------------
// Shift out 16+1 bits to shift-register IC
// This function needs two SN74HC595-ICs chained together.

#ifdef SO_ADDR
void so_addr(uint16_t data) {
  uint8_t i = 0;

  // write data to shift-register
  for (i=0;i<16;i++) {
    PIN_DATA = ((data>>i)&0x1);   // write bit value
    PIN_CLK  = 1;                 // toggle clock pin
    PIN_CLK  = 0;
  }
  PIN_CLK  = 1;                   // toggle clock pin
  PIN_CLK  = 0;
}
#endif
