/*
 * PCA9685_USE.C
 *
 *      使用I2C1
 *
 *  Created on: 2022年5月19日
 *      Author: XUAN
 */

#include "PCA9685_USE.h"


//IIC初始化
void IIC_Init(u32 bound, u16 address)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};  //定义GPIO初始化结构体
    I2C_InitTypeDef  I2C_InitTSturcture = {0};  //定义IIC初始化结构体

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); //使能APB2总线上的GPIOB 且重映射了I2C1 所以使能AFIO
    GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);   //使能I2C1的重映射功能 本来I2C1是复用在PB6 PB7上的 经过重映射到PB8 PB9上
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);    //使能APB1总线上的外设I2C1

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;   //引脚8
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; //配置GPIO为开漏输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //配置GPIO引脚速度为50Mhz
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始化GPIO B 这里为PB8

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;   //引脚9
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; //配置GPIO为开漏输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //配置GPIO引脚速度为50Mhz
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始化GPIO B 这里为PB9

    I2C_InitTSturcture.I2C_ClockSpeed = bound;  //设置IIC时钟速度
    I2C_InitTSturcture.I2C_Mode = I2C_Mode_I2C; //设置为I2C模式
    I2C_InitTSturcture.I2C_DutyCycle = I2C_DutyCycle_16_9;  //指定时钟占空比,可选 low/high=2:1以及16:9模式
    I2C_InitTSturcture.I2C_OwnAddress1 = address;   //指定自身的I2C设备地址
    I2C_InitTSturcture.I2C_Ack = I2C_Ack_Enable;    //使能或者关闭响应 (一般都是使能)
    I2C_InitTSturcture.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; //确认是7位的地址
    I2C_Init(I2C1, &I2C_InitTSturcture); //初始化IIC

    I2C_Cmd(I2C1, ENABLE);  //使能IIC外设

    I2C_AcknowledgeConfig(I2C1, ENABLE);    //使能或者失能指定的I2C应答功能

}

/*********************************************************************
 *
 *PCA9685写操作
 *
 *参数：u8 adrr - 寄存器地址
 *     u8 data - 发送的数据
 *
 *返回：无
 *
 *启动信号-->发送从机7位地址-->发送需要操作的寄存器地址-->发送需要写入的数据(进行的操作)-->停止信号
 *
 **********************************************************************/
void pca_write(u8 adrr,u8 data)
{
    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) != RESET);  //读取BUSY标志位，等待I2C空闲后进入下列程序;

    I2C_GenerateSTART(I2C1, ENABLE);   //I2C发送起始信号

    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));//检测起始信号是否发送成功

    I2C_Send7bitAddress(I2C1, pca_adrr, I2C_Direction_Transmitter);//此功能为发送从机7位地址
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));//发送完成后从机接收并应答

    //I2C_Send7bitAddress与I2C_SendData不能混淆使用 虽然都只是发送一字节的数据 但在发送地址时仍有区别
    //  I2C_Send7bitAddress是发送设备地址选择设备通讯
    //  I2C_SendData是向设备发送一字节的数据
    //先发送设备地址选择设备-->发送设备内部寄存器地址-->发送数据操作寄存器

    if(I2C_GetFlagStatus(I2C1, I2C_FLAG_TXE) != RESET)  //等待发送完数据后才继续发送
    {
        I2C_SendData(I2C1, adrr);  //发送数据(寄存器地址)
    }
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));//检测是否成功发送数据

    if(I2C_GetFlagStatus(I2C1, I2C_FLAG_TXE) != RESET)  //等待发送完数据后才继续发送
    {
        I2C_SendData(I2C1, data);  //发送数据(操作寄存器)
    }
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));//检测是否成功发送数据

    I2C_GenerateSTOP(I2C1, ENABLE); //产生停止信号
}

/*********************************************************************
 *
 * PCA9685读操作
 *
 * 参数：u8 adrr - 寄存器地址
 *
 * 返回：u8 pca_read_data 读取到的数据
 *
 * 启动信号-->发送从机7位地址-->发送需要操作的寄存器地址-->启动信号-->发送7位器件地址+操作位-->读数据-->停止信号
 *
 **********************************************************************/
u8 pca_read(u8 adrr)
{
    u8 pca_read_data = 0;

    I2C_GenerateSTART(I2C1, ENABLE);   //I2C发送起始信号
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));//检测起始信号是否发送成功

    I2C_Send7bitAddress(I2C1, pca_adrr, I2C_Direction_Transmitter);//此功能为发送从机7位地址
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));//发送完成后从机接收并应答

    if(I2C_GetFlagStatus(I2C1, I2C_FLAG_TXE) != RESET)  //等待发送完数据后才继续发送
    {
        I2C_SendData(I2C1, adrr);  //发送数据(寄存器地址)
    }
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));//检测是否成功发送数据


    I2C_GenerateSTART(I2C1, ENABLE);   //I2C发送起始信号
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));//检测起始信号是否发送成功

    I2C_Send7bitAddress(I2C1, pca_adrr|0x01, I2C_Direction_Transmitter);//因为是发送设备地址位加操作位 所以这里需要使用 发送地址 的函数而不是使用发送数据的函数
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));//发送完成后从机接收并应答

    pca_read_data = I2C_ReceiveData(I2C1);//读数据

    I2C_GenerateSTOP(I2C1, ENABLE); //产生停止信号

    return pca_read_data;

}

