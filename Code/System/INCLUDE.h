/***********************************************************************************************************
* 版权                                                                                                     *
*                                                                                                          *
* 文件名称: include.h                                                                                      *
* 描    述: 链接工程所需要的头文件                                                                         *
* 作    者: 姜世奇                                                                                         *
* 当前版本: 1.0.1                                                                                          *  
* 完成时间:                                                                                                *
* ---------------------------------------------------------------------------------------------------------*
* 历史信息:                                                                                                *
*           <Date>            |    <Version>    |    <Author>    |    <Description>                        *
* ---------------------------------------------------------------------------------------------------------*
*   2019年9月26日10:49:03     |      1.0.1      |     姜世奇     |     Create file                         *            
*----------------------------------------------------------------------------------------------------------*
***********************************************************************************************************/
#ifndef __INCLUDE_H_
#define __INCLUDE_H_


#include "SYS.h"
#include "core_cm4.h"

//#include "I2c.h"
#include "Delay.h"
#include "USART.h" 
#include "GPIO.h"
//#include "GUI.h"
#include "API.h"
#include "systick.h"
//#include "oled_ssd1306.h"
//#include "AMG88.h"
//#include "OLED_ST7789.h"
#include "ADC.h"
#include "Toolkit.h"

#define EX_ERR  -1
#define EX_OK    0

#define true 1
#define false 0

#ifndef NULL
#define NULL                   ((void *) 0)
#endif

#endif

