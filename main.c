#include "lpc17xx.h"
#include "lpc_types.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_clkpwr.h"
#include "lpc17xx_nvic.h"



void USB_pinSelect()
{
	// D+ P0.29 -> PINSEL1 27:26 = 01
	// D- P0.30 -> PINSEL1 29:28 = 01
	LPC_PINCON->PINSEL1 &= ~(3<<26 | 3<<28); 	// 00 @ 27:26 & 29:28
	LPC_PINCON->PINSEL1 |= (1<<26 | 1<<28);		// 1 @ 26 & 28

	// Vbus P1.30 -> PINSEL3 29:28 = 10
	// GoodLink P1.18 -> PINSEL3 5:4 = 01
	LPC_PINCON->PINSEL3 &= ~(3<<28 | 3<<4);		// 00 @ 29:28 & 5:4
	LPC_PINCON->PINSEL3 |= (2<<28 | 1<<4);		// 1 @ 29 & 4

	// SoftConn P2.9 -> PINSEL4 19:18 = 01
	LPC_PINCON->PINSEL4 &= ~(3<<18);
	LPC_PINCON->PINSEL4 |= (1<<18);
}


void USB_ClkEnable() {
	LPC_USB->USBClkCtrl = 0x12;
	while ((LPC_USB->USBClkSt & 0x12) != 0x12)
		;
}

void USB_setup()
{
	USB_pinSelect();

	LPC_SC->PCONP |= 1<<31;
	USB_ClkEnable();



}

int main(void)
{

	while(1);
}

