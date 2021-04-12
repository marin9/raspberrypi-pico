#include "task.h"

static struct task_t *active_task;
static struct queue_t ready_queue;
static struct task_t task[TASK_COUNT];
static char __attribute__((aligned(8))) \
	stack[STACK_SIZE*TASK_COUNT];


static void task_enqueue(struct task_t *t) {
	if (!ready_queue.first) {
		ready_queue.first = t;
		ready_queue.last = t;
	} else {
		ready_queue.last->next = t;
		ready_queue.last = t;
	}
	t->next = 0;
}

static struct task_t* task_dequeue() {
	struct task_t *tmp = ready_queue.first;
	if (!tmp)
		return 0;

	ready_queue.first = tmp->next;
	if (!ready_queue.first)
		ready_queue.last = 0;

	return tmp;
}

void context_switch(void *prev, void *next);


void task_init(){
	int i;
	for (i = 0; i < TASK_COUNT; ++i)
		task[i].used = 0;

	active_task = 0;
	ready_queue.first = 0;
	ready_queue.last = 0;
}

void task_create(void (*func)()){
	int i;
	struct context_t *ctx;

	for (i = 0; i < TASK_COUNT; ++i)
		if (!task[i].used)
			break;

	if (i == TASK_COUNT)
		while (1);

	task[i].sp = (uint*)(stack + i * STACK_SIZE + STACK_SIZE);
	task[i].sp -= sizeof(struct context_t);
	task[i].used = 1;

	ctx = (struct context_t*)task[i].sp;
	ctx->lr = (uint)task_term;
  	ctx->pc = (uint)func;

	task_enqueue(&task[i]);
}


void task_yield(){
	struct task_t *prev_task = active_task;

	if (!prev_task || !(prev_task->used)) {
		active_task = task_dequeue();
		context_switch((void*)0x20001100, &active_task->sp);
	} else {
		task_enqueue(active_task);
		active_task = task_dequeue();
		context_switch(&prev_task->sp, &active_task->sp);
	}
}

void task_term() {
	active_task->used = 0;
	task_yield();
}
