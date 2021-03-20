// --------------------------------------------------------------------------
// Sample project blink_led_tmr0
//
// Toggle LED on GPx every 0.5s using the internal 8Bit timer
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

CONFIG_WORDS;

////////////////////////////////////////////////////////////////////////
/*
  Source of this information:
  http://freesourcecode.net/cprojects/97307/Pic-microcontroller-tmr0-interrupt-with-sdcc-in-c

  The TMR0 interupt will occur when TMR0 overflows from 0xFF to
  0x00.  Without a prescaler, TMR0 will increment every clock
  cycle resulting in an interrupt every 256 cycles.  However, 
  using a prescaler, we can force that interrupt to occure at
  less frequent intervals.
    
  Each clock cycle is 1/4 the external clock.  Using that, and
  knowing the prescaler, we can determine the time interval for
  our interrupt.  
    
  PS2 PS1 PS0 Ratio   Cycles  4MHz        10MHz
  0   0   0   1:2     512      512.0 uS    204.8 uS    
  0   0   1   1:4     1024     1.024 mS    409.6 uS
  0   1   0   1:8     2048     2.048 mS    819.2 uS
  0   1   1   1:16    4096     4.096 mS    1.638 mS
  1   0   0   1:32    8192     8.192 mS    3.276 mS
  1   0   1   1:64    16384   16.384 mS    6.553 mS
  1   1   0   1:128   32768   32.768 mS   13.107 mS
  1   1   1   1:256   65536   65.536 mS   26.214 mS 
*/

////////////////////////////////////////////////////////////////////////
// globals

static volatile uint8_t counter = 0;
static volatile char    on      = 0;

////////////////////////////////////////////////////////////////////////
// Intialize registers

static void init(void) {
  // configure registers

  __asm__ ("CLRWDT");  // clear WDT even if WDT is disabled
  ANSELA   = 0;        // no analog input
  TRISA    = 0;        // all GPIOs are output
  CM1CON0  = 0x07;     // disable comparator for GP0-GP2
  NOT_GPPU = 1;        // no pullups
  T0CS     = 0;        // clear to enable timer mode
  PSA      = 0;        // clear to assign prescaler to TMRO
  PS2      = 0;        // 010 @ 4Mhz = 2.048 mS
  PS1      = 1;
  PS0      = 0;

  GP_LED   = 0;        // initial value of GP_LED

  INTCON   = 0;        // clear interrupt flag bits
  TMR0     = 0;        // clear the value in TMR0
  T0IE     = 1;        // TMR0 overflow interrupt enable
  GIE      = 1;        // global interrupt enable
}

////////////////////////////////////////////////////////////////////////
// Interrupt service routine

static void isr(void) __interrupt 0 {
  if (T0IE && T0IF) {
    T0IF = 0;           // Clear timer interrupt flag
    if (!++counter) {   // flip value of on every 256 interrupts
      on = 1-on;
      GP_LED = on;
    }
  }
}

////////////////////////////////////////////////////////////////////////
// main program 
//   - calibrate internal clock
//   - initialize registers
//   - do nothing

void main(void) {
  INIT_SPECIAL;
  CLOCK_4MHZ;
  init();
  while (1) {
    // don't sleep here, because sleep deactivates timer-interrupt
  }
}
