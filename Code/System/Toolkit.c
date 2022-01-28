#include "Toolkit.h"

int32_t StringToHex(char *s, uint8_t lenth)
{
  int32_t res;
	
	//判断数据有效性
	if((lenth > 9) || \
		 ((lenth == 1)&&(s[0] == '-')) || \
	   (lenth == 0) \
	)
		return 0;
	
	res = 0;
	if(s[0] != '-')
	{
		switch(lenth)
		{
			case 8:
				res = CharToUInt8(*s++);
			case 7:
				res <<= 4;
				res += CharToUInt8(*s++);		
			case 6:
				res <<= 4;
				res += CharToUInt8(*s++);		
			case 5:
				res <<= 4;
				res += CharToUInt8(*s++);		
			case 4:
				res <<= 4;
				res += CharToUInt8(*s++);		
			case 3:
				res <<= 4;
				res += CharToUInt8(*s++);		
			case 2:
				res <<= 4;
				res += CharToUInt8(*s++);		
			case 1:
				res <<= 4;
				res += CharToUInt8(*s);			
		}
	}
	else
	{
		s++;
		switch(lenth)
		{
			case 9:
				res = CharToUInt8(*s++);
			case 8:
				res <<= 4;
				res += CharToUInt8(*s++);		
			case 7:
				res <<= 4;
				res += CharToUInt8(*s++);		
			case 6:
				res <<= 4;
				res += CharToUInt8(*s++);		
			case 5:
				res <<= 4;
				res += CharToUInt8(*s++);		
			case 4:
				res <<= 4;
				res += CharToUInt8(*s++);		
			case 3:
				res <<= 4;
				res += CharToUInt8(*s++);		
			case 2:
				res <<= 4;
				res += CharToUInt8(*s);		 
		}
		res = 0 - res;
	}
	
	return res;
}

int32_t StringToDec(char *s, uint8_t lenth)
{
  int32_t res;
	
	//判断数据有效性
	if((lenth >= 10) || \
		 ((lenth == 1)&&(s[0] == '-')) || \
	   (lenth == 0) \
	)
		return 0;
	
	res = 0;
	if(s[0] != '-')
	{
		switch(lenth)
		{
			case 9:
				res = CharToUInt8(*s++);
			case 8:
				res *= 10;
				res += CharToUInt8(*s++);		
			case 7:
				res *= 10;
				res += CharToUInt8(*s++);		
			case 6:
				res *= 10;
				res += CharToUInt8(*s++);		
			case 5:
				res *= 10;
				res += CharToUInt8(*s++);		
			case 4:
				res *= 10;
				res += CharToUInt8(*s++);		
			case 3:
				res *= 10;
				res += CharToUInt8(*s++);		
			case 2:
				res *= 10;
				res += CharToUInt8(*s++);		
			case 1:
				res *= 10;
				res += CharToUInt8(*s);		
		}
	}
	else
	{
		s++;
		switch(lenth)
		{
			case 10:
				res = CharToUInt8(*s++);
			case 9:
				res *= 10;
				res += CharToUInt8(*s++);		
			case 8:
				res *= 10;
				res += CharToUInt8(*s++);		
			case 7:
				res *= 10;
				res += CharToUInt8(*s++);		
			case 6:
				res *= 10;
				res += CharToUInt8(*s++);		
			case 5:
				res *= 10;
				res += CharToUInt8(*s++);		
			case 4:
				res *= 10;
				res += CharToUInt8(*s++);		
			case 3:
				res *= 10;
				res += CharToUInt8(*s++);		
			case 2:
				res *= 10;
				res += CharToUInt8(*s);		
		}
		res = 0 - res;
	}
	
	return res;
}

uint8_t CharToUInt8(char c)
{
	uint8_t res = 0;
	switch(c)
	{
		case '1': res = 1; break; 
		case '2': res = 2; break; 
		case '3': res = 3; break; 
		case '4': res = 4; break; 
		case '5': res = 5; break; 
		case '6': res = 6; break; 
		case '7': res = 7; break; 
		case '8': res = 8; break; 
		case '9': res = 9; break;  
		case 'A':
		case 'a': res = 10; break; 
		case 'B':
		case 'b': res = 11; break; 
		case 'C':
		case 'c': res = 12; break; 
		case 'D':
		case 'd': res = 13; break; 
		case 'E':
		case 'e': res = 14; break; 
		case 'F':
		case 'f': res = 15; break;  
	}  
	return res;
}

int8_t my_Memcmp(char *a, char *b, uint16_t lenth)
{
	uint16_t i;
	
	for(i=0;i<lenth;i++)
	{
		if(*a != *b)
		{
			return EX_ERR;
		}
		a++;b++;
	}
	
	return EX_OK;
}

int16_t my_strlen(char *a)
{
	int16_t lenth;
	
	if(a == NULL)
	{
		lenth = -1;
	}
	else
	{
		for(lenth=0;*a != '\0';lenth++,a++);
	}
	
	return lenth;
}

void my_strcpy(char* strDestination, const char* strSource, uint16_t lenth)
{
	uint16_t i;
	
	i = 0;
	
	if(lenth == 0)
	{
		while(1)
		{
			if(strSource[i] != '\0')
			{
				strDestination[i] = strSource[i];
			}
			else
			{
				break;
			}
			i++;
		} 
	}
	else
	{
		for(i = 0;i < lenth;i++)
		{
			strDestination[i] = strSource[i];
		}
	} 
}

void * my_memcpy(void *dest, void *src, unsigned int count )
{
	if (dest == NULL || src == NULL)
	{
		return NULL;
	}
	char* pdest = (char*) dest;
	char* psrc = (char*)src;
	while (count--)
	{
		*pdest++ = *psrc++;
	}
	return dest;
}


void * my_memset(void *dest, int set, unsigned int len)
{
	if (dest == NULL || len == 0)
	{
		return NULL;
	}
	char *pdest = (char *)dest;
	while (len-- > 0)
	{
		*pdest++ = set;
	}
	return dest;
}
