#include <interrupt.h>
#include <mmio.h>
#include <stdint.h>
#include <time.h>

#include <arch/riscv.h>

#include <platform/platform.h>

#define CLINT_MTIMECMP_L(hart)		(0x4000 + 0x8 * (hart) + 0x0)
#define CLINT_MTIMECMP_H(hart)		(0x4000 + 0x8 * (hart) + 0x4)
#define CLINT_MTIME			(0xBFF8)

static u32 HZ = CONFIG_TIMER_INTERVAL;

static inline void clint_write(uintptr_t addr, u64 val)
{
	mmio_write_64(CLINT_BASE + addr, val);
}

static inline u64 clint_read(uintptr_t addr)
{
	return mmio_read_64(CLINT_BASE + addr);
}

static void riscv_timer_reload(u32 val)
{
	clint_write(CLINT_MTIMECMP_L(0), clint_read(CLINT_MTIMECMP_L(0)) + val);
}

static void riscv_timer_handler(void)
{
	tick++;
	riscv_timer_reload(HZ);
}

int arch_time_init(void)
{
	set_arch_timer_handler(riscv_timer_handler);

	riscv_timer_reload(HZ);

	return 0;
}
