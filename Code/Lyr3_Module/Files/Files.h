#ifndef __FILES_H_
#define __FILES_H_
 
#include "ff.h"			/* Obtains integer types */
#include "stm32f10x.h" 
#include "core_cm3.h"
#include "string.h"
#include "GUI_App.h"

#define ONE_BLOCK       512 
#define TWO_BLOCK      1024   

//文件显示行数与单行字符个数
#define DISFILELINE_MAX 30
#define DISFILECHAR_MAX 18

//文件类型
typedef enum 
{
	FOLDER,					//文件夹
	DOCUMENT,				//文档
	IMAGE,                  //图像
	AUDIO,					//音频
	VIDEO,					//影音
	DAT,					//数据
	UNKNOWN,				//未知
}FileType_e;

//文件管理器按键状态
typedef enum 
{ 
	None,			//无
	Up,				//向上
	Down,			//向下
	Enter,		//进入
	Back,			//退出 
}FileManagerKeyStatus_e;

//文件显示属性
typedef struct
{
	FileType_e type;
	char name[DISFILECHAR_MAX];
}FileAttr_st;

//文件显示列
typedef struct
{ 
    u32 currentSite;                            //指针相对于列表位置
    u8 poi;                                     //指针相对于显示框位置
    u8 lvevl;                                   //文件层级
	FileAttr_st attr[DISFILELINE_MAX];          //文件项属性
	unsigned int num;                           //文件项总数
}FileManagerList_st;


extern          FileManagerList_st fileManagerList;


FRESULT EnterFolder(FileManagerList_st *fileManagerList, char *path);
FRESULT BackFolder(FileManagerList_st *fileManagerList, char *path);
FRESULT BackonePath(char *path);
FRESULT ScanCurrentDirectory( FileManagerList_st *fileManagerList, char *path);

void FileManager_Init(void);
void FileManager_Service(void); 
 
#endif


