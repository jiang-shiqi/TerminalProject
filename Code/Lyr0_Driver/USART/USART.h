#ifndef __MY_USART_H
#define __MY_USART_H

#include "include.h"

//typedef   signed          char int8;
//typedef   signed short     int int16;
//typedef   signed           int int32;
//typedef   signed long 		 int int64;

//typedef unsigned          char u8;
//typedef unsigned short     int u16;
//typedef unsigned           int u32;
//typedef unsigned long 		 int u64;

#define EN_USART1_RX 			1	


void USART_init(u8 com,u32 bound);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART_Send_Byte(u8 com,u8 C_dat);
void USART_Send_Word(u8 com,char *P_word);
void USART_Send_Word_Lenth(u8 com,char *P_word,u16 lenth);
void USART_Send_Enter(u8 com);
void USART_Send_Int_Num(u8 com,u32 I_num,u8 len);
void USART_Send_Int(u8 com, u32 num);
#endif
