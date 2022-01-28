/***********************************************************************************************************
* ��Ȩ                                                                                                     *
*                                                                                                          *
* �ļ�����: systick.h                                                                                      *
* ��    ��: ��ʱ����������                                                                                 *
* ��    ��: ������                                                                                         *
* ��ǰ�汾: 1.0.1                                                                                          *  
* ���ʱ��:                                                                                                *
* ---------------------------------------------------------------------------------------------------------*
* ��ʷ��Ϣ:                                                                                                *
*           <Date>            |    <Version>    |    <Author>    |    <Description>                        *
* ---------------------------------------------------------------------------------------------------------*
*   2019��9��26��10:49:03     |      1.0.1      |     ������     |     Create file                         *            
*----------------------------------------------------------------------------------------------------------*
***********************************************************************************************************/ 
#include "include.h"
#include "systick.h"  



void SysTick_Init(void)
{
	SysTick->CTRL &= 0xfffffffb;	//ʹ���ⲿʱ��Դ8��Ƶ   9Mhz
//	SysTick->CTRL |= 0x00000002;	//�����жϷ���
	SysTick->CTRL &= 0xfffffffd;		//�ر��жϷ���
	
	SysTick->LOAD  =(uint32_t)100*9000;	//��װ��1ms

	SysTick->VAL   = 0;           //дֵʹ��Ĵ�������

	SysTick->CTRL |= 0x00000001;  //����SysTick��ʱ��
}	


	
	
//	while(1)
//	{
//		i=1-i;
//			
//		LED(~i);
//			
//		SysTick->CTRL|=0x00000001;	//������શ�ʱ��
//		SysTick->VAL=0;		//���������
//		do{
//			temp=SysTick->CTRL;	//��ѯ��־λ
//		}while((temp & (1<<16))==0);	//�ж��Ƿ����
//		SysTick->CTRL&=0xfffffffe;	//�رն�ʱ��
//	}



