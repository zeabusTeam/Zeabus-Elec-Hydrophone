/*
 * Author : Anol Paisal
 * Company : EmOne (Thailand) Co.,Ltd.
 * Email : anolpaisal@gmail.com
 * Copyright @ 2015
 * Base on pb_led_test.h ( ) @ Analog Devices, Inc.
 *		CHANGES:  1.00.0  - initial release
 */

#ifndef _PUSHBUTTON_H_
#define _PUSHBUTTON_H_

/* function prototypes */
void Init_PushButtons(void);
void Pushbutton_ISR(int sig_int);
/*******************************************************************
 *  function prototypes
 *******************************************************************/
void SW8_IRQ1_handler(int sig, void *);
void SW9_IRQ2_handler(int sig, void *);
void SW10_SW11_DAI_handler(int, void *);
#endif /* _PUSHBUTTON_H_ */
