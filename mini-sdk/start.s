.cpu cortex-m0
.thumb
vector_table:
        b reset
        .balign 4

        .word reset
        .word nmi
        .word hardfault

        .word unused
        .word unused
        .word unused
        .word unused

        .word unused
        .word unused
        .word unused
        .word svcall

        .word unused
        .word unused
        .word pendsv
        .word systick

        .word irq0
        .word irq1
        .word irq2
        .word irq3
        .word irq4
        .word irq5
        .word irq6
        .word irq7
        .word irq8
        .word irq9
        .word irq10
        .word irq11
        .word irq12
        .word irq13
        .word irq14
        .word irq15
        .word irq16
        .word irq17
        .word irq18
        .word irq19
        .word irq20
        .word irq21
        .word irq22
        .word irq23
        .word irq24
        .word irq25

.thumb_func
reset:
	ldr r0, =0x20001000
	mov sp, r0

	ldr r0, =0xE000ED08
	ldr r1, =vector_table
	str r1, [r0]

	bl init

unused:
	b .



.align
.ltorg
.balign 0x100



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
