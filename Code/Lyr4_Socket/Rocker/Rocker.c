#include "Rocker.h"

YGValStruct YGVal[YG_Total];

void Rocker_Init(void)
{
	uint8_t i;
	for(i=0;i<YG_Total;i++)
	{
		YGVal[i].rockerVal[0].val             =  50;
		YGVal[i].rockerVal[0].midVal          = 512;
		YGVal[i].rockerVal[0].midRange        =  50;
		YGVal[i].rockerVal[0].minValidVal     = 100;
		YGVal[i].rockerVal[0].maxVallidVal    = 922; 
		
		YGVal[i].rockerVal[1].val             =  50;
		YGVal[i].rockerVal[1].midVal          = 512;
		YGVal[i].rockerVal[1].midRange        =  50;
		YGVal[i].rockerVal[1].minValidVal     = 100;
		YGVal[i].rockerVal[1].maxVallidVal    = 922; 
		
		YGVal[i].angle               = 0;
		YGVal[i].dir                 = DIR_IDLE;
		YGVal[i].dirRange            = 15; 
		
	} 
	
	YGVal[0].rockerVal[0].currentVal = &ADCValue[YGX].currentVal;
	YGVal[0].rockerVal[1].currentVal = &ADCValue[YGY].currentVal;
	
	Rocker_CaliAdcValue();
}

void Rocker_Service(void)
{
	uint8_t i,j;
	for(i=0;i<YG_Total;i++)
	{ 
		for(j=0;j<2;j++)
		{
			//在中值范围内
			if((*(YGVal[i].rockerVal[0].currentVal) >= (YGVal[i].rockerVal[0].midVal - YGVal[i].rockerVal[0].midRange))&&   \
				 (*(YGVal[i].rockerVal[0].currentVal) <= (YGVal[i].rockerVal[0].midVal + YGVal[i].rockerVal[0].midRange))&&   \
				 (*(YGVal[i].rockerVal[1].currentVal) >= (YGVal[i].rockerVal[1].midVal - YGVal[i].rockerVal[1].midRange))&&   \
				 (*(YGVal[i].rockerVal[1].currentVal) <= (YGVal[i].rockerVal[1].midVal + YGVal[i].rockerVal[1].midRange)))
			{ 
				YGVal[i].rockerVal[j].val = 50;	  
			}
			
	 
			//小于中值范围
			else if(*(YGVal[i].rockerVal[j].currentVal) <= YGVal[i].rockerVal[j].midVal)
			{
				//在有效区外
				if(*(YGVal[i].rockerVal[j].currentVal) < YGVal[i].rockerVal[j].minValidVal)
					YGVal[i].rockerVal[j].val = 0;
				else
				{
					YGVal[i].rockerVal[j].val = (*(YGVal[i].rockerVal[j].currentVal) - YGVal[i].rockerVal[j].minValidVal)*50/(YGVal[i].rockerVal[j].midVal - YGVal[i].rockerVal[j].minValidVal);
				}
			}
			//大于中值范围
			else if(*(YGVal[i].rockerVal[j].currentVal) > YGVal[i].rockerVal[j].midVal)
			{
				//在有效区外
				if(*(YGVal[i].rockerVal[j].currentVal) > YGVal[i].rockerVal[j].maxVallidVal)
					YGVal[i].rockerVal[j].val = 100;
				else
				{
					YGVal[i].rockerVal[j].val = 50 + (*(YGVal[i].rockerVal[j].currentVal) - YGVal[i].rockerVal[j].midVal)*50/(YGVal[i].rockerVal[j].maxVallidVal - YGVal[i].rockerVal[j].midVal);
				}
			}
		}
		
		//硬件错误补丁
		if(i == 0)
		{
			YGVal[0].rockerVal[0].val = 100 - YGVal[0].rockerVal[0].val;
			YGVal[0].rockerVal[1].val = 100 - YGVal[0].rockerVal[1].val;
		}
		 
		//方向计算
		YGVal[i].dir = 0;
		//上
		if(YGVal[i].rockerVal[1].val <= 50 - YGVal[i].dirRange)
		{
			YGVal[i].dir += DIR_UP;
		}
		//下
		if(YGVal[i].rockerVal[1].val >  50 + YGVal[i].dirRange)
		{
		  YGVal[i].dir += DIR_DOWN;
		}
		//左
		if(YGVal[i].rockerVal[0].val <= 50 - YGVal[i].dirRange)
		{
		  YGVal[i].dir += DIR_LEFT;
		}
		//右
		if(YGVal[i].rockerVal[0].val >  50 + YGVal[i].dirRange)
		{
		  YGVal[i].dir += DIR_RIGHT; 
		}
		
		//夹角计算
		
	}
		
}

//校准AD中值
void Rocker_CaliAdcValue(void) 
{
	uint8_t i,j;
	
	for(i=0;i<ADC_IoTotal;i++)
	{
		for(j=0;j<2;j++)
		{ 
			YGVal[i].rockerVal[j].midVal = *(YGVal[i].rockerVal[j].currentVal); 
		}  
	}
}



