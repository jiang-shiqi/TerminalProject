#ifndef _ESP32_H_
#define _ESP32_H_

#include "include.h"
#include "SPI.h"

//ESP32ģ��ģ��SPI ID
#define ESP32_SPI_ID          0xEF62
//������ȷ������
#define ESP32_ReturnCode_OK   0x4F4B
//ESP32ʹ�õ�SPI�˿�
#define ESP32_SPICOM          SPI1
//ESP32ʹ��CS�˿�
#define ESP32_SPICS           ESP_CS

//ESP32��������󳤶�
#define ESP32_NetData_MAX   100
#define ESP32_WIFILIST_MAX   10
#define ESP32_WIFISSID_MAX   30
#define ESP32_WIFIPSWD_MAX   30

//ESP32 SPIָ���  
#define ESP32_COM_DeviceID          0x90 //��ȡ�豸ID
#define ESP32_COM_PowerDown         0xB9 //����
#define ESP32_COM_WakeUp            0xAB //����
#define ESP32_COM_ReadStatusReg     0x05 //��ȡ״̬�Ĵ���
#define ESP32_COM_WriteStatusReg    0x01 //д��״̬�Ĵ���
#define ESP32_COM_ReadReceivedData  0x03 //��ȡ��������
#define ESP32_COM_WriteSentoutData  0x02 //д�뷢������
#define ESP32_COM_SetWifiAttr       0x10 //����WiFi����
#define ESP32_COM_SetServerAttr     0x11 //���÷���������
#define ESP32_COM_ConnectWifi       0x20 //����WiFi
#define ESP32_COM_DisconnectWifi    0x21 //�Ͽ�WiFi
#define ESP32_COM_ConnectServer     0x22 //���ӷ�����
#define ESP32_COM_SelectSNTP        0x23 //��ѯSNTPʱ��

//������Ϣ������ͨ��д��flash�Ĳ������͸�ESP32
//��Ϊͨ��ָ���

//ESP32 ״̬�Ĵ���
#define ESP32_Register_SR1          0x01
typedef union {
	uint32_t dat;
	struct
	{
		uint32_t        wifiConSta       : 2; //WiFi����״̬ 0:δ���� 1:������ 2:������
		uint32_t        ServerConSta     : 2; //����������״̬ 0:δ���� 1:������ 2:������
		uint32_t                         : 2; //����֪ͨ 0:�������� 1:������� 2:���ڽ���
	
		uint32_t                         :26; 
	}bit; 
}ESP32_Register_SR1_un_t;



//����״̬ ö��
typedef enum Esp32_ConnectStatusType_en_t{
	ESPStatus_NoResponse,               //ģ������Ӧ
	ESPStatus_NoInit,                   //ģ��δ��ʼ��
	ESPStatus_NoWifi,                   //δ���ӵ�WiFi
	ESPStatus_ConnectedWifi,            //�����ӵ�WiFi
	ESPStatus_ConnectedTCP,             //�����ӵ�������
	ESPStatus_ServerResponse,           //����������Ӧ
}en_ConnectStatusType;

//���������ӷ�ʽ ö��
typedef enum ESP32_ServerConnectType_en_t{
	ServerConnect_Null,
	TCP,
	UDP,
	SSL,
}en_ServerConnectType;

//ʱ��ö��
typedef enum ESP32_TimeWeek_en_t{
	Monday = 1,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday,
}en_TimeWeek;
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
}en_TimeMonth;


//ESP�������Խṹ��
typedef struct {
	uint8_t wifiAutoConnectEnable         : 1;  //wifi�Զ�����ʹ��
	uint8_t serverAutoConnectEnable       : 1;  //�������Զ�����ʹ��
}ESP32_SetAttr_st_t;

//ESP���ͽṹ�� 
typedef struct { 
	uint8_t status;                      //����״̬ 
	uint16_t lenth;                      //���ݳ���
	char data[ESP32_NetData_MAX];          //��������
}ESP32_NetDataSendOut_st_t;

//ESP���սṹ�� 
typedef struct { 
	uint8_t status;                      //����״̬ 
	uint16_t lenth;                      //���ݳ���
	char data[ESP32_NetData_MAX];          //��������
}ESP32_NetDataReceived_st_t; 

