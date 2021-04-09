.cpu cortex-m0
.thumb
	// Enable XOSC
	ldr r0, =0x40024000
	ldr r1, =0xAA0
	str r1, [r0]
	ldr r0, =0x4002400C
	ldr r1, =0x2F
	str r1, [r0]
	ldr r0, =0x40024000
	ldr r1, =0xFABAA0
	str r1, [r0]
loop:
	// wait while xosc get ready
	ldr r0, =0x40024004
	ldr r1, =0x80000000
	ldr r2, [r0]
	and r2, r2, r1
	cmp r2, #0
	beq loop


	// Enable clk_peri
	ldr r0, =0x40008048
	ldr r1, =0x880
	str r1, [r0]

	// unreset all
	ldr r0, =0x4000C000
	mov r1, #0
	str r1, [r0]

	// wait for unreset
wait:
	ldr r0, =0x4000C008
	cmp r0, r1
	beq wait

	// IO_QSPI set to FUNC0 (XIP)
	ldr r0, =0x40018004
	str r1, [r0]
	ldr r0, =0x4001800C
	str r1, [r0]
	ldr r0, =0x40018014
	str r1, [r0]
	ldr r0, =0x4001801C
	str r1, [r0]

	// SSI disable
	ldr r0, =0x18000008
	mov r1, #0
	str r1, [r0]

	// SSI clk_divider = 8
	ldr r0, =0x18000014
	mov r1, #8
	str r1, [r0]

	// SSI 32 clk per frame, EEPROM read mode
	ldr r0, =0x18000000
	ldr r1, =0x001f0300
	str r1, [r0]

	// SSI read_cmd = 3, 8 bit instr, addr_len = 24 bit
	ldr r0, =0x180000f4
	ldr r1, =0x03000218
	str r1, [r0]

	// SSI slave select
	ldr r0, =0x18000010
	mov r1, #1
	str r1, [r0]

	// SSI set data frames
	ldr r0, =0x18000004
    ldr r0, =0x00000000
    str r1, [r0]

	// SSI enable
	ldr r0, =0x18000008
	mov r1, #1
	str r1, [r0]


	ldr r0, =0x10000000
	ldr r1, =0x20000000
	ldr r2, =0x400

copy:
	ldr r3,[r0]
	str r3,[r1]
	add r0, #4
	add r1, #4
	sub r2, #1
	bne copy

	ldr r0, =0x20000101
	bx r0

.align
.ltorg
.balign 0x100

	// Stack init
	ldr r0, =0x20001000
	mov sp, r0

	bl init
	b .
