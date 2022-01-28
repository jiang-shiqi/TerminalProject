#ifndef __CAN_H
#define __CAN_H	 
#include "sys.h"	    
	
//CAN����RX0�ж�ʹ��
#define CAN1_RX0_INT_ENABLE			1		 			//0,��ʹ��;1,ʹ��.	
#define CAN2_RX0_INT_ENABLE			1		 			//0,��ʹ��;1,ʹ��.		
					 							 				    
u8 CAN_Mode_Init(CAN_TypeDef *CANx,u16 BAUD,u8 mode);//CAN��ʼ��
u8 CAN_Tx_Msg(CAN_TypeDef *CANx,u32 id,u8 ide,u8 rtr,u8 len,u8 *dat);	//��������
u8 CAN_Msg_Pend(CAN_TypeDef *CANx,u8 fifox);								//��ѯ���䱨��
void CAN_Rx_Msg(CAN_TypeDef *CANx,u8 fifox,u32 *id,u8 *ide,u8 *rtr,u8 *len,u8 *dat);//��������
u8 CAN_Tx_Staus(CAN_TypeDef *CANx,u8 mbox);  							//���ط���״̬
u8 CAN_Send_Msg(CAN_TypeDef *CANx,u16 id,u8* msg,u8 len);   //��������
u8 CAN_Receive_Msg(CAN_TypeDef *CANx,u8 *buf);							//��������
#endif

















