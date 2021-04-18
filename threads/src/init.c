#include "resets.h"
#include "gpio.h"
#include "xosc.h"
#include "uart.h"
#include "thread.h"


void t1() {
	while (1) {
		uart_print("T1\r\n");
		thread_sleep(100);
	}
}

void t2() {
	while (1) {
		uart_print("T 2\r\n");
		thread_sleep(1000);
	}
}

void t3() {
	while (1) {
		uart_print("T  3\r\n");
		thread_sleep(2000);
	}
}

void init() {
	xosc_init();
	IO_WR(CLOCKS_BASE + 0x48, 0x880); // clk_peri enable
	reset_release_wait(RESET_IO_BANK0);
	reset_release_wait(RESET_PADS_BANK0);
	reset_release_wait(RESET_UART0);
	uart_init(0);
	gpio_init(0, GPIO_FUNC_UART);
	gpio_init(1, GPIO_FUNC_UART);
	gpio_dir(0, 1);

	rtos_init();

	thread_start(t1, 0);
	thread_start(t2, 0);
	thread_start(t3, 0);

	uart_print("start os\r\n");
	rtos_start();
	uart_print("os started\r\n");
}
