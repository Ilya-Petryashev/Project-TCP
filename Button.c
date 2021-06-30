#include "Button.h"

void Button_ini(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; 	//enabled clock for GPIOC
	
	GPIOC->MODER = 0x00000000;				//PC13 works in input mode
	GPIOC->OTYPER = 0x00000000;				//output type - push-pull (HL - 1, LL - 0)
	GPIOC->OSPEEDR = 0x00000000;			//output speed - low
	GPIOC->PUPDR = 0x00000000;				//no pull-up, no pull-down
}

uint8_t  Button_read(void)
{
	if (READ_BIT(GPIOC->IDR, GPIO_IDR_ID13) != RESET)
		return 1;
	else
		return 0;
}
