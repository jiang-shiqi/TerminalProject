/***********************************************************************************************************
* 版权                                                                                                     *
*                                                                                                          *
* 文件名称: register.h                                                                                     *
* 描    述: 包含寄存器联合体与宏定义                                                                       *
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
#ifndef __REGISTER_H_
#define __REGISTER_H_

#include "include.h"


#ifdef __CM3_CORE_H__

//GPIO
typedef union { 
uint32_t Byte; 
	struct {
		uint8_t P0         :1;                                       
		uint8_t P1         :1;                                       
		uint8_t P2         :1;                                       
		uint8_t P3         :1;                                       
		uint8_t P4         :1;                                       
		uint8_t P5         :1;                                       
		uint8_t P6         :1;                                       
		uint8_t P7         :1; 
    uint8_t P8         :1;                                       
		uint8_t P9         :1;                                       
		uint8_t P10        :1;                                       
		uint8_t P11        :1;                                       
		uint8_t P12        :1;                                       
		uint8_t P13        :1;                                       
		uint8_t P14        :1;                                       
		uint8_t P15        :1; 		
	} Bits;
} GPIO_DR_Union;


typedef union { 
uint32_t Byte; 
	struct {
		uint8_t P0         :4;                                       
		uint8_t P1         :4;                                       
		uint8_t P2         :4;                                       
		uint8_t P3         :4;                                       
		uint8_t P4         :4;                                       
		uint8_t P5         :4;                                       
		uint8_t P6         :4;                                       
		uint8_t P7         :4; 
		
	} Bits;
} GPIO_CR_Union;

 
typedef struct
{
	__IO GPIO_CR_Union CRL;
	__IO GPIO_CR_Union CRH;
	__IO GPIO_DR_Union IDR;
	__IO GPIO_DR_Union ODR;
	__IO uint32_t BSRR;
	__IO uint32_t BRR;
	__IO uint32_t LCKR;
} REG_GPIO_union;
#endif
#ifdef __CORE_CM4_H_GENERIC

typedef union { 
uint32_t Byte; 
	struct {
		uint8_t P0         :2;                                       
		uint8_t P1         :2;                                       
		uint8_t P2         :2;                                       
		uint8_t P3         :2;                                       
		uint8_t P4         :2;                                       
		uint8_t P5         :2;                                       
		uint8_t P6         :2;                                       
		uint8_t P7         :2; 
    uint8_t P8         :2;                                       
		uint8_t P9         :2;                                       
		uint8_t P10        :2;                                       
		uint8_t P11        :2;                                       
		uint8_t P12        :2;                                       
		uint8_t P13        :2;                                       
		uint8_t P14        :2;                                       
		uint8_t P15        :2; 		
	} Bits;
} GPIO_MODER_Union;

typedef union { 
uint32_t Byte; 
	struct {
		uint8_t P0         :2;                                       
		uint8_t P1         :2;                                       
		uint8_t P2         :2;                                       
		uint8_t P3         :2;                                       
		uint8_t P4         :2;                                       
		uint8_t P5         :2;                                       
		uint8_t P6         :2;                                       
		uint8_t P7         :2; 
    uint8_t P8         :2;                                       
		uint8_t P9         :2;                                       
		uint8_t P10        :2;                                       
		uint8_t P11        :2;                                       
		uint8_t P12        :2;                                       
		uint8_t P13        :2;                                       
		uint8_t P14        :2;                                       
		uint8_t P15        :2; 		
	} Bits;
} GPIO_OTYPER_Union;

typedef union { 
uint32_t Byte; 
	struct {
		uint8_t P0         :2;                                       
		uint8_t P1         :2;                                       
		uint8_t P2         :2;                                       
		uint8_t P3         :2;                                       
		uint8_t P4         :2;                                       
		uint8_t P5         :2;                                       
		uint8_t P6         :2;                                       
		uint8_t P7         :2; 
    uint8_t P8         :2;                                       
		uint8_t P9         :2;                                       
		uint8_t P10        :2;                                       
		uint8_t P11        :2;                                       
		uint8_t P12        :2;                                       
		uint8_t P13        :2;                                       
		uint8_t P14        :2;                                       
		uint8_t P15        :2; 		
	} Bits;
} GPIO_OSPEEDR_Union;

typedef union { 
uint32_t Byte; 
	struct {
		uint8_t P0         :2;                                       
		uint8_t P1         :2;                                       
		uint8_t P2         :2;                                       
		uint8_t P3         :2;                                       
		uint8_t P4         :2;                                       
		uint8_t P5         :2;                                       
		uint8_t P6         :2;                                       
		uint8_t P7         :2; 
    uint8_t P8         :2;                                       
		uint8_t P9         :2;                                       
		uint8_t P10        :2;                                       
		uint8_t P11        :2;                                       
		uint8_t P12        :2;                                       
		uint8_t P13        :2;                                       
		uint8_t P14        :2;                                       
		uint8_t P15        :2; 		
	} Bits;
} GPIO_PUPDR_Union;

typedef union { 
uint32_t Byte; 
	struct {
		uint8_t P0         :1;                                       
		uint8_t P1         :1;                                       
		uint8_t P2         :1;                                       
		uint8_t P3         :1;                                       
		uint8_t P4         :1;                                       
		uint8_t P5         :1;                                       
		uint8_t P6         :1;                                       
		uint8_t P7         :1; 
    uint8_t P8         :1;                                       
		uint8_t P9         :1;                                       
		uint8_t P10        :1;                                       
		uint8_t P11        :1;                                       
		uint8_t P12        :1;                                       
		uint8_t P13        :1;                                       
		uint8_t P14        :1;                                       
		uint8_t P15        :1; 		
	} Bits;
} GPIO_IDR_Union;

typedef union { 
uint32_t Byte; 
	struct {
		uint8_t P0         :1;                                       
		uint8_t P1         :1;                                       
		uint8_t P2         :1;                                       
		uint8_t P3         :1;                                       
		uint8_t P4         :1;                                       
		uint8_t P5         :1;                                       
		uint8_t P6         :1;                                       
		uint8_t P7         :1; 
    uint8_t P8         :1;                                       
		uint8_t P9         :1;                                       
		uint8_t P10        :1;                                       
		uint8_t P11        :1;                                       
		uint8_t P12        :1;                                       
		uint8_t P13        :1;                                       
		uint8_t P14        :1;                                       
		uint8_t P15        :1; 		
	} Bits;
} GPIO_ODR_Union;

typedef union { 
uint32_t Byte; 
	struct {
		uint8_t P0_L         :1;                                       
		uint8_t P1_L         :1;                                       
		uint8_t P2_L         :1;                                       
		uint8_t P3_L         :1;                                       
		uint8_t P4_L         :1;                                       
		uint8_t P5_L         :1;                                       
		uint8_t P6_L         :1;                                       
		uint8_t P7_L         :1; 
    uint8_t P8_L         :1;                                       
		uint8_t P9_L         :1;                                       
		uint8_t P10_L        :1;                                       
		uint8_t P11_L        :1;                                       
		uint8_t P12_L        :1;                                       
		uint8_t P13_L        :1;                                       
		uint8_t P14_L        :1;                                       
		uint8_t P15_L        :1; 		
		uint8_t P0_H         :1;                                       
		uint8_t P1_H         :1;                                       
		uint8_t P2_H         :1;                                       
		uint8_t P3_H         :1;                                       
		uint8_t P4_H         :1;                                       
		uint8_t P5_H         :1;                                       
		uint8_t P6_H         :1;                                       
		uint8_t P7_H         :1; 
    uint8_t P8_H         :1;                                       
		uint8_t P9_H         :1;                                       
		uint8_t P10_H        :1;                                       
		uint8_t P11_H        :1;                                       
		uint8_t P12_H        :1;                                       
		uint8_t P13_H        :1;                                       
		uint8_t P14_H        :1;                                       
		uint8_t P15_H        :1; 	
	} Bits;
} GPIO_BSRR_Union;

typedef union { 
uint32_t Byte; 
	struct {
		uint8_t P0         :1;                                       
		uint8_t P1         :1;                                       
		uint8_t P2         :1;                                       
		uint8_t P3         :1;                                       
		uint8_t P4         :1;                                       
		uint8_t P5         :1;                                       
		uint8_t P6         :1;                                       
		uint8_t P7         :1; 
    uint8_t P8         :1;                                       
		uint8_t P9         :1;                                       
		uint8_t P10        :1;                                       
		uint8_t P11        :1;                                       
		uint8_t P12        :1;                                       
		uint8_t P13        :1;                                       
		uint8_t P14        :1;                                       
		uint8_t P15        :1; 	   
		
		uint8_t LCKK       :1; 	
	} Bits;
} GPIO_LCKR_Union;

typedef union { 
uint32_t Byte[2]; 
	struct {
		uint8_t P0         :4;                                       
		uint8_t P1         :4;                                       
		uint8_t P2         :4;                                       
		uint8_t P3         :4;                                       
		uint8_t P4         :4;                                       
		uint8_t P5         :4;                                       
		uint8_t P6         :4;                                       
		uint8_t P7         :4; 
    uint8_t P8         :4;                                       
		uint8_t P9         :4;                                       
		uint8_t P10        :4;                                       
		uint8_t P11        :4;                                       
		uint8_t P12        :4;                                       
		uint8_t P13        :4;                                       
		uint8_t P14        :4;                                       
		uint8_t P15        :4; 	 	
	} Bits;
} GPIO_AFR_Union;
typedef struct
{
  __IO GPIO_MODER_Union   MODER;    /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO GPIO_OTYPER_Union  OTYPER;   /*!< GPIO port output type register,        Address offset: 0x04      */
  __IO GPIO_OSPEEDR_Union OSPEEDR;  /*!< GPIO port output speed register,       Address offset: 0x08      */
  __IO GPIO_PUPDR_Union   PUPDR;    /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
  __IO GPIO_IDR_Union     IDR;      /*!< GPIO port input data register,         Address offset: 0x10      */
  __IO GPIO_ODR_Union     ODR;      /*!< GPIO port output data register,        Address offset: 0x14      */
  __IO GPIO_BSRR_Union    BSRR;    /*!< GPIO port bit set/reset low register,  Address offset: 0x18      */ 
  __IO GPIO_LCKR_Union    LCKR;     /*!< GPIO port configuration lock register, Address offset: 0x1C      */
  __IO GPIO_AFR_Union     AFR;   /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
} REG_GPIO_union; 

