/*
 * init.c
 *
 *  Created on: Jan 29, 2015
 * Author : Anol Paisal
 * Company : EmOne (Thailand) Co.,Ltd.
 * Email : anolpaisal@gmail.com
 * Copyright @ 2015
 */

#include <sys/platform.h>
#include <sru.h>

#include "AD1939.h"
#include "SPI.h"
#include "WDT.h"
#include "led.h"
#include "UART.h"

#include "common.h"
#include <services/int/adi_int.h>

#include "Robosub_Hydrophone.h"

//extern volatile bool g_ReadyProcess;

bool pm gb_sw8_pushed = true;
bool pm gb_sw9_pushed = false;
extern pm OutputResult output;
extern pm InputParam input;
/* TCB = "Transfer Control Block" */
/* TCB format:    ECx (length of destination buffer),
 EMx (destination buffer step size),
 EIx (destination buffer index (initialized to start address)),
 GPx ("general purpose"),
 CPx ("Chain Point register"; points to last address (IIx) of
 next TCB to jump to
 upon completion of this TCB.),
 Cx  (length of source buffer),
 IMx (source buffer step size),
 IIx (source buffer index (initialized to start address))       */
int I2S_rcv1a_tcb[8] = { 0, 0, 0, 0, 0, 2, 1, (int) I2S_rx1a_buf }; /* SPORT1 receive a tcb */
int I2S_rcv1b_tcb[8] = { 0, 0, 0, 0, 0, 2, 1, (int) I2S_rx1b_buf }; /* SPORT1 receive b tcb */
int I2S_xmit0a_tcb[8] = { 0, 0, 0, 0, 0, 2, 1, (int) I2S_tx0a_buf }; /* SPORT0 transmit a tcb */
int I2S_xmit0b_tcb[8] = { 0, 0, 0, 0, 0, 2, 1, (int) I2S_tx0b_buf }; /* SPORT0 transmit a tcb */
int I2S_xmit2a_tcb[8] = { 0, 0, 0, 0, 0, 2, 1, (int) I2S_tx2a_buf }; /* SPORT2 transmit a tcb */
int I2S_xmit2b_tcb[8] = { 0, 0, 0, 0, 0, 2, 1, (int) I2S_tx2b_buf }; /* SPORT2 transmit a tcb */

//////////////////////////////////////////////////////
// TDM definitions for 192 kHz sample rate
//
//////////////////////////////////////////////////////
int TDM_rcv1a_tcb[8] = { 0, 0, 0, 0, 0, 4, 1, (int) TDM_rx1a_buf }; /* SPORT1 receive tcb */
int TDM_xmit0a_tcb[8] = { 0, 0, 0, 0, 0, 4, 1, (int) TDM_tx0a_buf }; /* SPORT0 transmit A tcb */
int TDM_xmit0b_tcb[8] = { 0, 0, 0, 0, 0, 4, 1, (int) TDM_tx0b_buf }; /* SPORT0 transmit B tcb */
int TDM_xmit2a_tcb[8] = { 0, 0, 0, 0, 0, 4, 1, (int) TDM_tx2a_buf }; /* SPORT2 transmit A tcb */
int TDM_xmit2b_tcb[8] = { 0, 0, 0, 0, 0, 4, 1, (int) TDM_tx2b_buf }; /* SPORT2 transmit B tcb */

/*******************************************************************
 *   Function:    Init_PLL
 *   Description: initializes the PLL registers
 *******************************************************************/
void Init_PLL(void) {
	int pmctlsetting, i;

	// Step 1 - change the PLLD to 4
	pmctlsetting = *pPMCTL;
	pmctlsetting &= ~PLLD16;
	pmctlsetting |= (PLLD4 | DIVEN);
	*pPMCTL = pmctlsetting;

	// Step 2 - wait for dividers to stabilize
	for (i = 0; i < 16; i++)
		NOP;

	// Step 3 - set INDIV bit now to bring down the VCO speed and enter the bypass mode
	pmctlsetting &= ~DIVEN;
	pmctlsetting |= (INDIV | PLLBP);
	*pPMCTL = pmctlsetting;

	// Step 4 - wait for the PLL to lock
	for (i = 0; i < 4096; i++)
		NOP;

	// Step 5 - come out of the bypass mode
	pmctlsetting = *pPMCTL;
	pmctlsetting &= ~PLLBP;
	*pPMCTL = pmctlsetting;

	// Step 6 - wait for dividers to stabilize
	for (i = 0; i < 16; i++)
		NOP;

	// Step 7 - set the required PLLM and INDIV values here  and enter the bypass mode
	pmctlsetting = *pPMCTL;
	pmctlsetting &= ~(INDIV | PLLM63);
	pmctlsetting |= (PLL_MULT | PLLBP);
	*pPMCTL = pmctlsetting;

	// Step 8 - wait for the PLL to lock
	for (i = 0; i < 4096; i++)
		NOP;

	// Step 9 - come out of the bypass mode
	pmctlsetting = *pPMCTL;
	pmctlsetting &= ~PLLBP;
	*pPMCTL = pmctlsetting;

	// Step 10 - wait for dividers to stabilize
	for (i = 0; i < 16; i++)
		NOP;

	// Step 11 - set the required values of PLLD(=2) and SDCKR (=2.5 for ADSP-21489 and 2 for ADSP-21479) here
	pmctlsetting = *pPMCTL;
	pmctlsetting &= ~(PLLD16 | 0x1C0000);
#ifdef __ADSP21489__
	pmctlsetting |= (SDCKR2_5 | PLLD2 | DIVEN);
#elif __ADSP21479__
	pmctlsetting|= (SDCKR2 | PLLD2 | DIVEN);
#endif
	*pPMCTL = pmctlsetting;

	// Step 12 - wait for the dividers to stabilize
	for (i = 0; i < 16; i++)
		NOP;
}

/*******************************************************************
 *   Function:    Init_SDRAM
 *   Description: initializes the SDRAM registers
 *******************************************************************/
