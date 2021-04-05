#include "uart.h"

struct uart {
	uint dr;
	uint rsr;
	uint unused1[4];
	uint fr;
	uint unuded2;
	uint ilpr;
	uint ibrd;
	uint fbrd;
	uint lcr_h;
	uint cr;
};

#define uart0 ((volatile struct uart*)UART0_BASE)



void uart_init() {
	uart0->ibrd = 6;
	uart0->fbrd = 33;
	uart0->lcr_h = 0x70;
	uart0->cr = (1<<9) | (1<<8) | (1<<0);
}

void uart_print(char *s) {
    while (*s) {
		while (1)
			if (((uart0->fr) & (1<<5))==0)
				break;

		uart0->dr = *s;
        ++s;
    }
}

void uart_hex(uint x) {
	uint i, tmp;
	char buff[8 + 1];

	buff[8] = 0;
	for (i = 0; i < 8; ++i) {
		tmp = x & 0xF;
		buff[7 - i] = tmp < 10 ? tmp + '0' : tmp - 10 + 'A';
		x = x >> 4;
	}
	uart_print(buff);
}
