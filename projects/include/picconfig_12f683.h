// --------------------------------------------------------------------------
// pic-toolchain: autoconfigure C-code for PIC12F683
//
// Note: this file is included from picconfig.h, which in turn is automatically
//       generated by the makefile (see ptc_rules.inc)
//
// Author: Bernhard Bablok
//
// https://github.com/bablokb/pic-toolchain
//
// --------------------------------------------------------------------------

#ifndef PICCONFIG_12F683_H
  #define PICCONFIG_12F683_H

  #ifdef __SDCC
    #include <pic14regs.h>
    #include "picconfig_default.h"

    // special initialization (empty)
    #define INIT_SPECIAL

    // run at 4MHz (empty, since it is the default)
    #define CLOCK_4MHZ

    #define CMCON      CMCON0

    #define CONFIG_WORDS \
      __code uint16_t __at (_CONFIG) __configword = \
          MCLR & _PWRTE_ON & _WDT_OFF & _INTRC_OSC_NOCLKOUT & _BOD_OFF;
  #endif
#endif
