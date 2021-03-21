#include "resets.h"
#include "gpio.h"
#include "uart.h"


void delay(int t) {
	while (t--)
		asm volatile ("nop");
}

void tc1();

void init() {

	reset_release_wait(RESET_IO_BANK0);
	reset_release_wait(RESET_PADS_BANK0);
	reset_release_wait(RESET_UART0);

	*((uint*)(CLOCKS_BASE+0x48+0x0000)) = (1<<11)|(4<<5);

	gpio_init(0, GPIO_FUNC_UART);
	gpio_init(1, GPIO_FUNC_UART);




	while(1)
		uart_print("OK\r\n");

	tc0();

}
