//此文件用于保存扩展设备的数据类型
#ifndef _CAN_EXTENSION_EQUIPMENT_TYPES_H_
#define _CAN_EXTENSION_EQUIPMENT_TYPES_H_

//信息注册ID 0x000
typedef union 
{ 
    uint8_t Msg[8]; 
    struct 
    { 
      uint32_t   			                            :32; // Reserve  
      uint32_t   			                            :32; // Reserve  
    } Sig;  
} CAN_InfoRegisterID_un_t; 
//设备回复ID 0x001
typedef union 
{ 
    uint8_t Msg[8]; 
    struct 
    { 
      uint32_t   			                            :32; // Reserve  
      uint32_t   			                            :32; // Reserve  
    } Sig;  
} CAN_DeviceResponseID_un_t; 
//主机广播ID 0x002
typedef union 
{ 
    uint8_t Msg[8]; 
    struct 
    { 
      uint32_t   			                            :32; // Reserve  
      uint32_t   			                            :32; // Reserve  
    } Sig;  
} CAN_HostBroadcastID_un_t; 



//扩展按键
//按键类型1 单按键检测 适用于按键数量较多、不需要多按键的键盘
typedef union 
{ 
    uint8_t Msg[8]; 
    struct 
    {
      uint32_t   			status                      : 8; // 状态  
      uint32_t   			                            :24; // Reserve  
      uint32_t   			value                       :32; //   
    } Sig;  
} CAN_KeyboardType1_un_t; 
//按键类型2 多按键检测 适用于按键数量较少、需要多按键检测的键盘
typedef union 
{ 
    uint8_t Msg[8]; 
    struct 
    {
      uint32_t        status                      : 8; // 状态
      uint32_t   			key00                       : 1; //   
      uint32_t   			key01                       : 1; //   
      uint32_t   			key02                       : 1; //   
      uint32_t   			key03                       : 1; //    
      uint32_t   			key04                       : 1; //   
      uint32_t   			key05                       : 1; //   
      uint32_t   			key06                       : 1; //   
      uint32_t   			key07                       : 1; //   
      uint32_t   			key10                       : 1; //   
      uint32_t   			key11                       : 1; //   
      uint32_t   			key12                       : 1; //   
      uint32_t   			key13                       : 1; //    
      uint32_t   			key14                       : 1; //   
      uint32_t   			key15                       : 1; //   
      uint32_t   			key16                       : 1; //   
      uint32_t   			key17                       : 1; //   
      uint32_t   			key20                       : 1; //   
      uint32_t   			key21                       : 1; //   
      uint32_t   			key22                       : 1; //   
      uint32_t   			key23                       : 1; //    
      uint32_t   			key24                       : 1; //   
      uint32_t   			key25                       : 1; //   
      uint32_t   			key26                       : 1; //   
      uint32_t   			key27                       : 1; //   
      uint32_t   			key30                       : 1; //   
      uint32_t   			key31                       : 1; //   
      uint32_t   			key32                       : 1; //   
      uint32_t   			key33                       : 1; //    
      uint32_t   			key34                       : 1; //   
      uint32_t   			key35                       : 1; //   
      uint32_t   			key36                       : 1; //   
      uint32_t   			key37                       : 1; //   
      uint32_t   			key40                       : 1; //   
      uint32_t   			key41                       : 1; //   
      uint32_t   			key42                       : 1; //   
      uint32_t   			key43                       : 1; //    
      uint32_t   			key44                       : 1; //   
      uint32_t   			key45                       : 1; //   
      uint32_t   			key46                       : 1; //   
      uint32_t   			key47                       : 1; //   
      uint32_t   			key50                       : 1; //   
      uint32_t   			key51                       : 1; //   
      uint32_t   			key52                       : 1; //   
      uint32_t   			key53                       : 1; //    
      uint32_t   			key54                       : 1; //   
      uint32_t   			key55                       : 1; //   
      uint32_t   			key56                       : 1; //   
      uint32_t   			key57                       : 1; //   
      uint32_t   			key60                       : 1; //   
      uint32_t   			key61                       : 1; //   
      uint32_t   			key62                       : 1; //   
      uint32_t   			key63                       : 1; //    
      uint32_t   			key64                       : 1; //   
      uint32_t   			key65                       : 1; //   
      uint32_t   			key66                       : 1; //   
      uint32_t   			key67                       : 1; //   
    } Sig;  
} CAN_KeyboardType2_un_t; 

//AD检测
typedef union 
{ 
    uint8_t Msg[8]; 
    struct 
    {
      uint32_t   			ch                          : 8; // 通道  
      uint32_t   			                            :24; // Reserve  
      uint32_t   			value                       :32; // 检测数值  
    } Sig;  
} CAN_ADDetection_un_t; 

#endif
