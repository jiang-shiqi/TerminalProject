#ifndef __ESP8266_AT_H_ 
#define __ESP8266_AT_H_

#include "include.h" 


#define ESP_RECEIVEDDATA_MAX 200
#define ESP_RECEIVINGDATACOMPARISON_MAX 30
#define ESP_WIFILIST_MAX 30
#define ESP_WIFISSID_MAX 25
#define ESP_WIFIPSWD_MAX 20 
#define ESP_KEEPALIVE0_MAX 100
#define ESP_KEEPALIVE1_MAX 330
#define ESP_CALLBACKTIMEOUT_MAX 100
#define ESP_SENDOUT_MAX 100






//连接状态 枚举
typedef enum ConnectStatus_Type{
	ESPStatus_NoResponse,               //模块无响应
	ESPStatus_NoInit,                   //模块未初始化
	ESPStatus_NoWifi,                   //未连接到WiFi
	ESPStatus_ConnectedWifi,            //已连接到WiFi
	ESPStatus_ConnectedTCP,             //已连接到服务器
	ESPStatus_ServerResponse,           //服务器已响应
}ConnectStatus;

//服务器连接方式 枚举
typedef enum ServerConnect_Type{
	ServerConnect_Null,
	TCP,
	UDP,
	SSL,
}ServerConnect;

//UART设置参数枚举
//波特率
typedef enum EspUartBaud_en{
	Baud_110,
	Baud_9600,
	Baud_115200,
	Baud_1000000,
}EspUartBaud;
//数据位
typedef enum EspUartData_en{
	Data_5bit,
	Data_6bit,
	Data_7bit,
	Data_8bit,
}EspUartData;
//停止位
typedef enum EspUartStop_en{
	Stop_1bit,
	Stop_1_5bit,
	Stop_2bit, 
}EspUartStop;
//校验位
typedef enum EspUartParity_en{
	Parity_None,
	Parity_Odd,
	Parity_Even, 
}EspUartParity;
//流控帧
typedef enum EspUartFlowControl_en{
	FlowControl_None,
	FlowControl_RTS,
	FlowControl_CTS, 
	FlowControl_RTS_CTS, 
}EspUartFlowControl;

//时间枚举
typedef enum ESPTimeWeek_en{
	Monday = 1,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday,
}ESPTimeWeek;
typedef enum ESPTimeMonth_en{
	January = 1,
	February,
	March,
	April,
	May,
	June,
	July,
	August,
	September,
	October,
	November,
	December,
}ESPTimeMonth;




//wifi属性结构体 
//示例
//+CWLAP:(3,"LAPTOP-FTV1PBJJ 7782",-32,"4a:a4:72:73:0e:10",11,-4,0,4,4,7,1)
//+CWLAP:<ecn>,<ssid>,<rssi>,<mac>,<channel>,<freq offset>,<freqcali>,<pairwise_cipher>,<group_cipher>,<bgn>,<wps>
typedef struct {
	uint8_t ecn;	//加密方式
	char    ssid[ESP_WIFISSID_MAX];	//AP SSID
	int8_t  rssi;//信号强度
	uint8_t mac[6];//AP MAC地址
	uint8_t channel;//通道号
//	int8_t  freq_offset;//AP频偏 单位：kHz。此数值除以 2.4，可得到 ppm 值
//	int8_t  freqcali;//频偏校准值
//	uint8_t pairwise_cipher;
//	uint8_t group_cipher;
//	uint8_t bgn;
//	uint8_t wps; 
}WifiAttr_st;

typedef struct {
	WifiAttr_st attr[ESP_WIFILIST_MAX];
	uint8_t lenth;
}WifiList_st;

//服务器连接结构体
typedef struct {
	enum ServerConnect_Type type; 
	char website[50];
	uint8_t ip[4];
	uint16_t port; 
}ServerConnect_sr;
  
//UART结构体
typedef struct{
	uint8_t channel;
	enum EspUartBaud_en baud;//波特率 110-115200*40 推荐1000000 
	enum EspUartData_en data;//数据位
	enum EspUartStop_en stop;//停止位
	enum EspUartParity_en parity;//校验位
	enum EspUartFlowControl_en flowControl;//流控帧 
}EspUartAttr_st;

//wifi结构体
typedef struct {
	uint8_t ecn;                    //加密方式
	char    ssid[ESP_WIFISSID_MAX];	//AP SSID
	char    pwd[ESP_WIFIPSWD_MAX];  //AP PWD 
	int8_t  rssi;                   //信号强度
	uint8_t mac[6];                 //AP MAC地址
}EspWifiAttr_st;



//SNTP时间结构体
//+CIPSNTPTIME:Mon Feb 22 20:46:30 2021  
typedef struct{
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	enum ESPTimeWeek_en week; 
}STNPTime_st;

