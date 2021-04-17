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



.thumb
.global arm_switch
arm_switch:
	push {r4-r7}
    mov  r4, r8
    mov  r5, r9
    mov  r6, r10
    mov  r7, r11
    push {r4-r7}

    mov  r2, sp
    str  r2, [r0]
    ldr  r2, [r1]
    mov  sp, r2

    pop  {r4-r7}
    mov  r8, r4
    mov  r9, r5
    mov  r10, r6
    mov  r11, r7
    pop  {r4-r7}

	ldr r0, =0xfffffff1
	bx r0
