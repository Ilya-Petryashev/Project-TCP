#include "stm32f7xx.h"                  // Device header
#include "Clock.h"
#include "SysTimer.h"
#include "LED.h"
#include "Button.h"
#include "Usart_my.h"

uint8_t temp = 0;

int main(void)
{
	Clock_ini();
	SysTick_ini();
	LED_ini();
	Button_ini();
	USART_ini();
	
	//USART_TransmitData(0x5D);
		
	while(1) 
	{
		if (Button_Flag_Read() == 1) 
		{
			Button_Flag_Write(0);
			LED_ON();
			USART_TransmitData(0x5D);
			while (USART_TXE_Read() != 1) {}
		}
		else {LED_OFF();}
		
	}
}

