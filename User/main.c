#include <stdio.h>
#include "string.h"
#include "math.h"
#include "stdint.h"
#include "Delay.h"
#include "nrf24l01.h"
#include "AD.h"
#include "pwm.h"
#include "OLED.h"


uint8_t mode=0;	//1为发送模式、0为接收模式//1为发送模式、0为接收模式
//uint8_t mode=1; 		
uint32_t ad1,ad2,ad; //ad为发送端采集到的值，AD为接收端收到的值
uint32_t AD1,AD2,AD;
float Speed,Angle;	//电机转速、舵机角度
uint8_t rx_buf[33];	

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组，分2组
	NRF24L01_Init();	//初始化
	AD_Init();
	OLED_Init();
	TIM1_CH1_PWM_Init(20000-1,72-1);//50Hz,20ms
	TIM3_CH1_PWM_Init(20000-1,72-1);//20ms

	while(NRF24L01_Check())	 //检测NRF24L01是否存在
	{
		OLED_ShowString(1,1,"nrfError");	
	}
	OLED_ShowString(1,1,"nrfOK");	
	
	if(mode==1)
	{
		OLED_ShowString(1,10,"TxMode");
		NRF24L01_TX_Mode();//设置为发送模式
		while(1)
		{
			ad1=AD_GetValue(ADC_Channel_1); //摇杆adc采集
			ad2=AD_GetValue(ADC_Channel_2);
			OLED_ShowString(2,1,"Speed:");
			OLED_ShowString(3,1,"Angle:");
			OLED_ShowNum(2,7,ad1,4);
			OLED_ShowNum(3,7,ad2,4);
			
			ad=ad1*10000+ad2;	//把ad1和ad2的值拼接成一个值ad,然后发送出去
			sprintf((char *)rx_buf,"%d",ad);
			NRF24L01_TxPacket(rx_buf);
			Delay_ms(100);
		}
	}

	if(mode==0)
	{
		OLED_ShowString(1,10,"RxMode");
		NRF24L01_RX_Mode();	//设置为接收模式
		while(1)
		{
			if(NRF24L01_RxPacket(rx_buf)==0) 
			{
				rx_buf[32]='\0';						//加入字符串结束符
				sscanf((const char *)rx_buf,"%d",&AD);	//接收到的AD = ad
				AD1=AD/10000; 							//取AD的第四位之前的数值，AD1 = ad1
				AD2=AD%10000;							//取AD的后四位，AD2 = ad2
				
				Speed = (float)AD1 / 4095 * 1400 + 800;			//电调的pwm波范围为[800us 2200us]
				Angle = (float)AD2 / 4095 * 110 + 45;//舵机角度范围[45 155]
				
				OLED_ShowNum(2,1,AD1,4);
				OLED_ShowNum(2,7,AD2,4);
				OLED_ShowNum(3,1,Speed,4);
				OLED_ShowNum(3,7,Angle,3);
				
				TIM_SetCompare1(TIM1,Speed);					//输入电调的pwm波
				TIM_SetCompare1(TIM3,Angle / 180 * 2000 + 500); //输入舵机的pwm波
			}
	
		}
	}
	return 0;
}
