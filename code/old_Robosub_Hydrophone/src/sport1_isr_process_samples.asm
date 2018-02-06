/******************************************************************************************************
/                                                                                                     /
/                            AD1939 - SPORT0 RX INTERRUPT SERVICE ROUTINE                             /
/                                                                                                     /
/    Receives input data from the AD1939 ADCs via SPORT0 A/B and transmits processed audio data         /
/    back out to the four AD1939 Stereo DACs/Line Outputs through SPORT1 A         /
/                                                                                                     /
/   Date:  20/01/2015                                                                                 /
/   Author : Anol Paisal
/ 	Company : EmOne (Thailand) Co.,Ltd.
/ 	Email : anolpaisal@gmail.com
/   (C) Copyright 2015 - EmOne (Thailand) Co.,Ltd. 
/	Base on Analog Device Inc.                                                        /
*******************************************************************************************************
/                                                                                                     /
/   This Serial Port 1 Recieve Interrupt Service Routine performs arithmetic computations on          /
/   the SPORT0 receive DMA buffer (rx0a_buf) and places results to SPORT1 transmit                    /
/   DMA buffer (tx1a_buf)                                                                             /
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
/  tx0a_buf[2] - DSP SPORT0 A transmit buffer - AD1939 DSDATA3                                        /
/  Slot # Description                             DSP Data Memory Address                             /
/  ------ --------------------------------------  --------------------------------------------------  /
/  0      Internal DAC 3 Left Channel             DM(_tx0a_buf + 0) = DM(_tx0a_buf + Internal_DAC_L3) /
/  1      Internal DAC 3 Right Channel            DM(_tx0a_buf + 1) = DM(_tx0a_buf + Internal_DAC_R3) /
/                                                                                                     /
/                                                                                                     /
******************************************************************************************************/
#include "common.h"
#include <asm_sprt.h>


/*  Uncomment the following macro def to test the DACs only with some generated pure tones... */
/*  Running at 96 KHz vs 48 KHz, you should hear a 1-octave difference in the tones */
/*  Tones are generated a 4K sine wave lookup table (integer divisor of 48K/96K/192K */

#define GENERATE_DAC_PURE_TONES_TEST

.section /dm seg_dmda;

/* AD1939 stereo-channel data holders - used for DSP processing of audio data received from codec */
// input channels
.var 			_Left_Channel_In1;          /* Input values from the AD1939 internal stereo ADCs */			
.var 			_Right_Channel_In1;
.var 			_Left_Channel_In2;						
.var 			_Right_Channel_In2;
//.var 			_Left_Channel_In3;          /* Input values from the AD1939 internal stereo ADCs */			
//.var 			_Right_Channel_In3;
//.var 			_Left_Channel_In4;						
//.var 			_Right_Channel_In4;
//.var 			_Left_Channel_In5;          /* Input values from the AD1939 internal stereo ADCs */			
//.var 			_Right_Channel_In5;
//.var 			_Left_Channel_In6;						
//.var 			_Right_Channel_In6;

//output channels
.var			_Left_Channel_Out1;         /* Output values for the 4 AD1939 internal stereo DACs */
.var 			_Left_Channel_Out2;        
.var 			_Left_Channel_Out3;
.var 			_Left_Channel_Out4;
.var			_Right_Channel_Out1;
.var			_Right_Channel_Out2;
.var			_Right_Channel_Out3;
.var			_Right_Channel_Out4;
//.var			_Left_Channel_Out5;         /* Output values for the 4 AD1939 internal stereo DACs */
//.var 			_Left_Channel_Out6;        
//.var 			_Left_Channel_Out7;
//.var 			_Left_Channel_Out8;
//.var			_Right_Channel_Out5;
//.var			_Right_Channel_Out6;
//.var			_Right_Channel_Out7;
//.var			_Right_Channel_Out8;
//.var			_Left_Channel_Out9;         /* Output values for the 4 AD1939 internal stereo DACs */
//.var 			_Left_Channel_Out10;        
//.var 			_Left_Channel_Out11;
//.var 			_Left_Channel_Out12;
//.var			_Right_Channel_Out9;
//.var			_Right_Channel_Out10;
//.var			_Right_Channel_Out11;
//.var			_Right_Channel_Out12;

//.var			_Left_Channel;              /* Can use these variables as intermediate results to next filtering stage */
//.var            _Right_Channel;

