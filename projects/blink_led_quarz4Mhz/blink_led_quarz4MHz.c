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

#define NO_BIT_DEFINES
#include <pic12f675.h>
#include <stdint.h> 

// build with:
// make build

// MCLR on, Power on Timer, no WDT, int-oscillator, 
// no brown out

extern void minitime(uint8_t count);   // 0.1 mS
extern void miditime(uint8_t count);   // 1.0 mS
extern void maxitime(uint8_t count);   // 250 mS

__code uint16_t __at (_CONFIG) __configword = 
  _MCLRE_ON & _PWRTE_ON & _WDT_OFF & _INTRC_OSC_NOCLKOUT & _BODEN_OFF;

// --- main program   --------------------------------------------------------

void main(void) {
  // Load calibration
  __asm
    bsf  STATUS, RP0
    call 0x3ff    ; Wert auslesen
    movwf OSCCAL  ; Wert setzen
    bcf  STATUS, RP0
  __endasm;

  TRISIO = 0;
  while (1) {
    GPIObits.GP5 = 1; // LED an
    maxitime(2);
    GPIObits.GP5 = 0; // LED aus
    maxitime(2);
  }
}
