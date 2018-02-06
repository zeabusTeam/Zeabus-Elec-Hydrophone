/*
 * UART.c
 *
 *  Created on: Apr 22, 2015
 * Author : Anol Paisal
 * Company : EmOne (Thailand) Co.,Ltd.
 * Email : anolpaisal@gmail.com
 * Copyright @ 2015
 */

#include <sys/platform.h>
#include <sru.h>
#include <services/int/adi_int.h>
#include <stdio.h>
#include <builtins.h>

#include "UART.h"
#include "led.h"
#include "common.h"

extern pm InputParam input;
//extern pm int THRES_FRONT; //Div by 10 {0.1 ~0.9}
//extern pm int THRES_PWR; //Div by 100 {0.01 ~0.09}
//extern bool gb_sw8_pushed;
//extern bool gb_sw9_pushed;
/*DMA Transfer TCB
 * Peripheral
 DMA Bus
 Arbiter
 Optional
 (Stage 2)J 0 (highest) UART0RX UART0RXCTL IIUART0RX, IMUART0RX,
 CUART0RX, CPUART0RX,
 1 (lowest) UART0TX UART0TXCTL IIUART0TX, IMUART0TX,
 CUART0TX, CPUART0TX,*/
int UART_RXTX_TCB[4] = { 0,					//RXCP_UAC0/TXCP_UAC0 Chain Pointer
		UART_DEBUG_BUFFER_LINE_SIZE,	//RXC_UAC0/TXC_UAC0 Internal Count
		1,								//RXM_UAC0/TXM_UAC0 Internal Modifier
		(int) &UART_DEBUG_BUFFER			//RXI_UAC0/TXI_UAC0	Internal Index
		};

/*******************************************************************
 *   Function:    UART_ESTIMATEBEARING_PRINT
 *   Description: Prints estimate bearing info over the UART using a predefined
 *				 buffer.
 *******************************************************************/
void UART_ESTIMATEBEARING_PRINT(char * data, int len) {
	unsigned int i = 0; /* index */
	char temp; /* temp char */

	/* loop through the debug buffer until the end, a NULL, or an error */
	for (i = 0; i < len; i++) {
		temp = data[i];
		PutChar(temp);
	}
}

/*******************************************************************
 *   Function:    GetChar
 *   Description: Reads a character from the UART.

 *******************************************************************/
unsigned int count = 0x0;
int GetChar(char * const cVal) {
	int loop = 0;

	do {
//		if (1 /*UARTDR == (*pUART0LSR & UARTDR)*/) {
		if (*pUART0LSR & UARTDR) {
			UART_DEBUG_BUFFER_RX[count] = (char) *pUART0RBR;
			printf("Received data[%d] 0x%x\n", count,
					UART_DEBUG_BUFFER_RX[count]);
//			PutChar(UART_DEBUG_BUFFER_RX[count]);
			count++;

			break;
		}
		loop++;
	} while (loop < 0x100000);

	return loop;
}

/*******************************************************************
 *   Function:    UART_DEBUG_PRINT
 *   Description: Prints debug info over the UART using a predefined
 *				 buffer.
 *******************************************************************/
int UART_DEBUG_PRINT(void) {
	unsigned int i = 0; /* index */
	char temp; /* temp char */

	/* loop through the debug buffer until the end, a NULL, or an error */
	for (i = 0; i < UART_DEBUG_BUFFER_LINE_SIZE; i++) {
		temp = UART_DEBUG_BUFFER[i];

		/* if not NULL then print it */
		if (temp) {
			if (0 == PutChar(temp)) {
				/* if error was detected then quit */
				return 0;
			}

			/* if it was a newline we need to add a carriage return */
			if (0x0a == temp) {
				if (0 == PutChar(0x0d)) {
					/* if error was detected then quit */
					return 0;
				}
			}
		} else {
			/* else NULL was found */
			return 1;
		}
	}

	return 1;
}

/*******************************************************************
 *   Function:    PutChar
 *   Description: Writes a character to the UART.
 *******************************************************************/
int PutChar(const char cVal) {
	int nStatus = 0;
	unsigned int count = 0;

	do {
		if ((*pUART0LSR & UARTTHRE)) {
			*pUART0THR = cVal;
			nStatus = 1;
			break;
		}

		count++;

	} while (count < 0x100000);

	return nStatus;
}

/*******************************************************************
 *   Function:    UART_DEBUG_PRINT
 *   Description: Prints debug info over the UART using a predefined
 *				 buffer.
 *******************************************************************/
