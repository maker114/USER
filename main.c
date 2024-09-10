#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "Board.h"
#include "WS2812.h"
#include "Servo.h"

int num = 0;
int step = 2;

int main(void)
{
	delay_init();
	uart_init(115200);
	Board_Init();
	WS2812_init(8);
	Servo_Init();
	while (1)
	{
		Servo_SetAngle(120);
		num += 1;
	}
}