void Init_SDRAM(void) {
	// SDRAM memory on EZ-Board - MT48LC16M16A2-6A
	//// 5.4ns @ CL = 3 ,167 MHz speed
	//// Parameters
	//// Config - 64M x 16(16M x 16 x 4)
	//// Speed -        167 MHz
	//// CAS Latency -   3
	//// Row addressing - 8K(A0-A12)
	//// Column addressing - 512(A0-A8)
	//// No of Banks - 4
	//
	////tRAS - 42ns
	////tRCD - 18ns
	////tRP - 18ns
	////tRC - 60ns( tRP + tRAS >= tRC)
	////tWR - (1CLK + 6ns)
	//
	////For the 160 MHz case, tSDCLK = 1/160 MHz = 6.25ns
	//// CAS Latency = 3
	//// tRCD = 18 / 6.25 = 3(2.88)
	//// tRP = 18 / 6.25 = 3(2.88)
	//// tRC = 60 / 6.25 = 10
	//// tRAS = 42/ 6.25 = 7(6.72)
	//// tWR = (6.25 + 6)/6.25 = 2(1.96)
	//// fSDCLK = 160 MHz
	//// tREF=  64ms
	//// NRA = 8192
	//
	//// RDIV = ((f SDCLK X t REF)/NRA) - (t RAS + t RP)
	//// RDIV = (((160 X 10^6 x 64 x 10^-3)/8192) - (7 + 3))
	//// RDIV = 1240 = 0x4D8
	int nValue = 0;

	*pSYSCTL |= MSEN;

	// Mapping Bank 0 to SDRAM
	*pEPCTL |= B0SD;
	*pEPCTL &= (~(B1SD | B2SD | B3SD));

	nValue = RDIV;
	nValue |= SDROPT | BIT_17; // Enabling SDRAM read optimization
							   // Setting the Modify to 1
	*pSDRRC = nValue;

	// Programming SDRAM control register
	nValue = 0;
#ifdef __ADSP21489__
	nValue |= (SDCL3 | SDTRAS7 | SDTRP3 | SDCAW9 | SDPSS | SDTWR2 | SDTRCD3
			| SDRAW13 | X16DE);
#elif __ADSP21479__
	nValue |= (SDCL3|SDTRAS6|SDTRP3|SDCAW9|SDPSS|SDTWR2|SDTRCD3|SDRAW13|X16DE);
#endif
	*pSDCTL = nValue;

	*pSYSCTL |= EPDATA32; // Data [31:0] pins are configured as data lines

	// Flash is connected on Bank 1
	// Programming maximum waitstates

	*pAMICTL1 = AMIEN | BW8 | WS31;

	// SRAM is connected on Bank 3
	// SRAM part used - IS61WV102416BLL
	// As per datasheet access time is 10 ns, 8ns
	// Programming waitstates = 4

	*pAMICTL3 = AMIEN | BW16 | WS4;
}

void Clear_DAI_Pins(void) {
//------------------------------------------------------------------------
//  Tie the pin buffer inputs LOW for all DAI pins.  Even though
//    these pins are inputs to the SHARC, tying unused pin buffer inputs
//    LOW is "good coding style" to eliminate the possibility of
//    termination artifacts internal to the IC.  Note that signal
//    integrity is degraded only with a few specific SRU combinations.
//    In practice, this occurs VERY rarely, and these connections are
//    typically unnecessary.  This is GROUP D
	SRU(LOW, DAI_PB01_I);
	SRU(LOW, DAI_PB02_I);
	SRU(LOW, DAI_PB03_I);
	SRU(LOW, DAI_PB04_I);
	SRU(LOW, DAI_PB05_I);
	SRU(LOW, DAI_PB06_I);
	SRU(LOW, DAI_PB07_I);
	SRU(LOW, DAI_PB08_I);
	SRU(LOW, DAI_PB09_I);
	SRU(LOW, DAI_PB10_I);
	SRU(LOW, DAI_PB11_I);
	SRU(LOW, DAI_PB12_I);
	SRU(LOW, DAI_PB13_I);
	SRU(LOW, DAI_PB14_I);
	SRU(LOW, DAI_PB15_I);
	SRU(LOW, DAI_PB16_I);
	SRU(LOW, DAI_PB17_I);
	SRU(LOW, DAI_PB18_I);
	SRU(LOW, DAI_PB19_I);
	SRU(LOW, DAI_PB20_I);

//------------------------------------------------------------------------
//  Tie the pin buffer enable inputs LOW for all DAI pins so
//  that they are always input pins.  This is GROUP F.
	SRU(LOW, PBEN01_I);
	SRU(LOW, PBEN02_I);
	SRU(LOW, PBEN03_I);
	SRU(LOW, PBEN04_I);
	SRU(LOW, PBEN05_I);
	SRU(LOW, PBEN06_I);
	SRU(LOW, PBEN07_I);
	SRU(LOW, PBEN08_I);
	SRU(LOW, PBEN09_I);
	SRU(LOW, PBEN10_I);
	SRU(LOW, PBEN11_I);
	SRU(LOW, PBEN12_I);
	SRU(LOW, PBEN13_I);
	SRU(LOW, PBEN14_I);
	SRU(LOW, PBEN15_I);
	SRU(LOW, PBEN16_I);
	SRU(LOW, PBEN17_I);
	SRU(LOW, PBEN18_I);
	SRU(LOW, PBEN19_I);
	SRU(LOW, PBEN20_I);
}

void Init_TDM_DAI(MODE_SAMPLE_RATE sampe_rate) {
	Clear_DAI_Pins();

//-----------------------------------------------------------------------------
//  Connect the AD1939 ADCs: The AD1939 drives a BCLK output to DAI pin 7,
//          a frame sync to DAI pin 8 and TDM rx data to DAI pins 5
//
//          Connect the TDM ADC stream to SPORT1, using data input A
//
//          All four lines are always inputs to the SHARC so tie the pin
//          buffer inputs and pin buffer enable inputs all low.
	SRU(DAI_PB07_O, SPORT2_CLK_I);
	SRU(DAI_PB07_O, SPORT1_CLK_I);
	// DAIP7 (RSCLK1) to SPORT1 CLK (CLK)
	SRU(DAI_PB07_O, SPORT0_CLK_I);
	// DAIP7 (RSCLK1) to SPORT0 CLK (CLK)

	SRU(DAI_PB08_O, SPORT2_FS_I);
	SRU(DAI_PB08_O, SPORT1_FS_I);
	// DAIP8 (RFS1) to SPORT1 FS (FS)
	SRU(DAI_PB08_O, SPORT0_FS_I);
	// DAIP8 (RFS1) to SPORT0 FS (FS)

	SRU(DAI_PB05_O, SPORT1_DA_I);
	// DAIP5 (DR1PRI) to SPORT1 DA (RX)

//-----------------------------------------------------------------------------
//  Connect the AD1939 DACs in TDM mode to SPORT0:
//          The clock and frame sync inputs are provided by the ADCs
//
//          All DAC connections are always outputs from the SHARC
//          so tie the pin buffer enable inputs all high.
//          Connect the TDM DAC stream to SPORT0 A via DAI pins 11 and 12

	SRU(HIGH, PBEN12_I);
	SRU(SPORT0_DA_O, DAI_PB12_I);
	// DAIP12 (DSDATA1) to SPORT0 DA (TX)
	SRU(HIGH, PBEN11_I);
	SRU(SPORT0_DB_O, DAI_PB11_I);
	// DAIP11 (DSDATA2) to SPORT0 DB (TX)

	SRU(HIGH, PBEN10_I);
	SRU(SPORT2_DA_O, DAI_PB10_I);
	// DAIP10 (DSDATA3) to SPORT2 DA (TX)
	SRU(HIGH, PBEN09_I);
	SRU(SPORT2_DB_O, DAI_PB09_I);
	// DAIP09 (DSDATA4) to SPORT2 DB (TX)

//--------------------------------------------------------------------------
// Route SPI signals to AD1939 Control Port.

	SRU(SPI_MOSI_O, DPI_PB01_I);
	//Connect MOSI to DPI PB1.
	SRU(DPI_PB02_O, SPI_MISO_I);
	//Connect DPI PB2 to MISO.
	SRU(SPI_CLK_O, DPI_PB03_I);
	//Connect SPI CLK to DPI PB3.
	SRU(SPI_FLG0_O, DPI_PB04_I);
	//Connect SPI FLAG0 to DPI PB4.

//---------------------------------------------------------------------------
// Tie pin buffer enable from SPI peipheral to determine whether they are
// inputs or outputs

	SRU(SPI_MOSI_PBEN_O, DPI_PBEN01_I);
	SRU(SPI_MISO_PBEN_O, DPI_PBEN02_I);
	SRU(SPI_CLK_PBEN_O, DPI_PBEN03_I);
	SRU(SPI_FLG0_PBEN_O, DPI_PBEN04_I);

//-----------------------------------------------------------------------------
// Set the SRU and route so that a Flag pins connects to DPI pin buffers.
// Use Flags 4 to 15 only. Flags 0 to 3 not available on the DPI.
//	// Enabling the Buffer using the following sequence: High -> Output, Low -> Input
//	SRU(HIGH,DPI_PBEN06_I);
//	SRU(HIGH,DPI_PBEN13_I);
//	SRU(HIGH,DPI_PBEN14_I);
}

