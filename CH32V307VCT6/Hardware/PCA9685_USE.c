/*
 * PCA9685_USE.C
 *
 *      ʹ��I2C1
 *
 *  Created on: 2022��5��19��
 *      Author: XUAN
 */

#include "PCA9685_USE.h"


//IIC��ʼ��
void IIC_Init(u32 bound, u16 address)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};  //����GPIO��ʼ���ṹ��
    I2C_InitTypeDef  I2C_InitTSturcture = {0};  //����IIC��ʼ���ṹ��

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); //ʹ��APB2�����ϵ�GPIOB ����ӳ����I2C1 ����ʹ��AFIO
    GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);   //ʹ��I2C1����ӳ�书�� ����I2C1�Ǹ�����PB6 PB7�ϵ� ������ӳ�䵽PB8 PB9��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);    //ʹ��APB1�����ϵ�����I2C1

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;   //����8
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; //����GPIOΪ��©���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //����GPIO�����ٶ�Ϊ50Mhz
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��GPIO B ����ΪPB8

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;   //����9
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; //����GPIOΪ��©���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //����GPIO�����ٶ�Ϊ50Mhz
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��GPIO B ����ΪPB9

    I2C_InitTSturcture.I2C_ClockSpeed = bound;  //����IICʱ���ٶ�
    I2C_InitTSturcture.I2C_Mode = I2C_Mode_I2C; //����ΪI2Cģʽ
    I2C_InitTSturcture.I2C_DutyCycle = I2C_DutyCycle_16_9;  //ָ��ʱ��ռ�ձ�,��ѡ low/high=2:1�Լ�16:9ģʽ
    I2C_InitTSturcture.I2C_OwnAddress1 = address;   //ָ�������I2C�豸��ַ
    I2C_InitTSturcture.I2C_Ack = I2C_Ack_Enable;    //ʹ�ܻ��߹ر���Ӧ (һ�㶼��ʹ��)
    I2C_InitTSturcture.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; //ȷ����7λ�ĵ�ַ
    I2C_Init(I2C1, &I2C_InitTSturcture); //��ʼ��IIC

    I2C_Cmd(I2C1, ENABLE);  //ʹ��IIC����

    I2C_AcknowledgeConfig(I2C1, ENABLE);    //ʹ�ܻ���ʧ��ָ����I2CӦ����

}

/*********************************************************************
 *
 *PCA9685д����
 *
 *������u8 adrr - �Ĵ�����ַ
 *     u8 data - ���͵�����
 *
 *���أ���
 *
 *�����ź�-->���ʹӻ�7λ��ַ-->������Ҫ�����ļĴ�����ַ-->������Ҫд�������(���еĲ���)-->ֹͣ�ź�
 *
 **********************************************************************/
void pca_write(u8 adrr,u8 data)
{
    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) != RESET);  //��ȡBUSY��־λ���ȴ�I2C���к�������г���;

    I2C_GenerateSTART(I2C1, ENABLE);   //I2C������ʼ�ź�

    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));//�����ʼ�ź��Ƿ��ͳɹ�

    I2C_Send7bitAddress(I2C1, pca_adrr, I2C_Direction_Transmitter);//�˹���Ϊ���ʹӻ�7λ��ַ
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));//������ɺ�ӻ����ղ�Ӧ��

    //I2C_Send7bitAddress��I2C_SendData���ܻ���ʹ�� ��Ȼ��ֻ�Ƿ���һ�ֽڵ����� ���ڷ��͵�ַʱ��������
    //  I2C_Send7bitAddress�Ƿ����豸��ַѡ���豸ͨѶ
    //  I2C_SendData�����豸����һ�ֽڵ�����
    //�ȷ����豸��ַѡ���豸-->�����豸�ڲ��Ĵ�����ַ-->�������ݲ����Ĵ���

    if(I2C_GetFlagStatus(I2C1, I2C_FLAG_TXE) != RESET)  //�ȴ����������ݺ�ż�������
    {
        I2C_SendData(I2C1, adrr);  //��������(�Ĵ�����ַ)
    }
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));//����Ƿ�ɹ���������

    if(I2C_GetFlagStatus(I2C1, I2C_FLAG_TXE) != RESET)  //�ȴ����������ݺ�ż�������
    {
        I2C_SendData(I2C1, data);  //��������(�����Ĵ���)
    }
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));//����Ƿ�ɹ���������

    I2C_GenerateSTOP(I2C1, ENABLE); //����ֹͣ�ź�
}

/*********************************************************************
 *
 * PCA9685������
 *
 * ������u8 adrr - �Ĵ�����ַ
 *
 * ���أ�u8 pca_read_data ��ȡ��������
 *
 * �����ź�-->���ʹӻ�7λ��ַ-->������Ҫ�����ļĴ�����ַ-->�����ź�-->����7λ������ַ+����λ-->������-->ֹͣ�ź�
 *
 **********************************************************************/
