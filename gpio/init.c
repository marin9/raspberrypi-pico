#include "types.h"
#include "gpio.h"

#define ROM_BASE		0x00000000
#define XIP_BASE		0x10000000
#define SRAM_BASE		0x20000000
#define APB_BASE		0x40000000
#define AHB_BASE		0x50000000
#define IOP_BASE		0xd0000000
#define CM0_BASE		0xe0000000


#define RESETS_BASE		0x4000c000
#define IO_BANK_BASE	0x40014000
#define SIO_BASE		0xd0000000


#define WR(reg, val)	*((volatile unsigned int*)(reg)) = (val)
#define RD(reg)			*((volatile unsigned int*)(reg))


void delay(int t) {
	while (t--)
		asm volatile ("nop");
}

void init() {
	// release reset on IO_BANK0
	WR(RESETS_BASE + 0x3000, 1 << 5);
	
	WR(RESETS_BASE + 0x3000, 1 << 8);

	// wait for reset be done
	while (!(RD(RESETS_BASE + 0x08) & (1 << 5)));


	gpio_init(0, GPIO_FUNC_SIO);
	gpio_init(1, GPIO_FUNC_SIO);
	gpio_init(2, GPIO_FUNC_SIO);
	gpio_init(3, GPIO_FUNC_SIO);
	

	while (1) {
		delay(300000);
		gpio_set_pull(0, 0, 0);
		delay(300000);
		gpio_set_pull(0, 1, 0);
		gpio_set_pull(1, 1, 0);
		gpio_set_pull(2, 1, 0);
		gpio_set_pull(3, 1, 0);
	}
	
	gpio_set_dir_all(0x0000000f);
	
	while (1) {
		delay(300000);
		gpio_set_all(0xf);
		delay(300000);
		gpio_set_all(0x0);
	}
}

