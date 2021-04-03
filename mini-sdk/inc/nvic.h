#pragma once
#include "rp2040.h"

void nvic_enable(uint irq);
void nvic_disable(uint irq);
void nvic_setpending(uint irq);
void nvic_clearpending(uint irq);
