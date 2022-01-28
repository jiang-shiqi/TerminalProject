/*********************************************************************************************************** 
*                                                                                                          *
* 文件名称: test.c                                                                                         *
* 描    述:                                                                                                *
* 作    者: 姜世奇                                                                                         *
* 当前版本: 1.0.1                                                                                          * 
* 完成时间:                                                                                                *
* ---------------------------------------------------------------------------------------------------------*
* 历史信息:                                                                                                *
*           <Date>            |    <Version>    |    <Author>    |    <Description>                        *
* ---------------------------------------------------------------------------------------------------------*
*   2019年9月25日 21:33:40    |      1.0.1      |     姜世奇     |     Create file                         *            
*----------------------------------------------------------------------------------------------------------*
***********************************************************************************************************/
#include "include.h" 	
#include "Delay.h"	 
#include "GUI.h" 
#include "KEY.h"
#include "systick.h"
#include "API.h"
#include "LED.h"
#include "GPIO.h" 
#include "SPI.h"
#include "w25qxx.h"
#include "ADC.h" 
#include "GUI_App.h"
#include "Line_In.h"
#include "Analog_Signal_Processing.h"
#include "Rocker.h"
//#include "MMC_SD.h"
//#include "Files.h"
#include "ESP8266_AT.h"
#include "LCD.h"
#include "can.h"
#include "ESP32.h"
#include "exti.h"
 
	 
void Sys_Init( void )
{
    //驱动初始化 
	Stm32_Clock_Init(336,8,2,7);//设置时钟,168Mhz  
	API_Init(168);	  	//延时初始化  
	
	//LCD初始化需要延时函数 需优化
	INTX_ENABLE(); 
	SysTick->CTRL |= 1<<0;								//使能SysTick定时器 
	//单片机初始化
	GPIO_Init();
	EXTIX_Init();
	ADC_init();
	USART_init(1,115200); 
	LED_init();
	SPI_Init(SPI1);
	SPI_Init(SPI3);
	USART2_TX = 1;
 	CAN_Mode_Init(CAN1,500,0);	//CAN初始化,波特率500Kbps    
 	CAN_Mode_Init(CAN2,500,1);	//CAN初始化,波特率500Kbps    
//	IIC_Init();     

	//设备初始化
	LCD_Init(); 
	SPI_SetSpeed(SPI1, SPI_SPEED_4);
	SPI_SetSpeed(SPI3, SPI_SPEED_4);
	 
//  W25QXX_Init();    	//SPI1       
//	SD_Initialize();		//SPI2
//	OLED_Init(); 

	//service服务初始化
//	KEY_init(); 
  ASP_Init();
//  Rocker_Init();
//  FileManager_Init();
	ESP32_Init();

	
}


void Sys_Startup_Init( void )
{
//  OLED_Clear();
//  GUI_Clear(); 
	
	//最后一步使能嘀嗒定时器 开启API功能 
	//替换为API使能位 
//	delay_ms(500);
	API_SetEnable(1);
}


void calibration(void);
void Normal_Mode(void);

u32 num;

int main(void)
{				    
//	u32 i,j;
//	u16 id;
//	u8 canbuf[8] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
	
	Sys_Init(); 
	Sys_Startup_Init();
	
	
//	
//	//SD卡测试连接用
//	num = SD_Initialize();
	
//	//SPI测试
//	while(1)
//	{
//		id = W25QXX_ReadID();
//		if (id == W25Q128 || id == NM25Q128)
//			break;
//	} 
	
//	//CAN测试
//	CAN_Send_Msg(CAN1,0x123,canbuf,8);	//发送8个字节
//	CAN_Send_Msg(CAN2,0x123,canbuf,8);	//发送8个字节
//	CAN_Receive_Msg(CAN1,canbuf);
	
	while(1)
	{   
		num = SysTick->VAL;
		
		Task_Service();

//		while(W25QXX_ReadID() != W25Q128);
//  	API_Update();
		

//		GUI_Test();                         //OLED测试
	 
	}	 
}
  




















