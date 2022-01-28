#ifndef __MYIIC_H
#define __MYIIC_H     
 

 	   
//IO��������
#define SDA_IN()  {GPIOA->CRH&=0X0FFFFFFF;GPIOA->CRH|=(u32)8<<28;}
#define SDA_OUT() {GPIOA->CRH&=0X0FFFFFFF;GPIOA->CRH|=(u32)3<<28;}


#define IIC_SCL(a)		I2C1_SCL = a
#define IIC_SDA(a)		I2C1_SDA = a
#define READ_SDA  		((GPIOA->IDR >> 15) & 0x0001)


//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(unsigned char txd);			//IIC����һ���ֽ�
unsigned char IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
unsigned char IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(unsigned char daddr,unsigned char addr,unsigned char data);
unsigned char IIC_Read_One_Byte(unsigned char daddr,unsigned char addr);	  
#endif
















