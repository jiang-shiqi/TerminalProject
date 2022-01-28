#include "GUI.h"
#include "oled_ssd1306.h"
#include "GUI_App.h"
#include "key.h"



void GUI_Test(void)
{
	GUI_Display();
}
 

//摇杆测试
void Graphics_YG_Test(uint8_t x,uint8_t y)
{
	GUI_Draw_line( 7, 7,57, 7,FILL);
	GUI_Draw_line( 7,32,57,32,FILL);
	GUI_Draw_line( 7,57,57,57,FILL);
	
	GUI_Draw_line( 7, 7, 7,57,FILL);
	GUI_Draw_line(32, 7,32,57,FILL);
	GUI_Draw_line(57, 7,57,57,FILL);
	
	GUI_Draw_Circle((x>>1)+7,(y>>1)+7,6,FILL);
	if(keyDetectStruct[YG_DOWN].CurrentStatus == KEY_PRESS )
	{ 
		GUI_Draw_Point((x>>1)+7,(y>>1)+7,FILL);
	}
	if(keyDetectStruct[YG_DOWN].CurrentStatus == KEY_HOLD )
	{
		GUI_Draw_Point((x>>1)+7,(y>>1)+7,FILL);
		GUI_Draw_Circle((x>>1)+7,(y>>1)+7,2,FILL);
	}
	if(keyDetectStruct[YG_DOWN].CurrentStatus == KEY_LONG )
	{
		GUI_Draw_Point((x>>1)+7,(y>>1)+7,FILL);
		GUI_Draw_Circle((x>>1)+7,(y>>1)+7,2,FILL);
		GUI_Draw_Circle((x>>1)+7,(y>>1)+7,4,FILL);
	}
}

//按键测试



FileManagerDisplay_st FileManagerDisplay = 
{
	0,
	0,
	0,
	0,
	0,
	" ",
	" ",
	" ",
	" ",
	" ",
	0,
	0,
};
FileManagerDisplay_st FileManagerDisplayBackup;
const unsigned char* icon[] = {gImage_wenjianjia,gImage_wenjian,gImage_tuxiang,gImage_yinpin,gImage_yingyin,gImage_shuju,gImage_weizhi};


//文件管理器
void Graphics_FileManager_Init(void)
{
	GUI_Draw_Box( FM_LINE_X,   FM_LINE_Y, TOTAL_X-1, FM_LINE_Y+1 ,FILL);			//横线 
	GUI_Draw_Image(gImage_zhuye, FM_ZHUYE_X, FM_ZHUYE_Y);                     //主页图标
	GUI_Draw_Image(gImage_fanhui, FM_FANHUI_X, FM_FANHUI_Y);                  //返回图标
	
//	GUI_Draw_Box(         0, FM_LINE02_Y,         1, FM_LINE02_Y+12 ,FILL); //竖线
//	GUI_Draw_Image(gImage_wenjianjia, FM_ICON_X, FM_LINE01_Y);              //行一文件夹图标
//	GUI_Draw_Image(gImage_wenjianjia, FM_ICON_X, FM_LINE02_Y);              //行二文件夹图标
//	GUI_Draw_Image(gImage_wenjian,    FM_ICON_X, FM_LINE03_Y);              //行三文件图标
//	GUI_Draw_Image(gImage_wenjian,    FM_ICON_X, FM_LINE04_Y);              //行四文件图标
//	
//	GUI_Draw_String(F1206, "0:\\...", 15, 0);
//	GUI_Draw_String(F1206, "001", 15, FM_LINE01_Y);
//	GUI_Draw_String(F1206, "002", 15, FM_LINE02_Y);
//	GUI_Draw_String(F1206, "01.txt", 15, FM_LINE03_Y);
//	GUI_Draw_String(F1206, "02.txt", 15, FM_LINE04_Y);
}

void Graphics_FileManager(void)
{
	Graphics_FileManager_Init();
	
	//路径显示
	GUI_Draw_String(F1206, FileManagerDisplay.path, FM_ZHUYE_X+13, FM_ZHUYE_Y);
	//选择竖线显示
	switch(FileManagerDisplay.poi)
	{
		case 1:
			GUI_Draw_Box(  0, FM_ZHUYE_Y, 1, FM_ZHUYE_Y+12 ,FILL); //主页
			break;
		case 2:
			GUI_Draw_Box(  FM_FANHUI_X-2, FM_FANHUI_Y, FM_FANHUI_X-1, FM_FANHUI_Y+12 ,FILL); //返回
			break;
		case 3:
			GUI_Draw_Box(  0, FM_LINE01_Y, 1, FM_LINE01_Y+12 ,FILL); //行一
			break;
		case 4:
			GUI_Draw_Box(  0, FM_LINE02_Y, 1, FM_LINE02_Y+12 ,FILL); //行二
			break;
		case 5:
			GUI_Draw_Box(  0, FM_LINE03_Y, 1, FM_LINE03_Y+12 ,FILL); //行三
			break;
		case 6:
			GUI_Draw_Box(  0, FM_LINE04_Y, 1, FM_LINE04_Y+12 ,FILL); //行四
			break;
		default:
			break;
	}
	//行一显示
	if(FileManagerDisplay.icon01 != 0xff){
		GUI_Draw_Image(icon[FileManagerDisplay.icon01], FM_ICON_X, FM_LINE01_Y); 
		GUI_Draw_String(F1206, FileManagerDisplay.line01, FM_ICON_X+13, FM_LINE01_Y);
	}
	//行二显示
	if(FileManagerDisplay.icon02 != 0xff){
		GUI_Draw_Image(icon[FileManagerDisplay.icon02], FM_ICON_X, FM_LINE02_Y); 
		GUI_Draw_String(F1206, FileManagerDisplay.line02, FM_ICON_X+13, FM_LINE02_Y);
	}
	//行三显示
	if(FileManagerDisplay.icon03 != 0xff){
		GUI_Draw_Image(icon[FileManagerDisplay.icon03], FM_ICON_X, FM_LINE03_Y); 
		GUI_Draw_String(F1206, FileManagerDisplay.line03, FM_ICON_X+13, FM_LINE03_Y);
	}
	//行四显示
	if(FileManagerDisplay.icon04 != 0xff){
		GUI_Draw_Image(icon[FileManagerDisplay.icon04], FM_ICON_X, FM_LINE04_Y); 
		GUI_Draw_String(F1206, FileManagerDisplay.line04, FM_ICON_X+13, FM_LINE04_Y);
	}
	//进度条
	if((FileManagerDisplay.progressBarUp>FileManagerDisplay.progressBarDown)||(FileManagerDisplay.progressBarUp>100)||(FileManagerDisplay.progressBarUp>100))
	{
		FileManagerDisplay.progressBarUp = 0;
		FileManagerDisplay.progressBarDown = 0;
	}
	GUI_Draw_Box( FM_PRO_X, FM_PROMIN_Y + (FileManagerDisplay.progressBarUp>>1), FM_PRO_X+2, FM_PROMIN_Y + (FileManagerDisplay.progressBarDown>>1), FILL);	 
	GUI_Draw_line(  FM_PRO_X, FM_PROMAX_Y, FM_PRO_X+2, FM_PROMAX_Y, FILL);	
}





























