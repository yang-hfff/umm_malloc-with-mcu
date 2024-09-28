#ifndef __SYSTICK
#define __SYSTICK

#include "sys.h"

#define delay_us(x)     systick_delay_us(x)
#define delay_ms(x)     systick_delay_ms(x)

void systick_delay_us(__IO uint32_t us);
void systick_delay_ms(__IO uint32_t ms);

#endif /*__SYSTICK*/