u8 pca_read(u8 adrr)
{
    u8 pca_read_data = 0;

    I2C_GenerateSTART(I2C1, ENABLE);   //I2C������ʼ�ź�
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));//�����ʼ�ź��Ƿ��ͳɹ�

    I2C_Send7bitAddress(I2C1, pca_adrr, I2C_Direction_Transmitter);//�˹���Ϊ���ʹӻ�7λ��ַ
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));//������ɺ�ӻ����ղ�Ӧ��

    if(I2C_GetFlagStatus(I2C1, I2C_FLAG_TXE) != RESET)  //�ȴ����������ݺ�ż�������
    {
        I2C_SendData(I2C1, adrr);  //��������(�Ĵ�����ַ)
    }
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));//����Ƿ�ɹ���������


    I2C_GenerateSTART(I2C1, ENABLE);   //I2C������ʼ�ź�
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));//�����ʼ�ź��Ƿ��ͳɹ�

    I2C_Send7bitAddress(I2C1, pca_adrr|0x01, I2C_Direction_Transmitter);//��Ϊ�Ƿ����豸��ַλ�Ӳ���λ ����������Ҫʹ�� ���͵�ַ �ĺ���������ʹ�÷������ݵĺ���
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));//������ɺ�ӻ����ղ�Ӧ��

    pca_read_data = I2C_ReceiveData(I2C1);//������

    I2C_GenerateSTOP(I2C1, ENABLE); //����ֹͣ�ź�

    return pca_read_data;

}

/*********************************************************************
 *
 * ����PWMƵ��()
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

       pca_write(pca_mode1, newmode); // ����ʱ��ǰ�����Ƚ���sleepģʽ

       pca_write(pca_pre, prescale); // ���÷�Ƶ

       pca_write(pca_mode1, oldmode); // д��ԭ��ģʽ
       Delay_Ms(2);
       pca_write(pca_mode1, oldmode | 0xa1);

}

/*********************************************************************
 *
 *����ͨ��PWM()
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
 *PCA9685��ʼ��()
 *�������汾��
 *V1.0 :����ȫ�������ʼ������
 *V2.0 :ȡ��ȫ�������ʼ������ ����ʼ��Ƶ��
 *�˴��޸İ汾��Ҫͬ������PCA9685_USE.hͷ�ļ�
 *
 **********************************************************************/
//void PCA9685_Init(float hz,u8 angle) //��ʼ������V1.0 ����ȫ�������ʼ������
//{
//    u32 off=0;
//    u8 i=0;
//    pca_write(pca_mode1,0x0);
//
//    pca_setfreq(hz);//����PWMƵ��
//
//    off=(u32)(102+angle*2.2);
//    // ��ʼ������ͨ���̶�Ϊָ���ĽǶ�angle
//    for(i=0;i<=15;i++)
//    {
//        pca_setpwm(i,0,off);
//    }
//    Delay_Ms(500);
//}

void PCA9685_Init(float hz) //��ʼ������V2.0 ȡ��ȫ�������ʼ������ ����ʼ��Ƶ��
{
    pca_write(pca_mode1,0x0);

    pca_setfreq(hz);//����PWMƵ��

    Delay_Ms(250);
}
/*********************************************************************
 *
  *���ƶ��()
 *
 *
  *  �������ã����ƶ��ת����
  *  ������1.����˿ڣ���ѡ0~15��
 *        2.��ʼ�Ƕȣ���ѡ0~180��
 *        3.�����Ƕȣ���ѡ0~180��
 *        4.ģʽѡ�� 0 ��ʾ����������ʱ������ʱ��Ҫ�ں������������ʱ�������Ҳ��ɵ��٣������������������ֵ��
 *                    1 ��ʾ����������ʱ������ʱ����Ҫ�ں������������ʱ�������Ҳ��ɵ��٣������������������ֵ��
 *                    2 ��ʾ�ٶȿɵ��������������ʾ�ٶ�ֵ��
 *        5.�ٶȣ�������� 0 ������ֵ���� 1 ʱ�ٶ���죬��ֵԽ���ٶ�ԽС��
 *
  *  ע�����ģʽ 0��1 ���ٶȱ�ģʽ 2 ������ٶȴ�
 *
  * һ��ʹ�õĻ�modeѡ0�Ϳ����ˣ���ʱstart_angleҲ����д0���Լ�speed��ֻ��end_angle����Ҫ����ĽǶȡ�
 **********************************************************************/
void PCA_Set(u8 num,u8 start_angle,u8 end_angle,u8 mode,u8 speed)
{   u8 i;
u32 off=0;
switch(mode)
{

/*************  ģʽ0  *******************/
    case 0:
    {
        off=(u32)(102+end_angle*2.2);
        pca_setpwm(num,0,off);
    }break;

/*************  ģʽ1  *******************/
    case 1:
    {
        off=(u32)(158+end_angle*2.2);
        pca_setpwm(num,0,off);
        if(end_angle>start_angle)
        {
            Delay_Ms((u16)((end_angle-start_angle)*2.7));// ��Ҫʹ��ģʽ1����2�����Ե�������ı���2.7Ϊ����Ҫ��
        }
        else
        {
            Delay_Ms((u16)((start_angle-end_angle)*2.7));
        }
    }break;

/*************  ģʽ2  *******************/
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
