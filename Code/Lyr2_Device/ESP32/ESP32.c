#include "ESP32.h"

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
	//状态判断 状态处理
	switch(ESP32_Drive.connectStatus)
	{
		case ESPStatus_NoResponse:               //模块无响应
			//查询模块ID
			if(ESP32_Read_ID() == ESP32_SPI_ID)
				ESP32_Drive.connectStatus = ESPStatus_NoInit;
			break;
		case ESPStatus_NoInit:                   //模块未初始化
			//向ESP32写入WiFi信息
			//向ESP32写入服务器信息
			//待定：查询STNP时间
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
					ESP32_Drive.WifiConnectStatus = 2;
				}
			}
			if(ESP32_Drive.WifiConnectStatus == 2)
			{
				if(selectWifiConnectStatus(&ESP32_Drive))
				{
					switch(ESP32_Drive.WifiConnectStatus)
					{
						case 0:        //返回错误
							ESP32_Drive.WifiConnectStatus = 0;
							ESP32_Drive.errorNum ++;
							break;
						case 1:        //连接成功
							ESP32_Drive.connectStatus = ESPStatus_ConnectedWifi;
							ESP32_Drive.WifiConnectStatus = 1;
							ESP32_Drive.errorNum =0;
							break;
						case 2:        //正在连接
							break;
						case 3:        //连接失败
							ESP32_Drive.WifiConnectStatus = 0;
							ESP32_Drive.errorNum ++;
							break;
					}
				}
				else       //操作步骤错误 需重新断开WiFi再进行连接
				{
					ESP32_Drive.WifiConnectStatus = 0;
					ESP32_Drive.errorNum ++;
				} 
			}
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
//查询WiFi连接状态
uint8_t selectWifiConnectStatus(struct ESP32_Class_st_t *esp)
{
	unsigned int regSR1;
	uint16_t res;
	//读取状态寄存器SR1
	ESP32_SPICS=0;
	regSR1 = ESP32_Read_SR(ESP32_Register_SR1);
	res|=SPI_ReadWriteByte(ESP32_SPICOM, 0xFF)<<8;  
	res|=SPI_ReadWriteByte(ESP32_SPICOM, 0xFF);	
	ESP32_SPICS=1;
	//检测返回值是否正确
	if(res != ESP32_ReturnCode_OK)
		return 0;
	regSR1 = ((ESP32_Register_SR1_un_t *)&regSR1)->bit.wifiConSta;

	if(esp->WifiConnectStatus == 0)
	{
		return 0;
	}
	else if(esp->WifiConnectStatus == 1)
	{ 
		return 0;
	}
	else if(esp->WifiConnectStatus == 2)
	{
		if(regSR1 == 0)
			esp->WifiConnectStatus = 3;
		else if(regSR1 == 1)
			esp->WifiConnectStatus = 1;
		else if(regSR1 == 2)
			esp->WifiConnectStatus = 2;
	}

	return 1;
}
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

//读取FLASH ID
uint16_t  ESP32_Read_ID(void)
{
	uint16_t res = 0;	  
	ESP32_SPICS=0;				    
	SPI_ReadWriteByte(ESP32_SPICOM, ESP32_COM_DeviceID);//发送读取ID命令	     			   
	res|=SPI_ReadWriteByte(ESP32_SPICOM, 0xFF)<<8;  
	res|=SPI_ReadWriteByte(ESP32_SPICOM, 0xFF);	 
	ESP32_SPICS=1;				    
	return res;
}       
 

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


