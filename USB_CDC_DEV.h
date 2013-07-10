#include "LPC17xx.h"
#include "lpc17xx_clkpwr.h"
#include "lpc_types.h"

/*----------------------------------------------------------------------------
Include USB Stack
 *---------------------------------------------------------------------------*/
#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
#include "cdc.h"
#include "cdcuser.h"
#include "serial.h"

void LPC_USB_CDC()
{
        static char serBuf [USB_CDC_BUFSIZE];
        int  numBytesToRead, numBytesRead, numAvailByte;

        USB_Init();
        USB_Connect(TRUE);                        // USB Connect
        while (!USB_Configuration) ;              // wait until USB is configured
        while(1)
        {
                CDC_OutBufAvailChar (&numAvailByte);
                if (numAvailByte > 0)
                {
                        numBytesToRead = numAvailByte > 32 ? 32 : numAvailByte;
                    numBytesRead = CDC_RdOutBuf (&serBuf[0], &numBytesToRead);
                    USB_WriteEP (CDC_DEP_IN, (unsigned char *)&serBuf[0], numBytesRead);
                }
        }
}
