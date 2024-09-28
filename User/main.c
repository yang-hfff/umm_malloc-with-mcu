/*************************************************************
 * Copyright (C) 2024-09-28 Yang Haifeng. All rights reserved.
 *
 * This code is licensed under the MIT license
 *************************************************************/

#include "usart.h"
#include "logs.h"
#include "umm_malloc.h"
#include <stdlib.h>

int main(void)
{
    int i;
    uart_init(115200);
    LOG_I("uart init ok\r\n");
    umm_init();
    LOG_I("umm init ok\r\n");
    //��һ������
    uint8_t *p = (uint8_t *)umm_malloc(16);
    for(i = 0;i < 16;i++)
    {
        p[i] = 0XBB;
    }
    //�ڶ�������
    uint8_t *q = (uint8_t *)umm_malloc(16);
    for(i = 0;i < 16;i++)
    {
        q[i] = 0XAA;
    }
    //����������
    uint8_t *r = (uint8_t *)umm_malloc(16);
    for(i = 0;i < 16;i++)
    {
        r[i] = 0XDD;
    }   
    LOG_I("malloc OK\r\n");

    //����
    umm_free(p);
    umm_free(q);
    umm_free(r);
    LOG_I("free OK\r\n");
    for(;;)
    {
    }
}



