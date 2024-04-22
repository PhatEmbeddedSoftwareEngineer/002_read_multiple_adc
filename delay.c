#include "delay.h"

static __IO uint32_t usTicks;

void SysTick_Handler()
{
	if(usTicks != 0)
	{
		usTicks--;
	}
}

void delay_init()
{
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000000); // 72mhz 
	
}
void DelayUs(uint32_t us)
{
	usTicks=us;
	while(usTicks);
}
void DelayMs(uint32_t ms)
{
	while(ms--)
	{
		DelayUs(1000);
	}
}