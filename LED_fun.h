#include "lpc17xx_gpio.h"
#include "lpc17xx_clkpwr.h"


volatile uint32_t ticks;
unsigned long LED_PINS =  ((uint32_t)1<<2)|((uint32_t)1<<3)|((uint32_t)1<<4);
unsigned long FLASH_LED = ((uint32_t)1<<3);
unsigned long KEY_PINS = ((uint32_t)1<<11)|((uint32_t)1<<12);

void SysTick_Handler()
{
	ticks++;
}


void Delay(uint32_t delay)
{
	uint32_t current = ticks;
	while((ticks - current) < delay);
}



void LED_Config()
{
	CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCGPIO, ENABLE);
	GPIO_SetDir(2, LED_PINS|((uint32_t)1<<3), 1);

}

void KEY_Config()
{
	GPIO_SetDir(2, KEY_PINS, 0);

}


static void LED_on()
{
	GPIO_SetValue(2, 0X14);
}

static void LED_off()
{
	GPIO_ClearValue(2, 0X14);
}

void LED_fun()
{

	if(SysTick_Config(SystemCoreClock / 1000))
	{
		while(1)
		{
		}
	}

	NVIC_EnableIRQ(EINT3_IRQn);
	NVIC_SetPriority(SysTick_IRQn, 4);
	NVIC_SetPriority(EINT3_IRQn, 5);
	LPC_GPIOINT->IO2IntEnR = KEY_PINS;
	LED_Config();
	KEY_Config();

	while(1)
	{
		Delay(100);
		LED_on();
		Delay(100);
		LED_off();
	}
}


void EINT3_IRQHandler()
{
	uint32_t st = LPC_GPIOINT->IO2IntStatR;
	uint32_t fl = GPIO_ReadValue(2)&FLASH_LED;

	LPC_GPIOINT->IO2IntClr |= KEY_PINS;

	if(st & 1<<11)
	{
		Delay(200);
	}
	else
	{
		if(fl)
			GPIO_ClearValue(2, FLASH_LED);
		else
			GPIO_SetValue(2, FLASH_LED);
	}
}
