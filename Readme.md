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

The directory `projects` contains a number of sample projects.
You must copy (install) the rule-files `projects/ptc_rules*.inc`
(generic makefile-rules) to a system-include directory automatically
searched by `make`, e.g. `/usr/local/include` or add the `-I dir` option
to the invocation of `make`.

The directory `projects/include` contains `.h`-files (c-includes)
used by all projects. You should also copy (install) these files to
`/usr/local/include` if you want to use these files in other projects.

The projects demonstrate various aspects, e.g. how to embbed assembler code
into C-code, or link with preexisting assembler-code.