/*********************************************************************
 *
 * 设置PWM频率()
 *
 **********************************************************************/
void pca_setfreq(float freq)
{
    u8 prescale,oldmode,newmode;
       double prescaleval;
       freq *= 0.915;
       prescaleval = 25000000;
       prescaleval /= 4096;
       prescaleval /= freq;
       prescaleval -= 1;
       prescale = floor(prescaleval + 0.5f);

       oldmode = pca_read(pca_mode1);

       newmode = (oldmode&0x7F) | 0x10; // sleep

       pca_write(pca_mode1, newmode); // 设置时钟前必须先进入sleep模式

       pca_write(pca_pre, prescale); // 设置分频

       pca_write(pca_mode1, oldmode); // 写入原先模式
       Delay_Ms(2);
       pca_write(pca_mode1, oldmode | 0xa1);

}

/*********************************************************************
 *
 *设置通道PWM()
 *
 **********************************************************************/
void pca_setpwm(u8 num, u32 on, u32 off)
{
    pca_write(LED0_ON_L+4*num,on);
    pca_write(LED0_ON_H+4*num,on>>8);
    pca_write(LED0_OFF_L+4*num,off);
    pca_write(LED0_OFF_H+4*num,off>>8);
}

/*********************************************************************
 *
 *PCA9685初始化()
 *有两个版本：
 *V1.0 :具有全部舵机初始化功能
 *V2.0 :取消全部舵机初始化功能 仅初始化频率
 *此处修改版本需要同步更改PCA9685_USE.h头文件
 *
 **********************************************************************/
//void PCA9685_Init(float hz,u8 angle) //初始化函数V1.0 具有全部舵机初始化功能
//{
//    u32 off=0;
//    u8 i=0;
//    pca_write(pca_mode1,0x0);
//
//    pca_setfreq(hz);//设置PWM频率
//
//    off=(u32)(102+angle*2.2);
//    // 初始化所有通道固定为指定的角度angle
//    for(i=0;i<=15;i++)
//    {
//        pca_setpwm(i,0,off);
//    }
//    Delay_Ms(500);
//}

void PCA9685_Init(float hz) //初始化函数V2.0 取消全部舵机初始化功能 仅初始化频率
{
    pca_write(pca_mode1,0x0);

    pca_setfreq(hz);//设置PWM频率

    Delay_Ms(250);
}
/*********************************************************************
 *
  *控制舵机()
 *
 *
  *  函数作用：控制舵机转动；
  *  参数：1.输出端口，可选0~15；
 *        2.起始角度，可选0~180；
 *        3.结束角度，可选0~180；
 *        4.模式选择： 0 表示函数内无延时，调用时需要在函数后另外加延时函数，且不可调速，第五个参数可填任意值；
 *                    1 表示函数内有延时，调用时不需要在函数后另外加延时函数，且不可调速，第五个参数可填任意值；
 *                    2 表示速度可调，第五个参数表示速度值；
 *        5.速度，可填大于 0 的任意值，填 1 时速度最快，数值越大，速度越小；
 *
  *  注意事项：模式 0和1 的速度比模式 2 的最大速度大；
 *
  * 一般使用的话mode选0就可以了，此时start_angle也可以写0，以及speed，只有end_angle是你要输出的角度。
 **********************************************************************/
void PCA_Set(u8 num,u8 start_angle,u8 end_angle,u8 mode,u8 speed)
{   u8 i;
u32 off=0;
switch(mode)
{

/*************  模式0  *******************/
    case 0:
    {
        off=(u32)(102+end_angle*2.2);
        pca_setpwm(num,0,off);
    }break;

/*************  模式1  *******************/
    case 1:
    {
        off=(u32)(158+end_angle*2.2);
        pca_setpwm(num,0,off);
        if(end_angle>start_angle)
        {
            Delay_Ms((u16)((end_angle-start_angle)*2.7));// 若要使用模式1或者2，可以调整这里的倍数2.7为你需要的
        }
        else
        {
            Delay_Ms((u16)((start_angle-end_angle)*2.7));
        }
    }break;

/*************  模式2  *******************/
    case 2:
    {
        if(end_angle>start_angle)
        {
            for(i=start_angle;i<=end_angle;i++)
            {
                off=(u32)(158+i*2.2);
                pca_setpwm(num,0,off);
                Delay_Ms(2);
                Delay_Us(speed*250);

            }
        }
        else if(start_angle>end_angle)
        {
            for(i=start_angle;i>=end_angle;i--)
            {
                off=(u32)(158+i*2.2);
                pca_setpwm(num,0,off);
                Delay_Ms(2);
                Delay_Us(speed*250);
            }
        }
    }break;
}}
