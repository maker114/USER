#include "delay.h"
#include "sys.h"
#include "usart.h"
#ifndef __SG90_H
#define __SG90_H

/*
//�ṹ�嶨�岿��
*/
typedef enum
{
	Channel_0 = 0,
	Channel_1 = 1
} PWM_Channel;

void SG90_Init(void);
void SG90_SetAngle(uint8_t Channel, int Angle);

#endif
