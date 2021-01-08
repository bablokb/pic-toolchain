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
OBJ_C=$(PROJECT).obj $(patsubst %.c,%.obj,$(EXTRA_C))
OBJ_A=$(patsubst %.asm,%.obj,$(EXTRA_ASM))

# --- pattern  -------------------------------------------------------------

$(OBJ_C): %.obj: %.c
	xc8 --chip=$(MODEL) \
            -I../include -I/usr/local/include \
	        -DMCLR=$(MCLR) $(SDCC_ARGS) $(CPPFLAGS) $(CFLAGS) -c $<

$(OBJ_A): %.obj: %.asm
	xc8 --chip=$(MODEL) \
            -I../include -I/usr/local/include \
                -p -c $<

$(PROJECT).hex: $(OBJ_C) $(OBJ_A)
	xc8 --chip=$(MODEL) \
              -o$(PROJECT).hex $(OBJ_C) $(OBJ_A)

# --- targets   ------------------------------------------------------------

picconfig.inc:
	@echo "creating picconfig.inc"
	@echo '#include "xc.inc"' > picconfig.inc
	@echo '#define Z STATUS_Z_POSITION' >> picconfig.inc

clean:
	@rm -f tc.mk model.mk picconfig.h picconfig.inc \
            *.obj *.as *.pre *.d *.p1 *.cmf *.lst *.map *.hex *.elf *.hxl \
            *.sdb *.sym startup.* __eprom.* \
              $(PROJECT).asm $(patsubst %.c,%.asm,$(EXTRA_C)) $(EXTRA_CLEAN)
