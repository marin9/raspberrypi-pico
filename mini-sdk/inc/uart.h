#pragma once
#include "rp2040.h"

void uart_init(uint id, uint baudrate);
uint uart_read(uint id, char *buff, uint len);
uint uart_write(uint id, char *buff, uint len);
void uart_intr_enable(uint id, uint rx, uint tx);
void uart_flush(uint id);
void uart_deinit(uint id);
