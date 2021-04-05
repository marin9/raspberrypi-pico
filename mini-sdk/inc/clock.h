#pragma once
#include "rp2040.h"

#define CLK_GPOUT0		0
#define CLK_GPOUT1		1
#define CLK_GPOUT2		2
#define CLK_GPOUT3		3
#define CLK_REF			4
#define CLK_SYS			5
#define CLK_PERI		6
#define CLK_USB			7
#define CLK_ADC			8
#define CLK_RTC			9
#define CLK_COUNT		10


void clock_init();
void clock_configure(uint clk, uint src, uint auxsrc, uint src_freq, uint freq);
void clock_stop(uint clk);
uint clock_get_khz();
uint clock_freq_count_khz(uint src);
void clock_resus_enable(void (*callback)());
void clock_gpio_init(uint gpio, uint src, uint div);
void clock_conf_gpin(uint clk, uint gpio, uint src_freq, uint freq);
