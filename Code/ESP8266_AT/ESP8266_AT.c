#include "ESP8266_AT.h"
#include "API.h"
#include "Toolkit.h"

struct ESP_cl ESP_Device[1]; 
WifiList_st wifiList;

const ESP_SendComFun_st ESP_TXDComMessageTable[] = {
	{NULL,                             0 , 0 ,  0 ,/*"-----"*/             3000,          NULL},
	{ESP_SendCom_AT,                   1 , 1 ,  1 ,/*"OK"*/                3000,     ESP_SendCom_AT_Callback},
	{ESP_SendCom_AT_RST,               2 , 2 ,  9 ,/*"ready"*/             3000,     ESP_SendCom_AT_RST_Callback},
	{ESP_SendCom_ATE,                  3 , 1 ,  1 ,/*"-----"*/             3000,     ESP_SendCom_ATE_Callback},
	{ESP_SendCom_AT_SLEEP,             4 , 0 ,  0 ,/*"-----"*/             3000,     ESP_SendCom_AT_SLEEP_Callback},
	{ESP_SendCom_AT_CWMODE_DEF,        5 , 1 ,  1 ,/*"OK"*/                3000,     ESP_SendCom_AT_CWMODE_DEF_Callback},
	{ESP_SendCom_AT_CWLAP,             6 , 2 ,  2 ,/*"+CWLAP:"*/           3000,     ESP_SendCom_AT_CWLAP_Callback},
	{ESP_SendCom_AT_CWJAP_CUR,         7 , 2 ,  8 ,/*"WIFI GOT IP"*/      15000,     ESP_SendCom_AT_CWJAP_CUR_Callback},
	{ESP_SendCom_AT_CWQAP,             8 , 1 ,  1 ,/*"OK"*/                3000,     ESP_SendCom_AT_CWQAP_Callback},
	{ESP_SendCom_AT_CIPSTART,          9 , 1 ,  12,/*"CONNECT"*/           3000,     ESP_SendCom_AT_CIPSTART_Callback},
	{ESP_SendCom_AT_CIPSEND,          10 , 1 ,  14,/*"> "*/                3000,     ESP_SendCom_AT_CIPSEND_Callback},
	{ESP_SendCom_AT_CIPCLOSE,         11 , 1 ,  1 ,/*"OK"*/                3000,     ESP_SendCom_AT_CIPCLOSE_Callback},
	{ESP_SendCom_AT_CIPSNTPTIME,      12 , 1 ,  1 ,/*"OK"*/                3000,     ESP_SendCom_AT_CIPSNTPTIME_Callback},
	{ESP_SendCom_SENDOUT,             13 , 1 ,  13,/*"SEND OK"*/           3000,     ESP_SendCom_SENDOUT_Callback},
};

//�������ݻ�ִ������
//0:��Ч
//1:��ִ����
//2:ESP��������
const ESP_CommandMessage_st ESP_ReceivingDataComparisonTable[] ={
	{"-----"               , 0,  0,             NULL              },
	{"OK"                  , 1,  1, NULL                          },
	{"+CWLAP:"             , 2,  1, ESP_CWLAP_RxMessageOperationFun },   //WiFi��Ϣ
	{"+CWJAP_CUR"          , 3,  1, NULL                          },   //����WiFi�󷵻���Ϣ
	{"+STA_CONNECTED"      , 4,  1, NULL                          },   //���豸���ӵ�softAP
	{"+STA_DISCONNECTED"   , 5,  1, NULL                          },   //���豸�Ͽ�����
	{"+DIST_STA_IP"        , 6,  2, NULL                          },   //softAPΪ���豸����IP��ַ 
	{"WIFI CONNECTED"      , 7,  1, ESP_WifiCONNECTED_RxMessageOperationFun },   //wifi������
	{"WIFI GOT IP"         , 8,  2, ESP_WiFiGotIP_RxMessageOperationFun },//WiFi��ΪESP����IP
	{"ready"               , 9,  1, NULL                          },   //RSTָ��ʹ��
	{"+IPD"                , 10, 2, ESP_IPD_RxMessageOperationFun },   //���ܵ���������
	{"WIFI DISCONNECT"     , 11, 2, ESP_WifiDisconnect_RxMessageOperationFun },   //wifi�ѶϿ�
	{"CONNECT"             , 12, 1, ESP_CONNECT_RxMessageOperationFun },    //���ӵ�����������
	{"SEND OK"             , 13, 1, ESP_SENDOK_RxMessageOperationFun  },
	{"> "                  , 14, 1, ESP_ARROW_RxMessageOperationFun },    //���ͼ�ͷ
	{"Recv "               , 15, 1, NULL  },    //��ʾ����
	{"CLOSED"              , 16, 2, ESP_CLOSED_RxMessageOperationFun },
	{"link is not valid"   , 17, 2, ESP_CLOSED_RxMessageOperationFun },
	{"ALREADY CONNECTED"   , 18, 2, ESP_CONNECT_RxMessageOperationFun },
	{"OK" , 20, 1, NULL                         },
	{"OK" , 21, 1, NULL                         },
	{"OK" , 22, 1, NULL                         },
	{"OK" , 23, 1, NULL                         },
	{"OK" , 24, 1, NULL                         },
	{"OK" , 25, 1, NULL                         },
	{"OK" , 26, 1, NULL                         },
	{"OK" , 27, 1, NULL                         },
	{"OK" , 28, 1, NULL                         },
	{"OK" , 29, 1, NULL                         },  
};	

