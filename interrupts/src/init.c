#include "resets.h"
#include "gpio.h"
#include "nvic.h"
#include "xosc.h"


void delay(uint t) {
	while (t--)
		asm volatile ("nop");
}

void gpio_handler() {
	// Turn on LED
	gpio_set(18, 0);
	delay(100000);
	gpio_intr_ack(0);
}


void init() {
	xosc_init();
	IO_WR(CLOCKS_BASE+0x48, 0x880); // clk_peri enble

	reset_release_wait(RESET_IO_BANK0);
	reset_release_wait(RESET_PADS_BANK0);

	nvic_init();

	// LED
	gpio_init(18, GPIO_FUNC_SIO);
	gpio_dir(18, 1);

	// Button
	gpio_init(0, GPIO_FUNC_SIO);
	gpio_pullup(0, 1);
	gpio_intr_set(0, 1, GPIO_INT_EDGE_FALL);

	nvic_init();
	nvic_register_irq(IRQ_IO_BANK0, gpio_handler);
	nvic_enable(IRQ_IO_BANK0);

	while (1) {
		// Turn off LED
		gpio_set(18, 1);
	}
}
