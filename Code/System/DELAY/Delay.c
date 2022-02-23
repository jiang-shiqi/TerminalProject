/***********************************************************************************************************
* 版权                                                                                                       *
*                                                                                                          *
* 文件名称: Delay.c                                                                                            *
* 描    述: 使用嘀嗒定时器制作的OS与非OS延时函数                                                                             *
* 作    者: 姜世奇                                                                                              *
* 当前版本: 1.0.1                                                                                              *  
* 完成时间:                                                                                                    *
* ---------------------------------------------------------------------------------------------------------*
* 历史信息:                                                                                                    *
*           <Date>            |    <Version>    |    <Author>    |    <Description>                        *
* ---------------------------------------------------------------------------------------------------------*
*   2019年9月26日10:49:03        |      1.0.1      |     姜世奇        |     Create file                         *            
*----------------------------------------------------------------------------------------------------------*
***********************************************************************************************************/
#include "Delay.h"	 

static u8  fac_us=0;							//us延时倍乘数			   
static u16 fac_ms=0;							//ms延时倍乘数,在ucos下,代表每个节拍的ms数

u32 Timer_1ms = 0ul;

void delay_init(u8 SYSCLK)
{	
	fac_us=SYSCLK/8;					    	//不论是否使用OS,fac_us都需要使用
	fac_ms=(u16)fac_us*1000;				//非OS下,代表每个ms需要的systick时钟数  

	Timer_1ms = SLICE_MS * fac_ms;      //记录1ms的嘀嗒定时器所需步骤
	
	SysTick->LOAD = SLICE_MS * fac_ms;	//以1ms作为时基单位
	SysTick->VAL  = 0;										//写入使其清零
 	SysTick->CTRL &= ~(1<<2);							//SYSTICK使用外部时钟源	  
	SysTick->CTRL |= 1<<0;								//使能SysTick定时器 
}								    

//延时nus
//nus为要延时的us数.		    								   
void delay_us(u32 nus)
{		
//	unsigned int API_ExpVal;		//API期望值
//	unsigned int API_CurVal;		//API当前值
	u32 Tick_ExpVal;		//sysTick期望值
	u32 Tick_CurVal;		//sysTick当前值
	u32 Tick_Filp;			//API翻转值
	
	u32 CupA;
	
	Tick_Filp = API_Flip;
	
//	Tick_CurVal = SLICE_MS * fac_ms- SysTick->CTRL + API_Step * SLICE_MS * fac_ms;
	Tick_CurVal = SLICE_MS * fac_ms * (API_Step + 1) - SysTick->CTRL;
	
	if(((nus / 1000) + API_Step) >= API_Step_Max)
	{
		Tick_ExpVal = Tick_CurVal + ((nus / 1000) + API_Step - API_Step_Max) * SLICE_MS * fac_ms;
		Tick_Filp = 1 - Tick_Filp;
	}
	else 
	{
		Tick_ExpVal = Tick_CurVal + (nus / 1000) * SLICE_MS * fac_ms;
	}
	
	while(1)
	{
		CupA = SLICE_MS * fac_ms - SysTick->CTRL;
		if((Tick_Filp == API_Flip)&&((CupA + API_Step * SLICE_MS * fac_ms ) >= Tick_ExpVal))
			break;
	}
	
	//	if((nms + API_Step) >= API_Step_Max)
//	{
//		Tick_ExpVal = Tick_CurVal + (nms + API_Step - API_Step_Max) * SLICE_MS * fac_ms;
//		Tick_Filp = 1 - Tick_Filp;
//	}
//	else 
//		Tick_ExpVal = Tick_CurVal + nms * SLICE_MS * fac_ms;
//	
	
	
//	
//	API_CurVal = API_Step;				//保存定时器现值
//	Tick_CurVal = SysTick->VAL;
//	
//	if(nus*fac_us >= Tick_CurVal)
//	{
//		CupA = nus*fac_us - Tick_CurVal;
//		Tick_ExpVal = (SLICE_MS * fac_ms) - (CupA % (SLICE_MS * fac_ms));
//		API_ExpVal = API_CurVal + CupA / (SLICE_MS * fac_ms) + 1;
//		if(API_ExpVal >= API_Step_Max) 
//			API_ExpVal = 0;  
//	}
//	else
//	{
//		CupA = nus*fac_us;
//		Tick_ExpVal = Tick_CurVal - CupA;
//		API_ExpVal = API_CurVal;
//	}
//	
//	while(1)
//	{
//		CupA = SysTick->VAL;
//		if((API_Step >= API_ExpVal)&&(CupA <= Tick_ExpVal))
//			break;
//	} 
}

//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*8*10 00/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对72M条件下,nms<=1864 
//仅为 1ms 时间片可用
void delay_ms(u16 nms)
{	 		  	  
//	unsigned int API_ExpVal;		//API期徒值
//	unsigned int API_CurVal;		//API当前值
	u32 Tick_ExpVal;		//sysTick期望值
	u32 Tick_CurVal;		//sysTick当前值
	u32 Tick_Filp;			//API翻转值
	
	u32 CupA;
	
	Tick_Filp = API_Flip;
	
//	Tick_CurVal = SLICE_MS * fac_ms- SysTick->CTRL + API_Step * SLICE_MS * fac_ms;
	Tick_CurVal = SLICE_MS * fac_ms * (API_Step + 1) - SysTick->CTRL;
	
	if((nms + API_Step) >= API_Step_Max)
	{
		Tick_ExpVal = Tick_CurVal + (nms + API_Step - API_Step_Max) * SLICE_MS * fac_ms;
		Tick_Filp = 1 - Tick_Filp;
	}
	else 
	{
		Tick_ExpVal = Tick_CurVal + nms * SLICE_MS * fac_ms;
	}
	
	while(1)
	{
		CupA = SLICE_MS * fac_ms - SysTick->CTRL;
		if((Tick_Filp == API_Flip)&&((CupA + API_Step * SLICE_MS * fac_ms ) >= Tick_ExpVal))
			break;
	}
	 
} 



////systick中断服务函数 
//void SysTick_Handler(void)
//{	
//	if(delay_osrunning==1)					//OS开始跑了,才执行正常的调度处理
//	{
//		OSIntEnter();						//进入中断
//		OSTimeTick();       				//调用ucos的时钟服务程序               
//		OSIntExit();       	 				//触发任务切换软中断
//	}
//}
