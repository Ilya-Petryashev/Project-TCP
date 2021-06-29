#include "stm32f7xx.h"                  // Device header
#include "Clock.h"
#include "SysTimer.h"
#include "LED.h"
#include "Button.h"

#define BUTTON_READ()	READ_BIT(GPIOC->IDR, GPIO_IDR_ID13)
#define LED_ON()		SET_BIT(GPIOB->ODR, GPIO_ODR_OD7)
#define LED_OFF()		CLEAR_BIT(GPIOB->ODR, GPIO_ODR_OD7)

uint32_t delay_count = 0;
uint8_t button_count = 0, button_state = 0;

void SysTick_Handler(void)
{
	if (BUTTON_READ() == 1)
	{
		if (button_count < 10)
		{
			button_count++;
		}
		else
		{
			if (button_state == 0) 
			{
				button_state = 1;
			}
		}
	}
	else
	{
		if (button_count > 0)
		{
			button_count--;
		}
		else
		{
			if (button_state == 1) 
			{
				button_state = 0;
			}
		}
	}
}

int main(void)
{
	Clock_ini();
	SysTick_ini();
	LED_ini();
	Button_ini();
	
	while(1) 
	{
		if (button_state == 1) {LED_ON();}
		else {LED_OFF();}
	}
}

