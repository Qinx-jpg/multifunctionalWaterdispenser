#include "flo.h"   
#include "stm32f10x.h"
#include "dwt/bsp_dwt.h"   

// 全局变量
void flo_init(){
// 启用时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;   // 使能GPIOA时钟
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;   // 使能TIM3时钟

    // 配置PA7为输入模式（复用功能）
    GPIOA->CRL &= ~(GPIO_CRL_CNF7 | GPIO_CRL_MODE7);  // 清除原有配置
    GPIOA->CRL |= GPIO_CRL_CNF7_1;        // CNF7[1:0] = 10：复用功能输入
    GPIOA->CRL &= ~GPIO_CRL_MODE7;        // MODE7[1:0] = 00：输入模式

    // 配置TIM3
    TIM3->CR1 = 0;                        // 关闭定时器
    TIM3->PSC = 0;                        // 无预分频
    TIM3->ARR = 0xFFFF;                   // 自动重装载值设为最大
    TIM3->CCMR1 = TIM_CCMR1_CC2S_0;       // CC2通道配置为输入，映射到TI2
    TIM3->CCER = TIM_CCER_CC2E;           // 使能捕获通道2
    TIM3->SMCR = TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0  // 外部时钟模式1
               | TIM_SMCR_TS_2 | TIM_SMCR_TS_1;  // 触发源选择：TI2FP2
    
    TIM3->CR1 |= TIM_CR1_CEN;             // 启动定时器
}
float flo_read(void) {
        DWT_DelayS(1);               // 简单延时约1秒
        float pulse_count = TIM3->CNT;          // 读取计数值
        TIM3->CNT = 0;                    // 重置计数器
				return pulse_count;
}