void enable_SPORT012_MCM_mode(MODE_SAMPLE_RATE sampe_rate) {
	/* Clear out SPORT 0/1 registers */
	*pSPMCTL0 = 0;
	*pSPMCTL1 = 0;
	*pSPMCTL2 = 0;
	*pSPCTL0 = 0;
	*pSPCTL1 = 0;
	*pSPCTL2 = 0;

	/* External clock and frame syncs generated by AD1939 */
	*pDIV0 = 0x00000000; // Transmitter (SPORT0)
	*pDIV1 = 0x00000000; // Receiver (SPORT1) at 12.288 MHz SCLK and 48 kHz sample rate
	*pDIV2 = 0x00000000; // Transmitter (SPORT2)

	if (sampe_rate == TDM_192_KHZ_SAMPLE_RATE
			|| sampe_rate == TDM_192_KHZ_SAMPLE_RATE_OUT12
			|| sampe_rate == TDM_192_KHZ_SAMPLE_RATE_OUT34
			|| sampe_rate == EXTA_TDM_192_KHZ_SAMPLE_RATE_OUT12
			|| sampe_rate == EXTA_TDM_192_KHZ_SAMPLE_RATE_OUT34
			|| sampe_rate == EXTB_TDM_192_KHZ_SAMPLE_RATE_OUT12
			|| sampe_rate == EXTB_TDM_192_KHZ_SAMPLE_RATE_OUT34
			|| sampe_rate == EXTC_TDM_192_KHZ_SAMPLE_RATE_OUT12
			|| sampe_rate == EXTC_TDM_192_KHZ_SAMPLE_RATE_OUT34) {
		/* SPORT0 and SPORT1 are being operated in "multichannel" mode.
		 This is synonymous with TDM mode which is the operating mode for the AD1939 */

		/* SPORT 0&1  Miscellaneous Control Bits Registers */
		/* SP01MCTL = 0x000000E2,  Hold off on MCM enable, and number of TDM slots to 8 active channels */
		/* Multichannel Frame Delay=1, Number of Channels = 4, LB disabled */
		*pSPMCTL0 = NCH3 | MFD1;
		*pSPMCTL1 = NCH3 | MFD1;
		*pSPMCTL2 = NCH3 | MFD1;

		/* sport1 control register set up as a receiver in MCM */
		/* sport 1 control register SPCTL1 = 0x000C01F0 */
		/* externally generated SCLK1 and RFS1 */
		*pSPCTL1 = SCHEN_A | SDEN_A | SLEN32;

		/* sport0 control register set up as a transmitter in MCM */
		/* sport 0 control register, SPCTL0 = 0x000C01F0 */
		*pSPCTL0 = SCHEN_B | SDEN_B | SCHEN_A | SDEN_A | SPTRAN | SLEN32;

		/* sport2 control register set up as a transmitter in MCM */
		/* sport 2 control register, SPCTL2 = 0x000C01F0 */
		*pSPCTL2 = SCHEN_B | SDEN_B | SCHEN_A | SDEN_A | SPTRAN | SLEN32;

		/* sport1 receive & sport0 transmit multichannel word enable registers */
		/* enable receive channels 0-3 */
		/* enable transmit channels 0-3 */
		*pMT2CS0 = *pMR1CS0 = *pMT0CS0 = 0x0000000F;

	}

	/* sport1 & sport0 receive & transmit multichannel companding enable registers */
	/* no companding for our 8 active timeslots*/
	/* no companding on SPORT1 receive */
	/* no companding on SPORT0 transmit */
	/* no companding on SPORT0 transmit */
	*pMT2CCS0 = *pMR1CCS0 = *pMT0CCS0 = 0;

	/* Enable Frame Sync Edge Detection in TDM Mode for SPORT0 and SPORT 1 */
	*pSPCTLN2 = FSED;
	*pSPCTLN1 = FSED;
	*pSPCTLN0 = FSED;
}

void enable_SPORT012_DMA_channels(MODE_SAMPLE_RATE sampe_rate) {
	if (sampe_rate == TDM_192_KHZ_SAMPLE_RATE
			|| sampe_rate == TDM_192_KHZ_SAMPLE_RATE_OUT12
			|| sampe_rate == TDM_192_KHZ_SAMPLE_RATE_OUT34) {
		TDM_xmit2a_tcb[4] = *pCPSP2A = (((int) TDM_xmit2a_tcb + 7) & 0x7FFFF)
				| (1 << 19);
		TDM_xmit2b_tcb[4] = *pCPSP2B = (((int) TDM_xmit2b_tcb + 7) & 0x7FFFF)
				| (1 << 19);
		TDM_xmit0a_tcb[4] = *pCPSP0A = (((int) TDM_xmit0a_tcb + 7) & 0x7FFFF)
				| (1 << 19);
		TDM_xmit0b_tcb[4] = *pCPSP0B = (((int) TDM_xmit0b_tcb + 7) & 0x7FFFF)
				| (1 << 19);
		TDM_rcv1a_tcb[4] = *pCPSP1A = (((int) TDM_rcv1a_tcb + 7) & 0x7FFFF)
				| (1 << 19);
		// Enable multichannel operation (SPORT mode and DMA in standby and ready)
		*pSPMCTL0 |= MCEA | MCEB;
	}
	*pSPMCTL1 |= MCEA;
}

///////////////////////////////////////////////////////////////////////////////
// Set up all AD1939 registers via SPI
///////////////////////////////////////////////////////////////////////////////
int LockCount = 0;
unsigned int LockTest;

