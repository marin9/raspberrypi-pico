#include "spi.h"

struct spi_hw {
	uint cr0;
	uint cr1;
	uint dr;
	uint sr;
	uint cpsr;
	uint imsc;
	uint ris;
	uint mis;
	uint icr;
};

#define spi0 	((volatile struct spi_hw*)SPI0_BASE);

#define CR0_FRF		(0 << 4)
#define CR0_DSS		0xf
