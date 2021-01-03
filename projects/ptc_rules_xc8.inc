# --------------------------------------------------------------------------
# Generic xc8 build rules for all projects
#
# Author: Bernhard Bablok
#
# https://github.com/bablokb/pic-toolchain
#
# --------------------------------------------------------------------------

$(info including ptc_rules_xc8.inc)

# --- configuration   ------------------------------------------------------

MCLR=OFF
OBJS=$(PROJECT).obj $(patsubst %.asm,%.obj,$(EXTRA_ASM)) \
                  $(patsubst %.c,%.obj,$(EXTRA_C))

# --- pattern  -------------------------------------------------------------

$(OBJS): %.obj: %.c
	xc8 --chip=$(MODEL) \
            -I../include -I/usr/local/include \
	        -DMCLR=$(MCLR) $(SDCC_ARGS) $(CPPFLAGS) $(CFLAGS) -c $<

$(patsubst %.asm,%.obj,$(EXTRA_ASM)): %.obj: %.asm
	xc8 --chip=$(MODEL) -c $<

$(PROJECT).hex: $(OBJS)
	xc8 --chip=$(MODEL) \
              -o$(PROJECT).hex $(OBJS)

# --- targets   ------------------------------------------------------------

clean:
	@rm -f model.mk picconfig.h picconfig.inc *.obj *.cod *.lst *.map *.hex \
              $(PROJECT).asm $(patsubst %.c,%.asm,$(EXTRA_C)) $(EXTRA_CLEAN)
