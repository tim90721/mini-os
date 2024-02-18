include $(SCRIPTS_DIR)/build-include.mk
include $(SCRIPTS_DIR)/compiler.mk
include .config

out-elf := $(elf)
src-lib := $(lib)

all: __link

__link: $(out-elf)


ld-flags := $(LD_FLAGS) $(ld-flags-y) -Wl,--whole-archive
quiet_cmd_link =   LINK   $(patsubst $(TARGET_OUTDIR)/%,%,$@)
cmd_link = $(CC) $(ld-flags) -o $@ $^
$(out-elf): $(src-lib)
	$(call if_changed,link)

PHONY += FORCE
FORCE:

.PHONY: $(PHONY)