.var			AD1939_audio_frame_timer;

.var 			sine4000[4000] = "sinetbl.dat";
.var			TEMP_L4;
.var			Sine1_B_reg, Sine1_I_reg, Sine1_M_reg, Sine1_L_reg;
.var			Sine2_B_reg, Sine2_I_reg, Sine2_M_reg, Sine2_L_reg;
.var			Sine3_B_reg, Sine3_I_reg, Sine3_M_reg, Sine3_L_reg;
.var			Sine4_B_reg, Sine4_I_reg, Sine4_M_reg, Sine4_L_reg;
//.var			Sine5_B_reg, Sine5_I_reg, Sine5_M_reg, Sine5_L_reg;
//.var			Sine6_B_reg, Sine6_I_reg, Sine6_M_reg, Sine6_L_reg;
//.var			Sine7_B_reg, Sine7_I_reg, Sine7_M_reg, Sine7_L_reg;
//.var			Sine8_B_reg, Sine8_I_reg, Sine8_M_reg, Sine8_L_reg;
//.var			Sine9_B_reg, Sine9_I_reg, Sine9_M_reg, Sine9_L_reg;
//.var			Sine10_B_reg, Sine10_I_reg, Sine10_M_reg, Sine10_L_reg;
//.var			Sine11_B_reg, Sine11_I_reg, Sine11_M_reg, Sine11_L_reg;
//.var			Sine12_B_reg, Sine12_I_reg, Sine12_M_reg, Sine12_L_reg;


.global			_Left_Channel_In1;
.global			_Right_Channel_In1;
.global			_Left_Channel_In2;
.global			_Right_Channel_In2;
//.global			_Left_Channel_In3;
//.global			_Right_Channel_In3;
//.global			_Left_Channel_In4;
//.global			_Right_Channel_In4;
//.global			_Left_Channel_In5;
//.global			_Right_Channel_In5;
//.global			_Left_Channel_In6;
//.global			_Right_Channel_In6;

.global			_Left_Channel_Out1;
.global			_Right_Channel_Out1;
.global			_Left_Channel_Out2;
.global			_Right_Channel_Out2;
.global			_Left_Channel_Out3;
.global			_Right_Channel_Out3;
.global			_Left_Channel_Out4;
.global			_Right_Channel_Out4;
//.global			_Left_Channel_Out5;
//.global			_Right_Channel_Out5;
//.global			_Left_Channel_Out6;
//.global			_Right_Channel_Out6;
//.global			_Left_Channel_Out7;
//.global			_Right_Channel_Out7;
//.global			_Left_Channel_Out8;
//.global			_Right_Channel_Out8;
//.global			_Left_Channel_Out9;
//.global			_Right_Channel_Out9;
//.global			_Left_Channel_Out10;
//.global			_Right_Channel_Out10;
//.global			_Left_Channel_Out11;
//.global			_Right_Channel_Out11;
//.global			_Left_Channel_Out12;
//.global			_Right_Channel_Out12;

// I2S
.extern			_I2S_rx1a_buf;
.extern			_I2S_rx1b_buf;
.extern			_I2S_tx0a_buf;
.extern			_I2S_tx0b_buf;
.extern			_I2S_tx2a_buf;
.extern			_I2S_tx2b_buf;
//TDM
.extern			_TDM_rx1a_buf;
//.extern			_TDM_rx1b_buf;
.extern			_TDM_tx0a_buf;
.extern			_TDM_tx0b_buf;
.extern			_TDM_tx2a_buf;
.extern			_TDM_tx2b_buf;
//.extern			_TDM_4896_rx1a_buf;
//.extern			_TDM_4896_tx0a_buf;

//Sharc audio extender 
//.extern			_ext_rx1a_buf;
//.extern			_ext_rx1b_buf;
//.extern			_ext_tx0a_buf;
//.extern			_ext_tx0b_buf;
//.extern			_ext_rx3a_buf;
//.extern			_ext_tx2a_buf;
//.extern			_ext_tx2b_buf;
//.extern			_ext_rx5a_buf;
//.extern			_ext_tx4a_buf;
//.extern			_ext_tx4b_buf;


.section/pm seg_pmco;
//.section/pm seg_swco;

