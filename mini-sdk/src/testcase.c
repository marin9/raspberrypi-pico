#include "gpio.h"

/*
// test led blink (25)
void tc0() {
    uint dl;
    gpio_init(25, GPIO_FUNC_SIO);
    gpio_set_dir(25, 1);

    while (1) {
        gpio_set(25, 1);
        dl = 100000;
        while (dl--) asm volatile ("nop");
        gpio_set(25, 0);
        dl = 100000;
        while (dl--) asm volatile ("nop");
    }
}

// test gpio in(5)/out(0, 1, 2)
void tc1() {
    uint blink, stat, dl;

    gpio_init(0, GPIO_FUNC_SIO);
    gpio_init(1, GPIO_FUNC_SIO);
    gpio_init(2, GPIO_FUNC_SIO);
    gpio_init(5, GPIO_FUNC_SIO);

    gpio_set_dir_all(0x00000007);

    blink = 0;
    stat = 0;
    while (1) {
        if (!gpio_get(5)) {
            switch(blink) {
            case 0:
                gpio_set(0, 0);
                gpio_set(1, 1);
                gpio_set(2, 0);
                ++blink;
                break;
            case 1:
                gpio_set(0, 0);
                gpio_set(1, 0);
                gpio_set(2, 0);
                blink = 0;
                break;
            }
        } else {
            switch(stat) {
            case 0:
                gpio_set(0, 1);
                gpio_set(1, 0);
                gpio_set(2, 0);
                ++stat;
                break;
            case 1:
                gpio_set(0, 1);
                gpio_set(1, 1);
                gpio_set(2, 0);
                ++stat;
                break;
            case 2:
                gpio_set(0, 0);
                gpio_set(1, 0);
                gpio_set(2, 1);
                ++stat;
                break;
            case 3:
                gpio_set(0, 0);
                gpio_set(1, 1);
                gpio_set(2, 0);
                stat = 0;
                break;
            }
        }
        dl = 1000000;
        while (dl--) asm volatile ("nop");
    }
}
*/
