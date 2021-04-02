#include "resets.h"
#include "gpio.h"
#include "uart.h"

#define SYS_CSR    (PPB_BASE + 0xE010)
#define SYS_RVR    (PPB_BASE + 0xE014)
#define SYS_CVR    (PPB_BASE + 0xE018)
#define SYS_CALIB  (PPB_BASE + 0xE01C)
#define NVIC_ISER   (PPB_BASE + 0xE100)
#define NVIC_ICER   (PPB_BASE + 0xE180)
#define NVIC_ISPR   (PPB_BASE + 0xE200)
#define NVIC_ICPR   (PPB_BASE + 0xE280)


void delay(int t) {
	while (t--)
		asm volatile ("nop");
}


void systick() {
	uart_print("M\r\n");
	reg_rd(SYS_CSR);
	//reg_wr(NVIC_ICPR, 1 << 15);
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

reg_wr(SYS_CSR, 4);
reg_wr(SYS_RVR, 12000000-1);
reg_wr(SYS_CVR, 12000000-1);
reg_wr(SYS_CSR, 7);

reg_wr(NVIC_ISER, 1 << 13);

asm volatile("cpsie i");

gpio_init(0, GPIO_FUNC_UART);
gpio_init(1, GPIO_FUNC_UART);



reg_wr(IO_BANK0_BASE+0x100, 1<<27);



	gpio_init(18, GPIO_FUNC_SIO);
	gpio_init(19, GPIO_FUNC_SIO);
	gpio_init(20, GPIO_FUNC_SIO);
	gpio_set_dir(18, 1);
	gpio_set_dir(19, 1);
	gpio_set_dir(20, 1);

	while(1){
		gpio_set(18, 0);
		gpio_set(19, 1);
		gpio_set(20, 1);
		delay(1000000);
		gpio_set(18, 1);
		gpio_set(19, 0);
		gpio_set(20, 1);
		delay(1000000);
		gpio_set(18, 1);
		gpio_set(19, 1);
		gpio_set(20, 0);
		delay(1000000);
	}
}
