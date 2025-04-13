#include "usart3/usart3.h"	
#include <stdlib.h>  // 提供atoi声明 
#include <string.h>  // 提供memset声明 
#include <ctype.h>   // 提供isdigit声明 
//串口1中断服务程序
	//初始化 IO 串口 3
	//pclk1:PCLK1 时钟频率(Mhz)
	//bound:波特率  
	
uint8_t rx_index = 0;
// 实际定义（仅在此文件定义一次）
volatile uint8_t rx_buffer[MAX_DATA_LEN] = {0};
volatile uint8_t rx_flag = 0;
volatile uint16_t rx_count = 0;

void USART3_Config()
{ 
		GPIO_InitTypeDef GPIO_InitStructure;
    
    // 使能GPIOB和USART3时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    // 配置PB10为复用推挽输出（TX）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // 配置PB11为浮空输入（RX）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		USART_InitTypeDef USART_InitStructure;

    USART_InitStructure.USART_BaudRate = HC05_BAUDRATE;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(HC05_USART, &USART_InitStructure);
    USART_Cmd(HC05_USART, ENABLE);
    USART_ITConfig(HC05_USART, USART_IT_RXNE, ENABLE);

}

// 中断服务程序
void USART3_IRQHandler(void)
{
		if(USART_GetITStatus(HC05_USART, USART_IT_RXNE) != RESET)
    {
        uint8_t data = USART_ReceiveData(HC05_USART);
        
        if(rx_count < MAX_DATA_LEN-1){
            rx_buffer[rx_count++] = data;
            
            // 检测结束符（根据实际协议调整）
            if(data == '\n' || data == '\r'){
                rx_buffer[rx_count] = '\0'; // 添加字符串终止符
                rx_flag = 1;                // 置位接收完成标志
                rx_count = 0;
            }
        }
        else{
            // 缓冲区溢出处理
            rx_count = 0;
            memset((void*)rx_buffer, 0, MAX_DATA_LEN);
        }
    }
}
void NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
// 辅助函数实现
void USART_SendString(USART_TypeDef* USARTx, char* str)
{
    while(*str){
        USART_SendData(USARTx, *str++);
        while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
    }
}

uint8_t is_numeric(volatile const uint8_t* str)  // 匹配声明 
{
    while(*str){
        if(!isdigit(*str) && *str != '-' && *str != '.') 
            return 0;
        str++;
    }
    return 1;
}
