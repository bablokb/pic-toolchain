// --------------------------------------------------------------------------
// Sample project blink_led_quarz4Mhz
//
// This project links to preexisting asm-routines.
// See https://sourceforge.net/p/sdcc/mailman/message/35239527/
//
// Author: Bernhard Bablok, Lothar Hiller (quartz4MHz.asm)
//
// https://github.com/bablokb/pic-toolchain
//
// --------------------------------------------------------------------------

#include "picconfig.h"
#include <stdint.h> 

extern void maxitime(uint8_t count);   // 250 mS

#ifndef PIN_LED
  #define PIN_LED 5
#endif
#define GP_LED _CONCAT(GP,PIN_LED)

CONFIG_WORDS;

// --- main program   --------------------------------------------------------

void main(void) {
  INIT_SPECIAL;
  CLOCK_4MHZ;
  TRISIO = 0;
  while (1) {
    GP_LED = 1;       // LED on
    maxitime(2);
    GP_LED = 0;       // LED off
    maxitime(2);
  }
}
