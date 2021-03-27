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


#define red(s)		gpio_set(2, (s))
#define yellow(s)	gpio_set(3, (s))
#define green(s)	gpio_set(4, (s))
#define blue(s)		gpio_set(5, (s))

static void leds_init() {
	gpio_init(2, GPIO_FUNC_SIO);
	gpio_init(3, GPIO_FUNC_SIO);
	gpio_init(4, GPIO_FUNC_SIO);
	gpio_init(5, GPIO_FUNC_SIO);
	gpio_set_dir(2, 1);
	gpio_set_dir(3, 1);
	gpio_set_dir(4, 1);
	gpio_set_dir(5, 1);
	yellow(0);
	green(0);
	blue(0);
	red(0);
}

static void buttons_init() {
	gpio_init(6, GPIO_FUNC_SIO);
	gpio_init(7, GPIO_FUNC_SIO);
	gpio_init(8, GPIO_FUNC_SIO);
	gpio_init(9, GPIO_FUNC_SIO);
	gpio_set_dir(6, 0);
	gpio_set_dir(7, 0);
	gpio_set_dir(8, 0);
	gpio_set_dir(9, 0);

	gpio_set_pull(6, 1, 0);
	gpio_set_pull(7, 1, 0);
	gpio_set_pull(8, 1, 0);
	gpio_set_pull(9, 1, 0);
}


void delay(int t) {
	while (t--)
		asm volatile ("nop");
}


void systick() {
	uart_print("sys tick\r\n");
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

//reg_wr(NVIC_ICPR, 1 << 15);
//reg_wr(NVIC_ISER, 1 << 0);

asm volatile("cpsie i");

gpio_init(0, GPIO_FUNC_UART);
gpio_init(1, GPIO_FUNC_UART);



	leds_init();
	buttons_init();
	while(1) {
		red(!gpio_get(6));
		yellow(!gpio_get(7));
		green(!gpio_get(8));
		blue(!gpio_get(9));
	}



	while(1) {
		uart_print(" B\r\n");
		delay(1000000);
	}

}
