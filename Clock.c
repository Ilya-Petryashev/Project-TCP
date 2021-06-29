#include "Clock.h"

void Clock_ini(void)
{
	RCC -> CR |= RCC_CR_HSEON;          // HSE ON
	RCC -> CFGR |= RCC_CFGR_SW_0;       // HSE is selected for SYSCLK
	RCC -> CFGR |= RCC_CFGR_HPRE_DIV1;  // AHB Prescaler is divided by 1
}
