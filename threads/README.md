Threads

```
int thread_start(void (*thread_func)(void* args), void *args);
void thread_sleep(uint ticks);
void thread_terminate();
int sem_init(uint sem_id, uint value);
int sem_signal(uint sem_id);
int sem_wait(uint sem_id);
```

Usage:

- make
- copy picobin.uf2 to rpi-pico
