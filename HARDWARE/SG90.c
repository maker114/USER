/**
 * @file SG90.c
 * @author maker114
 * @brief  控制舵机的转向,默认以舵机转动范围的一半作为原点，范围正负90度，定时器重装栽植为5000（T=20ms）
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

#define SG90_PWM_MID 1570 // 舵机机械中值，即舵机处于0度时的PWM值
#define SG90_PWM_MAX 2499 // 舵机最大角度对应的PWM值
#define SG90_PWM_MIN 499  // 舵机最小角度对应的PWM值

uint16_t PWM_Lode_Value = 0; // 舵机PWM值

/**
 * @brief 电机初始化函数，开启舵机PWM时钟，上电时默认复位置原点
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
 * @brief 设置舵机角度
 *
 * @param Channel 选择通道
 * 			|- Channel_0 通道一
 * 			|- Channel_1 通道二
 * @param Angle 设置的角度，以舵机转动范围的一半作为原点，范围正负60度
 */
void SG90_SetAngle(uint8_t Channel, int Angle)
{
	// 检察输入数据合法性
//	Angle = (Angle < -60) ? -60 : Angle;
//	Angle = (Angle > 60) ? 60 : Angle;5
	// 装载PWM值
	TIM_SetCompare2(TIM2,Angle / 180 * 2000 + 500);
}
