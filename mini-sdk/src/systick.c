#include "systick.h"

struct systick_hw {
	uint csr;
	uint rvr;
	uint cvr;
	uint calib;
};

#define systick 	((volatile struct systick_hw*)(PPB_BASE + 0xE010))

#define CSR_COUNTFLAG 	(1 << 16)
#define CSR_CLKSRC 		(1 << 2)
#define CSR_TICKINT 	(1 << 1)
#define CSR_ENABLE 		(1 << 0)


void systick_init() {
	systick->csr = CSR_ENABLE | CSR_CLKSRC | CSR_TICKINT;
}

void systick_set(uint value) {
	systick->rvr = value;
	systick->cvr = value;
}

uint systick_get() {
	return systick->cvr;
}

void systick_int(uint enable) {
	if (enable) {
		systick->csr |= CSR_TICKINT;
	} else {
		systick->csr &= ~(CSR_TICKINT);
	}
}
