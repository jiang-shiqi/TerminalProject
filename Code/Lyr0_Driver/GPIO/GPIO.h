/***********************************************************************************************************
* 版权                                                                                                     *
*                                                                                                          *
* 文件名称: GPIO.h                                                                                         *
* 描    述: GPIO配置表                                                                                     *
* 作    者: 姜世奇                                                                                         *
* 当前版本: 1.0.1                                                                                          * 
* 完成时间: 2019年9月25日                                                                                  *
* ---------------------------------------------------------------------------------------------------------*
* 历史信息:                                                                                                *
*           <Date>            |    <Version>    |    <Author>    |    <Description>                        *
* ---------------------------------------------------------------------------------------------------------*
*   2019年9月25日 21:33:40    |      1.0.1      |     姜世奇     |     Create file                         *            
*----------------------------------------------------------------------------------------------------------*
***********************************************************************************************************/
 
#ifndef __GPIO_H_
#define __GPIO_H_  
#include "include.h"
#include "register.h"
#include "ADC.h"


/*===========================================================================================================================================
  GPIOA 端口配置
  -------------------------------------------------------------------------------------------------------------------------------------
  | 名称              | 端口       |  引脚  |  方向  |  初值  |  上下拉使能  |  上/下拉  |  说明
  ===================================================================================================================================*/
#define BAT_VIN          Get_Adc_Value(0)   // AD        1            0            0     电池电压输入 
//#define ADC1_IN1         Get_Adc_Value(1)   // AD        1            0            0     扩展AD输入1
#define ADC1_IN1         PAIN_PA1      //      IN        1            0            0     暂时被用作ESP32从机动作检测引脚
#define USART2_TX        PAOUT_PA2     //      AF        1            0            0     串口2发送端  
#define USART2_RX        PAOUT_PA3     //      AF        1            1            1     串口2接收端   
#define ADC1_IN4         Get_Adc_Value(4)   // AD        1            0            0     扩展AD输入4
#define ESP_SCK          GPIO_Trap()   //      AF        1            0            0     ESP_Clk        
#define ESP_MISO         GPIO_Trap()   //      AF        1            0            0     ESP_Miso        
#define ESP_MOSI         GPIO_Trap()   //      AF        1            0            0     ESP_Mosi        
#define T_PEN            PAOUT_PA8     //      OUT       1            0            0     LCD触摸 PEN端
#define ESP_TXD          GPIO_Trap()   //      AF        1            0            0     ESP8266接收端（主机发送）  
#define ESP_RXD          GPIO_Trap()   //      AF        1            0            1     ESP8266发送端（主机接收）
#define USB_FS_DM        GPIO_Trap()   //      AF        1            0            0     USB D+        
#define USB_FS_DP        GPIO_Trap()   //      AF        1            0            0     USB D-        
#define SWDIO            GPIO_Trap()   //      AF        1            0            0     下载数据口          
#define SWCLK            GPIO_Trap()   //      AF        1            0            0     下载时钟口       
#define MH_Key           PAOUT_PA15    //      OUT       1            0            0     电源模块按键  

/*===========================================================================================================================================
  GPIOB 端口配置
  -------------------------------------------------------------------------------------------------------------------------------------
  | 名称              | 端口       |  引脚  |  方向  |  初值  |  上下拉使能  |  上/下拉  |  说明
  ===================================================================================================================================*/
