autogen-cflags = -Wp,-MD,$(depfile) $(CFLAGS)

quiet_cmd_cc_s_c =   CC     $(patsubst $(OUTDIR)/%,%,$@)
cmd_cc_s_c = $(CC) $(autogen-cflags) -S -o $@ $<
$(TARGET_OUTDIR)/%.s: $(TARGET_SRCDIR)/%.c FORCE	# compile .c to assembly
	$(call if_changed_dep,cc_s_c)

define autogen
	$(Q)set -e;						\
	mkdir -p $(dir $@);					\
	{ $(autogen_$(1)) } > $@.tmp;				\
	if [ -r $@ ] && cmp -s $@ $@.tmp ; then			\
		rm $@.tmp;					\
	else							\
		echo "  GEN    $(patsubst $(OUTDIR)/%,%,$@)";	\
		mv $@.tmp $@;					\
	fi
endef
