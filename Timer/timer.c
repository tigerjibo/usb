#include "lpc17xx_nvic.h"
#include "timer.h"

volatile uint32_t ticks;

void SysTick_Handler()
{
	ticks++;
}

void Timer_Init()
{
	if(SysTick_Config(SystemCoreClock / 1000))
	{
		while(1)
		{
		}
	}
	//NVIC_SetPriority(SysTick_IRQn, TIMER_PRIORITY);
}

void Timer_Delay(uint32_t delay)
{
	uint32_t current = ticks;
	while((ticks - current) < delay);
}

