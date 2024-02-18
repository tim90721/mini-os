all:

CROSS_COMPILE ?= riscv32-unknown-elf-
QEMU ?= qemu-system-riscv32
export CROSS_COMPILE QEMU

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

# target related variables including target name, directory name etc.
TARGET		?= image
TARGET_SRCDIR	:= $(SRCDIR)/
TARGET_OUTDIR	:= $(OUTDIR)/$(TARGET)
TARGET_LIB	:= $(TARGET_OUTDIR)/built-in.a
TARGET_ELF	:= $(TARGET_OUTDIR)/$(TARGET).elf
export TARGET TARGET_OUTDIR

include $(SCRIPTS_DIR)/verbosity.mk
include $(SCRIPTS_DIR)/build-include.mk
include $(SCRIPTS_DIR)/qemu.mk

MAKEFLAGS += --no-print-directory

menuconfig:
	@export srctree=$(SRCDIR);					\
	python3 $(KCONFIG_DIR)/menuconfig.py Config.in

config:
	$(if $(wildcard .config),,$(error "please configure project first"))

all: build
	@:

build: config tools $(TARGET_ELF)

tools: FORCE
	$(Q)$(MAKE) $(build)=tools/basic

$(TARGET_ELF): $(TARGET_LIB)
	$(Q)$(MAKE) -f $(SCRIPTS_DIR)/link-target.mk elf=$(TARGET_ELF) lib=$(TARGET_LIB)

$(TARGET_LIB): $(TARGET_SRCDIR)

PHONY += $(TARGET_SRCDIR)
$(TARGET_SRCDIR):
	$(Q)$(MAKE) $(build)=$@

quiet_cmd_clean =   CLEAN
cmd_clean = rm -rf $(OUTDIR)
PHONY += clean
clean:
	$(call cmd,clean)

PHONY += run
run: $(TARGET_ELF)

PHONY += FORCE
FORCE:

.PHONY: $(PHONY)
