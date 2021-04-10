#include "resets.h"
#include "gpio.h"
#include "uart.h"
#include "flash.h"

static char rbuff[4096];
static char wbuff[4096];


void init() {
	int i;
	IO_WR(CLOCKS_BASE + 0x48, 0x880); 		// Enable clk_peri
	reset_release_wait(RESET_IO_BANK0);
	reset_release_wait(RESET_PADS_BANK0);
	reset_release_wait(RESET_UART0);

	uart_init(0);
	gpio_init(0, GPIO_FUNC_UART);
	gpio_init(1, GPIO_FUNC_UART);
	gpio_dir(0, 1);

	for (i = 0; i < 16; ++i) {
		wbuff[i] = 'a' + i;
	}

	flash_init();

	uart_print("FLASH write\r\n");
	flash_sector_write(0, wbuff);

	uart_print("FLASH read\r\n");
	flash_sector_read(0, rbuff);

	uart_print("FLASH print:\r\n");
	for (i = 0; i < 32; ++i) {
		uart_hexb(rbuff[i]);
		uart_print("\r\n");
	}

	uart_print("\r\n");
	while (1);
}
