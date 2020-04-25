// --------------------------------------------------------------------------
// Sample project sn74hc595_dbg
//
// A simple SN74HC595-based "debugger" which only uses two pins to shift-out
// 8 or 16 bits. Connected to the SN74HC595 are LEDs to display the data.
//
// The sample program uses a button on GP5. After intitialization,
// the leds should display '0000 1111'. The button toggles a counter showing
// all values from 1 to 255. When pressed again or when the counter wraps
// around to zero, the counting stops again.
//
// Author: Bernhard Bablok
// https://github.com/bablokb/pic-toolchain/src/sn74hc595_dbg
//
// --------------------------------------------------------------------------

#define NO_BIT_DEFINES
#include <pic12f675.h>
#include <stdint.h>

#include "shift_lib.h"
#include "delay.h"

// build with:
// make build

// MCLR on, Power on Timer, no WDT, int-oscillator, 
// no brown out

__code uint16_t __at (_CONFIG) __configword = 
  _MCLRE_ON & _PWRTE_ON & _WDT_OFF & _INTRC_OSC_NOCLKOUT & _BODEN_OFF;


static uint8_t counter  = 0;

////////////////////////////////////////////////////////////////////////
// Intialize registers

static void init(void) {
  // configure registers

  __asm__ ("CLRWDT");            // clear WDT even if WDT is disabled
  ANSEL  = 0;                    // no analog input
  CMCON  = 0x07;                 // disable comparator for GP0-GP2
  TRISIO = 0b100000;             // GP5 is input
  WPU    = 0b100000;             // weak pullups enable on GP5
  IOC    = 0b100000;             // IOC on GP5

  GPIObits.GP5            = 0;   // initial value of GP5

  OPTION_REGbits.NOT_GPPU = 0;   // enable pullups
  GPIO                    = 0;
  INTCON                  = 0;   // clear interrupt flag bits
  INTCONbits.GPIE         = 1;   // enable IOC
  INTCONbits.GIE          = 1;   // global interrupt enable
}

////////////////////////////////////////////////////////////////////////
// Interrupt service routine

static void isr(void) __interrupt 0 {
  if (INTCONbits.GPIF) {                  // interrupt-on-change
    // just wait a bit to debounce
    delay_ms(250);
    if (counter) {   // active: stop counting
      counter = 0;
    } else {         // waiting: start counting
      counter = 1;
    }
    INTCONbits.GPIF = 0;                  // clear IOC interrupt flag
  }
}

// --- main program   --------------------------------------------------------

void main(void) {
  // Load calibration
  __asm
    bsf  STATUS, RP0
    call 0x3ff    ; read value
    movwf OSCCAL  ; set  value
    bcf  STATUS, RP0
  __endasm;

  init();
  so_init();
  so_byte(0x0F);                            // 0000 1111
  while (1) {
    // if counter is zero, wait for button-press and ...
    while (!counter) {
      __asm__("SLEEP");
    }
    // ... display and increment and wait some time
    so_byte(counter++);
    delay_ms(250);
  }
}
