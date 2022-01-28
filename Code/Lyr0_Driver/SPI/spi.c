#include "spi.h"

//������SPIģ��ĳ�ʼ�����룬���ó�����ģʽ������W25Q128/NRF24L01
//SPI�ڳ�ʼ�� 
 

void SPI_Init(SPI_TypeDef *SPIx)
{	  
#ifdef __CM3_CORE_H__	
	RCC->APB2ENR|=1<<12;   	//SPI1ʱ��ʹ�� 
	//����ֻ���SPI�ڳ�ʼ��
//	GPIOA->CRL&=0X000FFFFF; 
//	GPIOA->CRL|=0XBBB00000;	//PA5/6/7���� 	    
	GPIOA->ODR|=0X7<<5;   	//PA5/6/7����
	SPIx->CR1|=0<<10;		//ȫ˫��ģʽ	
	SPIx->CR1|=1<<9; 		//���nss����
	SPIx->CR1|=1<<8;  

	SPIx->CR1|=1<<2; 		//SPI����
	SPIx->CR1|=0<<11;		//8bit���ݸ�ʽ	
	SPIx->CR1|=1<<1; 		//����ģʽ��SCKΪ1 CPOL=1
	SPIx->CR1|=1<<0; 		//���ݲ����ӵڶ���ʱ����ؿ�ʼ,CPHA=1  
	//��SPI2����APB1������.ʱ��Ƶ�����Ϊ36M  
	//SP1��APB2�� ʱ�����72M
	SPIx->CR1|=3<<3; 		//Fsck=Fpclk1/256
	SPIx->CR1|=0<<7; 		//MSBfirst   
	SPIx->CR1|=1<<6; 		//SPI�豸ʹ��
	SPIx_ReadWriteByte(0xff);//��������		 
#endif
#ifdef __CORE_CM4_H_GENERIC
	u16 tempreg=0; 
	if(SPIx == SPI1) 
	{
		RCC->APB2ENR|=1<<12;   	//SPI1ʱ��ʹ��    
		RCC->APB2RSTR|=1<<12;	//��λSPI1
		RCC->APB2RSTR&=~(1<<12);//ֹͣ��λSPI1

	}
	else if(SPIx == SPI2)
	{
		RCC->APB1ENR|=1<<14;   	//SPI2ʱ��ʹ��  
		RCC->APB1RSTR|=1<<14;	//��λSPI1
		RCC->APB1RSTR&=~(1<<14);//ֹͣ��λSPI1
	}
	else if(SPIx == SPI3)
	{
		RCC->APB1ENR|=1<<15;   	//SPI2ʱ��ʹ��  
		RCC->APB1RSTR|=1<<15;	//��λSPI1
		RCC->APB1RSTR&=~(1<<15);//ֹͣ��λSPI1
	}
	else
		return ;
	tempreg|=0<<10;			//ȫ˫��ģʽ	
	tempreg|=1<<9;			//���nss����
	tempreg|=1<<8;			 
	tempreg|=1<<2;			//SPI����  
	tempreg|=0<<11;			//8λ���ݸ�ʽ	
	tempreg|=1<<1;			//����ģʽ��SCKΪ1 CPOL=1 
	tempreg|=1<<0;			//���ݲ����ӵ�2��ʱ����ؿ�ʼ,CPHA=1  
 	//��SPI1����APB2������.ʱ��Ƶ�����Ϊ84MhzƵ��.
	tempreg|=7<<3;			//Fsck=Fpclk1/256
	tempreg|=0<<7;			//MSB First  
	tempreg|=1<<6;			//SPI���� 
	SPIx->CR1=tempreg; 		//����CR1  
	SPIx->I2SCFGR&=~(1<<11);//ѡ��SPIģʽ
	SPI_ReadWriteByte(SPIx,0xff);//��������		 
#endif
}   


void SPI_SetSpeed(SPI_TypeDef *SPIx,u8 SpeedSet)
{
	SpeedSet&=0X07;			//���Ʒ�Χ
	SPIx->CR1&=0XFFC7; 
	SPIx->CR1|=SpeedSet<<3;	//����SPI2�ٶ�  
	SPIx->CR1|=1<<6; 		//SPI�豸ʹ��	  
}  


u8 SPI_ReadWriteByte(SPI_TypeDef *SPIx, u8 TxData)
{		
	u16 retry=0;				 
	while((SPIx->SR&1<<1)==0)		//�ȴ���������	
	{
		retry++;
		if(retry>=0XFFFE)return 0; 	//��ʱ�˳�
	}			  
	SPIx->DR=TxData;	 	  		//����һ��byte 
	retry=0;
	while((SPIx->SR&1<<0)==0) 		//�ȴ�������һ��byte  
	{
		retry++;
		if(retry>=0XFFFE)return 0;	//��ʱ�˳�
	}	  						    
	return SPIx->DR;          		//�����յ�������				    
}

