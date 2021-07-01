#include "Usart_my.h"

void USART_ini(void)
{
	// init PORT A (RX - PA3, TX - PA2)
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 						//enabled clock for GPIOB
	
	GPIOA->MODER |= GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1;	//PA2,PA3 works alternate function mode
	GPIOA->OTYPER = 0x00000000;									//output type - push-pull (HL - 1, LL - 0) - reset value
	GPIOA->OSPEEDR = 0x0C000000;								//output speed - low - reset value
	GPIOA->PUPDR = 0x64000000;									//no pull-up, no pull-down - reset value
	GPIOA->AFR[0] |= 0x00007700;								// AF7 for A3 and A2 
	
	
	// init USART2
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	
	//USART2->CR3 = USART_CR3_OVRDIS;	//disable overrun error bit
	USART2->BRR = 0x45;   // 69d  - speed
	USART2->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_RXNEIE; 
	USART2->CR1 = USART_CR1_UE;
		
	NVIC_EnableIRQ(USART2_IRQn);
}
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
uint8_t Is_TXE_Set(void)
{
	if (READ_BIT(USART2->ISR, USART_ISR_TXE) != RESET)
		return 1;
	else
		return 0;
}

uint8_t Is_TC_Set(void)
{
	if (READ_BIT(USART2->ISR, USART_ISR_TC) != RESET)
		return 1;
	else
		return 0;
}
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void USART2_IRQHandler(void) 
{  
	RX_buf = (USART2->RDR & 0xFF);
	RX_flag = 1;
}
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void USART_TransmitData(uint8_t data)
{
	USART2->TDR = data;
}
