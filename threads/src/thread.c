#include "thread.h"
#include "arm.h"
#include "nvic.h"
#include "systick.h"

#define TASK_UNUSED		0
#define TASK_READY		1

#define SYS_ENTRY()		arm_intds()
#define SYS_EXIT()		arm_inten()

static uint scheduler;
static uint sys_time;
static task_t *active_task;
static queue_t ready_queue;
static queue_t sleep_queue;
static task_t task[TASK_COUNT + 1];
static char stack[TASK_COUNT + 1][STACK_SIZE] __attribute__((aligned(8)));

static void queue_init(queue_t *q) {
	q->first = 0;
	q->last = 0;
}

static void queue_push(queue_t *q, task_t *t) {
	if (q->first == 0) {
		t->next = 0;
		q->first = t;
		q->last = t;
	} else {
		t->next = 0;
		q->last->next = t;
		q->last = t;
	}
}

static void queue_pushsort(queue_t *q, task_t *t) {
	task_t *tmp;

	if (q->first == 0) {
		q->first = t;
		q->last = t;
		t->next = 0;
	} else {
		tmp = q->first;
		if (t->param < tmp->param) {
			t->next = tmp;
			q->first = t;
		} else {
			while (tmp->next && (t->param > tmp->next->param))
				tmp = tmp->next;

			if (tmp->next == 0) {
				tmp->next = t;
				t->next = 0;
				q->last = t;
			} else {
				t->next = tmp->next;
				tmp->next = t;
			}
		}
	}
}

static task_t* queue_pop(queue_t *q) {
	task_t *tmp = q->first;
	if (!tmp)
		return 0;

	q->first = tmp->next;
	if (!q->first)
		q->last = 0;

	return tmp;
}

static task_t* queue_peek(queue_t *q) {
	return q->first;
}

static void task_yield() {
	*((uint*)0xE000ED04) = (1 << 28);
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
}

void pendsv_handler() {
	task_t *prev = active_task;
uart_print("pendsv handler\r\n");
	if (prev && prev->status == TASK_READY)
		queue_push(&ready_queue, prev);

	active_task = queue_pop(&ready_queue);

uart_print("prev: ");
uart_hex(prev);
uart_print(" active: ");
uart_hex(active_task);
uart_print("\r\n");

	if (prev)
		arm_switch(prev, active_task);
	else
		arm_switch((void*)0x20030000, active_task);

}

void systick_handler() {
	int sched;
	task_t *t;

	if (!scheduler)
		return;

	sys_time += 1;
	sched = 0;
	t = queue_peek(&sleep_queue);
	while (t) {
		if (sys_time >= t->param) {
			t = queue_pop(&sleep_queue);
			queue_push(&ready_queue, t);
			t = queue_peek(&sleep_queue);
			sched = 1;
		} else {
			break;
		}
	}

	if (sched)
		task_yield();
}

static void idle() {
	while (1) {
		SYS_ENTRY();
		uart_print("idle\r\n");
		task_yield();
		uart_print("idle after yield\r\n");
		SYS_EXIT();
	}
}


void rtos_init() {
	int i;
	active_task = 0;
	sys_time = 0;
	scheduler = 0;

	for (i = 0; i < TASK_COUNT; ++i)
		task[i].status = TASK_UNUSED;

	queue_init(&ready_queue);
	queue_init(&sleep_queue);
	thread_start(idle, 0);
}

void rtos_start() {
	nvic_init();
	systick_init();
	//systick_set(12000-1);
	scheduler = 1;
	task_yield();
}

uint rtos_ticks() {
	return sys_time;
}


int thread_start(thread_func func, void *args) {
	int i;

	SYS_ENTRY();
	for (i = 0; i < TASK_COUNT; ++i)
		if (!task[i].status)
			break;

	if (i >= TASK_COUNT) {
		SYS_EXIT();
		return -ERR_NORES;
	}

	task[i].status = TASK_READY;
	task[i].sp = (uint*)(stack[i] + STACK_SIZE - 8);
	task[i].sp -= sizeof(context_t);

	context_t *ctx = (context_t*)task[i].sp;
	ctx->psr = 0x21000000;
  	ctx->lr = (uint)thread_terminate;
  	ctx->pc = (uint)func;
  	ctx->r0 = (uint)args;

	queue_push(&ready_queue, &task[i]);
	if (scheduler)
		task_yield();
	SYS_EXIT();
	return ERR_OK;
}

void thread_sleep(uint ticks) {
	SYS_ENTRY();
	if (ticks) {
		active_task->param = ticks + sys_time;
		queue_pushsort(&sleep_queue, active_task);
	}
	task_yield();
	SYS_EXIT();
}

void thread_terminate() {
	SYS_ENTRY();
	active_task->status = TASK_UNUSED;
	task_yield();
}

int sem_init(sem_t *sem, uint value) {
	if (!sem)
		return -ERR_PARAMS;

	sem->value = value;
	queue_init(&sem->waitq);
	return ERR_OK;
}

int sem_wait(sem_t *sem) {
	int ret = ERR_OK;

	if (!sem)
		return -ERR_PARAMS;

	SYS_ENTRY();
	if (sem->value > 0) {
		sem->value -= 1;
	} else {
		queue_push(&(sem->waitq), active_task);
		task_yield();
	}
	SYS_EXIT();
	return ret;
}

int sem_signal(sem_t *sem) {
	int ret = ERR_OK;
	task_t *tmp;

	if (!sem)
		return -ERR_PARAMS;

	SYS_ENTRY();
	tmp = queue_pop(&(sem->waitq));
	if (tmp) {
		queue_push(&ready_queue, tmp);
		task_yield();
	} else {
		sem->value += 1;
	}

	SYS_EXIT();
	return ret;
}
