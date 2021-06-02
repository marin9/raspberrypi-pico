.cpu cortex-m0
.thumb
.global reset
reset:
	ldr r0, =0x20001000
	mov sp, r0

	mov r0, #2
	msr control, r0

	ldr r0, =0x20002000
	mov sp, r0

	bl init
	b .

.align
.ltorg
.balign 0x100




.text
.align 4
.force_thumb
.global __aeabi_idiv
__aeabi_idiv:
	ldr r3, =0xD0000000
	str r0, [r3, #0x68]
	str r1, [r3, #0x6C]
	b 1f
1:	b 1f
1:	b 1f
1:	b 1f
1:	ldr r0, [r3, #0x70]
	bx lr


.text
.align 4
.force_thumb
.global __aeabi_idivmod
__aeabi_idivmod:
	ldr r3, =0xD0000000
	str r0, [r3, #0x68]
	str r1, [r3, #0x6C]
	b 1f
1:	b 1f
1:	b 1f
1:	b 1f
1:	ldr r0, [r3, #0x74]
	bx lr


.text
.align 4
.force_thumb
.global __aeabi_udiv
__aeabi_udiv:
	ldr r3, =0xD0000000
	str r0, [r3, #0x60]
	str r1, [r3, #0x64]
	b 1f
1:	b 1f
1:	b 1f
1:	b 1f
1:	ldr r0, [r3, #0x70]
	bx lr


.text
.align 4
.force_thumb
.global __aeabi_udivmod
__aeabi_udivmod:
	ldr r3, =0xD0000000
	str r0, [r3, #0x60]
	str r1, [r3, #0x64]
	b 1f
1:	b 1f
1:	b 1f
1:	b 1f
1:	ldr r0, [r3, #0x74]
	bx lr




.text
.align 0
.force_thumb
.syntax unified
.global __gnu_thumb1_case_uqi
.thumb_func
.type __gnu_thumb1_case_uqi,function
__gnu_thumb1_case_uqi:
push	{r1}
mov	r1, lr
lsrs	r1, r1, #1
lsls	r1, r1, #1
ldrb	r1, [r1, r0]
lsls	r1, r1, #1
add	lr, lr, r1
pop	{r1}
bx	lr
.size __gnu_thumb1_case_uqi, . - __gnu_thumb1_case_uqi

.text
.align 0
.force_thumb
.syntax unified
.global __gnu_thumb1_case_uhi
.thumb_func
.type __gnu_thumb1_case_uhi,function
__gnu_thumb1_case_uhi:
push	{r0, r1}
mov	r1, lr
lsrs	r1, r1, #1
lsls	r0, r0, #1
lsls	r1, r1, #1
ldrh	r1, [r1, r0]
lsls	r1, r1, #1
add	lr, lr, r1
pop	{r0, r1}
bx	lr
.size __gnu_thumb1_case_uhi, . - __gnu_thumb1_case_uhi
