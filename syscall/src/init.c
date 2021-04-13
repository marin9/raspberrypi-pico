#include "resets.h"
#include "gpio.h"
#include "nvic.h"
#include "xosc.h"
#include "uart.h"
#include "systick.h"


void delay(uint t) {
	while (t--)
		asm volatile ("nop");
}


void init() {
	xosc_init();
	IO_WR(CLOCKS_BASE+0x48, 0x880); // clk_peri enble

	reset_release_wait(RESET_IO_BANK0);
	reset_release_wait(RESET_PADS_BANK0);
	reset_release_wait(RESET_UART0);

	uart_init(0);
	gpio_init(0, GPIO_FUNC_UART);
	gpio_init(1, GPIO_FUNC_UART);
	gpio_dir(0, 1);

	gpio_init(19, GPIO_FUNC_SIO);
	gpio_dir(19, 1);

	nvic_init();
	systick_init();
	systick_set(1000000-1);

	while (1) {
		delay(1000000);
		uart_print("call svc\r\n");
		asm volatile ("svc #5");
		asm volatile ("svc #9");
		asm volatile ("svc #2");
	}
}
