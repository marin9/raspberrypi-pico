#include "resets.h"
#include "gpio.h"
#include "uart.h"

void delay(int t) {
	while (t--)
		asm volatile ("nop");
}

void init() {
	IO_WR(CLOCKS_BASE+0x48, 0x880); // Enable clk_peri
	reset_release_wait(RESET_IO_BANK0);
	reset_release_wait(RESET_PADS_BANK0);
	reset_release_wait(RESET_IO_QSPI);
	reset_release_wait(RESET_UART0);

	// UART init
	uart_init(0);
	gpio_init(0, GPIO_FUNC_UART);
	gpio_init(1, GPIO_FUNC_UART);
	gpio_dir(0, 1);
	uart_print("UART OK\r\n");
	delay(100000);

	// IO_QSPI <= FUNC_0
	IO_WR(0x40018000+0x04, 0);
	IO_WR(0x40018000+0x0C, 0);
	IO_WR(0x40018000+0x14, 0);
	IO_WR(0x40018000+0x1C, 0);

	// XIP init
	IO_WR(0x18000008, 0);			// SSI disable
	IO_WR(0x18000014, 8);			// Clk divider = 8
	IO_WR(0x18000000, 0x001f0300);	// 32 clk per frame, EEPROM read mode
	IO_WR(0x180000f4, 0x03000218);	// read_cmd = 3, 8 bit instr, addr_len = 24 bit
	IO_WR(0x18000010, 1);			// Slave select
	IO_WR(0x18000008, 1);			// SSI enable

	// Read
	int i;
	for (i = 0; i < 512; i += 4) {
		uart_hex(IO_RD(0x10000000 + i));
	}
	uart_print("\r\n\r\n");
}
