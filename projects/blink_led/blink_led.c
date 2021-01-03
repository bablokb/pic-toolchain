// --------------------------------------------------------------------------
// Sample project blink_led
//
// Code copied and modified from https://github.com/diegoherranz/sdcc-examples
//
// --------------------------------------------------------------------------

#include "picconfig.h"
#include <stdint.h>

#ifndef PIN_LED
  #define PIN_LED 5
#endif
#define GP_LED _CONCAT(GP,PIN_LED)

CONFIG_WORDS

// --- uncalibrated delay   --------------------------------------------------

void delay(uint16_t iterations) {
  uint16_t i;
  for (i = 0; i < iterations; i++) {
    __asm__("nop");          // add a no-op to prevent removal by optimization
  }
}

// --- main program   --------------------------------------------------------

void main(void) {
  INIT_SPECIAL;
  CLOCK_4MHZ;
  TRISIO = 0;
  while (1) {
    GP_LED = 1;       // LED on
    delay(30000);     // ~500ms @ 4MHz
    GP_LED = 0;       // LED off
    delay(30000);     // ~500ms @ 4MHz
  }
}
