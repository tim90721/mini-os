#ifndef _MMIO_H_
#define _MMIO_H_

#include <stdint.h>

static inline u8 mmio_read_8(uintptr_t addr)
{
	return *(volatile u8 *)addr;
}

static inline void mmio_write_8(uintptr_t addr, u8 val)
{
	*(volatile u8 *)addr = val;
}

static inline void mmio_clrbits_8(uintptr_t addr, u8 mask)
{
	*(volatile u8 *)addr &= ~mask;
}

static inline void mmio_setbits_8(uintptr_t addr, u8 mask)
{
	*(volatile u8 *)addr |= mask;
}

static inline void mmio_clrsetbits_8(uintptr_t addr, u8 mask, u8 val)
{
	*(volatile u8 *)addr &= ~mask;
	*(volatile u8 *)addr |= val;
}

static inline u16 mmio_read_16(uintptr_t addr)
{
	return *(volatile u16 *)addr;
}

static inline void mmio_write_16(uintptr_t addr, u16 val)
{
	*(volatile u16 *)addr = val;
}

static inline void mmio_clrbits_16(uintptr_t addr, u16 mask)
{
	*(volatile u16 *)addr &= ~mask;
}

static inline void mmio_setbits_16(uintptr_t addr, u16 mask)
{
	*(volatile u16 *)addr |= mask;
}

static inline void mmio_clrsetbits_16(uintptr_t addr, u16 mask, u16 val)
{
	*(volatile u16 *)addr &= mask;
	*(volatile u16 *)addr |= val;
}

static inline u32 mmio_read_32(uintptr_t addr)
{
	return *(volatile u32 *)addr;
}

static inline void mmio_write_32(uintptr_t addr, u32 val)
{
	*(volatile u32 *)addr = val;
}

static inline void mmio_clrbits_32(uintptr_t addr, u32 mask)
{
	*(volatile u32 *)addr &= ~mask;
}

static inline void mmio_setbits_32(uintptr_t addr, u32 mask)
{
	*(volatile u32 *)addr |= mask;
}

static inline void mmio_clrsetbits_32(uintptr_t addr, u32 mask, u32 val)
{
	*(volatile u32 *)addr &= ~mask;
	*(volatile u32 *)addr |= val;
}
#endif /* _MMIO_H_ */
