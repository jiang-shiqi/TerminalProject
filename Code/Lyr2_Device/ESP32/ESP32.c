#include "ESP32.h"     
#include "GPIO.h"
#include "SPI.h"
#include "Delay.h"
#include "Toolkit.h"


uint8_t  ESP32_ConnectionFlag;
uint8_t  ESP32_ConnectionStatus;

uint8_t  ESP32_Wait_Flag;		//等待状态
uint8_t  ESP32_Ready_Flag;		//ESP32返回的就绪状态
uint8_t  ESP32_Ready_Flag;		//ESP32返回的待发送状态

char ReceiveNetDatBuf[1024];
uint16_t ReceiveNetDatLenth;

struct ESP32_Class_st_t ESP32_Drive;

//RSP32初始化
void ESP32_Init(void)
{
    ESP32_Drive.initStatus = false;                      //初始化状态
	ESP32_Drive.driveID = 0x0000;                        //设备ID
	ESP32_Drive.connectStatus = ESPStatus_NoResponse;    //连接状态 
	ESP32_Drive.infoDisplay = ESPInfo_NoResponse;        //信息显示
	ESP32_Drive.connectionReady = false;                 //连接就绪
	ESP32_Drive.requestManualAction = false;             //需手动确认标志位
	ESP32_Drive.setAttr.serverAutoConnectEnable = true;  //可设置属性  
    ESP32_Drive.setAttr.wifiAutoConnectEnable = true;
	ESP32_Drive.timeout = 0;                             //超时等待时间
	ESP32_Drive.errorNum = 0;                            //错误计数器
	// ESP32_Drive.netSendoutData; //待发送的网络数据
	// ESP32_Drive.netReceivedData;//接收到的网络数据
	// ESP32_Drive.WifiAttr;                                //WiFi属性
	// ESP32_Drive.serverAttr;                              //服务器属性
	// ESP32_Drive.stnpTime;                                //STNP时间
	//函数指针初始化
	// ESP32_Drive.connectWifi = connectWifi;               //连接WiFi
	// ESP32_Drive.disconnectWifi = disconnectWifi;         //断开WiFi
	// ESP32_Drive.connectServer = connectServer;           //连接服务器
	// ESP32_Drive.disconnectServer = disconnectServer;     //断开服务器
	// ESP32_Drive.netSendOutFun = netSendOutFun;           //发送网络数据
	// ESP32_Drive.netReceivedFun = netReceivedFun;         //接收网络数据
	// ESP32_Drive.selectSNTPTime = selectSNTPTime;         //查询SNTP时间
}

