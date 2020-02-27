PIC Toolchain
=============

This is a collection of notes, sources and tools for a complete
PIC toolchain for the Raspbian operating-system.


Toolset
=======

To compile, link and flash PIC code, you need on software-side

  - a compiler (SDCC)
  - an assembler and linker (gputils)
  - a flasher

The first two programs are available for Raspbian, but it is recommended
to build both programs from source. For flashing, you need the 
program `pk2cmd`. You can find a precompiled version for armv6l in
`files/usr/local/bin`.


Example Programs
================

The directory `src` contains a number of sample projects for the PIC12F675.
Be sure to copy also the file `src/rules.inc`, which contains generic
make-rules used by all projects.

The projects demonstrate various aspects, e.g. how to embbed assembler code
into C-code, or link with preexisting assembler-code.
