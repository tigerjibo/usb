#include "lpc17xx_gpio.h"
#include "lpc17xx_clkpwr.h"

#include "lpc17xx_gpio.h"
#include "lpc17xx_clkpwr.h"

void LEDBlinkExp(){
    int i, j;
    unsigned long LED_PINS  =  ((uint32_t)1<<2)|((uint32_t)1<<4) ;

    /* Enable GPIO Clock */
    CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCGPIO, ENABLE);
    /* LEDs on PORT2.2 & PORT2.4 defined as Output  */
    GPIO_SetDir(2, LED_PINS, 1);

    while(1) {
	    /* Delay some time */
	    for(i=500; i>0; i--)
		    for(j=10000; j>0; j--) {
		    }
	    /* Output low level  */
		GPIO_ClearValue(2, 0X14);
		/* Delay some time */
		for(i=500; i>0; i--)
			for(j=10000; j>0; j--) {				
			}
		/* Output high level */
		GPIO_SetValue(2, 0X14);
	  }
}
