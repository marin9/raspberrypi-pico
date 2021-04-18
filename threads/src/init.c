#include "xosc.h"
#include "gpio.h"
#include "uart.h"
#include "nvic.h"
#include "thread.h"
#include "systick.h"


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
	uart_init();
	nvic_init();
	systick_init();

	rtos_init();

	thread_start(t1, 0);
	thread_start(t2, 0);
	thread_start(t3, 0);

	rtos_start();
}