void ESP32_Service(void)
{
	uint8_t  resU8;
	uint16_t resU16;
	uint32_t resU32; 
	int8_t   res8;
	int16_t  res16;
	int32_t  res32; 

	//判断设备ID
	if(ESP32_Drive.driveID != ESP32_DRIVE_ID)
	{
		ESP32_Drive.driveID = ESP32_ReadDeviceID();
	}

	//状态检测 
	res16 = ESP32_SelectStatus();
	
	//检测 ESP32连接状态错误 || 设备号不正确
	if((!IS_Esp32_ConnectStatusType(res16))||(ESP32_Drive.driveID != ESP32_DRIVE_ID))
	{
		//ESP32连接状态错误 || 设备号不正确 处理
		ESP32_Drive.infoDisplay = ESPInfo_NoResponse;
		ESP32_Drive.connectStatus = ESPStatus_NoResponse;
		ESP32_Drive.connectionReady = false;
		return ;
	}

	//状态赋值
	ESP32_Drive.connectStatus = res16;

	//判断下载是否为需手动操作
	if(ESP32_Drive.requestManualAction == true)
	{
		ESP32_Drive.connectionReady = false;
		return ;
	}

	//如果已经就绪 就跳过本服务函数 
	if(ESP32_Drive.connectionReady == true)
	{
		ESP32_Drive.infoDisplay = ESPInfo_ServerConnectSucceeded;
		return ;
	}


	//状态处理
	switch(ESP32_Drive.connectStatus)
	{
		case ESPStatus_NoWifi:          //未连接到WiFi
			//是否直接连接WiFi
			if(ESP32_Drive.setAttr.wifiAutoConnectEnable == false)
			{
				ESP32_Drive.infoDisplay = ESPInfo_WiFiWaitConnect;
				ESP32_Drive.requestManualAction = true;
				return ;
			}
			//wifi属性是否准备好
			if(ESP32_Drive.WifiAttr.ready_Flag == false)
			{
				ESP32_Drive.infoDisplay = ESPInfo_WifiAttrError;
				ESP32_Drive.requestManualAction = true;
				return ;
			}

			ESP32_Drive.infoDisplay = ESPInfo_WifiConnecting;
			res16 = connectWifi( &ESP32_Drive );
			while(res16 != 0); 	//陷阱函数
			break;

		case ESPStatus_WifiConnecting:    //WiFi连接中       
			ESP32_Drive.timeout ++;
			if(ESP32_Drive.timeout < ESP32_TIMEOUT_WiFi)
			{
				ESP32_Drive.infoDisplay = ESPInfo_WifiConnecting;
			}
			else
			{
				ESP32_Drive.setAttr.wifiAutoConnectEnable = false;
				disconnectWifi( &ESP32_Drive );
				ESP32_Drive.infoDisplay = ESPInfo_WifiConnectTimeout;
				//请求手动操作标志位置一
				ESP32_Drive.requestManualAction = true;
			}
			break;
		case ESPStatus_WifiConnectError:  //wifi连接错误    
			res16 = ESP32_SelectWiFiStatus();
			if(res16 == ESPWifiStatus_PSWDError)
			{
				ESP32_Drive.setAttr.wifiAutoConnectEnable = false;
				disconnectWifi( &ESP32_Drive );
				ESP32_Drive.infoDisplay = ESPInfo_WifiPasswordError;
			}
			else if(ESPWifiStatus_NoFound)
			{
				ESP32_Drive.setAttr.wifiAutoConnectEnable = false;
				disconnectWifi( &ESP32_Drive );
				ESP32_Drive.infoDisplay = ESPInfo_NoAPFound;
			}
			else
			{
				//不应该到这
				while(1);
			}
			//请求手动操作标志位置一
			ESP32_Drive.requestManualAction = true;
			break;
		case ESPStatus_WifiConnectSucceeded:  //已连接到WiFi
			//服务器属性是否准备好
			if(ESP32_Drive.serverAttr.ready_Flag == false)
			{
				ESP32_Drive.infoDisplay = ESPInfo_ServerAttrError;
				ESP32_Drive.requestManualAction = true;
				return ;
			}

			ESP32_Drive.infoDisplay = ESPInfo_ServerConnecting;
			res16 = connectServer( &ESP32_Drive );
			while(res16 != 0); 	//陷阱函数
			break;
		case ESPStatus_ServerConnecting:  //服务器连接中    
			ESP32_Drive.timeout ++;
			if(ESP32_Drive.timeout < ESP32_TIMEOUT_Server)
			{
				ESP32_Drive.infoDisplay = ESPInfo_ServerConnecting;
			}
			else
			{ 
				disconnectServer( &ESP32_Drive );
				ESP32_Drive.infoDisplay = ESPInfo_ServerConnectTimeout;
				//请求手动操作标志位置一
				ESP32_Drive.requestManualAction = true;
			}
			break;	
		default:	//不应该能到这
			while(1);
			break;
	
	}
	//如果错误累加值到达一定数量 则将连接状态重置
	// if(ESP32_Drive.errorNum > 100)
	// {
	// 	ESP32_Drive.connectStatus = ESPStatus_NoResponse;
	// 	ESP32_Drive.errorNum = 0;
	// }
}

