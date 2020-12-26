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
#endif
