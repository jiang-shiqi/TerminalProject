#include "USART.h" 
#include "ESP8266_AT.h" 

#ifdef __CM3_CORE_H__
////#define PCLK1_HZ 36000000
////#define PCLK2_HZ 72000000
////  

//////串口1中断服务程序
////void USART1_IRQHandler(void)
////{
////	uint8_t cupA;
////	uint8_t res;
////	if(USART1->SR&(1<<5))	//接收到数据
////	{	 
////		cupA = USART1->DR; 
////		
////		switch(ESP_Device[0].receivedData.status)
////		{
////			case 0:
////				if(cupA == 0x0D) 
////				{
////					ESP_Device[0].receivedData.status++; 
////					ESP_Device[0].receivedData.lenth = 0;
////				}
////				break;
////			case 1:
////				if(cupA == 0x0A) 
////					ESP_Device[0].receivedData.status++; 
////				else 
////					ESP_Device[0].receivedData.status = 0;
////				break;		
////			case 2:
////				if(cupA == 0x0D)
////				{
////					if(ESP_Device[0].receivedData.lenth == 0)  	//如果0D0A后还是个0D0A 则将最后的0D0A作为开头
////					{
////						ESP_Device[0].receivedData.lenth = 0;
////						ESP_Device[0].receivedData.status = 1; 
////					}
////					else
////						ESP_Device[0].receivedData.status++;  
////				}
////					
////				else if(cupA >= ESP_RECEIVEDDATA_MAX-1)
////				{
////					ESP_Device[0].receivedData.status = 0;
////					ESP_Device[0].receivedData.lenth = 0;
////				}
////				else 
////					ESP_Device[0].receivedData.data.data[ESP_Device[0].receivedData.lenth] = cupA; 
////				break;
////			case 3:
////				if(cupA == 0x0A)
////				{ 
////					//分拣接收数据类型
////					res = ESP_JudgeRXDataType(&ESP_Device[0]); 
////					 
////					if(res == 0)															//判断结果正确 状态切为接收完毕
////					{
////						ESP_Device[0].receivedData.status = 4;
////						break;
////					}
////				}	
////				ESP_Device[0].receivedData.status = 0;      //判断结果不正确 则丢弃接收数据
////				ESP_Device[0].receivedData.lenth = 0;
////				break;
////		}  
////	}
////}

////void USART2_IRQHandler(void)
////{
////	if(USART2->SR&(1<<5))	//接收到数据
////	{	 
////			 									     
////	}
////}



//////串口初始化函数
//////输入：com 串口号 bound 波特率
////void USART_init(u8 com,u32 bound)
////{
////	float temp;				//
////	u16 mant,frac;		//整数部分 小数部分
////																//换算出USARTDIV寄存器的值
////	if(1==com){
////		temp=(float)(PCLK2_HZ/(bound * 16));	//获取USARTDIV寄存器的（float）值	mant=temp*16;
////		mant = temp;                                    //取得整数部分
////		frac = (temp-mant)*16;                          //取得小数部分
////		mant=mant*16+frac;
////		RCC->APB2ENR|=1<<2;          //使能GPIOA的时钟
////		RCC->APB2ENR|=1<<14;         //使能串口1时钟
//////		GPIOA->CRH &= 0xfffff00f;    //配置PA9为复用推挽
//////		GPIOA->CRH |= 0x000008b0;    //配置PA10为浮空输入 
////		RCC->APB2RSTR |= 1<<14;      //复位串口1
////		RCC->APB2RSTR &= ~(1<<14);    //停止复位
////		
////		USART1->BRR=mant;//0x0271;            //波特率设置
////		USART1->CR1|=0x200C;         //1停止位 无校验位
////		
////		USART1->CR1 |= 1<<5;         //打开接收中断
////		MY_NVIC_Init(3,3,USART1_IRQn,2);//设置中断优先级
////	}
////	else if(2==com)
////	{
////		temp=(float)(PCLK1_HZ/(bound * 16));	//获取USARTDIV寄存器的（float）值	mant=temp*16;
////		mant = temp;                                    //取得整数部分
////		frac = (temp-mant)*16;                          //取得小数部分
////		mant=mant*16+frac;
////		RCC->APB2ENR|=1<<2;          //使能GPIOA的时钟
////		RCC->APB1ENR|=1<<17;         //使能串口1时钟
//////		GPIOA->CRL &= 0xffff00ff;    //配置PA2为复用推挽
//////		GPIOA->CRL |= 0x00008b00;    //配置PA3为浮空输入 	
////		RCC->APB1RSTR |= 1<<17;      //复位串口2
////		RCC->APB1RSTR &= ~(1<<17);    //停止复位
////		
////		USART2->BRR=mant;//0x0271;            //波特率设置
////		USART2->CR1|=0x200C;         //1停止位 无校验位
////		
////		USART2->CR1 |= 1<<5;         //打开接收中断
////		MY_NVIC_Init(3,3,USART2_IRQn,2);//设置中断优先级
////	}
////} 
#endif

#ifdef __CORE_CM4_H_GENERIC
#define PCLK1_HZ 42000000
#define PCLK2_HZ 84000000
  

//串口1中断服务程序
void USART1_IRQHandler(void)
{
//	uint8_t cupA; 
	
	if(USART1->SR&(1<<5))	//接收到数据
	{	 
//		cupA = USART1->DR;  
	}
}

void USART2_IRQHandler(void)
{
	if(USART2->SR&(1<<5))	//接收到数据
	{	 
			 									     
	}
}