_SinTableInit:
.global _SinTableInit;

	// use Compiler Scratch Registers for initializing sine wavetables in assembly
	DM(TEMP_L4) = L4;
	
	B4=sine4000;
	I4=sine4000;
	L4 = 4000;
	
	M4 = 40;

	DM(Sine1_B_reg) = B4;
	DM(Sine1_I_reg) = I4;
	DM(Sine1_L_reg) = L4;
	DM(Sine1_M_reg) = M4;
	
	M4 = 50;

	DM(Sine2_B_reg) = B4;
	DM(Sine2_I_reg) = I4;
	DM(Sine2_L_reg) = L4;
	DM(Sine2_M_reg) = M4;
	
	M4 = 60;

	DM(Sine3_B_reg) = B4;
	DM(Sine3_I_reg) = I4;
	DM(Sine3_L_reg) = L4;
	DM(Sine3_M_reg) = M4;

	M4 = 80;

	DM(Sine4_B_reg) = B4;
	DM(Sine4_I_reg) = I4;
	DM(Sine4_L_reg) = L4;
	DM(Sine4_M_reg) = M4;
	
	L4 = DM(TEMP_L4);

	leaf_exit;
_SinTableInit.end:



///////////////////////
// I2S
///////////////////////
_Receive_ADC_Samples_I2S:
.global _Receive_ADC_Samples_I2S;
//void	Receive_ADC_Samples();
	/* get AD1939 left channel input samples, save to data holders for processing */
	r1 = -31;
	r0 = dm(_I2S_rx1a_buf + I2S_Internal_ADC_L1);	f0 = float r0 by r1;	dm(_Left_Channel_In1) = r0;	
	r0 = dm(_I2S_rx1a_buf + I2S_Internal_ADC_R1);	f0 = float r0 by r1;	dm(_Right_Channel_In1) = r0;			

	/* get AD1939 right channel input samples, save to data holders for processing */
	r0 = dm(_I2S_rx1b_buf + I2S_Internal_ADC_L2);	f0 = float r0 by r1;	dm(_Left_Channel_In2) = r0;	
	r0 = dm(_I2S_rx1b_buf + I2S_Internal_ADC_R2);	f0 = float r0 by r1;	dm(_Right_Channel_In2) = r0;			

	r0 = DM(AD1939_audio_frame_timer);
	r0 = r0 + 1;
	DM(AD1939_audio_frame_timer) = r0;
	
	leaf_exit;
_Receive_ADC_Samples_I2S.end:


_Transmit_DAC_Samples_I2S:
.global _Transmit_DAC_Samples_I2S;

	r1 = 31;
	/* output processed left ch audio samples to AD1939 */ 
	r0 = dm(_Left_Channel_Out1);	r0 = trunc f0 by r1;	dm(_I2S_tx0a_buf + I2S_Internal_DAC_L1) = r0;
	r0 = dm(_Left_Channel_Out2);	r0 = trunc f0 by r1;	dm(_I2S_tx0b_buf + I2S_Internal_DAC_L2) = r0;
	r0 = dm(_Left_Channel_Out3);	r0 = trunc f0 by r1;	dm(_I2S_tx2a_buf + I2S_Internal_DAC_L3) = r0;
	r0 = dm(_Left_Channel_Out4);	r0 = trunc f0 by r1;	dm(_I2S_tx2b_buf + I2S_Internal_DAC_L4) = r0;

	/* output processed right ch audio samples to AD1939 */ 
	r0 = dm(_Right_Channel_Out1); 	r0 = trunc f0 by r1;	dm(_I2S_tx0a_buf + I2S_Internal_DAC_R1) = r0;
	r0 = dm(_Right_Channel_Out2);	r0 = trunc f0 by r1;	dm(_I2S_tx0b_buf + I2S_Internal_DAC_R2) = r0;
	r0 = dm(_Right_Channel_Out3);	r0 = trunc f0 by r1;	dm(_I2S_tx2a_buf + I2S_Internal_DAC_R3) = r0;
	r0 = dm(_Right_Channel_Out4);	r0 = trunc f0 by r1;	dm(_I2S_tx2b_buf + I2S_Internal_DAC_R4) = r0;

#ifdef GENERATE_DAC_PURE_TONES_TEST
	//Call make_DAC_Pure_Tones_I2S;
#endif

	leaf_exit;
_Transmit_DAC_Samples_I2S.end:

make_DAC_Pure_Tones_I2S:
	// use Compiler Scratch Registers for generating sine tones in assembly
	DM(TEMP_L4) = L4;
	
	/* generate sine1 tone from lookup table */
	B4 = DM(Sine1_B_reg);
	I4 = DM(Sine1_I_reg);
	L4 = DM(Sine1_L_reg);
	M4 = DM(Sine1_M_reg);
	
	r4 = dm(i4, m4);		
	dm(_I2S_tx0a_buf + I2S_Internal_DAC_L1) = r4;
	dm(_I2S_tx0a_buf + I2S_Internal_DAC_R1) = r4;
	
	DM(Sine1_I_reg) = I4;
	
	/* generate sine2 tone from lookup table */
	B4 = DM(Sine2_B_reg);
	I4 = DM(Sine2_I_reg);
	L4 = DM(Sine2_L_reg);
	M4 = DM(Sine2_M_reg);
	
	r4 = dm(i4, m4);
	dm(_I2S_tx0b_buf + I2S_Internal_DAC_L2) = r4;
	dm(_I2S_tx0b_buf + I2S_Internal_DAC_R2) = r4;
	
	DM(Sine2_I_reg) = I4;
	
	/* generate sine3 tone from lookup table */
	B4 = DM(Sine3_B_reg);
	I4 = DM(Sine3_I_reg);
	L4 = DM(Sine3_L_reg);
	M4 = DM(Sine3_M_reg);
	
	r4 = dm(i4, m4);		
	dm(_I2S_tx2a_buf + I2S_Internal_DAC_L3) = r4;
	dm(_I2S_tx2a_buf + I2S_Internal_DAC_R3) = r4;
	
	DM(Sine3_I_reg) = I4;
	
	/* generate sine4 tone from lookup table */
	B4 = DM(Sine4_B_reg);
	I4 = DM(Sine4_I_reg);
	L4 = DM(Sine4_L_reg);
	M4 = DM(Sine4_M_reg);
	
	r4 = dm(i4, m4);
	dm(_I2S_tx2b_buf + I2S_Internal_DAC_L4) = r4;
	dm(_I2S_tx2b_buf + I2S_Internal_DAC_R4) = r4;
	
	DM(Sine4_I_reg) = I4;
	
	L4 = DM(TEMP_L4);
	
	RTS;

Make_DAC_Pure_Tones_I2S.end:

/////////////
// TDM 192 kHz sample rate
/////////////
_Receive_ADC_Samples_TDM:
.global _Receive_ADC_Samples_TDM;
//void	Receive_ADC_Samples();
	/* get AD1939 left channel input samples, save to data holders for processing */
	r1 = -31;
	r0 = dm(_TDM_rx1a_buf + TDM_Internal_ADC_L1);	f0 = float r0 by r1;	dm(_Left_Channel_In1) = r0;	
	r0 = dm(_TDM_rx1a_buf + TDM_Internal_ADC_L2);	f0 = float r0 by r1;	dm(_Left_Channel_In2) = r0;	
   	

	/* get AD1939 right channel input samples, save to data holders for processing */
	r0 = dm(_TDM_rx1a_buf + TDM_Internal_ADC_R1);	f0 = float r0 by r1;	dm(_Right_Channel_In1) = r0;	
	r0 = dm(_TDM_rx1a_buf + TDM_Internal_ADC_R2);	f0 = float r0 by r1;	dm(_Right_Channel_In2) = r0;			

	r0 = DM(AD1939_audio_frame_timer);
	r0 = r0 + 1;
	DM(AD1939_audio_frame_timer) = r0;
	
	leaf_exit;
_Receive_ADC_Samples_TDM.end:


