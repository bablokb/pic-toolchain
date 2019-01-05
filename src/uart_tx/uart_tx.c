// --------------------------------------------------------------------------
// Sample project uart_tx
//
// Software uart
// Source of uart-code:
// https://pic-microcontroller.com/pic12f675-software-uart-bit-banging-code-and-proteus-simulation/
//
// Author: Bernhard Bablok
//
// https://github.com/bablokb/pic-toolchain
//
// --------------------------------------------------------------------------

#define NO_BIT_DEFINES
#include <pic12f675.h>
#include <stdint.h> 

#include "softuart.h"
#include "quarz4MHz.h"

// build with:
// make build

// MCLR on, Power on Timer, no WDT, int-oscillator, 
// no brown out

__code uint16_t __at (_CONFIG) __configword = 
  _MCLRE_ON & _PWRTE_ON & _WDT_OFF & _INTRC_OSC_NOCLKOUT & _BODEN_OFF;

////////////////////////////////////////////////////////////////////////
// Intialize registers

static void init(void) {
  // configure registers

  __asm__ ("CLRWDT");            // clear WDT even if WDT is disabled
  ANSEL  = 0;                    // no analog input
  ADCON0 = 0;                    // no A/D converter
  VRCON  = 0;                    // no voltage reference
  CMCON  = 0x07;                 // disable comparator for GP0-GP2

  softuart_init();               // configure RX,TX pins (GP2,GP0)

  INTCON                 = 0;    // clear interrupt flag bits
}

// --- main program   --------------------------------------------------------

void main(void) {
  const unsigned char msg[] = "Hallo\n";
  // Load calibration
  __asm
    bsf  STATUS, RP0
    call 0x3ff    ; read value
    movwf OSCCAL  ; set  value
    bcf  STATUS, RP0
  __endasm;

  init();
  while (1) {
    for (unsigned char *p = msg; *p; p++) {
      softuart_transmit(*p);
    }
    maxitime(4);
  }
}
