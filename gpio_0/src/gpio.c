#include "gpio.h"

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
};

struct io_bank0_hw {
	struct gpio {
		uint status;
		uint ctrl;
	} gpio[30];
};

struct pads_bank0_hw {
	uint voltage_select;
	uint gpio[30];
	uint swclk;
	uint swd;
};

#define sio		((volatile struct sio_hw*)SIO_BASE)
#define io		((volatile struct io_bank0_hw*)IO_BANK0_BASE)
#define pads 	((volatile struct pads_bank0_hw*)PADS_BANK0_BASE)


#define PADS_GPIO_OD				(1 << 7)
#define PADS_GPIO_IE				(1 << 6)
#define PADS_GPIO_PUE				(1 << 3)
#define PADS_GPIO_PDE				(1 << 2)


void gpio_init(uint gpio, uint func) {
	io->gpio[gpio].ctrl = func;
	pads->gpio[gpio] = PADS_GPIO_IE | PADS_GPIO_OD;
	sio->gpio_oe_clr = 1 << gpio;
}

void gpio_dir(uint gpio, uint out) {
	if (out) {
		sio->gpio_oe_set = 1 << gpio;
		pads->gpio[gpio] = 0;
	} else {
		sio->gpio_oe_clr = 1 << gpio;
		pads->gpio[gpio] = PADS_GPIO_IE | PADS_GPIO_OD;
	}
}

void gpio_set(uint gpio, uint value) {
	if (value)
		sio->gpio_out_set = 1 << gpio;
	else
		sio->gpio_out_clr = 1 << gpio;
}

uint gpio_get(uint gpio) {
	return sio->gpio_in & (1 << gpio);
}

void gpio_pullup(uint gpio, uint enable) {
	uint reg = pads->gpio[gpio];

	if (enable) {
		reg |= PADS_GPIO_PUE;
	} else {
		reg &= (~PADS_GPIO_PUE);
	}
	pads->gpio[gpio] = reg;
}

void gpio_pulldown(uint gpio, uint enable) {
	uint reg = pads->gpio[gpio];

	if (enable) {
		reg |= PADS_GPIO_PDE;
	} else {
		reg &= (~PADS_GPIO_PDE);
	}
	pads->gpio[gpio] = reg;
}
