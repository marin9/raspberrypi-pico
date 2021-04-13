.cpu cortex-m0
.thumb
.global reset
reset:
	ldr r0, =0x20010000
	mov sp, r0

	bl init
	b .

.align
.ltorg
.balign 0x100
