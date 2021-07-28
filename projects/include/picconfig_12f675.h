// --------------------------------------------------------------------------
// pic-toolchain: autoconfigure C-code for PIC12F675
//
// Note: this file is included from picconfig.h, which in turn is automatically
//       generated by the makefile (see ptc_rules.inc)
//
// Author: Bernhard Bablok
//
// https://github.com/bablokb/pic-toolchain
//
// --------------------------------------------------------------------------

#ifndef PICCONFIG_12F675_H
  #define PICCONFIG_12F675_H

  #include "picconfig_default.h"

  // IOC-macros (12F675 has only global IOC on a single port)
  #define IOC_ENABLE(pin,port,edge) bitset(IOC,pin)
  #define IOC_CLEAR(pin,port)       bitclear(IOC,pin);

  #ifdef __SDCC
    #define __12F675
    #define CONFIG_WORDS \
      __code uint16_t __at (_CONFIG) __configword = \
        MCLR & _PWRTE_ON & _WDT_OFF & _INTRC_OSC_NOCLKOUT & _BODEN_OFF
    // special initialization
    #undef RP0
    #define INIT_SPECIAL \
      __asm \
        bsf  STATUS, RP0 \
        call 0x3ff    ; Wert auslesen \
        movwf OSCCAL  ; Wert setzen \
        bcf  STATUS, RP0 \
      __endasm;

    #ifndef nGPPU
      #define nGPPU NOT_GPPU
    #endif

  #elif defined __XC8
    #pragma config MCLRE = MCLR, PWRTE = ON, WDTE = OFF, FOSC = INTRCIO
    #pragma config BOREN = OFF

    #ifndef NOT_GPPU
      #define NOT_GPPU nGPPU
    #endif
  #endif

  // run at 4MHz (empty, since it is the default)
  #define CLOCK_4MHZ

  #define CM1CON0   CMCON
  #define ANSELA    ANSEL
  #define TRISA     TRISIO
  #define PORTA     GPIO
  #define PORTAbits GPIObits
  #define WPUA      WPU
  #define IOCAN     IOC
  #define IOCIE     GPIE
  #define IOCIF     GPIF
  #define RA        GP
#endif
