/*************************************************************
 * Copyright (C) 2024-09-28 Yang Haifeng. All rights reserved.
 *
 * This code is licensed under the MIT license
 *************************************************************/

#include "umm_malloc_cfgport.h"
#include <stdint.h>

//@config<array>
//堆消耗 = 16字节固定开销 + 用户累计申请字节数 + 8*用户申请次数 + 内存碎片(可能有)
uint8_t heap_buff[16+16*3+8*3] = {0};
void * heap_addr = (void *)heap_buff;
uint32_t heap_size = sizeof(heap_buff);
