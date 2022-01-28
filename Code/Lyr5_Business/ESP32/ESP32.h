#ifndef __ESP32_H
#define __ESP32_H			    
#include "sys.h"  

//ʹ�õ�SPI�˿�
#define ESP32_SPICOM       SPI1

//�豸ID
#define ESP32_DRIVE_ID     0XEF17

//����IO
#define ESP32_HANDSHAKE_IO   ADC1_IN1


//��ʼ��
#define ESP32_START_BIT             0x5577
//ָ���
#define ESP32_COM_RESET             0x0001
#define ESP32_COM_REQUEST_ID        0x0002
#define ESP32_COM_SENDER            0x0003
#define ESP32_COM_RECEIVER          0x0004
#define ESP32_COM_GET_STATUS        0x0005
#define ESP32_COM_SET_WIFI_ATTR     0x0006
#define ESP32_COM_SET_SERVER_ATTR   0x0007
#define ESP32_COM_RECONNECT_WIFI    0x0008



//ȫ�ֱ���
extern uint16_t ESP32_SerialNumber;
extern uint8_t  ESP32_Wait_Flag;
extern uint8_t  ESP32_Ready_Flag;


//����
void ESP32_Init(void);
void ESP32_Service(void);

void ESP32_SendCom(uint16_t com);
void ESP32_TransmitData(char *sendBuf,char *readBuf, uint16_t len);




int16_t ESP32_ReadDeviceID(void);
int16_t ESP32_SendNetData(char *sendBuf, uint16_t lenth);
int16_t ESP32_ReceiveNetData(char *receiveBuf, uint16_t lenth);
int16_t ESP32_SelectStatus(void);



#endif 
