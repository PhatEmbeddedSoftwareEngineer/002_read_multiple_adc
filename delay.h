#ifndef __DELAY_H
#define __DELAY_H

#ifdef _cplusplus
extern "C"{
#endif

#include "stm32f10x.h"
void delay_init(void);
void DelayUs(uint32_t us);
void DelayMs(uint32_t ms);

#ifdef __cplusplus
}
#endif
#endif
