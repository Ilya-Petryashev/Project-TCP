#include "stm32f7xx.h"                  // Device header
#include "Clock.h"
#include "SysTimer.h"
#include "LED.h"
#include "Button.h"
#include "Usart_my.h"

uint8_t temp = 0;
uint8_t TX_buffer[64] = {0};

struct Data_packet
{
	uint32_t T_ID;			//ID of Transmitter
	uint32_t R_ID;			//ID of Receiver
	uint32_t P_ID;			//ID of Packet
	uint32_t MLen;			//Message length
	uint8_t data[46];
	uint16_t checksum;	
} Packet;

void Fill_TX_buffer(void);
uint16_t CRC16(uint8_t* pcBlock_t, uint8_t len);

void Fill_TX_buffer (void)
{
	TX_buffer[0] = Packet.T_ID >> 24;
	TX_buffer[1] = Packet.T_ID >> 16;
	TX_buffer[2] = Packet.T_ID >> 8;
	TX_buffer[3] = Packet.T_ID;
	
	TX_buffer[4] = Packet.R_ID >> 24;
	TX_buffer[5] = Packet.R_ID >> 16;
	TX_buffer[6] = Packet.R_ID >> 8;
	TX_buffer[7] = Packet.R_ID;
	
	TX_buffer[8] = Packet.P_ID >> 24;
	TX_buffer[9] = Packet.P_ID >> 16;
	TX_buffer[10] = Packet.P_ID >> 8;
	TX_buffer[11] = Packet.P_ID;
	
	TX_buffer[13] = Packet.MLen >> 24;
	TX_buffer[14] = Packet.MLen >> 16;
	TX_buffer[15] = Packet.MLen >> 8;
	TX_buffer[16] = Packet.MLen;
	
	for (uint8_t i = 17; i < 62; i++)
	{
		TX_buffer[i] = Packet.data[i - 17];
	}
	
	Packet.checksum = CRC16(&TX_buffer[0], 62);
	TX_buffer[62] = Packet.checksum >> 8;
	TX_buffer[63] = Packet.checksum;
}


uint16_t CRC16(uint8_t* pcBlock_t, uint8_t len)
{
    uint16_t crc = 0xFFFF;
    uint16_t pcBlock = *pcBlock_t;

    while (len--)
    {
        crc ^= pcBlock++ << 8;

        for (uint8_t i = 0; i < 8; i++)
            crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
    }
    return crc;
}

int main(void)
{
	Clock_ini();
	SysTick_ini();
	LED_ini();
	Button_ini();
	USART_ini();
	
	// fill the struct
	Packet.T_ID = 0xFFFFFFFF;		//MCU
	Packet.R_ID = 0xAAAAAAAA;		//PC
	Packet.P_ID = 0x0A0A0A0A;	
	Packet.MLen = 46;
	for (uint8_t i = 0; i<=45; i++)
	{
		Packet.data[i] = i;
	}
	// fill TX_buffer
	Fill_TX_buffer();
	
	while(1) 
	{
		if (Button_Flag_Read() == 1) 
		{
			Button_Flag_Write(0);
			LED_ON();
			USART_TransmitBuffer(&TX_buffer[64]);
			while(USART_TC_Read() == 0) {}
			LED_OFF();
		}
		
		if (USART_RXE_Read() == 1)
		{
			temp = 1;
		}
	}
}

