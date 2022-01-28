#include "Menu.h"
#include "API.h"
#include "Data_Service.h"
//#include "Files.h"

 
//单页子项个数
#define CONTENT_TOTAL 7

//标题Y轴（X需自行计算）
#define TITLE_Y 5   
//横线坐标
const uint16_t LINE_Y[] = {34, 256}; 
//子项坐标
const uint16_t CONTENT_X = 16;
const uint16_t CONTENT_Y[] = {50, 80, 110, 140, 170, 200, 230};
//菜单外发数据坐标
#define SENDOUT_ID_X 16
#define SENDOUT_ID_Y 80
const uint16_t SENDOUT_X[] = {54, 90, 126, 162};
const uint16_t SENDOUT_Y[] = {110, 140};





//菜单信息
_Menu_Info 	 menuInfo;
//菜单用-显示数据
_Menu_Dat 	 menuDat;
//菜单用-按键值
_Menu_KeyVal menuKeyVal; 

//菜单属性
_Menu_Attribute Menu_Level_Tab[]=
{
   { 0,   0,   0,   0,   7,        NULL,            NULL  ,     NULL   ,      NULL,                NULL,     NULL                          },
      
/*
    { 0,   0,   0,   0,   7,        Menu_Show_LED,   NULL  ,     NULL   ,      Menu_SW,                Menu_Set_LED,     zhishideng                          },
    { 0,   7,   0,   1,   7,          NULL       ,   NULL  ,     NULL   ,      Menu_SW,                   NULL     ,     liangbiao                           },
    { 0,  18,   0,   2,   7,          NULL       ,   NULL  ,     NULL   ,      Menu_SW,                   NULL     ,     zhutiqiehuan                        },
    { 0,  21,   0,   3,   7,          NULL       ,   NULL  ,     NULL   ,      Menu_SW,                   NULL     ,     duomeitiqingling                    },
    { 0,   4,   0,   4,   7,    Menu_Show_SendOut,   NULL  ,     NULL   ,      Menu_SW,            Menu_Set_SendOut,     waifabaowen                         },
    { 0,   5,   0,   5,   7,       Menu_Show_Warn,   NULL  ,     NULL   ,      Menu_SW,               Menu_Set_Warn,     baojingxinxi                        },
    { 0,   6,   0,   6,   7,   Menu_Show_UESwitch,   NULL  ,     NULL   ,      Menu_SW,                 Menu_Set_UE,     UExianshi                           },
    { 1,   7,   0,   0,  10,          NULL       ,  Menu_Up,   Menu_Down,      Menu_SW,               Menu_Set_Gear,     dangwei                             },
    { 1,   8,   0,   1,  10,          NULL       ,  Menu_Up,   Menu_Down,      Menu_SW,              Menu_Set_Clock,     shizhong                            },
    { 1,   9,   0,   2,  10,          NULL       ,  Menu_Up,   Menu_Down,      Menu_SW,        Menu_Set_Temperature,     wendu                               },
    { 1,  10,   0,   3,  10,          NULL       ,  Menu_Up,   Menu_Down,      Menu_SW,              Menu_Set_Power,     gonglv                              },
    { 1,  11,   0,   4,  10,          NULL       ,  Menu_Up,   Menu_Down,      Menu_SW,             Menu_Set_Vspeed,     chesu                               },
    { 1,  12,   0,   5,  10,          NULL       ,  Menu_Up,   Menu_Down,      Menu_SW,             Menu_Set_Espeed,     zhuansu                             },
    { 1,  13,   0,   6,  10,          NULL       ,  Menu_Up,   Menu_Down,      Menu_SW,            Menu_Set_Battery,     dianliang                           },
    { 1,  14,   0,   7,  10,          NULL       ,  Menu_Up,   Menu_Down,      Menu_SW,               Menu_Set_Fuel,     ranyou                              },
    { 1,  15,   0,   8,  10,          NULL       ,  Menu_Up,   Menu_Down,      Menu_SW,   Menu_Set_WaterTemperature,     shuiwen                             },
    { 1,  16,   0,   9,  10,          NULL       ,  Menu_Up,   Menu_Down,      Menu_SW,            Menu_Set_Mileage,     licheng                             },
	{ 1,   1,   0,  10,  10,          NULL       ,   NULL  ,     NULL   ,      Menu_SW,            Menu_Return     ,                       NULL              },
    { 1,  18,   1,   0,   2,          NULL       ,  Menu_Up,   Menu_Down,      Menu_SW,          Menu_Set_Backlight,     beiguangqiehuan                     },
    { 1,  19,   1,   1,   2,          NULL       ,  Menu_Up,   Menu_Down,      Menu_SW,     Menu_Set_LanguageSwitch,     zhongyingwenqiehuan                 },
	{ 1,   2,   1,   2,   2,          NULL       ,   NULL  ,     NULL   ,      Menu_SW,            Menu_Return     ,                       NULL              },																	      
    { 1,  21,   2,   0,   5,          NULL       ,  Menu_Up,   Menu_Down,      Menu_SW,    Menu_Set_ClearMultimedia,     qinglingranyouxiaohao               },
    { 1,  22,   2,   1,   5,          NULL       ,  Menu_Up,   Menu_Down,      Menu_SW,    Menu_Set_ClearMultimedia,     qinglingwaijiechongdiandianliang    },
    { 1,  23,   2,   2,   5,          NULL       ,  Menu_Up,   Menu_Down,      Menu_SW,    Menu_Set_ClearMultimedia,     qinglingpingjunchesu                },
    { 1,  24,   2,   3,   5,          NULL       ,  Menu_Up,   Menu_Down,      Menu_SW,    Menu_Set_ClearMultimedia,     qinglingxingshishijian              },
    { 1,  25,   2,   4,   5,          NULL       ,  Menu_Up,   Menu_Down,      Menu_SW,    Menu_Set_ClearMultimedia,     qingling50kmpingjunnenghao          },
	{ 1,   3,   2,   5,   5,          NULL       ,   NULL  ,     NULL   ,      Menu_SW,            Menu_Return     ,                       NULL              },	

*/
};
	
