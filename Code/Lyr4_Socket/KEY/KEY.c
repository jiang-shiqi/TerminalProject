#include "KEY.h"
#include "include.h"
#include "Delay.h"
#include "LED.h"
#include "GPIO.h"
#include "Line_In.h"

/*** 按键属性列表 ***/
const KeyAttrStruct KeyAttrTable[KEY_TOTAL] =
{
/*===================================================================== 
-----------------------------------------------------------------------
    ID           |     长按检测模式   | 连按检测使能
---------------------------------------------------------------------*/
//{/*	KEY_UP           */     KEY_HOLD_ONLY,         0,     },
//{/*	KEY_DOWN         */     KEY_HOLD_ONLY,         0,     },
//{/*	KEY_LEFT         */     KEY_HOLD_ONLY,         0,     },
//{/*	KEY_RIGHT        */     KEY_HOLD_ONLY,         0,     }, 
{/*	KEY_A            */     KEY_LONG_ONLY,         0,     },
{/*	KEY_B            */     KEY_LONG_ONLY,         0,     },
{/*	KEY_X            */     KEY_LONG_ONLY,         0,     },
{/*	KEY_Y            */     KEY_LONG_ONLY,         0,     },
{/*	KEY_ROLLER_LEFT  */     KEY_LONG_ONLY,         0,     },
{/*	KEY_ROLLER_RIGHT */     KEY_LONG_ONLY,         0,     },
{/*	KEY_ROLLER_DOWN  */     KEY_LONG_ONLY,         0,     },
/*===================================================================*/
};
		
KeyDetectStruct keyDetectStruct[KEY_TOTAL_NUMBER];

void KEY_init(void)
{
	uint8_t i;
	 
	LineIn_Init();
	for(i=0;i<KEY_TOTAL_NUMBER;i++)
	{
		keyDetectStruct[i].UpdateEnable = 0;
		keyDetectStruct[i].Timer = 0;
		keyDetectStruct[i].IdleTimer = 0;
		keyDetectStruct[i].FinalStatus = KEY_IDLE;
		keyDetectStruct[i].CurrentStatus = KEY_IDLE;
	}
}
 
void KEY_Service(void)
{ 
	uint8_t i = 0;
	
//	LineIn_Debounce_Service();
	
	for(i=0;i<KEY_TOTAL_NUMBER;i++)
	{
		switch(keyDetectStruct[i].CurrentStatus)
		{
			case KEY_IDLE:       //无效
				if(lineInDeb[i].Current == 1)
				{
					//按键间隔小于双击最大间隔 并符合进入双击状态条件
					if((keyDetectStruct[i].FinalStatus == KEY_PRESS)&&(keyDetectStruct[i].IdleTimer < KEY_DOUBLE_INTERVAL)&&(KeyAttrTable[i].DoubleDetEn))
					{
						keyDetectStruct[i].FinalStatus = keyDetectStruct[i].CurrentStatus;
						keyDetectStruct[i].CurrentStatus = KEY_DOUBLE;
						keyDetectStruct[i].Timer = 0;
						keyDetectStruct[i].UpdateEnable = 1;
					}
					else
					{
						keyDetectStruct[i].FinalStatus = keyDetectStruct[i].CurrentStatus;
						keyDetectStruct[i].CurrentStatus = KEY_PRESS;
						keyDetectStruct[i].Timer = 0;
						keyDetectStruct[i].UpdateEnable = 1;
					}
				}
				else
				{
					if(keyDetectStruct[i].IdleTimer < 50000)
						keyDetectStruct[i].IdleTimer ++;
				}
				break;
			case KEY_PRESS:      //短按
				if(lineInDeb[i].Current == 1)
				{
					//短按时间累加
					if(keyDetectStruct[i].Timer < 65535)
						keyDetectStruct[i].Timer ++;
					//按键达到按住时间 并符合进入按键按住状态条件
					if((keyDetectStruct[i].Timer > KEY_HOLD_THRESHOLD)&&(KeyAttrTable[i].HoldDetMode & KEY_HOLD_ONLY))
					{
						keyDetectStruct[i].FinalStatus = keyDetectStruct[i].CurrentStatus;
						keyDetectStruct[i].CurrentStatus = KEY_HOLD; 
						keyDetectStruct[i].UpdateEnable = 1; 
					}
					//按键达到长按时间 并符合进入按键长按状态条件
					else if((keyDetectStruct[i].Timer > KEY_LONG_THRESHOLD)&&(KeyAttrTable[i].HoldDetMode & KEY_LONG_ONLY))
					{
						keyDetectStruct[i].FinalStatus = keyDetectStruct[i].CurrentStatus;
						keyDetectStruct[i].CurrentStatus = KEY_LONG; 
						keyDetectStruct[i].UpdateEnable = 1; 
					}
					//按键达到卡住时间 并符合进入按键卡住状态条件
					else if((keyDetectStruct[i].Timer > KEY_STUCK_THRESHOLD)&&(KeyAttrTable[i].HoldDetMode & KEY_STUCK_ONLY))
					{
						keyDetectStruct[i].FinalStatus = keyDetectStruct[i].CurrentStatus;
						keyDetectStruct[i].CurrentStatus = KEY_STUCK; 
						keyDetectStruct[i].UpdateEnable = 1; 
					}
				}
				else
				{
					keyDetectStruct[i].FinalStatus = keyDetectStruct[i].CurrentStatus;
					keyDetectStruct[i].CurrentStatus = KEY_IDLE; 
					keyDetectStruct[i].Timer = 0;
					keyDetectStruct[i].UpdateEnable = 1; 
				}
				break;
			case KEY_HOLD:       //按住
				if(lineInDeb[i].Current == 1)
				{
					//短按时间累加
					if(keyDetectStruct[i].Timer < 65535)
						keyDetectStruct[i].Timer ++;
					 
					//按键达到长按时间 并符合进入按键长按状态条件
					if((keyDetectStruct[i].Timer > KEY_LONG_THRESHOLD)&&(KeyAttrTable[i].HoldDetMode & KEY_LONG_ONLY))
					{
						keyDetectStruct[i].FinalStatus = keyDetectStruct[i].CurrentStatus;
						keyDetectStruct[i].CurrentStatus = KEY_LONG; 
						keyDetectStruct[i].UpdateEnable = 1; 
					}
					//按键达到卡住时间 并符合进入按键卡住状态条件
					else if((keyDetectStruct[i].Timer > KEY_STUCK_THRESHOLD)&&(KeyAttrTable[i].HoldDetMode & KEY_STUCK_ONLY))
					{
						keyDetectStruct[i].FinalStatus = keyDetectStruct[i].CurrentStatus;
						keyDetectStruct[i].CurrentStatus = KEY_STUCK; 
						keyDetectStruct[i].UpdateEnable = 1; 
					}
				}
				else
				{
					keyDetectStruct[i].FinalStatus = keyDetectStruct[i].CurrentStatus;
					keyDetectStruct[i].CurrentStatus = KEY_IDLE; 
					keyDetectStruct[i].Timer = 0;
					keyDetectStruct[i].UpdateEnable = 1; 
				}
				break;
			case KEY_LONG:       //长按
				if(lineInDeb[i].Current == 1)
				{
					//短按时间累加
					if(keyDetectStruct[i].Timer < 65535)
						keyDetectStruct[i].Timer ++;
					 
					 
					//按键达到卡住时间 并符合进入按键卡住状态条件
				  if((keyDetectStruct[i].Timer > KEY_STUCK_THRESHOLD)&&(KeyAttrTable[i].HoldDetMode & KEY_STUCK_ONLY))
					{
						keyDetectStruct[i].FinalStatus = keyDetectStruct[i].CurrentStatus;
						keyDetectStruct[i].CurrentStatus = KEY_STUCK; 
						keyDetectStruct[i].UpdateEnable = 1; 
					}
				}
				else
				{
					keyDetectStruct[i].FinalStatus = keyDetectStruct[i].CurrentStatus;
					keyDetectStruct[i].CurrentStatus = KEY_IDLE; 
					keyDetectStruct[i].Timer = 0;
					keyDetectStruct[i].UpdateEnable = 1; 
				}
				break;
			case KEY_STUCK:      //卡住
				if(lineInDeb[i].Current == 1)
				{
					//短按时间累加
					if(keyDetectStruct[i].Timer < 65535)
						keyDetectStruct[i].Timer ++; 
				}
				else
				{
					keyDetectStruct[i].FinalStatus = keyDetectStruct[i].CurrentStatus;
					keyDetectStruct[i].CurrentStatus = KEY_IDLE; 
					keyDetectStruct[i].Timer = 0;
					keyDetectStruct[i].UpdateEnable = 1; 
				}
				break;
			case KEY_DOUBLE:     //双击
				if(lineInDeb[i].Current == 1)
				{
					//短按时间累加
					if(keyDetectStruct[i].Timer < 65535)
						keyDetectStruct[i].Timer ++; 
				}
				else
				{
					keyDetectStruct[i].FinalStatus = keyDetectStruct[i].CurrentStatus;
					keyDetectStruct[i].CurrentStatus = KEY_IDLE; 
					keyDetectStruct[i].Timer = 0;
					keyDetectStruct[i].UpdateEnable = 1; 
				} 
				break;
		}
	} 
 	return ;
}	





