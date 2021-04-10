#pragma once
#include "rp2040.h"

void spi_init();
void spi_rw(char *data, uint len);
