#include "SysTimer.h"
#include "Button.h"

void SysTick_ini(void)
{
	SysTick->LOAD = (1000000/1000)-1;
	SysTick->CTRL |=  SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
	SysTick->CTRL &=  ~(SysTick_CTRL_COUNTFLAG_Msk);
}

void SysTick_Handler(void)
{
	if (Button_read() == 1)
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
