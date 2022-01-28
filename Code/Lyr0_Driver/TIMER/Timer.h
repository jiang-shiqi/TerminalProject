#ifndef __TIMER_H_
#define __TIMER_H_

#include "sys.h"


#define TIM3_PWM_val TIM3->CCR2

void TIM2_init(u16 arr,u16 psc);
void TIM3_PWM_init(u16 arr,u16 psc);

#endif
