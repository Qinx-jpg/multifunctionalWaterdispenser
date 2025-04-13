#include "stm32f10x.h"
#include "led/bsp_gpio_led.h"
#include "key/bsp_gpio_key.h"
#include "delay/bsp_delay.h"
#include "oled/bsp_i2c_oled.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>  // 提供atoi声明 
#include <string.h>  // 提供memset声明 
#include <ctype.h>   // 提供isdigit声明 
#include "debug/bsp_debug.h"
#include "usart/usart_com.h"
#include "i2c/bsp_i2c.h"
#include "dwt/bsp_dwt.h"  
#include "TDS/tds.h"
#include "adc/adcx.h"
#include "DS18B20/ds18b20.h"
#include "sys/sys.h"
#include "flo.h"   
#include "usart3/usart3.h"	

//A0 tds输入，A1/A2 电动机驱动，A0/C13/B8/B9 按键1/2/3/4，B6/B7 屏幕输出，A6 温度计输入,A7 水流量检测输入
//u8 dakai;
int page = 0;
int heat = 0;
int cold = 0;
int pump = 0;
int tempctrl = 0;
float tempset = 20.0;

int main(void)
{
	  SystemInit();//配置系统时钟为72M	

		float data1     = 0.0;
		float temp     = 0.0;
		float flo     = 0.0;
	
		char txt1[32]   = {NULL};
		char txt2[32]   = {NULL};
		char txt3[32]   = {NULL};
		char txt4[32]   = {NULL};

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    
    DEBUG_USART_Init();
    DWT_Init();
    IIC_Init();
    OLED_Init();
		TDS_Init();
		flo_init();		
		//GPIO_Config();
    USART3_Config();
    NVIC_Config();
		
    KEY_GPIO_Config();
		//电动机驱动端口设置
    GPIO_InitTypeDef gpio_initstruct1 = {0};
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		/* IO输出状态初始化控制 */
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
		/*选择要控制的GPIO引脚、设置GPIO模式为 推挽模式、设置GPIO速率为50MHz*/
		gpio_initstruct1.GPIO_Pin    = GPIO_Pin_1;
		gpio_initstruct1.GPIO_Mode   = GPIO_Mode_Out_PP;
		gpio_initstruct1.GPIO_Speed  = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&gpio_initstruct1);
		
    GPIO_InitTypeDef gpio_initstruct2 = {0};
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		/* IO输出状态初始化控制 */
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
		/*选择要控制的GPIO引脚、设置GPIO模式为 推挽模式、设置GPIO速率为50MHz*/
		gpio_initstruct2.GPIO_Pin    = GPIO_Pin_2;
		gpio_initstruct2.GPIO_Mode   = GPIO_Mode_Out_PP;
		gpio_initstruct2.GPIO_Speed  = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&gpio_initstruct2);
		
    GPIO_InitTypeDef gpio_initstruct3 = {0};
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		/* IO输出状态初始化控制 */
		GPIO_ResetBits(GPIOA,GPIO_Pin_3);
		/*选择要控制的GPIO引脚、设置GPIO模式为 推挽模式、设置GPIO速率为50MHz*/
		gpio_initstruct3.GPIO_Pin    = GPIO_Pin_3;
		gpio_initstruct3.GPIO_Mode   = GPIO_Mode_Out_PP;
		gpio_initstruct3.GPIO_Speed  = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&gpio_initstruct3);
		
    GPIO_InitTypeDef gpio_initstruct4 = {0};
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		/* IO输出状态初始化控制 */
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		/*选择要控制的GPIO引脚、设置GPIO模式为 推挽模式、设置GPIO速率为50MHz*/
		gpio_initstruct4.GPIO_Pin    = GPIO_Pin_4;
		gpio_initstruct4.GPIO_Mode   = GPIO_Mode_Out_PP;
		gpio_initstruct4.GPIO_Speed  = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&gpio_initstruct4);
		page = 0;
		heat = 0;
		cold = 0;
		tempctrl = 0;
		tempset = 20.0;
		pump = 0;
		
    while(1)
    {
//						if(rx_flag)
//						{
//								rx_flag = 0; // 清除标志
//								
//								// 1. 原始数据显示
//								USART_SendString(USART1, "Received: ");
//								USART_SendString(USART1, (char*)rx_buffer);
//								
//								// 2. 文本转换处理
//								char display_text[MAX_DATA_LEN];
//								snprintf(display_text, sizeof(display_text), "TEXT: %s", rx_buffer);
//								OLED_ShowString_F8X16(1,1,(uint8_t*)display_text); // 假设有LCD显示函数
//								
//								// 3. 数字转换处理
//								if(is_numeric(rx_buffer)){
//										int number = atoi((const char*)(volatile const void*)rx_buffer);
//										uint32_t numeric_value = (uint32_t)number;
//										OLED_ShowString_F8X16(2,1,(uint8_t*)numeric_value); // 假设有LED数码管显示
//										}
//        
//								memset((void*)rx_buffer, 0, MAX_DATA_LEN);
//						}
					//int data = dakai;
					//sprintf(txt1,"%f",dakai);
					//OLED_ShowString_F8X16(1,1,(uint8_t*)USART_ReceiveData(HC05_USART));
				if(page == 0 && KEY_Scan(KEY6_GPIO_PORT,KEY6_GPIO_PIN,KEY_LOW_TRIGGER) == KEY_DOWN)
				{
						page = 1;
						OLED_CLS();
						DWT_DelayMs(10);
				}
				if(page == 1 && KEY_Scan(KEY6_GPIO_PORT,KEY6_GPIO_PIN,KEY_LOW_TRIGGER) == KEY_DOWN)
				{
						page = 0;
						OLED_CLS();
						DWT_DelayMs(10);
				}
//				OLED_ShowString_F8X16(3,5,(uint8_t*)page);
				if(pump == 0)
				{
						//电动机停止
							GPIO_ResetBits(GPIOA,GPIO_Pin_1);
							GPIO_ResetBits(GPIOA,GPIO_Pin_2);
							if(page == 0)
									OLED_ShowString_F8X16(0,1,(uint8_t*)"pump:off");
				}
				if(pump == 1)
				{
						//电动机启动
							GPIO_ResetBits(GPIOA,GPIO_Pin_2);
							GPIO_SetBits(GPIOA,GPIO_Pin_1);
							if(page == 0)
									OLED_ShowString_F8X16(0,1,(uint8_t*)"pump: on");
				}

				if(page == 0)
				{
						if(KEY_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN,KEY_HIGH_TRIGGER) == KEY_DOWN)
						{
									pump = 1;
						}
						if(KEY_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN,KEY_HIGH_TRIGGER) == KEY_DOWN || KEY_Scan(KEY5_GPIO_PORT,KEY5_GPIO_PIN,KEY_LOW_TRIGGER) == KEY_DOWN)
						{
									pump = 0;
						}
						temp = DS18B20_Get_Temp()/10;//校准
						//tds
						data1 = TDS_GetData_PPM() / (1 + 0.02 * (temp - 25));//温度补偿
						sprintf(txt1,"%f",data1);
						OLED_ShowString_F8X16(1,1,(uint8_t*)"TDS:");
						OLED_ShowString_F8X16(1,5,(uint8_t*)txt1);
						//温度
						
						sprintf(txt2,"%.1f",temp);
						OLED_ShowString_F8X16(2,1,(uint8_t*)"Temp:");
						OLED_ShowString_F8X16(2,6,(uint8_t*)txt2);
						OLED_ShowString_F8X16(2,11,(uint8_t*)".C");
						
						//流量
						flo = flo_read()/450.00;
						sprintf(txt3,"%.2f",flo);
						OLED_ShowString_F8X16(3,1,(uint8_t*)"Flo:");
						OLED_ShowString_F8X16(3,5,(uint8_t*)txt3);
						OLED_ShowString_F8X16(3,11,(uint8_t*)"L/s");
						
						//蓝牙
						OLED_ShowString_F8X16(0,13,(uint8_t*)"B?");

				}
				if(page == 1)
				{
						pump = 0;
					  if(tempctrl == 0 && KEY_Scan(KEY5_GPIO_PORT,KEY5_GPIO_PIN,KEY_LOW_TRIGGER) == KEY_DOWN)
						{
								tempctrl = 1;
								DWT_DelayMs(25);
						}
					  if(tempctrl == 1 && KEY_Scan(KEY5_GPIO_PORT,KEY5_GPIO_PIN,KEY_LOW_TRIGGER) == KEY_DOWN)
						{
								tempctrl = 0;
								DWT_DelayMs(25);
						}
						if(tempctrl == 0)
						{
								OLED_ShowString_F8X16(0,1,(uint8_t*)"tempctrl:off");
						}
						else
						{
								OLED_ShowString_F8X16(0,1,(uint8_t*)"tempctrl: on");
						}
						if(KEY_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN,KEY_HIGH_TRIGGER) == KEY_DOWN)
						{
							tempset --;
						}
						if(KEY_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN,KEY_HIGH_TRIGGER) == KEY_DOWN)
						{
							tempset ++;
						}
						OLED_ShowString_F8X16(1,1,(uint8_t*)"Tset:");
						sprintf(txt4,"%.1f",tempset);
						OLED_ShowString_F8X16(1,6,(uint8_t*)txt4);
						OLED_ShowString_F8X16(1,11,(uint8_t*)".C");
				}
				
				if(tempctrl == 1)
				{
						temp = DS18B20_Get_Temp()/10;//校准
						if(temp > tempset)
						{
								heat = 0;
								cold = 1;
						}
						if(temp < tempset)
						{
								heat = 1;
								cold = 0;
						}
				}
				if(tempctrl == 0)
				{
						heat = 0;
						cold = 0;
				}
				if(heat == 1)
				{
						if(page == 1)
								OLED_ShowString_F8X16(2,1,(uint8_t*)"heat: on");
						GPIO_SetBits(GPIOA,GPIO_Pin_3);
				}
				else
				{
						if(page == 1)
								OLED_ShowString_F8X16(2,1,(uint8_t*)"heat:off");
						GPIO_ResetBits(GPIOA,GPIO_Pin_3);
				}
				if(cold == 1)
				{
						if(page == 1)
								OLED_ShowString_F8X16(3,1,(uint8_t*)"cold: on");
						GPIO_SetBits(GPIOA,GPIO_Pin_4);

				}
				else
				{
						if(page == 1)
								OLED_ShowString_F8X16(3,1,(uint8_t*)"cold:off");
						GPIO_ResetBits(GPIOA,GPIO_Pin_4);
				}
    }
}