void ESP_Init(void)
{
	//���Գ�ʼ��
	ESP_Device[0].initStatus = 0;
	ESP_Device[0].connectStatus = ESPStatus_NoResponse;//����״̬ 
	ESP_Device[0].sendComNumber = 0;
	ESP_Device[0].callbackTimeout = 0;
	ESP_Device[0].keepAlive = 0;
	//USART���սṹ��
	ESP_Device[0].uartReceivedData.number = 0;
	ESP_Device[0].uartReceivedData.lenth = 0;
	ESP_Device[0].uartReceivedData.status = 0;
	ESP_Device[0].uartReceivedData.timeoutVal = 0;
	//UART����
	ESP_Device[0].uartAttr.channel = 1;
	ESP_Device[0].uartAttr.baud = Baud_115200;
	ESP_Device[0].uartAttr.data = Data_8bit;
	ESP_Device[0].uartAttr.stop = Stop_1bit;
	ESP_Device[0].uartAttr.parity = Parity_None;
	ESP_Device[0].uartAttr.flowControl = FlowControl_None;
  //WiFi����
//	ESP_Device[0].EspWifiAttr.ecn = 0xff;
	ESP_Device[0].WifiAttr.ecn = 1;
	my_strcpy(ESP_Device[0].WifiAttr.ssid, "LAPTOP-FTV1PBJJ 7782", 0);
	my_strcpy(ESP_Device[0].WifiAttr.pwd, "QWERasdf1234", 0);
	//���������� 
	ESP_Device[0].serverAttr.type = TCP;
	my_strcpy(ESP_Device[0].serverAttr.website, "boredgod.qicp.vip", 0); 
	ESP_Device[0].serverAttr.port = 55215;
	//����ָ��
	ESP_Device[0].connectWifi = ESP_connectWifi;
	ESP_Device[0].disconnectWifi = ESP_disconnectWifi;
	ESP_Device[0].connectServer = ESP_connectServer;
	ESP_Device[0].disconnectServer = ESP_disconnectServer;
	ESP_Device[0].netReceivedFun = ESP_netReceivedFun;
	ESP_Device[0].netSendOutFun = ESP_netSendOutFun;
	ESP_Device[0].setUARTParameters = ESP_setUARTParameters;
	ESP_Device[0].selectSNTPTime = ESP_selectSNTPTime;
	
	//WiFi�б��ʼ��
	wifiList.lenth = 0;
	
	//ESP������״̬
	ESP_Device[0].setAttr.wifiAutoConnectEnable = 1;
	ESP_Device[0].setAttr.serverAutoConnectEnable = 1;
	
	//����UART 
	
	//���ͽṹ��
	ESP_Device[0].netSendoutData.status = 0;
	ESP_Device[0].netSendoutData.lenth = 0; 
	
	
}

void ESP_SendoutTineout_operating(struct ESP_cl *esp)
{
	esp->callbackTimeout = 0;
	esp->sendComStatus = 0;
	esp->sendComNumber = 0;
	esp->waitingSendComNumber = 0;
}

