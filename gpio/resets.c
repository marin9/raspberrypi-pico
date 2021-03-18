#include "resets.h"

struct resets_hw {
	uint reset;
	uint wdsel;
	uint resetdone;
};

#define reg	((volatile struct resets_hw*)RESETS_BASE)


void reset_block(uint block) {
	reg->reset |= (1 << block);
}

void unreset_block(uint block) {
	reg->reset &= (~(1 << block));
}

void unreset_block_wait(uint block) {
	reg->reset &= (~(1 << block));

	while (~reg->resetdone & (1 << block));
}
