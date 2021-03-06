#include "GUI.h"
#include "LCD.h"

unsigned char GUI_dat[ARRAY_NUM]= { /* 0X00,0X01,0X80,0X00,0X40,0X00, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X10,0X00,0X00,
0X06,0X00,0X00,0X00,0X00,0X00,0X06,0X00,0X00,0X00,0X00,0X00,0X00,0X1C,0X00,0X00,
0X03,0X80,0X20,0X00,0X08,0X00,0X07,0XC0,0X00,0X00,0X00,0X00,0X00,0X1F,0X18,0X00,
0X01,0XC0,0X38,0X00,0X1C,0X00,0X07,0XC0,0X00,0X40,0X00,0X00,0X00,0X1F,0X8E,0X00,
0X01,0XE0,0X3F,0XFF,0XFE,0X00,0X07,0X80,0X00,0X60,0X00,0X00,0X00,0X1F,0X0F,0X80,
0X00,0XF0,0X3F,0XFF,0XFF,0X00,0X07,0X80,0X00,0X30,0X00,0X00,0X00,0X1E,0X07,0XC0,
0X00,0XF8,0X38,0X00,0X1C,0X00,0X07,0X80,0X00,0X3C,0X00,0X00,0X00,0X1E,0X03,0XE0,
0X00,0X78,0X38,0X00,0X1C,0X00,0X07,0X80,0X00,0X1E,0X00,0X00,0X00,0X1E,0X01,0XF0,
0X00,0X78,0X38,0X00,0X1C,0X00,0X07,0X80,0X00,0X1F,0X00,0X00,0X00,0X1E,0X01,0XF0,
0X00,0X38,0X38,0X00,0X1C,0X08,0X07,0X80,0X00,0X1F,0X00,0X00,0X00,0X1E,0X00,0XE0,
0X00,0X38,0X38,0X00,0X1C,0X0E,0X07,0X80,0X00,0X0F,0X80,0X00,0X00,0X1E,0X00,0XE0,
0X00,0X00,0X38,0X00,0X1C,0X0F,0X87,0X80,0X00,0X0F,0X80,0X00,0X00,0X1E,0X00,0X40,
0X00,0X00,0X38,0X00,0X1C,0X0F,0X87,0X80,0X00,0X0F,0X80,0X00,0X00,0X0E,0X00,0X10,
0X00,0X00,0X38,0X30,0X1C,0X0F,0X07,0X80,0X00,0X07,0X80,0X00,0X00,0X0E,0X00,0X38,
0X00,0X00,0X38,0X3C,0X1C,0X0F,0X07,0X80,0X00,0X07,0X80,0X00,0X00,0X0E,0X00,0X7C,
0X60,0X00,0X38,0X3E,0X1C,0X0F,0X07,0X80,0X00,0X07,0X00,0X00,0X00,0X0E,0X00,0XFE,
0X70,0X00,0X38,0X3C,0X1C,0X0F,0X07,0X80,0X00,0X00,0X03,0XFF,0XFF,0XFF,0XFF,0XFF,
0X38,0X01,0X38,0X3C,0X1C,0X0F,0X07,0X80,0X00,0X00,0X01,0X80,0X00,0X0F,0X00,0X00,
0X1E,0X01,0X38,0X3C,0X1C,0X0F,0X07,0X80,0X00,0X00,0X00,0X00,0X00,0X0F,0X00,0X00,
0X1F,0X01,0X38,0X3C,0X1C,0X0F,0X07,0X80,0X00,0X00,0X00,0X00,0X00,0X0F,0X00,0X00,
0X0F,0X03,0X38,0X3C,0X1C,0X0F,0X07,0X80,0X00,0X00,0X00,0X00,0X00,0X0F,0X00,0X00,
0X0F,0X82,0X38,0X3C,0X1C,0X0F,0X07,0X80,0X00,0X00,0X00,0X00,0X00,0X0F,0X00,0X00,
0X0F,0X82,0X38,0X3C,0X1C,0X0F,0X07,0X80,0X00,0X00,0X00,0X00,0X00,0X0F,0X00,0X00,
0X07,0X86,0X38,0X3C,0X1C,0X0F,0X07,0X80,0X00,0X03,0X00,0X00,0X00,0X0F,0X00,0X00,
0X07,0X06,0X38,0X3C,0X1C,0X0F,0X07,0X80,0X00,0X07,0X80,0X00,0X00,0X07,0X00,0X00,
0X02,0X04,0X38,0X3C,0X1C,0X0F,0X07,0X80,0X1F,0XFF,0XE0,0X00,0X00,0X87,0X00,0X00,
0X00,0X0C,0X38,0X3C,0X1C,0X0F,0X07,0X80,0X0F,0XFF,0XC0,0X00,0X01,0XC7,0X00,0X00,
0X00,0X0C,0X38,0X3C,0X1C,0X0F,0X07,0X80,0X00,0X07,0X80,0X00,0X03,0XE7,0X00,0X00,
0X00,0X0C,0X38,0X3C,0X1C,0X0F,0X07,0X80,0X00,0X07,0X81,0XFF,0XFF,0XF7,0X80,0X00,
0X00,0X08,0X38,0X38,0X1C,0X0F,0X07,0X80,0X00,0X07,0X80,0XFF,0XFF,0XF7,0X80,0X00,
0X00,0X18,0X38,0X38,0X1C,0X0F,0X07,0X80,0X00,0X07,0X80,0X00,0XF0,0X0F,0X80,0X00,
0X00,0X18,0X38,0X38,0X1C,0X0F,0X07,0X80,0X00,0X07,0X80,0X00,0XF0,0X03,0X80,0X00,
0X00,0X18,0X38,0X38,0X1C,0X0F,0X07,0X80,0X00,0X07,0X80,0X00,0XF0,0X03,0X80,0X00,
0X00,0X30,0X38,0X38,0X1C,0X0F,0X07,0X80,0X00,0X07,0X80,0X00,0XF0,0X03,0XC0,0X00,
0X00,0X30,0X38,0X38,0X1C,0X0F,0X07,0X80,0X00,0X07,0X80,0X00,0XF0,0X03,0XC0,0X00,
0X00,0X70,0X38,0X38,0X1C,0X0F,0X07,0X80,0X00,0X07,0X80,0X00,0XF0,0X03,0XC0,0X00,
0X00,0X70,0X38,0X38,0X1C,0X0F,0X07,0X80,0X00,0X07,0X80,0X00,0XF0,0X01,0XC0,0X00,
0X00,0X60,0X38,0X78,0X1C,0X0F,0X07,0X80,0X00,0X07,0X80,0X00,0XF0,0X01,0XE0,0X00,
0X00,0XE0,0X38,0X70,0X1C,0X0F,0X07,0X80,0X00,0X07,0X80,0X00,0XF0,0X01,0XE0,0X00,
0X01,0XE0,0X38,0X70,0X1C,0X0F,0X07,0X80,0X00,0X07,0X80,0X00,0XF0,0X01,0XE0,0X00,
0XFF,0XE0,0X38,0X70,0X18,0X0F,0X07,0X80,0X00,0X07,0X80,0X00,0XF0,0X00,0XF0,0X00,
0X3F,0XC0,0X38,0X70,0X00,0X0F,0X07,0X80,0X00,0X07,0X80,0X60,0XF0,0X00,0XF0,0X00,
0X0F,0XC0,0X30,0XF0,0X00,0X0F,0X07,0X80,0X00,0X07,0X80,0XC0,0XF0,0X00,0XF0,0X02,
0X07,0XC0,0X00,0XE0,0X00,0X0F,0X07,0X80,0X00,0X07,0X81,0X80,0XF0,0X00,0X78,0X02,
0X03,0XC0,0X00,0XE4,0X00,0X0C,0X07,0X80,0X00,0X07,0X83,0X80,0XF0,0X00,0X78,0X02,
0X03,0XC0,0X01,0XE3,0X00,0X00,0X07,0X80,0X00,0X07,0X83,0X00,0XF0,0X1C,0X3C,0X06,
0X03,0XC0,0X01,0XC3,0X80,0X00,0X07,0X80,0X00,0X07,0X86,0X00,0XF1,0XF0,0X3C,0X06,
0X03,0XC0,0X03,0XC1,0XC0,0X00,0X07,0X80,0X00,0X07,0X8E,0X00,0XFF,0X80,0X1E,0X06,
0X03,0XC0,0X03,0X80,0XE0,0X00,0X07,0X80,0X00,0X07,0X9C,0X00,0XFE,0X00,0X1F,0X06,
0X03,0XC0,0X07,0X80,0X78,0X00,0X07,0X80,0X00,0X07,0XB8,0X07,0XF8,0X00,0X0F,0X06,
0X07,0XC0,0X0F,0X00,0X7C,0X00,0X07,0X80,0X00,0X07,0XF8,0X7F,0XE0,0X00,0X0F,0X8E,
0X07,0XC0,0X0E,0X00,0X3C,0X00,0X07,0X80,0X00,0X07,0XF1,0XFF,0X00,0X00,0X07,0XCE,
0X07,0XC0,0X1C,0X00,0X3E,0X00,0X07,0X80,0X00,0X07,0XE0,0XFC,0X00,0X00,0X03,0XEE,
0X07,0XC0,0X38,0X00,0X1E,0X00,0X07,0X80,0X00,0X0F,0XE0,0XF0,0X00,0X00,0X01,0XFE,
0X07,0XC0,0X70,0X00,0X1E,0X0F,0XFF,0X80,0X00,0X07,0XC0,0X60,0X00,0X00,0X01,0XFE,
0X07,0XC0,0XE0,0X00,0X0E,0X03,0XFF,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0XFE,
0X01,0XC1,0X80,0X00,0X0E,0X00,0XFF,0X00,0X00,0X01,0X80,0X00,0X00,0X00,0X00,0X7E,
0X00,0X07,0X00,0X00,0X04,0X00,0X7F,0X00,0X00,0X00,0X80,0X00,0X00,0X00,0X00,0X1E,
0X00,0X0E,0X00,0X00,0X00,0X00,0X3E,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,
0X00,0X18,0X00,0X00,0X00,0X00,0X18,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X07,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
};
unsigned char GUI_buffer[ARRAY_NUM];

void GUI_Init(void)
{
	OLED_Init();
}


//????????????????????????
void GUI_Clear(void)
{
	unsigned int i;
	for(i=0;i<ARRAY_NUM;i++)
	{
		GUI_dat[i] = 0x00;
	}
}
 

//?????????????????? (????????????????????????????????????)
void GUI_Display(void)
{
	OLED_CharToOLEDBuffer(GUI_dat); //1ms 7172
	OLED_Conversion();  //2ms 91170//4ms 167936
	OLED_Refresh_Gram();       //6ms 162224//10ms 225280
}

//GUI????????????
//??????????????????????????? 
//param[in] sta_x ???????????????x??????
//param[in] sta_y ???????????????y??????
//param[in] end_x ???????????????x??????
//param[in] end_y ???????????????y??????
void GUI_Fill_Rectangle(unsigned int sta_x,unsigned int sta_y,unsigned int end_x,unsigned int end_y,unsigned char colorMode)
{
	unsigned int i ;
	
	if(((sta_x == end_x)&&(sta_y == end_y))||(colorMode > 2))
		return;
	
	if(sta_x > end_x)
	{
		i = sta_x;
		sta_x = end_x;
		end_x = i;
	}
	if(sta_y > end_y)
	{
		i = sta_y;
		sta_y = end_y;
		end_y = i;
	}
	
	if(end_x>=TOTAL_X)
		end_x = TOTAL_X-1;
	if(end_y>=TOTAL_Y)
		end_y = TOTAL_Y-1; 
	
	for(i = sta_y;i <= end_y;i++)
	  GUI_Draw_line(sta_x,i,end_x,i,colorMode);
 
	
}

//GUI??????????????????
//??????????????????GUI???????????????????????????
//param[in] num	  ?????????????????????
//param[in] x     ????????????x??????
//param[in] y     ????????????y?????? 
void GUI_Draw_Number(unsigned char num, unsigned int x, unsigned int y)
{
	unsigned char i;
	if(((x+7)>TOTAL_X)||((y+10)>TOTAL_Y))
		return; 
	
	if((x>>3)==((x+7)>>3))             //??????????????????
	{
		for(i=0;i<10;i++)
		{
			GUI_dat[((y+i)*16)+(x>>3)] |= Font_1014[num][i]>>(x%8);
		}
	}
	else if(((x>>3)+1)==((x+7)>>3))    //?????????????????????
	{
		for(i=0;i<10;i++)
		{
			GUI_dat[((y+i)*16)+(x>>3)]   |= Font_1014[num][i]>>(x%8);
			GUI_dat[((y+i)*16)+(x>>3)+1] |= (Font_1014[num][i]<<(8-(x%8))) & 0x00ff;
		}
	}
}


//GUI???????????????
//??????????????????GUI???????????????????????????
//param[in] fontType    ???????????????????????????
//param[in] s     ?????????????????????????????????
//param[in] x     ????????????x??????
//param[in] y     ????????????y?????? 
void GUI_Draw_String(eFontType fontType,char *s, unsigned int x, unsigned int y)
{
	unsigned char num_lenth = 0;
	unsigned char i;
	unsigned char fontW, fontH;
	for(i=0;s[i]!=0; i++);
	num_lenth = i;
	
	switch (fontType)
    {
        case F1014:
            fontW =  7;
            fontH = 10; 
            break;

        case F1206:
            fontW =  6;
            fontH = 12; 
            break;

        case F1608:
            fontW =  8;
            fontH = 16; 
            break; 
        default:
            return;
    }
	
	if((x + (num_lenth*fontW)) > TOTAL_X) 
		num_lenth = TOTAL_X / fontW;
		
	if((y + fontH) > TOTAL_Y)
		return;
	
	for(i=0;i<num_lenth;i++)
	{
			GUI_Draw_Char(fontType,s[i], x+i*fontW, y);
	} 
}

//GUI????????????
//??????????????????GUI???????????????????????????
//param[in] fontType    ???????????????????????????
//param[in] c 	        ?????????????????????
//param[in] x           ????????????x??????
//param[in] y           ????????????y?????? 
//
//????????????????????????8bit????????????
void GUI_Draw_Char(eFontType fontType ,char c, unsigned int x, unsigned int y)
{
	u8 i;
	u16 endX,endY;
	u8  fontW,fontH;        //?????????
	const u8 *pc;
	

    switch (fontType)
    {
        case F1014:
            fontW =  7;
            fontH = 10;
            pc = Font_1014[c-32];
            break;

        case F1206:
            fontW =  6;
            fontH = 12;
            pc = Font_1206[c-32];
            break;

        case F1608:
            fontW =  8;
            fontH = 16;
            pc = Font_1608[c-32];
            break;

        default:
            return;
    }

    //????????????	
    endX = x + fontW;
    endY = y + fontH;
	if((endX > TOTAL_X)||( endY > TOTAL_Y))
		return; 
	//????????????
	if((x>>3)==(endX>>3))             //??????????????????
	{
		for(i=0;i<fontH;i++)
		{
			GUI_dat[((y+i)*16)+(x>>3)] |= pc[i]>>(x%8);
		}
	}
	else if(((x>>3)+1)==((x+8)>>3))    //?????????????????????
	{
		for(i=0;i<fontH;i++)
		{
			GUI_dat[((y+i)*16)+(x>>3)]   |= pc[i]>>(x%8);
			GUI_dat[((y+i)*16)+(x>>3)+1] |= ( pc[i]<<(8-(x%8))) & 0x00ff;
		}
	}

}



//GUI?????????????????????
//??????????????????GUI?????????????????????????????????
//param[in] num	  ?????????????????????
//param[in] x     ????????????x??????
//param[in] y     ????????????y?????? 
void GUI_Draw_Digit_String(uint32_t str_num, unsigned int x, unsigned int y)
{
	unsigned char num_lenth=0;
	     if(str_num<10)             num_lenth=1; 
    else if(str_num<100)            num_lenth=2;
    else if(str_num<1000)           num_lenth=3; 
    else if(str_num<10000)          num_lenth=4; 
    else if(str_num<100000)         num_lenth=5; 
    else if(str_num<1000000)        num_lenth=6; 	
	else if(str_num<10000000)       num_lenth=7; 
	else if(str_num<100000000)      num_lenth=8; 
	else if(str_num<1000000000)     num_lenth=9; 
	else                            num_lenth=10; 
	
	switch(num_lenth)
	{
		case 10:GUI_Draw_Number(str_num/1000000000%10,   x,                y);
		case  9:GUI_Draw_Number(str_num/100000000%10,    x+(num_lenth-9)*7,y);
		case  8:GUI_Draw_Number(str_num/10000000%10,     x+(num_lenth-8)*7,y);
		case  7:GUI_Draw_Number(str_num/1000000%10,      x+(num_lenth-7)*7,y);
		case  6:GUI_Draw_Number(str_num/100000%10,       x+(num_lenth-6)*7,y);
		case  5:GUI_Draw_Number(str_num/10000%10,        x+(num_lenth-5)*7,y);
		case  4:GUI_Draw_Number(str_num/1000%10,         x+(num_lenth-4)*7,y);
		case  3:GUI_Draw_Number(str_num/100%10,          x+(num_lenth-3)*7,y);
		case  2:GUI_Draw_Number(str_num/10%10,           x+(num_lenth-2)*7,y);
		case  1:GUI_Draw_Number(str_num%10,              x+(num_lenth-1)*7,y);
		case  0:break;
	}
	
}
//GUI????????????
//??????????????????GUI???????????????????????????
//param[in] p	    ??????????????????
//param[in] sta_x ????????????x??????
//param[in] sta_y ????????????y??????
//p[0]??????????????? p[1]???????????????
//?????? ???????????????????????????
void GUI_Draw_Image(const unsigned char *p,unsigned int sta_x,unsigned int sta_y)
{
	unsigned int end_x,end_y;
	unsigned int i,j,k;
	unsigned char cupA,cupB,cupC,cupD,cupE;
	
	end_x = sta_x + *p;
	end_y = sta_y + *(p+1);
	if((end_x>TOTAL_X)||(end_y>TOTAL_Y))  
		return; 
	
	cupA = sta_x>>3;
	cupB = end_x>>3;
	cupC = sta_x%8;
	cupD = 8 - cupC;
	
	for(j=sta_y,k=2;j<end_y;j++)
	{
		cupE = *p;     //????????????????????????
		for(i=cupA;;i++,k++,cupE-=8)
		{
			GUI_dat[j*16+i] |= ((*(p+k))>>cupC);
			GUI_dat[j*16+i+1] |= ((*(p+k))<<cupD);
			if(cupE < 8)
			{
				k++;
				break;
			}
		}
	}
}

//GUI????????????(?????????)
//??????????????????????????????????????????
//param[in] (x,y):?????????
//param[in] r    :??????
//param[in] color:????????????
//?????????????????????
void GUI_Draw_Circle(unsigned int x,unsigned int y,unsigned int r,unsigned char color)
{
	int a,b;
	int di;
	
	a=0;b=r;          
	di=3-(r<<1);             //??????????????????????????????
	
	while(a<=b)
	{
		GUI_Draw_Point(x-b,y-a,color);             //3           
		GUI_Draw_Point(x+b,y-a,color);             //0           
		GUI_Draw_Point(x-a,y+b,color);             //1       
		GUI_Draw_Point(x-b,y-a,color);             //7           
		GUI_Draw_Point(x-a,y-b,color);             //2             
		GUI_Draw_Point(x+b,y+a,color);             //4               
		GUI_Draw_Point(x+a,y-b,color);             //5
		GUI_Draw_Point(x+a,y+b,color);             //6 
		GUI_Draw_Point(x-b,y+a,color);             
		a++;
		//??????Bresenham????????????     
		if(di<0)di +=4*a+6;          
		else
		{
						di+=10+4*(a-b);   
						b--;
		} 
		GUI_Draw_Point(x+a,y+b,color);
	}
} 

//GUI????????????
//???????????????????????????????????????(????????????)
//param[in] (sta_x,sta_y):???????????????
//param[in] (end_x,end_y):???????????????
//param[in] color        :????????????
void GUI_Draw_line(unsigned int sta_x,unsigned int sta_y,unsigned int end_x,unsigned int end_y,unsigned char color)
{
  uint16_t i;
	uint16_t a,b,c,d;
	//???????????? ??????
	if(((sta_x == end_x)&&(sta_y == end_y))||(color > 2))
		return;
	
	if(sta_x > end_x)
	{
		a = sta_x;
		sta_x = end_x;
		end_x = a;
	}
	if(sta_y > end_y)
	{
		a = sta_y;
		sta_y = end_y;
		end_y = a;
	}
	
	if(end_x>=TOTAL_X)
		end_x = TOTAL_X-1;
	if(end_y>=TOTAL_Y)
		end_y = TOTAL_Y-1;
	
	//??????
	if(color == CLEAR)
	{
		//????????????
		//??????
		if(sta_x == end_x)
		{ 
			a = sta_y;
			b = end_y; 
			c = sta_x>>3;
			d = sta_x%8;
			
			for(i=a;i<=b;i++)
			{ 
  			GUI_dat[(i<<4)+c] |= ~(0x80>>d);
			}
		}
		//??????
		else if(sta_y == end_y)
		{
			a = sta_x>>3;
			b = end_x>>3;
			c = sta_x%8;
			d = end_x%8;
			if(a == b)
			{  
  			GUI_dat[(sta_y<<4)+a] &= ((0xff>>(d+1))|(~(0xff>>c))); 
			}
			else if((a + 1) == b)
			{ 
				GUI_dat[(sta_y<<4)+a] &= ~(0xff>>c);
				GUI_dat[(sta_y<<4)+b] &= 0xff>>(d+1);
			}
			else
			{ 
				GUI_dat[(sta_y<<4)+a] &= ~(0xff>>c);
				for(i=a+1;i<b;i++)
					GUI_dat[(sta_y<<4)+i] &= 0x00;
				GUI_dat[(sta_y<<4)+b] &= 0xff>>(d+1);
			}			
		}
		//????????????
		else
		{
            a = end_x - sta_x;
            b = end_y - sta_y;
			for(i=sta_x;i<end_x;i++)
			{
			    c = i*b/a;
			    GUI_Draw_Point( i, c, color);
			}
			GUI_Draw_Point( end_x, end_y, color);
		}
	}
	//??????
	else if(color == FILL)
	{
	  //????????????
		//??????
		if(sta_x == end_x)
		{ 
			a = sta_y;
			b = end_y; 
			c = sta_x>>3;
			d = sta_x%8;
			
			for(i=a;i<=b;i++)
			{
				GUI_dat[(i<<4)+c] |= 0x80>>d; 
			}
		}
		//??????
		else if(sta_y == end_y)
		{
			a = sta_x>>3;
			b = end_x>>3;
			c = sta_x%8;
			d = end_x%8;
			if(a == b)
			{ 
				GUI_dat[(sta_y<<4)+a] |= ((~(0xff>>(d+1)))&(0xff>>c));  
			}
			else if((a + 1) == b)
			{
				GUI_dat[(sta_y<<4)+a] |= 0xff>>c;
				GUI_dat[(sta_y<<4)+b] |= ~(0xff>>(d+1)); 
			}
			else
			{
				GUI_dat[(sta_y<<4)+a] |= 0xff>>c;
				for(i=a+1;i<b;i++)
					GUI_dat[(sta_y<<4)+i] |= 0xff;
				GUI_dat[(sta_y<<4)+b] |= ~(0xff>>(d+1)); 
			}			
		}
		//????????????
		else
		{
            a = end_x - sta_x;
            b = end_y - sta_y;
			for(i=sta_x;i<end_x;i++)
			{
			    c = i*b/a;
			    GUI_Draw_Point( i, c, color);
			}
			GUI_Draw_Point( end_x, end_y, color);
		}
	}
	//??????
	else 
	{
		//????????????
		//??????
		if(sta_x == end_x)
		{ 
			a = sta_y;
			b = end_y; 
			c = sta_x>>3;
			d = sta_x%8;
			
			for(i=a;i<=b;i++)
			{
				GUI_dat[(i<<4)+c] ^= 0x80>>d; 
			}
		}
		//??????
		else if(sta_y == end_y)
		{
			a = sta_x>>3;
			b = end_x>>3;
			c = sta_x%8;
			d = end_x%8;
			if(a == b)
			{ 
				GUI_dat[(sta_y<<4)+a] ^= ((~(0xff>>(d+1)))&(0xff>>c));  
			}
			else if((a + 1) == b)
			{
				GUI_dat[(sta_y<<4)+a] ^= 0xff>>c;
				GUI_dat[(sta_y<<4)+b] ^= ~(0xff>>(d+1)); 
			}
			else
			{
				GUI_dat[(sta_y<<4)+a] ^= 0xff>>c;
				for(i=a+1;i<b;i++)
					GUI_dat[(sta_y<<4)+i] ^= 0xff;
				GUI_dat[(sta_y<<4)+b] ^= ~(0xff>>(d+1)); 
			}			
		}
		//????????????
		else
		{
            a = end_x - sta_x;
            b = end_y - sta_y;
			for(i=sta_x;i<end_x;i++)
			{
			    c = i*b/a;
			    GUI_Draw_Point( i, c, color);
			}
			GUI_Draw_Point( end_x, end_y, color);
		}
	
	} 
}


//???????????????????????????
//(x,y):?????????
//color:????????????
void GUI_Draw_Point(unsigned int x,unsigned int y,unsigned char color)
{
	unsigned char arr_x,bit_x;
	
	if((x >= TOTAL_X) || (y >= TOTAL_Y))
		return;
	
	arr_x = x>>3;
	bit_x = x%8;
	
	if(color == CLEAR)
	{
		GUI_dat[y*TOTAL_LIST + arr_x] &=~(1<<(7-bit_x)); 
	}
	else if(color == FILL)
	{
	  GUI_dat[y*TOTAL_LIST + arr_x] |=1<<(7-bit_x); 
	}
	else if(color == XOR)
	{
	  if((GUI_dat[y*TOTAL_LIST + arr_x] & 1<<(7-bit_x)) == 1)
		{
		  GUI_dat[y*TOTAL_LIST + arr_x] &=~(1<<(7-bit_x)); 
		}
		else
		{
		  GUI_dat[y*TOTAL_LIST + arr_x] |=1<<(7-bit_x); 
		}
	}
	else 
		return;
}

void GUI_Draw_Box(unsigned int sta_x,unsigned int sta_y,unsigned int end_x,unsigned int end_y,unsigned char color)
{
  u16 a;

	//?????????
	if(((sta_x == end_x)&&(sta_y == end_y))||(color > 2))
		return;
	
	if(sta_x > end_x)
	{
		a = sta_x;
		sta_x = end_x;
		end_x = a;
	}
	if(sta_y > end_y)
	{
		a = sta_y;
		sta_y = end_y;
		end_y = a;
	}
	
	if(end_x>=TOTAL_X)
		end_x = TOTAL_X-1;
	if(end_y>=TOTAL_Y)
		end_y = TOTAL_Y-1;
	
	
	//??????
	GUI_Draw_line(sta_x,sta_y,end_x,sta_y,color);
	//??????
	GUI_Draw_line(sta_x,end_y,end_x,end_y,color);
	//??????
	GUI_Draw_line(sta_x,sta_y+1,sta_x,end_y-1,color);
	//??????
	GUI_Draw_line(end_x,sta_y+1,end_x,end_y-1,color);
	
}