//wifi���Խṹ��  
typedef struct {
	uint8_t ecn;	//���ܷ�ʽ
	char    ssid[ESP32_WIFISSID_MAX];	//AP SSID
	int8_t  rssi;//�ź�ǿ��
	uint8_t mac[6];//AP MAC��ַ
	uint8_t channel;//ͨ����
//	int8_t  freq_offset;//APƵƫ ��λ��kHz������ֵ���� 2.4���ɵõ� ppm ֵ
//	int8_t  freqcali;//ƵƫУ׼ֵ
//	uint8_t pairwise_cipher;
//	uint8_t group_cipher;
//	uint8_t bgn;
//	uint8_t wps; 
}ESP32_WifiAttr_st_t;

//wifi�б�ṹ��
typedef struct {
	ESP32_WifiAttr_st_t attr[ESP32_WIFILIST_MAX];
	uint8_t lenth;
}ESP32_WifiList_st_t;

//���������ӽṹ��
typedef struct {
	enum ServerConnect_Type type; 
	char website[50];
	uint8_t ip[4];
	uint16_t port; 
}ESP32_ServerConnect_st_t;

//wifi�ṹ��
typedef struct {
	uint8_t ecn;                    //���ܷ�ʽ
	char    ssid[ESP32_WIFISSID_MAX];	//AP SSID
	char    pswd[ESP32_WIFIPSWD_MAX];  //AP PWD 
	int8_t  rssi;                   //�ź�ǿ��
	uint8_t mac[6];                 //AP MAC��ַ
}ESP32_WifiConnectAttr_st_t;

//SNTPʱ��ṹ��  
typedef struct{
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	enum ESPTimeWeek_en week; 
}ESP32_STNPTime_st_t;

//ESP��ṹ��
struct ESP32_Class_st_t{
	uint8_t initStatus;                                //��ʼ��״̬
	enum Esp32_ConnectStatusType_en_t connectStatus;   //����״̬ 
	ESP32_SetAttr_st_t setAttr;                        //����������  
	uint8_t sendComStatus;                             //����ָ���״̬
	uint32_t callbackTimeout;                          //�ص���ʱʱ��
	uint32_t keepAlive;                                //������ʱ��
	uint32_t errorNum;                                 //�����ۼ�ֵ
	ESP32_NetDataSendOut_st_t netSendoutData;          //�����͵���������
	ESP32_NetDataReceived_st_t netReceivedData;        //���յ�����������
	uint8_t WifiConnectStatus;                         //wifi����״̬
	ESP32_WifiConnectAttr_st_t WifiAttr;               //WiFi����
	ESP32_ServerConnect_st_t serverAttr;               //����������
	ESP32_STNPTime_st_t stnpTime;                      //STNPʱ��
	uint16_t (*connectWifi)(struct ESP32_Class_st_t *esp);             //����WiFi
	uint8_t (*disconnectWifi)(struct ESP32_Class_st_t *esp);          //�Ͽ�WiFi
	uint8_t (*connectServer)(struct ESP32_Class_st_t *esp);           //���ӷ�����
	uint8_t (*disconnectServer)(struct ESP32_Class_st_t *esp);        //�Ͽ�������
	uint8_t (*netSendOutReceivedFun)(struct ESP32_Class_st_t *esp, char *s, uint16_t num);  //����/������������
	uint8_t (*selectSNTPTime)(struct ESP32_Class_st_t *esp);          //��ѯSNTPʱ��
};

void ESP32_Init(void);
u16  ESP32_Read_ID(void);               //��ȡFLASH ID
uint32_t ESP32_Read_SR(uint16_t registerNum);               //��ȡ״̬�Ĵ��� 
uint32_t ESP32_Write_SR(uint16_t registerNum,uint32_t sr);             //д״̬�Ĵ���
void ESP32_Write_Enable(void);          //дʹ�� 
void ESP32_Write_Disable(void);         //д���� 
void ESP32_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead);   //��ȡflash
void ESP32_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);//д��flash
void ESP32_Erase_Chip(void);    	  	//��Ƭ���� 
void ESP32_Wait_Busy(void);           	//�ȴ�����
void ESP32_PowerDown(void);        	//�������ģʽ
void ESP32_WAKEUP(void);				//����

uint16_t connectWifi(struct ESP32_Class_st_t *esp);             //����WiFi
uint8_t disconnectWifi(struct ESP32_Class_st_t *esp);          //�Ͽ�WiFi
uint8_t connectServer(struct ESP32_Class_st_t *esp);           //���ӷ�����
uint8_t disconnectServer(struct ESP32_Class_st_t *esp);        //�Ͽ�������
uint8_t netSendOutReceivedFun(struct ESP32_Class_st_t *esp, char *s, uint16_t num);  //������������
uint8_t selectSNTPTime(struct ESP32_Class_st_t *esp);          //��ѯSNTPʱ��

#endif 
