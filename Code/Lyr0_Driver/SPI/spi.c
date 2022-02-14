#include "spi.h"

//以下是SPI模块的初始化代码，配置成主机模式，访问W25Q128/NRF24L01
//SPI口初始化 
 

void SPI_Init(SPI_TypeDef *SPIx)
{	  
#ifdef __CM3_CORE_H__	
	RCC->APB2ENR|=1<<12;   	//SPI1时钟使能 
	//这里只针对SPI口初始化
//	GPIOA->CRL&=0X000FFFFF; 
//	GPIOA->CRL|=0XBBB00000;	//PA5/6/7复用 	    
	GPIOA->ODR|=0X7<<5;   	//PA5/6/7上拉
	SPIx->CR1|=0<<10;		//全双工模式	
	SPIx->CR1|=1<<9; 		//软件nss管理
	SPIx->CR1|=1<<8;  

	SPIx->CR1|=1<<2; 		//SPI主机
	SPIx->CR1|=0<<11;		//8bit数据格式	
	SPIx->CR1|=1<<1; 		//空闲模式下SCK为1 CPOL=1
	SPIx->CR1|=1<<0; 		//数据采样从第二个时间边沿开始,CPHA=1  
	//对SPI2属于APB1的外设.时钟频率最大为36M  
	//SP1在APB2上 时钟最大72M
	SPIx->CR1|=3<<3; 		//Fsck=Fpclk1/256
	SPIx->CR1|=0<<7; 		//MSBfirst   
	SPIx->CR1|=1<<6; 		//SPI设备使能
	SPIx_ReadWriteByte(0xff);//启动传输		 
#endif
#ifdef __CORE_CM4_H_GENERIC
	u16 tempreg=0; 
	if(SPIx == SPI1) 
	{
		RCC->APB2ENR|=1<<12;   	//SPI1时钟使能    
		RCC->APB2RSTR|=1<<12;	//复位SPI1
		RCC->APB2RSTR&=~(1<<12);//停止复位SPI1

	}
	else if(SPIx == SPI2)
	{
		RCC->APB1ENR|=1<<14;   	//SPI2时钟使能  
		RCC->APB1RSTR|=1<<14;	//复位SPI1
		RCC->APB1RSTR&=~(1<<14);//停止复位SPI1
	}
	else if(SPIx == SPI3)
	{
		RCC->APB1ENR|=1<<15;   	//SPI2时钟使能  
		RCC->APB1RSTR|=1<<15;	//复位SPI1
		RCC->APB1RSTR&=~(1<<15);//停止复位SPI1
	}
	else
		return ;
	tempreg|=0<<10;			//全双工模式	
	tempreg|=1<<9;			//软件nss管理
	tempreg|=1<<8;			 
	tempreg|=1<<2;			//SPI主机  
	tempreg|=0<<11;			//8位数据格式	
	tempreg|=1<<1;			//空闲模式下SCK为1 CPOL=1 
	tempreg|=1<<0;			//数据采样从第2个时间边沿开始,CPHA=1
 	//对SPI1属于APB2的外设.时钟频率最大为84Mhz频率.
	tempreg|=7<<3;			//Fsck=Fpclk1/256
	tempreg|=0<<7;			//MSB First  
	tempreg|=1<<6;			//SPI启动 
	SPIx->CR1=tempreg; 		//设置CR1  
	SPIx->I2SCFGR&=~(1<<11);//选择SPI模式
	SPI_ReadWriteByte(SPIx,0xff);//启动传输		 
#endif
}   


void SPI_SetSpeed(SPI_TypeDef *SPIx,u8 SpeedSet)
{
	SpeedSet&=0X07;			//限制范围
	SPIx->CR1&=0XFFC7; 
	SPIx->CR1|=SpeedSet<<3;	//设置SPI2速度  
	SPIx->CR1|=1<<6; 		//SPI设备使能	  
}  


u8 SPI_ReadWriteByte(SPI_TypeDef *SPIx, u8 TxData)
{		
	u16 retry=0;				 
	while((SPIx->SR&1<<1)==0)		//等待发送区空	
	{
		retry++;
		if(retry>=0XFFFE)return 0; 	//超时退出
	}			  
	SPIx->DR=TxData;	 	  		//发送一个byte 
	retry=0;
	while((SPIx->SR&1<<0)==0) 		//等待接收完一个byte  
	{
		retry++;
		if(retry>=0XFFFE)return 0;	//超时退出
	}	  						    
	return SPIx->DR;          		//返回收到的数据				    
}

