#ifndef __LINE_IN_H_
#define __LINE_IN_H_ 
#include "GPIO.h"

/*** 按键ID列表 ***/
typedef enum { 
	KEY_0             = 0,  
	KEY_1             ,  
	KEY_2             ,  
	KEY_3             ,  
	KEY_ROLLER_LEFT   ,  
	KEY_ROLLER_RIGHT  ,  
	KEY_ROLLER_DOWN   ,  
}KeyIDEnum; 

/*** 按键消抖状态 ***/
typedef enum {
  DEB_NOT           = 0,				//无效
	DEB_DEBOUNCE_0,               //消抖
	DEB_VALID,                    //有效
	DEB_DEBOUNCE_1,
}KeyDebounceStatus; 
 
#define   LINE_IN_DEBOUNCE_CYCLE            20    //消抖时间 单位ms

//输入消抖
typedef struct
{
    uint8_t   Current; 
	  uint8_t   Status;
    uint16_t  Timer;
	  uint16_t  BackupTimer; 
} LineInDebStruct;

//引脚属性结构体
typedef struct
{
//uint8_t KeyID;        //索引  
volatile	uint8_t *pCup;
	uint8_t Type;         //类型
	uint8_t Valid;        //有效值
	uint8_t Default;      //默认值
}LineInDebAttr;

//类型列表
#define AD_KEY 0
#define IO_KEY 1

//引脚总数
#define LINEIN_TOTAL 7

//全局声明
extern uint8_t KeyCup[LINEIN_TOTAL];
extern LineInDebStruct lineInDeb[LINEIN_TOTAL];

//引脚属性列表
extern const LineInDebAttr lineInDebAttr[LINEIN_TOTAL]; 
 
//函数声明
void LineIn_Init(void);
void LineIn_Debounce_Service(void);
void LineIn_Debounce(uint8_t keyID);
void LineIn_RefreshKeyVal(void);



#endif
