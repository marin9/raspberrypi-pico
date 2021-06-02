#include "rp2040.h"

#define CPUID 			((volatile uint*)(SIO_BASE + 0x000))

#define GPIO_IN 		((volatile uint*)(SIO_BASE + 0x004))
#define GPIO_HI_IN 		((volatile uint*)(SIO_BASE + 0x008))
#define GPIO_OUT 		((volatile uint*)(SIO_BASE + 0x010))
#define GPIO_OUT_SET 	((volatile uint*)(SIO_BASE + 0x014))
#define GPIO_OUT_CLR 	((volatile uint*)(SIO_BASE + 0x018))
#define GPIO_OUT_XOR 	((volatile uint*)(SIO_BASE + 0x01C))
#define GPIO_OE 		((volatile uint*)(SIO_BASE + 0x020))
#define GPIO_OE_SET 	((volatile uint*)(SIO_BASE + 0x024))
#define GPIO_OE_CLR 	((volatile uint*)(SIO_BASE + 0x028))
#define GPIO_OE_XOR 	((volatile uint*)(SIO_BASE + 0x02C))
#define GPIO_HI_OUT 	((volatile uint*)(SIO_BASE + 0x030))
#define GPIO_HI_OUT_SET ((volatile uint*)(SIO_BASE + 0x034))
#define GPIO_HI_OUT_CLR ((volatile uint*)(SIO_BASE + 0x038))
#define GPIO_HI_OUT_XOR ((volatile uint*)(SIO_BASE + 0x03C))
#define GPIO_HI_OE 		((volatile uint*)(SIO_BASE + 0x040))
#define GPIO_HI_OE_SET 	((volatile uint*)(SIO_BASE + 0x044))
#define GPIO_HI_OE_CLR 	((volatile uint*)(SIO_BASE + 0x048))
#define GPIO_HI_OE_XOR 	((volatile uint*)(SIO_BASE + 0x04C))

#define FIFO_ST 		((volatile uint*)(SIO_BASE + 0x050))
#define FIFO_WR 		((volatile uint*)(SIO_BASE + 0x054))
#define FIFO_RD 		((volatile uint*)(SIO_BASE + 0x058))

#define SPINLOCK_ST 	((volatile uint*)(SIO_BASE + 0x05C)) // 1 = locked

#define DIV_UDIVIDEND	((volatile uint*)(SIO_BASE + 0x060))
#define DIV_UDIVISOR	((volatile uint*)(SIO_BASE + 0x064))
#define DIV_SDIVIDEND	((volatile uint*)(SIO_BASE + 0x068))
#define DIV_SDIVISOR	((volatile uint*)(SIO_BASE + 0x06C))
#define DIV_QUOTIENT	((volatile uint*)(SIO_BASE + 0x070))
#define DIV_REMAINDER	((volatile uint*)(SIO_BASE + 0x074))
#define DIV_CSR			((volatile uint*)(SIO_BASE + 0x078))

#define SPINLOCK_N		((volatile uint*)(SIO_BASE + 0x100)) // 0-31


#define FIFO_ST_ROE		(1 << 3) // RX FIFO was read when empty
#define FIFO_ST_WOF		(1 << 2) // TX FIFO was written when full
#define FIFO_ST_RDY		(1 << 1) // 1 when TX FIFO is not full
#define FIFO_ST_VLD		(1 << 0) // 1 when RX FIFO is not empty

#define DIV_CSR_DIRTY	(1 << 1)
#define DIV_CSR_READY	(1 << 0)


uint cpuid() {
	return *CPUID;
}

uint gpio_in(uint gpio) {
	return *GPIO_IN & (1 << gpio);
}

uint gpio_hi_in(uint gpio) {
	return *GPIO_HI_IN & (1 << gpio);
}

void gpio_out(uint gpio, uint value) {
	if (value)
		*GPIO_OUT_SET = 1 << gpio;
	else
		*GPIO_OUT_CLR = 1 << gpio;
}

void gpio_oe(uint gpio, uint oe) {
	if (oe)
		*GPIO_OE_SET = 1 << gpio;
	else
	 	*GPIO_OE_CLR = 1 << gpio;
}

void gpio_hi_out(uint gpio, uint value) {
	if (value)
		*GPIO_HI_OUT_SET = 1 << gpio;
	else
		*GPIO_HI_OUT_CLR = 1 << gpio;
}

void gpio_hi_oe(uint gpio, uint oe) {
	if (oe)
		*GPIO_HI_OE_SET = 1 << gpio;
	else
	 	*GPIO_HI_OE_CLR = 1 << gpio;
}

int fifo_write(uint value) {
	if (!(*FIFO_ST & FIFO_ST_RDY))
		return -1;

	*FIFO_WR = value;
	return 0;
}

int fifo_read(uint *value) {
	if (!(*FIFO_ST & FIFO_ST_VLD))
		return -1;

	*value = *FIFO_RD;
	return 0;
}

uint spinlock_get(uint n) {
	return *SPINLOCK_ST & (1 << n);
}

uint spinlock_lock(uint n) {
	uint notlocked = *(SPINLOCK_N + 4 * n);
	if (notlocked)
		return 0;
	else
		return -1;
}

void spinlock_unlock(uint n) {
	*(SPINLOCK_N + 4 * n) = 1;
}