#define ADC1_IN8         Get_Adc_Value(8)   // AD        1            0            0      扩展AD输入8 
#define ADC1_IN9         Get_Adc_Value(9)   // AD        1            0            0      扩展AD输入9 
#define ESP_CS           PBOUT_PB2  //         AF        1            0            0      ESP_CS       
#define SPI3_SCK         GPIO_Trap()//         AF        1            0            0      扩展SPI接口 CLK 
#define SPI3_MISO        GPIO_Trap()//         AF        1            0            0      扩展SPI接口 MISO
#define SPI3_MOSI        GPIO_Trap()//         AF        1            0            0      扩展SPI接口 MOSI
#define I2C1_SCL         GPIO_Trap()//         AF        1            0            0      扩展I2C1接口 SCL
#define I2C1_SDA         GPIO_Trap()//         AF        1            0            0      扩展I2C1接口 SDA
#define CAN1_TX          GPIO_Trap()//         AF        1            0            0      扩展CAN1接口 TX 
#define CAN1_RX          GPIO_Trap()//         AF        1            0            0      扩展CAN1接口 RX
#define I2C2_SCL         GPIO_Trap()//         AF        1            0            0      扩展I2C2接口 SCL
#define I2C2_SDA         GPIO_Trap()//         AF        1            0            0      扩展I2C2接口 SDA
#define CAN2_TX          GPIO_Trap()//         AF        1            0            0      扩展CAN2接口 TX 
#define CAN2_RX          GPIO_Trap()//         AF        1            0            0      扩展CAN2接口 RX
#define CAN1_STB         PBOUT_PB14 //         OUT       1            0            0      扩展CAN1接口 STB
#define CAN2_STB         PBOUT_PB15 //         OUT       1            0            0      扩展CAN2接口 STB

/*===========================================================================================================================================
  GPIOC 端口配置
  -------------------------------------------------------------------------------------------------------------------------------------
  | 名称              | 端口       |  引脚  |  方向  |  初值  |  上下拉使能  |  上/下拉  |  说明
  ===================================================================================================================================*/
#define ADC1_IN10        Get_Adc_Value(10)  // AD        1            0            0      扩展AD输入10
#define ADC1_IN11        Get_Adc_Value(11)  // AD        1            0            0      扩展AD输入11
#define ADC1_IN12        Get_Adc_Value(12)  // AD        1            0            0      扩展AD输入12
#define ADC1_IN13        Get_Adc_Value(13)  // AD        1            0            0      扩展AD输入13
//#define 预留             PCOUT_PC4  //         OUT       1            0            0  
//#define 预留             PCOUT_PC5  //         OUT       1            0            0  
#define T_MOSI           PCOUT_PC6  //         OUT       1            0            0      LCD触摸 MOSI
#define T_MISO           PCOUT_PC7  //         OUT       1            0            0      LCD触摸 MISO
#define SDIO_D0          GPIO_Trap()//         AF        1            0            0      TF卡SDIO接口 D0 
#define SDIO_D1          GPIO_Trap()//         AF        1            0            0      TF卡SDIO接口 D1 
#define SDIO_D2          GPIO_Trap()//         AF        1            0            0      TF卡SDIO接口 D2   
#define SDIO_D3          GPIO_Trap()//         AF        1            0            0      TF卡SDIO接口 D3  
#define SDIO_SCK         GPIO_Trap()//         AF        1            0            0      TF卡SDIO接口 SCK 
#define LED0             PCOUT_PC13 //         AF        1            0            0      推挽输出 3
//#define 预留             PCOUT_PC14 //         OUT       1            0            0  
//#define 预留             PCOUT_PC15 //         OUT       1            0            0  

/*===========================================================================================================================================
  GPIOD 端口配置
  -------------------------------------------------------------------------------------------------------------------------------------
  | 名称              | 端口       |  引脚  |  方向  |  初值  |  上下拉使能  |  上/下拉  |  说明
  ===================================================================================================================================*/