#endif

//GPIOA
#define REG_GPIO_A              ((REG_GPIO_union *) GPIOA_BASE)

#define PAIN_ALL             (*REG_GPIO_A).IDR.Byte
#define PAIN_PA0             (*REG_GPIO_A).IDR.Bits.P0
#define PAIN_PA1             (*REG_GPIO_A).IDR.Bits.P1
#define PAIN_PA2             (*REG_GPIO_A).IDR.Bits.P2
#define PAIN_PA3             (*REG_GPIO_A).IDR.Bits.P3
#define PAIN_PA4             (*REG_GPIO_A).IDR.Bits.P4
#define PAIN_PA5             (*REG_GPIO_A).IDR.Bits.P5
#define PAIN_PA6             (*REG_GPIO_A).IDR.Bits.P6
#define PAIN_PA7             (*REG_GPIO_A).IDR.Bits.P7
#define PAIN_PA8             (*REG_GPIO_A).IDR.Bits.P8
#define PAIN_PA9             (*REG_GPIO_A).IDR.Bits.P9
#define PAIN_PA10            (*REG_GPIO_A).IDR.Bits.P10
#define PAIN_PA11            (*REG_GPIO_A).IDR.Bits.P11
#define PAIN_PA12            (*REG_GPIO_A).IDR.Bits.P12
#define PAIN_PA13            (*REG_GPIO_A).IDR.Bits.P13
#define PAIN_PA14            (*REG_GPIO_A).IDR.Bits.P14
#define PAIN_PA15            (*REG_GPIO_A).IDR.Bits.P15

