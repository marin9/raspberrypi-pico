#include "resets.h"
#include "gpio.h"
#include "uart.h"
#include "xosc.h"

void delay(uint t) {
	while (t--)
		asm volatile ("nop");
}

void init() {
	xosc_init();
	IO_WR(CLOCKS_BASE+0x48, 0x880); // Enable clk_peri

	reset_release_wait(RESET_IO_BANK0);
	reset_release_wait(RESET_PADS_BANK0);
	reset_release_wait(RESET_UART0);

	uart_init(0); // Baud rate = 115200
	gpio_init(0, GPIO_FUNC_UART);
	gpio_init(1, GPIO_FUNC_UART);
	gpio_dir(0, 1);

	while(1){
		uart_write(0, "ABCD\r\n", 7);
		delay(1000000);
	}
}
