#include "BKP.h"

void BKP_Init(void)
{
  RCC->APB1ENR |= 3<<27;				//开启BKP，PWR时钟
	PWR->CR |= 1<<8;              //允许写入RTC和后备寄存器
}

unsigned char BKP_Read_DR1(void)
{
	return BKP->DR1;
}

void BKP_Write_DR1(unsigned char dat)
{
	BKP->DR1 = dat;
}