void Menu_Initialization(void)
{
	menuInfo.index = 0;
	menuInfo.indexBackup = 0xffff;
	menuInfo.refreshFlag = 1;
	menuInfo.titleBackup = 0xffff;
	menuInfo.pageBackup = 0xffff;

	menuKeyVal.status         = 0;
	menuKeyVal.statusBackup   = 0;
	menuKeyVal.upKeyStatus    = 0;
	menuKeyVal.downKeyStatus  = 0;
	menuKeyVal.swKeyStatus    = 0;
	menuKeyVal.setKeyStatus   = 0;

	

	
	
 	//TFT_LCD_Draw_Box(0,            0, 239, 319,0, 0); // 
	
	
	
}

//数据处理
//界面切换 刷新阈值控制
void Menu_DataProcessing(void)
{
	switch (menuKeyVal.status)
	{
		case MenuKeyUp:
			if(Menu_Level_Tab[menuInfo.index].upOperation != NULL)
			{
				Menu_Level_Tab[menuInfo.index].upOperation();
			}
			break;
			
		case MenuKeyDown:
			if(Menu_Level_Tab[menuInfo.index].downOperation != NULL)
			{
				Menu_Level_Tab[menuInfo.index].downOperation();
			}
			break;
			
		case MenuKeySW:
			if(Menu_Level_Tab[menuInfo.index].switchOperation != NULL)
			{
				Menu_Level_Tab[menuInfo.index].switchOperation();
			}
			break;
			
		case MenuKeySet:
			if(Menu_Level_Tab[menuInfo.index].confirmOperation != NULL)
			{
				Menu_Level_Tab[menuInfo.index].confirmOperation();
			}
			break;
	}

	menuKeyVal.status = MenuKeyINV;

	if(menuInfo.index != menuInfo.indexBackup)
	{
	  menuInfo.refreshFlag = 1;
	  menuInfo.indexBackup = menuInfo.index;
	}
}

