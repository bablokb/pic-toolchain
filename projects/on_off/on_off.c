// --------------------------------------------------------------------------
// Sample project on_off
//
// Toggle LED connected PIN_LED with PIN_ON (on) and PIN_OFF (off).
//
// PIN_ON and PIN_OFF use internal pullups.
//
// Author: Bernhard Bablok
//
// https://github.com/bablokb/pic-toolchain
//
// --------------------------------------------------------------------------

#include "picconfig.h"
#include <stdint.h>

#ifndef PIN_LED
  #define PIN_LED 5
#endif
#define GP_LED _CONCAT(RA,PIN_LED)

#ifndef PIN_ON
  #define PIN_ON 0
#endif
#define GP_ON _CONCAT(RA,PIN_ON)

#ifndef PIN_OFF
  #define PIN_OFF 4
#endif
#define GP_OFF _CONCAT(RA,PIN_OFF)

CONFIG_WORDS;

////////////////////////////////////////////////////////////////////////
// Intialize registers

static void init(void) {
  // configure registers
  __asm__ ("CLRWDT");                  // clear WDT even if WDT is disabled
  ANSELA  = 0;                         // no analog input
  CM1CON0 = 0x07;                      // disable comparator for GP0-GP2

  TRISA = 0;
  bitset(TRISA,PIN_ON);                // all GPIOs are output except: on/off
  bitset(TRISA,PIN_OFF);
  bitset(WPUA,PIN_ON);                 // pullups for on/off GPs
  bitset(WPUA,PIN_OFF);
  NOT_GPPU = 0;                        // enable pullups

  IOC_ENABLE(PIN_ON,A,IOC_NEG_EDGE);
  IOC_ENABLE(PIN_OFF,A,IOC_NEG_EDGE);

  INTCON = 0;                          // clear interrupt flag bits
  GP_LED = 0;                          // turn off LED
  IOCIE  = 1;                          // port-change enable
  GIE    = 1;                          // global interrupt enable
}

////////////////////////////////////////////////////////////////////////
// Interrupt service routine

static void isr(void) __interrupt 0 {
  if (IOCIF) {
    if (!GP_ON) {
      GP_LED = 1;      // turn on LED
      IOC_CLEAR(PIN_ON,A);
    } else if (!GP_OFF) {
      GP_LED = 0;      // turn off LED
      IOC_CLEAR(PIN_OFF,A);
    }
  }
}

////////////////////////////////////////////////////////////////////////
// main program 
//   - calibrate internal clock
//   - initialize registers
//   - go to sleep

void main(void) {
  INIT_SPECIAL;
  init();
  while (1) {
    __asm__("SLEEP");
  }
}
