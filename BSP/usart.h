#ifndef __USART_H
#define __USART_H

#include "sys.h"
#include "stdio.h"

void uart_init(uint32_t bound);
int print(const char *format,...);

#endif /*__USART_H*/


