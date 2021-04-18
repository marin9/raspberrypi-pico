#include "xosc.h"
#include "gpio.h"
#include "uart.h"
#include "nvic.h"
#include "thread.h"
#include "systick.h"

// -------------------------------------

static sem_t sem1;

static void thread_x(void *args){
	int i;
	while (1) {
		sem_wait(&sem1);
		for (i = 0; i < 5; ++i) {
			uart_print((char*)args);
			thread_sleep(10);
		}
		sem_signal(&sem1);
		thread_sleep(10);
	}
}

static void test_sem() {
	sem_init(&sem1, 1);

	thread_start(thread_x, "T 0\r\n");
	thread_start(thread_x, "T  1\r\n");
	thread_start(thread_x, "T   2\r\n");
	thread_start(thread_x, "T    3\r\n");
	thread_start(thread_x, "T     4\r\n");
}

// -------------------------------------

void t1() {
	while (1) {
		uart_print("T1\r\n");
		thread_sleep(0);
	}
}

void t2() {
	while (1) {
		uart_print("T 2\r\n");
		thread_sleep(0);
	}
}

void t3() {
	while (1) {
		uart_print("T  3\r\n");
		thread_sleep(0);
	}
}

// -------------------------------------

void test_threads() {
	thread_start(t1, 0);
	thread_start(t2, 0);
	thread_start(t3, 0);
}


void tm() {
	while (1) {
		uart_hex(rtos_ticks());
		uart_print("\r\n");
		thread_sleep(0);
		uart_hex(rtos_ticks());
		uart_print(".\r\n");

	}
}

void test_time() {
	thread_start(tm, 0);
}

// -------------------------------------

void init() {
	xosc_init();
	uart_init();
	nvic_init();
	systick_init();

	rtos_init();

	//test_threads();
	test_time();
	//test_sem();

	rtos_start();
}
