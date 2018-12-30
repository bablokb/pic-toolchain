# --------------------------------------------------------------------------
# Generic build rules for all projects
#
# Author: Bernhard Bablok
#
# https://github.com/bablokb/pic-toolchain
#
# --------------------------------------------------------------------------

LIBDIR=/usr/local/share/sdcc/lib/pic14
LIBDIR_NONFREE=/usr/local/share/sdcc/non-free/lib/pic14
LIBS=libsdcc.lib pic$(MODEL).lib
OBJS=$(PROJECT).o $(patsubst %.asm,%.o,$(EXTRA_ASM))

# --- pattern  -------------------------------------------------------------

.c.o:
	sdcc --use-non-free -m$(ARCH) -p$(MODEL) -c $<

$(patsubst %.asm,%.o,$(EXTRA_ASM)): %.o: %.asm
	gpasm -a inhx8m -p$(MODEL) -c $<

$(PROJECT).hex: $(OBJS)
	gplink -S2 -w -r -m -a inhx8m -I$(LIBDIR) -I$(LIBDIR_NONFREE) \
                  -o $(PROJECT).hex $(OBJS) $(LIBS)

# --- targets   ------------------------------------------------------------

.PH0NY: flash clean

default:
	@echo "make build: create $(PROJECT).hex"
	@echo "make flash: build and flash hex-file to PIC"
	@echo "make clean: remove intermediate files"

build: $(PROJECT).hex

flash: $(PROJECT).hex
	pk2cmd -Ppic$(MODEL) -X -M -F $(PROJECT).hex

clean:
	@rm -f *.o *.cod *.lst *.map *.hex $(PROJECT).asm $(EXTRA_CLEAN)


