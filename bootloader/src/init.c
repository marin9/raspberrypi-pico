#include "resets.h"
#include "gpio.h"
#include "uart.h"

void delay(int t) {
	while (t--)
		asm volatile ("nop");
}

void init() {
	//IO_WR(CLOCKS_BASE+0x48, 0x880); 		// Enable clk_peri
	reset_release_wait(RESET_IO_BANK0);
	reset_release_wait(RESET_PADS_BANK0);
	reset_release_wait(RESET_UART0);

	uart_init(0);
	gpio_init(0, GPIO_FUNC_UART);
	gpio_init(1, GPIO_FUNC_UART);
	gpio_dir(0, 1);

	while (1) {
		uart_print("XIP 1\r\n");
		delay(500000);
		uart_print("XIP  2\r\n");
		delay(500000);
		uart_print("XIP   3\r\n");
		delay(500000);
		uart_print("XIP    4\r\n");
		delay(500000);
		uart_print("XIP     5\r\n");
		delay(500000);
	}
}
