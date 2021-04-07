#include "uart.h"

struct uart_hw {
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
	uint ifls;
	uint imsc;
	uint ris;
	uint mis;
	uint icr;
};

#define uart0 ((volatile struct uart_hw*)UART0_BASE)
#define uart1 ((volatile struct uart_hw*)UART1_BASE)

#define FR_TXFE		(1 << 7)
#define FR_RXFF		(1 << 6)
#define FR_TXFF		(1 << 5)
#define FR_RXFE		(1 << 4)
#define FR_BUSY		(1 << 3)

#define LCR_WLEN_5	(0 << 5)
#define LCR_WLEN_6	(1 << 5)
#define LCR_WLEN_7	(2 << 5)
#define LCR_WLEN_8	(3 << 5)
#define LCR_FEN		(1 << 4)

#define CR_RXE		(1 << 9)
#define CR_TXE		(1 << 8)
#define CR_UARTEN	(1 << 0)


void uart_init(uint id) {
	volatile struct uart_hw *uart;

	if (id == 0)
		uart = uart0;
	else
		uart = uart1;

	uart->cr = 0;
	uart->ibrd = 6; // 115200
	uart->fbrd = 33;
	uart->lcr_h = LCR_WLEN_8 | LCR_FEN;
	uart->cr = CR_TXE | CR_RXE | CR_UARTEN;
}

uint uart_read(uint id, char *buff, uint len) {
	uint i;
	volatile struct uart_hw *uart;

	if (id == 0)
		uart = uart0;
	else
		uart = uart1;

	for (i = 0; i < len; ++i) {
		while (uart->fr & FR_RXFE);
		buff[i] = uart->dr & 0xFF;
	}
	return i;
}

uint uart_write(uint id, char *buff, uint len) {
	uint i;
	volatile struct uart_hw *uart;

	if (id == 0)
		uart = uart0;
	else
		uart = uart1;

	for (i = 0; i < len; ++i) {
		while (uart->fr & FR_TXFF);

		uart->dr = buff[i];
	}
	return i;
}
