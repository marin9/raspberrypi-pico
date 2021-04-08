#pragma once
#include "rp2040.h"

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


void gpio_init(uint gpio, uint func);
void gpio_dir(uint gpio, uint out);
void gpio_pullup(uint gpio, uint enable);
void gpio_pulldown(uint gpio, uint enable);
void gpio_set(uint gpio, uint value);
uint gpio_get(uint gpio);
