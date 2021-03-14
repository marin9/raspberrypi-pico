#include <stdio.h>
#include <stdlib.h>
#include "defs.h"


int crc32(char *data, uint size, struct crc_param param) {
	uint *table;
	uint i, j, crcn;
	unsigned char byte;

	if (!data || !size) {
		printf(" ERROR: crc32: Illegal parameters.\n");
		return -1;
	}

	// initialize
	table = (uint*)malloc(4 * size);
	if (!table) {
		printf(" ERROR: crc32: No memory.\n");
		return -2;
	}

	// generate table
	for (i = 0; i < size; ++i) {
		crcn = i;
		for (j = 0; j < 32; ++j) {
			crcn = (crcn << 1) ^ ((crcn & 0x80000000) ? param.polynomial : 0);
		}
		table[i] = crcn;
		//printf(" [%d]: %x\n", i, crcn);
	}

	// calculate crc
	crcn = param.init_value;
	for (i = 0; i < size - 4; ++i) {
		byte = (crcn >> 24) & 0xff;
		byte ^= data[i];
		crcn = crcn << 8;
		crcn = crcn ^ table[(int)byte];
	}

	data[size - 4] = (crcn >> 0) & 0xff;
	data[size - 3] = (crcn >> 8) & 0xff;
	data[size - 2] = (crcn >> 16) & 0xff;
	data[size - 1] = (crcn >> 24) & 0xff;
	//printf(" crc: %x\n", crcn);

	free(table);
	return 0;
}

