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

#include <pic14regs.h>
#include <stdint.h>

#include "alias.h"

#ifndef PIN_LED
  #define PIN_LED 5
#endif
#define GP_LED _CONCAT(GP,PIN_LED)

#ifndef PIN_ON
  #define PIN_ON 2
#endif
#define GP_ON _CONCAT(GP,PIN_ON)

#ifndef PIN_OFF
  #define PIN_OFF 4
#endif
#define GP_OFF _CONCAT(GP,PIN_OFF)

CONFIG_WORDS

////////////////////////////////////////////////////////////////////////
// Intialize registers

static void init(void) {
  // configure registers
  __asm__ ("CLRWDT");                  // clear WDT even if WDT is disabled
  TRISIO = (1<<PIN_ON) + (1<<PIN_OFF); // all GPIOs are output except: on/off
  WPU    = TRISIO;                     // pullups for on/off GPs
  NOT_GPPU = 0;                        // enable pullups
  IOC    = TRISIO;                     // IOC for on/off GPs

  ANSEL  = 0;                          // no analog input
  CMCON  = 0x07;                       // disable comparator for GP0-GP2

  INTCON = 0;                          // clear interrupt flag bits
  INTEDG = 1;                          // IOC falling edge
  GP_LED = 0;                          // turn off LED
  GPIE   = 1;                          // port-change enable
  GIE    = 1;                          // global interrupt enable
}

////////////////////////////////////////////////////////////////////////
// Interrupt service routine

static void isr(void) __interrupt 0 {
  if (GPIF) {
    if (!GP_ON) {
      GP_LED = 1;      // turn on LED
    } else if (!GP_OFF) {
      GP_LED = 0;      // turn off LED
    }
    GPIF   = 0;    // clear IOC interrupt flag
  }
}

////////////////////////////////////////////////////////////////////////
// main program 
//   - calibrate internal clock
//   - initialize registers
//   - go to sleep

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

  init();
  while (1) {
    __asm__("SLEEP");
  }
}