#define PAOUT_ALL            (*REG_GPIO_A).ODR.Byte
#define PAOUT_PA0            (*REG_GPIO_A).ODR.Bits.P0
#define PAOUT_PA1            (*REG_GPIO_A).ODR.Bits.P1
#define PAOUT_PA2            (*REG_GPIO_A).ODR.Bits.P2
#define PAOUT_PA3            (*REG_GPIO_A).ODR.Bits.P3
#define PAOUT_PA4            (*REG_GPIO_A).ODR.Bits.P4
#define PAOUT_PA5            (*REG_GPIO_A).ODR.Bits.P5
#define PAOUT_PA6            (*REG_GPIO_A).ODR.Bits.P6
#define PAOUT_PA7            (*REG_GPIO_A).ODR.Bits.P7
#define PAOUT_PA8            (*REG_GPIO_A).ODR.Bits.P8
#define PAOUT_PA9            (*REG_GPIO_A).ODR.Bits.P9
#define PAOUT_PA10           (*REG_GPIO_A).ODR.Bits.P10
#define PAOUT_PA11           (*REG_GPIO_A).ODR.Bits.P11
#define PAOUT_PA12           (*REG_GPIO_A).ODR.Bits.P12
#define PAOUT_PA13           (*REG_GPIO_A).ODR.Bits.P13
#define PAOUT_PA14           (*REG_GPIO_A).ODR.Bits.P14
#define PAOUT_PA15           (*REG_GPIO_A).ODR.Bits.P15


