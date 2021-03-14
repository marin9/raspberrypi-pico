#pragma once

// UF2 defines
#define BLOCK_SIZE	512
#define HEADER_SIZE	(8 * 4)
#define DATA_SIZE	(BLOCK_SIZE - HEADER_SIZE - 4)

#define UF2_MAGICSTART0	0x0a324655
#define UF2_MAGICSTART1	0x9e5d5157
#define UF2_MAGICEND		0x0ab16f30
#define UF2_RPIPICO_ID		0xe48bff56

// RPi Pico defines
#define RPI_FLASH		0x10000000
#define RPI_SRAM		0x20000000


typedef unsigned int uint;

struct __attribute__((__packed__)) uf2_block{
	uint magicStart0;
	uint magicStart1;
	uint flags;
	uint targetAddr;
	uint payloadSize;
	uint blockNo;
	uint numBlocks;
	uint fileSize;		// or familyID
	char data[DATA_SIZE];
	uint magicEnd;
};

struct crc_param {
	uint polynomial;
	uint init_value;
	uint final_xor;
};


int crc32(char *data, uint size, struct crc_param param);

