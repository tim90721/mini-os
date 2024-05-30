include .config
include $(SCRIPTS_DIR)/build-include.mk
include $(SCRIPTS_DIR)/compiler.mk
include $(SCRIPTS_DIR)/compiler-host.mk

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
else # hostprog == ""

ifneq ($(autogen-target),)
include $(SCRIPTS_DIR)/build-autogen.mk
else # autogen-target == ""
include $(SCRIPTS_DIR)/build-target.mk
endif # autogen-target != ""

endif # hostprog != ""

__build: $(hostprog) $(autogen-target) $(target) $(subdir-obj-y)
	@:

$(subdir-obj-y): $(subdir-y)

PHONY += $(subdir-y)
$(subdir-y):
	$(Q)$(MAKE) $(build)=$@

PHONY += FORCE
FORCE:

# if obj directory is not exist, create for it
ifeq ($(wildcard $(obj)),)
$(shell mkdir -p $(obj))
endif # $(wildcard $(obj)) == ""

-include $(foreach m,$(target) $(obj-y),$(dir $(m))/.$(notdir $(m)).cmd)
.PHONY: $(PHONY)
