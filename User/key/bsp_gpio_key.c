#include "key/bsp_gpio_key.h"
#include "delay/bsp_delay.h"

/**
  * @brief  初始化控制 KEY 的IO
  * @param  无
  * @retval 无
  */
void KEY_GPIO_Config(void)
{
    /* 定义一个 GPIO 结构体 */
    GPIO_InitTypeDef gpio_initstruct = {0};
    
/**************************** 核心板载按键 *****************************/   
#if 1    
    
    /* 开启 KEY 相关的GPIO外设/端口时钟 */
    RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK_PORT,ENABLE);
    
    /* IO输出状态初始化控制 */
    GPIO_SetBits(KEY1_GPIO_PORT,KEY1_GPIO_PIN);
    
    /*选择要控制的GPIO引脚、设置GPIO模式为 浮空输入、设置GPIO速率为50MHz*/
    gpio_initstruct.GPIO_Pin    = KEY1_GPIO_PIN;
    gpio_initstruct.GPIO_Mode   = GPIO_Mode_IN_FLOATING;
    gpio_initstruct.GPIO_Speed  = GPIO_Speed_50MHz;
    GPIO_Init(KEY1_GPIO_PORT,&gpio_initstruct);
   
#endif 
    
#if 1    
    
    /* 开启 KEY 相关的GPIO外设/端口时钟 */
    RCC_APB2PeriphClockCmd(KEY2_GPIO_CLK_PORT,ENABLE);
    
    /* IO输出状态初始化控制 */
    GPIO_SetBits(KEY2_GPIO_PORT,KEY2_GPIO_PIN);
    
    /*选择要控制的GPIO引脚、设置GPIO模式为 浮空输入、设置GPIO速率为50MHz*/
    gpio_initstruct.GPIO_Pin    = KEY2_GPIO_PIN;
    gpio_initstruct.GPIO_Mode   = GPIO_Mode_IN_FLOATING;
    gpio_initstruct.GPIO_Speed  = GPIO_Speed_50MHz;
    GPIO_Init(KEY2_GPIO_PORT,&gpio_initstruct);
   
#endif 

/**************************** 用户自定义扩展按键 *****************************/

//#if 1    
//    
//    /* 开启 KEY 相关的GPIO外设/端口时钟 */
//    RCC_APB2PeriphClockCmd(KEY3_GPIO_CLK_PORT,ENABLE);
//    
//    /* IO输出状态初始化控制 */
//    GPIO_SetBits(KEY3_GPIO_PORT,KEY3_GPIO_PIN);
//    
//    /*选择要控制的GPIO引脚、设置GPIO模式为 下拉输入、设置GPIO速率为50MHz*/
//    gpio_initstruct.GPIO_Pin    = KEY3_GPIO_PIN;
//    gpio_initstruct.GPIO_Mode   = GPIO_Mode_IPD;
//    gpio_initstruct.GPIO_Speed  = GPIO_Speed_50MHz;
//    GPIO_Init(KEY3_GPIO_PORT,&gpio_initstruct);
//   
//#endif 

//#if 1    
//    
//    /* 开启 KEY 相关的GPIO外设/端口时钟 */
//    RCC_APB2PeriphClockCmd(KEY4_GPIO_CLK_PORT,ENABLE);
//    
//    /* IO输出状态初始化控制 */
//    GPIO_SetBits(KEY4_GPIO_PORT,KEY4_GPIO_PIN);
//    
//    /*选择要控制的GPIO引脚、设置GPIO模式为 上拉输入、设置GPIO速率为50MHz*/
//    gpio_initstruct.GPIO_Pin    = KEY4_GPIO_PIN;
//    gpio_initstruct.GPIO_Mode   = GPIO_Mode_IPU;
//    gpio_initstruct.GPIO_Speed  = GPIO_Speed_50MHz;
//    GPIO_Init(KEY4_GPIO_PORT,&gpio_initstruct);
//   
//#endif 

#if 1    
    
    /* 开启 KEY 相关的GPIO外设/端口时钟 */
    RCC_APB2PeriphClockCmd(KEY5_GPIO_CLK_PORT,ENABLE);
    
    /* IO输出状态初始化控制 */
    GPIO_SetBits(KEY5_GPIO_PORT,KEY5_GPIO_PIN);
    
    /*选择要控制的GPIO引脚、设置GPIO模式为 上拉输入、设置GPIO速率为50MHz*/
    gpio_initstruct.GPIO_Pin    = KEY5_GPIO_PIN;
    gpio_initstruct.GPIO_Mode   = GPIO_Mode_IPU;
    gpio_initstruct.GPIO_Speed  = GPIO_Speed_50MHz;
    GPIO_Init(KEY5_GPIO_PORT,&gpio_initstruct);
   
#endif 

#if 1    
    
    /* 开启 KEY 相关的GPIO外设/端口时钟 */
    RCC_APB2PeriphClockCmd(KEY6_GPIO_CLK_PORT,ENABLE);
    
    /* IO输出状态初始化控制 */
    GPIO_SetBits(KEY6_GPIO_PORT,KEY6_GPIO_PIN);
    
    /*选择要控制的GPIO引脚、设置GPIO模式为 上拉输入、设置GPIO速率为50MHz*/
    gpio_initstruct.GPIO_Pin    = KEY6_GPIO_PIN;
    gpio_initstruct.GPIO_Mode   = GPIO_Mode_IPU;
    gpio_initstruct.GPIO_Speed  = GPIO_Speed_50MHz;
    GPIO_Init(KEY6_GPIO_PORT,&gpio_initstruct);
   
#endif 
}


/**
  * @brief  基础检测按键
  * @param  GPIOx：x 可以是 A，B，C等
  * @param  GPIO_Pin：待操作的pin脚号
  * @param  key_pressstatus：按键按下时的IO电平状态
  * @retval KEY_UP(没有触发按键)、KEY_DOWN(触发按键)
  */
KEY_Status KEY_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, KEY_TriggerLevel key_pressstatus)
{
    if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == key_pressstatus)
    {
        Rough_Delay_Ms(50);
        while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == key_pressstatus);
        Rough_Delay_Ms(50);
        return KEY_DOWN;
    }
    else
    {
        return KEY_UP;
    }
}

/*****************************END OF FILE***************************************/
