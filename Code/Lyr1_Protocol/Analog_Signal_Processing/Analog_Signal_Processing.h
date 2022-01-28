#ifndef __ANALOG_SIGNAL_PROCESSING_
#define __ANALOG_SIGNAL_PROCESSING_

#include "stdint.h"

typedef enum {
	YGX,
	YGY,
	BatVol, 
}ADC_List;

#define ADC_IoTotal 3
#define ADC_BuffSize 5

typedef struct
{
	uint16_t bufVal[ADC_BuffSize];          //AD缓冲值
	uint8_t curBufPoi;           //AD缓冲区当前位置指针
	uint16_t currentVal;         //当前AD值
//	/*换算角度： 0-------0-----------------50-------50------50----------------100-------100*/
//	/*当前AD值： 0------100---------------462------512------562---------------922------1023*/
//	/*范围定义： 左值  左有效值        -中值范围  中值   +中值范围          右有效值   右值*/
//	uint8_t  angleVal;           //换算后角度值
//	uint16_t midVal;             //中值
//	uint16_t midRange;           //中值范围
//	uint16_t LeftValidVal;       //左有效值
//	uint16_t RightVallidVal;     //右有效值
}ADC_ADValue_st_t;

extern ADC_ADValue_st_t ADCValue[ADC_IoTotal];

void ASP_Init(void);
void ASP_Service(void); 


#endif