#define FMC_D2           GPIO_Trap()//         AF        1            0            0      LCD FSMC接口 D2
#define FMC_D3           GPIO_Trap()//         AF        1            0            0      LCD FSMC接口 D3 
#define SDIO_CMD         GPIO_Trap()//         AF        1            0            0      TF卡SDIO接口 CMD 
//#define 预留             PDOUT_PD3  //         OUT       1            0            0       
#define FMC_NOE          GPIO_Trap()//         AF        1            0            0      LCD FSMC接口 NOE 
#define FMC_NWE          GPIO_Trap()//         AF        1            0            0      LCD FSMC接口 NWE 
//#define 预留             PDOUT_PD6  //         OUT       1            0            0       
#define FMC_NE1          GPIO_Trap()//         AF        1            0            0      LCD FSMC接口 NE1 
#define FMC_D13          GPIO_Trap()//         AF        1            0            0      LCD FSMC接口 D13 
#define FMC_D14          GPIO_Trap()//         AF        1            0            0      LCD FSMC接口 D14
#define FMC_D15          GPIO_Trap()//         AF        1            0            0      LCD FSMC接口 D15
#define T_SCK            PDOUT_PD11 //         OUT       1            0            0      LCD触摸 SCK 
#define FMC_A17          GPIO_Trap()//         AF        1            0            0      LCD FSMC接口 A17 
#define T_CS             PDOUT_PD13 //         OUT       1            0            0      LCD触摸 CS 
#define FMC_D0           GPIO_Trap()//         AF        1            0            0      LCD FSMC接口 D0 
#define FMC_D1           GPIO_Trap()//         AF        1            0            0      LCD FSMC接口 D1 

/*===========================================================================================================================================
  GPIOE 端口配置
  -------------------------------------------------------------------------------------------------------------------------------------
  | 名称              | 端口       |  引脚  |  方向  |  初值  |  上下拉使能  |  上/下拉  |  说明
  ===================================================================================================================================*/
#define KEY_0_IN         PEIN_PE0   //         IN        1            0            0      按键0
#define KEY_1_IN         PEIN_PE1   //         IN        1            0            0      按键1 
#define KEY_2_IN         PEIN_PE2   //         IN        1            0            0      按键2 
#define KEY_3_IN         PEIN_PE3   //         IN        1            0            0      按键3 
#define ROLLER_LEFT      PEIN_PE4   //         IN        1            0            0      滚轮 左键 
#define ROLLER_DOWN      PEIN_PE5   //         IN        1            0            0      滚轮 按下 
#define ROLLER_RIGHT     PEIN_PE6   //         IN        1            0            0      滚轮 右键 
#define FMC_D4           GPIO_Trap()//         AF        1            0            0      LCD FSMC接口 D4 
#define FMC_D5           GPIO_Trap()//         AF        1            0            0      LCD FSMC接口 D5 
#define FMC_D6           GPIO_Trap()//         AF        1            0            0      LCD FSMC接口 D6 
#define FMC_D7           GPIO_Trap()//         AF        1            0            0      LCD FSMC接口 D7 
#define FMC_D8           GPIO_Trap()//         AF        1            0            0      LCD FSMC接口 D8 
#define FMC_D9           GPIO_Trap()//         AF        1            0            0      LCD FSMC接口 D9 
#define FMC_D10          GPIO_Trap()//         AF        1            0            0      LCD FSMC接口 D10 
#define FMC_D11          GPIO_Trap()//         AF        1            0            0      LCD FSMC接口 D11 
#define FMC_D12          GPIO_Trap()//         AF        1            0            0      LCD FSMC接口 D12 
																																													 
																																													 
//JTAG接口转IO用宏定义
#define GPIO_Remap_SWJ_JTAGDisable  ((uint32_t)0x00300200)  /*!< JTAG-DP Disabled and SW-DP Enabled */
#define EVCR_PORTPINCONFIG_MASK     ((uint16_t)0xFF80)
#define LSB_MASK                    ((uint16_t)0xFFFF)
#define DBGAFR_POSITION_MASK        ((uint32_t)0x000F0000)
#define DBGAFR_SWJCFG_MASK          ((uint32_t)0xF0FFFFFF)
#define DBGAFR_LOCATION_MASK        ((uint32_t)0x00200000)
#define DBGAFR_NUMBITS_MASK         ((uint32_t)0x00100000)

 
//函数声明
void GPIO_Init(void);
void GPIO_JtagToIo(void);
void GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState);
void GPIO_Trap(void);














#endif
