#include "ESP32.h"

struct ESP32_Class_st_t ESP32_Drive;

//RSP32��ʼ��
void ESP32_Init(void)
{
    ESP32_Drive.initStatus = 1;                          //��ʼ��״̬
	ESP32_Drive.connectStatus = ESPStatus_NoResponse;    //����״̬ 
	ESP32_Drive.setAttr.serverAutoConnectEnable = 1;     //����������  
    ESP32_Drive.setAttr.wifiAutoConnectEnable = 1;
	ESP32_Drive.sendComStatus = 0;                       //����ָ���״̬
	ESP32_Drive.callbackTimeout = 0;                     //�ص���ʱʱ��
	ESP32_Drive.keepAlive = 100;                         //������ʱ��
	ESP32_Drive.errorNum = 0;                            //���������
	// ESP32_Drive.netSendoutData; //�����͵���������
	// ESP32_Drive.netReceivedData;//���յ�����������
	ESP32_Drive.WifiConnectStatus = 0;                   //wifi����״̬
	ESP32_Drive.WifiAttr;                  //WiFi����
	ESP32_Drive.serverAttr;              //����������
	ESP32_Drive.stnpTime;                     //STNPʱ��
	//����ָ���ʼ��
	ESP32_Drive.connectWifi = connectWifi;            //����WiFi
	ESP32_Drive.disconnectWifi = disconnectWifi;          //�Ͽ�WiFi
	ESP32_Drive.connectServer = connectServer;         //���ӷ�����
	ESP32_Drive.disconnectServer = disconnectServer;  //�Ͽ�������
	ESP32_Drive.netSendOutFun = netSendOutFun; //������������
	ESP32_Drive.netReceivedFun = netReceivedFun; //������������
	ESP32_Drive.selectSNTPTime = selectSNTPTime;          //��ѯSNTPʱ��
}

void ESP32_Service(void)
{
	uint8_t res8;
	uint16_t res16;
	uint32_t res32; 
	//״̬�ж� ״̬����
	switch(ESP32_Drive.connectStatus)
	{
		case ESPStatus_NoResponse:               //ģ������Ӧ
			//��ѯģ��ID
			if(ESP32_Read_ID() == ESP32_SPI_ID)
				ESP32_Drive.connectStatus = ESPStatus_NoInit;
			break;
		case ESPStatus_NoInit:                   //ģ��δ��ʼ��
			//��ESP32д��WiFi��Ϣ
			//��ESP32д���������Ϣ
			//��������ѯSTNPʱ��
			break;
		case ESPStatus_NoWifi:                   //δ���ӵ�WiFi
			//����Ϊ�Զ�����WiFiʱ ֱ������WiFi
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
						case 0:        //���ش���
							ESP32_Drive.WifiConnectStatus = 0;
							ESP32_Drive.errorNum ++;
							break;
						case 1:        //���ӳɹ�
							ESP32_Drive.connectStatus = ESPStatus_ConnectedWifi;
							ESP32_Drive.WifiConnectStatus = 1;
							ESP32_Drive.errorNum =0;
							break;
						case 2:        //��������
							break;
						case 3:        //����ʧ��
							ESP32_Drive.WifiConnectStatus = 0;
							ESP32_Drive.errorNum ++;
							break;
					}
				}
				else       //����������� �����¶Ͽ�WiFi�ٽ�������
				{
					ESP32_Drive.WifiConnectStatus = 0;
					ESP32_Drive.errorNum ++;
				} 
			}
			break;
		case ESPStatus_ConnectedWifi:            //�����ӵ�WiFi
			//����Ϊ�Զ����ӷ�����ʱ ֱ�����ӷ�����
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
		case ESPStatus_ConnectedTCP:             //�����ӵ�������
			//��ȡESP32 SPI����Ĵ��� �ж��Ƿ������ӵ�������
			break;
		case ESPStatus_ServerResponse:           //����������Ӧ
			//����������
			//������/�������ݴ���
			res8 = netSendOutReceivedFun(&ESP32_Drive);
			if((ESP32_Drive.netSendoutData.status == 1)&&(res8 == 1))
			{
				ESP32_Drive.netSendoutData.status = 2;
			}	
			//���������ۼӻ��� ���ʹ���+1������ȷ-8 ���� ��ⶪ����
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
	//��������ۼ�ֵ����һ������ ������״̬����
	if(ESP32_Drive.errorNum > 100)
	{
		ESP32_Drive.connectStatus = ESPStatus_NoResponse;
		ESP32_Drive.errorNum = 0;
	}
}

