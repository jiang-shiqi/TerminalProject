#include "ESP32.h"     
#include "GPIO.h"
#include "SPI.h"
#include "Delay.h"


uint16_t ESP32_SerialNumber;
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
    ESP32_Drive.initStatus = 1;                          //初始化状态
	ESP32_Drive.connectStatus = ESPStatus_NoResponse;    //连接状态 
	ESP32_Drive.setAttr.serverAutoConnectEnable = 1;     //可设置属性  
    ESP32_Drive.setAttr.wifiAutoConnectEnable = 1;
	ESP32_Drive.sendComStatus = 0;                       //发送指令的状态
	ESP32_Drive.callbackTimeout = 0;                     //回调超时时间
	ESP32_Drive.keepAlive = 100;                         //心跳包时间
	ESP32_Drive.errorNum = 0;                            //错误计数器
	// ESP32_Drive.netSendoutData; //待发送的网络数据
	// ESP32_Drive.netReceivedData;//接收到的网络数据
	ESP32_Drive.WifiConnectStatus = 0;                   //wifi连接状态
	ESP32_Drive.WifiAttr;                  //WiFi属性
	ESP32_Drive.serverAttr;              //服务器属性
	ESP32_Drive.stnpTime;                     //STNP时间
	//函数指针初始化
	ESP32_Drive.connectWifi = connectWifi;            //连接WiFi
	ESP32_Drive.disconnectWifi = disconnectWifi;          //断开WiFi
	ESP32_Drive.connectServer = connectServer;         //连接服务器
	ESP32_Drive.disconnectServer = disconnectServer;  //断开服务器
	ESP32_Drive.netSendOutFun = netSendOutFun; //发送网络数据
	ESP32_Drive.netReceivedFun = netReceivedFun; //接收网络数据
	ESP32_Drive.selectSNTPTime = selectSNTPTime;          //查询SNTP时间
}

void ESP32_Service(void)
{
	uint8_t res8;
	uint16_t res16;
	uint32_t res32; 
	//状态检测 
	ESP32_ConnectionStatus = ESP32_SelectStatus();
	//状态处理
	switch(ESP32_Drive.connectStatus)
	{
		case ESPStatus_NoResponse:               //模块无响应
			//查询模块ID
				ESP32_SerialNumber = ESP32_ReadDeviceID();
				if(ESP32_SerialNumber == ESP32_DRIVE_ID)
				{
					ESP32_Drive.connectStatus = ESPStatus_NoInit;
				}
			break;
		case ESPStatus_NoWifi:                   //未连接到WiFi
			//配置为自动连接WiFi时 直接连接WiFi
			if((ESP32_Drive.setAttr.wifiAutoConnectEnable == 1)&&(ESP32_Drive.WifiConnectStatus == 0))
			{
				res8 = connectWifi(&ESP32_Drive);
				if(res8 == 0)
				{
					ESP32_Drive.errorNum ++;
				}
				else
				{
					ESP32_Drive.errorNum =0;
				}
			}
			if(ESP32_Drive.WifiConnectStatus == 2)
			{
				
			}
			break;
		case ESPStatus_WifiConnecting:			//WiFi连接中

			break;
		case ESPStatus_ConnectedWifi:            //已连接到WiFi
			//配置为自动连接服务器时 直接连接服务器
			if(ESP32_Drive.setAttr.serverAutoConnectEnable == 1)
			{
				res8 = connectServer(&ESP32_Drive);
				if(res8 == 1)
				{
					ESP32_Drive.connectStatus = ESPStatus_ConnectedTCP;
					ESP32_Drive.errorNum = 0;
				} 
				else
					ESP32_Drive.errorNum ++;
			}
			break;
		case ESPStatus_ConnectedTCP:             //已连接到服务器
			//读取ESP32 SPI虚拟寄存器 判断是否已连接到服务器
			break;
		case ESPStatus_ServerResponse:           //服务器已响应
			//发送心跳包
			//待发送/接收数据处理
			res8 = netSendOutReceivedFun(&ESP32_Drive);
			if((ESP32_Drive.netSendoutData.status == 1)&&(res8 == 1))
			{
				ESP32_Drive.netSendoutData.status = 2;
			}	
			//建立错误累加机制 发送错误+1发送正确-8 或是 检测丢包率
			if(res8 == 1)
			{
				if(ESP32_Drive.errorNum >= 8)
					ESP32_Drive.errorNum -= 8;
			}
			else
			{
				ESP32_Drive.errorNum ++;
			}
			break;
	}
	//如果错误累加值到达一定数量 则将连接状态重置
	if(ESP32_Drive.errorNum > 100)
	{
		ESP32_Drive.connectStatus = ESPStatus_NoResponse;
		ESP32_Drive.errorNum = 0;
	}
}

