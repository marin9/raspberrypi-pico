#include "resets.h"
#include "gpio.h"
#include "uart.h"
#include "flash.h"


void delay(int t) {
	while (t--)
		asm volatile ("nop");
}

static char buff[4096];


void init() {
	IO_WR(CLOCKS_BASE + 0x48, 0x880); 		// Enable clk_peri
	reset_release_wait(RESET_IO_BANK0);
	reset_release_wait(RESET_PADS_BANK0);
	reset_release_wait(RESET_UART0);

	uart_init(0);
	gpio_init(0, GPIO_FUNC_UART);
	gpio_init(1, GPIO_FUNC_UART);
	gpio_dir(0, 1);

	flash_init();
	//flash_sector_write(0, "0123456789abcdefghijklmno");
	flash_sector_write(0, "ABCDEFGHIJKLMNO0123456789");
	flash_sector_read(0, buff);

	int i;
	uart_print("flash read:\r\n");
	for (i = 0; i < 32; ++i) {
		uart_hexb(buff[i]);
		uart_print("\r\n");
	}
	uart_print("\r\n");
	while (1);
}
