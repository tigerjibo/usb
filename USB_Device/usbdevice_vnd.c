#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
#include "lpc_types.h"
#include "LPC17xx.h"

#include "usbdevice.h"

#include "timer.h"
#include "led.h"

#define VND_EP_IN 0x82
#define VND_EP_OUT 0x02

#if !USB_CLASS

void USB_Device_VND()
{
        int  numBytesToRead, numBytesRead, numAvailByte;
        static char buf[USB_VND_BUFSZIE];

        buf[0] = 'h';
  /*      buf[1] = 'e';
        buf[2] = 'l';
        buf[3] = 'l';
        buf[4] = 'l';
        buf[5] = '0';
        buf[6] = '\n';*/
        Timer_Init();
		LED_Init();
		LED_On(LED_NONE);


        USB_Init();
		USB_Connect(TRUE);                        // USB Connect
		while (!USB_Configuration) ;              // wait until USB is configured
		while(1)
		{
			Timer_Delay(1000);
			//uint8_t c = LED_Count();
			//buf[0] = c;
			USB_WriteEP (VND_EP_IN, (unsigned char *)&buf[0], 1);
		}
}

#endif /* !USB_CLASS */