//连接WiFi
//-1:失败 0:成功
int8_t connectWifi(struct ESP32_Class_st_t *esp)
{
	char esp32_receive[20] = "";
	char esp32_send[2 + ESP32_WIFISSID_MAX + ESP32_WIFIPSWD_MAX] = "";

	//处理ESP32结构体中的变量
	esp->timeout = 0;
	//先判断该阶段是否可以连接WiFi

	//发送指令
	esp32_send[0] = ESP32_START_BIT >> 8;
	esp32_send[1] = ESP32_START_BIT &  0x00ff;
	esp32_send[2] = ESP32_COM_ConnectWifi >> 8;
	esp32_send[3] = ESP32_COM_ConnectWifi &  0x00ff;
	esp32_send[4] = my_strlen(esp->WifiAttr.ssid) >> 8;
	esp32_send[5] = my_strlen(esp->WifiAttr.ssid) &  0x00ff;
	esp32_send[6] = my_strlen(esp->WifiAttr.pswd) >> 8;
	esp32_send[7] = my_strlen(esp->WifiAttr.pswd) &  0x00ff;

	ESP32_TransmitData( esp32_send, NULL, 8);

	//发送ssid和pswd
	my_strcat( esp32_send, esp->WifiAttr.ssid, 2, my_strlen(esp->WifiAttr.ssid));
	my_strcat( esp32_send, esp->WifiAttr.pswd, 2 + my_strlen(esp->WifiAttr.ssid), my_strlen(esp->WifiAttr.pswd));
	
	ESP32_TransmitData( esp32_send, esp32_receive, 2 + my_strlen(esp->WifiAttr.ssid) + my_strlen(esp->WifiAttr.pswd));

	//检测返回值是否正确
	if((esp32_receive[0] == (ESP32_START_BIT >> 8)) && \
	   (esp32_receive[1] == (ESP32_START_BIT &  0x00ff)) && \
	   (esp32_receive[2] == (ESP32_COM_ConnectWifi >> 8)) && \
	   (esp32_receive[3] == (ESP32_COM_ConnectWifi &  0x00ff)) && \
	   (esp32_receive[4] == 'O') && \
	   (esp32_receive[5] == 'K'))
	  {
		  return EX_OK;
	  }

	return EX_ERR;
}   
//断开WiFi          
int8_t disconnectWifi(void)
{
	char esp32_receive[20] = "";
	int16_t res;

	ESP32_SendCom(ESP32_COM_DisconnectWifi);
	// delay_ms(1);
	ESP32_TransmitData( NULL, esp32_receive, 20);
	
	if((esp32_receive[0] == (ESP32_START_BIT >> 8)) && \
	   (esp32_receive[1] == (ESP32_START_BIT & 0x00ff)) && \
	   (esp32_receive[2] == (ESP32_COM_DisconnectWifi >> 8)) && \
	   (esp32_receive[3] == (ESP32_COM_DisconnectWifi & 0x00ff)) && \
	   (esp32_receive[4] == 'O') && \
	   (esp32_receive[5] == 'K'))
	{
		res = EX_OK;
	}
	res = EX_ERR;
}

//连接服务器          
int8_t connectServer(struct ESP32_Class_st_t *esp)
{
	char esp32_receive[20] = "";
	char esp32_send[2 + ESP32_WEBSITE_MAX + 2] = "";
	
	//先判断该阶段是否可以连接服务器

	//处理ESP32结构体中的变量
	esp->timeout = 0;

	//发送指令
	esp32_send[0] = ESP32_START_BIT >> 8;
	esp32_send[1] = ESP32_START_BIT &  0x00ff;
	esp32_send[2] = ESP32_COM_ConnectServer >> 8;
	esp32_send[3] = ESP32_COM_ConnectServer &  0x00ff;
	esp32_send[4] = my_strlen(esp->serverAttr.website) >> 8;
	esp32_send[5] = my_strlen(esp->serverAttr.website) &  0x00ff;

	ESP32_TransmitData( esp32_send, NULL, 6);

	//发送website和port
	my_strcat( esp32_send, esp->serverAttr.website, 2, my_strlen(esp->serverAttr.website));
	esp32_send[2 + my_strlen(esp->serverAttr.website)] = esp->serverAttr.port >> 8;
	esp32_send[2 + my_strlen(esp->serverAttr.website) + 1] = esp->serverAttr.port & 0x00ff;

	ESP32_TransmitData( esp32_send, esp32_receive, 2 + my_strlen(esp->serverAttr.website) + 2);

	//检测返回值是否正确
	if((esp32_receive[0] == (ESP32_START_BIT >> 8)) && \
	   (esp32_receive[1] == (ESP32_START_BIT &  0x00ff)) && \
	   (esp32_receive[2] == (ESP32_COM_ConnectServer >> 8)) && \
	   (esp32_receive[3] == (ESP32_COM_ConnectServer &  0x00ff)) && \
	   (esp32_receive[4] == 'O') && \
	   (esp32_receive[5] == 'K'))
	  {
		  return EX_OK;
	  }

	return EX_ERR;
}   
//断开服务器
int8_t disconnectServer(void)
{
	char esp32_receive[20] = "";
	int16_t res;

	ESP32_SendCom(ESP32_COM_DisconnectServer);
	// delay_ms(1);
	ESP32_TransmitData( NULL, esp32_receive, 20);
	
	if((esp32_receive[0] == (ESP32_START_BIT >> 8)) && \
	   (esp32_receive[1] == (ESP32_START_BIT & 0x00ff)) && \
	   (esp32_receive[2] == (ESP32_COM_DisconnectServer >> 8)) && \
	   (esp32_receive[3] == (ESP32_COM_DisconnectServer & 0x00ff)) && \
	   (esp32_receive[4] == 'O') && \
	   (esp32_receive[5] == 'K'))
	{
		res = EX_OK;
	}
	res = EX_ERR;
}        
//发送/接收网络数据
int8_t netSendOutReceivedFun(struct ESP32_Class_st_t *esp){}  
//查询SNTP时间
int8_t selectSNTPTime(struct ESP32_Class_st_t *esp){}          
//读取状态寄存器 
uint32_t ESP32_Read_SR(uint16_t registerNum){}
//写状态寄存器
uint32_t ESP32_Write_SR(uint16_t registerNum,uint32_t sr){}
//写使能 
int8_t ESP32_Write_Enable(void){}
//写保护
int8_t ESP32_Write_Disable(void){}
//读取flash
int8_t ESP32_Read(uint8_t* pBuffer,u32 ReadAddr,uint16_t NumByteToRead){}
//写入flash
int8_t ESP32_Write(uint8_t* pBuffer,u32 WriteAddr,uint16_t NumByteToWrite){}
//整片擦除
int8_t ESP32_Erase_Chip(void){}
//进入掉电模式
int8_t ESP32_PowerDown(void){}
//唤醒
int8_t ESP32_WAKEUP(void){}

