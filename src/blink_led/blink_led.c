// --------------------------------------------------------------------------
// Sample project blink_led
//
// Code copied and modified from https://github.com/diegoherranz/sdcc-examples
//
// --------------------------------------------------------------------------

#define NO_BIT_DEFINES
#include <pic12f675.h>
#include <stdint.h> 

// compile with:
// sdcc --use-non-free -mpic14 -p12f675 blink_led.c

// MCLR on, Power on Timer, no WDT, int-oscillator, no brown out

__code uint16_t __at (_CONFIG) __configword = 
  _MCLRE_ON & _PWRTE_ON & _WDT_OFF & _INTRC_OSC_NOCLKOUT & _BODEN_OFF;

// --- uncalibrated delay   --------------------------------------------------

void delay(uint16_t iterations) {
  uint16_t i;
  for (i = 0; i < iterations; i++) {
    __asm nop __endasm;       // add a no-op to prevent removal by optimization
  }
}

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
    delay(30000);     // ~500ms @ 4MHz
    GPIObits.GP5 = 0; // LED aus
    delay(30000);     // ~500ms @ 4MHz
  }
}
