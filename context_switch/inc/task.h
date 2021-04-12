#pragma once

#define STACK_SIZE	1024
#define TASK_COUNT	8

typedef unsigned int uint;

struct context_t {
	uint r0, r1, r2, r3, r4, r5, r6, r7;
	uint r8, r9, r10, r11, lr, pc;
};

struct task_t {
	uint *sp;
	uint used;
    struct task_t *next;
};

struct queue_t {
	struct task_t *first;
	struct task_t *last;
};

void task_init();
void task_create(void (*func)());
void task_yield();
void task_term();