//按键处理
void Menu_KeyProcessing(void)
{
	uint8_t tempA = 0;
	
	menuKeyVal.upKeyStatus	  = 0;
	menuKeyVal.downKeyStatus  = 0;
	menuKeyVal.swKeyStatus	  = 0;
	menuKeyVal.setKeyStatus   = 0;
	
	if(menuKeyVal.upKeyStatus == 0)
	{
		tempA = MenuKeyUp;
	}
	else if(menuKeyVal.downKeyStatus == 0)
	{
		tempA = MenuKeyDown;
	}
	if(menuKeyVal.swKeyStatus == 0)
	{
		tempA = MenuKeySW;
	}
	if(menuKeyVal.setKeyStatus == 0)
	{
		tempA = MenuKeySet;
 	}

	if((menuKeyVal.statusBackup == tempA)&&(menuKeyVal.status == MenuKeyINV))
	{
		menuKeyVal.status = MenuKeyINV;
	}
 	else
 	{
		menuKeyVal.status = tempA;
		menuKeyVal.statusBackup = menuKeyVal.status;
 	}
	

//	if((menuKeyVal.upKeyStatus == 1)&&(menuKeyVal.downKeyStatus == 1)&&(menuKeyVal.swKeyStatus == 1)&&(menuKeyVal.setKeyStatus == 1))
//	{
//		menuKeyVal.status = MenuKeyINV;
//	}
}

//菜单显示
void Menu_Display_Service(void)
{
	uint16_t page = 0;
	uint16_t i,j;
	uint16_t tempA,tempB;

	if(menuInfo.refreshFlag == 1)
	{
		menuInfo.refreshFlag = 0;

		tempA = Menu_GetTitle();
		tempB = Menu_GetCurrentPage();
		if(menuInfo.titleBackup != tempA)
		{
//  			TFT_LCD_Draw_Box(0,            0, 239, TITLE_Y + 24,TFT_LCD_FILL_FULL, TFT_LCD_TYPE_CLR); //标题清除
//  			TFT_LCD_Draw_Box(0, CONTENT_Y[0], 239, CONTENT_Y[CONTENT_TOTAL-1] + 24,TFT_LCD_FILL_FULL, TFT_LCD_TYPE_CLR); //中间清除
//  			TFT_LCD_Draw_Box(0, CONTENT_Y[0], CONTENT_X, CONTENT_Y[CONTENT_TOTAL-1] + 24,TFT_LCD_FILL_FULL, TFT_LCD_TYPE_CLR); //箭头清除
			menuInfo.titleBackup = tempA;

		}
		else if(menuInfo.pageBackup != tempB)
		{
//			TFT_LCD_Draw_Box(0, CONTENT_Y[0], 239, CONTENT_Y[CONTENT_TOTAL-1] + 24,TFT_LCD_FILL_FULL, TFT_LCD_TYPE_CLR); //中间清除
//			TFT_LCD_Draw_Box(0, CONTENT_Y[0], CONTENT_X, CONTENT_Y[CONTENT_TOTAL-1] + 24,TFT_LCD_FILL_FULL, TFT_LCD_TYPE_CLR); //箭头清除
			menuInfo.pageBackup = tempB;
		}
		else
		{
//			TFT_LCD_Draw_Box(0, CONTENT_Y[0], CONTENT_X, CONTENT_Y[CONTENT_TOTAL-1] + 24,TFT_LCD_FILL_FULL, TFT_LCD_TYPE_CLR); //箭头清除
//			menuInfo.indexBackup = tempA;
		}


		if((Menu_Level_Tab[menuInfo.index].menuLevel1 == 0))		//指针指向的为标题项
		{
			if(Menu_Level_Tab[menuInfo.index].shwo != NULL)         //判断标题是否自有显示函数           
			{
				Menu_Level_Tab[menuInfo.index].shwo();
			}
			else if(Menu_Level_Tab[menuInfo.index].menuIndex != menuInfo.index)  //没有则指针指向子标题显示
			{
				menuInfo.index = Menu_Level_Tab[menuInfo.index].menuIndex;	
			}
		}
		else
		{
			tempA = Menu_GetTitle();     //返回标题
			tempB = (240 - (Menu_Level_Tab[tempA].stringImage)[0]) >> 1;	//确定标题所在X轴坐标
//			TFT_LCD_Draw_Bmp(NotCompress, Inverse, tempB, TITLE_Y, Menu_Level_Tab[tempA].stringImage);	//画标题

			if(Menu_Level_Tab[menuInfo.index].shwo != NULL)		//判断子标题是否自有显示函数
			{
				Menu_Level_Tab[menuInfo.index].shwo();
			}
			else												//没有则显示列表
			{
				page = Menu_GetCurrentPage();
 				if(page < (Menu_Level_Tab[menuInfo.index].menuTotal / CONTENT_TOTAL))
				{
					tempA = CONTENT_TOTAL;
				}
				else
				{
					tempA = Menu_Level_Tab[menuInfo.index].menuTotal % CONTENT_TOTAL;
				}
				tempB = page*CONTENT_TOTAL + Menu_GetFirstItem();
				for(i = 0, j = tempB; i < tempA ; i++, j++)
				{
//					TFT_LCD_Draw_Bmp(NotCompress, Inverse, CONTENT_X, CONTENT_Y[i], Menu_Level_Tab[j].stringImage);	//画子项文字
				}
//				TFT_LCD_Draw_Bmp(NotCompress, Inverse, 0, CONTENT_Y[Menu_GetCurrentItemLine()],sanjiaojiantou);
				
			}
		}
	}	
		
}



