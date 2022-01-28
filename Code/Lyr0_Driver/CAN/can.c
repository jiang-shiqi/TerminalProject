#include "can.h"
#include "GPIO.h"
//#include "led.h"
//#include "delay.h"
//#include "usart.h"

//CAN��ʼ��
//tsjw:����ͬ����Ծʱ�䵥Ԫ.��Χ:1~3;
//tbs2:ʱ���2��ʱ�䵥Ԫ.��Χ:1~8;
//tbs1:ʱ���1��ʱ�䵥Ԫ.��Χ:1~16;
//brp :�����ʷ�Ƶ��.��Χ:1~1024;(ʵ��Ҫ��1,Ҳ����1~1024) tq=(brp)*tpclk1
//ע�����ϲ����κ�һ����������Ϊ0,�������.
//������=Fpclk1/((tbs1+tbs2+1)*brp);
//mode:0,��ͨģʽ;1,�ػ�ģʽ;
//Fpclk1��ʱ���ڳ�ʼ����ʱ������Ϊ42M,�������CAN1_Mode_Init(1,6,7,6,1);
//������Ϊ:42M/((6+7+1)*6)=500Kbps
//����ֵ:0,��ʼ��OK;
//    ����,��ʼ��ʧ��;
u8 CAN_Mode_Init(CAN_TypeDef *CANx,u16 BAUD,u8 mode)
{
	u8 tsjw;
	u8 tbs2;
	u8 tbs1;
	u16 brp;
	u16 i=0;

	switch (BAUD)
	{
	case 100:
		tsjw = 1;tbs2 = 6;tbs1 = 7;brp = 30;
		break;
	case 125:
		tsjw = 1;tbs2 = 6;tbs1 = 7;brp = 24;
		break;
	case 250:
		tsjw = 1;tbs2 = 6;tbs1 = 7;brp = 12;
		break;
	case 500:
		tsjw = 1;tbs2 = 6;tbs1 = 7;brp = 6;
		break;
	
	default:
		break;
	}

	if(BAUD == 500)
	{
		tsjw = 1;tbs2 = 6;tbs1 = 7;brp = 6;
	}
	else if(BAUD == 250)
	{
		tsjw = 1;tbs2 = 6;tbs1 = 7;brp = 6;
	}
	else
		return 1;

 	if(tsjw==0||tbs2==0||tbs1==0||brp==0)return 1;
	tsjw-=1;//�ȼ�ȥ1.����������
	tbs2-=1;
	tbs1-=1;
	brp-=1;

	if((uint32_t)CANx == (uint32_t)CAN1)
	{
		CAN1_STB = 0;
		RCC->APB1ENR|=1<<25;//ʹ��CAN1ʱ�� CAN1ʹ�õ���APB1��ʱ��(max:42M)
	}
	else if((uint32_t)CANx == (uint32_t)CAN2)
	{
		CAN2_STB = 0;	
		RCC->APB1ENR|=1<<26;//ʹ��CAN2ʱ�� CAN1ʹ�õ���APB1��ʱ��(max:42M)
	}
	
	CANx->MCR=0x0000;	//�˳�˯��ģʽ(ͬʱ��������λΪ0)
	CANx->MCR|=1<<0;		//����CAN�����ʼ��ģʽ
	while((CANx->MSR&1<<0)==0)
	{
		i++;
		if(i>100)return 2;//�����ʼ��ģʽʧ��
	}
	CANx->MCR|=0<<7;		//��ʱ�䴥��ͨ��ģʽ
	CANx->MCR|=0<<6;		//����Զ����߹���
	CANx->MCR|=0<<5;		//˯��ģʽͨ���������(���CAN1->MCR��SLEEPλ)
	CANx->MCR|=1<<4;		//��ֹ�����Զ�����
	CANx->MCR|=0<<3;		//���Ĳ�����,�µĸ��Ǿɵ�
	CANx->MCR|=0<<2;		//���ȼ��ɱ��ı�ʶ������
	CANx->BTR=0x00000000;	//���ԭ��������.
	CANx->BTR|=mode<<30;	//ģʽ���� 0,��ͨģʽ;1,�ػ�ģʽ;2,��Ĭģʽ
	CANx->BTR|=tsjw<<24; 	//����ͬ����Ծ���(Tsjw)Ϊtsjw+1��ʱ�䵥λ
	CANx->BTR|=tbs2<<20; 	//Tbs2=tbs2+1��ʱ�䵥λ
	CANx->BTR|=tbs1<<16;	//Tbs1=tbs1+1��ʱ�䵥λ
	CANx->BTR|=brp<<0;  	//��Ƶϵ��(Fdiv)Ϊbrp+1
							//������:Fpclk1/((Tbs1+Tbs2+1)*Fdiv)
	CANx->MCR&=~(1<<0);		//����CAN�˳���ʼ��ģʽ
	while((CANx->MSR&1<<0)==1)
	{
		i++;
		if(i>0XFFF0)return 3;//�˳���ʼ��ģʽʧ��
	}
	//��������ʼ��
	CANx->FMR|=1<<0;		//�������鹤���ڳ�ʼ��ģʽ
	CANx->FA1R&=~(1<<0);	//������0������
	CANx->FS1R|=1<<0; 		//������λ��Ϊ32λ.
	CANx->FM1R|=0<<0;		//������0�����ڱ�ʶ������λģʽ
	CANx->FFA1R|=0<<0;		//������0������FIFO0
	CANx->sFilterRegister[0].FR1=0X00000000;//32λID
	CANx->sFilterRegister[0].FR2=0X00000000;//32λMASK
	CANx->FA1R|=1<<0;		//���������0
	CANx->FMR&=0<<0;		//���������������ģʽ

	if((uint32_t)CANx == (uint32_t)CAN1)
	{
#if CAN1_RX0_INT_ENABLE
		//ʹ���жϽ���
		CAN1->IER|=1<<1;		//FIFO0��Ϣ�Һ��ж�����.	    
		MY_NVIC_Init(1,0,CAN1_RX0_IRQn,2);//��2
#endif
	}
	else if((uint32_t)CANx == (uint32_t)CAN2)
	{
#if CAN2_RX0_INT_ENABLE
		//ʹ���жϽ���
		CAN2->IER|=1<<1;		//FIFO0��Ϣ�Һ��ж�����.	    
		MY_NVIC_Init(1,0,CAN2_RX0_IRQn,2);//��2
#endif
	}



	return 0;
}   
//id:��׼ID(11λ)/��չID(11λ+18λ)	    
//ide:0,��׼֡;1,��չ֡
//rtr:0,����֡;1,Զ��֡
//len:Ҫ���͵����ݳ���(�̶�Ϊ8���ֽ�,��ʱ�䴥��ģʽ��,��Ч����Ϊ6���ֽ�)
//*dat:����ָ��.
//����ֵ:0~3,������.0XFF,����Ч����.
u8 CAN_Tx_Msg(CAN_TypeDef *CANx,u32 id,u8 ide,u8 rtr,u8 len,u8 *dat)
{	   
	u8 mbox;	  
	if(CANx->TSR&(1<<26))mbox=0;			//����0Ϊ��
	else if(CANx->TSR&(1<<27))mbox=1;	//����1Ϊ��
	else if(CANx->TSR&(1<<28))mbox=2;	//����2Ϊ��
	else return 0XFF;					//�޿�����,�޷����� 
	CANx->sTxMailBox[mbox].TIR=0;		//���֮ǰ������
	if(ide==0)	//��׼֡
	{
		id&=0x7ff;//ȡ��11λstdid
		id<<=21;		  
	}else		//��չ֡
	{
		id&=0X1FFFFFFF;//ȡ��32λextid
		id<<=3;									   
	}
	CANx->sTxMailBox[mbox].TIR|=id;		 
	CANx->sTxMailBox[mbox].TIR|=ide<<2;	  
	CANx->sTxMailBox[mbox].TIR|=rtr<<1;
	len&=0X0F;//�õ�����λ
	CANx->sTxMailBox[mbox].TDTR&=~(0X0000000F);
	CANx->sTxMailBox[mbox].TDTR|=len;		   //����DLC.
	//���������ݴ�������.
	CANx->sTxMailBox[mbox].TDHR=(((u32)dat[7]<<24)|
								((u32)dat[6]<<16)|
 								((u32)dat[5]<<8)|
								((u32)dat[4]));
	CANx->sTxMailBox[mbox].TDLR=(((u32)dat[3]<<24)|
								((u32)dat[2]<<16)|
 								((u32)dat[1]<<8)|
								((u32)dat[0]));
	CANx->sTxMailBox[mbox].TIR|=1<<0; //��������������
	return mbox;
}
//��÷���״̬.
//mbox:������;
//����ֵ:����״̬. 0,����;0X05,����ʧ��;0X07,���ͳɹ�.
u8 CAN_Tx_Staus(CAN_TypeDef *CANx,u8 mbox)
{	
	u8 sta=0;					    
	switch (mbox)
	{
		case 0: 
			sta |= CANx->TSR&(1<<0);			//RQCP0
			sta |= CANx->TSR&(1<<1);			//TXOK0
			sta |=((CANx->TSR&(1<<26))>>24);	//TME0
			break;
		case 1: 
			sta |= CANx->TSR&(1<<8)>>8;		//RQCP1
			sta |= CANx->TSR&(1<<9)>>8;		//TXOK1
			sta |=((CANx->TSR&(1<<27))>>25);	//TME1	   
			break;
		case 2: 
			sta |= CANx->TSR&(1<<16)>>16;	//RQCP2
			sta |= CANx->TSR&(1<<17)>>16;	//TXOK2
			sta |=((CANx->TSR&(1<<28))>>26);	//TME2
			break;
		default:
			sta=0X05;//����Ų���,�϶�ʧ��.
		break;
	}
	return sta;
} 
//�õ���FIFO0/FIFO1�н��յ��ı��ĸ���.
//fifox:0/1.FIFO���;
//����ֵ:FIFO0/FIFO1�еı��ĸ���.
u8 CAN_Msg_Pend(CAN_TypeDef *CANx,u8 fifox)
{
	if(fifox==0)return CANx->RF0R&0x03; 
	else if(fifox==1)return CANx->RF1R&0x03; 
	else return 0;
}
//��������
//fifox:�����
//id:��׼ID(11λ)/��չID(11λ+18λ)	    
//ide:0,��׼֡;1,��չ֡
//rtr:0,����֡;1,Զ��֡
//len:���յ������ݳ���(�̶�Ϊ8���ֽ�,��ʱ�䴥��ģʽ��,��Ч����Ϊ6���ֽ�)
//dat:���ݻ�����
void CAN_Rx_Msg(CAN_TypeDef *CANx,u8 fifox,u32 *id,u8 *ide,u8 *rtr,u8 *len,u8 *dat)
{	   
	*ide=CANx->sFIFOMailBox[fifox].RIR&0x04;//�õ���ʶ��ѡ��λ��ֵ  
 	if(*ide==0)//��׼��ʶ��
	{
		*id=CANx->sFIFOMailBox[fifox].RIR>>21;
	}else	   //��չ��ʶ��
	{
		*id=CANx->sFIFOMailBox[fifox].RIR>>3;
	}
	*rtr=CANx->sFIFOMailBox[fifox].RIR&0x02;	//�õ�Զ�̷�������ֵ.
	*len=CANx->sFIFOMailBox[fifox].RDTR&0x0F;//�õ�DLC
 	//*fmi=(CANx->sFIFOMailBox[FIFONumber].RDTR>>8)&0xFF;//�õ�FMI
	//��������
	dat[0]=CANx->sFIFOMailBox[fifox].RDLR&0XFF;
	dat[1]=(CANx->sFIFOMailBox[fifox].RDLR>>8)&0XFF;
	dat[2]=(CANx->sFIFOMailBox[fifox].RDLR>>16)&0XFF;
	dat[3]=(CANx->sFIFOMailBox[fifox].RDLR>>24)&0XFF;    
	dat[4]=CANx->sFIFOMailBox[fifox].RDHR&0XFF;
	dat[5]=(CANx->sFIFOMailBox[fifox].RDHR>>8)&0XFF;
	dat[6]=(CANx->sFIFOMailBox[fifox].RDHR>>16)&0XFF;
	dat[7]=(CANx->sFIFOMailBox[fifox].RDHR>>24)&0XFF;    
  	if(fifox==0)CANx->RF0R|=0X20;//�ͷ�FIFO0����
	else if(fifox==1)CANx->RF1R|=0X20;//�ͷ�FIFO1����	 
}