//GPIOB
#define REG_GPIO_B              ((REG_GPIO_union *) GPIOB_BASE)

#define PBIN_ALL              (*REG_GPIO_B).IDR.Byte
#define PBIN_PB0              (*REG_GPIO_B).IDR.Bits.P0
#define PBIN_PB1              (*REG_GPIO_B).IDR.Bits.P1
#define PBIN_PB2              (*REG_GPIO_B).IDR.Bits.P2
#define PBIN_PB3              (*REG_GPIO_B).IDR.Bits.P3
#define PBIN_PB4              (*REG_GPIO_B).IDR.Bits.P4
#define PBIN_PB5              (*REG_GPIO_B).IDR.Bits.P5
#define PBIN_PB6              (*REG_GPIO_B).IDR.Bits.P6
#define PBIN_PB7              (*REG_GPIO_B).IDR.Bits.P7
#define PBIN_PB8              (*REG_GPIO_B).IDR.Bits.P8
#define PBIN_PB9              (*REG_GPIO_B).IDR.Bits.P9
#define PBIN_PB10             (*REG_GPIO_B).IDR.Bits.P10
#define PBIN_PB11             (*REG_GPIO_B).IDR.Bits.P11
#define PBIN_PB12             (*REG_GPIO_B).IDR.Bits.P12
#define PBIN_PB13             (*REG_GPIO_B).IDR.Bits.P13
#define PBIN_PB14             (*REG_GPIO_B).IDR.Bits.P14
#define PBIN_PB15             (*REG_GPIO_B).IDR.Bits.P15

#define PBOUT_ALL             (*REG_GPIO_B).ODR.Byte
#define PBOUT_PB0             (*REG_GPIO_B).ODR.Bits.P0
#define PBOUT_PB1             (*REG_GPIO_B).ODR.Bits.P1
#define PBOUT_PB2             (*REG_GPIO_B).ODR.Bits.P2
#define PBOUT_PB3             (*REG_GPIO_B).ODR.Bits.P3
#define PBOUT_PB4             (*REG_GPIO_B).ODR.Bits.P4
#define PBOUT_PB5             (*REG_GPIO_B).ODR.Bits.P5
#define PBOUT_PB6             (*REG_GPIO_B).ODR.Bits.P6
#define PBOUT_PB7             (*REG_GPIO_B).ODR.Bits.P7
#define PBOUT_PB8             (*REG_GPIO_B).ODR.Bits.P8
#define PBOUT_PB9             (*REG_GPIO_B).ODR.Bits.P9
#define PBOUT_PB10            (*REG_GPIO_B).ODR.Bits.P10
#define PBOUT_PB11            (*REG_GPIO_B).ODR.Bits.P11
#define PBOUT_PB12            (*REG_GPIO_B).ODR.Bits.P12
#define PBOUT_PB13            (*REG_GPIO_B).ODR.Bits.P13
#define PBOUT_PB14            (*REG_GPIO_B).ODR.Bits.P14
#define PBOUT_PB15            (*REG_GPIO_B).ODR.Bits.P15
 
