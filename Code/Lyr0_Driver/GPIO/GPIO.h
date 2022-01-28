/***********************************************************************************************************
* ��Ȩ                                                                                                     *
*                                                                                                          *
* �ļ�����: GPIO.h                                                                                         *
* ��    ��: GPIO���ñ�                                                                                     *
* ��    ��: ������                                                                                         *
* ��ǰ�汾: 1.0.1                                                                                          * 
* ���ʱ��: 2019��9��25��                                                                                  *
* ---------------------------------------------------------------------------------------------------------*
* ��ʷ��Ϣ:                                                                                                *
*           <Date>            |    <Version>    |    <Author>    |    <Description>                        *
* ---------------------------------------------------------------------------------------------------------*
*   2019��9��25�� 21:33:40    |      1.0.1      |     ������     |     Create file                         *            
*----------------------------------------------------------------------------------------------------------*
***********************************************************************************************************/
 
#ifndef __GPIO_H_
#define __GPIO_H_  
#include "include.h"
#include "register.h"
#include "ADC.h"


/*===========================================================================================================================================
  GPIOA �˿�����
  -------------------------------------------------------------------------------------------------------------------------------------
  | ����              | �˿�       |  ����  |  ����  |  ��ֵ  |  ������ʹ��  |  ��/����  |  ˵��
  ===================================================================================================================================*/
#define BAT_VIN          Get_Adc_Value(0)   // AD        1            0            0     ��ص�ѹ���� 
//#define ADC1_IN1         Get_Adc_Value(1)   // AD        1            0            0     ��չAD����1
#define ADC1_IN1         PAIN_PA1      //      IN        1            0            0     ��ʱ������ESP32�ӻ������������
#define USART2_TX        PAOUT_PA2     //      AF        1            0            0     ����2���Ͷ�  
#define USART2_RX        PAOUT_PA3     //      AF        1            1            1     ����2���ն�   
#define ADC1_IN4         Get_Adc_Value(4)   // AD        1            0            0     ��չAD����4
#define ESP_SCK          GPIO_Trap()   //      AF        1            0            0     ESP_Clk        
#define ESP_MISO         GPIO_Trap()   //      AF        1            0            0     ESP_Miso        
#define ESP_MOSI         GPIO_Trap()   //      AF        1            0            0     ESP_Mosi        
#define T_PEN            PAOUT_PA8     //      OUT       1            0            0     LCD���� PEN��
#define ESP_TXD          GPIO_Trap()   //      AF        1            0            0     ESP8266���նˣ��������ͣ�  
#define ESP_RXD          GPIO_Trap()   //      AF        1            0            1     ESP8266���Ͷˣ��������գ�
#define USB_FS_DM        GPIO_Trap()   //      AF        1            0            0     USB D+        
#define USB_FS_DP        GPIO_Trap()   //      AF        1            0            0     USB D-        
#define SWDIO            GPIO_Trap()   //      AF        1            0            0     �������ݿ�          
#define SWCLK            GPIO_Trap()   //      AF        1            0            0     ����ʱ�ӿ�       
#define MH_Key           PAOUT_PA15    //      OUT       1            0            0     ��Դģ�鰴��  

/*===========================================================================================================================================
  GPIOB �˿�����
  -------------------------------------------------------------------------------------------------------------------------------------
  | ����              | �˿�       |  ����  |  ����  |  ��ֵ  |  ������ʹ��  |  ��/����  |  ˵��
  ===================================================================================================================================*/
