/*
 * hw_accel.h
 *
 *  Created on: Feb 7, 2015
 *  Author : Anol Paisal
 * 	Company : EmOne (Thailand) Co.,Ltd.
 * 	Email : anolpaisal@gmail.com
 * 	Copyright @ 2015
 */

#ifndef HW_ACCEL_H_
#define HW_ACCEL_H_


extern int fir_right_in1_tcb[13];
extern int fir_left_in1_tcb[13];
extern int fir_right_in2_tcb[13];
extern int fir_left_in2_tcb[13];

void Init_FFT(void);
void Init_FIR(void);
void Init_IIR(void);

void ACC_ISR(void);
void ACC_DMA_ISR(void);

#endif /* HW_ACCEL_H_ */