//返回当前标题（当前子项所属一级菜单 当当前菜单等级为标题（0）时，返回其本身）下标
uint16_t Menu_GetTitle(void)
{
	uint16_t i;
	uint16_t tempA;

	tempA = menuInfo.index;
	for(i = Menu_Level_Tab[menuInfo.index].menuLevel1; i>0 ; i--)
	{
		tempA = menuInfo.index + (Menu_Level_Tab[menuInfo.index].menuTotal - Menu_Level_Tab[menuInfo.index].menuItem);
		tempA = Menu_Level_Tab[tempA].menuIndex;
	}

	return tempA;
}

//返回当前子项所在当前菜单的页数（起始0页）
uint16_t Menu_GetCurrentPage(void)
{
	return (Menu_Level_Tab[menuInfo.index].menuItem / CONTENT_TOTAL);
}

//返回当前子项所在当前菜单的总页数（起始0页）
uint16_t Menu_GetTotalPage(void)
{
	return (Menu_Level_Tab[menuInfo.index].menuTotal / CONTENT_TOTAL + 1);
}

//返回当前菜单第一个子项下标
uint16_t Menu_GetFirstItem(void)
{
	return (menuInfo.index - Menu_Level_Tab[menuInfo.index].menuItem);
}

//返回当前菜单最后一位子项下标(不包含返回项)
uint16_t Menu_GetLastItem(void)
{
	return (menuInfo.index + (Menu_Level_Tab[menuInfo.index].menuTotal - Menu_Level_Tab[menuInfo.index].menuItem) - 1);
}

//返回当前子项所显示的行数（起始0行）
uint16_t Menu_GetCurrentItemLine(void)
{
	return (Menu_Level_Tab[menuInfo.index].menuItem % CONTENT_TOTAL);
}

//计算图片行居中显示所需的起始X坐标
uint16_t Menu_CalcPicCenteredDisplayX(uint8_t *  pic)
{
	return ((240 - pic[0]) >> 1);
}



