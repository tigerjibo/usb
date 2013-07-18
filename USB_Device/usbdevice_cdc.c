#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
#include "lpc_types.h"
#include "LPC17xx.h"

#include "usbdevice.h"

#if USB_CDC
#include "cdc.h"
#include "cdcuser.h"
#include "serial.h"

#include "timer.h"

void USB_Device_CDC()
{
        int  numBytesToRead, numBytesRead, numAvailByte;
        static char serBuf [USB_CDC_BUFSIZE];
        static unsigned char b[1];
        b[0] = 'h';
	#if PORT_NUM
        CDC_Init (1);
	#else
	  	CDC_Init (0);
	#endif

	  	Timer_Init();
	  	LED_Init();
        USB_Init();
        USB_Connect(TRUE);                        // USB Connect
        while (!USB_Configuration) ;              // wait until USB is configured

        uint8_t buffer[10];
        uint32_t idx, len;

        while(1)
        {
        	len = 0;
        	while(len == 0)
        	{
        		len = UARTReceive((LPC_UART_TypeDef *)LPC_UART0, buffer, sizeof(buffer));
        	}
        	idx = 0;
			while (idx < len)
			{
				UARTSend((LPC_UART_TypeDef *)LPC_UART0, &buffer[idx], 1);
				idx++;
			}
			USB_WriteEP (CDC_DEP_IN, buffer, len);

  /*              CDC_OutBufAvailChar (&numAvailByte);
                if (numAvailByte > 0)
                {
                	numBytesToRead = numAvailByte > 32 ? 32 : numAvailByte;
                    numBytesRead = CDC_RdOutBuf (&serBuf[0], &numBytesToRead);
                    USB_WriteEP (CDC_DEP_IN, (unsigned char *)&serBuf[0], numBytesRead);
                }*/
          /*      else
                {
                	Timer_Delay(100);
                	USB_WriteEP (CDC_DEP_IN, b, 1);
                }*/
        }
}
#endif /* USB_CDC */
