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

#include "picconfig.h"
#include <stdint.h> 

#include "softuart.h"
#include "quarz4MHz.h"

CONFIG_WORDS

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

  INTCON = 0;                    // clear interrupt flag bits
}

// --- main program   --------------------------------------------------------

void main(void) {
  INIT_SPECIAL;
  CLOCK_4MHZ;
  init();
  while (1) {
    softuart_print("Hallo\n");  // send message
    maxitime(4);                // wait one second
  }
}
