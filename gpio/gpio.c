#define SIO_BASE		0xd0000000
#define GPIO_IN			(SIO_BASE + 0x04)
#define GPIO_OUT		(SIO_BASE + 0x10)
#define GPIO_OUT_SET	(SIO_BASE + 0x14)
#define GPIO_OUT_CLR	(SIO_BASE + 0x18)
#define GPIO_OUT_XOR	(SIO_BASE + 0x1C)
#define GPIO_OE			(SIO_BASE + 0x20)
#define GPIO_OE_SET		(SIO_BASE + 0x24)
#define GPIO_OE_CLR		(SIO_BASE + 0x28)
#define GPIO_OE_XOR		(SIO_BASE + 0x2C)



#define APB_BASE		0x40000000
#define IO_BANK_BASE	(APB_BASE + 0x14000)
#define PADS_BANK0_BASE	(APB_BASE + 0x1C000)



#define IO_FUNC_SPI		1
#define IO_FUNC_UART	2
#define IO_FUNC_I2C		3
#define IO_FUNC_PWM		4
#define IO_FUNC_SIO		5
#define IO_FUNC_PIO0	6
#define IO_FUNC_PIO1	7
#define IO_FUNC_CLK		8
#define IO_FUNC_USB		9


void gpio_set_func(uint gpio_n, uint func) {


}

void gpio_set_dir(uint n, uint d) {


}

void gpio_write(uint n, uint v) {


}

uint gpio_read(uint gpio_n) {
	return 0;
}

void gpio_attach_intr(uint n, uint m) {


}

