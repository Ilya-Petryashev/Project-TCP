#ifndef LED_H
#define LED_H
#endif

#include "stm32f7xx.h"

#define LED_ON()	SET_BIT(GPIOB->ODR, GPIO_ODR_OD7)
#define LED_OFF()	CLEAR_BIT(GPIOB->ODR, GPIO_ODR_OD7)

void LED_ini(void);
