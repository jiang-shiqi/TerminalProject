#include "Analog_Signal_Processing.h"
#include "ADC.h"
#include "GPIO.h"
#include "delay.h"

ADC_ADValue_st_t ADCValue[ADC_IoTotal];

void ASP_Init(void)
{
	uint8_t i; 

	for(i=0;i<ADC_IoTotal;i++)
	{
		ADCValue[i].curBufPoi = 0;
	}	
}

void ASP_Service(void)
{ 
	//算出电压 单位mV
	ADCValue[0].bufVal[0] = Get_Adc_Value(0)*3300/2048;
	
 
}















