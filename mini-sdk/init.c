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

	tc0();

}
