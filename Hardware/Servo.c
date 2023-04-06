#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Servo_Init(void)
{
	PWM_Init();
}

void Servo_SetAngle(float Angle)
{													//PWMռ�ձ� = CRR/(ARR+1)
	PWM_SetCompare2(Angle / 180 * 2000 + 500);		//Angle=0 ��Ӧռ�ձȣ�0.5ms/20ms 
}													//Angle=180 ��Ӧռ�ձȣ�2.5ms/20ms
