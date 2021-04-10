#pragma once
#include "rp2040.h"

void flash_init();
void flash_sector_read(uint addr, char *d);
void flash_sector_write(uint addr, char *d);
