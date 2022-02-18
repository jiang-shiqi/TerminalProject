#ifndef __DATA_SERVICE_H_
#define __DATA_SERVICE_H_

#include "include.h"
#include "ESP8266_AT.h"
//
#define SNAKE_MAX_LIGHT 50

//贪吃蛇游戏属性
typedef struct 
{
	const uint8_t  multiple;    //单个点所占像素倍率
	const uint8_t  speedUp;     //按下加速按键时 速度提升到值
	const uint16_t W;           //地图宽能容纳最大点数
	const uint16_t H;           //地图高能容纳最大点数 
}Data_Game_Snake_st;
 
//蛇属性
typedef struct
{
	uint16_t x[SNAKE_MAX_LIGHT];   //蛇身数组坐标X (下标0为蛇头)
	uint16_t y[SNAKE_MAX_LIGHT];   //Y
	uint8_t  light;                //长度
	uint8_t  dir;                  //当前方向
	uint8_t  speed;                //当前速度
	uint16_t delay;                //下次行动延时 
}Data_Game_SnakeAttr_st;

//食物属性
typedef struct
{
	uint16_t x;                    //食物坐标X
	uint16_t y;                    //Y
	uint8_t  status;               //状态(是否被吃掉)
}Data_Game_SnakeFood_st;

//Data_Service服务函数调用间隔
#define DATA_SERVICE_CYCLE  1000


#define DATA_NET_RXTIMEOUT_MAX 100
#define DATA_NET_KEYLENTH_MAX 30
#define DATA_NET_VALLENTH_MAX 30

#define DATA_SMARTFLOWERPOT_SENDHUMIDITYTIME_MAX 500
#define DATA_SMARTFLOWERPOT_SENDHUMIDITYTIMEOUT_MAX 300




//网络协议结构体
typedef struct
{
	uint16_t protocolVersion;       //协议版本  
	uint16_t keyLenth;              //键长度
	char key[DATA_NET_KEYLENTH_MAX];//键
	uint16_t valType;               //值类型
	uint16_t valLenth;              //值长度
	char val[DATA_NET_VALLENTH_MAX];//值
}Data_Net_Data_st;

//网络发送键结构体
typedef struct
{
	uint16_t num;
	const char *sendKey;
	const uint16_t sendKeyLenth;

}Data_Net_SendString_st;

typedef enum Data_Net_Key_en_t{
	DataNet_projectName,
	DataNet_Time,
	DataNet_Watering,
	DataNet_Humidity,
	DataNet_CriticalHumidity,
	DataNet_Character,
	DataNet_sentry,
}en_Data_Net_Key;

typedef enum Data_Net_ValType_en_t{
	DataNet_TYPE_NULL,
	DataNet_TYPE_Byte,
	DataNet_TYPE_Short,
	DataNet_TYPE_Int,
	DataNet_TYPE_Long,
	DataNet_TYPE_Float,
	DataNet_TYPE_Double,
	DataNet_TYPE_Boolean,
	DataNet_TYPE_Char,
	DataNet_TYPE_Bytelist,
	DataNet_TYPE_String,
	DataNet_TYPE_Object,
	DataNet_TYPE_File,
	DataNet_TYPE_sentry,
}en_Net_ValType;



void Data_Service(void);
void Graphics_Display(void);


//游戏贪吃蛇
void Game_Snake_Init(void);
void Game_Snake_processing(void);
void Game_Snake_NextStep(void);
void Game_Snake_CollisionCheck(void);
void Game_Snake_EatFoodCheck(void);
void Game_Snake_AttrCheckout(void);
void Game_Snake_GameOver(void);

//绘图
void Game_Snake_Graphics(void);
void Game_Snake_Backdrop(void);
void Game_Snake_DrawAttr(void);
void Game_Snake_DrawSnake(void); 
void Game_Snake_DrawFood(void); 



#endif