void Init1939viaSPI(MODE_SAMPLE_RATE sampe_rate) {
	int configSize = 0;
	int i, j = 0;
	int iControl = AD1939_CS;

	if (sampe_rate == I2S_192_KHZ_SAMPLE_RATE) {
		configSize = sizeof(ConfigParam1939_192KHZ_I2S);
	} else if (sampe_rate == TDM_192_KHZ_SAMPLE_RATE) {
		configSize = sizeof(ConfigParam1939_192KHZ_TDM);
	}
//	else if (sampe_rate == I2S_192_KHZ_SAMPLE_RATE_OUT34) {
//		configSize = sizeof(ConfigParam1939_192KHZ_I2S_OUT34);
//	}

	//Set up AD1939
	SetupSPI1939(iControl);

	//Write register settings
	for (i = 0; i < configSize; i += 3) {
		if (sampe_rate == I2S_192_KHZ_SAMPLE_RATE) {
			Configure1939Register(ConfigParam1939_192KHZ_I2S[i],
					ConfigParam1939_192KHZ_I2S[i + 1],
					ConfigParam1939_192KHZ_I2S[i + 2], AD1939_CS);
		} else if (sampe_rate == TDM_192_KHZ_SAMPLE_RATE) {
			Configure1939Register(ConfigParam1939_192KHZ_TDM[i],
					ConfigParam1939_192KHZ_TDM[i + 1],
					ConfigParam1939_192KHZ_TDM[i + 2], AD1939_CS);
		}
//		else if (sampe_rate == I2S_192_KHZ_SAMPLE_RATE_OUT34) {
//			Configure1939Register(ConfigParam1939_192KHZ_I2S_OUT34[i],
//					ConfigParam1939_192KHZ_I2S_OUT34[i + 1],
//					ConfigParam1939_192KHZ_I2S_OUT34[i + 2], AD1939_CS);
//		}
//		Configure1939Register(ConfigParam1939[i],
//				ConfigParam1939[i + 1],
//				ConfigParam1939[i + 2], iControl);

		Delay(272);

		//Read back register settings for debugging
		//AD1938_Regs_Read[j++] = Get1939Register(ConfigParam1939[i+1], AD1939_CS);
		//Delay(272);
	}
//	LockTest = Get1939Register(0x1, AD1939_CS);
//	while (!(LockTest & AD1938_PLL_LOCK)) {
//		LockTest = Get1939Register(CLKCTRL1, AD1939_CS);
//		LockCount++;
//	}
//	//Write register settings
//	for (i = configSize - 6; i < configSize; i += 3) {
////		if (sampe_rate == I2S_192_KHZ_SAMPLE_RATE) {
////			Configure1939Register(ConfigParam1939_192KHZ_I2S[i],
////					ConfigParam1939_192KHZ_I2S[i + 1],
////					ConfigParam1939_192KHZ_I2S[i + 2], AD1939_CS);
////		} else if (sampe_rate == I2S_192_KHZ_SAMPLE_RATE_OUT12) {
////			Configure1939Register(ConfigParam1939_192KHZ_I2S_OUT12[i],
////					ConfigParam1939_192KHZ_I2S_OUT12[i + 1],
////					ConfigParam1939_192KHZ_I2S_OUT12[i + 2], AD1939_CS);
////		} else if (sampe_rate == I2S_192_KHZ_SAMPLE_RATE_OUT34) {
////			Configure1939Register(ConfigParam1939_192KHZ_I2S_OUT34[i],
////					ConfigParam1939_192KHZ_I2S_OUT34[i + 1],
////					ConfigParam1939_192KHZ_I2S_OUT34[i + 2], AD1939_CS);
////		}
//		Configure1939Register(ConfigParam1939[i],
//						ConfigParam1939[i + 1],
//						ConfigParam1939[i + 2], AD1939_CS);
//
//		Delay(272);
//
//		//Read back register settings for debugging
//		AD1938_Regs_Read[j++] = Get1939Register(ConfigParam1939[i+1], AD1939_CS);
//		Delay(272);
//	}
	DisableSPI1939();
}

///////////////////////////////////////////////////////////////////////////////
// Set up the SPI port to access the AD1939
// Call with SPI flag to use
///////////////////////////////////////////////////////////////////////////////

void SetupSPI1939(unsigned int SPI_Flag) {

	/*
	 //soft reset ad1393 codec
	 SRU(LOW,DAI_PB02_I);
	 SRU(HIGH,PBEN02_I);
	 SRU(LOW,DAI_PB02_I);

	 Delay(500);
	 SRU(HIGH,DAI_PB02_I);
	 */

	// Configure the SPI Control registers
	// First clear a few registers
	*pSPICTL = (TXFLSH | RXFLSH);
	*pSPIFLG = 0;

	// Setup the baud rate to 1MHz
	//*pSPIBAUD = 100;
	*pSPIBAUD = 25;

	// Setup the SPI Flag register using the Flag specified in the call
	*pSPIFLG = (0xF00 | SPI_Flag);

	// Now setup the SPI Control register
	*pSPICTL =
			(SPIEN | SPIMS | WL8 | MSBF | TIMOD1 | CPHASE | SMLS | CLKPL | GM); //works
}
///////////////////////////////////////////////////////////////////////////////
// Disable the SPI Port
///////////////////////////////////////////////////////////////////////////////

void DisableSPI1939(void) {
	*pSPICTL = (TXFLSH | RXFLSH);
}

///////////////////////////////////////////////////////////////////////////////
// Send a word to the AD1939 via SPI
// Call with the AD1939 address, register address, register data,
// and SPI flag to use
///////////////////////////////////////////////////////////////////////////////

void Configure1939Register(unsigned char rwaddr, unsigned char regaddr,
		unsigned char regdata, unsigned int spiselect) {
	int i, j;
	unsigned char val[3];

	SELECT_SPI_SLAVE(spiselect);

	val[0] = WR(rwaddr);
	val[1] = regaddr;
	val[2] = regdata;

	for (i = 0; i < 3; i++) {
		j = 0;
		*pTXSPI = val[i];
		//Delay(136);		//Wait for the SPI to indicate that it has finished.
		while ((*pSPISTAT & TXS)) {
			j++;
		}
	}

	j = 0;
	//Wait for the SPI to indicate that it has finished.
	while (!(*pSPISTAT & SPIF)) {
		j++;
	}

	Delay(10);
	DESELECT_SPI_SLAVE(spiselect);

}
///////////////////////////////////////////////////////////////////////////////
// Receive a register setting from the AD1939
// Call with the register address, and SPI flag to use; returns register data
///////////////////////////////////////////////////////////////////////////////

unsigned char Get1939Register(unsigned char regaddr, unsigned int spiselect) {
	int i, j;
	unsigned char val[3];
	unsigned int tmp;

	SELECT_SPI_SLAVE(spiselect);

	val[0] = RD(AD1939_ADDR);
	val[1] = regaddr;
	val[2] = 0;

	for (i = 0; i < 3; i++) {
		j = 0;
		*pTXSPI = val[i];

		//Wait for the SPI to indicate that it has finished.
		while ((*pSPISTAT & TXS)) {
			j++;
		}

	}

	j = 0;
	//Wait for the SPI to indicate that it has finished.

	while (!(*pSPISTAT & SPIF)) {
		j++;
	}
	while (!(*pSPISTAT & SPIFE)) {
		j++;
	}

	Delay(10);

	tmp = *pRXSPI;

	DESELECT_SPI_SLAVE(spiselect);

	return tmp;
}

/*******************************************************************
 *   Function:    Init_WDT
 *   Description: Initialize WDT with the appropriate values
 *******************************************************************/

void Init_WDT(void) {
	int n = 0;

	*pWDTUNLOCK = CMD_UNLOCK;

	*pWDTCLKSEL = WDT_CLK_SRC_CER_RESO;

	*pWDTCNT = COUNT_VALUE;

	*pWDTTRIP = TRIP_VALUE;

	// WDT effect latency - 2.5 WDTCLK cycles at 2 MHz
	/* wait at least 4096 cycles for the pll to lock */
	for (n = 0; n < 500; n++) {
		NOP;
	}
	*pWDTCTL = WDT_EN;

	*pWDTUNLOCK = CMD_LOCK;

}



