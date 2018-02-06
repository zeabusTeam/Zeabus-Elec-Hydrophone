/*
 * led.c
 *
 *  Created on: Apr 22, 2015
 *  Author : Anol Paisal
 * Company : EmOne (Thailand) Co.,Ltd.
 * Email : anolpaisal@gmail.com
 * Copyright @ 2015
 */

#include "led.h"
#include "common.h"

int g_LEDs[] = { LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8 };

/*******************************************************************
 *   Function:    LED_Bar
 *   Description: Display a blinking LED bar
 *******************************************************************/
void LED_Bar(const int iSpeed) {
	int n, j;

	for (n = 0; n <= g_nNumLEDs - 1; n++) {
		ClearSet_LED(g_LEDs[n], LED_TOGGLE);
		Delay(iSpeed);
	}
}

/*******************************************************************
 *   Function:    LED_Bar_Reverse
 *   Description: Display a blinking LED bar in reverse
 *******************************************************************/
void LED_Bar_Reverse(const int iSpeed) {
	int n, j;

	for (n = g_nNumLEDs - 1; n >= 0; n--) {
		ClearSet_LED(g_LEDs[n], LED_TOGGLE);
		Delay(iSpeed);
	}
}

/*******************************************************************
 *   Function:    LED_Bar_BacknForth
 *   Description: Display a blinking LED bar that goes back and forth.
 *******************************************************************/
void LED_Bar_BacknForth(const int iSpeed) {
	static unsigned int state = 0; /* remember the state */

	if ((state % 4) == 0) {
		ClearSet_LED(LED1, 1);
		ClearSet_LED(LED2, 0);
		ClearSet_LED(LED3, 0);
	} else if ((state % 4) == 1) {
		ClearSet_LED(LED1, 0);
		ClearSet_LED(LED2, 1);
		ClearSet_LED(LED3, 0);
	} else if ((state % 4) == 2) {
		ClearSet_LED(LED1, 0);
		ClearSet_LED(LED2, 0);
		ClearSet_LED(LED3, 1);
	} else {
		ClearSet_LED(LED1, 0);
		ClearSet_LED(LED2, 1);
		ClearSet_LED(LED3, 0);
	}

	Delay(iSpeed);
	state++;
}

/*******************************************************************
 *   Function:    Strobe_LEDs
 *   Description: This strobes the LEDs based on the pattern provide
 *				 with a specified delay until the condition is met.
 *				 If the condition is NULL, we strobe once and exit.
 *******************************************************************/
void Strobe_LEDs(unsigned int pattern_a, unsigned int pattern_b,
		unsigned int delay, bool *pbDone) {
	int cnt = 0;
	volatile bool b = false;

	/* use a copy in case pbDone is NULL */
	if (NULL != pbDone)
		b = *pbDone;

	while (!b) {
		for (cnt = delay; cnt > 0; cnt--) {
			ClearSet_LED_Bank(pattern_a);
			Delay(cnt); /* delay decreasing */

			ClearSet_LED_Bank(pattern_b);
			Delay(delay - cnt); /* delay increasing */
		}

		/* check it again */
		if (NULL != pbDone) {
			b = *pbDone;
			if (b)
				break; /* if not NULL see if condition has now been met */
		} else
			b = true; /* after one time break out if NULL */

		for (cnt = 0; cnt < delay; cnt++) {
			ClearSet_LED_Bank(pattern_a);
			Delay(cnt); /* delay increasing */

			ClearSet_LED_Bank(pattern_b);
			Delay(delay - cnt); /* delay decreasing */
		}
	}
}

/*******************************************************************
 *   Function:    Blink_LED
 *   Description: Blink various LEDs
 *******************************************************************/
void Blink_LED(const int iSpeed) {
	int n, j;

	while (1) {
		for (n = 0; n <= g_nNumLEDs - 1; n++) {
			ClearSet_LED(g_LEDs[n], LED_TOGGLE);
		}

		Delay(iSpeed);
	}
}

/*******************************************************************
 *   Function:    ClearSet_LED_Bank
 *   Description: Clear or sets the group of LEDs based on specified state.
 *******************************************************************/
void ClearSet_LED_Bank(const int iState) {
	int n;
	int nTempState = iState;

	for (n = 0; n <= g_nNumLEDs - 1; n++) {
		ClearSet_LED(g_LEDs[n], (nTempState & 0x3));
		nTempState >>= 2;
	}
}

void ClearSet_Freq_LED(const uint32_t freq){
	int i;

	int state = ((freq - MIN_FREQ)/ 1000) % 16;

	ClearSet_LED(LED1, (state) & 0x1);
	ClearSet_LED(LED2, (state >> 1) & 0x1);
	ClearSet_LED(LED3, (state >> 2) & 0x1);
	ClearSet_LED(LED4, (state >> 3) & 0x1);

}


