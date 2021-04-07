#include "rp2040.h"

#define PRIMASK_INTEN		(0 << 0)
#define PRIMASK_INTDI		(1 << 0)
#define CONTROL_MSP			(0 << 1)
#define CONTROL_PSP			(1 << 1)
#define CONTROL_PRIV 		(0 << 0)
#define CONTROL_UNPRIV		(1 << 0)


void arm_set_mode(uint priv);
uint arm_get_mode();
