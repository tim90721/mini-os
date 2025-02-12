#include <compiler.h>
#include <errno.h>
#include <interrupt.h>
#include <mmio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include <drivers/irqchip/irqchip-gic-v2.h>

#include <platform/platform.h>

static int gic_irq_enable(struct irq_desc *, bool en);
static int gic_irq_set_priority(struct irq_desc *desc, u32 priority);
static struct irq_desc *gic_irq_desc_get(enum irq_id id);

struct gic_device {
	struct irq_chip chip;
	struct {
		uintptr_t dist;
		uintptr_t cpu;
	} base;
};

static struct gic_device gic = {
	.chip = {
		.irq_enable = gic_irq_enable,
		.irq_set_priority = gic_irq_set_priority,
		.irq_desc_get = gic_irq_desc_get,
	},
	.base = {
		.dist = GIC_BASE_DIST,
		.cpu = GIC_BASE_CPU,
	},
};

static struct irq_desc gic_irqdescs[__NR_GIC_IRQ] = {
	[0 ... __NR_GIC_IRQ - 1] = {
		.action.irq_handler = unused_irq_handler,
		.chip = &gic.chip,
	},
};

static inline void gic_dist_write(uintptr_t ofs, u32 val)
{
	mmio_write_32(gic.base.dist + ofs, val);
}

static inline u32 gic_dist_read(uintptr_t ofs)
{
	return mmio_read_32(gic.base.dist + ofs);
}

static inline void gic_cpu_write(uintptr_t ofs, u32 val)
{
	mmio_write_32(gic.base.cpu + ofs, val);
}

static inline u32 gic_cpu_read(uintptr_t ofs)
{
	return mmio_read_32(gic.base.cpu + ofs);
}

static int gic_irq_enable(struct irq_desc *desc, bool en)
{
	enum gic_irq_id id;

	if (!desc)
		return -EINVAL;

	id = desc->id - __GIC_IRQ_ID_OFS;
	if (unlikely(id >= __NR_GIC_IRQ))
		return -EINVAL;

	if (en)
		gic_dist_write(GICD_ISENABLER(id), 1 << (id % 32));
	else
		gic_dist_write(GICD_ICENABLER(id), 1 << (id % 32));

	return 0;
}

static int gic_irq_set_priority(struct irq_desc *desc, u32 priority)
{
	enum gic_irq_id id;

	if (!desc)
		return -EINVAL;

	id = desc->id - __GIC_IRQ_ID_OFS;
	if (unlikely(id >= __NR_GIC_IRQ))
		return -EINVAL;

	gic_dist_write(GICD_IPRIORITYR(id),
		       gic_dist_read(GICD_IPRIORITYR(id)) | (priority << ((id % 4) * 8)));

	return 0;
}

static struct irq_desc *gic_irq_desc_get(enum irq_id id)
{
	enum gic_irq_id gid = id - __GIC_IRQ_ID_OFS;

	if (gid >= __NR_GIC_IRQ)
		return NULL;
	return &gic_irqdescs[gid];
}

static int gic_dist_init(void)
{
	u32 i;

	gic_dist_write(GICD_CTLR, gic_dist_read(GICD_CTLR) & (~GICD_CTLR_ENABLE));

	/* initialize IRQ send to CPU #0, all priority to lowest */
	for (i = 32; i < __NR_GIC_IRQ; i += 4) {
		gic_dist_write(GICD_ITARGETR(i), 0x01010101);
		gic_dist_write(GICD_IPRIORITYR(i), 0xFF);
	}

	gic_dist_write(GICD_CTLR, gic_dist_read(GICD_CTLR) | GICD_CTLR_ENABLE);

	return 0;
}

static int gic_cpu_init(void)
{
	/* initialize CPU to allow all IRQ -> priority mask to 0xFF */
	gic_cpu_write(GICC_PMR, 0xFF);
	gic_cpu_write(GICC_CTLR, gic_cpu_read(GICC_CTLR) | GICC_CTLR_ENABLE);

	return 0;
}

static void gic_show_info(void)
{
	u32 iidr = gic_dist_read(GICD_IIDR);

	printf("GIC product ID: 0x%x, variant: 0x%x, revision: 0x%x, manufacturer: 0x%x\n",
		(iidr >> GICD_IIDR_PROD_ID_SHIFT) & GICD_IIDR_PROD_ID_MASK,
		(iidr >> GICD_IIDR_VARIANT_SHIFT) & GICD_IIDR_VARIANT_MASK,
		(iidr >> GICD_IIDR_REV_SHIFT) & GICD_IIDR_REV_MASK,
		(iidr >> GICD_IIDR_MAKER_SHIFT) & GICD_IIDR_MAKER_MASK);
}

static void gic_arch_irq_handler(void)
{
	struct irq_desc *desc;
	enum gic_irq_id id;

	/* read irq ID and acknowledge */
	id = gic_cpu_read(GICC_IAR);
	if (unlikely(id >= __NR_GIC_IRQ))
		exit(-EINVAL); /* should not end here */

	/* call IRQ handler */
	desc = &gic_irqdescs[id];
	desc->action.irq_handler(desc->action.priv);

	/* EOI */
	gic_cpu_write(GICC_EOIR, id);
}

int gic_init(void)
{
	struct irq_desc *desc;
	u32 i;

	for (i = 0; i < __NR_GIC_IRQ; i++) {
		desc = &gic_irqdescs[i];
		desc->id = i + __GIC_IRQ_ID_OFS;
	}

	/* initialize distributer */
	gic_dist_init();

	/* initialize cpu interface */
	gic_cpu_init();

	/* show GIC information */
	gic_show_info();

	set_arch_irq_handler(gic_arch_irq_handler);

	return register_irqchip(IRQCHIP_GIC, &gic.chip);
}
