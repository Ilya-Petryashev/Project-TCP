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
		
	while(1) 
	{
		if (Button_Flag_Read() == 1) 
		{
			Button_Flag_Write(0);
			USART_TransmitData(0x5D);
			while (USART_TC_Read() != 1) {}
		}
		else {LED_OFF();}
		
		
		
		/*    Data_packet.T_ID = 0xFFFFFFFF;
    Data_packet.R_ID = 0x00000000;
    Data_packet.Mlen = 46;
    for (int i = 0; i<=45; i++)
    {
        Data_packet.data[i] = i;
    }
    Data_packet.checksum = 666;*/
		
		
	}
}

