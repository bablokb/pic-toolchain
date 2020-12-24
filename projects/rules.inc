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

TC=sdcc
MCLR=_MCLRE_OFF

# --- includes   -----------------------------------------------------------

rules_dir := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
include $(rules_dir)rules_$(TC).inc
ifneq ($(@),default)
ifneq ($(@),)
include model.mk
endif
endif

# --- targets   ------------------------------------------------------------

.PH0NY: mcheck flash flash2 clean

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

picconfig.h:
	@echo "creating picconfig.h"
	@echo '#include "picconfig_$(MODEL).h"' > picconfig.h

picconfig.inc:
	@echo "creating picconfig.inc"
	@echo '#include "p$(MODEL).inc"' > picconfig.inc

build: mcheck picconfig.h picconfig.inc $(PROJECT).hex

flash: $(PROJECT).hex
	pkcmd-lx -w -ppic$(MODEL) -f $(PROJECT).hex -mpc

flash2: $(PROJECT).hex
	pk2cmd -Ppic$(MODEL) -X -M -F $(PROJECT).hex
