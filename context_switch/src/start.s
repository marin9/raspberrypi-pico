.cpu cortex-m0
.thumb
	ldr r0, =0x20010000
	mov sp, r0

	bl init
	b .

.align
.ltorg
.balign 0x100


.thumb_func
.global context_switch
context_switch:
	push {lr}
	push {r0}
	push {r0-r3}
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
	pop {r0-r3}
	pop {r0}
	mov lr, r0
	pop {pc}
