#include "LED.h"
#include "include.h"
#include "GPIO.h"
void LED_init(void)
{
	LED0=1;//
}

void LED(int num)
{
	 
}

void LED_Service(void)
{
	LED0 = !LED0;
}
