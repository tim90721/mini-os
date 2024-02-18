QFLAGS := -nographic -smp 1 -machine virt -bios none

quiet_cmd_qemu_run =   RUN    $(patsubst $(TARGET_OUTDIR)/%,%,$(TARGET_ELF))
cmd_qemu_run = $(QEMU) $(QFLAGS) -kernel $(TARGET_ELF)

quiet_cmd_qemu_debug =   DBG    $(patsubst $(TARGET_OUTDIR)/%,%,$(TARGET_ELF))
cmd_qemu_debug = $(QEMU) $(QFLAGS) -kernel $(TARGET_ELF) -s -S & \
		$(GDB) $(TARGET_ELF) $(GDB_FLAGS)
