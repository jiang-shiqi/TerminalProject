#ifndef __CAN_H
#define __CAN_H	 
#include "sys.h"	    
	
//CAN接收RX0中断使能
#define CAN1_RX0_INT_ENABLE			1		 			//0,不使能;1,使能.	
#define CAN2_RX0_INT_ENABLE			1		 			//0,不使能;1,使能.		
					 							 				    
u8 CAN_Mode_Init(CAN_TypeDef *CANx,u16 BAUD,u8 mode);//CAN初始化
u8 CAN_Tx_Msg(CAN_TypeDef *CANx,u32 id,u8 ide,u8 rtr,u8 len,u8 *dat);	//发送数据
u8 CAN_Msg_Pend(CAN_TypeDef *CANx,u8 fifox);								//查询邮箱报文
void CAN_Rx_Msg(CAN_TypeDef *CANx,u8 fifox,u32 *id,u8 *ide,u8 *rtr,u8 *len,u8 *dat);//接收数据
u8 CAN_Tx_Staus(CAN_TypeDef *CANx,u8 mbox);  							//返回发送状态
u8 CAN_Send_Msg(CAN_TypeDef *CANx,u16 id,u8* msg,u8 len);   //发送数据
u8 CAN_Receive_Msg(CAN_TypeDef *CANx,u8 *buf);							//接收数据
#endif

















