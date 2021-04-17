.cpu cortex-m0
.thumb
.global reset
reset:
	ldr r0, =0x20020000
	mov sp, r0
	bl init
	b .

.align
.ltorg
.balign 0x100


.thumb
.global arm_inten
arm_inten:
	//cpsie i
	bx lr

.thumb
.global arm_intds
arm_intds:
	//cpsid i
	bx lr

.thumb
.global arm_getpsr
arm_getpsr:
	mrs r0, psr
	bx lr

.thumb
.global arm_getprim
arm_getprim:
	mrs r0, primask
	bx lr

.thumb
.global arm_getcontrol
arm_getcontrol:
	mrs r0, control
	bx lr
