#include "resets.h"
#include "gpio.h"


void delay(int t) {
	while (t--)
		asm volatile ("nop");
}

void tc1();

void init() {

	reset_release_wait(RESET_IO_BANK0);
	reset_release_wait(RESET_PADS_BANK0);

	tc1();

	gpio_init(25, GPIO_FUNC_SIO);
	gpio_set_dir(25, 1);

	while (1) {
		delay(100000);
		gpio_set(25, 1);
		delay(100000);
		gpio_set(25, 0);
	}
}
