include $(SRCDIR)/arch/$(ARCH)/platform/$(PLATFORM)/qemu.mk

QFLAGS = $(qflags-y)

quiet_cmd_qemu_run =   RUN    $(patsubst $(TARGET_OUTDIR)/%,%,$(TARGET_ELF))
cmd_qemu_run = $(QEMU) $(QFLAGS) -kernel $(TARGET_ELF)

quiet_cmd_qemu_debug =   DBG    $(patsubst $(TARGET_OUTDIR)/%,%,$(TARGET_ELF))
cmd_qemu_debug = $(QEMU) $(QFLAGS) -kernel $(TARGET_ELF) -s -S & \
		$(GDB) $(TARGET_ELF) $(GDB_FLAGS)
