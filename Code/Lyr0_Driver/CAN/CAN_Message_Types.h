
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
    uint8_t             Channel;         //通道
    volatile uint8_t   *pMsg;
    volatile uint8_t   *pStatus;
    volatile uint8_t   *pRecordCnt;  //记录接收的次数（循环计数）或 记录已经发送的次数
    volatile uint8_t   *pReqCnt;     //外部接收的次数（循环计数）或 请求发送的次数
    volatile uint16_t  *pTimer;
    uint8_t             Init[8];
    uint8_t             TimeOut[8];
    uint8_t             Mask[8];
} CAN_Msg_Data_st_t;

typedef struct
{
  uint8_t ChildID;   //子ID
  uint8_t Index;     //在ID数组中，索引号
}CAN_Child_Msg_Map_t;

typedef struct
{
    uint32_t                   MsgID;           //ID
    uint8_t                    pro;
    CAN_Msg_ID_Type_en_t       IDType;          //报文类型（标准帧/扩展帧）
    const CAN_Msg_Data_st_t   *pMsgData;        //报文数据
    uint8_t                    DLCMax;          //最大长度
    uint8_t                    DLCMin;          //最小长度
    CAN_Msg_Dir_en_t           Dir;             //方向
    CAN_Msg_Cyc_Type_en_t      Type;            //报文类型(周期/事件)
    uint16_t                   Cycle;           //循环周期
    uint16_t                   Offset;          //偏移量
    uint8_t                    NumofChild;      //子ID个数
    const CAN_Child_Msg_Map_t *Map;             //子ID映射
    void                       ( *pDataRdyCallbBack ) ( uint8_t Num );  //回调函数
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
    
//报文状态宏定义
#define   CAN_MSG_STAT_BIT_TX_EN            0x80    //掉线
#define   CAN_MSG_STAT_BIT_UPDATE           0x02    //被更新
#define   CAN_MSG_STAT_BIT_MSG_LOST         0x01
#define   CAN_MSG_LOST  CAN_MSG_STAT_BIT_MSG_LOST
#define   CAN_UPDATE    CAN_MSG_STAT_BIT_UPDATE
#define   CAN_TX_EN     CAN_MSG_STAT_BIT_TX_EN
#endif