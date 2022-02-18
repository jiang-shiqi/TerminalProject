#include "CAN_Communication_Matrix.h"

//信息注册
extern volatile CAN_InfoRegisterID_un_t           InfoRegister; 
extern volatile CAN_Msg_Stat_un_t                 CANInfoRegisterStatus; 
extern volatile uint8_t                           CANInfoRegisterLastRxCnt; 
extern volatile uint8_t                           CANInfoRegisterCurrRxCnt; 
extern volatile uint16_t                          CANInfoRegisterTimer;  



volatile CANMsg08CUnion                           CANMsg08C; 
volatile CAN_Msg_Stat_un_t                        CANMsg08CStatus;
volatile uint8_t                                  CANMsg08CLastRxCnt; 
volatile uint8_t                                  CANMsg08CCurrRxCnt; 
volatile uint16_t                                 CANMsg08CTimer; 