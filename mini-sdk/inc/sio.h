#pragma once

uint cpuid();

uint gpio_in(uint gpio);
uint gpio_hi_in(uint gpio);
void gpio_out(uint gpio, uint value);
void gpio_oe(uint gpio, uint oe);
void gpio_hi_out(uint gpio, uint value);
void gpio_hi_oe(uint gpio, uint oe);

int fifo_write(uint value);
int fifo_read(uint *value);

uint spinlock_get(uint n);
uint spinlock_lock(uint n);
void spinlock_unlock(uint n);