void preventWDT(void) {
	*pWDTUNLOCK = CMD_UNLOCK;
	*pWDTCURCNT = COUNT_VALUE;
	*pWDTUNLOCK = CMD_LOCK;
}

void Init_TWI_TempSensor() {
//	/* setup the interrupt */
//		*pPICR0 = TWI_INTERRUPT;
//		interrupt(SIG_P0, TempSensor_ISR);
//
//		*pTWIMITR = 20 | TWIEN;				/* reference clock = 159.7/16=9.984 MHz */
//		*pTWIDIV = 0x6464;					/* SCL clock divider, high and low */
//		*pTWIMADDR = TEMP_SENSOR_ADDRESS;	/* device address specific to temp sensor */
//		*pTWIFIFOCTL = TWIBHD;				/* read/write happens regardless of FIFO status */
}

/*******************************************************************
 *   Function:    Init_LEDs
 *   Description: This function configures PORTH for LEDs.
 *******************************************************************/
void Init_LEDs(void) {
	/* setting the SRU and route so that flag pins connect to DPI pin buffers */

	/* use flags 4 to 15 only, flags 0 to 3 not available on the DPI */

	SRU(FLAG6_O, DPI_PB06_I);
	/* connect Flag6 output to DPI_PB06 input (LED1) */
	SRU(FLAG7_O, DPI_PB13_I);
	/* connect Flag7 output to DPI_PB13 input (LED2) */
	SRU(FLAG4_O, DPI_PB14_I);
	/* connect Flag4 output to DPI_PB14 input (LED3) */

	SRU(LOW, DAI_PB03_I);
	/* connect Input LOW to LED4 */
	SRU(LOW, DAI_PB04_I);
	/* connect Input LOW to LED5 */
	SRU(LOW, DAI_PB15_I);
	/* connect Input LOW to LED6 */
	SRU(LOW, DAI_PB16_I);
	/* connect Input LOW to LED7 */
	SRU(LOW, DAI_PB17_I);
	/* connect Input LOW to LED8 */

	/* enabling the buffer using the following sequence: high -> output, low -> input */

	SRU(HIGH, DPI_PBEN06_I);
	/* LED1 */
	SRU(HIGH, DPI_PBEN13_I);
	/* LED2 */
	SRU(HIGH, DPI_PBEN14_I);
	/* LED3 */
	SRU(HIGH, PBEN03_I);
	/* LED4 */
	SRU(HIGH, PBEN04_I);
	/* LED5 */
	SRU(HIGH, PBEN15_I);
	/* LED6 */
	SRU(HIGH, PBEN16_I);
	/* LED7 */
	SRU(HIGH, PBEN17_I);
	/* LED8 */

	/* setting flag pins as outputs */
	sysreg_bit_set( sysreg_FLAGS, (FLG3O|FLG4O|FLG5O|FLG6O|FLG7O|FLG8O));

	/* clearing flag pins */
	sysreg_bit_clr( sysreg_FLAGS, (FLG3|FLG4|FLG5|FLG6|FLG7|FLG8));
}

/*******************************************************************
 *   Function:    ClearSet_LED
 *   Description: Clear or set a particular LED (not a group of LEDs).
 *******************************************************************/
void ClearSet_LED(const int led, const int bState) {
	/* if bState is 0 (LED_OFF) we clear the LED,
	 if bState is 1 (LED_ON) we set the LED,
	 else we toggle the LED */

	switch (led) {
	case LED1: {
		if (LED_OFF == bState) {
			sysreg_bit_clr(sysreg_FLAGS, FLG6);
		} else if (LED_ON == bState) {
			sysreg_bit_set(sysreg_FLAGS, FLG6);
		} else /* toggle */{
			sysreg_bit_tgl(sysreg_FLAGS, FLG6);
		}
	}
		break;

	case LED2: {
		if (LED_OFF == bState) {
			sysreg_bit_clr(sysreg_FLAGS, FLG7);
		} else if (LED_ON == bState) {
			sysreg_bit_set(sysreg_FLAGS, FLG7);
		} else /* toggle */{
			sysreg_bit_tgl(sysreg_FLAGS, FLG7);
		}
	}
		break;

	case LED3: {
		if (LED_OFF == bState) {
			sysreg_bit_clr(sysreg_FLAGS, FLG4);
		} else if (LED_ON == bState) {
			sysreg_bit_set(sysreg_FLAGS, FLG4);
		} else /* toggle */{
			sysreg_bit_tgl(sysreg_FLAGS, FLG4);
		}
	}
		break;

	case LED4: {
		if (LED_OFF == bState) {
			SRU(LOW, DAI_PB03_I);
		} else if (LED_ON == bState) {
			SRU(HIGH, DAI_PB03_I);
		} else /* toggle */{
			(*pSRU_PIN0) ^= 0x00004000;
		}
	}
		break;

	case LED5: {
		if (LED_OFF == bState) {
			SRU(LOW, DAI_PB04_I);
		} else if (LED_ON == bState) {
			SRU(HIGH, DAI_PB04_I);
		} else /* toggle */{
			(*pSRU_PIN0) ^= 0x00200000;
		}
	}
		break;

	case LED6: {
		if (LED_OFF == bState) {
			SRU(LOW, DAI_PB15_I);
		} else if (LED_ON == bState) {
			SRU(HIGH, DAI_PB15_I);
		} else /* toggle */{
			(*pSRU_PIN3) ^= 0x00004000;
		}
	}
		break;

	case LED7: {
		if (LED_OFF == bState) {
			SRU(LOW, DAI_PB16_I);
		} else if (LED_ON == bState) {
			SRU(HIGH, DAI_PB16_I);
		} else /* toggle */{
			(*pSRU_PIN3) ^= 0x00200000;
		}
	}
		break;

	case LED8: {
		if (LED_OFF == bState) {
			SRU(LOW, DAI_PB17_I);
		} else if (LED_ON == bState) {
			SRU(HIGH, DAI_PB17_I);
		} else /* toggle */{
			(*pSRU_PIN4) ^= 0x00000001;
		}
	}
		break;
	}
}

/*******************************************************************
 *   Function:    SW8_IRQ1_handler Processing
 *   Description: Called each time SW8 is pressed.
 *******************************************************************/
void SW8_IRQ1_handler(int sig_int, void *pCBParam) {
	static int sw8_ctr = 0;

	sw8_ctr += 1; /* bump counter */
	gb_sw8_pushed = true; /* set the flag */
	gb_sw9_pushed = false; /* set the flag */
	ClearSet_LED(LED5, 0x1);
}

/*******************************************************************
 *   Function:    SW9_IRQ2_handler Scope
 *   Description: Called each time SW9 is pressed.
 *******************************************************************/
void SW9_IRQ2_handler(int sig_int, void *pCBParam) {
	static int sw9_ctr = 0;

	sw9_ctr += 1; /* bump counter */
	gb_sw9_pushed = true; /* set the flag */
	gb_sw8_pushed = false; /* set the flag */
	ClearSet_LED(LED5, 0x0);
}

/*******************************************************************
 *   Function:    SW10_SW11_DAI_handler
 *   Description: Called each time SW10 or SW11 is pressed.
 *******************************************************************/
