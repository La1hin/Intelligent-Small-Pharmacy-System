/******************************
 X轴
 定时器TIM8  PC6
 电机方向脚     PD14
 电机使能脚     PD12
 微动开关        PE2,PE3    2左3右

 Y轴
 定时器TIM1  PA8
 电机方向脚     PB6
 电机使能脚     PB7
 微动开关        PE0,PE1    0下1上
 *******************************/
#include "debug.h"
#include "string.h"
#include "Interrupt_Init.h"
#include "Motor.h"
#include "PCA9685_Init.h"
#include "Usart.h"

#define len 100
volatile u_int32_t TimeCountX = 0;
volatile u_int32_t TimeCountY = 0;
static char Receive_Str[len] = { 0 };
static char Receive_Data[len] = { 0 };
volatile int x = 0, y = 0;

volatile int Data_Flag = 0; //获取定位信息，判断是否完成抓取

//电机X复位    Motor_Flag_X电机是否复位
volatile int Motor_Flag_X = 0;
//电机Y复位    Motor_Flag_Y电机是否复位
volatile int Motor_Flag_Y = 0;

//回应服务器“1”
void Write_Server(void) {
    Usart_Send_String(USART2, "AT+MIPSEND=1,1\r\n");
    Delay_Ms(50);
    while (1) {
        if (strcmp(Receive_Str, ">\r\n")==0) {
            break;
        }
        Receive_Str[len] = 0;
    }
    while(1) {
        if (strcmp(Receive_Str, "OK\r\n")==0) {
            break;
        }
        Receive_Str[len] = 0;
        Usart_Send_String(USART2, "1\r\n");
        Delay_Ms(50);
    }
}
//等待L610初始化
void Delay_Init_L610(int i) {
    volatile static int l610_compare = 0;
    while(1) {
//        printf("l610_compare=%d\r\n",l610_compare);
        if (i==1) {
            if (strcmp(Receive_Str, "SIM READY\r\n")==0) {
                l610_compare=1;
                Usart_Send_String(USART2, "AT+GTSET=\"IPRFMT\",2\r\n"); //设置广和通字符串接收
                Delay_Ms(20);
            }
        } else {
            l610_compare=1;
            Usart_Send_String(USART2, "AT+GTSET=\"IPRFMT\",2\r\n"); //设置广和通字符串接收
            Delay_Ms(20);
        }

        if (l610_compare==1&&strcmp(Receive_Str, "OK\r\n")==0) {
            memset(Receive_Str, 0, sizeof Receive_Str);
            l610_compare=2;
            while(1) {
                Usart_Send_String(USART2, "AT+MIPOPEN=1,,\"106.52.146.151\",3500,0\r\n");
                Delay_Ms(20);
                if (strcmp(Receive_Str, "OK\r\n")==0) {
                    break;
                }
            }
        }
        if (l610_compare==2&&strcmp(Receive_Str, "MIPOPEN: 1,1\r\n")==0) {
            l610_compare=4;
            Usart_Send_String(USART2, "AT+MIPSEND=1,1\r\n");
            Delay_Ms(20);
        }
        if (l610_compare==4&&strcmp(Receive_Str, ">\r\n")==0) {
            l610_compare=5;
            Usart_Send_String(USART2, "1\r\n");
            Delay_Ms(20);
        }
        if (l610_compare==5&&strcmp(Receive_Str, "OK\r\n")==0) {
            break;
        }
    }
    return;
}
//读取TCP数据
void Receive_Usart(void) {
    int i;
    static char compare[15] = { 0 };
    if (strcmp(Receive_Str, "MIPRTCP: 1,8,Received\r\n") == 0) {
        Write_Server();
    }
    if (strcmp(Receive_Str, "MIPSTAT: 1,2\r\n") == 0) {
        Delay_Init_L610(0);
    }
    for (i = 0; i < sizeof("MIPRTCP: 1,13,") - 1; ++i) {
        compare[i] = Receive_Str[i];
    }
    if (strcmp(compare, "MIPRTCP: 1,13,") == 0) {
        int j = 0;
        for (i = sizeof("MIPRTCP: 1,13,") - 1; i < sizeof(Receive_Str); ++i) {
            Receive_Data[j++] = Receive_Str[i];
        }
        x = Receive_Data[5] - '0';
        y = Receive_Data[11] - '0';
        Data_Flag = 1;
    }
}
//接收到数据后，移动电机到指定位置
void Motor_Move() {
    volatile static u_int32_t timeCountX = 0;
    int MM_uint = 690;
    //24为X轴右边多出的2.4cm
    float mm = 52 * (9 - 2 * x) + 60;
    timeCountX = TimeCountX + MM_uint * mm;
    if (timeCountX >= 4294967295) {
        timeCountX = timeCountX - 4294967295;
    }

    ENA_X_DISENABLE();
    DIR_X_ENABLE();
    ENA_X_ENABLE();
    while(1) {
        if (TimeCountX>=timeCountX)break;
    }
    ENA_X_DISENABLE();
    Motor_Y_Move();
    DIR_X_DISENABLE();
    ENA_X_ENABLE();
    return;
}
//移动Y轴的电机
void Motor_Y_Move() {
    volatile static u_int32_t timeCountY = 0;
    int MM_uint = 690;
    //24为X轴右边多出的2.4cm
    float mm = 140 * (2 - y) + 50;
    timeCountY = TimeCountY + MM_uint * mm;
    if (timeCountY >= 4294967295) {
        timeCountY = timeCountY - 4294967295;
    }

    ENA_Y_DISENABLE();
    DIR_Y_ENABLE();
    ENA_Y_ENABLE();
    while(1) {
        if (TimeCountY>=timeCountY)break;
    }
    ENA_Y_DISENABLE();
    M_A_Init();
    M_A_Catch();
    DIR_Y_DISENABLE();
    ENA_Y_ENABLE();
//    Motor_Flag_Y=1;
//    while(1) {
//            if (Motor_Flag_Y==2) break;
//        }
    return;
}

