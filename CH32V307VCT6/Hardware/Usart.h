#ifndef __USART_H
#define __USART_H
#include "ch32v30x.h"

void Init_Usart(void);
void Usart_Send_Byte(USART_TypeDef* pUSARTx, uint8_t data);
void Usart_Send_String(USART_TypeDef* pUSARTx, uint8_t *str);

#endif
