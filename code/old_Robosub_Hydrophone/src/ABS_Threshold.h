/*****************************************************************************
 * ABS_Threshold.h
 * Author : Anol Paisal
 * Company : EmOne (Thailand) Co.,Ltd.
 * Email : anolpaisal@gmail.com
 * Copyright @ 2015
 *****************************************************************************/

#ifndef __ABS_THRESHOLD_H__
#define __ABS_THRESHOLD_H__

#include <stdint.h>

/* Declare myFunction() */
bool ABS_Threshold( float *H1,  float *H2,  float *H3, float *H4, int index,float thres, uint_fast8_t* status);

#endif /* __ABS_THRESHOLD_H__ */