//GPIOC
#define REG_GPIO_C              ((REG_GPIO_union *) GPIOC_BASE)

#define PCIN_ALL              (*REG_GPIO_C).IDR.Byte
#define PCIN_PC0              (*REG_GPIO_C).IDR.Bits.P0
#define PCIN_PC1              (*REG_GPIO_C).IDR.Bits.P1
#define PCIN_PC2              (*REG_GPIO_C).IDR.Bits.P2
#define PCIN_PC3              (*REG_GPIO_C).IDR.Bits.P3
#define PCIN_PC4              (*REG_GPIO_C).IDR.Bits.P4
#define PCIN_PC5              (*REG_GPIO_C).IDR.Bits.P5
#define PCIN_PC6              (*REG_GPIO_C).IDR.Bits.P6
#define PCIN_PC7              (*REG_GPIO_C).IDR.Bits.P7
#define PCIN_PC8              (*REG_GPIO_C).IDR.Bits.P8
#define PCIN_PC9              (*REG_GPIO_C).IDR.Bits.P9
#define PCIN_PC10             (*REG_GPIO_C).IDR.Bits.P10
#define PCIN_PC11             (*REG_GPIO_C).IDR.Bits.P11
#define PCIN_PC12             (*REG_GPIO_C).IDR.Bits.P12
#define PCIN_PC13             (*REG_GPIO_C).IDR.Bits.P13
#define PCIN_PC14             (*REG_GPIO_C).IDR.Bits.P14
#define PCIN_PC15             (*REG_GPIO_C).IDR.Bits.P15
                                   
#define PCOUT_ALL             (*REG_GPIO_C).ODR.Byte																	 
#define PCOUT_PC0             (*REG_GPIO_C).ODR.Bits.P0
#define PCOUT_PC1             (*REG_GPIO_C).ODR.Bits.P1
#define PCOUT_PC2             (*REG_GPIO_C).ODR.Bits.P2
#define PCOUT_PC3             (*REG_GPIO_C).ODR.Bits.P3
#define PCOUT_PC4             (*REG_GPIO_C).ODR.Bits.P4
#define PCOUT_PC5             (*REG_GPIO_C).ODR.Bits.P5
#define PCOUT_PC6             (*REG_GPIO_C).ODR.Bits.P6
#define PCOUT_PC7             (*REG_GPIO_C).ODR.Bits.P7
#define PCOUT_PC8             (*REG_GPIO_C).ODR.Bits.P8
#define PCOUT_PC9             (*REG_GPIO_C).ODR.Bits.P9
#define PCOUT_PC10            (*REG_GPIO_C).ODR.Bits.P10
#define PCOUT_PC11            (*REG_GPIO_C).ODR.Bits.P11
#define PCOUT_PC12            (*REG_GPIO_C).ODR.Bits.P12
#define PCOUT_PC13            (*REG_GPIO_C).ODR.Bits.P13
#define PCOUT_PC14            (*REG_GPIO_C).ODR.Bits.P14
#define PCOUT_PC15            (*REG_GPIO_C).ODR.Bits.P15

//GPIOC
#define REG_GPIO_D              ((REG_GPIO_union *) GPIOD_BASE)

