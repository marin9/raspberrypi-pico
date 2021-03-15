#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "defs.h"


static uint size, flash, nocrc;
static char *input, *output;
static char data[MAX_PROG_SIZE];


void check_arguments(int argc, char **argv) {
	int c;

	flash = 0;
	input = 0;
	output = 0;
	nocrc = 0;

	while ((c = getopt(argc, argv, "i:o:fnh")) != -1) {
		switch (c) {
		case 'i':
			input = optarg;
			break;
		case 'o':
			output = optarg;
			break;
		case 'f':
			flash = 1;
			break;
		case 'n':
			nocrc = 1;
			break;
		case 'h':
			printf(" Usage: %s -i [input] -o [output]\n", argv[0]);
			printf(" i - input file\n");
			printf(" o - output file (uf2)\n");
			printf(" f - write to flash\n");
			printf(" n - don't use crc\n");
			printf(" h - print help\n");
			printf("\n");
			exit(0);
		case '?':
			printf(" Unknown option: %c\n", optopt);
			printf(" Type -h for help.\n");
			exit(-1);
		}
	}

	if (!input) {
		printf(" Required: -i [input] option.\n");
		exit(-1);
	}
	if (!output) {
		printf(" Required: -o [output] option.\n");
		exit(-1);
	}
}

void load_file(char *fname) {
	FILE *fd;

	fd = fopen(fname, "rb");
	if (fd == NULL) {
		printf(" ERROR: load_file: %s.\n", strerror(errno));
		exit(-11);
	}

	fseek(fd, 0, SEEK_END);
	size = ftell(fd);
	fseek(fd, 0, SEEK_SET);

	if (size >= MAX_PROG_SIZE) {
		printf(" Program too big: %d B, max : %d B.\n", size, MAX_PROG_SIZE);
		exit(-12);
	} else {
		printf(" Program size: %d B.\n", size);
	}

	memset(data, 0, MAX_PROG_SIZE);
	fread(data, 1, size, fd);
	fclose(fd);
}

void add_crc_to_first_block() {
	int ret;
	struct crc_param cp;

	if (nocrc)
		return;

	cp.polynomial = RPI_CRC_POLYN;
	cp.init_value = RPI_CRC_INIT;
	cp.final_xor = RPI_CRC_FXOR;

	ret = crc32(data, RPI_BLOCK_SIZE, cp);
	if (ret) {
		printf(" ERROR: CRC fail: %d.\n", ret);
		exit(-2);
	}
}

void write_uf2(char *name) {
	FILE *fd;
	uint i, addr, offs;
	uint blocks_count;
	struct uf2_block bl;

	fd = fopen(name, "wb");
	if (fd == NULL) {
		printf(" ERROR: write_uf2: %s.\n", strerror(errno));
		exit(-21);
	}

	offs = 0;
	blocks_count = (size + RPI_BLOCK_SIZE) >> 8;
	if (flash)
		addr = RPI_FLASH;
	else
		addr = RPI_SRAM;

	//printf(" Blocks: %d.\n", blocks_count);

	for (i = 0; i < blocks_count; ++i) {
		bl.magicStart0	= UF2_MAGICSTART0;
		bl.magicStart1	= UF2_MAGICSTART1;
		bl.flags		= 0x00002000;		// familyID present
		bl.targetAddr	= addr;
		bl.payloadSize	= RPI_BLOCK_SIZE;
		bl.blockNo		= i;
		bl.numBlocks	= blocks_count;
		bl.fileSize		= UF2_RPIPICO_ID;

		memset(&bl.data, 0, DATA_SIZE);
		memcpy(&bl.data, data + offs, RPI_BLOCK_SIZE);

		bl.magicEnd		= UF2_MAGICEND;

		if (fwrite(&bl, 1, sizeof(bl), fd) != BLOCK_SIZE) {
			printf(" ERROR: write_uf2 fail: %s.\n", strerror(errno));
			exit(-22);
		}
		addr += RPI_BLOCK_SIZE;
		offs += RPI_BLOCK_SIZE;
	}
	fclose(fd);
}


int main(int argc, char **argv) {
	check_arguments(argc, argv);
	load_file(input);
	add_crc_to_first_block();
	write_uf2(output);
	return 0;
}
