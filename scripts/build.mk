include $(SCRIPTS_DIR)/build-include.mk
include $(SCRIPTS_DIR)/compiler-host.mk
include .config

src := $(object)
obj := $(object)

all: __build

target-build-dir := $(if $(filter /%,$(src)),$(src),$(TOPDIR)/$(src))
target-build-mk := $(wildcard $(target-build-dir)/Makefile)

ifeq ($(target-build-mk),)
$(error "no Makefile to make target: $(obj)")
endif # target-build-mk == ""

include $(target-build-mk)

ifneq ($(hostprog),)
include $(SCRIPTS_DIR)/build-host.mk
endif # hostprog != ""

__build: $(hostprog)
	@:

# if obj directory is not exist, create for it
ifeq ($(wildcard $(obj)),)
$(shell mkdir -p $(obj))
endif # $(wildcard $(obj)) == ""

.PHONY: $(PHONY)
