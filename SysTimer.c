#include "SysTimer.h"

void SysTick_ini(void)
{
	SysTick->LOAD = (1000000/1000)-1;
	SysTick->CTRL |=  SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
	SysTick->CTRL &=  ~(SysTick_CTRL_COUNTFLAG_Msk);
}
