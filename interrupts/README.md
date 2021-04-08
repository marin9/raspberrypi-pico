GPIO interrupts

```
void gpio_init(uint gpio, uint func);
void gpio_dir(uint gpio, uint out);
void gpio_pullup(uint gpio, uint enable);
void gpio_pulldown(uint gpio, uint enable);
void gpio_set(uint gpio, uint value);
uint gpio_get(uint gpio);
void gpio_deinit(uint gpio);
void gpio_intr_set(uint gpio, uint enable, uint event);
void gpio_intr_ack(uint gpio);

void nvic_init();
void nvic_register_irq(uint irq, void (*handler)());
void nvic_enable(uint irq);
void nvic_disable(uint irq);
void nvic_setpending(uint irq);
void nvic_clearpending(uint irq);
```

Usage:

- make
- copy picobin.uf2 to rpi-pico
