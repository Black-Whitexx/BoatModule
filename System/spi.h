#ifndef __SPI_H
#define __SPI_H

#include "stm32f10x.h"

		  	    													  
void SPI2_Init_JX(void);			// ��ʼ��SPI��

void SPI2_SetSpeed(uint8_t SpeedSet); 	// ����SPI�ٶ�  

uint8_t SPI2_ReadWriteByte(uint8_t TxData);	// SPI��дһ���ֽ�
		 
		 
#endif	/* __SPI_H */
