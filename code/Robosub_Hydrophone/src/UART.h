/*
 * UART.h
 *
 *  Created on: Jan 12, 2015
 * Author : Anol Paisal
 * Company : EmOne (Thailand) Co.,Ltd.
 * Email : anolpaisal@gmail.com
 * Copyright @ 2015
 *      Description:  Universal asynchronous receiver/transmitter
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>

/*******************************************************************
 *  global variables and defines
 *******************************************************************/
#define BAUD_RATE_115200 	(0x15A2 >> 7)
#define NUM_TEST_CHARS		(1*1024)
#define UART_DEBUG_BUFFER_LINE_SIZE 256
char UART_DEBUG_BUFFER[UART_DEBUG_BUFFER_LINE_SIZE];
char UART_DEBUG_BUFFER_RX[UART_DEBUG_BUFFER_LINE_SIZE];

void Init_UART(void);
int GetChar(char * cVal);
int PutChar(const char cVal);
int UART_DEBUG_PRINT(void);
void UART_ESTIMATEBEARING_PRINT(char * data, int len);
void UART_PRINT(int size);

void uart_RX_ISR(uint32_t iid, void* param);

#endif /* UART_H_ */