void Delay_Init_Motor_X(void) {
    static u_int32_t timeCount = 0;
    int MM_uint = 693;
    timeCount = TimeCountX + MM_uint * 50;
    if (timeCount >= 4294967295) {
        timeCount = timeCount - 4294967295;
    }

    ENA_X_DISENABLE();
    DIR_X_ENABLE();
    ENA_X_ENABLE();
    while(1) {
        if (TimeCountX>=timeCount) {
            break;
        }
    }
    ENA_X_DISENABLE();
    DIR_X_DISENABLE();
    ENA_X_ENABLE();
    Motor_Flag_X = 1;
    while(1) {
        if (Motor_Flag_X==2)break;
    }
    ENA_X_DISENABLE();
}

void Delay_Init_Motor_Y(void) {
    static u_int32_t timeCount = 0;
    int MM_uint = 693;
    timeCount = TimeCountY + MM_uint * 50;
    if (timeCount >= 4294967295) {
        timeCount = timeCount - 4294967295;
    }

    ENA_Y_DISENABLE();
    DIR_Y_ENABLE();
    ENA_Y_ENABLE();
    while(1) {
        if (TimeCountY>=timeCount) break;
    }
    ENA_Y_DISENABLE();
    DIR_Y_DISENABLE();
    ENA_Y_ENABLE();
    Motor_Flag_Y = 1;
    while(1) {
        if (Motor_Flag_Y==2) break;
    }
    ENA_Y_DISENABLE();
}
//全部初始化
void My_Init(void) {
    //串口初始化
    Init_Usart();
    //等待L610初始化
    Delay_Init_L610(1);
    //电机初始化
    Motor_X_Init();
    //电机初始化
    Motor_Y_Init();
    //微动开关初始化
    Swich_Key_Init();
    //机械臂初始化
    PCA9685_Active();
    //等待电机X复位
    Delay_Init_Motor_X();
    //等待电机Y复位
    Delay_Init_Motor_Y();
    //电机复位后关闭中断
    Swich_Key_Close();

}

int main(void) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);

    printf("start wlw2\r\n");
    My_Init();
    while(1)
    {
        Receive_Usart();

        printf("Receive_Str=%s\r\n",Receive_Str);
        printf("Receive_Data=%s\r\n",Receive_Data);
        printf("x=%d,y=%d,Data_Flag=%d\r\n",x-'0',y-'0',Data_Flag);
        if (Data_Flag==1&&x>=0&&y>=0) {
            Swich_Key_Init();
            Motor_Move();
            while(1) {
                if (Data_Flag==0) {
                    //还要判断是否已经复位才回应
                    Write_Server();
                    Swich_Key_Close();
                    break;
                }
            }
        }
    }
}

