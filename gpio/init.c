#define ROM_BASE		0x00000000
#define XIP_BASE		0x10000000
#define SRAM_BASE		0x20000000
#define APB_BASE		0x40000000
#define AHB_BASE		0x50000000
#define IOP_BASE		0xd0000000
#define CM0_BASE		0xe0000000


#define RESETS_BASE		0x4000c000
#define IO_BANK_BASE		0x40014000
#define SIO_BASE		0xd0000000


#define WR(reg, val)		*((volatile unsigned int*)(reg)) = (val)
#define RD(reg)			*((volatile unsigned int*)(reg))


void delay(int t) {
	while (t--)
		asm volatile ("nop");
}

void init() {
	// release reset on IO_BANK0
	WR(RESETS_BASE + 0x3000, 1 << 5);

	// wait for reset be done
	while (!(RD(RESETS_BASE + 0x08) & (1 << 5)));


}
