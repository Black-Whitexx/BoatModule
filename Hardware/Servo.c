#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Servo_Init(void)
{
	PWM_Init();
}

void Servo_SetAngle(float Angle)
{													//PWM占空比 = CRR/(ARR+1)
	PWM_SetCompare2(Angle / 180 * 2000 + 500);		//Angle=0 对应占空比：0.5ms/20ms 
}													//Angle=180 对应占空比：2.5ms/20ms
