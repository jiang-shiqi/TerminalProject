/***********************************************************************************************************
* 版权                                                                                                     *
*                                                                                                          *
* 文件名称: API.h                                                                                          *
* 描    述: 记录任务调度的属性和函数的声明                                                                 *
* 作    者: 姜世奇                                                                                         *
* 当前版本: 1.0.1                                                                                          *  
* 完成时间:                                                                                                *
* ---------------------------------------------------------------------------------------------------------*
* 历史信息:                                                                                                *
*           <Date>            |    <Version>    |    <Author>    |    <Description>                        *
* ---------------------------------------------------------------------------------------------------------*
*   2019年9月26日10:49:03     |      1.0.1      |     姜世奇     |     Create file                         *            
*----------------------------------------------------------------------------------------------------------*
***********************************************************************************************************/

#ifndef _API_H_
#define _API_H_

#include "sys.h" 
#include "core_cm4.h"

#define SLICE_MS 1

 

//任务块结构体
typedef struct
{
	const u8    index;                     //任务索引
	const u8    *name;                     //任务名称
	      u8    PRIO;                      //任务优先级  0-63
	      u8    status;                    //任务状态
	      u32   delay;                     //延时时间
	const u32   cycle;                    //任务执行周期时间       ms
	      u32   runOnceTime;               //执行单次任务所需时间   us
	      u32   run1SecTime;               //1秒总执行任务所需时间  us
	      u32   runNum;                    //执行次数
	u8    (*pCheckResourcesFun)(void);     //资源检查函数
	void  (*pTaskFun)(void);               //任务函数
	void  (*pErr)(void);                   //错误函数
}TaskTCBStruct;

//任务管理器结构体
typedef struct
{
    u16 utilization;         //CPU利用率
	u32 runOnceTime;         //单次执行时间
	u32 run1SecTime;         //1秒总执行时间
	u32 runNum;              //运行次数
	
}TaskManagerStruct;

enum TaskStatusEnum
{
    RUNNABLE,            //可运行
	BLOCKED,             //阻塞
	SLEEP,               //休眠
	RUNNING,             //运行中 
};
 

typedef enum
{
	Tack_TaskManager,   //  任务管理器
	
	Tack_LineInCheck,   //  硬线检测 
	Tack_KeyCheck,      //  按键检测 
	Tack_ASP,           //  AD采集 
	Tack_Rocker,        //  摇杆数据采集 
	Tack_ESP,           //  ESP模块处理  
	Tack_DataProcess,   //  数据处理 
	Tack_MenuProcess,   //  菜单处理 
	Tack_Graphics,      //  图像绘制 
	Tack_GUIDisplay,    //  图像显示 
	Tack_Idle,          //  空闲任务  
	
	Tack_Num_Sentry,
}Tack_Num_en;



void Task_CheckStatus(void);
void Task_Manager(void);
void Task_Service(void); 

u8 Task_CR_Def(void);  //任务检查资源默认函数

 


extern u32 API_Step;
extern u8  API_Flip;	 
extern TaskTCBStruct TaskTCBAttr[];

#define API_Step_Max 10000
 
void API_Init(u8 SYSCLK);
void API_SetEnable(uint8_t enable);
void API_Update(void);

//直接就绪函数
void API_ToReady(uint16_t num);

/*-------------------------------------
调度函数
-------------------------------------*/ 



/*-------------------------------------
任务函数
-------------------------------------*/ 
void TASK_OLED_Display(void);

#endif

