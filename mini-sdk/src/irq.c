#include "uart.h"

void nmi() {

}

void hardfault() {

}

void svcall() {

}

void pendsv() {

}


void irq0() {

}

void irq1() {

}

void irq2() {

}

void irq3() {

}

void irq4() {

}

void irq5() {

}

void irq6() {

}

void irq7() {

}

void irq8() {

}

void irq9() {

}

void irq10() {

}

void irq11() {

}

void irq12() {

}

void irq13() {
    uart_print("13\r\n");
    reg_wr(IO_BANK0_BASE + 0xf0, 1 << 27);
}

void irq14() {

}

void irq15() {

}

void irq16() {

}

void irq17() {

}

void irq18() {

}

void irq19() {

}

void irq20() {

}

void irq21() {

}

void irq22() {

}

void irq23() {

}

void irq24() {

}

void irq25() {

}
