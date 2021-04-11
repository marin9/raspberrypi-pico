#include "flash.h"
#include "resets.h"

#define CMD_WRITE	0x02
#define CMD_READ	0x03
#define CMD_RDSR	0x05
#define CMD_WREN	0x06
#define CMD_ERASE	0x20

#define PAGE_SIZE	256
#define SECTOR_SIZE	4096

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

static void flash_write_enable() {
	char cmd = CMD_WREN;

	while (flash_busy());

	SSI_START
	ssi_read_write(&cmd, 1);
	SSI_END
}

static void flash_page_write(uint addr, char *d) {
	char cmd_wr[4];
	cmd_wr[0] = CMD_WRITE;
	cmd_wr[1] = (addr >> 16) & 0xff;
	cmd_wr[2] = (addr >> 8) & 0xff;
	cmd_wr[3] = (addr >> 0) & 0xff;

	flash_write_enable();
	while (flash_busy());

	SSI_START
	ssi_read_write(cmd_wr, 4);
	ssi_read_write(d, PAGE_SIZE);
	SSI_END
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
	char cmd_rd[4];
	cmd_rd[0] = CMD_READ;
	cmd_rd[1] = (addr >> 16) & 0xff;
	cmd_rd[2] = (addr >> 8) & 0xff;
	cmd_rd[3] = (addr >> 0) & 0xff;

	while (flash_busy());

	SSI_START
	ssi_read_write(cmd_rd, 4);
	ssi_read_write(d, SECTOR_SIZE);
	SSI_END
}

void flash_sector_write(uint addr, char *d) {
	uint i;
	uint offset = 0;

	flash_sector_erase(addr);
	for (i = 0; i < 16; ++i) {
		flash_page_write(addr + offset, d + offset);
		offset += PAGE_SIZE;
	}
}

void flash_sector_erase(uint addr) {
	char cmd_wr[4];
	cmd_wr[0] = CMD_ERASE;
	cmd_wr[1] = (addr >> 16) & 0xff;
	cmd_wr[2] = (addr >> 8) & 0xff;
	cmd_wr[3] = (addr >> 0) & 0xff;

	flash_write_enable();
	while (flash_busy());

	SSI_START
	ssi_read_write(cmd_wr, 4);
	SSI_END
}

uint flash_busy() {
	char cmd[2];
	cmd[0] = CMD_RDSR;

	SSI_START
	ssi_read_write(cmd, 2);
	SSI_END

	return cmd[1] & 1;
}
