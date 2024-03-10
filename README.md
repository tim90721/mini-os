# mini-os
mini-os is a project that is aimed to practice anything from scratch. The topic
includes but not limited to OS essential functions, system calls, libc
implementation, driver development or Makefile build system. The project
usually refers to Linux Kernel as its reference design. Some of the
implementations are inspired from
[riscv-operating-system-mooc](https://github.com/plctlab/riscv-operating-system-mooc)
and
[mini-riscv-os](https://github.com/cccriscv/mini-riscv-os).

This project uses a python library Kconfiglib to configure the project. For
more information about Kconfiglib, please refer to the
[github repo](https://github.com/ulfalizer/Kconfiglib).

The project only support RISC-V toolchain right now, however, it can be
extended to other architectures in the future.

## Requirements
To build this project, one must have **qemu** and **toolchain** installed. The
build system will assume the qemu and toolchain are already added to the system
path. Otherwise CROSS_COMPILE and QEMU should be provided to Make arguments.

The version of the building environment while developing this project are
 - QEMU version: 7.0.0 target: riscv32-softmmu
 - RISC-V toolchain architecture: RV32G ABI: ilp32d

## Installation
Since Kconfiglib is used and is presented in the .gitsubmodule list, the user
needs to clone Kconfiglib as well. Following of the two commands can be used to
clone the complete repository.
```
git clone --recurse-submodules https://github.com/tim90721/mini-os.git
```
or
```
git clone https://github.com/tim90721/mini-os.git
git submodule update --init --recursive
```

## Usage
Similar to Linux Kernel, the building process consists of at least two steps
which are configure and build image. In addition to configure and build, this
project also provides the ability to run and debug on the virtual machine.

### Configure
One must configure the project before building. To configure, use below command
```
make menuconfig
```
Once it is configured, a .config will be generated in the building directory.

[TODO] provide savedefconfig, defconfig etc. functions to configure a target
more efficiently.

### Build
To build the project without running, simply use below command
```
make
```
The default building directory will be <mini-os repo>/build. To build the
project in another directory,
```
make O=<path>
```

To build the project with other cross compiler
```
make CROSS_COMPILE=<toolchain prefix>
```

### Run and Debug
Once the image is built, the image can be loaded on the qemu for running and
debugging.

To run the image
```
make run
```

To debug the image
```
make debug
```

To use other virtual machine
```
make run QEMU=<qemu executable>
```

Note that, before running or debugging the image, if the iamge is not build yet,
the build system will automatically build it before running or debugging.

## Current Status
 - Boot
   - A basic startup file to bringup 1 CPU
   - [TODO]
     - interrupt setup
 - Kernel
   - [TODO]
     - scheduler
     - context switch
     - generic register definition generation by build system
     - task
     - memory management
     - MMU
     - system call
     - spinlock, mutex, semaphore
 - libc
   - printf
     - support %d, %x, %c, %s, %%
     - [TODO]
       - %p
       - %u
 - driver
   - UART
     - support basic RISC-V virt platform
