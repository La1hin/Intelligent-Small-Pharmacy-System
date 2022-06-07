#ifndef __INTERRUPT_INIT_H
#define __INTERRUPT_INIT_H

#include "debug.h"
#include "Motor.h"
#include "PCA9685_Init.h"

void Motor_X_Move();
void Motor_Y_Move();
void Delay_Init_Motor_X(void);
void Delay_Init_Motor_Y(void);

#endif
