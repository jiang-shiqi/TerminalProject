#ifndef __BKP_H
#define __BKP_H	  
#include <stm32f10x.h>  


void BKP_Init(void);
unsigned char BKP_Read_DR1(void);
void BKP_Write_DR1(unsigned char dat);





#endif

