// --------------------------------------------------------------------------
// pic-toolchain: autoconfigure C-code for PIC12F1612
//
// Note: this file is included from picconfig.h, which in turn is automatically
//       generated by the makefile (see rules.inc)
//
// Author: Bernhard Bablok
//
// https://github.com/bablokb/pic-toolchain
//
// --------------------------------------------------------------------------

#ifndef PICCONFIG_12F1612_H
  #define PICCONFIG_12F1612_H

  #ifdef __SDCC
    #include <pic14regs.h>
    #include "picconfig_default.h"

    // special initialization (empty)
    #define INIT_SPECIAL

    // run at 4MHz
    #define CLOCK_4MHZ \
      OSCCONbits.IRCF = 0b1101;                 // run at 4MHz

    #define CMCON    CM1CON0
    #define ANSEL    ANSELA
    #define TRISIO   TRISA
    #define GPIO     PORTA
    #define WPU      WPUA
    #define IOC      IOCAN
    #define GPIE     IOCIE
    #define GPIF     IOCIF
    #define NOT_GPPU NOT_WPUEN
  
    #define GP0      RA0
    #define GP1      RA1
    #define GP2      RA2
    #define GP3      RA3
    #define GP4      RA4
    #define GP5      RA5
  
    #define CONFIG_WORDS \
      __code uint16_t __at (_CONFIG1) __configword1 = \
        MCLR & _PWRTE_ON & _CLKOUTEN_OFF & _BOREN_OFF & _FOSC_INTOSC; \
      __code uint16_t __at (_CONFIG2) __configword2 = \
        _LVP_OFF & _DEBUG_OFF & _WRT_OFF; \
      __code uint16_t __at (_CONFIG3) __configword3 = _WDTE_OFF;

  #endif
#endif
