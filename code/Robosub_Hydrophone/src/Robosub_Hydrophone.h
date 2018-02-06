/*****************************************************************************
 * Robosub_Hydrophone.h
 * Author : Anol Paisal
 * Company : EmOne (Thailand) Co.,Ltd.
 * Email : anolpaisal@gmail.com
 * Copyright @ 2015
 *****************************************************************************/

#ifndef __ROBOSUB_HYDROPHONE_H__
#define __ROBOSUB_HYDROPHONE_H__

#include <services/int/adi_int.h>
#include "common.h"
#include <complex.h>

/* Add your custom header content here */
int processing(float * azimuth, float * elavator, float * pwr, complex_float *cout, const uint32_t freq);

//void Block_Fixed_To_Float(int * Fixed_In, float * Float_Out_L,
//		float * Float_Out_R);
//void Block_Float_To_Fixed(int * Fixed_Out, float * Float_In_L,
//		float * Float_In_R);
//
////----- Prototypes ------------------------------------------------------------
//word16 checksum(byte *addr, word32 count);
//void UART_PRINT(int size);

void GetFrameHandler (uint32_t iid, void * callback_data);
void PrintOutput(OutputResult pm* output);

#endif /* __ROBOSUB_HYDROPHONE_H__ */
