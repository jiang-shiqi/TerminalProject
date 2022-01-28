#ifndef __ROCKER_H_
#define __ROCKER_H_

#include "stdint.h"
#include "Analog_Signal_Processing.h"

typedef enum {
	YG0,
}Rocker_List;



#define YG_Total 1                //摇杆总数

#define DIR_IDLE   0x00
#define DIR_UP     0x01
#define DIR_DOWN   0x02
#define DIR_LEFT   0x04
#define DIR_RIGHT  0x08


typedef struct
{ 
	uint16_t *currentVal;
	/*换算角度： 0--------0-----------------50-------50------50----------------100----- --100*/
	/*当前AD值： 0-------100---------------462------512------562---------------922---- --1023*/
	/*范围定义： 左值 最小有效值        -中值范围  中值   +中值范围         最大有效值   右值*/
	uint8_t  val;           //换算后角度值
	uint16_t midVal;             //中值
	uint16_t midRange;           //中值范围
	uint16_t minValidVal;        //最小有效值
	uint16_t maxVallidVal;       //最大有效值
}RockerValStruct;

typedef struct
{
	RockerValStruct rockerVal[2];
	uint8_t  dir;                //方向
	uint8_t  dirRange;           //方向范围--值越小越灵敏 0-50
	uint16_t angle;              //角度值---与12点方向所成顺时针夹角
}YGValStruct;

extern YGValStruct YGVal[YG_Total];

void Rocker_Init(void);
void Rocker_Service(void);
void Rocker_CaliAdcValue(void);

#endif
