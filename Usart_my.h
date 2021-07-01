#ifndef Usart_my_H
#define Usart_my_H
#endif

#include "stm32f7xx.h"

#define USART_ReceiveData	(USART2->RDR & 0xFF)

uint8_t RX_buf = 0, RX_flag = 0;

void USART2_IRQHandler(void);
void USART_ini(void);
uint8_t Is_TXE_Set(void);
uint8_t Is_TC_Set(void);
void USART_TransmitData(uint8_t data);
	
typedef struct
{
	uint32_t T_ID;
	uint32_t R_ID;
	uint32_t MLen;
	uint8_t data[46];
	uint16_t checksum;
} Data_packet;
