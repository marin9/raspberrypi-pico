#include "resets.h"
#include "gpio.h"
#include "uart.h"
#include "nvic.h"
#include "xosc.h"
#include "lib.h"
#include "systick.h"


void delay(int t) {
	while (t--)
		asm volatile ("nop");
}

uint psr() {
	asm volatile ("mrs r0, psr");
	asm volatile ("bx lr");
	return 0;
}

uint primask() {
	asm volatile ("mrs r0, primask");
	asm volatile ("bx lr");
	return 0;
}

uint control() {
	asm volatile ("mrs r0, control");
	asm volatile ("bx lr");
	return 0;
}

int count;

void handler() {
	char buff[32];
	memset(buff, 0, 32);
	uart_read(0, buff, 32);
	printf("UART RX: %s\r\n", buff);

	asm volatile ("cpsid i");
	printf("PSR: \t\t%x\r\n", psr());
	printf("PRIMASK: \t%x\r\n", primask());
	printf("CONTROL: \t%x\r\n\r\n", control());
	asm volatile ("cpsie i");

	++count;
	if (count > 2){
		asm volatile ("mov r0, #2");
		asm volatile ("msr control, r0");
	}
}



void init() {
	xosc_init();
	IO_WR(CLOCKS_BASE+0x48, 0x880); // clk_peri enble

	reset_release_wait(RESET_IO_BANK0);
	reset_release_wait(RESET_PADS_BANK0);
	reset_release_wait(RESET_UART0);

	//printf("uart init\r\n");
	uart_init(0, 115200);
	gpio_init(0, GPIO_FUNC_UART);
	gpio_init(1, GPIO_FUNC_UART);
	gpio_dir(0, 1);

	printf("nvic init\r\n");
	nvic_init();
	nvic_register_irq(IRQ_UART0, handler);
	uart_intr_enable(0, 1, 0);
	printf("nvic enable uart0\r\n");
	nvic_enable(IRQ_UART0);

	systick_init();
	systick_set(12000000-1);
	//systick_init(1);

	count = 0;
	while(1){
		printf("PSR: \t\t%x\r\n", psr());
		printf("PRIMASK: \t%x\r\n", primask());
		printf("CONTROL: \t%x\r\n\r\n", control());
		delay(5000000);
	}
}


/*

#define SYS_CSR    (PPB_BASE + 0xE010)
#define SYS_RVR    (PPB_BASE + 0xE014)
#define SYS_CVR    (PPB_BASE + 0xE018)
#define SYS_CALIB  (PPB_BASE + 0xE01C)
#define NVIC_ISER   (PPB_BASE + 0xE100)
#define NVIC_ICER   (PPB_BASE + 0xE180)
#define NVIC_ISPR   (PPB_BASE + 0xE200)
#define NVIC_ICPR   (PPB_BASE + 0xE280)


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

reg_wr(SYS_CSR, 4);
reg_wr(SYS_RVR, 12000000-1);
reg_wr(SYS_CVR, 12000000-1);
reg_wr(SYS_CSR, 7);

reg_wr(NVIC_ISER, 1 << 13);

asm volatile("cpsie i");

gpio_init(0, GPIO_FUNC_UART);
gpio_init(1, GPIO_FUNC_UART);

*/


/*
gpio irq


void irq13() {
	gpio_set(20, 0);
	delay(1000000);
	gpio_set(20, 1);
	gpio_int_ack(7);
}


	gpio_init(18, GPIO_FUNC_SIO);
	gpio_init(19, GPIO_FUNC_SIO);
	gpio_init(20, GPIO_FUNC_SIO);
	gpio_dir(18, 1);
	gpio_dir(19, 1);
	gpio_dir(20, 1);

	gpio_init(0, GPIO_FUNC_SIO);
	gpio_init(1, GPIO_FUNC_SIO);
	gpio_init(2, GPIO_FUNC_SIO);
	gpio_pullup(0, 1);
	gpio_pullup(1, 1);
	gpio_pullup(2, 1);

	gpio_init(7, GPIO_FUNC_SIO);
	gpio_pullup(7, 1);
	delay(10000);
	gpio_int_set(7, 1, GPIO_INT_EDGE_FALL);
	nvic_init();
	nvic_register_irq(13, irq13);
	nvic_enable(13);

	gpio_set(19, 1);
	gpio_set(20, 1);
	*/
