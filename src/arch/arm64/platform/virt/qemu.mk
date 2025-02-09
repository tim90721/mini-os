-include $(TOPDIR)/.config

qflags-y += -machine virt,gic-version=$(CONFIG_ARM64_VIRT_GIC_VERSION)
qflags-y += -cpu cortex-a57
qflags-y += -nographic
qflags-y += -m 2048
qflags-y += -smp $(CONFIG_ARM64_VIRT_CPU_CORES)

qflags-$(CONFIG_ARM64_HYPERVISOR) += -machine virtualization=on
qflags-$(CONFIG_ARM64_TRUSTZONE) += -machine secure=on
