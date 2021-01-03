// --------------------------------------------------------------------------
// pic-toolchain: default macros
//
// Note: this file is included from the files picconfig_*.h
//
// Author: Bernhard Bablok
//
// https://github.com/bablokb/pic-toolchain
//
// --------------------------------------------------------------------------

#ifndef PICCONFIG_DEF_H
  #define PICCONFIG_DEF_H

  #define bitset(var, bitno)   ((var) |= 1UL << (bitno))
  #define bitread(var, bitno)  ((var) & (1UL << (bitno)))
  #define bitclear(var, bitno) ((var) &= ~(1UL << (bitno)))

  #ifdef __XC8
    #ifndef _CONCAT
      #undef  _CONCAT2
      #define _CONCAT(a,b)  _CONCAT2(a,b)
      #define _CONCAT2(a,b) a ## b
    #endif
    #ifndef __asm__
      #define __asm__(code) asm(code)
    #endif
  #endif
#endif
