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
	//TODO
};

#define io		((volatile struct io_bank0_hw*)IO_BANK0_BASE)
#define pads 	((volatile struct pads_bank0_hw*)PADS_BANK0_BASE)
#define sio		((volatile struct sio_hw*)SIO_BASE)


void gpio_init(uint gpio, uint fn) {
	io->gpio[gpio].ctrl = fn;
	//TODO
}

void gpio_set_pull(uint gpio, uint up, uint down) {
	uint reg = 0;

	if (down)
		reg |= (1 << 2);
	if (up)
		reg |= (1 << 3);

	pads->gpio[gpio] = reg;
}

void gpio_set_dir(uint gpio, uint out) {
	if (out)
		sio->gpio_oe_set = 1 << gpio;
	else
		sio->gpio_oe_clr = 1 << gpio;
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
