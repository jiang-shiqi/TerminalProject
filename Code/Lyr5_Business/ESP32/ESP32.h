#ifndef __ESP32_H
#define __ESP32_H			    
#include "sys.h"  

//使用的SPI端口
#define ESP32_SPICOM       SPI1

//设备ID
#define ESP32_DRIVE_ID     0XEF17

//握手IO
#define ESP32_HANDSHAKE_IO   ADC1_IN1


//起始符
#define ESP32_START_BIT             0x5577
//指令符
#define ESP32_COM_RESET             0x0001
#define ESP32_COM_REQUEST_ID        0x0002
#define ESP32_COM_SENDER            0x0003
#define ESP32_COM_RECEIVER          0x0004
#define ESP32_COM_GET_STATUS        0x0005
#define ESP32_COM_SET_WIFI_ATTR     0x0006
#define ESP32_COM_SET_SERVER_ATTR   0x0007
#define ESP32_COM_RECONNECT_WIFI    0x0008



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



#endif 
