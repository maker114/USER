#ifndef __SERVO_H
#define __SERVO_H

void Servo_Init(void);
void Servo_SetAngle(float Angle, uint8_t GROUP);

#define GROUP_1 1
#define GROUP_2 2
#define GROUP_3 3

#endif
