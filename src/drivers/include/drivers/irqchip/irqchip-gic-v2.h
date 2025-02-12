#ifndef _IRQCHIP_GIC_V2_H_
#define _IRQCHIP_GIC_V2_H_

#include <stdint.h>

#include <bits.h>

/* Distributer */
#define GICD_CTLR		0x0000
#define GICD_TYPER		0x0004
#define GICD_IIDR		0x0008
#define GICD_IGROUPR(i)		(0x0080 + ((i) / 32) * 0x0004)
#define GICD_ISENABLER(i)	(0x0100 + ((i) / 32) * 0x0004)
#define GICD_ICENABLER(i)	(0x0180 + ((i) / 32) * 0x0004)
#define GICD_ISPENDR(i)		(0x0200 + ((i) / 32) * 0x0004)
#define GICD_ICPENDR(i)		(0x0280 + ((i) / 32) * 0x0004)
#define GICD_ISACTIVER(i)	(0x0300 + ((i) / 32) * 0x0004)
#define GICD_ICACTIVER(i)	(0x0380 + ((i) / 32) * 0x0004)
#define GICD_IPRIORITYR(i)	(0x0400 + ((i) / 4) * 0x0004)
#define GICD_ITARGETR(i)	(0x0800 + ((i) / 4) * 0x0004)
#define GICD_ICFGR(i)		(0x0C00 + ((i) / 2) * 0x0004)
#define GICD_PPISR		0x0D00
#define GICD_SPISR(i)		(0x0D04 + (((i) - 32) / 2) * 0x0004)
#define GICD_SGIR		0x0F00
#define GICD_CPENDSGIR(i)	(0x0F10 + ((i) / 4) * 0x0004)
#define GICD_SPENDSGIR(i)	(0x0F20 + ((i) / 4) * 0x0004)

/* CPU interface */
#define GICC_CTLR		0x0000
#define GICC_PMR		0x0004
#define GICC_BPR		0x0008
#define GICC_IAR		0x000C
#define GICC_EOIR		0x0010
#define GICC_RPR		0x0014
#define GICC_HPPIR		0x0018
#define GICC_ABPR		0x001C
#define GICC_AIAR		0x0020
#define GICC_AEOIR		0x0024
#define GICC_AHPPIR		0x0028
#define GICC_APR0		0x00D0
#define GICC_NSAPR0		0x00E0
#define GICC_IIDR		0x00FC
#define GICC_DIR		0x1000

/* GICD_CTLR */
#define GICD_CTLR_ENABLE	BIT(0)

/* GICD_IIDR */
#define GICD_IIDR_PROD_ID_MASK	0xFF
#define GICD_IIDR_PROD_ID_SHIFT	24
#define GICD_IIDR_VARIANT_MASK	0xF
#define GICD_IIDR_VARIANT_SHIFT	16
#define GICD_IIDR_REV_MASK	0xF
#define GICD_IIDR_REV_SHIFT	12
#define GICD_IIDR_MAKER_MASK	0xFFF
#define GICD_IIDR_MAKER_SHIFT	0

/* GICC_CTLR */
#define GICC_CTLR_ENABLE	BIT(0)

int gic_init(void);
#endif /* _IRQCHIP_GIC_V2_H_ */