//ESP接收数据联合体
typedef union
{
	char data[ESP_RECEIVEDDATA_MAX];
	WifiAttr_st cwlapData;
}ESP_Received_Data_union;

//ESP接收结构体
typedef struct {
	uint8_t number;                      //接收数据类型
	uint8_t status;                      //接收状态
	uint32_t timeoutVal;                 //超时计数器
	uint16_t lenth;                      //数据长度
	ESP_Received_Data_union data;        //接收数据
}ESP_UartReceived_st;

//ESP发送结构体 
typedef struct { 
	uint8_t status;                      //发送状态 
	uint16_t lenth;                      //数据长度
	char data[ESP_SENDOUT_MAX];          //接收数据
}ESP_NetworkDataSendOut_st;

//ESP网路发送结构体 
typedef struct { 
	uint8_t status;                      //发送状态 
	uint16_t lenth;                      //数据长度
	char data[ESP_SENDOUT_MAX];          //接收数据
}ESP_NetworkDataReceived_st; 

//ESP设置属性结构体
typedef struct {
	uint8_t wifiAutoConnectEnable         : 1;  //wifi自动连接使能
	uint8_t serverAutoConnectEnable       : 1;  //服务器自动连接使能
}ESP_SetAttr_st;


//ESP类结构体
struct ESP_cl{
	uint8_t initStatus;
	uint8_t connectStatus;                    //连接状态 
	ESP_SetAttr_st setAttr;                   //可设置属性
	uint16_t waitingSendComNumber;            //等待发送类型
	uint16_t sendComNumber;                   //最后发送的命令
	uint8_t sendComStatus;                    //发送指令的状态
	uint32_t callbackTimeout;                 //回调超时时间
	uint32_t keepAlive;                       //心跳包时间
	ESP_UartReceived_st uartReceivedData;     //接收到的UART数据
	ESP_NetworkDataSendOut_st netSendoutData; //待发送的网络数据
	ESP_NetworkDataReceived_st netReceivedData;//接收到的网络数据
	EspUartAttr_st uartAttr;                  //UART属性
	EspWifiAttr_st WifiAttr;                  //WiFi属性
	ServerConnect_sr serverAttr;              //服务器属性
	STNPTime_st stnpTime;                     //STNP时间
	uint8_t (*connectWifi)(struct ESP_cl *esp);             //连接WiFi
	uint8_t (*disconnectWifi)(struct ESP_cl *esp);          //断开WiFi
	uint8_t (*connectServer)(struct ESP_cl *esp);           //连接服务器
	uint8_t (*disconnectServer)(struct ESP_cl *esp);        //断开服务器
	int8_t (*netSendOutFun)(struct ESP_cl *esp, char *s, uint16_t num);  //发送网络数据
	int8_t (*netReceivedFun)(struct ESP_cl *esp, char *s, uint16_t *num); //接收网络数据
	uint8_t (*setUARTParameters)(struct ESP_cl *esp);       //设置串口属性
	uint8_t (*selectSNTPTime)(struct ESP_cl *esp);          //查询SNTP时间
};



//接收数据回执表结构体
typedef struct {
	char *str;
	uint16_t number; 
	uint8_t type;
	int8_t (*rxMessageOperationFun)(struct ESP_cl *esp); 
}ESP_CommandMessage_st;


//AT指令发送函数
void ESP_SendCom_AT(struct ESP_cl *esp);
void ESP_SendCom_AT_RST(struct ESP_cl *esp);  
void ESP_SendCom_ATE(struct ESP_cl *esp);             	
void ESP_SendCom_AT_SLEEP(struct ESP_cl *esp);    
void ESP_SendCom_AT_CWMODE_DEF(struct ESP_cl *esp);     	
void ESP_SendCom_AT_CWLAP(struct ESP_cl *esp);         
void ESP_SendCom_AT_CWJAP_CUR(struct ESP_cl *esp);   	
void ESP_SendCom_AT_CWQAP(struct ESP_cl *esp);        
void ESP_SendCom_AT_CIPSTART(struct ESP_cl *esp);     
void ESP_SendCom_AT_CIPSEND(struct ESP_cl *esp);      
void ESP_SendCom_AT_CIPCLOSE(struct ESP_cl *esp);     
void ESP_SendCom_AT_CIPSNTPTIME(struct ESP_cl *esp);  
void ESP_SendCom_SENDOUT(struct ESP_cl *esp);   

