// --------------------------------------------------------------------------
// Sample project sn74hc595_dbg
//
// Author: Bernhard Bablok
// https://github.com/bablokb/pic-toolchain/src/sn74hc595_dbg
//
// --------------------------------------------------------------------------


#ifndef __SHIFT_LIB_H
  #define __SHIFT_LIB_H

  #include <pic12f675.h>
  #include <stdint.h>

  // Define Pins
  #ifndef PIN_CLK
    #define PIN_CLK GP1             // Serial clock pin
    #define PIN_CLK_TRISIO TRISIO1
  #endif
  #ifndef PIN_DATA
    #define PIN_DATA GP2            // Serial data pin
    #define PIN_DATA_TRISIO TRISIO2
  #endif

  // Function Declarations
  void so_init(void);
  #ifdef SO_BYTE
    void so_byte(uint8_t data);
    #define so_clear() so_byte(0x00)
  #endif
  #ifdef SO_ADDR
    void so_addr(uint16_t data);
    #define so_clear() so_addr(0x00)
  #endif
#endif
