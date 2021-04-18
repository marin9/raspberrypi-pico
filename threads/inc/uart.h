#pragma once
#include "rp2040.h"

void uart_init();
uint uart_read(char *buff, uint len);
uint uart_write(char *buff, uint len);
void uart_print(char *s);
void uart_hex(uint x);
