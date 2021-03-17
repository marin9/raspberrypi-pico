#include "gpio.h"

#define APB_BASE			0x40000000
#define SIO_BASE			0xd0000000

#define GPIO_IN				(SIO_BASE + 0x04)
#define GPIO_OUT			(SIO_BASE + 0x10)
#define GPIO_OUT_SET		(SIO_BASE + 0x14)
#define GPIO_OUT_CLR		(SIO_BASE + 0x18)
#define GPIO_OUT_XOR		(SIO_BASE + 0x1C)
#define GPIO_OE				(SIO_BASE + 0x20)
#define GPIO_OE_SET			(SIO_BASE + 0x24)
#define GPIO_OE_CLR			(SIO_BASE + 0x28)
#define GPIO_OE_XOR			(SIO_BASE + 0x2C)

#define IO_BANK_BASE		(APB_BASE + 0x14000)
#define PADS_BANK0_BASE		(APB_BASE + 0x1C000)



#define WR(reg, val)	*((volatile unsigned int*)(reg)) = (val)
#define RD(reg)			*((volatile unsigned int*)(reg))




void gpio_init(uint gpio, uint fn) {
	WR(IO_BANK_BASE + (gpio * 8) + 4, fn);
}

void gpio_set_pull(uint gpio, uint up, uint down) {
	uint reg = 0;
	
	if (down)
		reg |= (1 << 2);
	if (up)
		reg |= (1 << 3);
		
	WR(PADS_BANK0_BASE + 4 + (gpio * 4), reg);
}

void gpio_set_dir(uint gpio, uint out) {
	if (out)
		WR(GPIO_OE_SET, 1 << gpio);
	else
		WR(GPIO_OE_CLR, 1 << gpio);
}

void gpio_set_dir_all(uint mask) {
	WR(GPIO_OE, mask);
}

void gpio_set(uint gpio, uint val) {
	if (val)
		WR(GPIO_OUT_SET, 1 << gpio);
	else
		WR(GPIO_OUT_CLR, 1 << gpio);
}

void gpio_set_all(uint mask) {
	WR(GPIO_OUT, mask);
}

uint gpio_get(uint gpio) {
	return RD(GPIO_IN) & (1 << gpio);
}

uint gpio_get_all() {
	return RD(GPIO_IN);
}


/*
void gpio_set_irq(uint gpio, uint event, uint en, func callback) {
	//TODO
}

void gpio_ack_irq(uint gpio, uint event) {
	//TODO
}
*/

