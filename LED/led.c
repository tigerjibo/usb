#include "lpc17xx_gpio.h"
#include "lpc17xx_clkpwr.h"
#include "lpc17xx_nvic.h"


#include "led.h"
#include "gpiodefs.h"

static uint8_t count;

void LED_Init()
{
	CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCGPIO, ENABLE);
	GPIO_SetDir(LED_PORT_NUM, LED_ALL, GPIO_DIR_OUT);
}

void LED_On(uint32_t led)
{
	GPIO_SetValue(LED_PORT_NUM, led);
}

void LED_Off(uint32_t led)
{
	GPIO_ClearValue(LED_PORT_NUM, led);
}

uint8_t LED_Count()
{
	count++;
	LED_Off(LED_ALL);
	LED_On((uint32_t)count);
	return count;
}
