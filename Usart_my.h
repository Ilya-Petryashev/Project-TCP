#ifndef Usart_my_H
#define Usart_my_H
#endif

#include "stm32f7xx.h"

#define USART_ReceiveData	(USART2->RDR & 0xFF)

void USART2_IRQHandler(void);
void USART_ini(void);
uint8_t USART_TXE_Read(void);
uint8_t USART_TC_Read(void);
void USART_TransmitData(uint8_t data);
	
typedef struct
{
	uint32_t T_ID;			//ID of Transmitter
	uint32_t R_ID;			//ID of Receiver
	uint32_t MLen;			//Message length
	uint8_t data[46];
	uint16_t checksum;	
} Data_packet;
