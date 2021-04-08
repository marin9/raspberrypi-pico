#include "resets.h"
#include "gpio.h"
#include "nvic.h"
#include "xosc.h"
#include "systick.h"


void init() {
	xosc_init();
	IO_WR(CLOCKS_BASE+0x48, 0x880); // clk_peri enble

	reset_release_wait(RESET_IO_BANK0);
	reset_release_wait(RESET_PADS_BANK0);

	gpio_init(19, GPIO_FUNC_SIO);
	gpio_dir(19, 1);

	nvic_init();
	systick_init();
	systick_set(6000000-1);

	while (1);
}
