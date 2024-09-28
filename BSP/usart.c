/*************************************************************
 * Copyright (C) 2024-09-28 Yang Haifeng. All rights reserved.
 *
 * This code is licensed under the MIT license
 *************************************************************/

#include "usart.h"
#include "stdarg.h"


/*����1��ʼ��*/
void uart_init(uint32_t bound)
{
    /*�ṹ�帳��ֵ*/
    USART_InitTypeDef USART_InitStruct = {
        .USART_BaudRate = bound,
        .USART_WordLength =USART_WordLength_8b,
        .USART_StopBits = USART_StopBits_1,
        .USART_Parity = USART_Parity_No,
        .USART_Mode = USART_Mode_Rx | USART_Mode_Tx,
        .USART_HardwareFlowControl = USART_HardwareFlowControl_None
    };
	NVIC_InitTypeDef NVIC_InitStruct = {
        .NVIC_IRQChannel = USART1_IRQn,
        .NVIC_IRQChannelPreemptionPriority = 3,
        .NVIC_IRQChannelSubPriority = 3,
        .NVIC_IRQChannelCmd = ENABLE
    };
	GPIO_InitTypeDef GPIO_InitStruct_TX = {
        .GPIO_Pin = GPIO_Pin_9,
        .GPIO_Speed = GPIO_Speed_50MHz,
        .GPIO_Mode = GPIO_Mode_AF_PP
    };
	GPIO_InitTypeDef GPIO_InitStruct_RX = {
        .GPIO_Pin = GPIO_Pin_10,
        .GPIO_Speed = GPIO_Speed_50MHz,
        .GPIO_Mode = GPIO_Mode_IN_FLOATING
    };
	 
    /*ʹ��ʱ��*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);
    
    /*��ʼ������*/
    GPIO_Init(GPIOA, &GPIO_InitStruct_TX);
    GPIO_Init(GPIOA, &GPIO_InitStruct_RX);
	
    /*�����ж����ȼ�*/
    NVIC_Init(&NVIC_InitStruct);	
  
    /*ʹ�ܴ��ں���Ӧ�ж�*/
    USART_Init(USART1,&USART_InitStruct); 
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART1,ENABLE);                   
}



/*�жϷ�����*/
void USART1_IRQHandler(void)
{
    //uint8_t temp;
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        //temp =USART_ReceiveData(USART1);
    }
}



/*���������ģʽ*/
#ifndef __MICROLIB
#pragma import(__use_no_semihosting)   
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
 
/*����֧�ֺ���*/
void _sys_exit(int x) 
{ 
	x = x; 
} 

#endif




/*�ض���*/
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0)
    {
        /*...*/
    }
    USART1->DR = (u8) ch;      
	return ch;
}



/*����һ���ֽ�*/
static inline void uart_SendByte(USART_TypeDef* USARTx,uint8_t ch)
{
    USART_SendData(USARTx,ch);
    while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE) == RESET);
}


/*�����ַ���*/
static inline void usart_SendStr(USART_TypeDef* USARTx,char *str)
{
    uint16_t k = 0;
    do{
        uart_SendByte(USARTx,str[k++]);
    }while(str[k] != '\0');
    while(USART_GetFlagStatus(USARTx,USART_FLAG_TC) == RESET);
}


/*��ʽ����ӡ���*/
__weak int print(const char *format,...)
{
    int ret;
    char String[128];
    va_list arg;
    va_start(arg,format);
    
    ret = vsprintf(String,format,arg);
    
    va_end(arg);
    usart_SendStr(USART1,String);
    
    return ret;
}



/*�������*/
void assert_failed(uint8_t* file, uint32_t line)
{
    /*User can add his own implementation to report the file name and line number*/
    print("Wrong parameters value:file %s on line %d\r\n",file,line);
    
    /*Infinite loop*/
    while(1)
    {
    }
}


