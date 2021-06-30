#include "stm32f7xx.h"                  // Device header
#include "Clock.h"
#include "SysTimer.h"
#include "LED.h"
#include "Button.h"
#include "Usart_my.h"

#define LED_ON()	SET_BIT(GPIOB->ODR, GPIO_ODR_OD7)
#define LED_OFF()	CLEAR_BIT(GPIOB->ODR, GPIO_ODR_OD7)

uint32_t delay_count = 0, temp = 0;
volatile uint8_t button_count = 0, button_state = 0;

/*void USART2_IRQHandler(void) 
{  
	// prepyvanie po peredache
	if(USART_GetITStatus(USART2, USART_IT_TXE) == 1)
	{
		USART_ClearITPendingBit(USART2, USART_IT_TXE); // ochistka bita prerivaniya
	
		if (i != i_size)
		{
			USART_SendData(USART2, TX_buffer[i]);
			i++;
		}
		else
		{
			USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
			i = 0;
		}
	}
}*/

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

int main(void)
{
	Clock_ini();
	SysTick_ini();
	LED_ini();
	Button_ini();
	USART_ini();
	
	while(1) 
	{
		if (Button_read() == 1) {LED_ON();}
		else {LED_OFF();}
	}
}

