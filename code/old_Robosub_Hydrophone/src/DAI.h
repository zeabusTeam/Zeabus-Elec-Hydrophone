/*
 * DAI.h
 *
 *  Created on: Jan 13, 2015
 *  Author : Anol Paisal
 * Company : EmOne (Thailand) Co.,Ltd.
 * Email : anolpaisal@gmail.com
 * Copyright @ 2015
 */

#ifndef DAI_H_
#define DAI_H_

void Clear_DAI_Pins(void);
//void Init_DAI(void);
void Init_DAI_I2S(void);
void Init_TDM_DAI(MODE_SAMPLE_RATE sampe_rate);

#endif /* SRU_H_ */
