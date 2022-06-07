#ifndef __MOTOR_H
#define __MOTOR_H

#include "ch32v30x.h"


#define DIR_X_ENABLE()        GPIO_WriteBit(GPIOD,GPIO_Pin_14,Bit_SET)
#define DIR_X_DISENABLE()     GPIO_WriteBit(GPIOD,GPIO_Pin_14,Bit_RESET)
#define ENA_X_ENABLE()        GPIO_WriteBit(GPIOD,GPIO_Pin_12,Bit_SET)
#define ENA_X_DISENABLE()     GPIO_WriteBit(GPIOD,GPIO_Pin_12,Bit_RESET)

#define DIR_Y_ENABLE()        GPIO_WriteBit(GPIOB,GPIO_Pin_6,Bit_SET)
#define DIR_Y_DISENABLE()     GPIO_WriteBit(GPIOB,GPIO_Pin_6,Bit_RESET)
#define ENA_Y_ENABLE()        GPIO_WriteBit(GPIOB,GPIO_Pin_7,Bit_SET)
#define ENA_Y_DISENABLE()     GPIO_WriteBit(GPIOB,GPIO_Pin_7,Bit_RESET)

void TIM1_OutCompare_Init(u16 arr, u16 psc, u16 ccp);
void TIM8_OutCompare_Init(u16 arr, u16 psc, u16 ccp);
void MOTOR_X_GPIO_INIT(void);
void MOTOR_Y_GPIO_INIT(void);
void Swich_Key_Init(void);
void Swich_Key_Close(void);
void Motor_X_Init(void);
void Motor_Y_Init(void);

#endif
