/**
  ******************************************************************************
  * @file       usart_com.c
  * @author     embedfire
  * @version     V1.0
  * @date        2024
  * @brief   重定向C库printf函数到usart端口
  ******************************************************************************
  */
  
  
#include "usart/usart_com.h"
#include "debug/bsp_debug.h"

/**
 * @brief 发送一个字节函数
 * @param pusartx：USARTx(x=1,2,3)/UARTx(x=4,5) 
 * @param ch:要发送的数据
 * @note  无
 * @retval 无
 */
void USARTX_SendByte(USART_TypeDef *pusartx, uint8_t ch)
{
    /* 等待发送完成 */
    while (USART_GetFlagStatus(pusartx, USART_FLAG_TC) == RESET);
    
    /* 发送一个字节数据到 pusartx */
    USART_SendData(pusartx,ch);
    
    /* 等待发送数据寄存器为空 */
    while (USART_GetFlagStatus(pusartx, USART_FLAG_TXE) == RESET);

}

/**
 * @brief 发送8位的数组函数
 * @param pusartx：USARTx(x=1,2,3)/UARTx(x=4,5)  
 * @param array:要发送的数组
 * @param num:数组大小
 * @note  无
 * @retval 无
 */
void USARTX_SendArray(USART_TypeDef *pusartx, uint8_t *array, uint32_t num)
{
    /* 等待发送完成 */
    while (USART_GetFlagStatus(pusartx, USART_FLAG_TC) == RESET);
    
    /* 发送多个字节数据到 pusartx */
    for (uint32_t i = 0; i < num; i++)
    {
        /* 发送一个字节数据到 pusartx */
        USART_SendData(pusartx,array[i]);
        
        /* 等待发送数据寄存器为空 */
        while (USART_GetFlagStatus(pusartx, USART_FLAG_TXE) == RESET);
    }

}

/**
 * @brief 发送字符串函数
 * @param pusartx：USARTx(x=1,2,3)/UARTx(x=4,5) 
 * @param str:要发送的数据
 * @note  无
 * @retval 无
 */
void USARTX_SendString(USART_TypeDef *pusartx, char *str)
{
    uint32_t k = 0;
    
    /* 等待发送完成 */
    while (USART_GetFlagStatus(pusartx, USART_FLAG_TC) == RESET);
    
    do
    {
        /* 发送一个字节数据到 pusartx */
        USART_SendData(pusartx,*(str + k));
        k++;
        
        /* 等待发送数据寄存器为空 */
        while (USART_GetFlagStatus(pusartx, USART_FLAG_TXE) == RESET);
        
    } while (*(str + k) != '\0');

}

/**
 * @brief 将一个字符写入到文件中,重定向c库函数printf到串口，重定向后可使用printf函数
 * @param ch: 要写入的字符
 * @param f: 指向FILE结构的指针
 * @note  无
 * @retval 成功，返回该字符
 */
int fputc(int ch, FILE *f)
{
    /* 等待发送完成 */
    while (USART_GetFlagStatus(DEBUG_USARTX, USART_FLAG_TC) == RESET);
    
    /* 发送一个字节数据到串口 */
    USART_SendData(DEBUG_USARTX, (uint8_t)ch);
    
    /* 等待发送数据寄存器为空 */
    while (USART_GetFlagStatus(DEBUG_USARTX, USART_FLAG_TXE) == RESET);

    return (ch);
}

/*****************************END OF FILE***************************************/

