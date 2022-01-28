#ifndef __MENU_H_
#define __MENU_H_
#include "stdint.h"


/***********************************************************************
菜单显示
***********************************************************************/

typedef void(* operation)(void);

//菜单信息指示器结构体
typedef struct
{
     uint16_t index; 
	 uint16_t indexBackup; 
	 uint8_t  refreshFlag;
	 uint16_t titleBackup;
	 uint16_t pageBackup;
} _Menu_Info;

//按键状态结构体
typedef struct
{
	uint8_t status;						//按键结果
	uint8_t statusBackup;				//结果备份
	uint8_t upKeyStatus;				//上键状态
	uint8_t downKeyStatus;				//下键状态
	uint8_t swKeyStatus;				//切换键状态
	uint8_t setKeyStatus;				//确认键状态
}_Menu_KeyVal;

//菜单结构结构体
typedef struct
{
	 uint8_t menuLevel1;				//菜单等级
	 uint8_t menuIndex;					//确定后到达
	 uint8_t menuLevel3;				//本级菜单第几个
	 uint8_t menuItem; 					//当前菜单第几个
	 uint8_t menuTotal;					//当前页面总数 
	 operation shwo;   					//自带显示函数（值为空时,使用默认结构显示）
	 operation upOperation;				//上键按下后操作函数
	 operation downOperation;			//下键按下后操作函数
	 operation switchOperation;			//切换键按下后操作函数
	 operation confirmOperation;		//确认键按下后操作函数
	 uint8_t *  stringImage;		//显示文字贴图
} _Menu_Attribute;

//图片信息结构体
typedef struct
{
  const int8_t* image;  
  uint16_t x;
  uint16_t y;
} _Image_Info;

//菜单显示用数据结构体
typedef struct
{
	int a;
}_Menu_Dat;



extern _Menu_Dat  menuDat;
extern _Menu_KeyVal menuKeyVal; 




#define MenuKeyINV	   0
#define MenuKeyUp      1
#define MenuKeyDown    2
#define MenuKeySW      3
#define MenuKeySet     4


void Menu_Initialization(void); 
void Menu_DataProcessing(void);
void Menu_Display_Service(void);
void Menu_KeyProcessing(void);
void Menu_AutoKey(void);

uint16_t Menu_GetTitle(void);
uint16_t Menu_GetCurrentPage(void);
uint16_t Menu_GetTotalPage(void);
uint16_t Menu_GetFirstItem(void);
uint16_t Menu_GetLastItem(void);
uint16_t Menu_GetCurrentItemLine(void);
uint16_t Menu_CalcPicCenteredDisplayX(uint8_t *  pic);



void Menu_Up(void);
void Menu_Down(void);
void Menu_SW(void);
void Menu_Return(void);


void Menu_Show_LED(void);
void Menu_Show_SendOut(void);
void Menu_Show_Warn(void);

void Menu_Set_LED	(void);
void Menu_Set_SendOut	(void);
void Menu_Set_Warn	(void);
void Menu_Set_Gear	(void);
void Menu_Set_Clock	(void);
void Menu_Set_Temperature	(void);
void Menu_Set_Power	(void);
void Menu_Set_Vspeed	(void);
void Menu_Set_Espeed	(void);
void Menu_Set_Battery	(void);
void Menu_Set_Fuel	(void);
void Menu_Set_WaterTemperature	(void);
void Menu_Set_Mileage	(void);
void Menu_Set_Backlight	(void);
void Menu_Set_LanguageSwitch	(void);
void Menu_Set_ClearMultimedia	(void);
void Menu_Set_MenuKey	(void);
void Menu_Set_OKKey	(void);
void Menu_Set_UpKey	(void);
void Menu_Set_DownKey	(void);
void Menu_Set_LeftKey   (void);
void Menu_Set_RightKey	(void);


    
      
      

 



void Menu_Processing_Service(void);

#endif

