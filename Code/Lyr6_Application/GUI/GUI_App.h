#ifndef __GUI_APP_H_
#define __GUI_APP_H_

#include "stdint.h"
#include "GUI_Font.h"

//贴图位置结构体
typedef struct
{ 
	const unsigned char *bmp;
  uint16_t x;
  uint16_t y;
} bmpSite_t;

//文件管理器显示
typedef struct 
{
	unsigned char poi;
	unsigned char icon01;
	unsigned char icon02;
	unsigned char icon03;
	unsigned char icon04;
	char path[16];
	char line01[18];
	char line02[18];
	char line03[18];
	char line04[18]; 
	unsigned char progressBarUp;
	unsigned char progressBarDown;
}FileManagerDisplay_st;

//typedef struct
//{
//  uint16_t x;
//  uint16_t y;
//} bmpsSite_t;

//文件管理器
//const bmpSite_t FileManagerSite[] =
//{
//	{   2,   1,},	//主页
//	{ 116,   1,}, //返回
//	{   0,  13,}, //横线 
//	{   2,  15,}, //行一图标
//	{   2,  26,}, //行二图标
//	{   2,  37,}, //行三图标
//	{   2,  49,}, //行四图标
//};

#define FM_ZHUYE_X       2
#define FM_ZHUYE_Y       1
#define FM_FANHUI_X    116
#define FM_FANHUI_Y      1
#define FM_LINE_X        0
#define FM_LINE_Y       13
#define FM_ICON_X        2
#define FM_LINE01_Y     15
#define FM_LINE02_Y     27
#define FM_LINE03_Y     39
#define FM_LINE04_Y     51
#define FM_PROMIN_Y     14
#define FM_PROMAX_Y     63
#define FM_PRO_X       124


extern FileManagerDisplay_st FileManagerDisplay;

void GUI_Test(void);
void Graphics_YG_Test(uint8_t x,uint8_t y);

void Graphics_FileManager_Init(void);
void Graphics_FileManager(void);

#endif
