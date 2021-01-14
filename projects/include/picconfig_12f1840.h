// --------------------------------------------------------------------------
// pic-toolchain: autoconfigure C-code for PIC12F1840
//
// Note: this file is included from picconfig.h, which in turn is automatically
//       generated by the makefile (see ptc_rules.inc)
//
// Author: Bernhard Bablok
//
// https://github.com/bablokb/pic-toolchain
//
// --------------------------------------------------------------------------

#ifndef PICCONFIG_12F1840_H
  #define PICCONFIG_12F1840_H

  #include "picconfig_default.h"

  #ifdef __SDCC
    #define __12F1840
    // special initialization (empty)
    #define INIT_SPECIAL

    #define CONFIG_WORDS \
      __code uint16_t __at (_CONFIG1) __configword1 = \
        MCLR & _PWRTE_ON & _WDTE_OFF & _CLKOUTEN_OFF & _BOREN_OFF & _FOSC_INTOSC; \
      __code uint16_t __at (_CONFIG2) __configword2 = _LVP_OFF & _DEBUG_OFF;

    #ifndef NOT_GPPU
      #define NOT_GPPU NOT_WPUEN
    #endif
    #ifndef nWPUEN
      #define nWPUEN   NOT_WPUEN
    #endif

  #elif defined __XC8
    #pragma config MCLRE = MCLR, PWRTE = ON, WDTE = OFF, FOSC = INTOSC
    #pragma config CLKOUTEN = OFF, BOREN = OFF, LVP = OFF

    #ifndef NOT_GPPU
      #define NOT_GPPU nWPUEN
    #endif
    #ifndef NOT_WPUEN
      #define NOT_WPUEN nWPUEN
    #endif

  #endif

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
  
  #define GP0      RA0
  #define GP1      RA1
  #define GP2      RA2
  #define GP3      RA3
  #define GP4      RA4
  #define GP5      RA5
#endif
