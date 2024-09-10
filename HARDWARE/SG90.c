/**
 * @file SG90.c
 * @author maker114
 * @brief  ���ƶ����ת��,Ĭ���Զ��ת����Χ��һ����Ϊԭ�㣬��Χ����90�ȣ���ʱ����װ��ֲΪ5000��T=20ms��
 * @version 0.1
 * @date 2024-07-26
 *
 *
 */
#include "usart.h"
#include "SG90.h"
#include "delay.h"
#include "math.h"
#include "stdlib.h"
#include "stm32f10x.h" 
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"

#define SG90_PWM_MID 1570 // �����е��ֵ�����������0��ʱ��PWMֵ
#define SG90_PWM_MAX 2499 // ������Ƕȶ�Ӧ��PWMֵ
#define SG90_PWM_MIN 499  // �����С�Ƕȶ�Ӧ��PWMֵ

uint16_t PWM_Lode_Value = 0; // ���PWMֵ

/**
 * @brief �����ʼ���������������PWMʱ�ӣ��ϵ�ʱĬ�ϸ�λ��ԭ��
 *
 */
void SG90_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
}

/**
 * @brief ���ö���Ƕ�
 *
 * @param Channel ѡ��ͨ��
 * 			|- Channel_0 ͨ��һ
 * 			|- Channel_1 ͨ����
 * @param Angle ���õĽǶȣ��Զ��ת����Χ��һ����Ϊԭ�㣬��Χ����60��
 */
void SG90_SetAngle(uint8_t Channel, int Angle)
{
	// ����������ݺϷ���
//	Angle = (Angle < -60) ? -60 : Angle;
//	Angle = (Angle > 60) ? 60 : Angle;5
	// װ��PWMֵ
	TIM_SetCompare2(TIM2,Angle / 180 * 2000 + 500);
}
