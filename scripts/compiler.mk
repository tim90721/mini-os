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
CFLAGS := -Wall -Werror			# enable all warning as error
CFLAGS += -fno-builtin			# disable compiler default built-in functions
CFLAGS += -I$(SRCDIR)/include		# add default include directory
CFLAGS += -I$(SRCDIR)/libc/include	# add libc include directory
CFLAGS += -march=rv32g
CFLAGS += -mabi=ilp32

# arch default include directories
CFLAGS += -I$(SRCDIR)/arch/include
CFLAGS += -I$(SRCDIR)/arch/$(ARCH)/include
CFLAGS += -I$(SRCDIR)/arch/$(ARCH)/platform/$(PLATFORM)/include

# drivers default include directories
CFLAGS += -I$(SRCDIR)/drivers/include

# auto-generated include
CFLAGS += -I$(TARGET_OUTDIR)/include
CFLAGS += -include$(AUTOCONF_HEADER)

ifeq ($(DEBUG_BUILD),1)
CFLAGS += -g
endif

# customizable C flags
ccflags-y :=

# default LD flags
LD_FLAGS := -nostdlib					# disable default libc implementation

# customizable LD flags
ldflags-y :=
