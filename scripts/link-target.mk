include .config
include $(SCRIPTS_DIR)/build-include.mk
include $(SCRIPTS_DIR)/compiler.mk

out-elf := $(elf)
src-lib := $(lib)

all: __link

__link: $(out-elf)

# default output linker script
TARGET_OUTPUT_LD := $(SRCDIR)/arch/$(ARCH)/platform/$(PLATFORM)/output.ld

LD_FLAGS += -T $(TARGET_OUTPUT_LD)
LD_FLAGS += -Wl,-Map=$(TARGET_OUTDIR)/$(TARGET).map

ld-flags := $(LD_FLAGS) $(ld-flags-y) -Wl,--whole-archive
quiet_cmd_link =   LINK   $(patsubst $(TARGET_OUTDIR)/%,%,$@)
cmd_link = $(CC) $(ld-flags) -o $@ $<
$(out-elf): $(src-lib) FORCE
	$(call if_changed,link)

PHONY += FORCE
FORCE:

-include $(dir $(out-elf))/.$(notdir $(out-elf)).cmd
.PHONY: $(PHONY)
