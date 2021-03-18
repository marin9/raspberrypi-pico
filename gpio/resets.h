#pragma once
#include "pico.h"

#define RESET_ADC			0
#define RESET_BUSCTRL		1
#define RESET_DMA			2
#define RESET_I2C0			3
#define RESET_I2C1			4
#define RESET_IO_BANK0		5
#define RESET_IO_QSPI		6
#define RESET_JTAG			7
#define RESET_PADS_BANK0	8
#define RESET_PADS_QSPI		9
#define RESET_PIO0			10
#define RESET_PIO1			11
#define RESET_PLL_SYS		12
#define RESET_PLL_USB		13
#define RESET_PWM			14
#define RESET_RTC			15
#define RESET_SPI0			16
#define RESET_SPI1			17
#define RESET_SYSCFG		18
#define RESET_SYSINFO		19
#define RESET_TBMAN			20
#define RESET_TIMER			21
#define RESET_UART0			22
#define RESET_UART1			23
#define RESET_USBCTRL		24


void reset_block(uint block);
void unreset_block(uint block);
void unreset_block_wait(uint block);
