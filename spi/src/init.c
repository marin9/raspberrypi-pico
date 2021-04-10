#include "resets.h"
#include "gpio.h"
#include "uart.h"
#include "spi.h"


void delay(int t) {
	while (t--)
		asm volatile ("nop");
}

static char buff[256];

void write() {
	buff[0] = 0x06;
	gpio_set(26, 0);
	delay(10000);
	spi_rw(buff, 1);
	delay(10000);
	gpio_set(26, 1);
	delay(100000);

	buff[0] = 0x02;
	buff[1] = 0x00;
	buff[2] = 0x00;
	buff[3] = 0x00;
	buff[4] = 0x11;
	buff[5] = 0x22;
	buff[6] = 0x33;
	buff[7] = 0x44;
	gpio_set(26, 0);
	delay(10000);
	spi_rw(buff, 8);
	delay(10000);
	gpio_set(26, 1);
	delay(100000);
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

	spi_init();
	gpio_init(4, GPIO_FUNC_SPI);
	gpio_init(5, GPIO_FUNC_SPI);
	gpio_init(6, GPIO_FUNC_SPI);
	gpio_init(7, GPIO_FUNC_SPI);
	gpio_dir(6, 1);
	gpio_dir(7, 1);

	gpio_init(26, GPIO_FUNC_SIO);
	gpio_dir(26, 1);
	gpio_set(26, 1);

	//write();


	buff[0] = 0x03;
	buff[1] = 0x00;
	buff[2] = 0x00;
	buff[3] = 0x00;

	gpio_set(26, 0);
	delay(10000);
	spi_rw(buff, 128);
	delay(10000);
	gpio_set(26, 1);

	uart_print("SPI:\r\n");
	int i;
	for (i = 4; i < 128; ++i)
		uart_hex(buff[i]);

	uart_print("\r\n\r\n");
	while (1);
}
