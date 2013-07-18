#include "lpc17xx_uart.h"

int main(void)
{
//	USB_Device_VND();

	UART_PrintExp();
	USB_Device_CDC();

}

