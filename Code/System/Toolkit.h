/***********************************************************************************************************
* 版权                                                                                                     *
*                                                                                                          *
* 文件名称: Toolkit.h                                                                                      *
* 描    述: 工具包                                                                      *
* 作    者: 姜世奇                                                                                         *
* 当前版本: 1.0.1                                                                                          *  
* 完成时间:                                                                                                *
* ---------------------------------------------------------------------------------------------------------*
* 历史信息:                                                                                                *
*           <Date>            |    <Version>    |    <Author>    |    <Description>                        *
* ---------------------------------------------------------------------------------------------------------*
*    2020年5月2日10:36:08     |      1.0.1      |     姜世奇     |     Create file                         *            
*----------------------------------------------------------------------------------------------------------*
***********************************************************************************************************/
#ifndef __TOOLKIT_H_
#define __TOOLKIT_H_
  
#include "include.h" 
 

//typedef unsigned          char uint8_t;
//typedef unsigned short     int uint16_t;
//typedef unsigned           int uint32_t;
//typedef  char int8_t;
//typedef  int int16_t;
//typedef  int int32_t;

 
typedef union
{
    uint8_t byte;
    
    struct
    {
        uint8_t a0:1;
        uint8_t a1:1;
        uint8_t a2:1;
        uint8_t a3:1;
        uint8_t a4:1;
        uint8_t a5:1;
        uint8_t a6:1;
        uint8_t a7:1;
    }bit;
}union_ByteTobit;
 

uint8_t CharToUInt8(char c);
int32_t StringToDec(char *s, uint8_t lenth);
int32_t StringToHex(char *s, uint8_t lenth);

int8_t my_Memcmp(char *a, char *b, uint16_t lenth);
int16_t my_strlen(char *a);
void my_strcpy(char* strDestination, const char* strSource, uint16_t lenth);
void my_strcat(char* strDestination, const char* strSource, uint16_t position, uint16_t lenth);

void * my_memcpy(void *dest, void *src, unsigned int count );
void * my_memset(void *dest, int set, unsigned int len);

#endif

