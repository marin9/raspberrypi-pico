#pragma once

uint arm_getpsr();
uint arm_getprim();
uint arm_getcontrol();
void arm_intds();
void arm_inten();
void arm_switch(void* prev, void* next);