_Transmit_DAC_Samples_TDM:
.global _Transmit_DAC_Samples_TDM;

	r1 = 31;

	/* output processed left ch audio samples to AD1939 */
	r0 = dm(_Left_Channel_Out1);	r0 = trunc f0 by r1;	dm(_TDM_tx2a_buf + TDM_Internal_DAC_L1) = r0; dm(_TDM_tx0a_buf + TDM_Internal_DAC_L1) = r0;
	r0 = dm(_Left_Channel_Out2);	r0 = trunc f0 by r1;	dm(_TDM_tx2a_buf + TDM_Internal_DAC_L2) = r0; dm(_TDM_tx0a_buf + TDM_Internal_DAC_L2) = r0;
	r0 = dm(_Left_Channel_Out3);	r0 = trunc f0 by r1;	dm(_TDM_tx2b_buf + TDM_192_Internal_DAC_L3) = r0; dm(_TDM_tx0b_buf + TDM_192_Internal_DAC_L3) = r0;
	r0 = dm(_Left_Channel_Out4);	r0 = trunc f0 by r1;	dm(_TDM_tx2b_buf + TDM_192_Internal_DAC_L4) = r0; dm(_TDM_tx0b_buf + TDM_192_Internal_DAC_L4) = r0;

	/* output processed right ch audio samples to AD1939 */
	r0 = dm(_Right_Channel_Out1); 	r0 = trunc f0 by r1;	dm(_TDM_tx2a_buf + TDM_Internal_DAC_R1) = r0; dm(_TDM_tx0a_buf + TDM_Internal_DAC_R1) = r0;
	r0 = dm(_Right_Channel_Out2);	r0 = trunc f0 by r1;	dm(_TDM_tx2a_buf + TDM_Internal_DAC_R2) = r0; dm(_TDM_tx0a_buf + TDM_Internal_DAC_R2) = r0;
	r0 = dm(_Right_Channel_Out3);	r0 = trunc f0 by r1;	dm(_TDM_tx2b_buf + TDM_192_Internal_DAC_R3) = r0; dm(_TDM_tx0b_buf + TDM_192_Internal_DAC_R3) = r0;
	r0 = dm(_Right_Channel_Out4);	r0 = trunc f0 by r1;	dm(_TDM_tx2b_buf + TDM_192_Internal_DAC_R4) = r0; dm(_TDM_tx0b_buf + TDM_192_Internal_DAC_R4) = r0;

#ifdef GENERATE_DAC_PURE_TONES_TEST
	Call make_DAC_Pure_Tones_TDM;
#endif

	leaf_exit;
_Transmit_DAC_Samples_TDM.end:



make_DAC_Pure_Tones_TDM:
	// use Compiler Scratch Registers for generating sine tones in assembly
	DM(TEMP_L4) = L4;
	
	/* generate sine1 tone from lookup table */
	B4 = DM(Sine1_B_reg);
	I4 = DM(Sine1_I_reg);
	L4 = DM(Sine1_L_reg);
	M4 = DM(Sine1_M_reg);
		
	r4 = dm(i4, m4);
	dm(_TDM_tx0a_buf + TDM_Internal_DAC_L1) = r4;
	dm(_TDM_tx0a_buf + TDM_Internal_DAC_R1) = r4;
	
	DM(Sine1_I_reg) = I4;
	
	/* generate sine2 tone from lookup table */
	B4 = DM(Sine2_B_reg);
	I4 = DM(Sine2_I_reg);
	L4 = DM(Sine2_L_reg);
	M4 = DM(Sine2_M_reg);
	
	r4 = dm(i4, m4);
	dm(_TDM_tx0a_buf + TDM_Internal_DAC_L2) = r4;
	dm(_TDM_tx0a_buf + TDM_Internal_DAC_R2) = r4;
	
	DM(Sine2_I_reg) = I4;
	
	/* generate sine3 tone from lookup table */
	B4 = DM(Sine3_B_reg);
	I4 = DM(Sine3_I_reg);
	L4 = DM(Sine3_L_reg);
	M4 = DM(Sine3_M_reg);
	
	r4 = dm(i4, m4);
	dm(_TDM_tx0b_buf + TDM_192_Internal_DAC_L3) = r4;
	dm(_TDM_tx0b_buf + TDM_192_Internal_DAC_R3) = r4;
	
	DM(Sine3_I_reg) = I4;
	
	/* generate sine4 tone from lookup table */
	B4 = DM(Sine4_B_reg);
	I4 = DM(Sine4_I_reg);
	L4 = DM(Sine4_L_reg);
	M4 = DM(Sine4_M_reg);
	
	r4 = dm(i4, m4);
	dm(_TDM_tx0b_buf + TDM_192_Internal_DAC_L4) = r4;
	dm(_TDM_tx0b_buf + TDM_192_Internal_DAC_R4) = r4;
	
	DM(Sine4_I_reg) = I4;
	
	L4 = DM(TEMP_L4);
	
	RTS;

Make_DAC_Pure_Tones_TDM.end:

