#ifndef _ESP32_H_
#define _ESP32_H_

#include "sys.h"  

//ESP32模块模拟SPI ID
#define ESP32_DRIVE_ID     0XEF17
//操作正确返回码
#define ESP32_ReturnCode_OK   0x4F4B
//ESP32使用的SPI端口
#define ESP32_SPICOM          SPI1
//ESP32使用CS端口
#define ESP32_SPICS           ESP_CS
//握手IO
#define ESP32_HANDSHAKE_IO   ADC1_IN1
//ESP32_Service循环调用间隔
#define ESP32_SERVICE_CYCLE  DATA_SERVICE_CYCLE

//ESP32各数组最大长度
#define ESP32_NetData_MAX   100
#define ESP32_WIFILIST_MAX   10
#define ESP32_WIFISSID_MAX   30
#define ESP32_WIFIPSWD_MAX   30
#define ESP32_WEBSITE_MAX    50

//ESP32超时时间 ms
#define ESP32_TIMEOUT_WiFi   5000
#define ESP32_TIMEOUT_Server 5000

//ESP32 SPI指令表  
// #define ESP32_COM_DeviceID          0x90 //读取设备ID
// #define ESP32_COM_PowerDown         0xB9 //休眠
// #define ESP32_COM_WakeUp            0xAB //唤醒
// #define ESP32_COM_ReadStatusReg     0x05 //读取状态寄存器
// #define ESP32_COM_WriteStatusReg    0x01 //写入状态寄存器
// #define ESP32_COM_ReadReceivedData  0x03 //读取接收数据
// #define ESP32_COM_WriteSentoutData  0x02 //写入发送数据
// #define ESP32_COM_SetWifiAttr       0x10 //设置WiFi属性
// #define ESP32_COM_SetServerAttr     0x11 //设置服务器属性
// #define ESP32_COM_DisconnectWifi    0x21 //断开WiFi
// #define ESP32_COM_ConnectServer     0x22 //连接服务器
// #define ESP32_COM_SelectSNTP        0x23 //查询SNTP时间

//起始符
#define ESP32_START_BIT             0x5577
//指令符
#define ESP32_COM_RESET             0x0001 //设备重启
#define ESP32_COM_REQUEST_ID        0x0002 //获取ID
#define ESP32_COM_GET_STATUS        0x0003 //返回设备状态
#define ESP32_COM_GET_WIFI_STATUS   0x0004 //返回WIFI连接状态
#define ESP32_COM_ConnectWifi       0x0005 //连接WiFi
#define ESP32_COM_DisconnectWifi    0x0006 //断开WiFi
#define ESP32_COM_ReconnectWifi     0x0007 //重新连接WiFi
#define ESP32_COM_ScanWifi          0x0008 //扫描WiFi
#define ESP32_COM_ConnectServer     0x0009 //连接服务器
#define ESP32_COM_DisconnectServer  0x000A //断开服务器
#define ESP32_COM_ReconnectServer   0x000B //重新连接服务器
#define ESP32_COM_SET_WifiAttr      0x000C //设置WiFi属性
#define ESP32_COM_SET_ServerAttr    0x000D //设置服务器属性
#define ESP32_COM_SENDER            0x000E //发送数据
#define ESP32_COM_RECEIVER          0x000F //接收数据
#define ESP32_COM_SELECT_SNTP       0x0023 //查询SNTP时间
// #define ESP32_COM_PowerDown         0xB9 //休眠
// #define ESP32_COM_WakeUp            0xAB //唤醒

//属性信息都可以通过写入flash的操作发送给ESP32
//行为通过指令传输





//ESP32 状态寄存器
#define ESP32_Register_SR1          0x01
typedef union {
	uint32_t dat;
	struct
	{
		uint32_t        wifiConSta       : 2; //WiFi连接状态 0:未连接 1:已连接 2:连接中
		uint32_t        ServerConSta     : 2; //服务器连接状态 0:未连接 1:已连接 2:连接中
		uint32_t                         : 2; //接收通知 0:无新数据 1:接收完毕 2:正在接收
	
		uint32_t                         :26; 
	}bit; 
}ESP32_Register_SR1_un_t;



//连接状态 枚举
typedef enum Esp32_ConnectStatusType_en_t{
	ESPStatus_NoResponse,             //模块无响应
	// ESPStatus_RequestManualAction,    //需手动操作
	ESPStatus_NoWifi,                 //未连接到WiFi
	ESPStatus_WifiConnecting,         //WiFi连接中
	ESPStatus_WifiConnectError,       //wifi连接错误
	ESPStatus_WifiConnectSucceeded,   //已连接到WiFi
	ESPStatus_ServerConnecting,    	  //服务器连接中
	ESPStatus_ServerResponse,         //服务器已响应
//	ESPStatus_LargeFileTransferMode,  //大文件传输模式
}en_ConnectStatusType;

#define IS_Esp32_ConnectStatusType(type) ((type == ESPStatus_NoResponse) || \
                                        /*   (type == ESPStatus_RequestManualAction) || */\
                                          (type == ESPStatus_NoWifi) || \
                                          (type == ESPStatus_WifiConnecting) || \
                                          (type == ESPStatus_WifiConnectError) || \
                                          (type == ESPStatus_WifiConnectSucceeded) || \
                                          (type == ESPStatus_ServerConnecting) || \
                                          (type == ESPStatus_ServerResponse))

//信息显示 枚举
typedef enum Esp32_InfoDisplay_en_t{
	ESPInfo_NoResponse,               //模块无响应
	ESPInfo_WifiConnecting,           //WiFi连接中
	ESPInfo_WiFiWaitConnect,          //WiFi等待连接
	ESPInfo_WifiAttrError,            //WiFi属性有误
	ESPInfo_WifiConnectTimeout,       //WiFi连接超时
	ESPInfo_WifiPasswordError,        //WiFi密码错误
	ESPInfo_NoAPFound,                //未搜索到AP
	ESPInfo_ServerConnecting,         //服务器连接中
	ESPInfo_ServerAttrError,          //服务器属性有误
	ESPInfo_ServerConnectTimeout,     //服务器连接超时
	ESPInfo_ServerConnectSucceeded,   //已连接到服务器
}en_InfoDisplay;

//服务器连接方式 枚举
typedef enum ESP32_ServerConnectType_en_t{
	ServerConnect_Null,
	TCP,
	UDP,
	SSL,
}en_ServerConnectType;

//时间枚举
typedef enum ESP32_TimeWeek_en_t{
	Monday = 1,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday,
}en_TimeWeek;
typedef enum ESPTimeMonth_en_t{
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
}en_TimeMonth;

//WiFi连接状态枚举
typedef enum ESP32_WifiStatus_en_t{
	ESPWifiStatus_NoConnect = 0,      //WiFi未连接
	ESPWifiStatus_PSWDError,          //密码错误
	ESPWifiStatus_NoFound,            //未找到WiFi
	ESPWifiStatus_Connected,          //WiFi已连接
}en_WifiStatus;


//ESP设置属性结构体
typedef struct {
	uint8_t wifiAutoConnectEnable         : 1;  //wifi自动连接使能
	uint8_t serverAutoConnectEnable       : 1;  //服务器自动连接使能
}ESP32_SetAttr_st_t;

//ESP发送结构体 
typedef struct { 
	uint8_t status;                      //发送状态 
	uint16_t lenth;                      //数据长度
	char data[ESP32_NetData_MAX];          //接收数据
}ESP32_NetDataSendOut_st_t;

//ESP接收结构体 
typedef struct { 
	uint8_t status;                      //发送状态 
	uint16_t lenth;                      //数据长度
	char data[ESP32_NetData_MAX];          //接收数据
}ESP32_NetDataReceived_st_t; 

//wifi属性结构体  
typedef struct {
	uint8_t ecn;	//加密方式
	char    ssid[ESP32_WIFISSID_MAX];	//AP SSID
	int8_t  rssi;//信号强度
	uint8_t mac[6];//AP MAC地址
	uint8_t channel;//通道号
//	int8_t  freq_offset;//AP频偏 单位：kHz。此数值除以 2.4，可得到 ppm 值
//	int8_t  freqcali;//频偏校准值
//	uint8_t pairwise_cipher;
//	uint8_t group_cipher;
//	uint8_t bgn;
//	uint8_t wps; 
}ESP32_WifiAttr_st_t;

//wifi列表结构体
typedef struct {
	ESP32_WifiAttr_st_t attr[ESP32_WIFILIST_MAX];
	uint8_t lenth;
}ESP32_WifiList_st_t;

//服务器连接结构体
typedef struct {
	uint8_t ready_Flag;                 //准备就绪标志位
	enum ServerConnect_Type type;       //服务器连接方式
	char website[ESP32_WEBSITE_MAX];    //服务器网址
	uint8_t ip[4];                      //服务器IPV4
	uint16_t port;                      //服务器端口号
}ESP32_ServerConnect_st_t;

