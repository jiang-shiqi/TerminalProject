#ifndef __GUI_FONT_H
#define __GUI_FONT_H			
#include "include.h"

typedef enum 
{
	CLEAR = 0,						//清除
	FILL,                 //填充
	XOR,                  //反选
}eFillStyle;

typedef enum 
{
	F1014,
	F1206,
	F1608,
}eFontType;


extern const unsigned char Font_1014[10][10];
extern const unsigned char Font_1206[95][12];
extern const unsigned char Font_1608[95][16];

extern const unsigned char gImage_zhuye[];
extern const unsigned char gImage_fanhui[];
extern const unsigned char gImage_wenjianjia[];
extern const unsigned char gImage_wenjian[];
extern const unsigned char gImage_tuxiang[];
extern const unsigned char gImage_weizhi[];
extern const unsigned char gImage_yinpin[];
extern const unsigned char gImage_yingyin[];
extern const unsigned char gImage_shuju[];




#endif
