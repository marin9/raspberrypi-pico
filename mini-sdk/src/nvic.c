#include "nvic.h"

#define NVIC_ISER   (PPB_BASE + 0xE100)
#define NVIC_ICER   (PPB_BASE + 0xE180)
#define NVIC_ISPR   (PPB_BASE + 0xE200)
#define NVIC_ICPR   (PPB_BASE + 0xE280)


void nvic_enable(uint irq) {
	*((volatile uint*)(NVIC_ISER)) = 1 << irq;
}

void nvic_disable(uint irq) {
	*((volatile uint*)(NVIC_ICER)) = 1 << irq;
}

void nvic_setpending(uint irq) {
	*((volatile uint*)(NVIC_ISPR)) = 1 << irq;
}

void nvic_clearpending(uint irq) {
	*((volatile uint*)(NVIC_ICPR)) = 1 << irq;	
}