/***********************************************************************************************************
* ��������:ESP_Service
* ��    ��:ESP������
* ��    ��:1.�������ָ���ָ����һָ��
*          2.��ѯESP����״̬
*          3.
* �������:none
* ���ز���:none
* ��ǰ�汾:1.0.1
* ��    ��:jiangshiqi
* �������:2021/02/28
* ---------------------------------------------------------------------------------------------------------*
* ��ʷ��Ϣ�� 
*     <Date>    |    <Version>    |    <Author>    |    <Description>
* ---------------------------------------------------------------------------------------------------------*
*   20221/02/28 |     1.0.1       |   jiangshiqi   |     Create file                                       *
*----------------------------------------------------------------------------------------------------------*
***********************************************************************************************************/
void ESP_Service(void)
{
	int8_t res = 0;

	
	 //��ʱ�������ۼ� ���ڴ��ڽ��յ�����һ������ ���ȴ�ʱ��
	 if((ESP_Device[0].uartReceivedData.status != 2)&&(ESP_Device[0].uartReceivedData.status != 4))
	 {
	 	ESP_Device[0].uartReceivedData.timeoutVal += TaskTCBAttr[Tack_ESP].cyclel;
	 	if(ESP_Device[0].uartReceivedData.timeoutVal > 1000)
	 	{
	 		ESP_Device[0].uartReceivedData.timeoutVal = 0;
	 		ESP_Device[0].uartReceivedData.status = 2;
	 		ESP_Device[0].uartReceivedData.lenth = 0;
	 	}
	 }
	 else
	 {
	 	ESP_Device[0].uartReceivedData.timeoutVal = 0;
	 }
	//�ص���ʱ�ж� �����Ѿ����͵�ָ�����ȷ�Ļ�ִ���� ���ȴ�ʱ��
	if(ESP_Device[0].sendComStatus == 1)
	{
		ESP_Device[0].callbackTimeout += TaskTCBAttr[Tack_ESP].cyclel;
		if(ESP_Device[0].callbackTimeout > ESP_TXDComMessageTable[ESP_Device[0].sendComNumber].timeout)
		{
			//��ʱִ��
			ESP_SendoutTineout_operating(&ESP_Device[0]);
		}
	}
	else
	{
		ESP_Device[0].callbackTimeout = 0;
	}
	// //�����������ж�
	// //û�����ڷ��͵�ָ�� || ���ڷ��Ͳ���ָ�AT��
	// if((ESP_Device[0].sendComStatus == 0)||(ESP_Device[0].sendComNumber == 1))
	// {
	// 	ESP_Device[0].keepAlive ++;
	// 	//������ά��ʱ��
	// 	if(ESP_Device[0].keepAlive > ESP_KEEPALIVE0_MAX)
	// 	{
	// 		//���Ͳ���ָ��
	// 		ESP_Device[0].waitingSendComNumber = 1;
	// 	}
	// 	//�����������ȴ�ʱ��
	// 	else if(ESP_Device[0].keepAlive > ESP_KEEPALIVE1_MAX)
	// 	{
	// 		//�л�ESP״̬Ϊ��ESPģ������Ӧ
	// 		ESP_Device[0].connectStatus = ESPStatus_NoResponse;
	// 	}		
	// }
	// else
	// {
	// 		ESP_Device[0].keepAlive = 0;
	// }
	//���յ��±���
	if(ESP_Device[0].uartReceivedData.status == 4)
	{
		//���յ��ص�����
		if(ESP_ReceivingDataComparisonTable[ESP_Device[0].uartReceivedData.number].type == 1)
		{
			//�ּ��Ĳ�����
			res = ESP_SortingRXData(&ESP_Device[0]);
			//�ж� ������ȷ&&��ǰ�з��ͱ��ĵȴ���ִ&&����Ҫ�ı���
			if((res == 0)&& \
				 (ESP_Device[0].sendComStatus != 0)&& \
			   (((ESP_TXDComMessageTable[ESP_Device[0].sendComNumber].type == 2)&&(ESP_Device[0].uartReceivedData.number == 1)) ||\
				 (ESP_TXDComMessageTable[ESP_Device[0].sendComNumber].receivingType == ESP_Device[0].uartReceivedData.number))
			)
			{
				if(ESP_TXDComMessageTable[ESP_Device[0].sendComNumber].sendComCallback != NULL)
				{
					res = ESP_TXDComMessageTable[ESP_Device[0].sendComNumber].sendComCallback(&ESP_Device[0]); 
				}
				else
				{
					res = -1;
				}
				//�������
				switch(res)
				{
					case 0:  //������ȷ ����δ������� 
						break;
					case 1:  //ȷ�Ͻ������
						ESP_Device[0].sendComStatus = 0;
						break;
					default:  //���ճ��ִ���
						ESP_Device[0].sendComStatus = 0;
						break;
				} 
			}
			else
			{
			
			}
		}
		//���յ�ESP���ͱ���
		else if(ESP_ReceivingDataComparisonTable[ESP_Device[0].uartReceivedData.number].type == 2)
		{ 
			//�ּ��Ĳ�����
			res = ESP_SortingRXData(&ESP_Device[0]);  
			
//			ESP_Device[0].sendComStatus = 0;
//			ESP_Device[0].sendComNumber = 0; 
		}
		//�������
		else
		{
		
		} 
		ESP_Device[0].uartReceivedData.lenth = 0;
		ESP_Device[0].uartReceivedData.status = 2;
	}	 
	
	//״̬����
	ESP_OperationStatus(&ESP_Device[0]);
	
	//������ָ��
	//�д���������&&����״̬Ϊ��&&�����±�δ����
	if((ESP_Device[0].waitingSendComNumber != 0) && \
		 (ESP_Device[0].sendComStatus == 0) && \
	   ((sizeof(ESP_TXDComMessageTable)/sizeof(ESP_SendComFun_st)) > ESP_Device[0].waitingSendComNumber) \
		)
	{
		ESP_Device[0].sendComNumber = ESP_Device[0].waitingSendComNumber; 
		ESP_Device[0].waitingSendComNumber = 0;
	  ESP_Device[0].sendComStatus = ESP_TXDComMessageTable[ESP_Device[0].sendComNumber].type; 
		ESP_TXDComMessageTable[ESP_Device[0].sendComNumber].sendComFun(&ESP_Device[0]);
	}
	else
	//�����㷢��Ҫ��ʱ �жϴ�����ָ���Ƿ���ȷ
	{
		if((sizeof(ESP_TXDComMessageTable)/sizeof(ESP_SendComFun_st)) <= ESP_Device[0].waitingSendComNumber)
		{
			ESP_Device[0].waitingSendComNumber = 0;
		}
	}
} 

/*--���ӹ���--*/
//wifi API����
//��ѯWiFi�б�
uint8_t ESP_selectWifiList(WifiList_st *wifiList_buf)
{
	wifiList_buf = &wifiList;
	return 1;
}
//����WiFi
uint8_t ESP_connectWifi(struct ESP_cl *esp){return 1;} 
//�Ͽ�WiFi
uint8_t ESP_disconnectWifi(struct ESP_cl *esp)
{
	esp->sendComNumber = 8; 
	esp->waitingSendComNumber = 0;
	
	esp->sendComStatus = ESP_TXDComMessageTable[esp->sendComNumber].type; 
	ESP_TXDComMessageTable[esp->sendComNumber].sendComFun(esp);
	return 1;
}
//������ API����
//���ӷ�����
uint8_t ESP_connectServer(struct ESP_cl *esp)
{
	uint8_t res = 0;
	if(ESP_IS_ServiceAttrNonempty(esp) == 1)
	{
		esp->sendComNumber = 9; 
		esp->waitingSendComNumber = 0; 
		
		esp->sendComStatus = ESP_TXDComMessageTable[esp->sendComNumber].type; 
		ESP_TXDComMessageTable[esp->sendComNumber].sendComFun(esp);
//		ESP_SendCom_AT_CIPSTART(esp);
		res = 1;
	}
	else
	{
		res = 0;
	}

	return res;
}
	
