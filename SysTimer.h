#ifndef SysTimer_H
#define SysTimer_H
#endif

#include "stm32f7xx.h"

void SysTick_ini(void);
void SysTick_Handler(void);
uint8_t  Button_Flag_Read(void);
void Button_Flag_Write(uint8_t value);
