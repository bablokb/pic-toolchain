////////////////////////////////////////////////////////////////////////
// Use the PIC to turn a Raspberry Pi on or off via a mosfet.
// 
// This project uses the following pins:
//  - PIN_FROM_PI (GP0): Pi confirms shutdown (PIC can turn off power)
//  - PIN_TO_PI   (GP1): request shutdown from Pi
//  - PIN_SIG2    (GP2): external on/off signal (e.g. from button)
//  - PIN_SIG1    (GP4): external on/off signal (e.g. from button)
//  - PIN_POWER   (GP5): attach to gate of mosfet to turn power on or off
//
// Author: Bernhard Bablok
// https://github.com/bablokb/pic-toolchain
//
////////////////////////////////////////////////////////////////////////

#include "picconfig.h"
#include <stdint.h>

#include "quarz4MHz.h"

#ifndef PIN_FROM_PI
  #define PIN_FROM_PI 0
#endif
#define GP_FROM_PI _CONCAT(RA,PIN_FROM_PI)

#ifndef PIN_TO_PI
  #define PIN_TO_PI 1
#endif
#define GP_TO_PI _CONCAT(RA,PIN_TO_PI)

#ifndef PIN_SIG2
  #define PIN_SIG2 2
#endif
#define GP_SIG2 _CONCAT(RA,PIN_SIG2)

#ifndef PIN_SIG1
  #define PIN_SIG1 4
#endif
#define GP_SIG1 _CONCAT(RA,PIN_SIG1)

#ifndef PIN_POWER
  #define PIN_POWER 5
#endif
#define GP_POWER _CONCAT(RA,PIN_POWER)

#define BOOT_WAIT   20               // 5s = 20*250ms
#define POWER_ON    0
#define POWER_OFF   1

CONFIG_WORDS;

////////////////////////////////////////////////////////////////////////
// Intialize registers

static void init(void) {
  // configure registers
  __asm__ ("CLRWDT");                  // clear WDT even if WDT is disabled
  TRISA    = (1<<PIN_FROM_PI) +
    (1<<PIN_SIG1) + (1<<PIN_SIG2);     // GP4, GP2, GP0 are input
  WPU      = 
    (1<<PIN_SIG1) + (1<<PIN_SIG2);     // pullups for the GP4/GP2 pins
  NOT_GPPU = 0;                        // enable pullups
  IOC      = TRISA;                    // IOC for all input pins

  ANSELA   = 0;                        // no analog input
  CMCON    = 0x07;                     // disable comparator for GP0-GP2

  PORTA    = 0;                        // initial value of GPIOs
  GP_POWER = POWER_OFF;                //    except GP_POWER
  GP_TO_PI = 1;                        //    except GP_TO_PI

  INTCON   = 0;                        // clear interrupt flag bits
  GPIE     = 1;                        // enable IOC
  GIE      = 1;                        // global interrupt enable
}

////////////////////////////////////////////////////////////////////////
// Interrupt service routine

static void isr(void) __interrupt 0 {
  if (GPIF) {                            // interrupt-on-change
    if (!GP_SIG1||!GP_SIG2) {            // SIG1 or SIG2 is low
      if (GP_POWER == POWER_OFF) {       // power is off:
        GP_POWER = POWER_ON;             //   turn power on and
        maxitime(BOOT_WAIT);             //   wait until Pi is up
      } else {                           // power is on:
        GP_TO_PI = 0;                    //   signal shutdown to Pi
      }
    } else if (GP_FROM_PI) {             // High: shutdown complete
      GP_POWER = POWER_OFF;              // turn power off
      GP_TO_PI = 1;                      // and restore initial state
    }
    GPIF = 0;                            // clear IOC interrupt flag
  }
  maxitime(1);  // wait 250ms (debounce)
}

////////////////////////////////////////////////////////////////////////
// main program (boring)
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
