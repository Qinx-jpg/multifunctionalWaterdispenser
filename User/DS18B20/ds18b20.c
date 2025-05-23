#include "DS18B20/ds18b20.h"
#include "dwt/bsp_dwt.h"   

/*****************辰哥单片机设计******************
											STM32
 * 文件			:	DS18B20数字温度传感器c文件                   
 * 版本			: V1.0
 * 日期			: 2024.8.13
 * MCU			:	STM32F103C8T6
 * 接口			:	见DS18B20.h文件							
 * BILIBILI	:	辰哥单片机设计
 * CSDN			:	辰哥单片机设计
 * 作者			:	辰哥

**********************BEGIN***********************/			

void DS18B20_Rst(void)	   
{                 
		DS18B20_Mode(OUT); 	//SET OUTPUT
    DS18B20_Low; 				//拉低DQ
    DWT_DelayUs(750);    	//拉低750us
    DS18B20_High; 			//DQ=1 
		DWT_DelayUs(15);     	//15US
}
//等待DS18B20的回应
//返回1:未检测到DS18B20的存在
//返回0:存在
u8 DS18B20_Check(void) 	   
{   
	u8 retry=0;
	DS18B20_Mode(IN);	//SET  INPUT	 
    while (GPIO_ReadInputDataBit(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN)&&retry<200)
	{
		retry++;
		DWT_DelayUs(1);
	};	 
	if(retry>=200)return 1;
	else retry=0;
    while (!GPIO_ReadInputDataBit(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN)&&retry<240)
	{
		retry++;
		DWT_DelayUs(1);
	};
	if(retry>=240)return 1;	    
	return 0;
}
//从DS18B20读取一个位
//返回值：1/0
u8 DS18B20_Read_Bit(void) 	 
{
    u8 data;
	DS18B20_Mode(OUT);	//SET OUTPUT
    DS18B20_Low; 
	DWT_DelayUs(2);
    DS18B20_High; 
	DS18B20_Mode(IN);	//SET INPUT
	DWT_DelayUs(12);
	if(GPIO_ReadInputDataBit(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN))data=1;
    else data=0;	 
    DWT_DelayUs(50);           
    return data;
}
//从DS18B20读取一个字节
//返回值：读到的数据
u8 DS18B20_Read_Byte(void)     
{        
    u8 i,j,dat;
    dat=0;
	for (i=1;i<=8;i++) 
	{
        j=DS18B20_Read_Bit();
        dat=(j<<7)|(dat>>1);
    }						    
    return dat;
}
//写一个字节到DS18B20
//dat：要写入的字节
void DS18B20_Write_Byte(u8 dat)     
 {             
    u8 j;
    u8 testb;
	DS18B20_Mode(OUT);	//SET OUTPUT;
    for (j=1;j<=8;j++) 
	{
        testb=dat&0x01;
        dat=dat>>1;
        if (testb) 
        {
            DS18B20_Low;	// Write 1
            DWT_DelayUs(2);                            
            DS18B20_High;
            DWT_DelayUs(60);             
        }
        else 
        {
            DS18B20_Low;	// Write 0
            DWT_DelayUs(60);             
            DS18B20_High;
            DWT_DelayUs(2);                          
        }
    }
}
//开始温度转换
void DS18B20_Start(void) 
{   						               
    DS18B20_Rst();	   
		DS18B20_Check();	 
    DS18B20_Write_Byte(0xcc);	// skip rom
    DS18B20_Write_Byte(0x44);	// convert
} 

//初始化DS18B20的IO口 DQ 同时检测DS的存在
//返回1:不存在
//返回0:存在    	 
u8 DS18B20_Init(void)
{
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(DS18B20_GPIO_CLK, ENABLE);	 //使能PORTA口时钟 
	
 	GPIO_InitStructure.GPIO_Pin = DS18B20_GPIO_PIN;				//PORTA.6 推挽输出
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(DS18B20_GPIO_PORT, &GPIO_InitStructure);

 	GPIO_SetBits(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN);    //输出1

	DS18B20_Rst();

	return DS18B20_Check();
}  
//从ds18b20得到温度值
//精度：0.1C
//返回值：温度值 （-550~1250） 
short DS18B20_Get_Temp(void)
{
    u8 temp;
    u8 TL,TH;
	short tem;
    DS18B20_Start ();  			// ds1820 start convert
    DS18B20_Rst();
    DS18B20_Check();	 
    DS18B20_Write_Byte(0xcc);	// skip rom
    DS18B20_Write_Byte(0xbe);	// convert	    
    TL=DS18B20_Read_Byte(); 	// LSB   
    TH=DS18B20_Read_Byte(); 	// MSB  
	    	  
    if(TH>7)
    {
        TH=~TH;
        TL=~TL; 
        temp=0;					//温度为负  
    }else temp=1;				//温度为正	  	  
    tem=TH; 					//获得高八位
    tem<<=8;    
    tem+=TL;					//获得底八位
    tem=(float)tem*0.625;		//转换     
	if(temp)return tem; 		//返回温度值
	else return -tem;    
}

void DS18B20_Mode(u8 mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(DS18B20_GPIO_CLK, ENABLE);	 //使能PORTA口时钟
	
	if(mode)
	{
		GPIO_InitStructure.GPIO_Pin = DS18B20_GPIO_PIN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	}
	else
	{
		GPIO_InitStructure.GPIO_Pin =  DS18B20_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	}
	GPIO_Init(DS18B20_GPIO_PORT, &GPIO_InitStructure);
}


 
