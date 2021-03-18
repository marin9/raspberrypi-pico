#include "resets.h"
#include "gpio.h"


void delay(int t) {
	while (t--)
		asm volatile ("nop");
}

void init() {

	unreset_block_wait(RESET_IO_BANK0);

	gpio_init(25, GPIO_FUNC_SIO);
	gpio_set_dir(25, 1);

	while (1) {
		delay(100000);
		gpio_set(25, 1);
		delay(100000);
		gpio_set(25, 0);
	}
}
