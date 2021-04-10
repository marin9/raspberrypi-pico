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

#define spi0 	((volatile struct spi_hw*)SPI0_BASE)


#define CR0_DSS		0x7			// 8 bit data

#define CR1_SOD		(1 << 3)
#define CR1_MS		(1 << 2)
#define CR1_SSE		(1 << 1)
#define CR1_LBM		(1 << 0)

#define SR_BSY		(1 << 4)
#define SR_RFF		(1 << 3)
#define SR_RNE		(1 << 2)
#define SR_TNF		(1 << 1)
#define SR_TFE		(1 << 0)

#define IMSC_TX		(1 << 3)
#define IMSC_RX		(1 << 2)
#define IMSC_RT		(1 << 1)
#define IMSC_ROR	(1 << 0)


void spi_init() {
	spi0->cr0 = CR0_DSS;
	spi0->cpsr = 32;
	spi0->cr1 = CR1_SSE;
}

void spi_rw(char *data, uint len) {
	uint i;
	for (i = 0; i < len; ++i) {
		while (!(spi0->sr & SR_TNF));

		spi0->dr = data[i];

		while (spi0->sr & SR_BSY);

		if (spi0->sr & SR_RNE)
			data[i] = spi0->dr;
	}

}
