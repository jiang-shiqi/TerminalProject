#ifndef __KEY_H
#define __KEY_H
#include "stdint.h"
#include "Line_In.h"

#define KEY_TOTAL 7
 
/*** 按键属性结构 ***/
typedef struct
{
//  volatile  uint8_t   *pInputSignal;    //输入信号
            uint8_t   HoldDetMode;      //长按检测模式
            uint8_t   DoubleDetEn;      //连按检测使能
}KeyAttrStruct;

/*** 长按检测模式 ***/
#define   KEY_HOLD_DISABLE                  0x00      //不支持按住检测
#define   KEY_HOLD_ONLY                     0x01      //仅支持按住检测
#define   KEY_LONG_ONLY                     0x02      //仅支持长按检测
#define   KEY_STUCK_ONLY                    0x04      //仅支持卡住检测
#define   KEY_HOLD_LONG                     0x03      //支持按住/长按检测
#define   KEY_HOLD_STUCK                    0x05      //支持按住/卡住检测
#define   KEY_LONG_STUCK                    0x06      //支持长按/卡住检测
#define   KEY_HOLD_LONG_STUCK               0x07      //支持按住/长按/卡住检测

/*** 按键属性列表 ***/
extern const KeyAttrStruct KeyAttrTable[KEY_TOTAL];


/******************************************************************************
按键检测配置
******************************************************************************/
#define   KEY_DOUBLE_INTERVAL               200       //连按（双击）最长间隔
#define   KEY_HOLD_THRESHOLD                800       //按住判定时间阈值
#define   KEY_LONG_THRESHOLD                5000      //长按判定时间阈值
#define   KEY_STUCK_THRESHOLD               15000     //按键卡住判定时间阈值
#define   KEY_TOTAL_NUMBER                  (sizeof(KeyAttrTable) / sizeof(KeyAttrStruct))

/******************************************************************************
按键状态枚举
******************************************************************************/
typedef enum
{
  KEY_IDLE = 0,   //空闲 按键未按下
  KEY_PRESS,      //按键短按
  KEY_HOLD,       //按键按住
  KEY_LONG,       //按键长按
  KEY_STUCK,      //按键卡住
  KEY_DOUBLE,     //按键连续按下两次（双击）  
}KeyStatusEnum;
 
/******************************************************************************
按键状态检测结构
******************************************************************************/
typedef struct
{
  uint8_t         UpdateEnable;               //更新标志位
  uint16_t        Timer;                      //按下时间
  uint16_t        IdleTimer;                  //空闲时间
  KeyStatusEnum   FinalStatus;                //上次状态
  KeyStatusEnum   CurrentStatus;              //当前状态
}KeyDetectStruct;

extern KeyDetectStruct keyDetectStruct[KEY_TOTAL_NUMBER];

/******************************************************************************
按键结构
******************************************************************************/

/******************************************************************************
函数声明
******************************************************************************/
void KEY_init(void);
void KEY_Service(void);



#endif
