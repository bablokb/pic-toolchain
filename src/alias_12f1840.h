// --------------------------------------------------------------------------
// pic-toolchain: autoconfigure C-code for PIC12F1840
//
// Note: this file is included from alias.h, which in turn is automatically
//       generated by the makefile (see rules.inc)
//
// Author: Bernhard Bablok
//
// https://github.com/bablokb/pic-toolchain
//
// --------------------------------------------------------------------------

#ifndef ALIAS_12F1840_H
  #define ALIAS_12F1840_H

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
    _MCLRE_OFF & _PWRTE_ON & _WDTE_OFF & _CLKOUTEN_OFF & _BOREN_OFF & _FOSC_INTOSC; \
  __code uint16_t __at (_CONFIG2) __configword2 = _LVP_OFF & _DEBUG_OFF;

#endif
