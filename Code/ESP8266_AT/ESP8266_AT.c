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

//接收数据回执表数组
//0:无效
//1:回执报文
//2:ESP返回数据
const ESP_CommandMessage_st ESP_ReceivingDataComparisonTable[] ={
	{"-----"               , 0,  0,             NULL              },
	{"OK"                  , 1,  1, NULL                          },
	{"+CWLAP:"             , 2,  1, ESP_CWLAP_RxMessageOperationFun },   //WiFi信息
	{"+CWJAP_CUR"          , 3,  1, NULL                          },   //连接WiFi后返回信息
	{"+STA_CONNECTED"      , 4,  1, NULL                          },   //有设备连接到softAP
	{"+STA_DISCONNECTED"   , 5,  1, NULL                          },   //有设备断开连接
	{"+DIST_STA_IP"        , 6,  2, NULL                          },   //softAP为新设备分配IP地址 
	{"WIFI CONNECTED"      , 7,  1, ESP_WifiCONNECTED_RxMessageOperationFun },   //wifi已连接
	{"WIFI GOT IP"         , 8,  2, ESP_WiFiGotIP_RxMessageOperationFun },//WiFi已为ESP分配IP
	{"ready"               , 9,  1, NULL                          },   //RST指令使用
	{"+IPD"                , 10, 2, ESP_IPD_RxMessageOperationFun },   //接受到网络数据
	{"WIFI DISCONNECT"     , 11, 2, ESP_WifiDisconnect_RxMessageOperationFun },   //wifi已断开
	{"CONNECT"             , 12, 1, ESP_CONNECT_RxMessageOperationFun },    //连接到服务器返回
	{"SEND OK"             , 13, 1, ESP_SENDOK_RxMessageOperationFun  },
	{"> "                  , 14, 1, ESP_ARROW_RxMessageOperationFun },    //发送箭头
	{"Recv "               , 15, 1, NULL  },    //提示发送
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
	//属性初始化
	ESP_Device[0].initStatus = 0;
	ESP_Device[0].connectStatus = ESPStatus_NoResponse;//连接状态 
	ESP_Device[0].sendComNumber = 0;
	ESP_Device[0].callbackTimeout = 0;
	ESP_Device[0].keepAlive = 0;
	//USART接收结构体
	ESP_Device[0].uartReceivedData.number = 0;
	ESP_Device[0].uartReceivedData.lenth = 0;
	ESP_Device[0].uartReceivedData.status = 0;
	ESP_Device[0].uartReceivedData.timeoutVal = 0;
	//UART属性
	ESP_Device[0].uartAttr.channel = 1;
	ESP_Device[0].uartAttr.baud = Baud_115200;
	ESP_Device[0].uartAttr.data = Data_8bit;
	ESP_Device[0].uartAttr.stop = Stop_1bit;
	ESP_Device[0].uartAttr.parity = Parity_None;
	ESP_Device[0].uartAttr.flowControl = FlowControl_None;
  //WiFi属性
//	ESP_Device[0].EspWifiAttr.ecn = 0xff;
	ESP_Device[0].WifiAttr.ecn = 1;
	my_strcpy(ESP_Device[0].WifiAttr.ssid, "LAPTOP-FTV1PBJJ 7782", 0);
	my_strcpy(ESP_Device[0].WifiAttr.pwd, "QWERasdf1234", 0);
	//服务器属性 
	ESP_Device[0].serverAttr.type = TCP;
	my_strcpy(ESP_Device[0].serverAttr.website, "boredgod.qicp.vip", 0); 
	ESP_Device[0].serverAttr.port = 55215;
	//函数指针
	ESP_Device[0].connectWifi = ESP_connectWifi;
	ESP_Device[0].disconnectWifi = ESP_disconnectWifi;
	ESP_Device[0].connectServer = ESP_connectServer;
	ESP_Device[0].disconnectServer = ESP_disconnectServer;
	ESP_Device[0].netReceivedFun = ESP_netReceivedFun;
	ESP_Device[0].netSendOutFun = ESP_netSendOutFun;
	ESP_Device[0].setUARTParameters = ESP_setUARTParameters;
	ESP_Device[0].selectSNTPTime = ESP_selectSNTPTime;
	
	//WiFi列表初始化
	wifiList.lenth = 0;
	
	//ESP可设置状态
	ESP_Device[0].setAttr.wifiAutoConnectEnable = 1;
	ESP_Device[0].setAttr.serverAutoConnectEnable = 1;
	
	//设置UART 
	
	//发送结构体
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
* 函数名称:ESP_Service
* 描    述:ESP服务函数
* 功    能:1.处理传入的指令，并指向下一指令
*          2.查询ESP连接状态
*          3.
* 输入参数:none
* 返回参数:none
* 当前版本:1.0.1
* 作    者:jiangshiqi
* 完成日期:2021/02/28
* ---------------------------------------------------------------------------------------------------------*
* 历史信息： 
*     <Date>    |    <Version>    |    <Author>    |    <Description>
* ---------------------------------------------------------------------------------------------------------*
*   20221/02/28 |     1.0.1       |   jiangshiqi   |     Create file                                       *
*----------------------------------------------------------------------------------------------------------*
***********************************************************************************************************/
void ESP_Service(void)
{
	int8_t res = 0;

	
	 //超时计数器累加 对于串口接收到完整一条报文 最大等待时间
	 if((ESP_Device[0].uartReceivedData.status != 2)&&(ESP_Device[0].uartReceivedData.status != 4))
	 {
	 	ESP_Device[0].uartReceivedData.timeoutVal += TaskTCBAttr[Tack_ESP].cycle;
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
	//回调超时判断 对于已经发送的指令返回正确的回执报文 最大等待时间
	if(ESP_Device[0].sendComStatus == 1)
	{
		ESP_Device[0].callbackTimeout += TaskTCBAttr[Tack_ESP].cycle;
		if(ESP_Device[0].callbackTimeout > ESP_TXDComMessageTable[ESP_Device[0].sendComNumber].timeout)
		{
			//超时执行
			ESP_SendoutTineout_operating(&ESP_Device[0]);
		}
	}
	else
	{
		ESP_Device[0].callbackTimeout = 0;
	}
	// //心跳包发送判断
	// //没有正在发送的指令 || 正在发送测试指令（AT）
	// if((ESP_Device[0].sendComStatus == 0)||(ESP_Device[0].sendComNumber == 1))
	// {
	// 	ESP_Device[0].keepAlive ++;
	// 	//到达需维持时间
	// 	if(ESP_Device[0].keepAlive > ESP_KEEPALIVE0_MAX)
	// 	{
	// 		//发送测试指令
	// 		ESP_Device[0].waitingSendComNumber = 1;
	// 	}
	// 	//超过心跳包等待时间
	// 	else if(ESP_Device[0].keepAlive > ESP_KEEPALIVE1_MAX)
	// 	{
	// 		//切换ESP状态为：ESP模块无响应
	// 		ESP_Device[0].connectStatus = ESPStatus_NoResponse;
	// 	}		
	// }
	// else
	// {
	// 		ESP_Device[0].keepAlive = 0;
	// }
	//接收到新报文
	if(ESP_Device[0].uartReceivedData.status == 4)
	{
		//接收到回调报文
		if(ESP_ReceivingDataComparisonTable[ESP_Device[0].uartReceivedData.number].type == 1)
		{
			//分拣报文并处理
			res = ESP_SortingRXData(&ESP_Device[0]);
			//判断 报文正确&&当前有发送报文等待回执&&是需要的报文
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
				//接收完毕
				switch(res)
				{
					case 0:  //接受正确 但还未接收完毕 
						break;
					case 1:  //确认接收完毕
						ESP_Device[0].sendComStatus = 0;
						break;
					default:  //接收出现错误
						ESP_Device[0].sendComStatus = 0;
						break;
				} 
			}
			else
			{
			
			}
		}
		//接收到ESP发送报文
		else if(ESP_ReceivingDataComparisonTable[ESP_Device[0].uartReceivedData.number].type == 2)
		{ 
			//分拣报文并处理
			res = ESP_SortingRXData(&ESP_Device[0]);  
			
//			ESP_Device[0].sendComStatus = 0;
//			ESP_Device[0].sendComNumber = 0; 
		}
		//错误接收
		else
		{
		
		} 
		ESP_Device[0].uartReceivedData.lenth = 0;
		ESP_Device[0].uartReceivedData.status = 2;
	}	 
	
	//状态处理
	ESP_OperationStatus(&ESP_Device[0]);
	
	//发送新指令
	//有待发送命令&&发送状态为空&&命令下标未超出
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
	//不满足发送要求时 判断待发送指令是否正确
	{
		if((sizeof(ESP_TXDComMessageTable)/sizeof(ESP_SendComFun_st)) <= ESP_Device[0].waitingSendComNumber)
		{
			ESP_Device[0].waitingSendComNumber = 0;
		}
	}
} 

/*--连接功能--*/
//wifi API函数
//查询WiFi列表
uint8_t ESP_selectWifiList(WifiList_st *wifiList_buf)
{
	wifiList_buf = &wifiList;
	return 1;
}
//连接WiFi
uint8_t ESP_connectWifi(struct ESP_cl *esp){return 1;} 
//断开WiFi
uint8_t ESP_disconnectWifi(struct ESP_cl *esp)
{
	esp->sendComNumber = 8; 
	esp->waitingSendComNumber = 0;
	
	esp->sendComStatus = ESP_TXDComMessageTable[esp->sendComNumber].type; 
	ESP_TXDComMessageTable[esp->sendComNumber].sendComFun(esp);
	return 1;
}
//服务器 API函数
//连接服务器
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
	
//断开服务器
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

//判断接收报文类型
int8_t ESP_JudgeRXDataType(struct ESP_cl *esp)
{
	int8_t res = 0;
	uint16_t i;
	if(esp->sendComNumber != 0)
	{
		for(i=0;i<ESP_RECEIVINGDATACOMPARISON_MAX;i++)
		{
			//如果接收到的标号和接收标号数组里的一项匹配
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
//分拣接收报文 
int8_t ESP_SortingRXData(struct ESP_cl *esp)
{
	int8_t res = 0; 
	
	//如果接收报文处理函数不为空
	if(ESP_ReceivingDataComparisonTable[esp->uartReceivedData.number].rxMessageOperationFun != NULL)
	{
		res = ESP_ReceivingDataComparisonTable[esp->uartReceivedData.number].rxMessageOperationFun(esp);
	}
	return res;
}

//CWLAP接收报文处理函数
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
	//如果小于4个逗号
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
		//接收WiFi.Ecn
		cwlap_data.ecn = data->data.data[index];
		if((++index) >= data->lenth) return -2;
		if((++index) >= data->lenth) return -2;
		if((++index) >= data->lenth) return -2;
		//接收Wifi.SSID
		for(i=0;(i<ESP_WIFISSID_MAX)&&(data->data.data[index] != '"');i++)
		{
			cwlap_data.ssid[i] = data->data.data[index];
			
			if((++index) >= data->lenth) return -2;
		} 
		//如果SSID长度小于设定最大存储长度
		if(data->data.data[index] == '"')
		{
			//在结尾插入'\0'结束字符
			if(i != ESP_WIFISSID_MAX)
			{				
				cwlap_data.ssid[i] = 0; 
			}	
			ssid_lenth = i;	
		}
		else
		{
			//在结尾插入"~1"作为结尾
			cwlap_data.ssid[ESP_WIFISSID_MAX-2] = '~';
			cwlap_data.ssid[ESP_WIFISSID_MAX-1] = '1';			
			//使指针指向'"'位置
			for(;data->data.data[index]!='"';)
			{
				if((++index) >= data->lenth) return -2;
			}
			ssid_lenth = ESP_WIFISSID_MAX;
		}
		if((++index) >= data->lenth) return -2;
		if((++index) >= data->lenth) return -2;
		//接收WiFi.Rssi
		//测算RSSI所占长度
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
		//信号正确性判断
		if((a == 0) ||\
			 ((data->data.data[index] == '-')&&(a == 1)) \
			)
		return -3;
		cwlap_data.rssi = StringToDec(&data->data.data[index],a);
		//指针调整到下一起始位
		for(i=0;i<(a+2);i++)
		{
			if((++index) >= data->lenth) return -2;

		}
		//接收WiFi.Mac
		for(i=0;i<6;i++)
		{
			cwlap_data.mac[0] = StringToHex(&data->data.data[index],2);
			if((++index) >= data->lenth) return -2;
			if((++index) >= data->lenth) return -2;
			if((++index) >= data->lenth) return -2;
		}
		//接收Wifi.channel 通道号
		//接收Wifi.freq_offset 
		//接收Wifi.freqcali 
		//接收Wifi.pairwise_cipher
		//接收Wifi.group_cipher
		//接收Wifi.bgn
		//接收Wifi.wps  
		
		//数据转移
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
//WIFI Connected 接收报文处理函数
int8_t ESP_WifiCONNECTED_RxMessageOperationFun(struct ESP_cl *esp)
{
	// if(esp->connectStatus <= ESPStatus_ConnectedWifi)
	// {
	// 	esp->connectStatus = ESPStatus_ConnectedWifi;
	// }
	return 0;
}

//WIFI GOT IP接收报文处理函数
int8_t ESP_WiFiGotIP_RxMessageOperationFun(struct ESP_cl *esp)
{
	if(esp->connectStatus < ESPStatus_ConnectedWifi)
	{
		esp->connectStatus = ESPStatus_ConnectedWifi;
	}
		
	return 0;
}
//IPD接收报文处理函数
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
	
	//接收长度正确
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
	//接收长度不正确
	else
	{
		esp->netReceivedData.lenth = 0;
		esp->netReceivedData.status = 0;
		res = -1;
		//错误累计功能<<<<<<<<<<<<<<<<<<<
		//接受错误次数过多 返回到ESPStatus_ConnectedWifi
	}
	return res;
}
//WIFI DISCONNECT接收报文处理函数
int8_t ESP_WifiDisconnect_RxMessageOperationFun(struct ESP_cl *esp)
{
	if(esp->connectStatus >= ESPStatus_NoWifi)
	{
		esp->connectStatus = ESPStatus_NoWifi;
	}
	return 0;
}

//CONNECT 接收报文处理函数
int8_t ESP_CONNECT_RxMessageOperationFun(struct ESP_cl *esp)
{
	if(esp->connectStatus <= ESPStatus_ConnectedTCP)
	{
		esp->connectStatus = ESPStatus_ConnectedTCP;
	}
	return 0;
}

//SEND OK 接收报文处理函数
int8_t ESP_SENDOK_RxMessageOperationFun(struct ESP_cl *esp)
{
	esp->netSendoutData.status = 0;
	return 0;
}

//发送箭头 接收报文处理函数
int8_t ESP_ARROW_RxMessageOperationFun(struct ESP_cl *esp)
{
//	esp->netSendoutData.status = 2;
	return 0;
}
//服务器断连 接收报文处理函数
int8_t ESP_CLOSED_RxMessageOperationFun(struct ESP_cl *esp)
{
	if(esp->connectStatus >= ESPStatus_ConnectedWifi)
	{
		esp->connectStatus = ESPStatus_ConnectedWifi;
	}
	return 0;
}


/*--其他功能--*/ 

//查询ESP状态
uint8_t ESP_selectESPStatus(struct ESP_cl *esp)
{
	return esp->connectStatus; 
}

//状态处理函数
void ESP_OperationStatus(struct ESP_cl *esp)
{
	switch(esp->connectStatus)
	{ 
		case ESPStatus_NoResponse: //模块无响应 
			//发送AT测试指令 在AT测试回调指令中写入判断状态
			if(esp->sendComNumber != ESP_TXDComMessageTable[1].number)
			{
				esp->waitingSendComNumber = ESP_TXDComMessageTable[1].number;
			} 
			break;
		case ESPStatus_NoInit://模块未初始化
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
		case ESPStatus_NoWifi: //未连接到WiFi
			//配置成手动连接 无操作 等待手动选择 需手动连接函数
			//配置成自动连接 判断WiFi属性是否为空 非空开始连接
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
		case ESPStatus_ConnectedWifi: //已连接到WiFi
			//配置成手动连接 无操作 等待手动选择 需手动连接函数
			//配置成自动连接 判断服务器属性是否为空 非空开始连接
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
		case ESPStatus_ConnectedTCP: //已连接到服务器 
			//呼叫服务器响应
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
		case ESPStatus_ServerResponse: //服务器已响应
			//隔段时间发送心跳包
			break;
	}
}
//wifi属性非空判断
uint8_t ESP_IS_WifiAttrNonempty(struct ESP_cl *esp)
{
	if(esp->WifiAttr.ecn != 0xff)
		return 1;
	else
		return 0;
}
//service属性非空判断
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

//设置UART参数
uint8_t ESP_setUARTParameters(struct ESP_cl *esp){return 0;}//(EspUartAttr_st *EspUartAttr);
//查询SNTP时间	
uint8_t ESP_selectSNTPTime(struct ESP_cl *esp){return 0;}//(STNPTime_st *stnpTime);
/*--收发功能--*/
//向网络发送数据函数	
int8_t ESP_netSendOutFun(struct ESP_cl *esp, char *s, uint16_t num)
{
	esp->netSendoutData.status = 1;
	esp->netSendoutData.lenth = num;
	my_strcpy(esp->netSendoutData.data, s, num); 
	
	return 0;
}
//查询网络接收函数
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

//AT指令发送函数
//AT测试
void ESP_SendCom_AT(struct ESP_cl *esp)
{
	USART_Send_Word(esp->uartAttr.channel,"AT");
	USART_Send_Enter(esp->uartAttr.channel);
}
//复位指令
void ESP_SendCom_AT_RST(struct ESP_cl *esp)
{
	USART_Send_Word(esp->uartAttr.channel,"AT+RST");
	USART_Send_Enter(esp->uartAttr.channel);
}   
//ESP初始化：关闭回显
void ESP_SendCom_ATE(struct ESP_cl *esp)
{
	USART_Send_Word(esp->uartAttr.channel,"ATE0");
	USART_Send_Enter(esp->uartAttr.channel);
}             
//睡眠指令
void ESP_SendCom_AT_SLEEP(struct ESP_cl *esp)
{
	USART_Send_Word(esp->uartAttr.channel,"AT+SLEEP=0");
	USART_Send_Enter(esp->uartAttr.channel);
}  
//ESP初始化：设置WiFi连接模式 
//3：SoftAP+Station 模式
void ESP_SendCom_AT_CWMODE_DEF(struct ESP_cl *esp)
{
	USART_Send_Word(esp->uartAttr.channel,"AT+CWMODE_DEF=3");
	USART_Send_Enter(esp->uartAttr.channel);
}
//扫描AP
void ESP_SendCom_AT_CWLAP(struct ESP_cl *esp)
{
	USART_Send_Word(esp->uartAttr.channel,"AT+CWLAP=,,,1,,");
	USART_Send_Enter(esp->uartAttr.channel);
	wifiList.lenth = 0;
}        
//连接AP（临时）
//AT+CWJAP_CUR="abc","0123456789","ca:d7:19:d8:a6:44"
void ESP_SendCom_AT_CWJAP_CUR(struct ESP_cl *esp)
{
	//是否有WiFi存在
	if(esp->WifiAttr.ecn == 0xff)
		return;
	USART_Send_Word(esp->uartAttr.channel,"AT+CWJAP_CUR=\"");
	USART_Send_Word(esp->uartAttr.channel,esp->WifiAttr.ssid);
	USART_Send_Word(esp->uartAttr.channel,"\",\"");
	USART_Send_Word(esp->uartAttr.channel,esp->WifiAttr.pwd); 
	//发送Mac地址
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
//断开AP连接
void ESP_SendCom_AT_CWQAP(struct ESP_cl *esp)
{
	USART_Send_Word(esp->uartAttr.channel,"AT+CWQAP");
	USART_Send_Enter(esp->uartAttr.channel);
}        
//建立TCP连接
void ESP_SendCom_AT_CIPSTART(struct ESP_cl *esp)
{
	//是否有服务器存在 
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
//发送网络数据
void ESP_SendCom_AT_CIPSEND(struct ESP_cl *esp)
{
	USART_Send_Word(esp->uartAttr.channel,"AT+CIPSEND=");
	USART_Send_Int(esp->uartAttr.channel, esp->netSendoutData.lenth);
	USART_Send_Enter(esp->uartAttr.channel);
}
//断开TCP传输
void ESP_SendCom_AT_CIPCLOSE(struct ESP_cl *esp)
{
	USART_Send_Word(esp->uartAttr.channel,"AT+CIPCLOSE");
	USART_Send_Enter(esp->uartAttr.channel);
}     
//查询SNTP时间
void ESP_SendCom_AT_CIPSNTPTIME(struct ESP_cl *esp)
{
	USART_Send_Word(esp->uartAttr.channel,"AT+CIPSNTPTIME?");
	USART_Send_Enter(esp->uartAttr.channel);	
}  
//发送网络数据
void ESP_SendCom_SENDOUT(struct ESP_cl *esp)
{
	USART_Send_Word_Lenth(esp->uartAttr.channel,esp->netSendoutData.data,esp->netSendoutData.lenth);
}

//回调函数
//AT测试指令 回调
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
//复位指令 回调
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
//ESP初始化：关闭回显 回调
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
//进入睡眠模式 回调
int8_t ESP_SendCom_AT_SLEEP_Callback(struct ESP_cl *esp){return 1;}   
//ESP初始化：设置WiFi连接模式 回调
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
//查询WiFi列表回调
int8_t ESP_SendCom_AT_CWLAP_Callback(struct ESP_cl *esp)
{
	if(esp->uartReceivedData.number == ESP_TXDComMessageTable[esp->sendComNumber].receivingType)
	{
		//接收WiFi列表
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
//连接WiFi回调
int8_t ESP_SendCom_AT_CWJAP_CUR_Callback(struct ESP_cl *esp)
{
	if(esp->uartReceivedData.number == ESP_TXDComMessageTable[esp->sendComNumber].receivingType)
	{ 
    //连接过程中的其他信息
//		WIFI CONNECTED
//		WIFI GOT IP
		
		return 0;
	}
	else if(esp->uartReceivedData.number == 1)
	{
		//状态变更：已连接到WiFi
		//改为接收到 WiFi GOT IP时认为已连接到WiFi
//		esp->connectStatus = ESPStatus_ConnectedWifi;
		return 1;
	}
	else
	{
		return -1;
	}
}
//断开WiFi回调
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
//建立TCP连接回调
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
//关闭服务器
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

//wifi属性复制
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

