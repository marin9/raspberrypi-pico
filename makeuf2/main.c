#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "defs.h"


static uint size;
static char data[128 * 1024] = {0};


void check_arguments(int argc, char **argv) {
	if (argc != 3) {
		printf(" Usage: %s [input] [output]\n", argv[0]);
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
	printf(" Program size: %d B.\n", size);

	fread(data, 1, size, fd);
	fclose(fd);
}

void add_crc() {
	struct crc_param cp;

	// from RPi Pico doc
	cp.polynomial = 0x04c11db7;
	cp.init_value = 0xffffffff;
	cp.final_xor = 0x00000000;

	if (crc32(data, 256, cp) < 0) {
		printf(" ERROR: crc fail.\n");
		exit(-2);
	}
}

void write_uf2(char *name) {
	FILE *fd;
	uint i, addr, offs;
	uint blocks_count;	
	struct uf2_block bl;

	if (!name) {
		printf(" ERROR: write_uf2: Illegal arguments.\n");
		exit(-20);
	}

	fd = fopen(name, "wb");
	if (fd == NULL) {
		printf(" ERROR: write_uf2: %s.\n", strerror(errno));
		exit(-21);
	}

	blocks_count = (size + 256) >> 8;
	addr = 0x20000000;	// 0x10000000 flash, 0x20000000 ram
	offs = 0;

	printf(" Blocks: %d.\n", blocks_count);

	for (i = 0; i < blocks_count; ++i) {

		bl.magicStart0	= UF2_MAGICSTART0;
		bl.magicStart1	= UF2_MAGICSTART1;
		bl.flags	= 0x00002000;		// familyID present
		bl.targetAddr	= addr;
		bl.payloadSize	= 0x00000100;	// 256 B per block
		bl.blockNo	= i;
		bl.numBlocks	= blocks_count;
		bl.fileSize	= UF2_RPIPICO_ID;
		memset(&bl.data, 0, DATA_SIZE);
		memcpy(&bl.data, data + offs, 256);
		bl.magicEnd	= UF2_MAGICEND;

		if (fwrite(&bl, 1, sizeof(bl), fd) != BLOCK_SIZE) {
			printf(" ERROR: save_file: write fail.\n");
			exit(-22);
		}
		addr += 0x100;
		offs += 0x100;
	}
	fclose(fd);
}


int main(int argc, char **argv) {
	check_arguments(argc, argv);
	load_file(argv[1]);
	add_crc();
	write_uf2(argv[2]);
	return 0;
}
