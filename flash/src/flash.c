#include "flash.h"
#include "resets.h"

#define CMD_WRITE	0x02
#define CMD_READ	0x03
#define CMD_WREN	0x06
#define CMD_ERASE	0x20


#define SSI_START	IO_WR(0x40018000 + 0x0c, (2 << 8)); // CS = 0
#define SSI_END		IO_WR(0x40018000 + 0x0c, (3 << 8)); // CS = 1

static void ssi_read_write(char *data, uint len) {
	uint i;
	for (i = 0; i < len; ++i) {
		while (!(IO_RD(0x18000028) & (1 << 1)));
		IO_WR(0x18000060, data[i]);

		while (!(IO_RD(0x18000028) & (1 << 2)));
		while (IO_RD(0x18000028) & (1 << 0));

		while (!(IO_RD(0x18000028) & (1 << 3)));
		data[i] = IO_RD(0x18000060);
	}
}


static void delay(int t) {
	while (t--)
		asm volatile ("nop");
}

void flash_init() {
	reset_release_wait(RESET_IO_QSPI);
	reset_release_wait(RESET_PADS_QSPI);

	// IO_QSPI <= FUNC0 (XIP)
	IO_WR(IO_QSPI_BASE + 0x04, 0);
	IO_WR(IO_QSPI_BASE + 0x0C, (3 << 8)); // OUTOVER <= high
	IO_WR(IO_QSPI_BASE + 0x14, 0);
	IO_WR(IO_QSPI_BASE + 0x1C, 0);
	IO_WR(IO_QSPI_BASE + 0x24, (3 << 8)); // OUTOVER <= high
	IO_WR(IO_QSPI_BASE + 0x2C, (3 << 8)); // OUTOVER <= high

	// PADS_QSPI
	IO_WR(PADS_QSPI_BASE + 0x0C, ((1 << 6) | (1 << 2))); // input enable, pulldown

	// SSI init
	IO_WR(0x18000008, 0);
	IO_WR(0x18000014, 8);
	IO_WR(0x18000000, (7 << 16));
	IO_WR(0x180000f4, 0x00000218);
	IO_WR(0x18000010, 1);
	IO_WR(0x18000008, 1);
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
	while (!(IO_RD(0x18000028) & (1 << 2)));
	while (IO_RD(0x18000028) & (1 << 0));

	for (i = 0; i < 4; ++i)
		IO_RD(0x18000060);

	for (i = 0; i < 32; ++i) {
		IO_WR(0x18000060, 0);
		while (!(IO_RD(0x18000028) & (1 << 2)));
		while (IO_RD(0x18000028) & (1 << 0));
		d[i] = IO_RD(0x18000060);
	}
	IO_WR(0x40018000 + 0x0c, (3 << 8)); // cs = 1
}

void flash_sector_write(uint addr, char *d) {
	int i;
	char cmd_wr[4];

	flash_sector_erase(addr);

	// write enable
	IO_WR(0x40018000 + 0x0c, (2 << 8)); //cs = 0
	IO_WR(0x18000060, 0x06);
	while (!(IO_RD(0x18000028) & (1 << 2)));
	while (IO_RD(0x18000028) & (1 << 0));
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
		while (!(IO_RD(0x18000028) & (1 << 2)));
		while (IO_RD(0x18000028) & (1 << 0));
		IO_RD(0x18000060);
	}

	for (i = 0; i < 32; ++i) {
		IO_WR(0x18000060, d[i]);
		while (!(IO_RD(0x18000028) & (1 << 2)));
		while (IO_RD(0x18000028) & (1 << 0));
		IO_RD(0x18000060);
	}
	IO_WR(0x40018000 + 0x0c, (3 << 8)); // cs = 1
	delay(300000);
}

void flash_sector_erase(uint addr) {
	int i;
	char cmd_wr[4];

	// write enable
	IO_WR(0x40018000 + 0x0c, (2 << 8)); //cs = 0
	IO_WR(0x18000060, 0x06);
	while (!(IO_RD(0x18000028) & (1 << 2)));
	while (IO_RD(0x18000028) & (1 << 0));
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
	while (!(IO_RD(0x18000028) & (1 << 2)));
	while (IO_RD(0x18000028) & (1 << 0));
	for (i = 0; i < 4; ++i)
		IO_RD(0x18000060);

	IO_WR(0x40018000 + 0x0c, (3 << 8)); // cs = 1
	delay(500000);
}
