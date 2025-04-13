#ifndef __WATER_H
#define	__WATER_H
#include "stm32f10x.h"
#include "adc/adcx.h"
#include "delay/bsp_delay.h"
#include "math.h"

/**********************BEGIN***********************/

#define TDS_READ_TIMES	10  //TDS传感器ADC循环读取次数

/***************根据自己需求更改****************/
// TDS GPIO宏定义

#define		TDS_GPIO_CLK								RCC_APB2Periph_GPIOA
#define 	TDS_GPIO_PORT								GPIOA
#define 	TDS_GPIO_PIN								GPIO_Pin_0
#define   ADC_CHANNEL									ADC_Channel_0	// ADC 通道宏定义


/*********************END**********************/


void TDS_Init(void);
uint16_t TDS_GetData(void);
float TDS_GetData_PPM(void);

#endif /* __TDS_H */