//�Ͽ�������
uint8_t ESP_disconnectServer(struct ESP_cl *esp)
{
	esp->connectStatus = ESPStatus_ConnectedWifi;
	esp->sendComNumber = 11; 
	esp->waitingSendComNumber = 0;  
	
	esp->sendComStatus = ESP_TXDComMessageTable[esp->sendComNumber].type; 
	ESP_TXDComMessageTable[esp->sendComNumber].sendComFun(esp);
//	ESP_SendCom_AT_CIPCLOSE(esp);
	return 1;
}

//�жϽ��ձ�������
int8_t ESP_JudgeRXDataType(struct ESP_cl *esp)
{
	int8_t res = 0;
	uint16_t i;
	if(esp->sendComNumber != 0)
	{
		for(i=0;i<ESP_RECEIVINGDATACOMPARISON_MAX;i++)
		{
			//������յ��ı�źͽ��ձ���������һ��ƥ��
			if(my_Memcmp(esp->uartReceivedData.data.data,ESP_ReceivingDataComparisonTable[i].str,my_strlen(ESP_ReceivingDataComparisonTable[i].str)) == EX_OK)
			{
				esp->uartReceivedData.number = i;
				res = 0;
				break;
			}   
		}
		if(i == ESP_RECEIVINGDATACOMPARISON_MAX)
		{
			esp->uartReceivedData.number = 0;
			res = -1;
		}
	} 
	return res;
} 
//�ּ���ձ��� 
int8_t ESP_SortingRXData(struct ESP_cl *esp)
{
	int8_t res = 0; 
	
	//������ձ��Ĵ�������Ϊ��
	if(ESP_ReceivingDataComparisonTable[esp->uartReceivedData.number].rxMessageOperationFun != NULL)
	{
		res = ESP_ReceivingDataComparisonTable[esp->uartReceivedData.number].rxMessageOperationFun(esp);
	}
	return res;
}

//CWLAP���ձ��Ĵ�����
int8_t ESP_CWLAP_RxMessageOperationFun(struct ESP_cl *esp)
{
	ESP_UartReceived_st *data;
	uint8_t res = 0;
	uint16_t i,index;
	uint8_t ssid_lenth=0;
	uint8_t a;
	WifiAttr_st cwlap_data;
//	char *c;
	
	data = &esp->uartReceivedData;
	
	for(a=0,i=0;i<data->lenth;i++)
	{
		if(data->data.data[i] == ',')
			a++;
	} 
	//���С��4������
	if(a < 4)
		return -1;
	
	if((data->data.data[0] == '+') && \
     (data->data.data[1] == 'C') && \
     (data->data.data[2] == 'W') && \
     (data->data.data[3] == 'L') && \
     (data->data.data[4] == 'A') && \
     (data->data.data[5] == 'P') && \
		 (data->data.data[6] == ':') && \
     (data->data.data[7] == '(')    \
	)
	{
		index = 8;
		//����WiFi.Ecn
		cwlap_data.ecn = data->data.data[index];
		if((++index) >= data->lenth) return -2;
		if((++index) >= data->lenth) return -2;
		if((++index) >= data->lenth) return -2;
		//����Wifi.SSID
		for(i=0;(i<ESP_WIFISSID_MAX)&&(data->data.data[index] != '"');i++)
		{
			cwlap_data.ssid[i] = data->data.data[index];
			
			if((++index) >= data->lenth) return -2;
		} 
		//���SSID����С���趨���洢����
		if(data->data.data[index] == '"')
		{
			//�ڽ�β����'\0'�����ַ�
			if(i != ESP_WIFISSID_MAX)
			{				
				cwlap_data.ssid[i] = 0; 
			}	
			ssid_lenth = i;	
		}
		else
		{
			//�ڽ�β����"~1"��Ϊ��β
			cwlap_data.ssid[ESP_WIFISSID_MAX-2] = '~';
			cwlap_data.ssid[ESP_WIFISSID_MAX-1] = '1';			
			//ʹָ��ָ��'"'λ��
			for(;data->data.data[index]!='"';)
			{
				if((++index) >= data->lenth) return -2;
			}
			ssid_lenth = ESP_WIFISSID_MAX;
		}
		if((++index) >= data->lenth) return -2;
		if((++index) >= data->lenth) return -2;
		//����WiFi.Rssi
		//����RSSI��ռ����
		a = 0;
		if(data->data.data[index] != ',')
		{
			a++;
			if(data->data.data[index +1] != ',')
			{
				a++;
				if(data->data.data[index +2] != ',')
				{
					a++;
					if(data->data.data[index +3] != ',')
					{
						a++;
						if(data->data.data[index +4] != ',')
							return -3;
					}					
				}
			}
		}
		//�ź���ȷ���ж�
		if((a == 0) ||\
			 ((data->data.data[index] == '-')&&(a == 1)) \
			)
		return -3;
		cwlap_data.rssi = StringToDec(&data->data.data[index],a);
		//ָ���������һ��ʼλ
		for(i=0;i<(a+2);i++)
		{
			if((++index) >= data->lenth) return -2;

		}
		//����WiFi.Mac
		for(i=0;i<6;i++)
		{
			cwlap_data.mac[0] = StringToHex(&data->data.data[index],2);
			if((++index) >= data->lenth) return -2;
			if((++index) >= data->lenth) return -2;
			if((++index) >= data->lenth) return -2;
		}
		//����Wifi.channel ͨ����
		//����Wifi.freq_offset 
		//����Wifi.freqcali 
		//����Wifi.pairwise_cipher
		//����Wifi.group_cipher
		//����Wifi.bgn
		//����Wifi.wps  
		
		//����ת��
		data->data.cwlapData.ecn  = cwlap_data.ecn;
		for(i=0;i<ssid_lenth;i++)
		{
			data->data.cwlapData.ssid[i] = cwlap_data.ssid[i];
		} 
		data->data.cwlapData.rssi = cwlap_data.rssi;
		for(i=0;i<6;i++)
		{
			data->data.cwlapData.mac[i]  = cwlap_data.mac[i];
		}
		res = 0;
	}
	return res;
}
//WIFI Connected ���ձ��Ĵ�����
int8_t ESP_WifiCONNECTED_RxMessageOperationFun(struct ESP_cl *esp)
{
	// if(esp->connectStatus <= ESPStatus_ConnectedWifi)
	// {
	// 	esp->connectStatus = ESPStatus_ConnectedWifi;
	// }
	return 0;
}

