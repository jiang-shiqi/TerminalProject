/***********************************************************************************************************
* 版权                                                                                                     *
*                                                                                                          *
* 文件名称: GPIO.c                                                                                         *
* 描    述: 通过GPIO.h的GPIO配置表设置IO口状态                                                             *
* 作    者: 姜世奇                                                                                         *
* 当前版本: 1.0.1                                                                                          * 
* 完成时间: 2019年9月25日                                                                                  *
* ---------------------------------------------------------------------------------------------------------*
* 历史信息:                                                                                                *
*           <Date>            |    <Version>    |    <Author>    |    <Description>                        *
* ---------------------------------------------------------------------------------------------------------*
*   2019年9月25日 21:33:40    |      1.0.1      |     姜世奇     |     Create file                          *            
*   2021年7月09日 08:59:49    |      1.0.2      |     姜世奇     |     加入LCD引脚初始化                     *            
*----------------------------------------------------------------------------------------------------------*
*   待完成功能：
*   1.根据模块的开启状态时刻检测是否应开启IO口时钟（低功耗）制作Service函数放入任务循环里
***********************************************************************************************************/
 
#include "GPIO.h"

void GPIO_Init(void)
{
#ifdef F103C8	
	//GPIOA
	RCC->APB2ENR |= 1<<2;
//	GPIOA->CRH &= 0x0ffff000; 
//	GPIOA->CRH |= 0x800008b3; 
//	                          
//	GPIOA->CRL &= 0xfff00000; 
//	GPIOA->CRL |= 0x00038000; 
	                          
	GPIOA->ODR &= 0x00007cf7; 
	GPIOA->ODR |= 0x00008508;
	
	//GPIOB
	RCC->APB2ENR |= 1<<3;
//	GPIOB->CRH &= 0x00000000;
//	GPIOB->CRH |= 0xBBB38888;
//	                         
//	GPIOB->CRL &= 0x00000f00;
//	GPIOB->CRL |= 0x33333088;
	                         
	GPIOB->ODR &= 0x000010fc;
	GPIOB->ODR |= 0x0000ef03;
	
	//GPIOC
	RCC->APB2ENR |= 1<<4;
//	GPIOC->CRH &= 0xff0fffff;
//	GPIOC->CRH |= 0x00300000;
//	
//	GPIOC->CRL &= 0xffffffff;
//	GPIOC->CRL |= 0x00000000;
	
	GPIOC->ODR &= 0x0000dfff;
	GPIOC->ODR |= 0x00002000;

#ifdef F103ZE	

	//GPIOD
	RCC->APB2ENR |= 1<<5;
	GPIOD->CRH &= 0xff0fffff;
	GPIOD->CRH |= 0x00300000;
	
	GPIOD->CRL &= 0xffffffff;
	GPIOD->CRL |= 0x00000000;
	
	//GPIOE
	RCC->APB2ENR |= 1<<6;
	GPIOE->CRH &= 0xff0fffff;
	GPIOE->CRH |= 0x00300000;
	    
	GPIOE->CRL &= 0xffffffff;
	GPIOE->CRL |= 0x00000000;
	
	//GPIOF
	RCC->APB2ENR |= 1<<7;
	GPIOF->CRH &= 0xff0fffff;
	GPIOF->CRH |= 0x00300000;
	 
	GPIOF->CRL &= 0xffffffff;
	GPIOF->CRL |= 0x00000000;
	
	//GPIOG
	RCC->APB2ENR |= 1<<8;
	GPIOG->CRH &= 0xff0fffff;
	GPIOG->CRH |= 0x00300000;
	   
	GPIOG->CRL &= 0xffffffff;
	GPIOG->CRL |= 0x00000000;
	
	GPIO_JtagToIo();
#endif
#endif	 
#ifdef F407VG  
//	配置范例
//	GPIO_Set(GPIOE,PIN2|PIN3|PIN4,GPIO_MODE_IN,0,0,GPIO_PUPD_PU);	//PE2~4设置上拉输入
//	GPIO_Set(GPIOA,PIN0,GPIO_MODE_IN,0,0,GPIO_PUPD_PD); 			//PA0设置为下拉输入
//	GPIO_Set(GPIOA,PIN5,GPIO_MODE_AIN,0,0,GPIO_PUPD_PU);	//PA5,模拟输入,下拉  
//  GPIO_Set(GPIOF,PIN13,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU); //推挽输出 
//	GPIO_Set(GPIOB,7<<3,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);	//SPI1 PB3~5复用功能输出	
//  GPIO_AF_Set(GPIOB,3,5);	//PB3,AF5
// 	GPIO_AF_Set(GPIOB,4,5);	//PB4,AF5
// 	GPIO_AF_Set(GPIOB,5,5);	//PB5,AF5 

  RCC->AHB1ENR|=0x1F<<0;   	//使能ABCDE口时钟  
	//GPIOA
	GPIO_Set(GPIOA,PIN0,GPIO_MODE_AIN,0,0,GPIO_PUPD_PU);				//PA0 AD输入
//	GPIO_Set(GPIOA,PIN1,GPIO_MODE_AIN,0,0,GPIO_PUPD_PU);      //PA1 AD输入
	GPIO_Set(GPIOA,PIN1,GPIO_MODE_IN,0,0,GPIO_PUPD_PU); /////////////////////////////////暂时被用作ESP32从机动作检测引脚
	GPIO_Set(GPIOA,PIN2|PIN3,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PA2,PA3,复用功能,上拉输出
	GPIO_AF_Set(GPIOA,2,7);	//PA2,AF7
	GPIO_AF_Set(GPIOA,3,7); //PA3,AF7  	
	GPIO_Set(GPIOA,PIN4,GPIO_MODE_AIN,0,0,GPIO_PUPD_PU);
	GPIO_Set(GPIOA,7<<5,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);	//SPI1 PA5~7复用功能输出	
	GPIO_AF_Set(GPIOA,5,5);	//PA5,AF5
	GPIO_AF_Set(GPIOA,6,5);	//PA6,AF5
	GPIO_AF_Set(GPIOA,7,5);	//PA7,AF5 
	GPIO_Set(GPIOA,PIN8,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PA8 T_PEN 推挽输出
	GPIO_Set(GPIOA,PIN9|PIN10,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PA9,PA10,ESP串口复用功能,上拉输出
	GPIO_AF_Set(GPIOA,9,7);	//PA9,AF7
	GPIO_AF_Set(GPIOA,10,7);//PA10,AF7  	
//	//PA11 USB D+
//	//PA12 USB D-
//	//PA13 SWDIO
//	//PA14 SWCLK
	GPIO_Set(GPIOA,PIN15,GPIO_MODE_OUT,GPIO_OTYPE_OD,GPIO_SPEED_50M,GPIO_PUPD_NONE);//PA15 MH模块按键 推挽输出
	USART2_RX = 1;
	//GPIOB	
	GPIO_Set(GPIOB,PIN0,GPIO_MODE_AIN,0,0,GPIO_PUPD_PU);  //ADC1_IN8
	GPIO_Set(GPIOB,PIN1,GPIO_MODE_AIN,0,0,GPIO_PUPD_PU);  //ADC1_IN9
	GPIO_Set(GPIOB,PIN2,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU); //SPI3 CS 推挽输出
	GPIO_Set(GPIOB,7<<3,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);	//SPI3 PB3~5复用功能输出	
	GPIO_AF_Set(GPIOB,3,6);	//PB3,AF5
	GPIO_AF_Set(GPIOB,4,6);	//PB4,AF5
	GPIO_AF_Set(GPIOB,5,6);	//PB5,AF5 
//	I2C1_SCL 
//	I2C1_SDA 
	GPIO_Set(GPIOB,PIN8|PIN9,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PB8,PB9,复用功能,上拉输出
	GPIO_AF_Set(GPIOB,8,9);//PA11,AF9
	GPIO_AF_Set(GPIOB,9,9);//PA12,AF9
//	I2C2_SCL 
//	I2C2_SDA 
	GPIO_Set(GPIOB,PIN12|PIN13,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PB12,PB13,复用功能,上拉输出
	GPIO_AF_Set(GPIOB,12,9);//PA11,AF9
	GPIO_AF_Set(GPIOB,13,9);//PA12,AF9
	GPIO_Set(GPIOB,PIN14,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//	CAN1_STB 
	GPIO_Set(GPIOB,PIN15,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//	CAN2_STB 
	
	//GPIOC
	GPIO_Set(GPIOC,PIN0,GPIO_MODE_AIN,0,0,GPIO_PUPD_PU);  //ADC1_IN10
	GPIO_Set(GPIOC,PIN1,GPIO_MODE_AIN,0,0,GPIO_PUPD_PU);  //ADC1_IN11
	GPIO_Set(GPIOC,PIN2,GPIO_MODE_AIN,0,0,GPIO_PUPD_PU);  //ADC1_IN12
	GPIO_Set(GPIOC,PIN3,GPIO_MODE_AIN,0,0,GPIO_PUPD_PU);  //ADC1_IN13
//	PC4预留
//	PC5预留
//	T_MOSI
//	T_MISO
//	SDIO_D0  
//	SDIO_D1  
//	SDIO_D2  
//	SDIO_D3  
//	SDIO_SCK 
	LED0=1;
	GPIO_Set(GPIOC,PIN13,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);  //LED0 推挽输出
//	PC14预留
//	PC15预留
	
	//GPIOD
	GPIO_Set(GPIOD,PIN0|PIN1|PIN4|PIN5|PIN7|PIN8|PIN9|PIN10|PIN12|PIN14|PIN15,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);	//PD0,1,4,5,8,9,10,14,15 AF OUT		
	GPIO_AF_Set(GPIOD,0,12);	//PD0,AF12  FMC_D2    
	GPIO_AF_Set(GPIOD,1,12);	//PD1,AF12  FMC_D3
//	SDIO_CMD  
//	预留    
	GPIO_AF_Set(GPIOD,4,12);	//PD4,AF12  FMC_NOE
	GPIO_AF_Set(GPIOD,5,12);	//PD5,AF12  FMC_NWE
//	预留    
	GPIO_AF_Set(GPIOD,7,12);	//PD7,AF12  FMC_NE1
	GPIO_AF_Set(GPIOD,8,12);	//PD8,AF12  FMC_D13
	GPIO_AF_Set(GPIOD,9,12);	//PD9,AF12  FMC_D14
	GPIO_AF_Set(GPIOD,10,12);	//PD10,AF12  FMC_D15
//	T_SCK     
	GPIO_AF_Set(GPIOD,12,12);	//PD12,AF12  FMC_A17
//	T_CS      
	GPIO_AF_Set(GPIOD,14,12);	//PD14,AF12  FMC_D0
	GPIO_AF_Set(GPIOD,15,12);	//PD15,AF12  FMC_D1


	//GPIOE
	GPIO_Set(GPIOE,PIN0|PIN1|PIN2|PIN3|PIN4|PIN5|PIN6,GPIO_MODE_IN,0,0,GPIO_PUPD_PU);
//	KEY_0_IN    
//	KEY_1_IN    
//	KEY_2_IN    
//	KEY_3_IN    
//	ROLLER_LEFT 
//	ROLLER_DOWN 
//	ROLLER_RIGHT
	GPIO_Set(GPIOE,(0X1FF<<7),GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);	
	GPIO_AF_Set(GPIOE,7,12);	//PE7,AF12  FMC_D4
	GPIO_AF_Set(GPIOE,8,12);	//PE8,AF12  FMC_D5
	GPIO_AF_Set(GPIOE,9,12);	//PE9,AF12  FMC_D6
	GPIO_AF_Set(GPIOE,10,12);	//PE10,AF12  FMC_D7
	GPIO_AF_Set(GPIOE,11,12);	//PE11,AF12  FMC_D8
	GPIO_AF_Set(GPIOE,12,12);	//PE12,AF12  FMC_D9
	GPIO_AF_Set(GPIOE,13,12);	//PE13,AF12  FMC_D10
	GPIO_AF_Set(GPIOE,14,12);	//PE14,AF12  FMC_D11
	GPIO_AF_Set(GPIOE,15,12);	//PE15,AF12  FMC_D12
	

#endif

}

//JTAG转IO
void GPIO_JtagToIo(void)
{
	//关JTAG调试接口 
	RCC->APB2ENR |= 1<<0;  //AFIO
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
}
 



//
void GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState)
{
//  uint32_t tmp = 0x00, tmp1 = 0x00, tmpreg = 0x00, tmpmask = 0x00;
// 
//  
//  if((GPIO_Remap & 0x80000000) == 0x80000000)
//  {
//    tmpreg = AFIO->MAPR2;
//  }
//  else
//  {
//    tmpreg = AFIO->MAPR;
//  }

//  tmpmask = (GPIO_Remap & DBGAFR_POSITION_MASK) >> 0x10;
//  tmp = GPIO_Remap & LSB_MASK;

//  if ((GPIO_Remap & (DBGAFR_LOCATION_MASK | DBGAFR_NUMBITS_MASK)) == (DBGAFR_LOCATION_MASK | DBGAFR_NUMBITS_MASK))
//  {
//    tmpreg &= DBGAFR_SWJCFG_MASK;
//    AFIO->MAPR &= DBGAFR_SWJCFG_MASK;
//  }
//  else if ((GPIO_Remap & DBGAFR_NUMBITS_MASK) == DBGAFR_NUMBITS_MASK)
//  {
//    tmp1 = ((uint32_t)0x03) << tmpmask;
//    tmpreg &= ~tmp1;
//    tmpreg |= ~DBGAFR_SWJCFG_MASK;
//  }
//  else
//  {
//    tmpreg &= ~(tmp << ((GPIO_Remap >> 0x15)*0x10));
//    tmpreg |= ~DBGAFR_SWJCFG_MASK;
//  }

//  if (NewState != DISABLE)
//  {
//    tmpreg |= (tmp << ((GPIO_Remap >> 0x15)*0x10));
//  }

//  if((GPIO_Remap & 0x80000000) == 0x80000000)
//  {
//    AFIO->MAPR2 = tmpreg;
//  }
//  else
//  {
//    AFIO->MAPR = tmpreg;
//  }  
//	
}

//GPIO不应该被调用的陷阱
void GPIO_Trap(void)
{
	while(1)
	{
		
	}
}
