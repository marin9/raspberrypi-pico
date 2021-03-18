#pragma once
#include "pico.h"

#define GPIO_FUNC_XIP			0
#define GPIO_FUNC_SPI			1
#define GPIO_FUNC_UART			2
#define GPIO_FUNC_I2C			3
#define GPIO_FUNC_PWM			4
#define GPIO_FUNC_SIO			5
#define GPIO_FUNC_PIO0			6
#define GPIO_FUNC_PIO1			7
#define GPIO_FUNC_CLK			8
#define GPIO_FUNC_USB			9
#define GPIO_FUNC_NULL			0xf

#define GPIO_IRQ_LEVEL_LOW		1
#define GPIO_IRQ_LEVEL_HIGH		2
#define GPIO_IRQ_EDGE_FALL		4
#define GPIO_IRQ_EDGE_RISE		8


void gpio_init(uint gpio, uint fn);
void gpio_set_pull(uint gpio, uint up, uint down);
void gpio_set_dir(uint gpio, uint out);
void gpio_set_dir_all(uint mask);
void gpio_set(uint gpio, uint val);
void gpio_set_all(uint mask);
uint gpio_get(uint gpio);
uint gpio_get_all();

/*
void gpio_set_irq(uint gpio, uint event, uint en, func callback);
void gpio_ack_irq(uint gpio, uint event);
*/
