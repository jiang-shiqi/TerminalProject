#include "Data_Service.h"
//#include "GUI.h" 
//#include "GUI_App.h"
#include "Rocker.h"
#include "Line_In.h"
//#include "Files.h"
#include "SPI.h" 
#include "lcd.h"
#include "ESP32.h"

//显示图像绘制
//20ms
void Graphics_Display(void)
{ 
//    u8 i;
//		GUI_Clear();
	//摇杆绘制
//		Graphics_YG_Test(YGVal[0].rockerVal[0].val,YGVal[0].rockerVal[1].val);
  //贪吃蛇游戏图像绘制
//	Game_Snake_Graphics();
	
	//字符串绘制测试
//	GUI_Draw_String(F1206,"123ABC+-*/ ",0,0);

//	//文件系统菜单测试
//	displaynum = 5;
//	for(i=0;i<displaynum;i++)
//	{
//	    GUI_Draw_String(F1206,displayBuffer[i],0,i*12);//
//	}
	
	//文件管理器
//	Graphics_FileManager();
	
	//ESP8266 测试
//	//wifi连接功能显示
//	LCD_Clear(WHITE);
//	POINT_COLOR= BLACK;
//	
//	//连接状态
//	LCD_ShowString(30, 40,160,16,16,(uint8_t *)"Connection status: ");
//	LCD_ShowChar(190,40,ESP_Device[0].connectStatus+'0',16,0);
//	
	//WiFi信息
	LCD_ShowString(10, 60,100,16,16,(uint8_t *)"SSID: ");
	LCD_ShowString(30, 80,210,16,16,(uint8_t *)ESP32_Drive.WifiAttr.ssid);
	LCD_ShowString(10,100,100,16,16,(uint8_t *)"PSWD: ");
	LCD_ShowString(30,120,210,16,16,(uint8_t *)ESP32_Drive.WifiAttr.pswd);
	 
}

	char SPI1_buf[50];
//数据处理函数
void Data_Service(void)
{
//	Data_Net_processing();
//	LCD_ShowString(30,170,200,16,16,"Count:");
	
//		ESP_CS = 0;		    
//		SPI1_buf[0] = SPI_ReadWriteByte(SPI1, 0x90);//发送读取ID命令	    
//		SPI1_buf[1] = SPI_ReadWriteByte(SPI1, 1); 	    
//		SPI1_buf[2] = SPI_ReadWriteByte(SPI1, 2); 	    
//		SPI1_buf[3] = SPI_ReadWriteByte(SPI1, 3); 	 		
//		ESP_CS = 1;	
	
//	ESP32_TransmitData("111111111111111111111",SPI1_buf,20);
	
//	ESP32_Service();
}



 //游戏：贪吃蛇 
Data_Game_Snake_st     GameSnake = { 4, 1, 23, 15};
Data_Game_SnakeFood_st Food0     = { 5, 5, 0}; 
Data_Game_SnakeAttr_st Snake0;

//贪吃蛇初始化
void Game_Snake_Init(void)
{
	Food0.status = 0;
	Food0.x      = 5;
	Food0.y      = 5;
	Snake0.x[0]  = 3;
	Snake0.x[1]  = 2;
	Snake0.x[2]  = 1;
	Snake0.y[0]  = 2;
	Snake0.y[1]  = 2;
	Snake0.y[2]  = 2;
	Snake0.light = 3;
	Snake0.dir   = 3;
	Snake0.speed = 4;
	Snake0.delay = 10;
}																
																		
//贪吃蛇游戏 处理函数
void Game_Snake_processing(void)
{
 
	//下一步
	Game_Snake_NextStep(); 					
  //判断撞线
	Game_Snake_CollisionCheck();
	//吃食物
	Game_Snake_EatFoodCheck();
	//属性结算
	Game_Snake_AttrCheckout();
	
																				
		 
}

//绘制图层
void Game_Snake_Graphics(void)
{
	//背景贴图
	Game_Snake_Backdrop();
	//画属性栏
	Game_Snake_DrawAttr();
	//画蛇本体
	Game_Snake_DrawSnake();
	//画食物
	Game_Snake_DrawFood();
}

//背景
void Game_Snake_Backdrop(void)
{ 
//	//左竖线
//  GUI_Draw_line(   0,   0,   0,  63, 1);
//	GUI_Draw_line(   1,   0,   1,  63, 1);																			
//	GUI_Draw_line(   3,   0,   3,  63, 1);
//	//右竖线																			
//	GUI_Draw_line( 127,   0, 127,  63, 1);
//	GUI_Draw_line( 126,   0, 126,  63, 1);																			
//	GUI_Draw_line( 124,   0, 124,  63, 1);
//	//上横线																			
//	GUI_Draw_line(   0,   0, 127,   0, 1);
//	GUI_Draw_line(   0,   1, 127,   1, 1);
//	GUI_Draw_line(   0,   3, 127,   3, 1);
//	//下横线																			
//	GUI_Draw_line(   0,  63, 127,  63, 1);
//	GUI_Draw_line(   0,  62, 127,  62, 1);
//	GUI_Draw_line(   0,  60, 127,  60, 1);
//	
//	//中竖线
//  GUI_Draw_line(  93,   0,  93,  63, 1);
//	GUI_Draw_line(  95,   0,  95,  63, 1);																			
//	GUI_Draw_line(  96,   0,  96,  63, 1);																	
//	GUI_Draw_line(  98,   0,  98,  63, 1);
}
  
//画属性栏
void Game_Snake_DrawAttr(void)
{

}

