#include "flash.h"

static void delay(int t) {
	while (t--)
		asm volatile ("nop");
}

void flash_init() {
	// IO_QSPI <= FUNC0 (XIP)
	IO_WR(IO_QSPI_BASE + 0x04, 0);
	IO_WR(IO_QSPI_BASE + 0x0C, (3 << 8)); // OUTOVER <= high
	IO_WR(IO_QSPI_BASE + 0x14, 0);
	IO_WR(IO_QSPI_BASE + 0x1C, 0);
	IO_WR(IO_QSPI_BASE + 0x24, (3 << 8)); // OUTOVER <= high
	IO_WR(IO_QSPI_BASE + 0x2C, (3 << 8)); // OUTOVER <= high

	// PADS_QSPI
	IO_WR(PADS_QSPI_BASE + 0x08, (3 << 4)); // 12 mA
	IO_WR(PADS_QSPI_BASE + 0x0C, ((1 << 6) | (1 << 2))); // input enable, pulldown
	delay(50000);

	// SSI init
	IO_WR(0x18000008, 0);
	IO_WR(0x18000014, 8);
	IO_WR(0x18000000, (7 << 16));
	IO_WR(0x180000f4, 0x00000218);
	IO_WR(0x18000004, 0);
	IO_WR(0x18000010, 1);
	IO_WR(0x18000008, 1);
	delay(500000);
}

void flash_sector_read(uint addr, char *d) {
	int i;
	char cmd_rd[4];

	cmd_rd[0] = 0x03;
	cmd_rd[1] = (addr >> 16) & 0xff;
	cmd_rd[2] = (addr >> 8) & 0xff;
	cmd_rd[3] = (addr >> 0) & 0xff;

	IO_WR(0x40018000 + 0x0c, (2 << 8)); //cs = 0

	for (i = 0; i < 4; ++i) {
		IO_WR(0x18000060, cmd_rd[i]);
	}
	delay(10000);

	for (i = 0; i < 4; ++i)
		IO_RD(0x18000060);

	for (i = 0; i < 32; ++i) {
		IO_WR(0x18000060, 0);
		delay(10000);
		d[i] = IO_RD(0x18000060);
	}

	IO_WR(0x40018000 + 0x0c, (3 << 8)); // cs = 1
}

void flash_sector_write(uint addr, char *d) {
	int i;
	char cmd_wr[4];

	// write enable
	IO_WR(0x40018000 + 0x0c, (2 << 8)); //cs = 0
	IO_WR(0x18000060, 0x06);
	delay(10000);
	IO_RD(0x18000060);
	IO_WR(0x40018000 + 0x0c, (3 << 8)); // cs = 1
	delay(30000);

	// erase
	cmd_wr[0] = 0x20;
	cmd_wr[1] = (addr >> 16) & 0xff;
	cmd_wr[2] = (addr >> 8) & 0xff;
	cmd_wr[3] = (addr >> 0) & 0xff;
	IO_WR(0x40018000 + 0x0c, (2 << 8)); //cs = 0
	for (i = 0; i < 4; ++i) {
		IO_WR(0x18000060, cmd_wr[i]);
	}
	delay(10000);
	for (i = 0; i < 4; ++i)
		IO_RD(0x18000060);
	IO_WR(0x40018000 + 0x0c, (3 << 8)); // cs = 1
	delay(500000);

	// write enable
	IO_WR(0x40018000 + 0x0c, (2 << 8)); //cs = 0
	IO_WR(0x18000060, 0x06);
	delay(10000);
	IO_RD(0x18000060);
	IO_WR(0x40018000 + 0x0c, (3 << 8)); // cs = 1
	delay(10000);

	// write
	cmd_wr[0] = 0x02;
	cmd_wr[1] = (addr >> 16) & 0xff;
	cmd_wr[2] = (addr >> 8) & 0xff;
	cmd_wr[3] = (addr >> 0) & 0xff;
	IO_WR(0x40018000 + 0x0c, (2 << 8)); //cs = 0
	for (i = 0; i < 4; ++i) {
		IO_WR(0x18000060, cmd_wr[i]);
		delay(10000);
		IO_RD(0x18000060);
	}

	for (i = 0; i < 32; ++i) {
		IO_WR(0x18000060, d[i]);
		delay(10000);
		IO_RD(0x18000060);
	}
	IO_WR(0x40018000 + 0x0c, (3 << 8)); // cs = 1
	delay(300000);
}
