all:

# remove all default make rules
MAKEFLAGS += -rR

# default directories
TOPDIR		:= $(CURDIR)
SRCDIR		:= src
OUTDIR		:= $(TOPDIR)/build
TOOLS_DIR	:= $(TOPDIR)/tools
SCRIPTS_DIR	:= $(TOPDIR)/scripts
KCONFIG_DIR	:= $(TOOLS_DIR)/Kconfiglib

ifeq ("$(origin O)","command line")
	OUTDIR := $(O)
endif

# basic output directories
OUTDIR		:= $(shell mkdir -p $(OUTDIR) && cd $(OUTDIR) && pwd)
ifeq ($(OUTDIR),)
$(error "create output directory: $(OUTDIR) failed")
endif

TOOLS_OUTDIR	:= $(OUTDIR)/tools
export TOPDIR SRCDIR OUTDIR SCRIPTS_DIR KCONFIG_DIR TOOLS_OUTDIR

include $(SCRIPTS_DIR)/verbosity.mk
include $(SCRIPTS_DIR)/build-include.mk

MAKEFLAGS += --no-print-directory

menuconfig:
	@export srctree=$(SRCDIR);					\
	python3 $(KCONFIG_DIR)/menuconfig.py Config.in

config:
	$(if $(wildcard .config),,$(error "please configure project first"))

all: config tools
	@:

tools: FORCE
	$(Q)$(MAKE) $(build)=tools/basic

PHONY += FORCE
FORCE:

.PHONY: $(PHONY)
