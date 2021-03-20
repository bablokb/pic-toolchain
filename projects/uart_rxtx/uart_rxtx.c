// --------------------------------------------------------------------------
// Sample project uart_rxtx
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

CONFIG_WORDS;

////////////////////////////////////////////////////////////////////////
// Intialize registers

static void init(void) {
  // configure registers

  __asm__ ("CLRWDT");            // clear WDT even if WDT is disabled
  ANSELA  = 0;                   // no analog input
  ADCON0  = 0;                   // no A/D converter
  VRCON   = 0;                   // no voltage reference
  CM1CON0 = 0x07;                // disable comparator for GP0-GP2

  softuart_init();               // configure RX,TX pins (GP2,GP0)

  INTEDG = 0;                    // GP2/INT on falling edge
  INTCON = 0;                    // clear interrupt flag bits
  INTE   = 1;                    // GP2/INT external interrupt enable
  GIE    = 1;                    // global interrupt enable
}

////////////////////////////////////////////////////////////////////////
// Interrupt service routine

static void isr(void) __interrupt 0 {
  unsigned char p;
  if (INTE && INTF) {
    p = softuart_receive();
    softuart_print("char: ");
    softuart_transmit(p);
    softuart_transmit('\n');
    INTF = 0;    // Clear GP2/INT interrupt flag
  }
}

// --- main program   --------------------------------------------------------

void main(void) {
  INIT_SPECIAL;
  init();
  while (1) {
    __asm__("SLEEP");
  }
}