//wifi结构体
typedef struct {
	uint8_t ready_Flag;                 //准备就绪标志位
	uint8_t ecn;                        //加密方式
	char    ssid[ESP32_WIFISSID_MAX];	//AP SSID
	char    pswd[ESP32_WIFIPSWD_MAX];   //AP PWD 
	int8_t  rssi;                       //信号强度
	uint8_t mac[6];                     //AP MAC地址
}ESP32_WifiConnectAttr_st_t;

//SNTP时间结构体  
typedef struct{
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	enum ESPTimeWeek_en week; 
}ESP32_STNPTime_st_t;

//ESP类结构体
struct ESP32_Class_st_t{
	uint8_t initStatus;                                //初始化状态
	uint16_t driveID;                                  //设备ID
	enum Esp32_ConnectStatusType_en_t connectStatus;   //连接状态 
	enum Esp32_InfoDisplay_en_t infoDisplay;           //信息显示
	uint8_t connectionReady;                           //连接就绪
	uint8_t requestManualAction;                       //请求手动处理
	ESP32_SetAttr_st_t setAttr;                        //可设置属性  
	uint32_t timeout;                                  //超时等待时间
	uint32_t errorNum;                                 //错误累加值
	ESP32_NetDataSendOut_st_t netSendoutData;          //待发送的网络数据
	ESP32_NetDataReceived_st_t netReceivedData;        //接收到的网络数据
	ESP32_WifiConnectAttr_st_t WifiAttr;               //WiFi属性
	ESP32_ServerConnect_st_t serverAttr;               //服务器属性
	ESP32_STNPTime_st_t stnpTime;                      //STNP时间
	uint8_t  (*connectWifi)(struct ESP32_Class_st_t *esp);             //连接WiFi
	uint8_t  (*disconnectWifi)(void);                                  //断开WiFi
	uint8_t  (*connectServer)(struct ESP32_Class_st_t *esp);           //连接服务器
	uint8_t  (*disconnectServer)(void);                                //断开服务器
	uint8_t  (*netSendOutReceivedFun)(struct ESP32_Class_st_t *esp, char *s, uint16_t num);  //发送/接收网络数据
	uint8_t  (*selectSNTPTime)(struct ESP32_Class_st_t *esp);          //查询SNTP时间
};

void ESP32_Init(void);
int16_t ESP32_ReadDeviceID(void);               //读取FLASH ID
uint32_t ESP32_Read_SR(uint16_t registerNum);               //读取状态寄存器 
uint32_t ESP32_Write_SR(uint16_t registerNum,uint32_t sr);             //写状态寄存器
int8_t ESP32_Write_Enable(void);          //写使能 
int8_t ESP32_Write_Disable(void);         //写保护 
int8_t ESP32_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead);   //读取flash
int8_t ESP32_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);//写入flash
int8_t ESP32_Erase_Chip(void);    	  	//整片擦除 
int8_t ESP32_Wait_Busy(void);           	//等待空闲
int8_t ESP32_PowerDown(void);        	//进入掉电模式
int8_t ESP32_WAKEUP(void);				//唤醒

int8_t connectWifi(struct ESP32_Class_st_t *esp);             //连接WiFi
int8_t disconnectWifi(void);          //断开WiFi
int8_t connectServer(struct ESP32_Class_st_t *esp);           //连接服务器
int8_t disconnectServer(void);        //断开服务器
int8_t netSendOutReceivedFun(struct ESP32_Class_st_t *esp, char *s, uint16_t num);  //发送网络数据
int8_t selectSNTPTime(struct ESP32_Class_st_t *esp);          //查询SNTP时间




//全局变量
extern uint16_t ESP32_SerialNumber;
extern uint8_t  ESP32_Wait_Flag;
extern uint8_t  ESP32_Ready_Flag;

//函数
void ESP32_Init(void);
void ESP32_Service(void);

void ESP32_SendCom(uint16_t com);
void ESP32_TransmitData(char *sendBuf,char *readBuf, uint16_t len);

int16_t ESP32_ReadDeviceID(void);
int16_t ESP32_SendNetData(char *sendBuf, uint16_t lenth);
int16_t ESP32_ReceiveNetData(char *receiveBuf, uint16_t lenth);
int16_t ESP32_SelectStatus(void);
int16_t ESP32_SelectWiFiStatus(void);




#endif 