#if CAN1_RX0_INT_ENABLE	//ʹ��RX0�ж�
//�жϷ�����			    
void CAN1_RX0_IRQHandler(void)
{
	u8 rxbuf[8];
	u32 id;
	u8 ide,rtr,len;     
 	CAN_Rx_Msg(CAN1,0,&id,&ide,&rtr,&len,rxbuf);
    // printf("id:%d\r\n",id);
    // printf("ide:%d\r\n",ide);
    // printf("rtr:%d\r\n",rtr);
    // printf("len:%d\r\n",len);
    // printf("rxbuf[0]:%d\r\n",rxbuf[0]);
    // printf("rxbuf[1]:%d\r\n",rxbuf[1]);
    // printf("rxbuf[2]:%d\r\n",rxbuf[2]);
    // printf("rxbuf[3]:%d\r\n",rxbuf[3]);
    // printf("rxbuf[4]:%d\r\n",rxbuf[4]);
    // printf("rxbuf[5]:%d\r\n",rxbuf[5]);
    // printf("rxbuf[6]:%d\r\n",rxbuf[6]);
    // printf("rxbuf[7]:%d\r\n",rxbuf[7]);
}
#endif

#if CAN2_RX0_INT_ENABLE	//ʹ��RX0�ж�
//�жϷ�����			    
void CAN2_RX0_IRQHandler(void)
{
	u8 rxbuf[8];
	u32 id;
	u8 ide,rtr,len;     
 	CAN_Rx_Msg(CAN2,0,&id,&ide,&rtr,&len,rxbuf);
    // printf("id:%d\r\n",id);
    // printf("ide:%d\r\n",ide);
    // printf("rtr:%d\r\n",rtr);
    // printf("len:%d\r\n",len);
    // printf("rxbuf[0]:%d\r\n",rxbuf[0]);
    // printf("rxbuf[1]:%d\r\n",rxbuf[1]);
    // printf("rxbuf[2]:%d\r\n",rxbuf[2]);
    // printf("rxbuf[3]:%d\r\n",rxbuf[3]);
    // printf("rxbuf[4]:%d\r\n",rxbuf[4]);
    // printf("rxbuf[5]:%d\r\n",rxbuf[5]);
    // printf("rxbuf[6]:%d\r\n",rxbuf[6]);
    // printf("rxbuf[7]:%d\r\n",rxbuf[7]);
}
#endif

