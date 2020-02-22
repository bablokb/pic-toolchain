////////////////////////////////////////////////////////////////////////
// Use the PIC to turn a Raspberry Pi on or off via a mosfet.
// 
// This project uses the following pins:
//  - PIN_POWER  (GP5): attach to gate of mosfet to turn power on or off
//  - PIN_PI_OUT (GP4): request shutdown from Pi
//  - PIN_SIG1   (GP1): external on/off signal (e.g. from button)
//  - PIN_SIG2   (GP2): external on/off signal (e.g. from button)
//  - PIN_PI_IN  (GP0): Pi confirms shutdown (PIC can turn off power)
//
// build with:
//   make build
// flash with
//   make flash
//
// Author: Bernhard Bablok
// https://github.com/bablokb/pic-toolchain
//
////////////////////////////////////////////////////////////////////////

#define NO_BIT_DEFINES
#include <pic12f675.h>
#include <stdint.h> 
#include "quarz4MHz.h"

#define PIN_POWER  GPIObits.GP5
#define PIN_PI_OUT GPIObits.GP4
#define PIN_SIG2   GPIObits.GP2
#define PIN_SIG1   GPIObits.GP1
#define PIN_PI_IN  GPIObits.GP0

#define POWER_ON  1
#define POWER_OFF 0

////////////////////////////////////////////////////////////////////////
// MCLR on, Power on Timer, no WDT, int-Oscillator, 
// no brown out

__code uint16_t __at (_CONFIG) __configword = 
  _MCLRE_ON & _PWRTE_ON & _WDT_OFF & _INTRC_OSC_NOCLKOUT & _BODEN_OFF;

////////////////////////////////////////////////////////////////////////
// Intialize registers

static void init(void) {
  // configure registers
  __asm__ ("CLRWDT");             // clear WDT even if WDT is disabled
  TRISIO    = 0x07;               // GP5, GP4 are output
  ANSEL     = 0;                  // no analog input
  CMCON     = 0x07;               // disable comparator for GP0-GP2
  WPU       = 0x07;               // weak pullups enable on GP0-2

  INTCON                  = 0;    // clear interrupt flag bits
  OPTION_REGbits.INTEDG   = 1;    // IOC rising edge
  OPTION_REGbits.NOT_GPPU = 1;    // enable pullups
  IOC                     = 0x07; // IOC on GP0-2
  GPIO                    = 0;    // initial value of GPIOs
  INTCONbits.GIE          = 1;    // global interrupt enable
}

////////////////////////////////////////////////////////////////////////
// globals


////////////////////////////////////////////////////////////////////////
// Interrupt service routine

static void isr(void) __interrupt 0 {
  if (INTCONbits.GPIF) {
    INTCON = 0;             // clear interrupt flags
    INTCONbits.GPIF = 0;    // clear IOC interrupt flag
    if (PIN_SIG1|PIN_SIG2) {
      if (PIN_POWER) {
        // power is on, signal shutdown to Pi
        PIN_PI_OUT = 1;
      } else {
        // power is off, turn power on
        PIN_POWER  = 1;
      }
    } else if (PIN_PI_IN) {
      PIN_POWER  = 0;  // Pi signals shutdown complete, so turn power off
      PIN_PI_OUT = 0;  // and restore initial state
    }
  }
  maxitime(1);  // wait 250ms (debounce)
}

////////////////////////////////////////////////////////////////////////
// main program (boring)
//   - calibrate internal clock
//   - initialize registers
//   - go to sleep

void main(void) {
  // Load calibration
  __asm
    bsf  STATUS, RP0
    call 0x3ff    ; read value
    movwf OSCCAL  ; set value
    bcf  STATUS, RP0
  __endasm;

  init();
  while (1) {
    __asm__("SLEEP");
  }
}