//WIFI GOT IP���ձ��Ĵ�����
int8_t ESP_WiFiGotIP_RxMessageOperationFun(struct ESP_cl *esp)
{
	if(esp->connectStatus < ESPStatus_ConnectedWifi)
	{
		esp->connectStatus = ESPStatus_ConnectedWifi;
	}
		
	return 0;
}
//IPD���ձ��Ĵ�����
int8_t ESP_IPD_RxMessageOperationFun(struct ESP_cl *esp)
{
	int8_t res;
	uint16_t i,a;
	uint16_t num;

	num = 0;	
	for(i=5;i<16;i++)
	{
		if(esp->uartReceivedData.data.data[i] == ':')
			break;
		
		num *= 10;
		num += esp->uartReceivedData.data.data[i]-0x30;
	}
	
	//���ճ�����ȷ
	if((num != 0)&&(num < ESP_SENDOUT_MAX))
	{
		a = i+1;
		for(i=0;i<num;i++)
		{
			esp->netReceivedData.data[i] = esp->uartReceivedData.data.data[i+a];
		}
		esp->netReceivedData.lenth = num;
		esp->netReceivedData.status = 1;
		res = 0;  
	}
	//���ճ��Ȳ���ȷ
	else
	{
		esp->netReceivedData.lenth = 0;
		esp->netReceivedData.status = 0;
		res = -1;
		//�����ۼƹ���<<<<<<<<<<<<<<<<<<<
		//���ܴ���������� ���ص�ESPStatus_ConnectedWifi
	}
	return res;
}
//WIFI DISCONNECT���ձ��Ĵ�����
int8_t ESP_WifiDisconnect_RxMessageOperationFun(struct ESP_cl *esp)
{
	if(esp->connectStatus >= ESPStatus_NoWifi)
	{
		esp->connectStatus = ESPStatus_NoWifi;
	}
	return 0;
}

//CONNECT ���ձ��Ĵ�����
int8_t ESP_CONNECT_RxMessageOperationFun(struct ESP_cl *esp)
{
	if(esp->connectStatus <= ESPStatus_ConnectedTCP)
	{
		esp->connectStatus = ESPStatus_ConnectedTCP;
	}
	return 0;
}

//SEND OK ���ձ��Ĵ�����
int8_t ESP_SENDOK_RxMessageOperationFun(struct ESP_cl *esp)
{
	esp->netSendoutData.status = 0;
	return 0;
}

//���ͼ�ͷ ���ձ��Ĵ�����
int8_t ESP_ARROW_RxMessageOperationFun(struct ESP_cl *esp)
{
//	esp->netSendoutData.status = 2;
	return 0;
}
//���������� ���ձ��Ĵ�����
int8_t ESP_CLOSED_RxMessageOperationFun(struct ESP_cl *esp)
{
	if(esp->connectStatus >= ESPStatus_ConnectedWifi)
	{
		esp->connectStatus = ESPStatus_ConnectedWifi;
	}
	return 0;
}


/*--��������--*/ 

//��ѯESP״̬
uint8_t ESP_selectESPStatus(struct ESP_cl *esp)
{
	return esp->connectStatus; 
}