void SW10_SW11_DAI_handler(int sig_int, void *pCBParam) {
	int iTest; /* flag to indicate which button was pushed */

	/* read the latch register which also clears the latched interrupt */
	iTest = (*pDAI_IRPTL_H);

	/* if we are running tests already this may be the PB test so just return */
//	if ( STATE_SELECTED == g_nPostState )
//	{
//		return;
//	}
	/* update the state machine */
//	if ( (g_nPostState >= STATE_START) && (g_nPostState <= STATE_4) )
//	{
	/* if sw10 */
	if (SRU_EXTMISCA1_INT == iTest) {
		/* pushing a 0 */
		if (MIN_FREQ <= input.Frequency && input.Frequency < MAX_FREQ) {
			input.Frequency += 500;
		}
//			g_nPostState += 1;				/* update the state */
//			g_nSelectedTest <<= 1;			/* shift it up */
//			DEBUG_STATEMENT("0");
	}

	/* else if sw11 */
	else if (SRU_EXTMISCA2_INT == iTest) {
		/* pushing a 1 */
		if (MIN_FREQ < input.Frequency && input.Frequency <= MAX_FREQ) {
			input.Frequency -= 500;
		}
//			g_nPostState += 1;				/* update the state */
//			g_nSelectedTest <<= 1;			/* shift it up */
//			g_nSelectedTest |= 0x1;			/* OR in a 1 */
//			DEBUG_STATEMENT("1");
	}

//		if ( (g_nPostState >= STATE_1) && (g_nPostState <= STATE_4) )
//		{
//			DEBUG_STATEMENT("-");
//		}
//	}

	/* when we get to this state a test has been sucessfully entered */
//	if ( STATE_SELECTED == g_nPostState )
//	{
//		g_bIsTestChosen = true;
//	}
	ClearSet_Freq_LED(input.Frequency);
}

/*******************************************************************
 *   Function:    Init_PushButtons
 *   Description: This function configures PORTH and interrupts
 *					for push buttons.
 *******************************************************************/
void Init_PushButtons(void) {
	/* register the interrupt handlers */
	adi_int_InstallHandler(/*ADI_CID_DAIHI*/ADI_CID_P0I,
			(ADI_INT_HANDLER_PTR) SW10_SW11_DAI_handler, NULL, true);
	adi_int_InstallHandler(ADI_CID_IRQ1I,
			(ADI_INT_HANDLER_PTR) SW8_IRQ1_handler, NULL, true);
	adi_int_InstallHandler(ADI_CID_IRQ2I,
			(ADI_INT_HANDLER_PTR) SW9_IRQ2_handler, NULL, true);
	/* pin assignments in SRU_PIN3 (Group D) */

	SRU(LOW, DAI_PB19_I);
	/* assign pin buffer 19 low so it is an input */
	SRU(LOW, DAI_PB20_I);
	/* assign pin buffer 20 low so it is an input */

	/* route MISCA signals in SRU_EXT_MISCA (Group E) */

	SRU(DAI_PB19_O, MISCA1_I);
	/* route so that DAI pin buffer 19 connects to MISCA1 */
	SRU(DAI_PB20_O, MISCA2_I);
	/* route so that DAI pin buffer 20 connects to MISCA2 */

	/* pin buffer disable in SRU_PINEN0 (Group F) */

	SRU(LOW, PBEN19_I);
	/* assign pin 19 low so it is an input */
	SRU(LOW, PBEN20_I);
	/* assign pin 20 low so it is an input */

	/* unmask individual interrupts */
	(*pDAI_IRPTL_PRI) = (SRU_EXTMISCA1_INT | SRU_EXTMISCA2_INT);

	/* make sure interrupts latch on the rising edge */
	(*pDAI_IRPTL_RE) = (SRU_EXTMISCA1_INT | SRU_EXTMISCA2_INT);

	/* clear MSEN bit for this test */
	(*pSYSCTL) &= ~(MSEN);

	/* setup the IRQ pins to use the pushbuttons */
	(*pSYSCTL) |= (IRQ1EN | IRQ2EN);

	sysreg_bit_set(sysreg_MODE2, (IRQ1E | IRQ2E));
	sysreg_bit_clr(sysreg_IRPTL, (IRQ1I | IRQ2I));

	/* enable IRQ interrupts and make DAI interrupts high priority */
	sysreg_bit_set(sysreg_IMASK, (IRQ1I | IRQ2I | DAIHI));

	sysreg_bit_set(sysreg_MODE1, IRPTEN);
	/* enable global interrupts */
}

/*******************************************************************
 *   Function:    Init_AMI
 *   Description: initializes the AMI interface
 *******************************************************************/
void Init_AMI(void) {
	int sysctl = 0x0;
	int amictl = 0x0;

	sysctl = *pSYSCTL;
	sysctl |= EPDATA32;
	*pSYSCTL = sysctl;

	// Flash is on Bank1
	// Programming maximum wait states
	amictl = (AMIEN | BW8 | WS31);
	*pAMICTL1 = amictl;

	// SRAM is connected on Bank 3
	// SRAM part used - IS61WV102416BLL
	// As per datasheet access time is 10 ns, 8ns
	// Programming waitstates = 2
	amictl = (AMIEN | BW16 | WS2);
	*pAMICTL3 = amictl;
}

