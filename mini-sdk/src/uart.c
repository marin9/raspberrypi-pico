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

#define DR_OE		(1 << 11)
#define DR_BE		(1 << 10)
#define DR_PE		(1 << 9)
#define DR_FE		(1 << 8)
#define DR_DATA		(0xFF)

#define RSR_OE		(1 << 3)
#define RSR_BE		(1 << 2)
#define RSR_PE		(1 << 1)
#define RSR_FE		(1 << 0)

#define FR_RI		(1 << 8)
#define FR_TXFE		(1 << 7)
#define FR_RXFF		(1 << 6)
#define FR_TXFF		(1 << 5)
#define FR_RXFE		(1 << 4)
#define FR_BUSY		(1 << 3)
#define FR_DCD		(1 << 2)
#define FR_DSR		(1 << 1)
#define FR_CTS		(1 << 0)

#define LCR_SPS		(1 << 7)
#define LCR_WLEN_5	(0 << 5)
#define LCR_WLEN_6	(1 << 5)
#define LCR_WLEN_7	(2 << 5)
#define LCR_WLEN_8	(3 << 5)
#define LCR_FEN		(1 << 4)
#define LCR_STP2	(1 << 3)
#define LCR_EPS		(1 << 2)
#define LCR_PEN		(1 << 1)
#define LCR_BRK		(1 << 0)

#define CR_CTSEN	(1 << 15)
#define CR_RTSEN	(1 << 14)
#define CR_OUT2		(1 << 13)
#define CR_OUT1		(1 << 12)
#define CR_RTS		(1 << 11)
#define CR_DTR		(1 << 10)
#define CR_RXE		(1 << 9)
#define CR_TXE		(1 << 8)
#define CR_LBE		(1 << 7)
#define CR_SIRLP	(1 << 2)
#define CR_SIREN	(1 << 1)
#define CR_UARTEN	(1 << 0)

#define IFLS_RXIFSEL	(7 << 3)
#define IFLS_TXIFSEL	(7 << 0)

#define IMSC_OE		(1 << 10)
#define IMSC_BE		(1 << 9)
#define IMSC_PE		(1 << 8)
#define IMSC_FE		(1 << 7)
#define IMSC_RT		(1 << 6)
#define IMSC_TX		(1 << 5)
#define IMSC_RX		(1 << 4)
#define IMSC_DSR	(1 << 3)
#define IMSC_DCD	(1 << 2)
#define IMSC_CTS	(1 << 1)
#define IMSC_RIM	(1 << 0)

// RIS, MIS, ICR


void uart_init(uint id, uint baudrate) {
	volatile struct uart_hw *uart;

	if (id == 0)
		uart = uart0;
	else
		uart = uart1;

	(void)baudrate;

	uart->cr = 0;
	uart->ibrd = 6;
	uart->fbrd = 33;
	uart->lcr_h = LCR_WLEN_8 | LCR_FEN;
	uart->imsc = 0;
	uart->icr = 0xFFFFFFFF;
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
		if (uart->fr & FR_RXFE)
			break;

		buff[i] = uart->dr & DR_DATA;
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
		while (uart->fr & FR_TXFF)
			asm volatile ("nop");

		uart->dr = buff[i];
	}
	return i;
}

void uart_intr_enable(uint id, uint rx, uint tx) {
	volatile struct uart_hw *uart;

	if (id == 0)
		uart = uart0;
	else
		uart = uart1;

	uart->icr = 0xFFFFFFFF;

	if (rx)
		uart->imsc |= IMSC_RT;
	else
		uart->imsc &= ~(IMSC_RT);

	if (tx)
		uart->imsc |= IMSC_TX;
	else
		uart->imsc &= ~(IMSC_TX);
}

void uart_flush(uint id) {
	volatile struct uart_hw *uart;

	if (id == 0)
		uart = uart0;
	else
		uart = uart1;

	while (!(uart->fr & FR_TXFE))
		asm volatile ("nop");
}

void uart_deinit(uint id) {
	volatile struct uart_hw *uart;

	if (id == 0)
		uart = uart0;
	else
		uart = uart1;

	uart->cr = 0;
	uart->imsc = 0;
}
