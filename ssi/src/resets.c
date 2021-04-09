#include "resets.h"

struct resets_hw {
	uint reset;
	uint wdsel;
	uint reset_done;
};

#define rst	((volatile struct resets_hw*)RESETS_BASE)


void reset_set(uint hw) {
	rst->reset |= hw;
}

void reset_release(uint hw) {
	rst->reset &= (~hw);
}

void reset_release_wait(uint hw) {
	rst->reset &= (~hw);
	while (!(rst->reset_done & hw));
}
