/**
 * @file Servo.c
 * @author maker114
 * @brief ���Ӧ�ò�
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
	MAX_ANGLE, // ���Ƕ�
	MIN_ANGLE  // ��С�Ƕ�
};

// �洢��ÿ���������С�����Ƕ�
uint16_t ANGLE_Config[4][2] = {
	{1925, 500},
	{1925, 500},
	{1925, 500},
	{1925, 500}};
/**
 * @brief ���ö���Ƕ�
 *
 * @param Angle �Ƕȣ�0~180��
 * @param GROUP �����ţ�1~3��
 * @note GROUP1��
 * 			|- ͨ��һ��PA0��
 * 			|- ͨ������PA1��
 * 		 GROUP2��
 * 			|- ͨ������PA2��
 * 			|- ͨ���ģ�PA3��
 */
void Servo_SetAngle(float Angle, uint8_t GROUP)
{
	// �ж�����Ϸ���
	if (Angle < 0)
		Angle = 0;
	if (Angle > 180)
		Angle = 180;
	// �����������ţ����ö�Ӧ��PWMռ�ձ�
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
	// TODO:�����飨��Ҫ�������ö�ʱ����
}
