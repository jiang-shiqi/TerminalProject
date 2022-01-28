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






//����״̬ ö��
typedef enum ConnectStatus_Type{
	ESPStatus_NoResponse,               //ģ������Ӧ
	ESPStatus_NoInit,                   //ģ��δ��ʼ��
	ESPStatus_NoWifi,                   //δ���ӵ�WiFi
	ESPStatus_ConnectedWifi,            //�����ӵ�WiFi
	ESPStatus_ConnectedTCP,             //�����ӵ�������
	ESPStatus_ServerResponse,           //����������Ӧ
}ConnectStatus;

//���������ӷ�ʽ ö��
typedef enum ServerConnect_Type{
	ServerConnect_Null,
	TCP,
	UDP,
	SSL,
}ServerConnect;

//UART���ò���ö��
//������
typedef enum EspUartBaud_en{
	Baud_110,
	Baud_9600,
	Baud_115200,
	Baud_1000000,
}EspUartBaud;
//����λ
typedef enum EspUartData_en{
	Data_5bit,
	Data_6bit,
	Data_7bit,
	Data_8bit,
}EspUartData;
//ֹͣλ
typedef enum EspUartStop_en{
	Stop_1bit,
	Stop_1_5bit,
	Stop_2bit, 
}EspUartStop;
//У��λ
typedef enum EspUartParity_en{
	Parity_None,
	Parity_Odd,
	Parity_Even, 
}EspUartParity;
//����֡
typedef enum EspUartFlowControl_en{
	FlowControl_None,
	FlowControl_RTS,
	FlowControl_CTS, 
	FlowControl_RTS_CTS, 
}EspUartFlowControl;

//ʱ��ö��
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




//wifi���Խṹ�� 
//ʾ��
//+CWLAP:(3,"LAPTOP-FTV1PBJJ 7782",-32,"4a:a4:72:73:0e:10",11,-4,0,4,4,7,1)
//+CWLAP:<ecn>,<ssid>,<rssi>,<mac>,<channel>,<freq offset>,<freqcali>,<pairwise_cipher>,<group_cipher>,<bgn>,<wps>
typedef struct {
	uint8_t ecn;	//���ܷ�ʽ
	char    ssid[ESP_WIFISSID_MAX];	//AP SSID
	int8_t  rssi;//�ź�ǿ��
	uint8_t mac[6];//AP MAC��ַ
	uint8_t channel;//ͨ����
//	int8_t  freq_offset;//APƵƫ ��λ��kHz������ֵ���� 2.4���ɵõ� ppm ֵ
//	int8_t  freqcali;//ƵƫУ׼ֵ
//	uint8_t pairwise_cipher;
//	uint8_t group_cipher;
//	uint8_t bgn;
//	uint8_t wps; 
}WifiAttr_st;

typedef struct {
	WifiAttr_st attr[ESP_WIFILIST_MAX];
	uint8_t lenth;
}WifiList_st;

//���������ӽṹ��
typedef struct {
	enum ServerConnect_Type type; 
	char website[50];
	uint8_t ip[4];
	uint16_t port; 
}ServerConnect_sr;
  
//UART�ṹ��
typedef struct{
	uint8_t channel;
	enum EspUartBaud_en baud;//������ 110-115200*40 �Ƽ�1000000 
	enum EspUartData_en data;//����λ
	enum EspUartStop_en stop;//ֹͣλ
	enum EspUartParity_en parity;//У��λ
	enum EspUartFlowControl_en flowControl;//����֡ 
}EspUartAttr_st;

//wifi�ṹ��
typedef struct {
	uint8_t ecn;                    //���ܷ�ʽ
	char    ssid[ESP_WIFISSID_MAX];	//AP SSID
	char    pwd[ESP_WIFIPSWD_MAX];  //AP PWD 
	int8_t  rssi;                   //�ź�ǿ��
	uint8_t mac[6];                 //AP MAC��ַ
}EspWifiAttr_st;



//SNTPʱ��ṹ��
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

//ESP��������������
typedef union
{
	char data[ESP_RECEIVEDDATA_MAX];
	WifiAttr_st cwlapData;
}ESP_Received_Data_union;

//ESP���սṹ��
typedef struct {
	uint8_t number;                      //������������
	uint8_t status;                      //����״̬
	uint32_t timeoutVal;                 //��ʱ������
	uint16_t lenth;                      //���ݳ���
	ESP_Received_Data_union data;        //��������
}ESP_UartReceived_st;

//ESP���ͽṹ�� 
typedef struct { 
	uint8_t status;                      //����״̬ 
	uint16_t lenth;                      //���ݳ���
	char data[ESP_SENDOUT_MAX];          //��������
}ESP_NetworkDataSendOut_st;

//ESP��·���ͽṹ�� 
typedef struct { 
	uint8_t status;                      //����״̬ 
	uint16_t lenth;                      //���ݳ���
	char data[ESP_SENDOUT_MAX];          //��������
}ESP_NetworkDataReceived_st; 

//ESP�������Խṹ��
typedef struct {
	uint8_t wifiAutoConnectEnable         : 1;  //wifi�Զ�����ʹ��
	uint8_t serverAutoConnectEnable       : 1;  //�������Զ�����ʹ��
}ESP_SetAttr_st;


//ESP��ṹ��
struct ESP_cl{
	uint8_t initStatus;
	uint8_t connectStatus;                    //����״̬ 
	ESP_SetAttr_st setAttr;                   //����������
	uint16_t waitingSendComNumber;            //�ȴ���������
	uint16_t sendComNumber;                   //����͵�����
	uint8_t sendComStatus;                    //����ָ���״̬
	uint32_t callbackTimeout;                 //�ص���ʱʱ��
	uint32_t keepAlive;                       //������ʱ��
	ESP_UartReceived_st uartReceivedData;     //���յ���UART����
	ESP_NetworkDataSendOut_st netSendoutData; //�����͵���������
	ESP_NetworkDataReceived_st netReceivedData;//���յ�����������
	EspUartAttr_st uartAttr;                  //UART����
	EspWifiAttr_st WifiAttr;                  //WiFi����
	ServerConnect_sr serverAttr;              //����������
	STNPTime_st stnpTime;                     //STNPʱ��
	uint8_t (*connectWifi)(struct ESP_cl *esp);             //����WiFi
	uint8_t (*disconnectWifi)(struct ESP_cl *esp);          //�Ͽ�WiFi
	uint8_t (*connectServer)(struct ESP_cl *esp);           //���ӷ�����
	uint8_t (*disconnectServer)(struct ESP_cl *esp);        //�Ͽ�������
	int8_t (*netSendOutFun)(struct ESP_cl *esp, char *s, uint16_t num);  //������������
	int8_t (*netReceivedFun)(struct ESP_cl *esp, char *s, uint16_t *num); //������������
	uint8_t (*setUARTParameters)(struct ESP_cl *esp);       //���ô�������
	uint8_t (*selectSNTPTime)(struct ESP_cl *esp);          //��ѯSNTPʱ��
};



//�������ݻ�ִ��ṹ��
typedef struct {
	char *str;
	uint16_t number; 
	uint8_t type;
	int8_t (*rxMessageOperationFun)(struct ESP_cl *esp); 
}ESP_CommandMessage_st;


//ATָ��ͺ���
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

//���ͻص�����
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

//�������ݻ�ִ��ṹ��
typedef struct {
	void (*sendComFun)(struct ESP_cl *esp);             //ָ��ͺ���
	uint16_t number;                                    //ָ������
	uint8_t type;                                       //ָ����� 1�����е���ȷ�Ϸ���&&ֱ�ӷ��ز���ȴ� 2����������+����ȷ�Ϸ���
	uint16_t receivingType;                             //��������״η���ʱ�ӵ��ı��
	const uint16_t timeout;                             //��ʱʱ��
	int8_t (*sendComCallback)(struct ESP_cl *esp);      //ָ��ͻص�����
}ESP_SendComFun_st;



//ESP����
void ESP_Init(void);
void ESP_Service(void);

/*--���ӹ���--*/
//wifi API����
uint8_t ESP_selectWifiList(WifiList_st *wifiList_buf);
uint8_t ESP_connectWifi(struct ESP_cl *esp);//(char *ssid, char *pwd);
uint8_t ESP_disconnectWifi(struct ESP_cl *esp);
//������ API����
uint8_t ESP_connectServer(struct ESP_cl *esp);//(ServerConnect_sr *serverConnect);
uint8_t ESP_disconnectServer(struct ESP_cl *esp);

/*--�շ�����--*/
int8_t ESP_netSendOutFun(struct ESP_cl *esp, char *s, uint16_t num);
int8_t ESP_netReceivedFun(struct ESP_cl *esp, char *s, uint16_t *num);
int8_t ESP_JudgeRXDataType(struct ESP_cl *esp);  
int8_t ESP_SortingRXData(struct ESP_cl *esp);
//CWLAP���Ĵ�����
int8_t ESP_CWLAP_RxMessageOperationFun(struct ESP_cl *esp);
int8_t ESP_WifiCONNECTED_RxMessageOperationFun(struct ESP_cl *esp);
int8_t ESP_WiFiGotIP_RxMessageOperationFun(struct ESP_cl *esp);
int8_t ESP_IPD_RxMessageOperationFun(struct ESP_cl *esp);
int8_t ESP_WifiDisconnect_RxMessageOperationFun(struct ESP_cl *esp);
int8_t ESP_CONNECT_RxMessageOperationFun(struct ESP_cl *esp);
int8_t ESP_SENDOK_RxMessageOperationFun(struct ESP_cl *esp);
int8_t ESP_ARROW_RxMessageOperationFun(struct ESP_cl *esp);
int8_t ESP_CLOSED_RxMessageOperationFun(struct ESP_cl *esp);

//���ͱ��ĳ�ʱ����
void ESP_SendoutTineout_operating(struct ESP_cl *esp);


/*--��������--*/
uint8_t ESP_selectESPStatus(struct ESP_cl *esp);
void  ESP_OperationStatus(struct ESP_cl *esp);
uint8_t ESP_setUARTParameters(struct ESP_cl *esp);//(EspUartAttr_st *EspUartAttr);
uint8_t ESP_selectSNTPTime(struct ESP_cl *esp);//(STNPTime_st *stnpTime);

//wifi���Ը���
int8_t ESP_WifiAttrCopy(WifiAttr_st *wifiAttr1, WifiAttr_st *wifiAttr2);

//IS�жϺ���
uint8_t ESP_IS_WifiAttrNonempty(struct ESP_cl *esp);
uint8_t ESP_IS_ServiceAttrNonempty(struct ESP_cl *esp);


//ESP�豸����
extern struct ESP_cl ESP_Device[1];
//�������ݻ�ִ������
extern const ESP_CommandMessage_st ESP_ReceivingDataComparisonTable[];	
//����ָ�
extern const ESP_SendComFun_st ESP_TXDComMessageTable[];






#endif