//连接WiFi
//0:失败 1:成功 2:连接中
uint16_t connectWifi(struct ESP32_Class_st_t *esp)
{
	uint16_t res;
	uint16_t i;

	//先判断该阶段是否可以连接WiFi
	if((esp->connectStatus == ESPStatus_NoResponse) || \
	   (esp->connectStatus == ESPStatus_NoInit))
		return 0;

	if(esp->WifiConnectStatus == 0)
	{ 
		ESP32_SPICS=0;				    
		//向固定寄存器写入WiFi连接信息 
		SPI_ReadWriteByte(ESP32_SPICOM, ESP32_COM_SetWifiAttr);
		SPI_ReadWriteByte(ESP32_SPICOM, ESP32_WIFISSID_MAX); 
		SPI_ReadWriteByte(ESP32_SPICOM, ESP32_WIFIPSWD_MAX);
		for(i=0;i<ESP32_WIFISSID_MAX;i++)
		{
			SPI_ReadWriteByte(ESP32_SPICOM, esp->WifiAttr.ssid[i]);
		}
		for(i=0;i<ESP32_WIFIPSWD_MAX;i++)
		{
			SPI_ReadWriteByte(ESP32_SPICOM, esp->WifiAttr.pswd[i]);
		}
		res|=SPI_ReadWriteByte(ESP32_SPICOM, 0xFF)<<8;  
		res|=SPI_ReadWriteByte(ESP32_SPICOM, 0xFF);	 
		//检测返回值是否正确
		if(res != ESP32_ReturnCode_OK)
			return 0;
		//向ESP32发送WiFi连接指令
		SPI_ReadWriteByte(ESP32_SPICOM, ESP32_COM_ConnectWifi);//发送连接WiFi命令
		res|=SPI_ReadWriteByte(ESP32_SPICOM, 0xFF)<<8;  
		res|=SPI_ReadWriteByte(ESP32_SPICOM, 0xFF);	 
		ESP32_SPICS=1;
		//检测返回值是否正确
		if(res == ESP32_ReturnCode_OK)
			return 2;
		else
			return 0;
	}
	else if(esp->WifiConnectStatus == 1)
	{
		return 1;
	}
	else if(esp->WifiConnectStatus == 2)
	{ 
		return 2;
	}

	return 0;
}   
//断开WiFi          
uint8_t disconnectWifi(struct ESP32_Class_st_t *esp)
{
	uint16_t res;
	//向ESP32发送WiFi断开指令
	ESP32_SPICS=0;
	SPI_ReadWriteByte(ESP32_SPICOM, ESP32_COM_DisconnectWifi);//发送断开WiFi命令
	res|=SPI_ReadWriteByte(ESP32_SPICOM, 0xFF)<<8;  
	res|=SPI_ReadWriteByte(ESP32_SPICOM, 0xFF);	 
	ESP32_SPICS=1;
	//检测返回值是否正确
	if(res != ESP32_ReturnCode_OK)
		return 0;
	esp->WifiConnectStatus = 0;
	return 1;
}
// //查询WiFi连接状态
// uint8_t selectWifiConnectStatus(struct ESP32_Class_st_t *esp)
// {
// 	unsigned int regSR1;
// 	uint16_t res;
// 	//读取状态寄存器SR1
// 	ESP32_SPICS=0;
// 	regSR1 = ESP32_Read_SR(ESP32_Register_SR1);
// 	res|=SPI_ReadWriteByte(ESP32_SPICOM, 0xFF)<<8;  
// 	res|=SPI_ReadWriteByte(ESP32_SPICOM, 0xFF);	
// 	ESP32_SPICS=1;
// 	//检测返回值是否正确
// 	if(res != ESP32_ReturnCode_OK)
// 		return 0;
// 	regSR1 = ((ESP32_Register_SR1_un_t *)&regSR1)->bit.wifiConSta;

// 	if(esp->WifiConnectStatus == 0)
// 	{
// 		return 0;
// 	}
// 	else if(esp->WifiConnectStatus == 1)
// 	{ 
// 		return 0;
// 	}
// 	else if(esp->WifiConnectStatus == 2)
// 	{
// 		if(regSR1 == 0)
// 			esp->WifiConnectStatus = 3;
// 		else if(regSR1 == 1)
// 			esp->WifiConnectStatus = 1;
// 		else if(regSR1 == 2)
// 			esp->WifiConnectStatus = 2;
// 	}

// 	return 1;
// }
//连接服务器          
uint8_t connectServer(struct ESP32_Class_st_t *esp)
{
	//先判断该阶段是否可以连接服务器
}            
//断开服务器
uint8_t disconnectServer(struct ESP32_Class_st_t *esp){}        
//发送/接收网络数据
uint8_t netSendOutReceivedFun(struct ESP32_Class_st_t *esp){}  
//查询SNTP时间
uint8_t selectSNTPTime(struct ESP32_Class_st_t *esp){}          


