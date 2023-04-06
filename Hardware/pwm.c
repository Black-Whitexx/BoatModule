#include "pwm.h"

//Arr���Զ���װֵ
//Psc��ʱ��Ԥ��Ƶ��
void TIM1_CH1_PWM_Init(uint16_t Arr,uint16_t Psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  
	                                                                     	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 		 //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	TIM_TimeBaseStructure.TIM_Period = Arr; 					//�Զ���װֵ
	TIM_TimeBaseStructure.TIM_Prescaler =Psc; 					//Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 				//ʱ�ӷ�Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 			  //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; 							  //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  

    TIM_CtrlPWMOutputs(TIM1,ENABLE);				
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);//CH1Ԥװ��ʹ��	 
	TIM_ARRPreloadConfig(TIM1, ENABLE);				 //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	TIM_Cmd(TIM1, ENABLE);  						 //ʹ��
 
   
}

void TIM3_CH1_PWM_Init(uint16_t Arr,uint16_t Psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6; 		 //ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	 //�������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	 
	GPIO_Init(GPIOA,&GPIO_InitStructure); 	   
	
	TIM_TimeBaseInitStructure.TIM_Period=Arr;					 //�Զ�����ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=Psc;				 //Ԥ��Ƶֵ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;	 //1��Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	
	TIM_Cmd(TIM3,ENABLE);
	
}
