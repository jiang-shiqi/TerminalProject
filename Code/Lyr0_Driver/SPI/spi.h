#ifndef __SPI_H
#define __SPI_H

#include "include.h"
 
// SPI�����ٶ����� 
#define SPI_SPEED_2   		0
#define SPI_SPEED_4   		1
#define SPI_SPEED_8   		2
#define SPI_SPEED_16  		3
#define SPI_SPEED_32 		4
#define SPI_SPEED_64 		5
#define SPI_SPEED_128 		6
#define SPI_SPEED_256 		7


void SPI_Init(SPI_TypeDef *SPIx);			 //��ʼ��SPI��
void SPI_SetSpeed(SPI_TypeDef *SPIx, u8 SpeedSet); //����SPI�ٶ�   
u8 SPI_ReadWriteByte(SPI_TypeDef *SPIx, u8 TxData);//SPI���߶�дһ���ֽ� 
		 
#endif

