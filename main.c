#include "stm32f7xx.h"                  // Device header
#include "Clock.h"
#include "SysTimer.h"
#include "LED.h"
#include "Button.h"
#include "Usart_my.h"

uint32_t delay_count = 0, temp = 0;

int main(void)
{
	Clock_ini();
	SysTick_ini();
	LED_ini();
	Button_ini();
	USART_ini();
	
	for(int i = 0; i<1000; i++) 
	{
		
	}
	
	USART_TransmitData(0x5D);
		
	while(1) 
	{
		if (Button_read() == 1) {LED_ON();}
		else {LED_OFF();}
		if (RX_flag == 1) 
		{
			RX_flag = 0;
			LED_ON();
		}
	}
}