/**@brief 向ESP32结构体中设置服务器属性
* @param[in]  *esp            待修改的ESP32类  
* @param[in]  *serverAttr     填充好的服务器属性结构体  
*/
void ESP32_SetServiceAttr(struct ESP32_Class_st_t *esp,ESP32_ServerConnect_st_t *serverAttr)
{
	uint16_t i;

	esp->serverAttr.ready_Flag = serverAttr->ready_Flag;
	esp->serverAttr.type = serverAttr->type;
	for(i=0;i<ESP32_WEBSITE_MAX;i++)
		esp->serverAttr.website[i] = serverAttr->website[i];
	for(i=0;i<4;i++)
		esp->serverAttr.ip[i] = serverAttr->ip[i];
	esp->serverAttr.port = serverAttr->port;
}

/**@brief 向ESP32结构体中设置WiFi属性
* @param[in]  *esp            待修改的ESP32类  
* @param[in]  *wifiAttr       填充好的WiFi属性结构体  
*/
void ESP32_SetWiFiAttr(struct ESP32_Class_st_t *esp,ESP32_WifiConnectAttr_st_t *wifiAttr)
{
	uint16_t i;

	esp->WifiAttr.ready_Flag = wifiAttr->ready_Flag;
	esp->WifiAttr.ecn = wifiAttr->ecn;
	for(i=0;i<ESP32_WIFISSID_MAX;i++)
		esp->WifiAttr.ssid[i] = wifiAttr->ssid[i];
	for(i=0;i<ESP32_WIFISSID_MAX;i++)
		esp->WifiAttr.pswd[i] = wifiAttr->pswd[i];
	esp->WifiAttr.rssi = wifiAttr->rssi;
	for(i=0;i<6;i++)
		esp->WifiAttr.mac[i] = wifiAttr->mac[i];
}


//发送网络数据
void ESP32_SendNetData(char *s, uint32_t num)
{

}

//接收网络数据
void ESP32_ReceivedNetData(char *s, uint32_t num)
{

}


 
/**@brief 读取ID
* @return 函数执行结果
* - EX_ERR        	上报失败 
* - other           设备ID号
*/
int16_t ESP32_ReadDeviceID(void)
{ 
	char esp32_buf[20] = "";
	int16_t res;

	ESP32_SendCom(ESP32_COM_REQUEST_ID);
	// delay_ms(1);
	ESP32_TransmitData( NULL, esp32_buf, 20);
	
	if((esp32_buf[0] == (ESP32_START_BIT >> 8)) && \
	   (esp32_buf[1] == (ESP32_START_BIT & 0x00ff)) && \
	   (esp32_buf[2] == (ESP32_COM_REQUEST_ID >> 8)) && \
	   (esp32_buf[3] == (ESP32_COM_REQUEST_ID & 0x00ff))\
	   )
	{
		res = esp32_buf[4]<<8 | esp32_buf[5];
	}
	else
	{  
		res = EX_ERR;
	}
	
	return res;
}


