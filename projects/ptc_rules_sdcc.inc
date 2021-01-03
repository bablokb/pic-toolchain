# --------------------------------------------------------------------------
# Generic sdcc build rules for all projects
#
# Author: Bernhard Bablok
#
# https://github.com/bablokb/pic-toolchain
#
# --------------------------------------------------------------------------

$(info including ptc_rules_sdcc.inc)

# --- configuration   ------------------------------------------------------

MCLR=OFF
OBJS=$(PROJECT).o $(patsubst %.asm,%.o,$(EXTRA_ASM)) \
                  $(patsubst %.c,%.o,$(EXTRA_C))

# --- pattern  -------------------------------------------------------------

.c.o:
	sdcc --use-non-free -m$(ARCH) -p$(MODEL) \
            -I../include -I /usr/local/include \
	     -Wa -w1 -DMCLR=_MCLRE_$(MCLR) $(SDCC_ARGS) $(CPPFLAGS) $(CFLAGS) -c $<

$(patsubst %.asm,%.o,$(EXTRA_ASM)): %.o: %.asm
	gpasm -p$(MODEL) -c $<

$(PROJECT).hex: $(OBJS)
	sdcc --use-non-free -m$(ARCH) -p$(MODEL) \
             -Wl "-S2 -w -r -m" --out-fmt-ihx -o $(PROJECT).hex $(OBJS)

# --- targets   ------------------------------------------------------------

clean:
	@rm -f model.mk picconfig.h picconfig.inc *.o *.cod *.lst *.map *.hex \
              $(PROJECT).asm $(patsubst %.c,%.asm,$(EXTRA_C)) $(EXTRA_CLEAN)