//上按键按下后默认操作
void Menu_Up(void)
{
	if(menuInfo.index > Menu_GetFirstItem())
	{
		menuInfo.index --;
	}
}

//下按键按下后默认操作
void Menu_Down(void)
{
	if(menuInfo.index < Menu_GetLastItem())
	{
		menuInfo.index ++;
	}
}

//切换按键按下后默认操作
void Menu_SW(void)
{
	if(Menu_Level_Tab[menuInfo.index].menuLevel1 != 0)
	{
		menuInfo.index = Menu_GetTitle();
	}
	
	if(Menu_Level_Tab[menuInfo.index].menuItem < (Menu_Level_Tab[menuInfo.index].menuTotal - 1))
	{
		menuInfo.index ++;
	}
	else
	{
		menuInfo.index = 0;
	}
}

//返回上一级菜单
void Menu_Return(void)
{
	if(Menu_Level_Tab[menuInfo.index].menuLevel1 != 0)
	{
		menuInfo.index = Menu_GetLastItem() +1;
		menuInfo.index = Menu_Level_Tab[menuInfo.index].menuIndex;
	}
}

//指示灯一级菜单显示
void Menu_Show_LED(void)
{
	 

	menuInfo.refreshFlag = 1;

}

//报文外发一级菜单显示
void Menu_Show_SendOut(void)
{

	menuInfo.refreshFlag = 1;
}
//报警显示一级菜单显示
void Menu_Show_Warn(void)
{

	menuInfo.refreshFlag = 1;
}
//UE切换一级菜单显示
void Menu_Show_UESwitch(void)
{
	
	menuInfo.refreshFlag = 1;
}

//一级菜单指示灯-确定键按下后操作
void Menu_Set_LED	(void)
{
 
}
//一级菜单报文外发-确定键按下后操作
void Menu_Set_SendOut	(void)
{
	
}
//一级菜单报警-确定键按下后操作
void Menu_Set_Warn	(void)
{
 
}
//一级菜单UE切换-确定键按下后操作
void Menu_Set_UE	(void)
{
 
}
//二级菜单档位-确定键按下后操作
void Menu_Set_Gear	(void)
{
	 
}
//二级菜单时钟-确定键按下后操作
void Menu_Set_Clock	(void)
{
	 
}
//二级菜单室外温度-确定键按下后操作
void Menu_Set_Temperature	(void)
{
	 
}
//二级菜单功率表-确定键按下后操作
void Menu_Set_Power	(void)
{
	 
}
//二级车速表-确定键按下后操作
void Menu_Set_Vspeed	(void)
{
	 
}
//二级转速表-确定键按下后操作
void Menu_Set_Espeed	(void)
{
	 
}
//二级电量表-确定键按下后操作
void Menu_Set_Battery	(void)
{
	 

}
//二级燃油表-确定键按下后操作
void Menu_Set_Fuel	(void)
{

}
//二级水温表-确定键按下后操作
void Menu_Set_WaterTemperature	(void)
{

}
//二级里程表-确定键按下后操作
void Menu_Set_Mileage	(void)
{


}
//二级背光-确定键按下后操作
void Menu_Set_Backlight	(void)
{

}
//二级菜单语言切换-确定键按下后操作
void Menu_Set_LanguageSwitch	(void)
{

}
//二级菜单多媒体清零-确定键按下后操作
void Menu_Set_ClearMultimedia	(void)
{
	
}


/******************************************************************************
函数名：Menu_Processing_Service
功  能: 菜单处理服务,用于显示菜单及响应用户操作
参  数: 无
返回值：无
*******************************************************************************
注  意：该服务函数必须每100ms被调用一次
******************************************************************************/
void Menu_Processing_Service(void)
{
//	Game_Snake_processing();
	
	//理论上应该加UE界面判定 但现在就只有一个界面就不需要管理了...
	
	//文件管理器服务函数
//	FileManager_Service();
}