#define PDIN_ALL              (*REG_GPIO_D).IDR.Byte
#define PDIN_PD0              (*REG_GPIO_D).IDR.Bits.P0
#define PDIN_PD1              (*REG_GPIO_D).IDR.Bits.P1
#define PDIN_PD2              (*REG_GPIO_D).IDR.Bits.P2
#define PDIN_PD3              (*REG_GPIO_D).IDR.Bits.P3
#define PDIN_PD4              (*REG_GPIO_D).IDR.Bits.P4
#define PDIN_PD5              (*REG_GPIO_D).IDR.Bits.P5
#define PDIN_PD6              (*REG_GPIO_D).IDR.Bits.P6
#define PDIN_PD7              (*REG_GPIO_D).IDR.Bits.P7
#define PDIN_PD8              (*REG_GPIO_D).IDR.Bits.P8
#define PDIN_PD9              (*REG_GPIO_D).IDR.Bits.P9
#define PDIN_PD10             (*REG_GPIO_D).IDR.Bits.P10
#define PDIN_PD11             (*REG_GPIO_D).IDR.Bits.P11
#define PDIN_PD12             (*REG_GPIO_D).IDR.Bits.P12
#define PDIN_PD13             (*REG_GPIO_D).IDR.Bits.P13
#define PDIN_PD14             (*REG_GPIO_D).IDR.Bits.P14
#define PDIN_PD15             (*REG_GPIO_D).IDR.Bits.P15

#define PDOUT_ALL             (*REG_GPIO_D).ODR.Byte
#define PDOUT_PD0             (*REG_GPIO_D).ODR.Bits.P0
#define PDOUT_PD1             (*REG_GPIO_D).ODR.Bits.P1
#define PDOUT_PD2             (*REG_GPIO_D).ODR.Bits.P2
#define PDOUT_PD3             (*REG_GPIO_D).ODR.Bits.P3
#define PDOUT_PD4             (*REG_GPIO_D).ODR.Bits.P4
#define PDOUT_PD5             (*REG_GPIO_D).ODR.Bits.P5
#define PDOUT_PD6             (*REG_GPIO_D).ODR.Bits.P6
#define PDOUT_PD7             (*REG_GPIO_D).ODR.Bits.P7
#define PDOUT_PD8             (*REG_GPIO_D).ODR.Bits.P8
#define PDOUT_PD9             (*REG_GPIO_D).ODR.Bits.P9
#define PDOUT_PD10            (*REG_GPIO_D).ODR.Bits.P10
#define PDOUT_PD11            (*REG_GPIO_D).ODR.Bits.P11
#define PDOUT_PD12            (*REG_GPIO_D).ODR.Bits.P12
#define PDOUT_PD13            (*REG_GPIO_D).ODR.Bits.P13
#define PDOUT_PD14            (*REG_GPIO_D).ODR.Bits.P14
#define PDOUT_PD15            (*REG_GPIO_D).ODR.Bits.P15

//GPIOE
#define REG_GPIO_E              ((REG_GPIO_union *) GPIOE_BASE)

#define PEIN_ALL              (*REG_GPIO_E).IDR.Byte
#define PEIN_PE0              (*REG_GPIO_E).IDR.Bits.P0
#define PEIN_PE1              (*REG_GPIO_E).IDR.Bits.P1
#define PEIN_PE2              (*REG_GPIO_E).IDR.Bits.P2
#define PEIN_PE3              (*REG_GPIO_E).IDR.Bits.P3
#define PEIN_PE4              (*REG_GPIO_E).IDR.Bits.P4
#define PEIN_PE5              (*REG_GPIO_E).IDR.Bits.P5
#define PEIN_PE6              (*REG_GPIO_E).IDR.Bits.P6
#define PEIN_PE7              (*REG_GPIO_E).IDR.Bits.P7
#define PEIN_PE8              (*REG_GPIO_E).IDR.Bits.P8
#define PEIN_PE9              (*REG_GPIO_E).IDR.Bits.P9
#define PEIN_PE10             (*REG_GPIO_E).IDR.Bits.P10
#define PEIN_PE11             (*REG_GPIO_E).IDR.Bits.P11
#define PEIN_PE12             (*REG_GPIO_E).IDR.Bits.P12
#define PEIN_PE13             (*REG_GPIO_E).IDR.Bits.P13
#define PEIN_PE14             (*REG_GPIO_E).IDR.Bits.P14
#define PEIN_PE15             (*REG_GPIO_E).IDR.Bits.P15
                                    
