
#ifndef _CAN_MESSAGE_TYPES_H_
#define _CAN_MESSAGE_TYPES_H_

#include "include.h"

typedef enum
{
    CAN_MSG_CYCLE = 0,
    CAN_MSG_EVENT,
    CAN_MSG_EVENT_CYCLE,
} CAN_Msg_Cyc_Type_en_t;

typedef enum
{
    CAN_MSG_ID_TYPE_STD = 0,
    CAN_MSG_ID_TYPE_EXT,
} CAN_Msg_ID_Type_en_t;

typedef enum
{
    CAN_MSG_DIR_RX = 0,
    CAN_MSG_DIR_TX,
} CAN_Msg_Dir_en_t;

typedef struct
{
    uint8_t             Channel;         //ͨ��
    volatile uint8_t   *pMsg;
    volatile uint8_t   *pStatus;
    volatile uint8_t   *pRecordCnt;  //��¼���յĴ�����ѭ���������� ��¼�Ѿ����͵Ĵ���
    volatile uint8_t   *pReqCnt;     //�ⲿ���յĴ�����ѭ���������� �����͵Ĵ���
    volatile uint16_t  *pTimer;
    uint8_t             Init[8];
    uint8_t             TimeOut[8];
    uint8_t             Mask[8];
} CAN_Msg_Data_st_t;

typedef struct
{
  uint8_t ChildID;   //��ID
  uint8_t Index;     //��ID�����У�������
}CAN_Child_Msg_Map_t;

typedef struct
{
    uint32_t                   MsgID;           //ID
    uint8_t                    pro;
    CAN_Msg_ID_Type_en_t       IDType;          //�������ͣ���׼֡/��չ֡��
    const CAN_Msg_Data_st_t   *pMsgData;        //��������
    uint8_t                    DLCMax;          //��󳤶�
    uint8_t                    DLCMin;          //��С����
    CAN_Msg_Dir_en_t           Dir;             //����
    CAN_Msg_Cyc_Type_en_t      Type;            //��������(����/�¼�)
    uint16_t                   Cycle;           //ѭ������
    uint16_t                   Offset;          //ƫ����
    uint8_t                    NumofChild;      //��ID����
    const CAN_Child_Msg_Map_t *Map;             //��IDӳ��
    void                       ( *pDataRdyCallbBack ) ( uint8_t Num );  //�ص�����
} CAN_Msg_Attr_st_t;


typedef union
{
    uint8_t Byte;

    struct
    {
        uint8_t   Lost    : 1;
        uint8_t   Updt    : 1;
        uint8_t           : 5;
        uint8_t   TxEn    : 1;
    } Bit;
} CAN_Msg_Stat_un_t;
    
//����״̬�궨��
#define   CAN_MSG_STAT_BIT_TX_EN            0x80    //����
#define   CAN_MSG_STAT_BIT_UPDATE           0x02    //������
#define   CAN_MSG_STAT_BIT_MSG_LOST         0x01
#define   CAN_MSG_LOST  CAN_MSG_STAT_BIT_MSG_LOST
#define   CAN_UPDATE    CAN_MSG_STAT_BIT_UPDATE
#define   CAN_TX_EN     CAN_MSG_STAT_BIT_TX_EN
#endif