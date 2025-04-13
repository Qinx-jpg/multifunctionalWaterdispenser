#include "flo.h"   
#include "stm32f10x.h"
#include "dwt/bsp_dwt.h"   

// ȫ�ֱ���
void flo_init(){
// ����ʱ��
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;   // ʹ��GPIOAʱ��
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;   // ʹ��TIM3ʱ��

    // ����PA7Ϊ����ģʽ�����ù��ܣ�
    GPIOA->CRL &= ~(GPIO_CRL_CNF7 | GPIO_CRL_MODE7);  // ���ԭ������
    GPIOA->CRL |= GPIO_CRL_CNF7_1;        // CNF7[1:0] = 10�����ù�������
    GPIOA->CRL &= ~GPIO_CRL_MODE7;        // MODE7[1:0] = 00������ģʽ

    // ����TIM3
    TIM3->CR1 = 0;                        // �رն�ʱ��
    TIM3->PSC = 0;                        // ��Ԥ��Ƶ
    TIM3->ARR = 0xFFFF;                   // �Զ���װ��ֵ��Ϊ���
    TIM3->CCMR1 = TIM_CCMR1_CC2S_0;       // CC2ͨ������Ϊ���룬ӳ�䵽TI2
    TIM3->CCER = TIM_CCER_CC2E;           // ʹ�ܲ���ͨ��2
    TIM3->SMCR = TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0  // �ⲿʱ��ģʽ1
               | TIM_SMCR_TS_2 | TIM_SMCR_TS_1;  // ����Դѡ��TI2FP2
    
    TIM3->CR1 |= TIM_CR1_CEN;             // ������ʱ��
}
float flo_read(void) {
        DWT_DelayS(1);               // ����ʱԼ1��
        float pulse_count = TIM3->CNT;          // ��ȡ����ֵ
        TIM3->CNT = 0;                    // ���ü�����
				return pulse_count;
}
