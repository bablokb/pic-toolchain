// --------------------------------------------------------------------------
// Sample project blink_led
//
// Code copied and modified from https://github.com/diegoherranz/sdcc-examples
//
// --------------------------------------------------------------------------

#include <pic14regs.h>
#include <stdint.h> 

#include "alias.h"

CONFIG_WORDS

// --- uncalibrated delay   --------------------------------------------------

void delay(uint16_t iterations) {
  uint16_t i;
  for (i = 0; i < iterations; i++) {
    __asm nop __endasm;       // add a no-op to prevent removal by optimization
  }
}

// --- main program   --------------------------------------------------------

void main(void) {


#ifdef __SDCC_PIC12F675
  // Load calibration
  __asm
    bsf  STATUS, RP0
    call 0x3ff    ; Wert auslesen
    movwf OSCCAL  ; Wert setzen
    bcf  STATUS, RP0
  __endasm;
#endif

#ifdef __SDCC_PIC12F1840
  OSCCONbits.IRCF = 0b1101;                 // run at 4MHz
#endif

  TRISIO = 0;
  while (1) {
    GP5 = 1; // LED an
    delay(30000);     // ~500ms @ 4MHz
    GP5 = 0; // LED aus
    delay(30000);     // ~500ms @ 4MHz
  }
}
