#include "clock.h"


void clock_init();
void clock_configure(uint clk, uint src, uint auxsrc, uint src_freq, uint freq);
void clock_stop(uint clk);
uint clock_get_khz();
uint clock_freq_count_khz(uint src);
void clock_resus_enable(void (*callback)());
void clock_gpio_init(uint gpio, uint src, uint div);
void clock_conf_gpin(uint clk, uint gpio, uint src_freq, uint freq);
