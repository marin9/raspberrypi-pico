#pragma once
#define STACK_SIZE		4096
#define TASK_COUNT		16

#define ERR_OK			0
#define ERR_NORES		1
#define ERR_PARAMS		2

typedef void (*thread_func)(void* args);
typedef unsigned int uint;

typedef struct {
	uint r4, r5, r6, r7, r8, r9, r10, r11;
	uint r0, r1, r2, r3, r12, lr, pc, psr;
} context_t;

typedef struct task_t {
	uint *sp;
	uint param;
	uint status;
	struct task_t *next;
} task_t;

typedef struct {
	task_t *first;
	task_t *last;
} queue_t;

typedef struct {
	uint value;
	queue_t waitq;
} sem_t;

void rtos_init();
void rtos_start();
uint rtos_ticks();

int thread_start(thread_func func, void *args);
void thread_sleep(uint ticks);
void thread_terminate();
int sem_init(sem_t *sem, uint value);
int sem_signal(sem_t *sem);
int sem_wait(sem_t *sem);
