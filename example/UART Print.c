#include "lpc17xx_uart.h"
#include "lpc17xx_pinsel.h"
#include "UART_Interrupt.h"


LPC_UART_TypeDef *UARTx = (LPC_UART_TypeDef *)LPC_UART0;
void UART_PrintExp()
{
	static unsigned char rxbuf[4];


	/* UART Configuration structure variable */
	UART_CFG_Type UARTConfigStruct;
	/* UART FIFO configuration Struct variable */
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;
	/* Pin configuration for UART0 */
	PINSEL_CFG_Type PinCfg;


	if((uint32_t)UARTx == (uint32_t)LPC_UART0) {
		/*
		 * Initialize UART0 pin connect
		 */
		PinCfg.Funcnum = 1;
		PinCfg.OpenDrain = 0;
		PinCfg.Pinmode = 0;
		PinCfg.Pinnum = 2;
		PinCfg.Portnum = 0;
		PINSEL_ConfigPin(&PinCfg);
		PinCfg.Pinnum = 3;
		PINSEL_ConfigPin(&PinCfg);
	}
	else if ((uint32_t)UARTx == (uint32_t)LPC_UART2) {
		/*
		 * Initialize UART1 pin connect
		 */
		PinCfg.Funcnum = 1;
		PinCfg.OpenDrain = 0;
		PinCfg.Pinmode = 0;
		PinCfg.Pinnum = 10;
		PinCfg.Portnum = 0;
		PINSEL_ConfigPin(&PinCfg);
		PinCfg.Pinnum = 11;
		PINSEL_ConfigPin(&PinCfg);
	}

	/* Initialize UART Configuration parameter structure to default state:
	 * Baudrate = 9600bps
	 * 8 data bit
	 * 1 Stop bit
	 * None parity
	 */
	UART_ConfigStructInit(&UARTConfigStruct);

	/* Set Baudrate to 115200 */
	//UARTConfigStruct.Baud_rate = 115200;

	/* Initialize UART0 peripheral with given to corresponding parameter */
	UART_Init(UARTx, &UARTConfigStruct);

	/* Initialize FIFOConfigStruct to default state:
	 * 				- FIFO_DMAMode = DISABLE
	 * 				- FIFO_Level = UART_FIFO_TRGLEV0
	 * 				- FIFO_ResetRxBuf = ENABLE
	 * 				- FIFO_ResetTxBuf = ENABLE
	 * 				- FIFO_State = ENABLE
	 */
	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);

	/* Initialize FIFO for UART0 peripheral */
	UART_FIFOConfig(UARTx, &UARTFIFOConfigStruct);



	/*  Enable UART Transmit */
	UART_TxCmd(UARTx, ENABLE);

	UART_IntConfig(UARTx, UART_INTCFG_RBR, ENABLE);
	UART_IntConfig(UARTx, UART_INTCFG_RLS, ENABLE);

	  TxIntStat = RESET;

	        // Reset ring buf head and tail idx
	        __BUF_RESET(rb.rx_head);
	        __BUF_RESET(rb.rx_tail);
	        __BUF_RESET(rb.tx_head);
	        __BUF_RESET(rb.tx_tail);

	    /* preemption = 1, sub-priority = 1 */
	    NVIC_SetPriority(UART0_IRQn, ((0x01<<3)|0x01));
	        /* Enable Interrupt for UART0 channel */
	    NVIC_EnableIRQ(UART0_IRQn);


	        // print welcome screen
	        print_menu();


}



