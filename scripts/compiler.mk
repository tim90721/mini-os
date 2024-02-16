AS		= $(CROSS_COMPILE)as
AR		= $(CROSS_COMPILE)ar
CC		= $(CROSS_COMPILE)gcc
LD		= $(CROSS_COMPILE)ld
NM		= $(CROSS_COMPILE)nm
STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump
OBJSIZE		= $(CROSS_COMPILE)size

# default C flags
CFLAGS := -Wall -Werror		# enable all warning as error
CFLAGS += -fno-builtin		# disable compiler default built-in functions
CFLAGS += -I$(SRCDIR)/include	# add default include directories
CFLAGS += -I$(SRCDIR)/include/platform

# customizable C flags
ccflags-y :=

# default LD flags
LD_FLAGS := -nostdlib					# disable default libc implementation
LD_FLAGS += -Wl,-Map=$(TARGET_OUTDIR)/$(TARGET).map	# generate map
LD_FLAGS += -Ttext=0x80000000				# temporary linker script

# customizable LD flags
ldflags-y :=