//串口初始化函数
//输入：com 串口号 bound 波特率
void USART_init(u8 com,u32 bound)
{
	float temp;				//
	u16 mant,frac;		//整数部分 小数部分
																//换算出USARTDIV寄存器的值
	if(1==com){
		temp=(float)(PCLK2_HZ/(bound * 16));	//获取USARTDIV寄存器的（float）值	mant=temp*16;
		mant = temp;                                    //取得整数部分
		frac = (temp-mant)*16;                          //取得小数部分
		mant=mant*16+frac; 
		RCC->APB2ENR|=1<<4;  	//使能串口1时钟 
//		GPIO_Set(GPIOA,PIN9|PIN10,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PA9,PA10,复用功能,上拉输出
//		GPIO_AF_Set(GPIOA,9,7);	//PA9,AF7
//		GPIO_AF_Set(GPIOA,10,7);//PA10,AF7  	
		RCC->APB2RSTR |= 1<<4;      //复位串口1
		RCC->APB2RSTR &= ~(1<<4);    //停止复位
		
		USART1->BRR=mant;//0x0271;            //波特率设置
		USART1->CR1&=~(1<<15); 	//设置OVER8=0 
		USART1->CR1|=1<<3;  	//串口发送使能 
		
#if EN_USART1_RX		  	//如果使能了接收 
		USART1->CR1|=1<<2;  	//串口接收使能
		USART1->CR1|=1<<5;    	//接收缓冲区非空中断使能	    	
		MY_NVIC_Init(3,3,USART1_IRQn,2);//组2，最低优先级  
#endif
		USART1->CR1|=1<<13;  	//串口使能
	}
	else if(2==com)
	{
//		temp=(float)(PCLK1_HZ/(bound * 16));	//获取USARTDIV寄存器的（float）值	mant=temp*16;
//		mant = temp;                                    //取得整数部分
//		frac = (temp-mant)*16;                          //取得小数部分
//		mant=mant*16+frac;
//		RCC->APB2ENR|=1<<2;          //使能GPIOA的时钟
//		RCC->APB1ENR|=1<<17;         //使能串口1时钟 
////		GPIO_Set(GPIOA,PIN2|PIN3,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PA2,PA3,复用功能,上拉输出
////		GPIO_AF_Set(GPIOA,2,7);	//PA9,AF7
////		GPIO_AF_Set(GPIOA,3,7);//PA10,AF7  	
//		RCC->APB1RSTR |= 1<<17;      //复位串口2
//		RCC->APB1RSTR &= ~(1<<17);    //停止复位
//		
//		USART2->BRR=mant;//0x0271;            //波特率设置
//		USART2->CR1|=0x200C;         //1停止位 无校验位
//		
//		USART2->CR1 |= 1<<5;         //打开接收中断
//		MY_NVIC_Init(3,3,USART2_IRQn,2);//设置中断优先级
	}
} 
#endif

void USART_Send_Byte(u8 com,u8 C_dat)
{
	if(1==com)
	{
		USART1->DR=C_dat;
		while((USART1->SR&0x40)==0);
	}
	else if(2==com)
	{
		USART2->DR=C_dat;
		while((USART2->SR&0x40)==0);
	}
	
}

void USART_Send_Word(u8 com,char *P_word)
{
	while(*P_word!=0)
	{
		if(1==com)
		{
			USART1->DR=*P_word;
			while((USART1->SR&0x40)==0);
		}
		else if(2==com)
		{
			USART2->DR=*P_word;
			while((USART2->SR&0x40)==0);
		} 
		P_word++;
	}
}

void USART_Send_Word_Lenth(u8 com,char *P_word,u16 lenth)
{
	while(lenth!=0)
	{
		if(1==com)
		{
			USART1->DR=*P_word;
			while((USART1->SR&0x40)==0);
		}
		else if(2==com)
		{
			USART2->DR=*P_word;
			while((USART2->SR&0x40)==0);
		} 
		P_word++;
		lenth--;
	}
}

void USART_Send_Enter(u8 com)
{
	USART1->DR = 0x0D;
	while((USART1->SR&0x40)==0);
	USART1->DR = 0x0A;
	while((USART1->SR&0x40)==0);
}

void USART_Send_Int_Num(u8 com,u32 I_num,u8 len)
{
	switch(len)
	{
		case 10:USART_Send_Byte(com,I_num/1000000000%10+0x30);
		case 9:USART_Send_Byte(com,I_num/100000000%10+0x30);
		case 8:USART_Send_Byte(com,I_num/10000000%10+0x30);
		case 7:USART_Send_Byte(com,I_num/1000000%10+0x30);
		case 6:USART_Send_Byte(com,I_num/100000%10+0x30);
		case 5:USART_Send_Byte(com,I_num/10000%10+0x30);
		case 4:USART_Send_Byte(com,I_num/1000%10+0x30);
		case 3:USART_Send_Byte(com,I_num/100%10+0x30);
		case 2:USART_Send_Byte(com,I_num/10%10+0x30);
		case 1:USART_Send_Byte(com,I_num%10+0x30);
	}
}

void USART_Send_Int(u8 com, u32 num)
{
	if(num < 10) 
		USART_Send_Int_Num(com,num,1);
	else if(num < 100)
		USART_Send_Int_Num(com,num,2);
	else if(num < 1000)
		USART_Send_Int_Num(com,num,3);
	else if(num < 10000)
		USART_Send_Int_Num(com,num,4);
	else if(num < 100000)
		USART_Send_Int_Num(com,num,5);
	else if(num < 1000000)
		USART_Send_Int_Num(com,num,6);
	else if(num < 10000000)
		USART_Send_Int_Num(com,num,7);
	else if(num < 100000000)
		USART_Send_Int_Num(com,num,8);
	else if(num < 1000000000)
		USART_Send_Int_Num(com,num,9);
}
