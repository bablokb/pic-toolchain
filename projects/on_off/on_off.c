////////////////////////////////////////////////////////////////////////
// Toggle LED connected GP5 with external interrupt at GP2 (on) and
// interrupt-on-change (off) at GP4.
//
// GP2 and GP4 should be tied to GND with a pulldown (4.7k)
//
// compile with:
//   sdcc --use-non-free -mpic14 -p12f675 on_off.c
////////////////////////////////////////////////////////////////////////

#define NO_BIT_DEFINES
#include <pic12f675.h>
#include <stdint.h> 

////////////////////////////////////////////////////////////////////////
// MCLR on, Power on Timer, no WDT, int-Oscillator, 
// no brown out

__code uint16_t __at (_CONFIG) __configword = 
  _MCLRE_ON & _PWRTE_ON & _WDT_OFF & _INTRC_OSC_NOCLKOUT & _BODEN_OFF;


////////////////////////////////////////////////////////////////////////
// Intialize registers

static void init(void) {
  // configure registers
  __asm__ ("CLRWDT");          // clear WDT even if WDT is disabled
  TRISIO             = 0;      // all GPIOs are output except:
  TRISIObits.TRISIO2 = 1;
  TRISIObits.TRISIO4 = 1;
  ANSEL  = 0;                  // no analog input
  CMCON  = 0x07;               // disable comparator for GP0-GP2

  INTCON                 = 0;  // clear interrupt flag bits
  OPTION_REGbits.INTEDG  = 1;  // IOC rising edge
  IOCbits.IOC4           = 0;  // turn off GP4
  INTCONbits.INTE        = 1;  // GP2/INT external interrupt enable
  INTCONbits.INTF        = 0;  // Clear GP2/INT interrupt flag
  GPIO                   = 0;  // initial value of GPIOs
  GPIObits.GP5           = 0;  // turn off LED
  INTCONbits.GIE         = 1;  // global interrupt enable
}

////////////////////////////////////////////////////////////////////////
// globals


////////////////////////////////////////////////////////////////////////
// Interrupt service routine

static void isr(void) __interrupt 0 {
  if (INTCONbits.INTE && INTCONbits.INTF) {
    // switch external interrupt -> interrupt on change
    INTCON          = 0;    // clear interrupts flags

    INTCONbits.INTF = 0;    // Clear GP2/INT interrupt flag
    INTCONbits.INTE = 0  ;  // GP2/INT external interrupt disable

    GPIObits.GP5    = 1;    // turn on LED

    INTCONbits.GPIE = 1;    // turn on interrupt on change
    IOCbits.IOC4    = 1;    // GP4 enable
  } else if (INTCONbits.GPIE && INTCONbits.GPIF) {
    // switch interrupt on change -> external interrupt
    if (GPIObits.GP4) {         // should only happen on GP4 anyhow
      INTCON          = 0;      // clear interrupt flags

      INTCONbits.GPIE = 0;      // turn off interrupt on change
      IOCbits.IOC4    = 0;      // turn off GP4

      GPIObits.GP5    = 0;      // turn off LED

      INTCONbits.INTE = 1;      // GP2/INT external interrupt enable
    }
    INTCONbits.GPIF = 0;    // clear IOC interrupt flag
  }
}

////////////////////////////////////////////////////////////////////////
// main program 
//   - calibrate internal clock
//   - initialize registers
//   - go to sleep

void main(void) {
  // Load calibration
  __asm
    bsf  STATUS, RP0
    call 0x3ff    ; Wert auslesen
    movwf OSCCAL  ; Wert setzen
    bcf  STATUS, RP0
  __endasm;

  init();
  while (1) {
    __asm__("SLEEP");
  }
}
