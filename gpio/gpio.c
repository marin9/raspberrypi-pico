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


#define GPIO_FUNC_XIP		0
#define GPIO_FUNC_SPI		1
#define GPIO_FUNC_UART	2
#define GPIO_FUNC_I2C		3
#define GPIO_FUNC_PWM		4
#define GPIO_FUNC_SIO		5
#define GPIO_FUNC_PIO0	6
#define GPIO_FUNC_PIO1	7
#define GPIO_FUNC_CLK		8
#define GPIO_FUNC_USB		9
#define GPIO_FUNC_NULL		0xf

#define GPIO_IRQ_LEVEL_LOW	1
#define GPIO_IRQ_LEVEL_HIGH	2
#define GPIO_IRQ_EDGE_FALL	4
#define GPIO_IRQ_EDGE_RISE	8



void gpio_set_func(uint gpio, uint fn) {


}

void gpio_set_pull(uint gpio, uint up, uint down) {

}

void gpio_set_irq(uint gpio, uint event, uint en, func callback) {

}

void gpio_ack_irq(uint gpio, uint event) {

}

void gpio_init(uint gpio, uint dir) {

}

void gpio_set_dir(uint n, uint out) {


}

void gpio_set(uint n, uint v) {


}

uint gpio_get(uint gpio_n) {
	return 0;
}

uint gpio_get_all() {

}

uint gpio_set_all(uint mask) {

}

void gpio_set_dir_all(uint mask) {

}