//״̬������
void ESP_OperationStatus(struct ESP_cl *esp)
{
	switch(esp->connectStatus)
	{ 
		case ESPStatus_NoResponse: //ģ������Ӧ 
			//����AT����ָ�� ��AT���Իص�ָ����д���ж�״̬
			if(esp->sendComNumber != ESP_TXDComMessageTable[1].number)
			{
				esp->waitingSendComNumber = ESP_TXDComMessageTable[1].number;
			} 
			break;
		case ESPStatus_NoInit://ģ��δ��ʼ��
			if(ESP_Device[0].initStatus == 0)
			{
				if(esp->sendComNumber != ESP_TXDComMessageTable[5].number)
				{
					esp->waitingSendComNumber = ESP_TXDComMessageTable[5].number;
				} 
			}
			else if(ESP_Device[0].initStatus == 1)
			{
				if(esp->sendComNumber != ESP_TXDComMessageTable[3].number)
				{
					esp->waitingSendComNumber = ESP_TXDComMessageTable[3].number;
				} 
			}
			else if(ESP_Device[0].initStatus == 2)
			{
				esp->connectStatus = ESPStatus_NoWifi;
			}
			break;
		case ESPStatus_NoWifi: //δ���ӵ�WiFi
			//���ó��ֶ����� �޲��� �ȴ��ֶ�ѡ�� ���ֶ����Ӻ���
			//���ó��Զ����� �ж�WiFi�����Ƿ�Ϊ�� �ǿտ�ʼ����
			if(esp->setAttr.wifiAutoConnectEnable == 1)
			{
				if(ESP_IS_WifiAttrNonempty(esp))
				{
					if(esp->sendComNumber != ESP_TXDComMessageTable[7].number)
					{
						esp->waitingSendComNumber = ESP_TXDComMessageTable[7].number;
					} 
				}
			}
			break;
		case ESPStatus_ConnectedWifi: //�����ӵ�WiFi
			//���ó��ֶ����� �޲��� �ȴ��ֶ�ѡ�� ���ֶ����Ӻ���
			//���ó��Զ����� �жϷ����������Ƿ�Ϊ�� �ǿտ�ʼ����
			if(esp->setAttr.serverAutoConnectEnable == 1)
			{
				if(ESP_IS_ServiceAttrNonempty(esp))
				{
					if(esp->sendComNumber != ESP_TXDComMessageTable[9].number)
					{
						esp->waitingSendComNumber = ESP_TXDComMessageTable[9].number;
					} 
				}
			}
			break;
		case ESPStatus_ConnectedTCP: //�����ӵ������� 
			//���з�������Ӧ
			if((ESP_Device[0].netSendoutData.status == 1)&&(ESP_Device[0].netSendoutData.lenth != 0))
			{
				if(esp->sendComNumber != ESP_TXDComMessageTable[10].number)
				{
					esp->waitingSendComNumber = ESP_TXDComMessageTable[10].number;
				} 
			}
			else if(ESP_Device[0].netSendoutData.status == 2)
			{
				if(esp->sendComNumber != ESP_TXDComMessageTable[13].number)
				{
					esp->waitingSendComNumber = ESP_TXDComMessageTable[13].number;
				}  
			}
			break;
		case ESPStatus_ServerResponse: //����������Ӧ
			//����ʱ�䷢��������
			break;
	}
}
//wifi���Էǿ��ж�
uint8_t ESP_IS_WifiAttrNonempty(struct ESP_cl *esp)
{
	if(esp->WifiAttr.ecn != 0xff)
		return 1;
	else
		return 0;
}
//service���Էǿ��ж�
uint8_t ESP_IS_ServiceAttrNonempty(struct ESP_cl *esp)
{
	if(esp->serverAttr.type != ServerConnect_Null)
	{
		return 1;
	}
	else
	{
		return 0;
	} 
}

//����UART����
uint8_t ESP_setUARTParameters(struct ESP_cl *esp){return 0;}//(EspUartAttr_st *EspUartAttr);
//��ѯSNTPʱ��	
uint8_t ESP_selectSNTPTime(struct ESP_cl *esp){return 0;}//(STNPTime_st *stnpTime);
/*--�շ�����--*/
//�����緢�����ݺ���	
int8_t ESP_netSendOutFun(struct ESP_cl *esp, char *s, uint16_t num)
{
	esp->netSendoutData.status = 1;
	esp->netSendoutData.lenth = num;
	my_strcpy(esp->netSendoutData.data, s, num); 
	
	return 0;
}
//��ѯ������պ���
int8_t ESP_netReceivedFun(struct ESP_cl *esp, char *s, uint16_t *num)
{
	int8_t res = 0;

	if(esp->netReceivedData.status == 1)
	{
		*num = esp->netReceivedData.lenth;
		s = esp->netReceivedData.data;

		esp->netReceivedData.status = 2;

		res = 1; 
	}
	else
	{
		res = 0;
	}

	return res;
}	

