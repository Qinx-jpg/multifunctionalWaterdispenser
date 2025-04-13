#ifndef __USART3_H
#define __USART3_H

#include "stm32f10x.h"                  // Device header
#include "usart/usart_com.h"

#define HC05_USART               USART3
#define HC05_BAUDRATE            38400
#define MAX_DATA_LEN 64

// 外部声明（禁止直接定义）
extern volatile uint8_t rx_buffer[MAX_DATA_LEN];
extern volatile uint8_t rx_flag;
extern volatile uint16_t rx_count;

void USART3_Config(void);
//void GPIO_Config(void);
void NVIC_Config(void);
void USART_SendString(USART_TypeDef* USARTx, char* str);
uint8_t is_numeric(volatile const uint8_t* str);

#endif


