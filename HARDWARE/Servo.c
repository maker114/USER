/**
 * @file Servo.c
 * @author maker114
 * @brief 舵机应用层
 * @version 0.1
 * @date 2024-09-13
 */
#include "stm32f10x.h" // Device header
#include "PWM.h"
#include "Servo.h"

void Servo_Init(void)
{
	PWM_Init();
}

enum Angle
{
	MAX_ANGLE, // 最大角度
	MIN_ANGLE  // 最小角度
};

// 存储了每个舵机的最小与最大角度
uint16_t ANGLE_Config[4][2] = {
	{1925, 500},
	{1925, 500},
	{1925, 500},
	{1925, 500}};
/**
 * @brief 设置舵机角度
 *
 * @param Angle 角度（0~180）
 * @param GROUP 舵机组号（1~3）
 * @note GROUP1：
 * 			|- 通道一（PA0）
 * 			|- 通道二（PA1）
 * 		 GROUP2：
 * 			|- 通道三（PA2）
 * 			|- 通道四（PA3）
 */
void Servo_SetAngle(float Angle, uint8_t GROUP)
{
	// 判断输入合法性
	if (Angle < 0)
		Angle = 0;
	if (Angle > 180)
		Angle = 180;
	// 根据输入的组号，设置对应的PWM占空比
	if (GROUP == GROUP_1)
	{
		PWM_SetCompare1(Angle / 180 * ANGLE_Config[0][MAX_ANGLE] + ANGLE_Config[0][MIN_ANGLE]);
		PWM_SetCompare2((180 - Angle) / 180 * ANGLE_Config[1][MAX_ANGLE] + ANGLE_Config[1][MIN_ANGLE]);
	}
	if (GROUP == GROUP_2)
	{
		PWM_SetCompare3(Angle / 180 * ANGLE_Config[2][MAX_ANGLE] + ANGLE_Config[2][MIN_ANGLE]);
		PWM_SetCompare4((180 - Angle) / 180 * ANGLE_Config[3][MAX_ANGLE] + ANGLE_Config[3][MIN_ANGLE]);
	}
	// TODO:第三组（需要额外配置定时器）
}
