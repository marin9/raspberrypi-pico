#include "resets.h"
#include "gpio.h"
#include "uart.h"
#include "spi.h"


void delay(int t) {
	while (t--)
		asm volatile ("nop");
}

void init() {
	IO_WR(CLOCKS_BASE+0x48, 0x880); 		// Enable clk_peri
	reset_release_wait(RESET_IO_BANK0);
	reset_release_wait(RESET_PADS_BANK0);
	reset_release_wait(RESET_UART0);
	reset_release_wait(RESET_SPI0);

	uart_init(0);
	gpio_init(0, GPIO_FUNC_UART);
	gpio_init(1, GPIO_FUNC_UART);
	gpio_dir(0, 1);


	gpio_init(4, GPIO_FUNC_SPI);
	gpio_init(5, GPIO_FUNC_SPI);
	gpio_init(6, GPIO_FUNC_SPI);
	gpio_init(7, GPIO_FUNC_SPI);

}
