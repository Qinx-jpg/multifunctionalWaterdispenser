#include "TDS/tds.h"
#include "dwt/bsp_dwt.h"   

/*****************辰哥单片机设计******************
											STM32
 * 文件			:	TDS电导率传感器c文件                   
 * 版本			: V1.0
 * 日期			: 2024.2.2
 * MCU			:	STM32F103C8T6
 * 接口			:	见代码							
 * BILIBILI	:	辰哥单片机设计
 * CSDN			:	辰哥单片机设计
 * 作者			:	辰哥

**********************BEGIN***********************/

void TDS_Init(void)
{
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		
		RCC_APB2PeriphClockCmd (TDS_GPIO_CLK, ENABLE );	// 打开 ADC IO端口时钟
		GPIO_InitStructure.GPIO_Pin = TDS_GPIO_PIN;					// 配置 ADC IO 引脚模式
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		// 设置为模拟输入
		
		GPIO_Init(TDS_GPIO_PORT, &GPIO_InitStructure);				// 初始化 ADC IO

		ADCx_Init();
	}

}


uint16_t TDS_ADC_Read(void)
{
	//设置指定ADC的规则组通道，采样时间
	return ADC_GetValue(ADC_CHANNEL, ADC_SampleTime_55Cycles5);
}


uint16_t TDS_GetData(void)
{
	

	uint32_t  tempData = 0;
	for (uint8_t i = 0; i < TDS_READ_TIMES; i++)
	{
		tempData += TDS_ADC_Read();
		DWT_DelayMs(5);
	}

	tempData /= TDS_READ_TIMES;
	return tempData;
	
}

float TDS_GetData_PPM(void)
{
	float  tempData = 0;
	float TDS_DAT;

	for (uint8_t i = 0; i < TDS_READ_TIMES; i++)
	{
		tempData += TDS_ADC_Read();
		DWT_DelayMs(5);
	}
	tempData /= TDS_READ_TIMES;
	
	TDS_DAT = (tempData/4095.0)*3.3;
	TDS_DAT = 66.71*TDS_DAT*TDS_DAT*TDS_DAT-127.93*TDS_DAT*TDS_DAT+428.7*TDS_DAT;
	if(TDS_DAT<20) TDS_DAT = 0;
	
	return TDS_DAT;

}