//画蛇
void Game_Snake_DrawSnake(void)
{
//	u16 i;
//	
//	for(i=0;i<Snake0.light;i++)
//	{
//		GUI_Draw_Box((Snake0.x[i]) * GameSnake.multiple, \
//		             (Snake0.y[i]) * GameSnake.multiple, \
//		             (Snake0.x[i]+1) * GameSnake.multiple - 1, \
//		             (Snake0.y[i]+1) * GameSnake.multiple - 1, \
//		             FILL);
//	}
}

//画食物
void Game_Snake_DrawFood(void)
{
//	GUI_Fill_Rectangle((Food0.x) * GameSnake.multiple, \
//	                   (Food0.y) * GameSnake.multiple, \
//	                   (Food0.x+1) * GameSnake.multiple - 1, \
//	                   (Food0.y+1) * GameSnake.multiple - 1, \
//	                   FILL); 
}

//下一步
void Game_Snake_NextStep(void)
{ 
	u16 i,speedUpFlag=0;
	
	if((speedUpFlag == 0)&&(lineInDeb[KEY_1].Status == DEB_VALID))
	{
		Snake0.delay = 0;
		speedUpFlag  = 1;
	}
	else if(lineInDeb[KEY_1].Status != DEB_VALID)
	{
		speedUpFlag  = 0;
	}
	//定时判断
	if(Snake0.delay == 0)
	{
		if(lineInDeb[KEY_1].Status == DEB_VALID)
		{
			Snake0.delay = GameSnake.speedUp;
		}
		else
		{
			Snake0.delay = Snake0.speed;
		}
	}
	else
	{ 
	  Snake0.delay--;
		return;
	}
	
	//判断下一步方向
	switch(Snake0.dir)
	{
		case 1:
			if(YGVal[0].dir&0x08) 
				Snake0.dir = 4; 
			if(YGVal[0].dir&0x04)
				Snake0.dir = 3;  
			break;	
		
		case 2:
			if(YGVal[0].dir&0x08) 
				Snake0.dir = 4; 
			if(YGVal[0].dir&0x04)
				Snake0.dir = 3;  
			break;

		case 3:
			if(YGVal[0].dir&0x01) 
				Snake0.dir = 1; 
			if(YGVal[0].dir&0x02)
				Snake0.dir = 2;  
			break;

		case 4:
			if(YGVal[0].dir&0x01) 
				Snake0.dir = 1; 
			if(YGVal[0].dir&0x02)
				Snake0.dir = 2;  
			break; 
	  default:
			return;
	}
	 
	//走格
	for(i = Snake0.light; i > 0; i--)
	{
		Snake0.x[i] = Snake0.x[i-1];
		Snake0.y[i] = Snake0.y[i-1];
	}
	switch(Snake0.dir)
	{
		case 1: 
		  Snake0.y[0] = Snake0.y[0]-1;
			break;
		
		case 2: 
		  Snake0.y[0] = Snake0.y[0]+1;
			break;
		
		case 3:
			Snake0.x[0] = Snake0.x[0]-1; 
			break;
		
		case 4:
			Snake0.x[0] = Snake0.x[0]+1; 
			break; 
	}
	
	 
}
//判断撞线
void Game_Snake_CollisionCheck(void)
{
	u16 i;
	//头部是否越界 
	if((Snake0.x[0] >= GameSnake.W)||  \
	   (Snake0.y[0] >= GameSnake.H)||  \
	   (Snake0.x[0] == 0)          ||  \
	   (Snake0.y[0] == 0))
	{
	  Game_Snake_GameOver();
		return;
	}
	//头部是否与蛇身重合 
	for(i=4;i<Snake0.light;i++)
	{
		if((Snake0.x[0] == Snake0.x[i])&&   \
	     (Snake0.y[0] == Snake0.y[i]))
		{
			Game_Snake_GameOver();
	  	return;
		}
	}
	//头部是否与障碍重合(预留) 
}

//吃食物
void Game_Snake_EatFoodCheck(void)
{
	u32 random;
	u16 i;
	
	//头部是否与食物坐标重合
	if((Snake0.x[0] == Food0.x)&&   \
	   (Snake0.y[0] == Food0.y))
	{
		//更改食物状态
		Food0.status = 1;
	  //增加长度 并限制最大长度
		if(Snake0.light < SNAKE_MAX_LIGHT-1)
		{ 
			//注意增加蛇身最后一格预留坐标
			Snake0.x[Snake0.light] = Snake0.x[Snake0.light - 1];
			Snake0.y[Snake0.light] = Snake0.y[Snake0.light - 1];
			
			Snake0.light++;
		} 
		//生成食物 
		if(Food0.status == 1)
		{
			Food0.status = 0;
			
			//随机生成(取各种值做伪随机数)
			while(1)
			{
				random = *(YGVal[0].rockerVal[0].currentVal) + \
								 *(YGVal[0].rockerVal[1].currentVal) + \
								 SysTick->VAL;
				Food0.x = (random + 1234) % GameSnake.W; 
				Food0.y = (random - 1234) % GameSnake.H;
				if(Food0.x == 0)
					Food0.x++;
				if(Food0.y == 0)
					Food0.y++;
				
				//注意不能与蛇身重合 
				for(i=0;i<Snake0.light;i++)
				{
				  if((Food0.x == Snake0.x[i]) && (Food0.y == Snake0.y[i]))
						break;
				}
				
				//如果有重合就重新生成
				if(i == Snake0.light)
					break;
			}
		}
	}
}

//属性结算
void Game_Snake_AttrCheckout(void)
{

}

//游戏结束
void Game_Snake_GameOver(void)
{
	Game_Snake_Init();
}

 























