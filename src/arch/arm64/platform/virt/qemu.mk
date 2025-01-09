-include $(TOPDIR)/.config

qflags-y += -machine virt
qflags-y += -cpu cortex-a57
qflags-y += -machine type=virt
qflags-y += -nographic
qflags-y += -m 2048
qflags-y += -smp 2

qflags-$(CONFIG_ARM64_HYPERVISOR) += -machine virtualization=on
qflags-$(CONFIG_ARM64_TRUSTZONE) += -machine secure=on
