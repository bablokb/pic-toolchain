// --------------------------------------------------------------------------
// pic-toolchain: autoconfigure C-code for PIC12F675
//
// Note: this file is included from alias.h, which in turn is automatically
//       generated by the makefile (see rules.inc)
//
// Author: Bernhard Bablok
//
// https://github.com/bablokb/pic-toolchain
//
// --------------------------------------------------------------------------

#ifndef ALIAS_12F675_H
  #define ALIAS_12F675_H

  #undef RP0

  #define CONFIG_WORDS \
    __code uint16_t __at (_CONFIG) __configword = \
      MCLR & _PWRTE_ON & _WDT_OFF & _INTRC_OSC_NOCLKOUT & _BODEN_OFF;
#endif
