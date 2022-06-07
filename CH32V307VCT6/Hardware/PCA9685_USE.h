/*
 * PCA9685_USE.H
 *
 *  Created on: 2022年5月19日
 *      Author: XUAN
 */
#ifndef PCA9685_USE_H
#define PCA9685_USE_H

#define Under 0
#define RArm 4
#define LArm 8
#define Hand 12

#include "ch32v30x.h"
#include "PCA9685_Init.h"
#include "math.h"

void IIC_Init(u32 bound, u16 address);
void pca_write(u8 adrr,u8 data);
u8 pca_read(u8 adrr);
void pca_setfreq(float freq);
void pca_setpwm(u8 num, u32 on, u32 off);

//void PCA9685_Init(float hz,u8 angle);//初始化函数V1.0 具有全部舵机初始化功能
void PCA9685_Init(float hz);//初始化函数V2.0 取消全部舵机初始化功能 仅初始化频率

void PCA_Set(u8 num,u8 start_angle,u8 end_angle,u8 mode,u8 speed);

#endif
