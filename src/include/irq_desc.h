#ifndef _IRQ_DESC_H_
#define _IRQ_DESC_H_

struct irq_action {
	int (*irq_handler)(void *priv);
	void *priv;
};

struct irq_desc {
	struct irq_action action;
	struct irq_chip *chip;
	enum irq_id id;
	bool en;
	u32 en_cnt;
};
#endif /* _IRQ_DESC_H_ */
