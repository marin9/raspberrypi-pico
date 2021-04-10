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
	IO_WR(CLOCKS_BASE+0x48, 0x880); 		// Enable clk_peri
	reset_release_wait(RESET_IO_BANK0);
	reset_release_wait(RESET_IO_QSPI);
	reset_release_wait(RESET_PADS_BANK0);
	reset_release_wait(RESET_PADS_QSPI);
	reset_release_wait(RESET_UART0);

	uart_init(0);
	gpio_init(0, GPIO_FUNC_UART);
	gpio_init(1, GPIO_FUNC_UART);
	gpio_dir(0, 1);

	flash_init();
	uart_print("Write:\r\n");
	flash_sector_write(0, "ABCDEFGHIJKLMN");
	uart_print("\r\nRead:\r\n");
	delay(100000);
	flash_sector_read(0, buff);

	int i;
	for (i = 0; i < 32; ++i) {
		uart_hexb(buff[i]);
		uart_print("\r\n");
	}

	uart_print("\r\n\r\n");
	while (1);
}
