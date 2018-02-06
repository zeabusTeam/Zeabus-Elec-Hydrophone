/*
 * hw_accel.c
 *
 *  Created on: Apr 22, 2015
 *  Author : Anol Paisal
 * 	Company : EmOne (Thailand) Co.,Ltd.
 * 	Email : anolpaisal@gmail.com
 * 	Copyright @ 2015
 */

#include <sys/platform.h>
#include <services/int/adi_int.h>
#include "common.h"
#include "hw_accel.h"

/*******************************************************************
 *   Function:    Init_FIR
 *   Description: initializes the FIR interface
 *******************************************************************/
void Init_FIR(void) {
	int temp;
	//Mapping the FIR DMA interrupt
	temp = *pPICR0;
	temp &= ~(P17I2);
	//*pPICR1 &= ~(P6I0 | P6I1 | P6I2 | P6I3 | P6I4);
	temp |= (P17I0 | P17I1 | P17I3 | P17I4);
	//*pPICR1 |= (P6I0 | P6I1 | P6I2);
	*pPICR0 = temp;
	adi_int_InstallHandler(ADI_CID_P17I, (ADI_INT_HANDLER_PTR) ACC_DMA_ISR,
			NULL, true);
	//adi_int_InstallHandler(ADI_CID_P6I, (ADI_INT_HANDLER_PTR) ACC_MAC_ISR, NULL,
	//		true);

	//	//interrupt(SIG_P0,ACC_ISR);

	/* Power Management : PMCTL1 */
	temp = *pPMCTL1;
	temp &= ~(ACCOFF | FIRACCSEL | IIRACCSEL | FFTACCSEL); //Selecting the FIR Accelerator
	*pPMCTL1 = temp;
	asm("nop;nop;nop;nop;");

	/* Global Control : FIRCTL1 */
	//*pFIRCTL1 &= ~FIR_DMAEN;
	/* Channel Control :FIRCTL2 */
	//pFIRCTL2 |= (FIR_RATIO4);
	/* Debug Control : FIRDEBUGCTL */
	//*pFIRDEBUGCTL |= (FIR_DBGMODE | FIR_DBGMEM | FIR_HLD | FIR_ADRINC);
	//*pFIRDBGADDR = (unsigned int)In1_buf;
	//firctl1 = *pFIRCTL1;
//	//Initializing the chain pointer register
	temp = (((int) fir_right_in1_tcb + 12) & 0x7FFFF) | 1 << 19;
	*pCPFIR = temp;
	//Now Enabling the FIR Accelerator
	temp = FIR_EN | FIR_DMAEN | FIR_CH4 | FIR_RND0 | FIR_CAI;
	*pFIRCTL1 = temp;
}
