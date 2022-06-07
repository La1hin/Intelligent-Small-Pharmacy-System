#include "Motor.h"

//TIM1   A8  Y
//TIM8   C6  X
//优先级   0   0
void TIM1_OutCompare_Init(u16 arr, u16 psc, u16 ccp) {
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };
    TIM_OCInitTypeDef TIM_OCInitStructure = { 0 };
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = { 0 };
    NVIC_InitTypeDef NVIC_InitStructrue = { 0 };

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_TIM1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOA, &GPIO_InitStructure);

    TIM_TimeBaseInitStructure.TIM_Period = arr - 1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc - 1;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit( TIM1, &TIM_TimeBaseInitStructure);


    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = ccp - 1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init( TIM1, &TIM_OCInitStructure);

    NVIC_InitStructrue.NVIC_IRQChannel = TIM1_UP_IRQn;
    NVIC_InitStructrue.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructrue.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructrue.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStructrue);

    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

    TIM_CtrlPWMOutputs(TIM1, ENABLE);
    TIM_OC1PreloadConfig( TIM1, TIM_OCPreload_Disable);
    TIM_ARRPreloadConfig( TIM1, ENABLE);
    TIM_Cmd( TIM1, ENABLE);
}
void TIM8_OutCompare_Init(u16 arr, u16 psc, u16 ccp) {
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };
    TIM_OCInitTypeDef TIM_OCInitStructure = { 0 };
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = { 0 };
    NVIC_InitTypeDef NVIC_InitStructrue = { 0 };

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC | RCC_APB2Periph_TIM8, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOC, &GPIO_InitStructure);

    TIM_TimeBaseInitStructure.TIM_Period = arr - 1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc - 1;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit( TIM8, &TIM_TimeBaseInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = ccp - 1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init( TIM8, &TIM_OCInitStructure);

    NVIC_InitStructrue.NVIC_IRQChannel = TIM8_UP_IRQn;
    NVIC_InitStructrue.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructrue.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructrue.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStructrue);

    TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE);

    TIM_CtrlPWMOutputs(TIM8, ENABLE);
    TIM_OC1PreloadConfig( TIM8, TIM_OCPreload_Disable);
    TIM_ARRPreloadConfig( TIM8, ENABLE);
    TIM_Cmd( TIM8, ENABLE);
}

//TIM1 Y  方向 PB6  使能 PB7
//TIM8 X  反向PD14  使能PD12
void MOTOR_Y_GPIO_INIT(void) {
    GPIO_InitTypeDef GPIO_InitStructrue;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    //方向6和使能7脚定义
    GPIO_InitStructrue.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructrue.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructrue.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructrue);

}
void MOTOR_X_GPIO_INIT(void) {
    GPIO_InitTypeDef GPIO_InitStructrue;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    //方向14和使能12脚定义
    GPIO_InitStructrue.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructrue.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_12;
    GPIO_InitStructrue.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructrue);

}

//微动开关   X     PE2,PE3    2左3右
//微动开关   Y     PE0,PE1    0下1上
//优先级  2 1
void Swich_Key_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructrue;
    EXTI_InitTypeDef EXIT_InitStucture;
    NVIC_InitTypeDef NVIC_InitStucture;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitStructrue.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructrue.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructrue.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructrue);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource0);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource1);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource3);

    EXIT_InitStucture.EXTI_Line = EXTI_Line0;
    EXIT_InitStucture.EXTI_LineCmd = ENABLE;
    EXIT_InitStucture.EXTI_Mode = EXTI_Mode_Interrupt;
    EXIT_InitStucture.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Init(&EXIT_InitStucture);

    EXIT_InitStucture.EXTI_Line = EXTI_Line1;
    EXTI_Init(&EXIT_InitStucture);
    EXIT_InitStucture.EXTI_Line = EXTI_Line2;
    EXTI_Init(&EXIT_InitStucture);
    EXIT_InitStucture.EXTI_Line = EXTI_Line3;
    EXTI_Init(&EXIT_InitStucture);

    NVIC_InitStucture.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStucture.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStucture.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStucture.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStucture);

    NVIC_InitStucture.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_Init(&NVIC_InitStucture);
    NVIC_InitStucture.NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_Init(&NVIC_InitStucture);
    NVIC_InitStucture.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_Init(&NVIC_InitStucture);
}
//关闭中断
void Swich_Key_Close(void) {
    GPIO_InitTypeDef GPIO_InitStructrue;
    EXTI_InitTypeDef EXIT_InitStucture;
    NVIC_InitTypeDef NVIC_InitStucture;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitStructrue.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructrue.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructrue.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructrue);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource0);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource1);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource3);

    EXIT_InitStucture.EXTI_Line = EXTI_Line0;
    EXIT_InitStucture.EXTI_LineCmd = DISABLE;
    EXIT_InitStucture.EXTI_Mode = EXTI_Mode_Interrupt;
    EXIT_InitStucture.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Init(&EXIT_InitStucture);

    EXIT_InitStucture.EXTI_Line = EXTI_Line1;
    EXTI_Init(&EXIT_InitStucture);
    EXIT_InitStucture.EXTI_Line = EXTI_Line2;
    EXTI_Init(&EXIT_InitStucture);
    EXIT_InitStucture.EXTI_Line = EXTI_Line3;
    EXTI_Init(&EXIT_InitStucture);

    NVIC_InitStucture.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStucture.NVIC_IRQChannelCmd = DISABLE;
    NVIC_Init(&NVIC_InitStucture);

    NVIC_InitStucture.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_Init(&NVIC_InitStucture);
    NVIC_InitStucture.NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_Init(&NVIC_InitStucture);
    NVIC_InitStucture.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_Init(&NVIC_InitStucture);
}
void Motor_X_Init(void){
    TIM8_OutCompare_Init(30,200,15);
    MOTOR_X_GPIO_INIT();
}

void Motor_Y_Init(void){
    TIM1_OutCompare_Init(20,200,10);
    MOTOR_Y_GPIO_INIT();
}

