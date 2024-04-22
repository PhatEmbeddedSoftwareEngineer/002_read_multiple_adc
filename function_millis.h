#include "stm32f10x.h"                  // Device header

void SetSystem72Mhz(void);
void ConfigureTimer3(void);
typedef struct Time{
	unsigned long miliseconds;
};
extern struct Time Millis;
uint32_t millis(void);
