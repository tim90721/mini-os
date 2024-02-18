QFLAGS := -nographic -smp 1 -machine virt -bios none

quiet_cmd_qemu_run =   RUN    $(patsubst $(TARGET_OUTDIR)/%,%,$(TARGET_ELF))
cmd_qemu_run = $(QEMU) $(QFLAGS) -kernel $(TARGET_ELF)
run: $(TARGET_ELF)
	$(call cmd,qemu_run)
