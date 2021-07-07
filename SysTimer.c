#include "SysTimer.h"
#include "Button.h"

volatile uint8_t button_count = 0, button_state = 0, button_flag = 0, delay_count;

void SysTick_ini(void)
{
	SysTick->LOAD = (1000000/1000)-1;
	SysTick->CTRL |=  SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
	SysTick->CTRL &=  ~(SysTick_CTRL_COUNTFLAG_Msk);
}

void SysTick_Handler(void)
{
	if (Button_Read() == 1)
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
				button_flag = 1;
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
	delay_count--;
	
}

void delay_ms(uint8_t delay_temp)
	{
		delay_count = delay_temp;
		while(delay_count){}
	}
uint8_t  Button_Flag_Read(void)
{
	if (button_flag != 0)
		return 1;
	else
		return 0;
}

void Button_Flag_Write(uint8_t value)
{
	button_flag = value;
}
