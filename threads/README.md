Threads

```
uint thread_start(void (*thread_func)(void* args), void *args);
void thread_sleep(uint ticks);
void thread_terminate();
uint sem_init(uint sem_id, uint value);
uint sem_signal(uint sem_id);
uint sem_wait(uint sem_id);
```

Usage:

- make
- copy picobin.uf2 to rpi-pico
