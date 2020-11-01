# --------------------------------------------------------------------------
# Sample project blink_led_quarz4MHz
#
# Call external ASM-routine
# See https://sourceforge.net/p/sdcc/mailman/message/35239527/
#
# Author: Bernhard Bablok, Lothar Hiller (quartz4MHz.asm)
#
# https://github.com/bablokb/pic-toolchain
#
# --------------------------------------------------------------------------

PROJECT=blink_led_quarz4MHz
EXTRA_ASM=quarz4MHz.asm
ARCH=pic14

PIN_LED=5
SDCC_ARGS=-DPIN_LED=$(PIN_LED)

include ../rules.inc

# --------------------------------------------------------------------------