//ATָ��ͺ���
//AT����
void ESP_SendCom_AT(struct ESP_cl *esp)
{
	USART_Send_Word(esp->uartAttr.channel,"AT");
	USART_Send_Enter(esp->uartAttr.channel);
}
//��λָ��
void ESP_SendCom_AT_RST(struct ESP_cl *esp)
{
	USART_Send_Word(esp->uartAttr.channel,"AT+RST");
	USART_Send_Enter(esp->uartAttr.channel);
}   
//ESP��ʼ�����رջ���
void ESP_SendCom_ATE(struct ESP_cl *esp)
{
	USART_Send_Word(esp->uartAttr.channel,"ATE0");
	USART_Send_Enter(esp->uartAttr.channel);
}             
//˯��ָ��
void ESP_SendCom_AT_SLEEP(struct ESP_cl *esp)
{
	USART_Send_Word(esp->uartAttr.channel,"AT+SLEEP=0");
	USART_Send_Enter(esp->uartAttr.channel);
}  
//ESP��ʼ��������WiFi����ģʽ 
//3��SoftAP+Station ģʽ
void ESP_SendCom_AT_CWMODE_DEF(struct ESP_cl *esp)
{
	USART_Send_Word(esp->uartAttr.channel,"AT+CWMODE_DEF=3");
	USART_Send_Enter(esp->uartAttr.channel);
}
//ɨ��AP
void ESP_SendCom_AT_CWLAP(struct ESP_cl *esp)
{
	USART_Send_Word(esp->uartAttr.channel,"AT+CWLAP=,,,1,,");
	USART_Send_Enter(esp->uartAttr.channel);
	wifiList.lenth = 0;
}        
//����AP����ʱ��
//AT+CWJAP_CUR="abc","0123456789","ca:d7:19:d8:a6:44"
void ESP_SendCom_AT_CWJAP_CUR(struct ESP_cl *esp)
{
	//�Ƿ���WiFi����
	if(esp->WifiAttr.ecn == 0xff)
		return;
	USART_Send_Word(esp->uartAttr.channel,"AT+CWJAP_CUR=\"");
	USART_Send_Word(esp->uartAttr.channel,esp->WifiAttr.ssid);
	USART_Send_Word(esp->uartAttr.channel,"\",\"");
	USART_Send_Word(esp->uartAttr.channel,esp->WifiAttr.pwd); 
	//����Mac��ַ
//	USART_Send_Word(esp->uartAttr.channel,"\",\""); 
//	USART_Send_Byte(esp->uartAttr.channel,esp->EspWifiAttr.mac[0] /10 +0x30);
//	USART_Send_Byte(esp->uartAttr.channel,esp->EspWifiAttr.mac[0] %10 +0x30);
//	USART_Send_Word(esp->uartAttr.channel,":");
//	USART_Send_Byte(esp->uartAttr.channel,esp->EspWifiAttr.mac[1] /10 +0x30);
//	USART_Send_Byte(esp->uartAttr.channel,esp->EspWifiAttr.mac[1] %10 +0x30);
//	USART_Send_Word(esp->uartAttr.channel,":");
//	USART_Send_Byte(esp->uartAttr.channel,esp->EspWifiAttr.mac[2] /10 +0x30);
//	USART_Send_Byte(esp->uartAttr.channel,esp->EspWifiAttr.mac[2] %10 +0x30);
//	USART_Send_Word(esp->uartAttr.channel,":");
//	USART_Send_Byte(esp->uartAttr.channel,esp->EspWifiAttr.mac[3] /10 +0x30);
//	USART_Send_Byte(esp->uartAttr.channel,esp->EspWifiAttr.mac[3] %10 +0x30);
//	USART_Send_Word(esp->uartAttr.channel,":");
//	USART_Send_Byte(esp->uartAttr.channel,esp->EspWifiAttr.mac[4] /10 +0x30);
//	USART_Send_Byte(esp->uartAttr.channel,esp->EspWifiAttr.mac[4] %10 +0x30);
//	USART_Send_Word(esp->uartAttr.channel,":");
//	USART_Send_Byte(esp->uartAttr.channel,esp->EspWifiAttr.mac[5] /10 +0x30);
//	USART_Send_Byte(esp->uartAttr.channel,esp->EspWifiAttr.mac[5] %10 +0x30);
//	USART_Send_Word(esp->uartAttr.channel,":"); 
	USART_Send_Byte(esp->uartAttr.channel,'\"'); 
	USART_Send_Enter(esp->uartAttr.channel);
}   	
//�Ͽ�AP����
void ESP_SendCom_AT_CWQAP(struct ESP_cl *esp)
{
	USART_Send_Word(esp->uartAttr.channel,"AT+CWQAP");
	USART_Send_Enter(esp->uartAttr.channel);
}        
//����TCP����
void ESP_SendCom_AT_CIPSTART(struct ESP_cl *esp)
{
	//�Ƿ��з��������� 
	switch(esp->serverAttr.type)
	{ 
		case ServerConnect_Null:
			return; 
		case TCP:
			USART_Send_Word(esp->uartAttr.channel,"AT+CIPSTART=\"TCP");
		break;
		case UDP:
			USART_Send_Word(esp->uartAttr.channel,"AT+CIPSTART=\"UDP");
		break;
		case SSL:
			USART_Send_Word(esp->uartAttr.channel,"AT+CIPSTART=\"SSL");
		break;
		
	}
	USART_Send_Word(esp->uartAttr.channel,"\",\"");
	USART_Send_Word(esp->uartAttr.channel,esp->serverAttr.website);
	USART_Send_Word(esp->uartAttr.channel,"\",");
	USART_Send_Int_Num(esp->uartAttr.channel,esp->serverAttr.port,5);  
	
	USART_Send_Enter(esp->uartAttr.channel);
}     
//������������
void ESP_SendCom_AT_CIPSEND(struct ESP_cl *esp)
{
	USART_Send_Word(esp->uartAttr.channel,"AT+CIPSEND=");
	USART_Send_Int(esp->uartAttr.channel, esp->netSendoutData.lenth);
	USART_Send_Enter(esp->uartAttr.channel);
}
//�Ͽ�TCP����
void ESP_SendCom_AT_CIPCLOSE(struct ESP_cl *esp)
{
	USART_Send_Word(esp->uartAttr.channel,"AT+CIPCLOSE");
	USART_Send_Enter(esp->uartAttr.channel);
}     
//��ѯSNTPʱ��
void ESP_SendCom_AT_CIPSNTPTIME(struct ESP_cl *esp)
{
	USART_Send_Word(esp->uartAttr.channel,"AT+CIPSNTPTIME?");
	USART_Send_Enter(esp->uartAttr.channel);	
}  
//������������
void ESP_SendCom_SENDOUT(struct ESP_cl *esp)
{
	USART_Send_Word_Lenth(esp->uartAttr.channel,esp->netSendoutData.data,esp->netSendoutData.lenth);
}

