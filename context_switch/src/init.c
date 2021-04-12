#include "resets.h"
#include "gpio.h"
#include "uart.h"
#include "xosc.h"
#include "task.h"

static int n;

static void t0() {
	while (1) {
		uart_print("Task\t0\r\n");
		task_yield();
	}
}

static void t1() {
	while (1) {
		uart_print("Task\t\t1\r\n");
		++n;
		if (n > 100) break;
		task_yield();
	}
}

static void t2(){
	while (1) {
		uart_print("Task\t\t\t2\r\n");
		task_yield();
	}
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

	uart_print("ready\r\n");

	n = 0;
	task_create(t0);
	task_create(t1);
	task_create(t2);

	task_yield();
}