#define PEOUT_ALL             (*REG_GPIO_E).ODR.Byte
#define PEOUT_PE0             (*REG_GPIO_E).ODR.Bits.P0
#define PEOUT_PE1             (*REG_GPIO_E).ODR.Bits.P1
#define PEOUT_PE2             (*REG_GPIO_E).ODR.Bits.P2
#define PEOUT_PE3             (*REG_GPIO_E).ODR.Bits.P3
#define PEOUT_PE4             (*REG_GPIO_E).ODR.Bits.P4
#define PEOUT_PE5             (*REG_GPIO_E).ODR.Bits.P5
#define PEOUT_PE6             (*REG_GPIO_E).ODR.Bits.P6
#define PEOUT_PE7             (*REG_GPIO_E).ODR.Bits.P7
#define PEOUT_PE8             (*REG_GPIO_E).ODR.Bits.P8
#define PEOUT_PE9             (*REG_GPIO_E).ODR.Bits.P9
#define PEOUT_PE10            (*REG_GPIO_E).ODR.Bits.P10
#define PEOUT_PE11            (*REG_GPIO_E).ODR.Bits.P11
#define PEOUT_PE12            (*REG_GPIO_E).ODR.Bits.P12
#define PEOUT_PE13            (*REG_GPIO_E).ODR.Bits.P13
#define PEOUT_PE14            (*REG_GPIO_E).ODR.Bits.P14
#define PEOUT_PE15            (*REG_GPIO_E).ODR.Bits.P15

//GPIOF
#define REG_GPIO_F              ((REG_GPIO_union *) GPIOF_BASE)

#define PFIN_ALL              (*REG_GPIO_F).IDR.Byte
#define PFIN_PF0              (*REG_GPIO_F).IDR.Bits.P0
#define PFIN_PF1              (*REG_GPIO_F).IDR.Bits.P1
#define PFIN_PF2              (*REG_GPIO_F).IDR.Bits.P2
#define PFIN_PF3              (*REG_GPIO_F).IDR.Bits.P3
#define PFIN_PF4              (*REG_GPIO_F).IDR.Bits.P4
#define PFIN_PF5              (*REG_GPIO_F).IDR.Bits.P5
#define PFIN_PF6              (*REG_GPIO_F).IDR.Bits.P6
#define PFIN_PF7              (*REG_GPIO_F).IDR.Bits.P7
#define PFIN_PF8              (*REG_GPIO_F).IDR.Bits.P8
#define PFIN_PF9              (*REG_GPIO_F).IDR.Bits.P9
#define PFIN_PF10             (*REG_GPIO_F).IDR.Bits.P10
#define PFIN_PF11             (*REG_GPIO_F).IDR.Bits.P11
#define PFIN_PF12             (*REG_GPIO_F).IDR.Bits.P12
#define PFIN_PF13             (*REG_GPIO_F).IDR.Bits.P13
#define PFIN_PF14             (*REG_GPIO_F).IDR.Bits.P14
#define PFIN_PF15             (*REG_GPIO_F).IDR.Bits.P15