// The following definition allows the SRU macro to check for errors. Once the routings have
// been verified, this definition can be removed to save some program memory space.
// The preprocessor will issue a warning stating this when using the SRU macro without this
// definition
#define SRUDEBUG  // Check SRU Routings for errors.
void Init_DAI_I2S() {
	Clear_DAI_Pins();

//-----------------------------------------------------------------------------
//  Connect the AD1939 BCLKs and LRCLKs: The AD1939 drives a ABCLK output to
//  input DAI pin 7, a ALRCLK frame sync to DAI pin 8.
//
//  Internally connect ABCLK/ALRCLK DAI pins 7/8 back out to DBCLK/DLRCLK DAI
//  pins 13 and 14, respectively
//
//  In this example, the ADC clocks are master, DAC clocks are slaves
//
//  ABCLK/ALRCLK are always inputs to the SHARC so tie the pin
//  buffer inputs and pin buffer enable inputs all low (already done prior, see
//  initial SRU macro instructions above).
//-----------------------------------------------------------------------------
	//SRU(DAI_PB07_O, SRC1_CLK_OP_I);
	SRU(DAI_PB07_O, SPORT1_CLK_I);
	// DAIP7 (ABCLK) to SPORT1 CLK (RCLK)
	SRU(DAI_PB07_O, SPORT0_CLK_I);
	// DAIP7 (ABCLK) to SPORT0 CLK (TCLK)
	SRU(DAI_PB07_O, SPORT2_CLK_I);
	// DAIP7 (ABCLK) to SPORT2 CLK (TCLK)
//    SRU(HIGH, PBEN13_I);
//    SRU(DAI_PB07_O, DAI_PB13_I);  // DAIP7 (ABCLK) to DAIP13 (DBCLK)

	//SRU(DAI_PB08_O, SRC1_FS_OP_I);
	SRU(DAI_PB08_O, SPORT1_FS_I);
	// DAIP8 (ALRCLK) to SPORT1 FS (RFS1)
	SRU(DAI_PB08_O, SPORT0_FS_I);
	// DAIP8 (ALRCLK) to SPORT0 FS (TFS0)
	SRU(DAI_PB08_O, SPORT2_FS_I);
	// DAIP8 (ALRCLK) to SPORT2 FS (TFS2)
//	SRU(HIGH, PBEN14_I);
//	SRU(DAI_PB08_O, DAI_PB14_I);     // DAIP8 (ALRCLK) to DAIP14 (DLRCLK)

//-----------------------------------------------------------------------------
//  Connect the AD1939 ADCs: The AD1939 drives I2S rx ADC data to DAI pins 5
//  and 6.  We Connect the I2S ADC stream to SPORT1, using data inputs pri. A
//  and sec. B channels
//
//  These lines are always inputs to the SHARC so tie the pin
//  buffer inputs and pin buffer enable inputs all low. (already done prior,
//  see initial SRU macro instructions above).
//-----------------------------------------------------------------------------
	SRU(DAI_PB05_O, SPORT1_DA_I);
	// DAIP5 (ASDATA1) to SPORT1 DA (RX1A)
	SRU(DAI_PB06_O, SPORT1_DB_I);
	// DAIP6 (ASDATA2) to SPORT1 DB (RX1B)

//-----------------------------------------------------------------------------
//  Connect the AD1939 DACs in I2S mode to SPORT0 and SPORT2:
//  The DAC clock and frame sync inputs are provided by the ADCs
//
//  All eight DAC connections are always outputs from the SHARC
//  so tie the pin buffer enable inputs all high.
//
//  Connect the I2S DAC streams to SPORT0 A/B and SPORT2 A/B
//  via DAI pins 12, 11, 10 and 9
//
//  Connect DAC1 DSDATA1 to SPORT0, using data output A
//  Connect DAC2 DSDATA2 to SPORT0, using data output B
//  Connect DAC3 DSDATA3 to SPORT2, using data output A
//  Connect DAC4 DSDATA4 to SPORT2, using data output B
//-----------------------------------------------------------------------------

	SRU(HIGH, PBEN12_I);
	SRU(SPORT0_DA_O, DAI_PB12_I);
	// DAIP12 (DSDATA1) to SPORT0 DA (TX)
	SRU(HIGH, PBEN11_I);
	SRU(SPORT0_DB_O, DAI_PB11_I);
	// DAIP11 (DSDATA2) to SPORT0 DB (TX)

	SRU(HIGH, PBEN10_I);
	SRU(SPORT2_DA_O, DAI_PB10_I);
	// DAIP10 (DSDATA3) to SPORT2 DA (TX)
	SRU(HIGH, PBEN09_I);
	SRU(SPORT2_DB_O, DAI_PB09_I);
	// DAIP09 (DSDATA4) to SPORT2 DB (TX)

//--------------------------------------------------------------------------
// Route SPI signals to AD1939 Control Port.

	SRU(SPI_MOSI_O, DPI_PB01_I);
	//Connect MOSI to DPI PB1.
	SRU(DPI_PB02_O, SPI_MISO_I);
	//Connect DPI PB2 to MISO.
	SRU(SPI_CLK_O, DPI_PB03_I);
	//Connect SPI CLK to DPI PB3.
	SRU(SPI_FLG0_O, DPI_PB04_I);
	//Connect SPI FLAG0 to DPI PB4.

//---------------------------------------------------------------------------
// Tie pin buffer enable from SPI peripheral to determine whether they are
// inputs or outputs

	SRU(SPI_MOSI_PBEN_O, DPI_PBEN01_I);
	SRU(SPI_MISO_PBEN_O, DPI_PBEN02_I);
	SRU(SPI_CLK_PBEN_O, DPI_PBEN03_I);
	SRU(SPI_FLG0_PBEN_O, DPI_PBEN04_I);

//-----------------------------------------------------------------------------
//  Set the SRU and route so that a Flag pins connects to DPI pin buffers.
//  Use Flags 4 to 15 only. Flags 0 to 3 not available on the DPI.
//	SRU(FLAG6_O,DPI_PB08_I);	// Connect Flag6 output to DPI_PB08 input (LED1)
//	SRU(FLAG7_O,DPI_PB13_I);	// Connect Flag7 output to DPI_PB13 input (LED2)
//	SRU(FLAG4_O,DPI_PB06_I);	// Connect Flag4 output to DPI_PB06 input (LED3)
//	SRU(FLAG5_O,DPI_PB07_I);	// Connect Flag5 output to DPI_PB07 input (LED4)
//	SRU(FLAG8_O,DPI_PB14_I);	// Connect Flag8 output to DPI_PB14 input (LED5)

//	SRU(LOW,DAI_PB15_I);		// Connect Input LOW to LED6
//	SRU(LOW,DAI_PB16_I);		// Connect Input LOW to LED7

//Enabling the Buffer using the following sequence: High -> Output, Low -> Input

//	SRU(HIGH,DPI_PBEN08_I);
//	SRU(HIGH,DPI_PBEN13_I);
//	SRU(HIGH,DPI_PBEN06_I);
//	SRU(HIGH,DPI_PBEN07_I);
//	SRU(HIGH,DPI_PBEN14_I);
//	SRU(HIGH,PBEN15_I);
//	SRU(HIGH,PBEN16_I);

}

///////////////////////////////////////////////////////////////////////////////
// Set up all AD1939 registers via SPI
///////////////////////////////////////////////////////////////////////////////

/*
 * SPORT.c
 *
 *  Created on: Jan 13, 2015
 *      Author: Anol
 */
/******************************************************************************************************
 /                                                                                                     /
 /                            AD1939 - SPORT0 & SPORT1 Initialization Routines                         /
 /                                (C) Copyright 2009 - Analog Devices, Inc.                            /
 /                                                                                                     /
 /  Configures SPORT0 RX, SPORT0 RX and SPORT2 TX control and DMA registers for multichannel operation /
 /                                                                                                     /
 /                                                                                                     /
 / *************************************************************************************************** /
 /                                                                                                     /
 /                                                                                                     /
 /  rx1a_buf[2] - DSP SPORT1 A receive buffer - AD1939 ASDATA1                                         /
 /  Slot # Description                             DSP Data Memory Address                             /
 /  ------ --------------------------------------  --------------------------------------------------  /
 /  0      Internal ADC 0 Left Channel             DM(_rx1a_buf + 0) = DM(_rx1a_buf + Internal_ADC_L1) /
 /  1      Internal ADC 0 Right Channel            DM(_rx1a_buf + 1) = DM(_rx1a_buf + Internal_ADC_R1) /
 /                                                                                                     /
 /  rx1b_buf[2] - DSP SPORT1 B receive buffer - AD1939 ASDATA2                                         /
 /  Slot # Description                             DSP Data Memory Address                             /
 /  ------ --------------------------------------  --------------------------------------------------  /
 /  0      Internal ADC 1 Left Channel             DM(_rx1b_buf + 2) = DM(_rx1b_buf + Internal_ADC_L2) /
 /  1      Internal ADC 1 Right Channel            DM(_rx1b_buf + 3) = DM(_rx1b_buf + Internal_ADC_R2) /
 /                                                                                                     /
 /                                                                                                     /
 /  tx0a_buf[2] - DSP SPORT0 A transmit buffer - AD1939 DSDATA3                                        /
 /  Slot # Description                             DSP Data Memory Address                             /
 /  ------ --------------------------------------  --------------------------------------------------  /
 /  0      Internal DAC 3 Left Channel             DM(_tx0a_buf + 0) = DM(_tx0a_buf + Internal_DAC_L3) /
 /  1      Internal DAC 3 Right Channel            DM(_tx0a_buf + 1) = DM(_tx0a_buf + Internal_DAC_R3) /
 /                                                                                                     /
 ******************************************************************************************************/
