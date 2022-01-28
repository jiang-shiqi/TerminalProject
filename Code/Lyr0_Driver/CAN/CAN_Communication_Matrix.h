#include "CAN_Message_Types.h"


#define InfoRegister_000                          0x000
extern volatile CAN_InfoRegisterID_un_t           InfoRegister; 
extern volatile uint8_t                           CANInfoRegisterLastRxCnt; 
extern volatile uint8_t                           CANInfoRegisterCurrRxCnt; 
extern volatile uint16_t                          CANInfoRegisterTimer;  

extern volatile CAN_Msg_Stat_un_t                 CANInfoRegisterStatus; 

#define InfoRegister_LAST_RX_CNT                       CANInfoRegisterLastRxCnt 
#define InfoRegister_CURR_RX_CNT                       CANInfoRegisterCurrRxCnt 
#define InfoRegister_STATUS                            CANInfoRegisterStatus.Byte 
#define InfoRegister_STATUS_LOST                       CANInfoRegisterStatus.Bit.Lost 
#define InfoRegister_STATUS_UPDT                       CANInfoRegisterStatus.Bit.Updt 
#define InfoRegister_STATUS_TXEN                       CANInfoRegisterStatus.Bit.TxEn 


/******************************************************************************
Identifier  : 0x8C
Signals     : SRS_08C
              |- SRSFaultLamp
              |- PAB_SW
******************************************************************************/
typedef union 
{ 
    uint8_t Msg[8]; 
    struct 
    {
      uint32_t   			                            :8; // Reserve  
      uint32_t   			                            :8; // Reserve  
    } Sig;  
} CANMsg08CUnion; 
 
#define SRS_08C                                   0x8C
extern volatile CANMsg08CUnion                    CANMsg08C; 
extern volatile uint8_t                           CANMsg08CLastRxCnt; 
extern volatile uint8_t                           CANMsg08CCurrRxCnt; 
extern volatile uint16_t                          CANMsg08CTimer; 

// #define SRSFaultLamp                    	 		    CANMsg08C.Sig.SRSFaultLamp 
// #define PAB_SW                          	 		    CANMsg08C.Sig.PAB_SW 

extern volatile CAN_Msg_Stat_un_t                 CANMsg08CStatus; 

#define SRS_08C_LAST_RX_CNT                       CANMsg08CLastRxCnt 
#define SRS_08C_CURR_RX_CNT                       CANMsg08CCurrRxCnt 
#define SRS_08C_STATUS                            CANMsg08CStatus.Byte 
#define SRS_08C_STATUS_LOST                       CANMsg08CStatus.Bit.Lost 
#define SRS_08C_STATUS_UPDT                       CANMsg08CStatus.Bit.Updt 
#define SRS_08C_STATUS_TXEN                       CANMsg08CStatus.Bit.TxEn 

static const CAN_Msg_Data_st_t                    CANMsg08CData = 
{
    .pMsg           = CANMsg08C.Msg,
    .pStatus        = &CANMsg08CStatus.Byte,
    .pRecordCnt     = &CANMsg08CLastRxCnt,
    .pReqCnt        = &CANMsg08CCurrRxCnt,
    .pTimer         = &CANMsg08CTimer,
    .Init           = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    .TimeOut        = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    .Mask           = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
};

//常驻功能数组
static const CAN_Msg_Attr_st_t                      CANCommMatrix1Attr[] =
{
    /*==============================================================================================================================
                                  |                    |                |    DLC    |               |               |         |        | Data Ready
              Identifier          |  Identifier Type   |  Message Data  | --------- |   Direction   |   CycleType   |  Cycle  | Offset | Call Back
                                  |                    |                | Max | Min |               |               |         |        | Function*/
/*2AutoCreate Code Begin*/
{SRS_08C,          0,               CAN_MSG_ID_TYPE_STD,   &CANMsg08CData,    8,    8, CAN_MSG_DIR_RX,  CAN_MSG_CYCLE,     5000,       0, 1,NULL,NULL},
};

#define   CAN_COMM_MATRIX1_TX_MSG_NUM          1
#define   CAN_COMM_MATRIX1_RX_MSG_NUM          1
#define   CAN_COMM_MATRIX1_ALL_MSG_NUM         (sizeof(CANCommMatrix1Attr) / sizeof(CAN_Msg_Attr_st_t))


//CAN1 CAN收发板数组
CAN_Msg_Data_st_t CAN_Msg_Data2[100];
static const CAN_Msg_Attr_st_t                      CANCommMatrix2Attr[100];







