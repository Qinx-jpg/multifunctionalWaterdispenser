#ifndef __BSP_GPIO_KEY_H
#define __BSP_GPIO_KEY_H

#include "stm32f10x.h"

/* 定义 KEY 连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的 KEY 引脚 */

//KEY1
#define KEY1_GPIO_PORT          GPIOA                           /* GPIO端口 */
#define KEY1_GPIO_CLK_PORT      RCC_APB2Periph_GPIOA            /* GPIO端口时钟 */
#define KEY1_GPIO_PIN           GPIO_Pin_0                      /* 对应PIN脚 */

//KEY2
#define KEY2_GPIO_PORT          GPIOC                           /* GPIO端口 */
#define KEY2_GPIO_CLK_PORT      RCC_APB2Periph_GPIOC            /* GPIO端口时钟 */
#define KEY2_GPIO_PIN           GPIO_Pin_13                      /* 对应PIN脚 */

////KEY3
//#define KEY3_GPIO_PORT          GPIOB                           /* GPIO端口 */
//#define KEY3_GPIO_CLK_PORT      RCC_APB2Periph_GPIOB           /* GPIO端口时钟 */
//#define KEY3_GPIO_PIN           GPIO_Pin_15                      /* 对应PIN脚 */

////KEY4
//#define KEY4_GPIO_PORT          GPIOB                           /* GPIO端口 */
//#define KEY4_GPIO_CLK_PORT      RCC_APB2Periph_GPIOB            /* GPIO端口时钟 */
//#define KEY4_GPIO_PIN           GPIO_Pin_6                      /* 对应PIN脚 */

//KEY5
#define KEY5_GPIO_PORT          GPIOB                           /* GPIO端口 */
#define KEY5_GPIO_CLK_PORT      RCC_APB2Periph_GPIOB            /* GPIO端口时钟 */
#define KEY5_GPIO_PIN           GPIO_Pin_9                      /* 对应PIN脚 */

//KEY6
#define KEY6_GPIO_PORT          GPIOB                           /* GPIO端口 */
#define KEY6_GPIO_CLK_PORT      RCC_APB2Periph_GPIOB            /* GPIO端口时钟 */
#define KEY6_GPIO_PIN           GPIO_Pin_8                      /* 对应PIN脚 */


/* 按键按下时的IO电平 */
typedef enum 
{
    KEY_LOW_TRIGGER = 0, 
    KEY_HIGH_TRIGGER = 1,
}KEY_TriggerLevel;

/* 按键的状态 */
typedef enum 
{
    KEY_UP = 0, 
    KEY_DOWN = 1,
    KEY_INIT = 2,
}KEY_Status;

void KEY_GPIO_Config(void);
KEY_Status KEY_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, KEY_TriggerLevel key_pressstatus);

#endif /* __BSP_GPIO_KEY_H */
