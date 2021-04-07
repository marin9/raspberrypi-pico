#pragma once
#include "rp2040.h"

void systick_init();
void systick_set(uint value);
uint systick_get();
void systick_int(uint enable);
