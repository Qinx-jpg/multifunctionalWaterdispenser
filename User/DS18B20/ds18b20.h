#ifndef __DS18B20_H
#define __DS18B20_H 
#include "sys/sys.h"   

/*****************辰哥单片机设计******************
											STM32
 * 文件			:	DS18B20数字温度传感器h文件                   
 * 版本			: V1.0
 * 日期			: 2024.8.13
 * MCU			:	STM32F103C8T6
 * 接口			:	见代码							
 * BILIBILI	:	辰哥单片机设计
 * CSDN			:	辰哥单片机设计
 * 作者			:	辰哥

**********************BEGIN***********************/

/***************根据自己需求更改****************/
//DS18B20引脚宏定义						

#define DS18B20_GPIO_PORT		GPIOA
#define DS18B20_GPIO_PIN		GPIO_Pin_6
#define DS18B20_GPIO_CLK   	RCC_APB2Periph_GPIOA

/*********************END**********************/
//输出状态定义
#define OUT 1
#define IN  0

//控制DS18B20引脚输出高低电平
#define DS18B20_Low  GPIO_ResetBits(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN)
#define DS18B20_High GPIO_SetBits(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN)		
		
u8 DS18B20_Init(void);//初始化DS18B20
short DS18B20_Get_Temp(void);//获取温度
void DS18B20_Start(void);//开始温度转换
void DS18B20_Write_Byte(u8 dat);//写入一个字节
u8 DS18B20_Read_Byte(void);//读出一个字节
u8 DS18B20_Read_Bit(void);//读出一个位
void DS18B20_Mode(u8 mode);//DS18B20引脚输出模式控制
u8 DS18B20_Check(void);//检测是否存在DS18B20
void DS18B20_Rst(void);//复位DS18B20   

#endif