void enable_SPORT012_I2S_mode(void) {
	/* Clear out SPORT 0/1/2 registers */
	*pSPCTL0 = *pSPCTL1 = *pSPCTL2 = 0;
	*pSPMCTL0 = *pSPMCTL1 = *pSPMCTL2 = 0;
	*pSPCTLN0 = *pSPCTLN1 = *pSPCTLN2 = 0;

	/* External clock and frame syncs generated by AD1939 */
	*pDIV0 = 0x00000000; // Transmitter (SPORT0)
	*pDIV1 = 0x00000000; // Receiver (SPORT1) at 12.288 MHz SCLK and 48 kHz sample rate
	*pDIV2 = 0x00000000; // Transmitter (SPORT2)

	/* SPORT0 and SPORT1 are being operated in "I2S" mode.
	 This is synonymous with stereo operating mode for the AD1939 */

	I2S_rcv1a_tcb[4] = *pCPSP1A = ((int) (I2S_rcv1a_tcb + 7) & 0x7FFFF)
			| (1 << 19);
	I2S_rcv1b_tcb[4] = *pCPSP1B = ((int) (I2S_rcv1b_tcb + 7) & 0x7FFFF)
			| (1 << 19);
	I2S_xmit0a_tcb[4] = *pCPSP0A = ((int) (I2S_xmit0a_tcb + 7) & 0x7FFFF)
			| (1 << 19);
	I2S_xmit0b_tcb[4] = *pCPSP0B = ((int) (I2S_xmit0b_tcb + 7) & 0x7FFFF)
			| (1 << 19);
	I2S_xmit2a_tcb[4] = *pCPSP2A = ((int) (I2S_xmit2a_tcb + 7) & 0x7FFFF)
			| (1 << 19);
	I2S_xmit2b_tcb[4] = *pCPSP2B = ((int) (I2S_xmit2b_tcb + 7) & 0x7FFFF)
			| (1 << 19);

	/* SPORT1 control register is set up as a transmitter in I2S for DAC3*/
	/* SPORT1  control register SPCTL1 = 0x00000000 */
	/* externally generated SCLK1 and RFS1 */
	/* primary and secondary channels enabled with DMA chaining */
	*pSPCTL1 = (OPMODE | SLEN32 | SPEN_A | SCHEN_A | SDEN_A | SPEN_B | SCHEN_B
			| SDEN_B);

	/* SPORT0 control register set up as a receiver in I2S for ADC1 and ADC2  */
	/* externally generated SCLK0 and RFS0 */
	/* primary and secondary channels enabled with DMA chaining */
	*pSPCTL0 = (SPTRAN | OPMODE | L_FIRST | SLEN32 | SPEN_A | SCHEN_A | SDEN_A
			| SPEN_B | SCHEN_B | SDEN_B);

	/* SPORT2 control register set up as a transmitter in I2S for DAC3 and DAC4 */
	/* externally generated SCLK2 and RFS2 */
	/* primary and secondary channels enabled with DMA chaining */
	*pSPCTL2 = (SPTRAN | OPMODE | L_FIRST | SLEN32 | SPEN_A | SCHEN_A | SDEN_A
			| SPEN_B | SCHEN_B | SDEN_B);
}

#ifdef DEBUG
/* TDM audio frame/ISR counter, for debug purposes */
int audio_frame_timer = 0;
#endif

/*******************************************************************
 *   Function:    Init_SRAM
 *   Description: initializes the SRAM registers
 *******************************************************************/
void Init_SRAM(void) {
	int nValue = 0;

	*pSYSCTL |= MSEN;

}

void Init_SRC(void) {

	//============================================================
	//
	// Configure SRC Control Register (SRCCTL0).
	//
	//    SRC1_IN_I2S : SRC1 Serial Input Format= I2S mode
	//    SRC1_OUT_I2S: SRC1 Serial Output Format= I2S mode
	//    SRC1_OUT_24 : Output Word Length= 24 bits
	//------------------------------------------------------------

	*pSRCCTL0 = SRC1_IN_I2S | SRC1_OUT_I2S | SRC1_OUT_24;

// Enable SRC1 in a different cycle than setting the configuration
	*pSRCCTL0 |= SRC1_ENABLE;
}

/*******************************************************************
 *   Function:    Init_System
 *   Description: Initialize Peripheral
 *******************************************************************/

void Init_System(void) {

	/* Initialize PLL */
	Init_PLL();
	/* SDRAM Initial */
	Init_SDRAM();
	/* SRAM Initial */
	//Init_SRAM();
	/* AMI Initial */
	//Init_AMI();
	/* DAI 4 Analog Channels Input Initial */
	adi_int_InstallHandler(ADI_CID_SFT0I, (ADI_INT_HANDLER_PTR) GetFrameHandler,
				(int *)&g_iTrigger, true);

	sysreg_bit_set(sysreg_IMASK, P3I);
	adi_int_InstallHandler(ADI_CID_SP1I,
			(ADI_INT_HANDLER_PTR) process_AD1939_samples_ISR, &output, true);
#ifdef I2S
	Init_DAI_I2S();
	enable_SPORT012_I2S_mode();
	Init1939viaSPI(I2S_192_KHZ_SAMPLE_RATE);
#else
	Init_TDM_DAI(TDM_192_KHZ_SAMPLE_RATE);
	enable_SPORT012_MCM_mode(TDM_192_KHZ_SAMPLE_RATE);
	enable_SPORT012_DMA_channels(TDM_192_KHZ_SAMPLE_RATE);
	Init1939viaSPI(TDM_192_KHZ_SAMPLE_RATE);
#endif

	//Init_SPORT();

	//Init_SRC();

	/* Watch Dog Initial */
#if 1
	Init_WDT();
#endif
	/* Temperature Sensor Initial */
	//Init_TWI_TempSensor();
	/* UART0 Initialize */
	Init_UART();

	Init_LEDs();
	Init_PushButtons();

	// Unmask SPORT1 RX ISR Interrupt
	//#ifndef CCES
	//	interrupts(ADI_CID_SP1I, process_AD1939_samples_ISR);
	//#else

	//#endif

	//	adi_int_EnableInt(ADI_CID_SP1I, false);
	// Be in infinite loop and do nothing until done.
	//	while( g_iTrigger < AUDIO_REQUIRED_SAMPLES )
	//	{
	//		if( 0 == lTimeout-- )
	//		{
	//			adi_int_EnableInt(ADI_CID_P3I, false);
	//			adi_int_UninstallHandler(ADI_CID_P1I);
	//			return 0; // failed to get enough samples
	//		}
	//		// once the required number of samples has been collected,
	//		// process the signal.
	//	};

	// turn off interrupts so that the data is stable.
	//	adi_int_EnableInt(ADI_CID_SP0I, false);
	//	adi_int_UninstallHandler(ADI_CID_SP0I);

	}
