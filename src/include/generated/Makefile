offsets-target := $(GENERATED_INC_DIR)/asm-offsets.h
offsets-asm := $(TARGET_OUTDIR)/arch/$(ARCH)/kernel/asm-offsets.s
offsets-src := $(SRCDIR)/arch/$(ARCH)/kernel/asm-offsets.c

autogen-target += $(offsets-target)

$(offsets-target): $(offsets-asm) FORCE
	$(call autogen,offsets,_ASM_OFFSETS_H_)

define sed-offsets
	's:^[[:space:]]*\.ascii[[:space:]]*"\(.*\)".*:\1:;		\
	/^->/s:^->\([^ ]*\) \([^ ]*\) \(.*\):#define \1 \2 /* \3 */:p;'
endef

define autogen_offsets
	echo "#ifndef $2";		\
	echo "#define $2";		\
	echo "";			\
	sed -ne $(sed-offsets) < $<;	\
	echo "#endif /* $2 */";
endef

# TODO:
# Should use some other clever ways to create directory and include commands
ifeq ($(wildcard $(dir $(offsets-asm))),)
$(shell mkdir -p $(dir $(offsets-asm)))
endif # $(wildcard $(obj)) == ""

-include $(dir $(offsets-asm))/.$(notdir $(offsets-asm)).cmd