//����WiFi
//0:ʧ�� 1:�ɹ� 2:������
uint16_t connectWifi(struct ESP32_Class_st_t *esp)
{
	uint16_t res;
	uint16_t i;

	//���жϸý׶��Ƿ��������WiFi
	if((esp->connectStatus == ESPStatus_NoResponse) || \
	   (esp->connectStatus == ESPStatus_NoInit))
		return 0;

	if(esp->WifiConnectStatus == 0)
	{ 
		ESP32_SPICS=0;				    
		//��̶��Ĵ���д��WiFi������Ϣ 
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
		//��ⷵ��ֵ�Ƿ���ȷ
		if(res != ESP32_ReturnCode_OK)
			return 0;
		//��ESP32����WiFi����ָ��
		SPI_ReadWriteByte(ESP32_SPICOM, ESP32_COM_ConnectWifi);//��������WiFi����
		res|=SPI_ReadWriteByte(ESP32_SPICOM, 0xFF)<<8;  
		res|=SPI_ReadWriteByte(ESP32_SPICOM, 0xFF);	 
		ESP32_SPICS=1;
		//��ⷵ��ֵ�Ƿ���ȷ
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
//�Ͽ�WiFi          
uint8_t disconnectWifi(struct ESP32_Class_st_t *esp)
{
	uint16_t res;
	//��ESP32����WiFi�Ͽ�ָ��
	ESP32_SPICS=0;
	SPI_ReadWriteByte(ESP32_SPICOM, ESP32_COM_DisconnectWifi);//���ͶϿ�WiFi����
	res|=SPI_ReadWriteByte(ESP32_SPICOM, 0xFF)<<8;  
	res|=SPI_ReadWriteByte(ESP32_SPICOM, 0xFF);	 
	ESP32_SPICS=1;
	//��ⷵ��ֵ�Ƿ���ȷ
	if(res != ESP32_ReturnCode_OK)
		return 0;
	esp->WifiConnectStatus = 0;
	return 1;
}
//��ѯWiFi����״̬
uint8_t selectWifiConnectStatus(struct ESP32_Class_st_t *esp)
{
	unsigned int regSR1;
	uint16_t res;
	//��ȡ״̬�Ĵ���SR1
	ESP32_SPICS=0;
	regSR1 = ESP32_Read_SR(ESP32_Register_SR1);
	res|=SPI_ReadWriteByte(ESP32_SPICOM, 0xFF)<<8;  
	res|=SPI_ReadWriteByte(ESP32_SPICOM, 0xFF);	
	ESP32_SPICS=1;
	//��ⷵ��ֵ�Ƿ���ȷ
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
//���ӷ�����          
uint8_t connectServer(struct ESP32_Class_st_t *esp)
{
	//���жϸý׶��Ƿ�������ӷ�����
}            
//�Ͽ�������
uint8_t disconnectServer(struct ESP32_Class_st_t *esp){}        
//����/������������
uint8_t netSendOutReceivedFun(struct ESP32_Class_st_t *esp){}  
//��ѯSNTPʱ��
uint8_t selectSNTPTime(struct ESP32_Class_st_t *esp){}          

//��ȡFLASH ID
uint16_t  ESP32_Read_ID(void)
{
	uint16_t res = 0;	  
	ESP32_SPICS=0;				    
	SPI_ReadWriteByte(ESP32_SPICOM, ESP32_COM_DeviceID);//���Ͷ�ȡID����	     			   
	res|=SPI_ReadWriteByte(ESP32_SPICOM, 0xFF)<<8;  
	res|=SPI_ReadWriteByte(ESP32_SPICOM, 0xFF);	 
	ESP32_SPICS=1;				    
	return res;
}       
 

//��ȡ״̬�Ĵ��� 
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

//д״̬�Ĵ���
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

//дʹ�� 
void ESP32_Write_Enable(void)
{

}

//д����
void ESP32_Write_Disable(void)
{

}

//��ȡflash
void ESP32_Read(uint8_t* pBuffer,u32 ReadAddr,uint16_t NumByteToRead)
{

}

//д��flash
void ESP32_Write(uint8_t* pBuffer,u32 WriteAddr,uint16_t NumByteToWrite)
{

}

//��Ƭ����
uint8_t ESP32_Erase_Chip(void)
{
    uint8_t res ;
    SPI_ReadWriteByte(ESP32_SPICOM, ESP32_COM_ReadStatusReg); 
    res = SPI_ReadWriteByte(ESP32_SPICOM, 0x00); 

    return res;
}

//�ȴ�����
void ESP32_Wait_Busy(void)
{

}

//�������ģʽ
void ESP32_PowerDown(void)
{

}

//����
void ESP32_WAKEUP(void)
{

}

//���÷���������
void ESP32_SetServiceAttr(struct ESP32_Class_st_t *esp,ESP32_ServerConnect_st_t *serverAttr)
{

}

//����WiFi����
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


//������������
void ESP32_SendNetData(char *s, uint32_t num)
{

}

//������������
void ESP32_ReceivedNetData(char *s, uint32_t num)
{

}


