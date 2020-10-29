# --------------------------------------------------------------------------
# Generic build rules for all projects
#
# Author: Bernhard Bablok
#
# https://github.com/bablokb/pic-toolchain
#
# --------------------------------------------------------------------------

default:
	@echo "make build:  create $(PROJECT).hex"
	@echo "make flash:  build and flash $(PROJECT).hex to PIC using PICKitPlus"
	@echo "make flash2: build and flash $(PROJECT).hex to PIC using pk2cmd"
	@echo "make clean:  remove intermediate files"

# --- configuration   ------------------------------------------------------

HEXF=inhx8m
OBJS=$(PROJECT).o $(patsubst %.asm,%.o,$(EXTRA_ASM)) \
                  $(patsubst %.c,%.o,$(EXTRA_C))

# --- pattern  -------------------------------------------------------------

.c.o:
	sdcc --use-non-free -m$(ARCH) -p$(MODEL) -Wa -w1 -c $(SDCC_ARGS) $<

$(patsubst %.asm,%.o,$(EXTRA_ASM)): %.o: %.asm
	gpasm -a $(HEXF) -p$(MODEL) -c $<

$(PROJECT).hex: $(OBJS)
	sdcc --use-non-free -m$(ARCH) -p$(MODEL) \
             -Wl "-S2 -w -r -m" --out-fmt-ihx -o $(PROJECT).hex $(OBJS)

# --- targets   ------------------------------------------------------------

.PH0NY: mcheck flash flash2 clean

include model.mk

model.mk:
	@echo -en "creating model.mk ... "
	@if [ -z "$(MODEL)" ]; then pk2cmd -p | \
	  sed -ne '/Found part/s/.*Found part PIC\([^.]*\)\./MODEL = \L\1/p' > \
	    model.mk; \
	  if [ ! -s model.mk ]; then \
	    echo "can't set MODEL, aborting"; rm -f model.mk; exit 3; \
	  else \
	    cat model.mk; \
	  fi; \
	else \
	  tee model.mk <<< "MODEL = $(MODEL)"; \
	fi

mcheck:
	@if [ -z "$(MODEL)" ]; then \
	  echo "MODEL not specified, aborting"; exit 3; \
	fi

alias.h:
	@echo "creating alias.h and alias_$(MODEL).h"
	@echo '#include "alias_$(MODEL).h"' > alias.h

alias_$(MODEL).h:
	@cp -a "../alias_$(MODEL).h" .

build: mcheck alias.h alias_$(MODEL).h $(PROJECT).hex

flash: $(PROJECT).hex
	pkcmd-lx -w -ppic$(MODEL) -f $(PROJECT).hex -mpc

flash2: $(PROJECT).hex
	pk2cmd -Ppic$(MODEL) -X -M -F $(PROJECT).hex

clean:
	@rm -f model.mk alias*.h *.o *.cod *.lst *.map *.hex $(PROJECT).asm \
                         $(patsubst %.c,%.asm,$(EXTRA_C)) $(EXTRA_CLEAN)


