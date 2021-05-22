#include "uart.h"
#include "gpio.h"
#include "resets.h"

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

#define uart ((volatile struct uart_hw*)UART0_BASE)

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


void uart_init() {
	IO_WR(CLOCKS_BASE + 0x48, 0x880); // clk_peri enable
	IO_WR(CLOCKS_BASE + 0x30, 0x2);
	reset_release_wait(RESET_IO_BANK0);
	reset_release_wait(RESET_PADS_BANK0);
	reset_release_wait(RESET_UART0);

	uart->cr = 0;
	uart->ibrd = 6; // 115200
	uart->fbrd = 33;
	uart->lcr_h = LCR_WLEN_8 | LCR_FEN;
	uart->cr = CR_TXE | CR_RXE | CR_UARTEN;

	gpio_init(0, GPIO_FUNC_UART);
	gpio_init(1, GPIO_FUNC_UART);
	gpio_dir(0, 1);
}

uint uart_read(char *buff, uint len) {
	uint i;
	for (i = 0; i < len; ++i) {
		while (uart->fr & FR_RXFE);
		buff[i] = uart->dr & 0xFF;
	}
	return i;
}

uint uart_write(char *buff, uint len) {
	uint i;
	for (i = 0; i < len; ++i) {
		while (uart->fr & FR_TXFF);

		uart->dr = buff[i];
	}
	return i;
}

static void hex2str(char *str, int n) {
	int i, hb;
	for (i = 0; i < 8; ++i) {
		hb = n >> (7 - i) * 4;
		hb &= 0x0F;

		if (hb > 9)
			str[i] = (char)(hb + 'A' - 10);
		else
			str[i] = (char)(hb + '0');
	}
	str[8] = 0;
}

void uart_print(char *s) {
	while (*s) {
		uart_write(s, 1);
		++s;
	}
}

void uart_hex(uint x) {
	char str[8 + 1];
	hex2str(str, x);
	uart_print(str);
}