//发送回调函数
int8_t ESP_SendCom_AT_Callback(struct ESP_cl *esp);
int8_t ESP_SendCom_AT_RST_Callback(struct ESP_cl *esp);  
int8_t ESP_SendCom_ATE_Callback(struct ESP_cl *esp);             	
int8_t ESP_SendCom_AT_SLEEP_Callback(struct ESP_cl *esp);         	
int8_t ESP_SendCom_AT_CWMODE_DEF_Callback(struct ESP_cl *esp);        	
int8_t ESP_SendCom_AT_CWLAP_Callback(struct ESP_cl *esp);        	
int8_t ESP_SendCom_AT_CWJAP_CUR_Callback(struct ESP_cl *esp);   	
int8_t ESP_SendCom_AT_CWQAP_Callback(struct ESP_cl *esp);        
int8_t ESP_SendCom_AT_CIPSTART_Callback(struct ESP_cl *esp);     
int8_t ESP_SendCom_AT_CIPSEND_Callback(struct ESP_cl *esp);      
int8_t ESP_SendCom_AT_CIPCLOSE_Callback(struct ESP_cl *esp);     
int8_t ESP_SendCom_AT_CIPSNTPTIME_Callback(struct ESP_cl *esp);  
int8_t ESP_SendCom_SENDOUT_Callback(struct ESP_cl *esp);

//接收数据回执表结构体
typedef struct {
	void (*sendComFun)(struct ESP_cl *esp);             //指令发送函数
	uint16_t number;                                    //指令序列
	uint8_t type;                                       //指令类别 1：会有单次确认返回&&直接返回不需等待 2：会有数据+单次确认返回
	uint16_t receivingType;                             //接收类别：首次返回时接到的标号
	const uint16_t timeout;                             //超时时间
	int8_t (*sendComCallback)(struct ESP_cl *esp);      //指令发送回调函数
}ESP_SendComFun_st;



//ESP函数
void ESP_Init(void);
void ESP_Service(void);

/*--连接功能--*/
//wifi API函数
uint8_t ESP_selectWifiList(WifiList_st *wifiList_buf);
uint8_t ESP_connectWifi(struct ESP_cl *esp);//(char *ssid, char *pwd);
uint8_t ESP_disconnectWifi(struct ESP_cl *esp);
//服务器 API函数
uint8_t ESP_connectServer(struct ESP_cl *esp);//(ServerConnect_sr *serverConnect);
uint8_t ESP_disconnectServer(struct ESP_cl *esp);

/*--收发功能--*/
int8_t ESP_netSendOutFun(struct ESP_cl *esp, char *s, uint16_t num);
int8_t ESP_netReceivedFun(struct ESP_cl *esp, char *s, uint16_t *num);
int8_t ESP_JudgeRXDataType(struct ESP_cl *esp);  
int8_t ESP_SortingRXData(struct ESP_cl *esp);
//CWLAP报文处理函数
int8_t ESP_CWLAP_RxMessageOperationFun(struct ESP_cl *esp);
int8_t ESP_WifiCONNECTED_RxMessageOperationFun(struct ESP_cl *esp);
int8_t ESP_WiFiGotIP_RxMessageOperationFun(struct ESP_cl *esp);
int8_t ESP_IPD_RxMessageOperationFun(struct ESP_cl *esp);
int8_t ESP_WifiDisconnect_RxMessageOperationFun(struct ESP_cl *esp);
int8_t ESP_CONNECT_RxMessageOperationFun(struct ESP_cl *esp);
int8_t ESP_SENDOK_RxMessageOperationFun(struct ESP_cl *esp);
int8_t ESP_ARROW_RxMessageOperationFun(struct ESP_cl *esp);
int8_t ESP_CLOSED_RxMessageOperationFun(struct ESP_cl *esp);

//发送报文超时处理
void ESP_SendoutTineout_operating(struct ESP_cl *esp);


/*--其他功能--*/
uint8_t ESP_selectESPStatus(struct ESP_cl *esp);
void  ESP_OperationStatus(struct ESP_cl *esp);
uint8_t ESP_setUARTParameters(struct ESP_cl *esp);//(EspUartAttr_st *EspUartAttr);
uint8_t ESP_selectSNTPTime(struct ESP_cl *esp);//(STNPTime_st *stnpTime);

//wifi属性复制
int8_t ESP_WifiAttrCopy(WifiAttr_st *wifiAttr1, WifiAttr_st *wifiAttr2);

//IS判断函数
uint8_t ESP_IS_WifiAttrNonempty(struct ESP_cl *esp);
uint8_t ESP_IS_ServiceAttrNonempty(struct ESP_cl *esp);


//ESP设备本体
extern struct ESP_cl ESP_Device[1];
//接收数据回执表数组
extern const ESP_CommandMessage_st ESP_ReceivingDataComparisonTable[];	
//发送指令集
extern const ESP_SendComFun_st ESP_TXDComMessageTable[];






#endif
