#include "include.h"
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

//ESP32初始化函数
void ESP32_Init(void)
{
	ESP32_SerialNumber = 0;
	ESP32_ConnectionFlag = 0;
	ESP32_ConnectionStatus = 0;
	ESP32_Ready_Flag = 0;
	ESP32_Wait_Flag = 0;
}

//ESP32 服务函数
void ESP32_Service(void)
{
	if(ESP32_ConnectionFlag == 0)
	{
		ESP32_SerialNumber = ESP32_ReadDeviceID();
		if(ESP32_SerialNumber == ESP32_DRIVE_ID)
		{
			ESP32_ConnectionFlag = 1;
		}
	}
	else 
	{
		ESP32_ConnectionStatus = ESP32_SelectStatus();
		//已连接到服务器
		if(ESP32_ConnectionStatus == 2)
		{
			ESP32_SendNetData("Echo\n",5);
			ReceiveNetDatLenth = 0;
			while(1)
			{
				if(EX_OK == ESP32_ReceiveNetData(ReceiveNetDatBuf, ReceiveNetDatLenth))
					break;
				delay_ms(10);
			}
		}
		
	}
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
		// delay_ms(10);
		while(ESP32_HANDSHAKE_IO == 1);
		ESP32_Wait_Flag = 0;
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
		// delay_ms(10);
		while(ESP32_HANDSHAKE_IO == 1);
		ESP32_Wait_Flag = 0;
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
		// delay_ms(10);
		while(ESP32_HANDSHAKE_IO == 1);
		ESP32_Wait_Flag = 0;
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