//can����һ������(�̶���ʽ:��׼֡,����֡)	
//len:���ݳ���(���Ϊ8)				     
//msg:����ָ��,���Ϊ8���ֽ�.
//����ֵ:0,�ɹ�;
//		 ����,ʧ��;
u8 CAN_Send_Msg(CAN_TypeDef *CANx,u16 id,u8* msg,u8 len)
{	
	u8 mbox;
	u16 i=0;	  	 						       
    mbox=CAN_Tx_Msg(CANx,id,0,0,len,msg);
	while((CAN_Tx_Staus(CANx,mbox)!=0X07)&&(i<0XFFF))i++;//�ȴ����ͽ���
	if(i>=0XFFF)return 1;							//����ʧ��?
	return 0;										//���ͳɹ�;
}
//can�ڽ������ݲ�ѯ
//buf:���ݻ�����;	 
//����ֵ:0,�����ݱ��յ�;
//		 ����,���յ����ݳ���;
u8 CAN_Receive_Msg(CAN_TypeDef *CANx,u8 *buf)
{		   		   
	u32 id;
	u8 ide,rtr,len; 
	if(CAN_Msg_Pend(CANx,0)==0)return 0;		//û�н��յ�����,ֱ���˳� 	 
  	CAN_Rx_Msg(CANx,0,&id,&ide,&rtr,&len,buf); 	//��ȡ����
    if(id!=0x12||ide!=0||rtr!=0)len=0;		//���մ���	   
	return len;	
}














