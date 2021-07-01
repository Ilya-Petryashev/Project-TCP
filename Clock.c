#include "Clock.h"

void Clock_ini(void)
{
	RCC -> CR |= RCC_CR_HSEON;          			// HSE ON
	RCC -> CFGR |= RCC_CFGR_SW_0;       			// HSE is selected for SYSCLK
	RCC -> CFGR |= RCC_CFGR_HPRE_DIV1;  			// AHB Prescaler is divided by 1
	RCC -> DCKCFGR2 |= RCC_DCKCFGR2_USART2SEL_0;	// USART2 clock source - SYSCLK (8 MHz)
}
