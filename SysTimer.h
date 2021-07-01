#ifndef SysTimer_H
#define SysTimer_H
#endif

#include "stm32f7xx.h"

void SysTick_ini(void);
void SysTick_Handler(void);

volatile uint8_t button_count = 0, button_state = 0;
