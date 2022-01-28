#ifndef __GUI_H
#define __GUI_H			  	 

#include "include.h"
#include "GUI_Font.h"

#define TOTAL_X 128
#define TOTAL_Y 64
#define TOTAL_LIST 128/8
#define TOTAL_LINE 64
#define ARRAY_NUM (TOTAL_LIST*TOTAL_LINE)


void GUI_Init(void);
void GUI_Clear(void);
void GUI_Display(void);
//void OLED_Conversion(void);
//void OLED_Refresh_Gram(void);
void GUI_Fill_Rectangle(unsigned int startX,unsigned int startY,unsigned int endX,unsigned int endY,unsigned char colorMode);
void GUI_Draw_Number(unsigned char num, unsigned int x, unsigned int y); 
void GUI_Draw_String(eFontType fontType,char *s, unsigned int x, unsigned int y);
void GUI_Draw_Char(eFontType fontType ,char c, unsigned int x, unsigned int y);
void GUI_Draw_Digit_String(uint32_t str_num, unsigned int x, unsigned int y);
void GUI_Draw_Image(const unsigned char *p,unsigned int sta_x,unsigned int sta_y);
void GUI_Draw_Circle(unsigned int x,unsigned int y,unsigned int r,unsigned char color);
void GUI_Draw_Point(unsigned int x,unsigned int y,unsigned char color);
void GUI_Draw_line(unsigned int sta_x,unsigned int sta_y,unsigned int end_x,unsigned int end_y,unsigned char color);
void GUI_Draw_Box(unsigned int sta_x,unsigned int sta_y,unsigned int end_x,unsigned int end_y,unsigned char colorMode);

extern unsigned char GUI_dat[ARRAY_NUM];




#endif
