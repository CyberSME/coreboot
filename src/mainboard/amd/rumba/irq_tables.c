/*
 * This file is part of the coreboot project.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <arch/pirq_routing.h>

/* Platform IRQs */
#define PIRQA 11
#define PIRQB 5
#define PIRQC 10
#define PIRQD 10

/* Map */
#define M_PIRQA (1 << PIRQA)	/* Bitmap of supported IRQs */
#define M_PIRQB (1 << PIRQB)	/* Bitmap of supported IRQs */
#define M_PIRQC (1 << PIRQC)	/* Bitmap of supported IRQs */
#define M_PIRQD (1 << PIRQD)	/* Bitmap of supported IRQs */

/* Link */
#define L_PIRQA	 1		/* Means Slot INTx# Connects To Chipset INTA# */
#define L_PIRQB	 2		/* Means Slot INTx# Connects To Chipset INTB# */
#define L_PIRQC	 3		/* Means Slot INTx# Connects To Chipset INTC# */
#define L_PIRQD	 4		/* Means Slot INTx# Connects To Chipset INTD# */

static const struct irq_routing_table intel_irq_routing_table = {
	PIRQ_SIGNATURE,  /* u32 signature */
	PIRQ_VERSION,    /* u16 version   */
	32+16*CONFIG_IRQ_SLOT_COUNT,	 /* there can be total CONFIG_IRQ_SLOT_COUNT devices on the bus */
	0x00,		 /* Where the interrupt router lies (bus) */
	(0x12<<3)|0x0,   /* Where the interrupt router lies (dev) */
	0x800,		 /* IRQs devoted exclusively to PCI usage */
	0x1078,		 /* Vendor */
	0x2,		 /* Device */
	0,		 /* Miniport data */
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* u8 rfu[11] */
	0xdf,         /*  u8 checksum , this hase to set to some value that would give 0 after the sum of all bytes for this structure (including checksum) */
	{
		/* bus,     dev|fn,   {link, bitmap}, {link, bitmap}, {link, bitmap}, {link, bitmap},  slot, rfu */
		{0x00,(0x0e<<3)|0x0, {{0x02, 0xdeb8}, {0x03, 0xdeb8}, {0x04, 0xdeb8}, {0x01, 0x0deb8}}, 0x1, 0x0},
		{0x00,(0x0f<<3)|0x0, {{0x03, 0xdeb8}, {0x04, 0xdeb8}, {0x01, 0xdeb8}, {0x02, 0x0deb8}}, 0x2, 0x0},
	}
};
unsigned long write_pirq_routing_table(unsigned long addr)
{
        return copy_pirq_routing_table(addr, &intel_irq_routing_table);
}
