#include "xosc.h"

struct xosc_hw {
	uint ctrl;
	uint status;
	uint dormant;
	uint startup;
	uint count;
};

#define xosc 	((volatile struct xosc_hw*)XOSC_BASE)

#define CTRL_ENABLE 			(0xFAB << 12)
#define CTRL_DISABLE			(0xD1E << 12)
#define CTRL_FREQ_1_15_MHZ		0xAA0

#define STATUS_STABLE			(1 << 31)
#define STATUS_BADWRITE 		(1 << 24)
#define STATUS_ENABLED			(1 << 12)
#define STATUS_FREQ_1_15_MHZ	(0 << 0)

#define DORMANT_WAKE			0x77616B65
#define DORMANT_DORMANT			0x636F6D61


void xosc_init() {
	xosc->ctrl = CTRL_FREQ_1_15_MHZ;
	xosc->startup = (((12 * 1000000)/1000)+128)/256;
	xosc->ctrl |= CTRL_ENABLE;
	while (!(xosc->status & STATUS_STABLE));
}

void xosc_disable() {
	uint tmp = xosc->ctrl;
	tmp &= (0xFFF << 12);
	tmp |= CTRL_DISABLE;
	xosc->ctrl = tmp;
	while (xosc->status & STATUS_STABLE);
}

void xosc_dormant() {
	xosc->dormant = DORMANT_DORMANT;
	while (!(xosc->status & STATUS_STABLE));
}
