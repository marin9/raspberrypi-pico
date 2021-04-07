UART

```
void uart_init(uint id);
uint uart_read(uint id, char *buff, uint len);
uint uart_write(uint id, char *buff, uint len);
```

Usage:

- make
- copy picobin.uf2 to rpi-pico
- connect rpi-pico (GPIO0-TX, GPIO1-RX) to UART
