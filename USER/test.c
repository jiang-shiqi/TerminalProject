/*********************************************************************************************************** 
*                                                                                                          *
* �ļ�����: test.c                                                                                         *
* ��    ��:                                                                                                *
* ��    ��: ������                                                                                         *
* ��ǰ�汾: 1.0.1                                                                                          * 
* ���ʱ��:                                                                                                *
* ---------------------------------------------------------------------------------------------------------*
* ��ʷ��Ϣ:                                                                                                *
*           <Date>            |    <Version>    |    <Author>    |    <Description>                        *
* ---------------------------------------------------------------------------------------------------------*
*   2019��9��25�� 21:33:40    |      1.0.1      |     ������     |     Create file                         *            
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
    //������ʼ�� 
	Stm32_Clock_Init(336,8,2,7);//����ʱ��,168Mhz  
	API_Init(168);	  	//��ʱ��ʼ��  
	
	//LCD��ʼ����Ҫ��ʱ���� ���Ż�
	INTX_ENABLE(); 
	SysTick->CTRL |= 1<<0;								//ʹ��SysTick��ʱ�� 
	//��Ƭ����ʼ��
	GPIO_Init();
	EXTIX_Init();
	ADC_init();
	USART_init(1,115200); 
	LED_init();
	SPI_Init(SPI1);
	SPI_Init(SPI3);
	USART2_TX = 1;
 	CAN_Mode_Init(CAN1,500,0);	//CAN��ʼ��,������500Kbps    
 	CAN_Mode_Init(CAN2,500,1);	//CAN��ʼ��,������500Kbps    
//	IIC_Init();     

	//�豸��ʼ��
	LCD_Init(); 
	SPI_SetSpeed(SPI1, SPI_SPEED_4);
	SPI_SetSpeed(SPI3, SPI_SPEED_4);
	 
//  W25QXX_Init();    	//SPI1       
//	SD_Initialize();		//SPI2
//	OLED_Init(); 

	//service�����ʼ��
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
	
	//���һ��ʹ����શ�ʱ�� ����API���� 
	//�滻ΪAPIʹ��λ 
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
//	//SD������������
//	num = SD_Initialize();
	
//	//SPI����
//	while(1)
//	{
//		id = W25QXX_ReadID();
//		if (id == W25Q128 || id == NM25Q128)
//			break;
//	} 
	
//	//CAN����
//	CAN_Send_Msg(CAN1,0x123,canbuf,8);	//����8���ֽ�
//	CAN_Send_Msg(CAN2,0x123,canbuf,8);	//����8���ֽ�
//	CAN_Receive_Msg(CAN1,canbuf);
	
	while(1)
	{   
		num = SysTick->VAL;
		
		Task_Service();

//		while(W25QXX_ReadID() != W25Q128);
//  	API_Update();
		

//		GUI_Test();                         //OLED����
	 
	}	 
}
  




















