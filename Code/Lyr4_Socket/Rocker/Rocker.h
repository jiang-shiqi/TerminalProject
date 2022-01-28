#ifndef __ROCKER_H_
#define __ROCKER_H_

#include "stdint.h"
#include "Analog_Signal_Processing.h"

typedef enum {
	YG0,
}Rocker_List;



#define YG_Total 1                //ҡ������

#define DIR_IDLE   0x00
#define DIR_UP     0x01
#define DIR_DOWN   0x02
#define DIR_LEFT   0x04
#define DIR_RIGHT  0x08


typedef struct
{ 
	uint16_t *currentVal;
	/*����Ƕȣ� 0--------0-----------------50-------50------50----------------100----- --100*/
	/*��ǰADֵ�� 0-------100---------------462------512------562---------------922---- --1023*/
	/*��Χ���壺 ��ֵ ��С��Чֵ        -��ֵ��Χ  ��ֵ   +��ֵ��Χ         �����Чֵ   ��ֵ*/
	uint8_t  val;           //�����Ƕ�ֵ
	uint16_t midVal;             //��ֵ
	uint16_t midRange;           //��ֵ��Χ
	uint16_t minValidVal;        //��С��Чֵ
	uint16_t maxVallidVal;       //�����Чֵ
}RockerValStruct;

typedef struct
{
	RockerValStruct rockerVal[2];
	uint8_t  dir;                //����
	uint8_t  dirRange;           //����Χ--ֵԽСԽ���� 0-50
	uint16_t angle;              //�Ƕ�ֵ---��12�㷽������˳ʱ��н�
}YGValStruct;

extern YGValStruct YGVal[YG_Total];

void Rocker_Init(void);
void Rocker_Service(void);
void Rocker_CaliAdcValue(void);

#endif
