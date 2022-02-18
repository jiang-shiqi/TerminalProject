#include "timer.h" 

// 溢出时间 = (ARR+1)(PSC+1)/Tclk
//ARR：自动重装载值
//PSC：预分频器
//Tclk：时钟频率	72M

void TIM2_init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<0;
	TIM2->ARR=arr;			//设置自动重装值
	TIM2->PSC=psc;			//设置预分频器 7200
	TIM2->DIER|=1<<0;		//允许中断更新
	TIM2->CR1|=0x01;		//是能定时器3
	MY_NVIC_Init(1,3,TIM2_IRQn,2);
}

void TIM2_IRQHandler()
{
	if(TIM2->SR&0x0001)
	{
//		LED(~0x0001);
//		delay_ms(400);
	}
	TIM2->SR=~(1<<0);
}

void TIM3_PWM_init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;
	RCC->APB2ENR|=1<<2;
	// GPIOA->CRL&=0x0fffffff;
	// GPIOA->CRL|=0xb0000000;
	TIM3->ARR=arr;
	TIM3->PSC=psc;
	TIM3->CCMR1|=6<<12;
	TIM3->CCMR1|=1<<11;
	TIM3->CCER|=1<<4;
	TIM3->CR1=0x0080;
	TIM3->CR1|=0x01;
}