void UART_PRINT(int size) {
	unsigned int i = 0; /* index */
	/* loop through the debug buffer until the end, a NULL, or an error */
	for (i = 0; i < size; i++) {
		PutChar(UART_DEBUG_BUFFER[i]);
	}
}

/*******************************************************************
 *   Function:    Init_UART
 *   Description: Initialize UART with the appropriate values
 *******************************************************************/
void Init_UART(void) {
	volatile int temp;
	int picr2 = 0x0;

	/* maps the UART0 receive interrupt to P14 using the programmable interrupt controller */

	picr2 = *pPICR2; /* get PICR2 */
	picr2 &= (~(0x1f << 10)); /* clear P14 bits */
	picr2 |= (0x13 << 10); /* set UART0RX */
	(*pPICR2) = picr2; /* put it back */

	sysreg_bit_set(sysreg_IMASK, P14I);
	adi_int_InstallHandler(ADI_CID_DPII, (ADI_INT_HANDLER_PTR) uart_RX_ISR,
	NULL, true);
	/* unmask UART RX interrupt */

	(*pUART0IER) = UARTRBFIE;/* enable UART RX interrupt */

	SRU2(UART0_TX_O, DPI_PB09_I);
	/* UART TX signal is connected to DPI pin 9 */
	SRU2(HIGH, DPI_PBEN09_I);
	SRU2(DPI_PB10_O, UART0_RX_I);
	/* connect the pin buffer output signal to the UART0 RX */
	SRU2(LOW, DPI_PB10_I);
	SRU2(LOW, DPI_PBEN10_I);
	/* disable DPI pin10 as input */

	(*pUART0LCR) = UARTDLAB; /* enables access to divisor register to set baud rate */
#ifdef __ADSP21469__
	(*pUART0DLL) = 0xdc;
	(*pUART0DLH) = 0x2; /* 0x2dc = 732 for divisor value gives a baud rate of 19200 at 450 Mhz core clock */
#elif (__ADSP21479__)
	(*pUART0DLL) = 0xb0;
	(*pUART0DLH) = 0x1; /* 0x1B0 = 432 for divisor value gives a baud rate of 19200 at 266 Mhz core clock */
#elif (__ADSP21489__)
	//(*pUART0DLL) = 0x8b;
	//(*pUART0DLH) = 0x2; /* 0x28b = 651 for divisor value gives a baud rate of 19200 at 400 Mhz core clock */
	(*pUART0DLL) = 0x6D;
	(*pUART0DLH) = 0x00; /* 0xd9 = 271 for divisor value gives a baud rate of 115200 at 400 Mhz core clock */
#endif
	//(*pUART0LCR) = (UARTWLS8 | UARTPEN | UARTSTB);   /* 8 bit word, odd parity, 2 stop bits */
	(*pUART0LCR) = (UARTWLS8); /* 8 bit word, non parity, 1 stop bits */
	(*pUART0RXCTL) = UARTEN; /* enable UART0 RX */
	(*pUART0TXCTL) = UARTEN; /* enable UART0 TX */
}

void fillData(void* in) {
	unsigned long tmp = 0;
	tmp |= UART_DEBUG_BUFFER_RX[3];
	tmp |= UART_DEBUG_BUFFER_RX[4] << 8;
	tmp |= UART_DEBUG_BUFFER_RX[5] << 16;
	tmp |= UART_DEBUG_BUFFER_RX[6] << 24;
	__builtin_memcpyDD(in, &tmp, sizeof(unsigned long));
}

void uart_RX_ISR(uint32_t iid, void* param) {
//	int i;
//	for (i = 0; i < UART_DEBUG_BUFFER_LINE_SIZE; ++i) {
	GetChar(UART_DEBUG_BUFFER_RX);
//	}
	if (count > 1) {
		if (UART_DEBUG_BUFFER_RX[0] != 0xff
				&& UART_DEBUG_BUFFER_RX[1] != 0xff) {
			count = 0;
			return;
		}

		if (count > 7) {
			if (UART_DEBUG_BUFFER_RX[7] != 0x00) {
				count =0;
				return;
			}
			switch (UART_DEBUG_BUFFER_RX[2]) {
			case 0x00:
				fillData(&input.DelayObserve);
				break;
			case 0x01:
				fillData(&input.Frequency);
				ClearSet_Freq_LED(input.Frequency);
				break;
			case 0x02:
				fillData(&input.FrontThreshold);
				break;
			case 0x03:
				fillData(&input.PowerThreshold);
				break;
			case 0x04:
				fillData(&input.SoundSpeed);
				break;
			default:
				break;
			}
			count = 0;
		}
	}
}