#define PFOUT_ALL             (*REG_GPIO_F).ODR.Byte
#define PFOUT_PF0             (*REG_GPIO_F).ODR.Bits.P0
#define PFOUT_PF1             (*REG_GPIO_F).ODR.Bits.P1
#define PFOUT_PF2             (*REG_GPIO_F).ODR.Bits.P2
#define PFOUT_PF3             (*REG_GPIO_F).ODR.Bits.P3
#define PFOUT_PF4             (*REG_GPIO_F).ODR.Bits.P4
#define PFOUT_PF5             (*REG_GPIO_F).ODR.Bits.P5
#define PFOUT_PF6             (*REG_GPIO_F).ODR.Bits.P6
#define PFOUT_PF7             (*REG_GPIO_F).ODR.Bits.P7
#define PFOUT_PF8             (*REG_GPIO_F).ODR.Bits.P8
#define PFOUT_PF9             (*REG_GPIO_F).ODR.Bits.P9
#define PFOUT_PF10            (*REG_GPIO_F).ODR.Bits.P10
#define PFOUT_PF11            (*REG_GPIO_F).ODR.Bits.P11
#define PFOUT_PF12            (*REG_GPIO_F).ODR.Bits.P12
#define PFOUT_PF13            (*REG_GPIO_F).ODR.Bits.P13
#define PFOUT_PF14            (*REG_GPIO_F).ODR.Bits.P14
#define PFOUT_PF15            (*REG_GPIO_F).ODR.Bits.P15

//GPIOG
#define REG_GPIO_G              ((REG_GPIO_union *) GPIOG_BASE)

#define PGIN_ALL              (*REG_GPIO_G).IDR.Byte
#define PGIN_PG0              (*REG_GPIO_G).IDR.Bits.P0
#define PGIN_PG1              (*REG_GPIO_G).IDR.Bits.P1
#define PGIN_PG2              (*REG_GPIO_G).IDR.Bits.P2
#define PGIN_PG3              (*REG_GPIO_G).IDR.Bits.P3
#define PGIN_PG4              (*REG_GPIO_G).IDR.Bits.P4
#define PGIN_PG5              (*REG_GPIO_G).IDR.Bits.P5
#define PGIN_PG6              (*REG_GPIO_G).IDR.Bits.P6
#define PGIN_PG7              (*REG_GPIO_G).IDR.Bits.P7
#define PGIN_PG8              (*REG_GPIO_G).IDR.Bits.P8
#define PGIN_PG9              (*REG_GPIO_G).IDR.Bits.P9
#define PGIN_PG10             (*REG_GPIO_G).IDR.Bits.P10
#define PGIN_PG11             (*REG_GPIO_G).IDR.Bits.P11
#define PGIN_PG12             (*REG_GPIO_G).IDR.Bits.P12
#define PGIN_PG13             (*REG_GPIO_G).IDR.Bits.P13
#define PGIN_PG14             (*REG_GPIO_G).IDR.Bits.P14
#define PGIN_PG15             (*REG_GPIO_G).IDR.Bits.P15

#define PGOUT_ALL             (*REG_GPIO_G).ODR.Byte
#define PGOUT_PG0             (*REG_GPIO_G).ODR.Bits.P0
#define PGOUT_PG1             (*REG_GPIO_G).ODR.Bits.P1
#define PGOUT_PG2             (*REG_GPIO_G).ODR.Bits.P2
#define PGOUT_PG3             (*REG_GPIO_G).ODR.Bits.P3
#define PGOUT_PG4             (*REG_GPIO_G).ODR.Bits.P4
#define PGOUT_PG5             (*REG_GPIO_G).ODR.Bits.P5
#define PGOUT_PG6             (*REG_GPIO_G).ODR.Bits.P6
#define PGOUT_PG7             (*REG_GPIO_G).ODR.Bits.P7
#define PGOUT_PG8             (*REG_GPIO_G).ODR.Bits.P8
#define PGOUT_PG9             (*REG_GPIO_G).ODR.Bits.P9
#define PGOUT_PG10            (*REG_GPIO_G).ODR.Bits.P10
#define PGOUT_PG11            (*REG_GPIO_G).ODR.Bits.P11
#define PGOUT_PG12            (*REG_GPIO_G).ODR.Bits.P12
#define PGOUT_PG13            (*REG_GPIO_G).ODR.Bits.P13
#define PGOUT_PG14            (*REG_GPIO_G).ODR.Bits.P14
#define PGOUT_PG15            (*REG_GPIO_G).ODR.Bits.P15


#endif



















