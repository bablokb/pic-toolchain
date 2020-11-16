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

CONFIG_WORDS

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

#ifdef __SDCC_PIC12F1612
  OSCCONbits.IRCF = 0b1101;                 // run at 4MHz
#endif

  TRISIO = 0;
  while (1) {
    GP_LED = 1;       // LED on
    maxitime(2);
    GP_LED = 0;       // LED off
    maxitime(2);
  }
}
