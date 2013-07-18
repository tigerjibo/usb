#ifndef _LED_H_
#define _LED_H_

#include "lpc_types.h"

#define LED_PORT_NUM 2
#define LED0 0x01
#define LED1 0x02
#define LED2 0x04
#define LED3 0x08
#define LED4 0x10
#define LED5 0x20
#define LED6 0x40
#define LED7 0x80
#define LED_ALL 0xFF
#define LED_NONE 0x00

extern void LED_Init();
extern void LED_On(uint32_t led);
extern void LED_Off(uint32_t led);
extern uint8_t LED_Count();

#endif
