
src := $(patsubst %/,%,$(src))
obj := $(patsubst $(SRCDIR)/%,%,$(obj))
obj := $(TARGET_OUTDIR)/$(obj)
obj := $(patsubst %/,%,$(obj))

target := $(addsuffix built-in.a,$(obj)/)
subdir-obj-y := $(addsuffix built-in.a,$(addprefix $(obj)/,$(subdir-y)))
subdir-y := $(addprefix $(src)/,$(subdir-y))
obj-y := $(addprefix $(obj)/,$(obj-y))
obj-y += $(subdir-obj-y)

cflags = -Wp,-MD,$(depfile) $(CFLAGS) $(ccflags-y)

quiet_cmd_ar_builtin =   AR $(patsubst $(TARGET_OUTDIR)/%,%,$@)
cmd_ar_builtin = rm -rf $@; $(AR) cDPrST $@ $(filter-out $(PHONY), $^)
$(target): $(obj-y) FORCE		# aggregate objects to archives
	$(call if_changed,ar_builtin)

quiet_cmd_cc_o_c =   CC $(patsubst $(TARGET_OUTDIR)/%,%,$@)
cmd_cc_o_c = $(CC) $(cflags) -c -o $@ $<
$(obj)/%.o: $(src)/%.c FORCE		# compile .c to objects
	$(call if_changed_dep,cc_o_c)

quiet_cmd_cc_o_s =   ASM $(patsubst $(TARGET_OUTDIR)/%,%,$@)
cmd_cc_o_s = $(CC) $(cflags) -c -o $@ $<
$(obj)/%.o: $(src)/%.S FORCE		# assemble .s to objects
	$(call if_changed_dep,cc_o_s)
