#include "resets.h"
#include "gpio.h"
#include "uart.h"


void delay(int t) {
	while (t--)
		asm volatile ("nop");
}


void init() {

	reg_wr(CLOCKS_BASE+0x78, 0);

	reg_wr(XOSC_BASE+0x00, 0xaa0);
	reg_wr(XOSC_BASE+0x0c, 47);
	reg_wr(XOSC_BASE+0x00+0x2000, 0xfab000);

	while(1) {
		if (((reg_rd(XOSC_BASE+0x04)) & 0x80000000)!=0){
			break;
		}
	}

	reg_wr(CLOCKS_BASE+0x30, 2);
	reg_wr(CLOCKS_BASE+0x3c, 0);
	reg_wr(CLOCKS_BASE+0x48, 0x880);

	reset_release_wait(RESET_IO_BANK0);
	reset_release_wait(RESET_PADS_BANK0);
	reset_release_wait(RESET_UART0);


	uart_init();

	gpio_init(0, GPIO_FUNC_UART);
	gpio_init(1, GPIO_FUNC_UART);
	gpio_init(25, GPIO_FUNC_SIO);

	gpio_set_dir(25, 1);
	gpio_set(25, 1);

	while(1) {
		uart_print("OK\r\n");
		//delay(10000);
	}

}