//�ص�����
//AT����ָ�� �ص�
int8_t ESP_SendCom_AT_Callback(struct ESP_cl *esp)
{
	if(esp->uartReceivedData.number == ESP_TXDComMessageTable[esp->sendComNumber].receivingType)
	{
		if(esp->connectStatus == ESPStatus_NoResponse)
			esp->connectStatus = ESPStatus_NoInit;
		return 1;
	}
	else
	{
		return -1;
	}
}
//��λָ�� �ص�
int8_t ESP_SendCom_AT_RST_Callback(struct ESP_cl *esp)
{	
	if(esp->uartReceivedData.number == ESP_TXDComMessageTable[esp->sendComNumber].receivingType)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}
//ESP��ʼ�����رջ��� �ص�
int8_t ESP_SendCom_ATE_Callback(struct ESP_cl *esp)
{
	if(esp->uartReceivedData.number == ESP_TXDComMessageTable[esp->sendComNumber].receivingType)
	{
		esp->initStatus ++;
		return 1;
	}
	else
	{
		return -1;
	}
}        
//����˯��ģʽ �ص�
int8_t ESP_SendCom_AT_SLEEP_Callback(struct ESP_cl *esp){return 1;}   
//ESP��ʼ��������WiFi����ģʽ �ص�
int8_t ESP_SendCom_AT_CWMODE_DEF_Callback(struct ESP_cl *esp)
{
	if(esp->uartReceivedData.number == ESP_TXDComMessageTable[esp->sendComNumber].receivingType)
	{ 
		esp->initStatus ++;
		return 1;
	}
	else
	{
		return -1;
	}
}
//��ѯWiFi�б�ص�
int8_t ESP_SendCom_AT_CWLAP_Callback(struct ESP_cl *esp)
{
	if(esp->uartReceivedData.number == ESP_TXDComMessageTable[esp->sendComNumber].receivingType)
	{
		//����WiFi�б�
		if(wifiList.lenth < ESP_WIFILIST_MAX)
		{ 
			ESP_WifiAttrCopy(&wifiList.attr[wifiList.lenth], & esp->uartReceivedData.data.cwlapData);
			wifiList.lenth ++;
		}
		
		return 0;
	}
	else if(esp->uartReceivedData.number == 1)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}	
//����WiFi�ص�
int8_t ESP_SendCom_AT_CWJAP_CUR_Callback(struct ESP_cl *esp)
{
	if(esp->uartReceivedData.number == ESP_TXDComMessageTable[esp->sendComNumber].receivingType)
	{ 
    //���ӹ����е�������Ϣ
//		WIFI CONNECTED
//		WIFI GOT IP
		
		return 0;
	}
	else if(esp->uartReceivedData.number == 1)
	{
		//״̬����������ӵ�WiFi
		//��Ϊ���յ� WiFi GOT IPʱ��Ϊ�����ӵ�WiFi
//		esp->connectStatus = ESPStatus_ConnectedWifi;
		return 1;
	}
	else
	{
		return -1;
	}
}
//�Ͽ�WiFi�ص�
int8_t ESP_SendCom_AT_CWQAP_Callback(struct ESP_cl *esp)
{
	if(esp->uartReceivedData.number == ESP_TXDComMessageTable[esp->sendComNumber].receivingType)
	{ 
		return 1;
	}
	else
	{
		return -1;
	}
}        
//����TCP���ӻص�
int8_t ESP_SendCom_AT_CIPSTART_Callback(struct ESP_cl *esp)
{
	if(esp->uartReceivedData.number == ESP_TXDComMessageTable[esp->sendComNumber].receivingType)
	{  	
		return 1;
	} 
	else
	{
		return -1;
	}
}     
int8_t ESP_SendCom_AT_CIPSEND_Callback(struct ESP_cl *esp)
{
	if(esp->uartReceivedData.number == ESP_TXDComMessageTable[esp->sendComNumber].receivingType)
	{  	
		esp->netSendoutData.status = 2;
		return 1;
	} 
	else
	{
		return -1;
	}
}      
//�رշ�����
int8_t ESP_SendCom_AT_CIPCLOSE_Callback(struct ESP_cl *esp)
{
	if(esp->uartReceivedData.number == ESP_TXDComMessageTable[esp->sendComNumber].receivingType)
	{  	
//		esp->connectStatus = ESPStatus_ConnectedWifi;
		return 1;
	} 
	else
	{
		return -1;
	}
}    
int8_t ESP_SendCom_AT_CIPSNTPTIME_Callback(struct ESP_cl *esp){return 0;}  
int8_t ESP_SendCom_SENDOUT_Callback(struct ESP_cl *esp)
{
	if(esp->uartReceivedData.number == ESP_TXDComMessageTable[esp->sendComNumber].receivingType)
	{  	
		return 1;
	} 
	else
	{
		return -1;
	}
}   

//wifi���Ը���
int8_t ESP_WifiAttrCopy(WifiAttr_st *wifiAttr1, WifiAttr_st *wifiAttr2)
{
	uint8_t i;
	wifiAttr1->ecn = wifiAttr2->ecn;
	for(i=0;i<ESP_WIFISSID_MAX;i++)
	{ 
		wifiAttr1->ssid[i] = wifiAttr2->ssid[i];
	}
	wifiAttr1->rssi = wifiAttr2->rssi;
	wifiAttr1->mac[0] = wifiAttr2->mac[0];
	wifiAttr1->mac[1] = wifiAttr2->mac[1];
	wifiAttr1->mac[2] = wifiAttr2->mac[2];
	wifiAttr1->mac[3] = wifiAttr2->mac[3];
	wifiAttr1->mac[4] = wifiAttr2->mac[4];
	wifiAttr1->mac[5] = wifiAttr2->mac[5];
	wifiAttr1->channel = wifiAttr2->channel;
	
	return 0;
}

