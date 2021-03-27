#include "gpio.h"

struct io_bank0_hw {
	struct gpio {
		uint status;
		uint ctrl;
	} gpio[29];
	// TODO
};

struct pads_bank0_hw {
	uint voltage_select;
	uint gpio[29];
	uint swclk;
	uint swd;
};

struct sio_hw {
	uint cpuid;
	uint gpio_in;
	uint gpio_hi_in;
	uint unused;
	uint gpio_out;
	uint gpio_out_set;
	uint gpio_out_clr;
	uint gpio_out_xor;
	uint gpio_oe;
	uint gpio_oe_set;
	uint gpio_oe_clr;
	uint gpio_oe_xor;
	uint gpio_hi_out;
	uint gpio_hi_out_set;
	uint gpio_hi_out_clr;
	uint gpio_hi_out_xor;
	uint gpio_hi_oe;
	uint gpio_hi_oe_set;
	uint gpio_hi_oe_clr;
	uint gpio_hi_oe_xor;
	uint fifo_st;
	uint fifo_wr;
	uint fifo_rd;
	uint spinlock_st;
	uint div_udividend;
	uint div_udivisor;
	uint div_sdividend;
	uint div_sdivisor;
	uint div_quotient;
	uint remainder;
	uint div_csr;
};

struct splock {
	uint spinlock[32];
};


#define FIFO_ST_ROE		8
#define FIFO_ST_WOF		4
#define FIFO_ST_RDY		2
#define FIFO_ST_VLD		1

#define DIV_SCR_DIRTY	2
#define DIV_CSR_READY	1


#define io		((volatile struct io_bank0_hw*)IO_BANK0_BASE)
#define pads 	((volatile struct pads_bank0_hw*)PADS_BANK0_BASE)
#define sio		((volatile struct sio_hw*)SIO_BASE)
#define splock	((volatile struct splock_hw*)(SIO_BASE + 0x100))



void gpio_init(uint gpio, uint fn) {
	io->gpio[gpio].ctrl = fn;
	pads->gpio[gpio] = (1 << 6); // input enable
}

void gpio_set_pull(uint gpio, uint up, uint down) {
	uint reg = pads->gpio[gpio];
//TODO
	if (down)
		reg |= (1 << 2);
	if (up)
		reg |= (1 << 3);

	pads->gpio[gpio] = reg;
}

void gpio_set_dir(uint gpio, uint out) {
	if (out) {
		sio->gpio_oe_set = 1 << gpio;
	} else {
		sio->gpio_oe_clr = 1 << gpio;
		pads->gpio[gpio] = (1 << 6) | (1 << 7);
	}
}

void gpio_set_dir_all(uint mask) {
	sio->gpio_oe = mask;
}

void gpio_set(uint gpio, uint val) {
	if (val)
		sio->gpio_out_set = 1 << gpio;
	else
		sio->gpio_out_clr = 1 << gpio;
}

void gpio_set_all(uint mask) {
	sio->gpio_out = mask;
}

uint gpio_get(uint gpio) {
	return sio->gpio_in & (1 << gpio);
}

uint gpio_get_all() {
	return sio->gpio_in;
}


/*
void gpio_set_irq(uint gpio, uint event, uint en, func callback) {
	//TODO
}

void gpio_ack_irq(uint gpio, uint event) {
	//TODO
}
*/
