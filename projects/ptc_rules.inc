# --------------------------------------------------------------------------
# Generic build rules for all projects
#
# Author: Bernhard Bablok
#
# https://github.com/bablokb/pic-toolchain
#
# --------------------------------------------------------------------------

default:
	@echo "make config:    configure project"
	@echo "make build:     create $(PROJECT).hex"
	@echo "make flash:     build and flash $(PROJECT).hex to PIC using PICKitPlus"
	@echo "make flash2:    build and flash $(PROJECT).hex to PIC using pk2cmd"
	@echo "make clean:     remove intermediate files"
	@echo "make distclean: remove all generated files"

# --- configuration   ------------------------------------------------------

TC=sdcc
include tc.mk

# --- includes   -----------------------------------------------------------

ifneq ($(MAKECMDGOALS),default)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),)
include model.mk
endif
endif
endif

# --- targets   ------------------------------------------------------------

.PH0NY: mcheck flash flash2 clean

tc.mk:
	@echo -en "creating tc.mk ... "
	@if [ -z "$(TC)" ]; then \
          echo "toolchain $$TC undefined, aborting!"; rm -f tc.mk; exit 3; \
	else \
	  echo -e "include ptc_rules_$(TC).inc\nTC=$(TC)" > tc.mk; \
	fi

model.mk:
	@echo -en "creating model.mk ... "
	@if [ -z "$(MODEL)" -o "$(MODEL)" = "auto" ]; then pk2cmd -p | \
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

config: model.mk
	@echo -e "project configuration:\n\tMODEL=$(MODEL)\n\tTC=$(TC)"

build: mcheck picconfig.h picconfig.inc $(PROJECT).hex

flash: $(PROJECT).hex
	pkcmd-lx -w -ppic$(MODEL) -f $(PROJECT).hex -mpc

flash2: $(PROJECT).hex
	pk2cmd -Ppic$(MODEL) -X -M -F $(PROJECT).hex

distclean: clean
	@rm -f tc.mk model.mk
