#pragma once
#include "rp2040.h"

void uart_init(uint id);
uint uart_read(uint id, char *buff, uint len);
uint uart_write(uint id, char *buff, uint len);
void uart_print(char *s);
void uart_hex(uint x);
