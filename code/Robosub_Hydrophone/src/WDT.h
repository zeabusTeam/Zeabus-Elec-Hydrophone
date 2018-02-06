/*
 * WDT.h
 *
 *  Created on: Jan 13, 2015
 * Author : Anol Paisal
 * Company : EmOne (Thailand) Co.,Ltd.
 * Email : anolpaisal@gmail.com
 * Copyright @ 2015
 */

#ifndef WDT_H_
#define WDT_H_

/*******************************************************************
*  global variables and defines
*******************************************************************/
#define CMD_UNLOCK 0xAD21AD21
#define CMD_LOCK	0
#define COUNT_VALUE	0x3FFFFF
#define TRIP_VALUE	0x7

void Init_WDT(void);
void preventWDT(void);

#endif /* WDT_H_ */