//读取状态寄存器 
uint32_t ESP32_Read_SR(uint16_t registerNum)
{
    uint32_t res = 0;
	ESP32_SPICS=0;	
    SPI_ReadWriteByte(ESP32_SPICOM, ESP32_COM_ReadStatusReg);
    SPI_ReadWriteByte(ESP32_SPICOM, registerNum);
    res |= SPI_ReadWriteByte(ESP32_SPICOM, 0x00)<<24;
    res |= SPI_ReadWriteByte(ESP32_SPICOM, 0x00)<<16;
    res |= SPI_ReadWriteByte(ESP32_SPICOM, 0x00)<<8;
    res |= SPI_ReadWriteByte(ESP32_SPICOM, 0x00);
	ESP32_SPICS=1;	
    
    return res;
}

//写状态寄存器
uint32_t ESP32_Write_SR(uint16_t registerNum,uint32_t sr)
{ 
    uint8_t res;
    SPI_ReadWriteByte(ESP32_SPICOM, ESP32_COM_WriteStatusReg); 
    SPI_ReadWriteByte(ESP32_SPICOM, registerNum); 
    SPI_ReadWriteByte(ESP32_SPICOM, (sr>>24) &0x000000ff);  
    SPI_ReadWriteByte(ESP32_SPICOM, (sr>>16) &0x000000ff);  
    SPI_ReadWriteByte(ESP32_SPICOM, (sr>>8)  &0x000000ff);  
    SPI_ReadWriteByte(ESP32_SPICOM, (sr)     &0x000000ff);   
    res |= SPI_ReadWriteByte(ESP32_SPICOM, 0x00); 

    return res;
}

//写使能 
void ESP32_Write_Enable(void)
{

}

//写保护
void ESP32_Write_Disable(void)
{

}

//读取flash
void ESP32_Read(uint8_t* pBuffer,u32 ReadAddr,uint16_t NumByteToRead)
{

}

//写入flash
void ESP32_Write(uint8_t* pBuffer,u32 WriteAddr,uint16_t NumByteToWrite)
{

}

//整片擦除
uint8_t ESP32_Erase_Chip(void)
{
    uint8_t res ;
    SPI_ReadWriteByte(ESP32_SPICOM, ESP32_COM_ReadStatusReg); 
    res = SPI_ReadWriteByte(ESP32_SPICOM, 0x00); 

    return res;
}

//等待空闲
void ESP32_Wait_Busy(void)
{

}

//进入掉电模式
void ESP32_PowerDown(void)
{

}

//唤醒
void ESP32_WAKEUP(void)
{

}

//设置服务器属性
void ESP32_SetServiceAttr(struct ESP32_Class_st_t *esp,ESP32_ServerConnect_st_t *serverAttr)
{

}

//设置WiFi属性
void ESP32_SetWiFiAttr(struct ESP32_Class_st_t *esp,ESP32_WifiConnectAttr_st_t *wifiAttr)
{
	uint16_t i;

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
	// delay_ms(1);
	ESP32_TransmitData( NULL, esp32_buf, 20);
	
	if((esp32_buf[0] == (ESP32_START_BIT>>8))&& \
		 (esp32_buf[1] == (ESP32_START_BIT&0x00ff)) && \
		 (esp32_buf[2] == (ESP32_COM_GET_STATUS >> 8)) && \
	   (esp32_buf[3] == (ESP32_COM_GET_STATUS & 0x00ff))\
	)
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
	ESP_CS = 0;	
	// delay_ms(1);
	while(ESP32_HANDSHAKE_IO == 1);
	ESP32_Wait_Flag = 0;
	SPI_ReadWriteByte(ESP32_SPICOM, ESP32_START_BIT>>8);       //发送起始位
	SPI_ReadWriteByte(ESP32_SPICOM, ESP32_START_BIT&0x00ff);
	SPI_ReadWriteByte(ESP32_SPICOM, com>>8);                   //发送指令
	SPI_ReadWriteByte(ESP32_SPICOM, com&0x00ff);
	ESP_CS = 1;		   
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
		ESP_CS = 0;
		while(ESP32_Wait_Flag == 1);
		for(i=0;i<len;i++)
		{
			readBuf[i] = SPI_ReadWriteByte(ESP32_SPICOM, 0x00);
		}
		ESP_CS = 1;	
	}
	else if((sendBuf != NULL)&&(readBuf == NULL))
	{
		ESP32_Wait_Flag = 1;
		ESP_CS = 0;
		while(ESP32_Wait_Flag == 1);
		for(i=0;i<len;i++)
		{
			SPI_ReadWriteByte(ESP32_SPICOM, sendBuf[i]);
		}
		ESP_CS = 1;	
	}
	else if((sendBuf != NULL)&&(readBuf != NULL))
	{
		ESP32_Wait_Flag = 1;
		ESP_CS = 0;
		while(ESP32_Wait_Flag == 1);
		for(i=0;i<len;i++)
		{
			readBuf[i] = SPI_ReadWriteByte(ESP32_SPICOM, sendBuf[i]);
		}
		ESP_CS = 1;	
	}
	else
	{
		return;
	}
}



