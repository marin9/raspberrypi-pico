#define RW		0x0000
#define XOR		0x1000
#define SET		0x2000
#define CLR		0x3000


#define ROM_BASE	0x00000000
#define XIP_BASE	0x10000000
#define SRAM_BASE	0x20000000
#define APB_BASE	0x40000000
#define AHB_BASE	0x50000000
#define IOP_BASE	0xd0000000
#define CM0_BASE	0xe0000000


#define RESETS_BASE	0x4000c000
#define IO_BANK_BASE	0x40014000
#define SIO_BASE	0xd0000000



void delay(int t) {
	while (t--)
		asm volatile ("nop");
}

void init() {
	// release reset on IO_BANK0
	*((volatile unsigned int*)(RESETS_BASE + 0x00+0x3000)) = 1 << 5;


	// wait for reset be done
	while(! (*((volatile unsigned int*)(RESETS_BASE + 0x08+0x0000)) & (1<<5)));


	// output disable
	*((volatile unsigned int*)(SIO_BASE + 0x28)) = 1 << 25;


	// turn off pin 25
	*((volatile unsigned int*)(SIO_BASE + 0x18)) = 1 << 25;


	// set function
	*((volatile unsigned int*)(IO_BANK_BASE + 0xCC+0x0000)) = 5;


	// output enable
	*((volatile unsigned int*)(SIO_BASE + 0x24)) = 1 << 25;


	while(1) {
		*((volatile unsigned int*)(SIO_BASE + 0x14)) = 1 << 25;
		delay(2000000);
		*((volatile unsigned int*)(SIO_BASE + 0x18)) = 1 << 25;
		delay(200000);
	}
}