/**@brief 发送网络数据
* @return 函数执行结果
* - EX_ERR        	上报失败 
* - EX_OK      		上报成功
* - -2        		ESP32未连接到服务器
*/
int16_t ESP32_SendNetData(char *sendBuf, uint16_t lenth)
{ 
	char esp32_buf[20] = "";
	int16_t res;

	ESP32_SendCom(ESP32_COM_SENDER);
	// delay_ms(1);
	ESP32_TransmitData( NULL, esp32_buf, 20);
	
	if((esp32_buf[0] == (ESP32_START_BIT >> 8)) && \
	   (esp32_buf[1] == (ESP32_START_BIT & 0x00ff)) && \
	   (esp32_buf[2] == (ESP32_COM_SENDER >> 8)) && \
	   (esp32_buf[3] == (ESP32_COM_SENDER & 0x00ff)) && \
	   (my_Memcmp(&esp32_buf[4], "OK", 2) == EX_OK) \
	)
	{
		// delay_ms(1);
		esp32_buf[0] = ESP32_START_BIT >> 8;
		esp32_buf[1] = ESP32_START_BIT & 0x00ff;
		esp32_buf[2] = ESP32_COM_SENDER >> 8;
		esp32_buf[3] = ESP32_COM_SENDER & 0x00ff; 
		esp32_buf[4] = lenth >> 8;
		esp32_buf[5] = lenth & 0x00ff;

		ESP32_TransmitData( esp32_buf, NULL, 6);
		// delay_ms(1);
		ESP32_TransmitData(sendBuf, NULL, lenth);

		res = EX_OK;
	}
	else if((esp32_buf[0] == (ESP32_START_BIT >> 8)) && \
	   (esp32_buf[1] == (ESP32_START_BIT & 0x00ff)) && \
	   (esp32_buf[2] == (ESP32_COM_SENDER >> 8)) && \
	   (esp32_buf[3] == (ESP32_COM_SENDER & 0x00ff)) && \
	   (my_Memcmp(&esp32_buf[4], "ERROR", 5) == EX_OK) \
	)
	{
		res = -2;
	}
	else
	{                             
		res = EX_ERR;
	}
	
	return res;
}

/**@brief 接收网络数据
* @return 函数执行结果 
* - EX_ERR        	上报失败 
* - EX_OK      		上报成功 
* - -2              没有新的网络数据 
*/
int16_t ESP32_ReceiveNetData(char *receiveBuf, uint16_t lenth)
{
	char esp32_buf[20] = "";
	int16_t res;

	ESP32_SendCom(ESP32_COM_RECEIVER);
	// delay_ms(1);
	ESP32_TransmitData( NULL, esp32_buf, 20);
	
	if((esp32_buf[0] == (ESP32_START_BIT >> 8)) && \
	   (esp32_buf[1] == (ESP32_START_BIT & 0x00ff)) && \
	   (esp32_buf[2] == (ESP32_COM_RECEIVER >> 8)) && \
	   (esp32_buf[3] == (ESP32_COM_RECEIVER & 0x00ff)) && \
	   ((esp32_buf[4] | esp32_buf[5]) != 0) \
	)
	{
		//获取接收长度
		lenth = esp32_buf[4] << 8 |esp32_buf[5];
		// delay_ms(1);
		esp32_buf[0] = ESP32_START_BIT >> 8;
		esp32_buf[1] = ESP32_START_BIT & 0x00ff;
		esp32_buf[2] = ESP32_COM_RECEIVER >> 8;
		esp32_buf[3] = ESP32_COM_RECEIVER & 0x00ff; 
		esp32_buf[4] = 'O';
		esp32_buf[5] = 'K';
		//传输应答数据
		ESP32_TransmitData( esp32_buf, NULL, 8);
		// delay_ms(1);
		//接收网络数据
		ESP32_TransmitData( NULL, receiveBuf, ((lenth >> 2) + 1) << 2);

		res = EX_OK;
	}
	else if((esp32_buf[0] == (ESP32_START_BIT >> 8)) && \
	   (esp32_buf[1] == (ESP32_START_BIT & 0x00ff)) && \
	   (esp32_buf[2] == (ESP32_COM_RECEIVER >> 8)) && \
	   (esp32_buf[3] == (ESP32_COM_RECEIVER & 0x00ff)) && \
	   ((esp32_buf[4] | esp32_buf[5]) == 0) \
	)
	{
		//没有新的网络数据
		res = -2;
	}
	else
	{  
		res = EX_ERR;
	}
	
	return res;
}

/**@brief 查询ESP联网状态
* @return 函数执行结果
* - EX_ERR        	上报失败 
* - other      		ESP模块状态
*/
int16_t ESP32_SelectStatus(void)
{ 
	char esp32_buf[20] = "";
	int16_t res;

	ESP32_SendCom(ESP32_COM_GET_STATUS);
	ESP32_TransmitData( NULL, esp32_buf, 20);
	
	if((esp32_buf[0] == (ESP32_START_BIT>>8))&& \
	   (esp32_buf[1] == (ESP32_START_BIT&0x00ff)) && \
	   (esp32_buf[2] == (ESP32_COM_GET_STATUS >> 8)) && \
	   (esp32_buf[3] == (ESP32_COM_GET_STATUS & 0x00ff)))
	{
		res = ( esp32_buf[4] << 8 ) | esp32_buf[5];
	}
	else
	{  
		res = EX_ERR;
	}
	
	return res;
}

/**@brief 查询wifi连接状态
* @return 函数执行结果
* - EX_ERR        	上报失败 
* - other      		WiFi连接状态
*/
int16_t ESP32_SelectWiFiStatus(void)
{ 
	char esp32_buf[20] = "";
	int16_t res;

	ESP32_SendCom(ESP32_COM_GET_WIFI_STATUS);
	ESP32_TransmitData( NULL, esp32_buf, 20);
	
	if((esp32_buf[0] == (ESP32_START_BIT>>8))&& \
	   (esp32_buf[1] == (ESP32_START_BIT&0x00ff)) && \
	   (esp32_buf[2] == (ESP32_COM_GET_WIFI_STATUS >> 8)) && \
	   (esp32_buf[3] == (ESP32_COM_GET_WIFI_STATUS & 0x00ff)))
	{
		res = ( esp32_buf[4] << 8 ) | esp32_buf[5];
	}
	else
	{  
		res = EX_ERR;
	}
	
	return res;
}

/**@brief 发送指令
* @param[in]  com            发送的指令 
*/
void ESP32_SendCom(uint16_t com)
{
	ESP32_Wait_Flag = 1;
	ESP32_SPICS = 0;	
	// delay_ms(1);
	while(ESP32_HANDSHAKE_IO == 1);
	ESP32_Wait_Flag = 0;
	SPI_ReadWriteByte(ESP32_SPICOM, ESP32_START_BIT>>8);       //发送起始位
	SPI_ReadWriteByte(ESP32_SPICOM, ESP32_START_BIT&0x00ff);
	SPI_ReadWriteByte(ESP32_SPICOM, com>>8);                   //发送指令
	SPI_ReadWriteByte(ESP32_SPICOM, com&0x00ff);
	ESP32_SPICS = 1;		   
}

/**@brief ESP32 SPI传输数据
* @param[in]  sendBuf            发送数据缓存  
* @param[in]  readBuf            接收数据缓存  
* @param[in]  len                传输长度      -长度必须为4的倍数
*/
void ESP32_TransmitData(char *sendBuf,char *readBuf, uint16_t len)
{
	uint16_t i;
	
	if(((sendBuf == NULL)&&(readBuf == NULL))||(len == 0))
		return ;
	
	//len补位
	if((len & 0x03) != 0x00)
	{
		len = (((len>>2)+1)<<2);
	}

	if((sendBuf == NULL)&&(readBuf != NULL))
	{
		ESP32_Wait_Flag = 1;
		ESP32_SPICS = 0;
		while(ESP32_Wait_Flag == 1);
		for(i=0;i<len;i++)
		{
			readBuf[i] = SPI_ReadWriteByte(ESP32_SPICOM, 0x00);
		}
		ESP32_SPICS = 1;	
	}
	else if((sendBuf != NULL)&&(readBuf == NULL))
	{
		ESP32_Wait_Flag = 1;
		ESP32_SPICS = 0;
		while(ESP32_Wait_Flag == 1);
		for(i=0;i<len;i++)
		{
			SPI_ReadWriteByte(ESP32_SPICOM, sendBuf[i]);
		}
		ESP32_SPICS = 1;	
	}
	else if((sendBuf != NULL)&&(readBuf != NULL))
	{
		ESP32_Wait_Flag = 1;
		ESP32_SPICS = 0;
		while(ESP32_Wait_Flag == 1);
		for(i=0;i<len;i++)
		{
			readBuf[i] = SPI_ReadWriteByte(ESP32_SPICOM, sendBuf[i]);
		}
		ESP32_SPICS = 1;	
	}
	else
	{
		return;
	}
}



