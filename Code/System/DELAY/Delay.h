/***********************************************************************************************************
* 版权                                                                                                     *
*                                                                                                          *
* 文件名称: Delay.h                                                                                        *
* 描    述: 延时函数的声明                                                         *
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
#ifndef __DELAY_H
#define __DELAY_H 		
#include "include.h"
 
void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif


