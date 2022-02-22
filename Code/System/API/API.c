/***********************************************************************************************************
* 版权                                                                                                       *
*                                                                                                          *
* 文件名称: API.c                                                                                              *
* 描     述：任务调度函数                                                                                           *
* 作     者：姜世奇                                                                                              *
* 当前版本: 1.0.1                                                                                              * 
* 完成时间:                                                                                                    *
* ---------------------------------------------------------------------------------------------------------*
* 历史信息:                                                                                                    *
*           <Date>            |    <Version>    |    <Author>    |    <Description>                        *
* ---------------------------------------------------------------------------------------------------------*
*   2019年9月26日10:49:03        |      1.0.1      |     姜世奇        |     Create file                         *            
*----------------------------------------------------------------------------------------------------------*
***********************************************************************************************************/



#include "include.h" 
#include "Line_In.h"
#include "KEY.h" 
#include "LED.h"
#include "ADC.h" 
#include "GUI_App.h" 
#include "Line_In.h"
#include "Analog_Signal_Processing.h"
#include "Rocker.h"
#include "Data_Service.h"
#include "Delay.h"
#include "menu.h"
#include "ESP32.h"


u8 API_Enable_Flag = 0;

u32 API_Step = 0;     //API步数
u8  API_Flip = 0;     //API翻转 

u8 TaskCurrent = 0;  //当前执行任务

#define TCB_TOTAL    8   //(sizeof(TaskTCBAttr)/sizeof(TaskTCBStruct))

TaskManagerStruct TaskManager[TCB_TOTAL]; //任务管理器结构体

//任务检查资源默认函数
u8 Task_CR_Def(void){ return 1; }


TaskTCBStruct TaskTCBAttr[] ={
	
{  Tack_TaskManager ,   " 任务管理器 " ,      0 ,  BLOCKED , 0 , 1000 , 0 , 0 , 0 , Task_CR_Def ,            Task_Manager , NULL},	
{  Tack_LineInCheck ,     " 硬线检测 " ,      1 ,  BLOCKED , 0 ,    1 , 0 , 0 , 0 , Task_CR_Def , LineIn_Debounce_Service , NULL},
{  Tack_KeyCheck ,        " 按键检测 " ,      2 ,  BLOCKED , 0 ,    1 , 0 , 0 , 0 , Task_CR_Def ,             KEY_Service , NULL},
{  Tack_ASP ,               " AD采集 " ,      3 ,  BLOCKED , 0 ,    1 , 0 , 0 , 0 , Task_CR_Def ,             ASP_Service , NULL},
//{  Tack_Rocker ,      " 摇杆数据采集 " ,    4 ,  BLOCKED , 0 ,    1 , 0 , 0 , 0 , Task_CR_Def ,          Rocker_Service , NULL},

//{ Tack_ESP ,           " ESP模块处理 " ,     12 ,  BLOCKED , 0 ,   20 , 0 , 0 , 0 , Task_CR_Def ,             ESP_Service , NULL},
{ Tack_DataProcess ,      " 数据处理 " ,     12 ,  BLOCKED , 0 , DATA_SERVICE_CYCLE , 0 , 0 , 0 , Task_CR_Def ,            Data_Service , NULL},
{ Tack_MenuProcess ,      " 菜单处理 " ,     13 ,  BLOCKED , 0 ,  100 , 0 , 0 , 0 , Task_CR_Def , Menu_Processing_Service , NULL},                                                          

{ Tack_Graphics ,         " 图像绘制 " ,     14 ,  BLOCKED , 0 , 1000 , 0 , 0 , 0 , Task_CR_Def ,        Graphics_Display , NULL}, //暂时直接显示                                                         
//{ Tack_GUIDisplay ,       " 图像显示 " ,   15 ,  BLOCKED , 0 ,   20 , 0 , 0 , 0 , Task_CR_Def ,             GUI_Display , NULL}, 
                                                           
{                63 ,     " 空闲任务 " ,     63 , RUNNABLE , 0 ,    0 , 0 , 0 , 0 , Task_CR_Def ,             LED_Service , NULL},
 
}; 

//任务服务
void Task_Service(void)
{
	u8 i;
	u32 cupA;
	u32 cupA0,cupB0,cupC0;
	u32 cupA1,cupB1,cupC1;
	void  (*pTaskFunc)(void);
	
	cupA = SysTick->LOAD ;
	 
	//从小到大检查任务就绪
	for(i=0;i<TCB_TOTAL;i++)
	{
		if(TaskTCBAttr[i].status == RUNNABLE)
		{	
			TaskCurrent = i;
			break;
		}
	}
	
	//防止数据溢出
	if(i >= TCB_TOTAL)
	{
		TaskCurrent = TCB_TOTAL - 1;
	}
	 
	//记录任务开始时间
	cupA0 = SysTick->VAL;
	cupB0 = API_Step;
	cupC0 = API_Flip;
	
	//开始执行任务
	TaskTCBAttr[TaskCurrent].status = RUNNING;
	pTaskFunc = TaskTCBAttr[TaskCurrent].pTaskFun;
	if(pTaskFunc != NULL)
	{
		(*pTaskFunc)();
	}
	 
	//线程进入休眠 等待倒计时结束
		//空闲任务处理
	if(TaskTCBAttr[TaskCurrent].index == 63)
	{
		TaskTCBAttr[TaskCurrent].status = RUNNABLE;
	}
	else
	{
		TaskTCBAttr[TaskCurrent].status = SLEEP;
		TaskTCBAttr[TaskCurrent].delay = TaskTCBAttr[TaskCurrent].cycle;
	}
	
	//记录结束时间
	cupA1 = SysTick->VAL; 
	cupB1 = API_Step;
	cupC1 = API_Flip;
	
	//计算任务执行用时
	if(cupC0 != cupC1)
	{
		cupB1 += API_Step_Max;
	} 
	if(cupA0 < cupA1)
	{
		if(cupB1 == 0)
		{
		  cupB1++;
		}
  	cupB1 --;
		cupA0 += cupA;
	}
	//单次运行时间 
	TaskTCBAttr[TaskCurrent].runOnceTime = (cupB1 - cupB0) * cupA + (cupA0 - cupA1);
	//1秒总运行时间
	TaskTCBAttr[TaskCurrent].run1SecTime += TaskTCBAttr[TaskCurrent].runOnceTime;
	//执行次数
	TaskTCBAttr[TaskCurrent].runNum ++;
}

//任务状态检测
//中断1ms调用一次
//计算休眠时间 检测资源是否就绪
void Task_CheckStatus(void)
{
	u8 i;
	u8 (*pTaskFunc)(void);
	  
	for(i=0;i<TCB_TOTAL;i++)
	{
		pTaskFunc = TaskTCBAttr[i].pCheckResourcesFun;
		
		switch(TaskTCBAttr[i].status)
		{
			case SLEEP:
				if(TaskTCBAttr[i].delay == 0)
				{
					TaskTCBAttr[i].status = BLOCKED;
				}			
				else
				{
					TaskTCBAttr[i].delay --;
					break;
				}
			case BLOCKED:  
			  if(pTaskFunc == NULL)
				{
					TaskTCBAttr[i].status = RUNNABLE;
				} 
				if((*pTaskFunc)())
				{
					TaskTCBAttr[i].status = RUNNABLE; 
				} 
				break;
			
			case RUNNABLE: 
				if(pTaskFunc == NULL)
				{
//					TaskTCBAttr[i].status = RUNNABLE;
					break;
				}
				if(!(*pTaskFunc)())
				{
					TaskTCBAttr[i].status = BLOCKED; 
				}   
				break;			
		}
	} 
}





//任务管理器
void Task_Manager(void)
{
	u8 i;
	u32 cupA;
	
	//赋值
	for(i=0;i<TCB_TOTAL;i++)
	{
		TaskManager[i].runOnceTime = TaskTCBAttr[i].runOnceTime / 9;
		TaskManager[i].run1SecTime = TaskTCBAttr[i].run1SecTime / 9;
		TaskManager[i].runNum      = TaskTCBAttr[i].runNum;
		
		//每秒清零一次空闲任务总执行时间和执行次数
		TaskTCBAttr[i].run1SecTime = 0;
	  TaskTCBAttr[i].runNum      = 0;
	}
	 
	//计算利用率
	for(i=0;i<TCB_TOTAL;i++)
	{
		cupA =  (u32)TaskManager[i].run1SecTime/1000; 
		TaskManager[i].utilization = cupA;
	} 
}




void API_Init(u8 SYSCLK)
{ 
	SysTick->CTRL |= 1<<1;	//产生中断服务 
	delay_init(SYSCLK);
	
//	SysTick_Ctel_Num = SysTick->CTRL;		 
//	SysTick_Val_Num = SysTick->VAL;
	INTX_ENABLE(); 
}

//API开始运行
//用于初始化结束后开始调度
void API_SetEnable(uint8_t enable)
{
	API_Enable_Flag = enable;
	if(enable == 1)
	{
		INTX_ENABLE();                   //开启所有中断
		SysTick->CTRL |= 1<<0;								//使能SysTick定时器 
	}
	else
	{
		INTX_DISABLE();                  //关闭所有中断
		SysTick->CTRL &= 0xfffffffe;								//失能SysTick定时器 
	}
	API_Step = 0;
	API_Flip = 0;
	SysTick->VAL  = 0;										//写入使其清零
}


//ststick中断函数
void SysTick_Handler(void)
{
	API_Step++;
	if(API_Step >= API_Step_Max)
	{
		API_Step = 0;
		API_Flip = 1 - API_Flip;
	}
	//资源检测
	if(API_Enable_Flag == 1)
	{
		Task_CheckStatus();
	} 
}


 
void TASK_OLED_Display(void)
{
	static u16 i = 0;

	i++;
	if(i > 3229)
		i = 0;
//	W25QXX_Read(OLED_buffer,i*1024,1024);
//	GUI_Display();
//	delay_ms(10);
	
}	

//直接就绪函数
//专用于信号状态就位后急需调用处理函数的情景
void API_ToReady(uint16_t num)
{
	TaskTCBAttr[num].status = RUNNABLE;
}