#define ADC1_IN8         Get_Adc_Value(8)   // AD        1            0            0      ��չAD����8 
#define ADC1_IN9         Get_Adc_Value(9)   // AD        1            0            0      ��չAD����9 
#define ESP_CS           PBOUT_PB2  //         AF        1            0            0      ESP_CS       
#define SPI3_SCK         GPIO_Trap()//         AF        1            0            0      ��չSPI�ӿ� CLK 
#define SPI3_MISO        GPIO_Trap()//         AF        1            0            0      ��չSPI�ӿ� MISO
#define SPI3_MOSI        GPIO_Trap()//         AF        1            0            0      ��չSPI�ӿ� MOSI
#define I2C1_SCL         GPIO_Trap()//         AF        1            0            0      ��չI2C1�ӿ� SCL
#define I2C1_SDA         GPIO_Trap()//         AF        1            0            0      ��չI2C1�ӿ� SDA
#define CAN1_TX          GPIO_Trap()//         AF        1            0            0      ��չCAN1�ӿ� TX 
#define CAN1_RX          GPIO_Trap()//         AF        1            0            0      ��չCAN1�ӿ� RX
#define I2C2_SCL         GPIO_Trap()//         AF        1            0            0      ��չI2C2�ӿ� SCL
#define I2C2_SDA         GPIO_Trap()//         AF        1            0            0      ��չI2C2�ӿ� SDA
#define CAN2_TX          GPIO_Trap()//         AF        1            0            0      ��չCAN2�ӿ� TX 
#define CAN2_RX          GPIO_Trap()//         AF        1            0            0      ��չCAN2�ӿ� RX
#define CAN1_STB         PBOUT_PB14 //         OUT       1            0            0      ��չCAN1�ӿ� STB
#define CAN2_STB         PBOUT_PB15 //         OUT       1            0            0      ��չCAN2�ӿ� STB

/*===========================================================================================================================================
  GPIOC �˿�����
  -------------------------------------------------------------------------------------------------------------------------------------
  | ����              | �˿�       |  ����  |  ����  |  ��ֵ  |  ������ʹ��  |  ��/����  |  ˵��
  ===================================================================================================================================*/
#define ADC1_IN10        Get_Adc_Value(10)  // AD        1            0            0      ��չAD����10
#define ADC1_IN11        Get_Adc_Value(11)  // AD        1            0            0      ��չAD����11
#define ADC1_IN12        Get_Adc_Value(12)  // AD        1            0            0      ��չAD����12
#define ADC1_IN13        Get_Adc_Value(13)  // AD        1            0            0      ��չAD����13
//#define Ԥ��             PCOUT_PC4  //         OUT       1            0            0  
//#define Ԥ��             PCOUT_PC5  //         OUT       1            0            0  
#define T_MOSI           PCOUT_PC6  //         OUT       1            0            0      LCD���� MOSI
#define T_MISO           PCOUT_PC7  //         OUT       1            0            0      LCD���� MISO
#define SDIO_D0          GPIO_Trap()//         AF        1            0            0      TF��SDIO�ӿ� D0 
#define SDIO_D1          GPIO_Trap()//         AF        1            0            0      TF��SDIO�ӿ� D1 
#define SDIO_D2          GPIO_Trap()//         AF        1            0            0      TF��SDIO�ӿ� D2   
#define SDIO_D3          GPIO_Trap()//         AF        1            0            0      TF��SDIO�ӿ� D3  
#define SDIO_SCK         GPIO_Trap()//         AF        1            0            0      TF��SDIO�ӿ� SCK 
#define LED0             PCOUT_PC13 //         AF        1            0            0      ������� 3
//#define Ԥ��             PCOUT_PC14 //         OUT       1            0            0  
//#define Ԥ��             PCOUT_PC15 //         OUT       1            0            0  

/*===========================================================================================================================================
  GPIOD �˿�����
  -------------------------------------------------------------------------------------------------------------------------------------
  | ����              | �˿�       |  ����  |  ����  |  ��ֵ  |  ������ʹ��  |  ��/����  |  ˵��
  ===================================================================================================================================*/
