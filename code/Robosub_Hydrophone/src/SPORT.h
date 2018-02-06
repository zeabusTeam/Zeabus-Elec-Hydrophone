/*
 * SPORT.h
 *
 *  Created on: Jan 13, 2015
 * Author : Anol Paisal
 * Company : EmOne (Thailand) Co.,Ltd.
 * Email : anolpaisal@gmail.com
 * Copyright @ 2015
 */

#ifndef SPORT_H_
#define SPORT_H_

#include "common.h"

//void Init_SPORT(void);
void enable_SPORT012_I2S_mode(void);
void enable_SPORT012_MCM_mode(MODE_SAMPLE_RATE);
void enable_SPORT012_DMA_channels(MODE_SAMPLE_RATE);

#endif /* SPORT_H_ */
