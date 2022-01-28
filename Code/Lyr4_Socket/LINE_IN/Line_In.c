#include "Line_In.h"
#include "Analog_Signal_Processing.h"
 
const LineInDebAttr lineInDebAttr[LINEIN_TOTAL] = {	 
	{/*KEY_0             ,*/   &KeyCup[0]  ,  IO_KEY  ,  0   ,  1  },
	{/*KEY_1             ,*/   &KeyCup[1]  ,  IO_KEY  ,  0   ,  1  },
	{/*KEY_2             ,*/   &KeyCup[2]  ,  IO_KEY  ,  0   ,  1  },
	{/*KEY_3             ,*/   &KeyCup[3]  ,  IO_KEY  ,  0   ,  1  },
	{/*KEY_ROLLER_LEFT   ,*/   &KeyCup[4]  ,  IO_KEY  ,  0   ,  1  },
	{/*KEY_ROLLER_RIGHT  ,*/   &KeyCup[5]  ,  IO_KEY  ,  0   ,  1  },
	{/*KEY_ROLLER_DOWN   ,*/   &KeyCup[6]  ,  IO_KEY  ,  0   ,  1  },
};
 
//按键消抖状态
LineInDebStruct lineInDeb[LINEIN_TOTAL];

uint8_t KeyCup[LINEIN_TOTAL];


void LineIn_Init(void)
{
  uint8_t i;
	for(i=0;i<LINEIN_TOTAL;i++)
	{
		lineInDeb[i].Current = 0; 
		lineInDeb[i].Status  = DEB_NOT;
	  lineInDeb[i].Timer   = 0;
		lineInDeb[i].BackupTimer = 50000;
	} 
}

//按键消抖服务函数 
//1ms执行一次
void LineIn_Debounce_Service(void)
{
	uint8_t i;
	LineIn_RefreshKeyVal();
	for(i=0;i<LINEIN_TOTAL;i++)
	{
		LineIn_Debounce(i);
	} 
}

//消抖检测函数
void LineIn_Debounce(uint8_t keyID)
{
	if(lineInDebAttr[keyID].Type == AD_KEY)
	{
		//AD按键处理
		lineInDeb[keyID].Current = *(lineInDebAttr[keyID].pCup);
		lineInDeb[keyID].Status = DEB_VALID;
	}
	else if(lineInDebAttr[keyID].Type == IO_KEY) 
	{
		switch(lineInDeb[keyID].Status)
		{
			//无效
			case DEB_NOT:
				if(*(lineInDebAttr[keyID].pCup) == lineInDebAttr[keyID].Valid)        //引脚电平位为有效位
				{
					lineInDeb[keyID].Status = DEB_DEBOUNCE_0; 						             //引脚状态为消抖中
					lineInDeb[keyID].BackupTimer = lineInDeb[keyID].Timer;
					lineInDeb[keyID].Timer = 0;
				}
				else
				{
//					lineInDeb[keyID].Current = 0;
					if(lineInDeb[keyID].Timer <50000)
						lineInDeb[keyID].Timer++; 
				}
			  break;
			//无效->有效 消抖中
			case DEB_DEBOUNCE_0:
				if(*(lineInDebAttr[keyID].pCup) == lineInDebAttr[keyID].Valid)
				{
					lineInDeb[keyID].Timer++;
					if(lineInDeb[keyID].Timer > LINE_IN_DEBOUNCE_CYCLE)
					{
						lineInDeb[keyID].Status = DEB_VALID; 
						lineInDeb[keyID].Current = 1;
					  lineInDeb[keyID].Timer = 0;
					}
				}	
				else
				{
					lineInDeb[keyID].Status = DEB_NOT; 
					lineInDeb[keyID].Current = 0;
					lineInDeb[keyID].Timer = 0;
					lineInDeb[keyID].BackupTimer = 50000;
				}
				break;
			//有效	
			case DEB_VALID:
				if(*(lineInDebAttr[keyID].pCup) == lineInDebAttr[keyID].Valid)
				{
					if(lineInDeb[keyID].Timer <50000)
						lineInDeb[keyID].Timer++; 
				}
				else
				{ 
					lineInDeb[keyID].Status = DEB_DEBOUNCE_1;  
					lineInDeb[keyID].Current = 1; 
					lineInDeb[keyID].BackupTimer = lineInDeb[keyID].Timer; 
					lineInDeb[keyID].Timer = 0;
				}
				break;
			//有效->无效 消抖中
			case DEB_DEBOUNCE_1:
				if(*(lineInDebAttr[keyID].pCup) != lineInDebAttr[keyID].Valid)
				{
					lineInDeb[keyID].Timer++;
					if(lineInDeb[keyID].Timer > LINE_IN_DEBOUNCE_CYCLE)
					{
						lineInDeb[keyID].Status = DEB_NOT; 
						lineInDeb[keyID].Current = 0; 
						lineInDeb[keyID].Timer = 0;
					}
				}
				else
				{
					lineInDeb[keyID].Status = DEB_VALID;  
					lineInDeb[keyID].Timer = lineInDeb[keyID].Timer + lineInDeb[keyID].BackupTimer;
					if(lineInDeb[keyID].Timer >= 50000 )
						lineInDeb[keyID].Timer = 50000;
				}
				break;
		}
	}
}

//刷新按键容器数值
void LineIn_RefreshKeyVal(void)
{ 
	KeyCup[0]  = KEY_0_IN;
	KeyCup[1]  = KEY_1_IN;
	KeyCup[2]  = KEY_2_IN;
	KeyCup[3]  = KEY_3_IN;
	KeyCup[4]  = ROLLER_LEFT;
	KeyCup[5]  = ROLLER_RIGHT;
	KeyCup[6]  = ROLLER_DOWN; 
}