#define FMC_D2           GPIO_Trap()//         AF        1            0            0      LCD FSMC�ӿ� D2
#define FMC_D3           GPIO_Trap()//         AF        1            0            0      LCD FSMC�ӿ� D3 
#define SDIO_CMD         GPIO_Trap()//         AF        1            0            0      TF��SDIO�ӿ� CMD 
//#define Ԥ��             PDOUT_PD3  //         OUT       1            0            0       
#define FMC_NOE          GPIO_Trap()//         AF        1            0            0      LCD FSMC�ӿ� NOE 
#define FMC_NWE          GPIO_Trap()//         AF        1            0            0      LCD FSMC�ӿ� NWE 
//#define Ԥ��             PDOUT_PD6  //         OUT       1            0            0       
#define FMC_NE1          GPIO_Trap()//         AF        1            0            0      LCD FSMC�ӿ� NE1 
#define FMC_D13          GPIO_Trap()//         AF        1            0            0      LCD FSMC�ӿ� D13 
#define FMC_D14          GPIO_Trap()//         AF        1            0            0      LCD FSMC�ӿ� D14
#define FMC_D15          GPIO_Trap()//         AF        1            0            0      LCD FSMC�ӿ� D15
#define T_SCK            PDOUT_PD11 //         OUT       1            0            0      LCD���� SCK 
#define FMC_A17          GPIO_Trap()//         AF        1            0            0      LCD FSMC�ӿ� A17 
#define T_CS             PDOUT_PD13 //         OUT       1            0            0      LCD���� CS 
#define FMC_D0           GPIO_Trap()//         AF        1            0            0      LCD FSMC�ӿ� D0 
#define FMC_D1           GPIO_Trap()//         AF        1            0            0      LCD FSMC�ӿ� D1 

/*===========================================================================================================================================
  GPIOE �˿�����
  -------------------------------------------------------------------------------------------------------------------------------------
  | ����              | �˿�       |  ����  |  ����  |  ��ֵ  |  ������ʹ��  |  ��/����  |  ˵��
  ===================================================================================================================================*/
#define KEY_0_IN         PEIN_PE0   //         IN        1            0            0      ����0
#define KEY_1_IN         PEIN_PE1   //         IN        1            0            0      ����1 
#define KEY_2_IN         PEIN_PE2   //         IN        1            0            0      ����2 
#define KEY_3_IN         PEIN_PE3   //         IN        1            0            0      ����3 
#define ROLLER_LEFT      PEIN_PE4   //         IN        1            0            0      ���� ��� 
#define ROLLER_DOWN      PEIN_PE5   //         IN        1            0            0      ���� ���� 
#define ROLLER_RIGHT     PEIN_PE6   //         IN        1            0            0      ���� �Ҽ� 
#define FMC_D4           GPIO_Trap()//         AF        1            0            0      LCD FSMC�ӿ� D4 
#define FMC_D5           GPIO_Trap()//         AF        1            0            0      LCD FSMC�ӿ� D5 
#define FMC_D6           GPIO_Trap()//         AF        1            0            0      LCD FSMC�ӿ� D6 
#define FMC_D7           GPIO_Trap()//         AF        1            0            0      LCD FSMC�ӿ� D7 
#define FMC_D8           GPIO_Trap()//         AF        1            0            0      LCD FSMC�ӿ� D8 
#define FMC_D9           GPIO_Trap()//         AF        1            0            0      LCD FSMC�ӿ� D9 
#define FMC_D10          GPIO_Trap()//         AF        1            0            0      LCD FSMC�ӿ� D10 
#define FMC_D11          GPIO_Trap()//         AF        1            0            0      LCD FSMC�ӿ� D11 
#define FMC_D12          GPIO_Trap()//         AF        1            0            0      LCD FSMC�ӿ� D12 
																																													 
																																													 
//JTAG�ӿ�תIO�ú궨��
#define GPIO_Remap_SWJ_JTAGDisable  ((uint32_t)0x00300200)  /*!< JTAG-DP Disabled and SW-DP Enabled */
#define EVCR_PORTPINCONFIG_MASK     ((uint16_t)0xFF80)
#define LSB_MASK                    ((uint16_t)0xFFFF)
#define DBGAFR_POSITION_MASK        ((uint32_t)0x000F0000)
#define DBGAFR_SWJCFG_MASK          ((uint32_t)0xF0FFFFFF)
#define DBGAFR_LOCATION_MASK        ((uint32_t)0x00200000)
#define DBGAFR_NUMBITS_MASK         ((uint32_t)0x00100000)

 
//��������
void GPIO_Init(void);
void GPIO_JtagToIo(void);
void GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState);
void GPIO_Trap(void);














#endif
