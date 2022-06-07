#ifndef __PCA9685_Init_H
#define __PCA9685_Init_H

#include "ch32v30x.h"
#include "PCA9685_USE.h"

// 这里是你PWM模块的IIC地址，默认是0x80,你需要修改为你使用的地址
#define pca_adrr 0x80
// 芯片工作模式
#define pca_mode1 0x00
// 设置芯片分频
#define pca_pre 0xFE

#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

#define LED1_ON_L 0x0A
#define LED1_ON_H 0x0B
#define LED1_OFF_L 0x0C
#define LED1_OFF_H 0x0D

#define LED2_ON_L 0x0E
#define LED2_ON_H 0x0F
#define LED2_OFF_L 0x10
#define LED2_OFF_H 0x11

#define LED3_ON_L 0x12
#define LED3_ON_H 0x13
#define LED3_OFF_L 0x14
#define LED3_OFF_H 0x15

#define LED4_ON_L 0x16
#define LED4_ON_H 0x17
#define LED4_OFF_L 0x18
#define LED4_OFF_H 0x19

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD

void M_A_Init();
void M_A_Catch();
void M_A_Put();
void PCA9685_Active(void);


#endif