//串口中断
volatile u_int8_t RxCnt1 = 0;
void __attribute__((interrupt("WCH-Interrupt-fast"))) USART2_IRQHandler(void) {
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != Bit_RESET) {
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
        if (RxCnt1 >= len) {
            memset(Receive_Str, 0, sizeof Receive_Str);
            Receive_Str[len] = 0;
            RxCnt1 = 0;
        }
        if (Receive_Str[RxCnt1 - 1] == '+') {
            Receive_Str[RxCnt1 - 1] = 0;
            RxCnt1 -= 1;
        }
        if ((Receive_Str[RxCnt1 - 1] == '\n' && Receive_Str[RxCnt1 - 2] == '\r')
                || (Receive_Str[RxCnt1 - 1] == ' '
                        && Receive_Str[RxCnt1 - 2] == ' ')) {
            memset(Receive_Str, 0, sizeof Receive_Str);
            Receive_Str[len] = 0;
            RxCnt1 = 0;
        }

        Receive_Str[RxCnt1++] = USART_ReceiveData(USART2);
    }

}
//微动开关中断   0-Y轴的下，1-Y轴上

void __attribute__((interrupt("WCH-Interrupt-fast"))) EXTI0_IRQHandler(void) {
    Delay_Ms(50);
    if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0) == Bit_SET) {
        printf("EXTI0_IRQHandler\r\n");
        ENA_Y_DISENABLE();
        if (Motor_Flag_Y == 1) {
            Motor_Flag_Y = 2;
        }
    }
    EXTI_ClearITPendingBit(EXTI_Line0);
    while(EXTI_GetITStatus(EXTI_Line0) == Bit_SET);
}
void __attribute__((interrupt("WCH-Interrupt-fast"))) EXTI1_IRQHandler(void) {
    Delay_Ms(50);
    if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1) == Bit_SET) {
        printf("EXTI1_IRQHandler\r\n");
        ENA_Y_DISENABLE();
        DIR_Y_DISENABLE();
        ENA_Y_ENABLE();

    }
    EXTI_ClearITPendingBit(EXTI_Line1);
    while(EXTI_GetITStatus(EXTI_Line1) == Bit_SET);
}
//微动开关中断   2-X轴的左，3-X轴右

void __attribute__((interrupt("WCH-Interrupt-fast"))) EXTI2_IRQHandler(void) {
    Delay_Ms(50);
    if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == Bit_SET) {
        printf("EXTI2_IRQHandler\r\n");
        ENA_X_DISENABLE();
        DIR_X_DISENABLE();
        ENA_X_ENABLE();

    }
    EXTI_ClearITPendingBit(EXTI_Line2);
    while(EXTI_GetITStatus(EXTI_Line2) == Bit_SET);
}
void __attribute__((interrupt("WCH-Interrupt-fast"))) EXTI3_IRQHandler(void) {
    Delay_Ms(50);
    if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == Bit_SET) {
        printf("EXTI3_IRQHandler\r\n");
        ENA_X_DISENABLE();
        if (Data_Flag == 1) {
            M_A_Put(); //放下
            M_A_Init(); //姿态初始化
            Data_Flag = 0;
        }
        if (Motor_Flag_X == 1) {
            Motor_Flag_X = 2;
        }

    }
    EXTI_ClearITPendingBit(EXTI_Line3);
    while(EXTI_GetITStatus(EXTI_Line3) == Bit_SET);
}

//定时器中断
void __attribute__((interrupt("WCH-Interrupt-fast"))) TIM1_UP_IRQHandler(void) {
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != Bit_RESET) {
        TimeCountY++;
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
    }

}
//定时器中断X
void __attribute__((interrupt("WCH-Interrupt-fast"))) TIM8_UP_IRQHandler(void) {
    if (TIM_GetITStatus(TIM8, TIM_IT_Update) != Bit_RESET) {
        TimeCountX++;
        TIM_ClearITPendingBit(TIM8, TIM_IT_Update);
    }

}
