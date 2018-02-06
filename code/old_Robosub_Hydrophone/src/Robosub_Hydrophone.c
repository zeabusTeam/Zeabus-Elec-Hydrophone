/*****************************************************************************
 * Robosub_Hydrophone.c
 * Author : Anol Paisal
 * Company : EmOne (Thailand) Co.,Ltd.
 * Email : anolpaisal@gmail.com
 * Copyright (C) 2015  EmOne (Thailand) Co.,Ltd.
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * non-profit organization any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * For commercial context will be add fee. Please contact us.
 * EmOne (Thailand) Co.,Ltd.
 * 39/1 Soi.Sangkhom Songkhro 12 Sangkhom Songkhro Rd.
 * Lat Phrao, Bangkok 10230 Thailand
 * Email: info@emone.co.th
 ******************************************************************************/

#include <string.h>
#include <time.h>

#include <filter.h>

#include <complex.h>
#include <stdlib.h>
#include <math.h>
#include "UART.h"

#include "WDT.h"
//#include "ADM1032.h"	//Thermometer Sensor

#include "pushbutton.h"
#include "led.h"

#include "debug.h"
#include "Robosub_Hydrophone.h"
#include "common.h"

#include "ABS_Threshold.h"

/* Managed drivers and/or services include */
#include <adi_initialize.h>

/* Place program arguments in the following string, or delete the definition
 if arguments will be passed from the command line. */
const char __argv_string[] = "-abc -xyz";
/**
 * Place program arguments in the following string.
 */
//extern char __argv_string[] = "prog_name -in x.gif -out y.jpeg";
clock_t start_t, end_t, start_p_t, end_p_t;

volatile pm int g_iTrigger = NON_TRIGGER;
volatile pm uint32_t g_iSampleIndex = 0;
const pm int32_t endCircle = (uint32_t) AUDIO_REQUIRED_SAMPLES - 1;
volatile pm bool g_bRetreive = false;
int test_gain = 4000000;
//char terminate = '|';
bool scope_mode = false; //false = Oscilloscope, true = Bearing Estimation
pm int THRES_FRONT = 3; //Div by 10 {0.1 ~0.9}
pm int THRES_PWR = 2; //Div by 100 {0.01 ~0.09}
//long lTimeout = (AUDIO_REQUIRED_SAMPLES * 4000);
//struct EstimateBearing output;
float pwr[4] = { 0 };

/*******************************************************************
 *  global variables
 *******************************************************************/

#define FFT_SIZE 1024
float data_output[FFT_SIZE] ;

//extern bool g_bIsTestChosen;
//extern int g_nSelectedTest;
//extern volatile int g_nPostState;
#if defined(__DEBUG_FILE__)
extern FILE *pDebugFile; /* debug file */
#endif

section("seg_ext_data") float dm g_fSineWaveIn1_Right[AUDIO_REQUIRED_SAMPLES] =
		{ 0 };
section("seg_ext_data") float dm g_fSineWaveIn1_Left[AUDIO_REQUIRED_SAMPLES] = {
		0 };
section("seg_ext_data") float dm g_fSineWaveIn2_Right[AUDIO_REQUIRED_SAMPLES] =
		{ 0 };
section("seg_ext_data") float dm g_fSineWaveIn2_Left[AUDIO_REQUIRED_SAMPLES] = {
		0 };

extern float dm In1_buf[AUDIO_MAX_SAMPLES];
extern float dm In2_buf[AUDIO_MAX_SAMPLES];
extern float dm In3_buf[AUDIO_MAX_SAMPLES];
extern float dm In4_buf[AUDIO_MAX_SAMPLES];

extern bool pm gb_sw8_pushed;
extern bool pm gb_sw9_pushed;

///* contains the data we send out to S(D)RAM */
//section("seg_dmda") unsigned int out_buf[sizeof(unsigned int) * 800];
///* stores the data we receive from S(D)RAM */
//section("seg_dmda") unsigned int in_buf[sizeof(unsigned int) * 800];
///* stores a backup of the S(D)RAM data we'll overwrite */
//section("seg_dmda") unsigned int backup_buf[sizeof(unsigned int) * 800];

volatile bool g_ReadyProcess = false;
pm OutputResult output;
pm InputParam input;

void PrintOutput(OutputResult pm* output) {
	unsigned long tmp;
	//Header 0 ~ 1
	ClearSet_LED(LED3, LED_TOGGLE);
	UART_DEBUG_BUFFER[0] = 0xFF;
	UART_DEBUG_BUFFER[1] = 0xFF;

	//Sequence number 2 ~ 3
	UART_DEBUG_BUFFER[2] = (char) output->seq_num;
	UART_DEBUG_BUFFER[3] = (char) output->seq_num >> 8;

	//Azimuth 4 ~ 7
	memcpy((unsigned char*) &tmp, (unsigned char*) &output->azimuth,
			sizeof(unsigned long));
	UART_DEBUG_BUFFER[4] = (char) tmp;
	UART_DEBUG_BUFFER[5] = (char) tmp >> 8;
	UART_DEBUG_BUFFER[6] = (char) tmp >> 16;
	UART_DEBUG_BUFFER[7] = (char) tmp >> 24;

	//Elevator 8 ~ 11
	memcpy((unsigned char*) &tmp, (unsigned char*) &output->elavator,
			sizeof(unsigned long));
	UART_DEBUG_BUFFER[8] = (char) tmp >> 0;
	UART_DEBUG_BUFFER[9] = (char) tmp >> 8;
	UART_DEBUG_BUFFER[10] = (char) tmp >> 16;
	UART_DEBUG_BUFFER[11] = (char) tmp >> 24;

	//Interval time 12 ~ 13
	UART_DEBUG_BUFFER[12] = (char) output->interval_time;
	UART_DEBUG_BUFFER[13] = (char) output->interval_time >> 8;

	//Process time 14 ~ 15
	UART_DEBUG_BUFFER[14] = (char) output->process_time;
	UART_DEBUG_BUFFER[15] = (char) output->process_time >> 8;

	//Pulse detected power 16 ~ 31
	memcpy((unsigned char*) &tmp, (unsigned char*) &output->power[0],
			sizeof(unsigned long));
	UART_DEBUG_BUFFER[16] = (char) tmp;
	UART_DEBUG_BUFFER[17] = (char) tmp >> 8;
	UART_DEBUG_BUFFER[18] = (char) tmp >> 16;
	UART_DEBUG_BUFFER[19] = (char) tmp >> 24;

	memcpy((unsigned char*) &tmp, (unsigned char*) &output->power[1],
			sizeof(unsigned long));
	UART_DEBUG_BUFFER[20] = (char) tmp;
	UART_DEBUG_BUFFER[21] = (char) tmp >> 8;
	UART_DEBUG_BUFFER[22] = (char) tmp >> 16;
	UART_DEBUG_BUFFER[23] = (char) tmp >> 24;

	memcpy((unsigned char*) &tmp, (unsigned char*) &output->power[2],
			sizeof(unsigned long));
	UART_DEBUG_BUFFER[24] = (char) tmp;
	UART_DEBUG_BUFFER[25] = (char) tmp >> 8;
	UART_DEBUG_BUFFER[26] = (char) tmp >> 16;
	UART_DEBUG_BUFFER[27] = (char) tmp >> 24;

	memcpy((unsigned char*) &tmp, (unsigned char*) &output->power[3],
			sizeof(unsigned long));
	UART_DEBUG_BUFFER[28] = (char) tmp;
	UART_DEBUG_BUFFER[29] = (char) tmp >> 8;
	UART_DEBUG_BUFFER[30] = (char) tmp >> 16;
	UART_DEBUG_BUFFER[31] = (char) tmp >> 24;

#if 1
	//Status
	UART_DEBUG_BUFFER[32] = (char) output->status;

	//Reserved 33~36
	memcpy((unsigned char*) &tmp, (unsigned char*) &output->input->Frequency,
			sizeof(unsigned long));
	UART_DEBUG_BUFFER[33] = (char) tmp;
	UART_DEBUG_BUFFER[34] = (char) tmp >> 8;
	UART_DEBUG_BUFFER[35] = (char) tmp >> 16;
	UART_DEBUG_BUFFER[36] = (char) tmp >> 24;

	memcpy((unsigned char*) &tmp,
			(unsigned char*) &output->input->FrontThreshold,
			sizeof(unsigned long));
	UART_DEBUG_BUFFER[37] = (char) tmp;
	UART_DEBUG_BUFFER[38] = (char) tmp >> 8;
	UART_DEBUG_BUFFER[39] = (char) tmp >> 16;
	UART_DEBUG_BUFFER[40] = (char) tmp >> 24;

	memcpy((unsigned char*) &tmp,
			(unsigned char*) &output->input->PowerThreshold,
			sizeof(unsigned long));
	UART_DEBUG_BUFFER[41] = (char) tmp;
	UART_DEBUG_BUFFER[42] = (char) tmp >> 8;
	UART_DEBUG_BUFFER[43] = (char) tmp >> 16;
	UART_DEBUG_BUFFER[44] = (char) tmp >> 24;

	memcpy((unsigned char*) &tmp, (unsigned char*) &output->phase[0],
			sizeof(unsigned long));
	UART_DEBUG_BUFFER[45] = (char) tmp;
	UART_DEBUG_BUFFER[46] = (char) tmp >> 8;
	UART_DEBUG_BUFFER[47] = (char) tmp >> 16;
	UART_DEBUG_BUFFER[48] = (char) tmp >> 24;

	memcpy((unsigned char*) &tmp, (unsigned char*) &output->phase[1],
			sizeof(unsigned long));
	UART_DEBUG_BUFFER[49] = (char) tmp;
	UART_DEBUG_BUFFER[50] = (char) tmp >> 8;
	UART_DEBUG_BUFFER[51] = (char) tmp >> 16;
	UART_DEBUG_BUFFER[52] = (char) tmp >> 24;

	memcpy((unsigned char*) &tmp, (unsigned char*) &output->phase[2],
			sizeof(unsigned long));
	UART_DEBUG_BUFFER[53] = (char) tmp;
	UART_DEBUG_BUFFER[54] = (char) tmp >> 8;
	UART_DEBUG_BUFFER[55] = (char) tmp >> 16;
	UART_DEBUG_BUFFER[56] = (char) tmp >> 24;

	memcpy((unsigned char*) &tmp, (unsigned char*) &output->phase[3],
			sizeof(unsigned long));
	UART_DEBUG_BUFFER[57] = (char) tmp;
	UART_DEBUG_BUFFER[58] = (char) tmp >> 8;
	UART_DEBUG_BUFFER[59] = (char) tmp >> 16;
	UART_DEBUG_BUFFER[60] = (char) tmp >> 24;
	//c0r
	memcpy((unsigned char*) &tmp, (unsigned char*) &output->c0r,
				sizeof(unsigned long));
	UART_DEBUG_BUFFER[61] = (char) tmp;
	UART_DEBUG_BUFFER[62] = (char) tmp >> 8;
	UART_DEBUG_BUFFER[63] = (char) tmp >> 16;
	UART_DEBUG_BUFFER[64] = (char) tmp >> 24;
	//c0i
		memcpy((unsigned char*) &tmp, (unsigned char*) &output->c0i,
					sizeof(unsigned long));
		UART_DEBUG_BUFFER[65] = (char) tmp;
		UART_DEBUG_BUFFER[66] = (char) tmp >> 8;
		UART_DEBUG_BUFFER[67] = (char) tmp >> 16;
		UART_DEBUG_BUFFER[68] = (char) tmp >> 24;
	//c1r
		memcpy((unsigned char*) &tmp, (unsigned char*) &output->c1r,
					sizeof(unsigned long));
		UART_DEBUG_BUFFER[69] = (char) tmp;
		UART_DEBUG_BUFFER[70] = (char) tmp >> 8;
		UART_DEBUG_BUFFER[71] = (char) tmp >> 16;
		UART_DEBUG_BUFFER[72] = (char) tmp >> 24;
	//c1i
		memcpy((unsigned char*) &tmp, (unsigned char*) &output->c1i,
					sizeof(unsigned long));
		UART_DEBUG_BUFFER[73] = (char) tmp;
		UART_DEBUG_BUFFER[74] = (char) tmp >> 8;
		UART_DEBUG_BUFFER[75] = (char) tmp >> 16;
		UART_DEBUG_BUFFER[76] = (char) tmp >> 24;
	//c2r
		memcpy((unsigned char*) &tmp, (unsigned char*) &output->c2r,
					sizeof(unsigned long));
		UART_DEBUG_BUFFER[77] = (char) tmp;
		UART_DEBUG_BUFFER[78] = (char) tmp >> 8;
		UART_DEBUG_BUFFER[79] = (char) tmp >> 16;
		UART_DEBUG_BUFFER[80] = (char) tmp >> 24;
	//c2i
		memcpy((unsigned char*) &tmp, (unsigned char*) &output->c2i,
					sizeof(unsigned long));
		UART_DEBUG_BUFFER[81] = (char) tmp;
		UART_DEBUG_BUFFER[82] = (char) tmp >> 8;
		UART_DEBUG_BUFFER[83] = (char) tmp >> 16;
		UART_DEBUG_BUFFER[84] = (char) tmp >> 24;
	//c3r
		memcpy((unsigned char*) &tmp, (unsigned char*) &output->c3r,
					sizeof(unsigned long));
		UART_DEBUG_BUFFER[85] = (char) tmp;
		UART_DEBUG_BUFFER[86] = (char) tmp >> 8;
		UART_DEBUG_BUFFER[87] = (char) tmp >> 16;
		UART_DEBUG_BUFFER[88] = (char) tmp >> 24;
	//c3i
		memcpy((unsigned char*) &tmp, (unsigned char*) &output->c3i,
					sizeof(unsigned long));
		UART_DEBUG_BUFFER[89] = (char) tmp;
		UART_DEBUG_BUFFER[90] = (char) tmp >> 8;
		UART_DEBUG_BUFFER[91] = (char) tmp >> 16;
		UART_DEBUG_BUFFER[92] = (char) tmp >> 24;

	//reserved
	UART_DEBUG_BUFFER[93] = 0;

	//Check sum
	output->chksum = checksum((byte*) &UART_DEBUG_BUFFER, 94);

	UART_DEBUG_BUFFER[94] = (char) output->chksum;
	UART_DEBUG_BUFFER[95] = (char) output->chksum >> 8;
	UART_PRINT(96);

#else
	output.chksum = checksum((byte *) &UART_DEBUG_BUFFER, 12);
	UART_DEBUG_BUFFER[12] = (char) output.chksum;
	UART_DEBUG_BUFFER[13] = (char) output.chksum >> 8;
	UART_PRINT(14);
#endif
	ClearSet_LED(LED3, LED_TOGGLE);
}
float freq_select(float * in)
{
	// 192/1024 = 0.1875
	int i, j, num = 0;
	float freq = 0;
	complex_float data[FFT_SIZE] ;
	complex_float data_temp[FFT_SIZE];
	//float data_output[FFT_SIZE] ;
	int body = 800;

	for(int k = 0 ; k < FFT_SIZE  ; k++ )
	{
		if(k<body)
		{
			data[k].re = in[k+1200];
			data[k].im = 0.0;
		}
		else
		{
			data[k].re = 0.0;
			data[k].im = 0.0;
		}
	}


	cfft1024(data, data_temp) ;
	cfft_mag(data_temp, data_output, FFT_SIZE) ;

	float mag = data_output[120] ;
	int countnum = 0;

	for(j = 120 ; j < 240 ; j++)
	{
		if(mag < data_output[j])
		{
			mag = data_output[j] ;
			countnum = j ;
			//printf("countnum_run = %d\n", countnum);
		}
	}

	freq = countnum*0.1875 ;
	//printf("frequency(Not Round) = %fk\n", countnum*0.1875);

	float dec;
	float dot = modff(freq, &dec);

	if(dot < 0.5)
	{
		freq = dec;
	}
	else if(dot >= 0.5)
	{
		freq = dec+1;
	}
	printf("freq : %.0f\n",freq);
	return (freq);
}
int main(int argc, char *argv[]) {
	uint32_t index = 0;
	uint32_t iSeqNum = 0;
	int32_t gainLVL = 0;
	complex_float cout[4];
	int iii=0;
	float freq_s = 0 ;
	//int freq_28 = 0;
	//int freq_34 = 0;
	float freq_v = 0;
	float Measure_Frequency = 0 ;
	bool init_freq = true ;
	//Default parameter

	input.Frequency = 28000;
	input.SoundSpeed = 1500;
	input.FrontThreshold = 0.3;
	input.PowerThreshold = 0.02;
	input.DelayObserve = 2000000;

	output.input = &input;
//	unsigned int seq_num = 0;
//	unsigned int interval_time = 0;
//	unsigned char status = 0;
//	unsigned long reserved = 0;
//	unsigned int chksum = 0;

	double total_t, total_p_t;
	/* Initialize managed drivers and/or services */
	start_t = clock();

	adi_initComponents();

	Init_System();

	ClearSet_Freq_LED(input.Frequency);

//	start_t = clock();
    /* Freq selection*/
	/*while (i < 10)
	{
		if (g_ReadyProcess) {
			freq_v = freq_select((float *)In1_buf);
			if(freq_v == 28)
				freq_28++;
			else
				freq_34++;
			printf("frequency %f\n",freq_v);
			i++;
			g_ReadyProcess = false;
		}
		//adi_int_EnableInt(ADI_CID_SP1I, true);

	}
	if(freq_28<freq_34)
		input.Frequency = 34;*/
	/* Process */
	for (;;) {
		/* Receive Signal */
		/* Talk thought Signal Processing API*/
		/* Report Estimation bearing via UART0*/
		if (g_ReadyProcess) {
			/*if(iii<10)
			{
				if(iii == 0)
				{
					freq_s = freq_select((float *)In1_buf)*1000 ;
					iii++ ;
					input.Frequency = freq_s ;
				}
				else
				{
					freq_v = freq_select((float *)In1_buf)*1000 ;
					if(freq_v == freq_s)
					{
						iii++ ;
						input.Frequency = freq_v ;
					}
					else if(freq_v != freq_s)
					{
						iii = 0 ;
						input.Frequency = freq_s ;
					}
				}
			}*/



			//printf("frequency %d \n",input.Frequency);
			//adi_int_EnableInt(ADI_CID_SP1I, false);

			ClearSet_LED(LED7, LED_TOGGLE);
			if (gb_sw8_pushed) { //DEBUG
				output.azimuth = output.elavator = 0;
				Measure_Frequency = freq_select((float *)In1_buf)*1000;
				if (input.Frequency == Measure_Frequency) {
					start_p_t = clock();
					gainLVL = processing(&output.azimuth, &output.elavator, pwr,cout,
							input.Frequency);

					output.c0r = cout[0].re;

					output.c0i = cout[0].im;

					output.c1r = cout[1].re;
					output.c1i = cout[1].im;

					output.c2r = cout[2].re;
					output.c2i = cout[2].im;

					output.c3r = cout[3].re;
					output.c3i = cout[3].im;

					output.power[0] = pwr[0];
					output.power[1] = pwr[1];
					output.power[2] = pwr[2];
					output.power[3] = pwr[3];
					output.power[0] = -2;
					//output.power[1] = Measure_Frequency;

					//output.c_out[1] = cout[1];
					//output.c_out[2] = cout[2];
					//output.c_out[3] = cout[3];

					end_p_t = clock();

					total_p_t = (double) (end_p_t - start_p_t);
					output.process_time = ((uint_fast16_t) (MILLISECOND(total_p_t))
							& TIME_MASK);
					end_t = clock();
					total_t = (double) (end_t - start_t);
					//if (output.azimuth > 100) {
					printf("Check pulse\n");
					//}
					//				if (output.azimuth != 0 && output.elavator != 0) {
					output.interval_time = ((uint_fast16_t) (MILLISECOND(total_t))
							& TIME_MASK);
					start_t = clock();
				//}
	#ifdef DEBUG
					snprintf(UART_DEBUG_BUFFER, sizeof(UART_DEBUG_BUFFER),
							"P=%5.3f,A=%3.3f,E=%3.3f\r", MILLISECOND(total_t), output.azimuth,
							output.elavator);
					UART_DEBUG_PRINT();
	#else
					//}
					//else
					//{
					//	output.power[0] = -1;
					//	output.power[1] = Measure_Frequency;
				}
				else
				{
					output.power[0] = -1;
					output.power[1] =Measure_Frequency;

				}
				//if ((output.azimuth!=-999) && (output.elavator !=-999) ){
					output.seq_num = ++iSeqNum;
					PrintOutput(&output); //Output to rs 232
				//}
#ifdef _DEBUG
				printf("seq = %ul, az = %f, el = %f,c0r = %f, c0i = %f,c1r = %f, c1i = %f,c2r = %f, c2i = %f,c3r = %f, c3i = %f\n", output.seq_num,
					output.azimuth, output.elavator,output.c0r,output.c0i,output.c1r,output.c1i,output.c2r,output.c2i,output.c3r,output.c3i);
#endif
#endif
			//				printf("Detected Channel : 0x%X\n",
			//						(int) (output.status & CH_MASK));


				ClearSet_LED(LED7, LED_TOGGLE);
				Delay(input.DelayObserve);
			//				}
			} else if (gb_sw9_pushed) { //scope
				disable_interrupts();
				if (gb_sw8_pushed) {
					break;
				}
				for (index = 0; index < AUDIO_MAX_SAMPLES; ++index) {
					snprintf((char *) UART_DEBUG_BUFFER,
							sizeof(char) * UART_DEBUG_BUFFER_LINE_SIZE,
							"%f,%f,%f,%f\r", In1_buf[index], In2_buf[index],
							In3_buf[index], In4_buf[index]);
					UART_DEBUG_PRINT();
					ClearSet_LED(LED7, LED_TOGGLE);
					preventWDT();
				}
				enable_interrupts();
			}

			//adi_int_EnableInt(ADI_CID_SP1I, true);
			preventWDT();
			g_iTrigger = NON_TRIGGER;
			g_ReadyProcess = false;
			g_bRetreive = false;
			}

		IDLE;
	};
}

bool CheckTrigger(uint32_t index, struct EstimateBearing* output) {
	float *S1 = g_fSineWaveIn1_Right + index;
	float *S2 = g_fSineWaveIn1_Left + index;
	float *S3 = g_fSineWaveIn2_Right + index;
	float *S4 = g_fSineWaveIn2_Left + index;
	float thers = input.FrontThreshold;
	bool bDetect = false;

	//Pulse amplitude trigger
//	if (g_iTrigger == NON_TRIGGER) {
	bDetect = ABS_Threshold(g_fSineWaveIn1_Right, g_fSineWaveIn1_Left,
			g_fSineWaveIn2_Right, g_fSineWaveIn2_Left, index,thers, &output->status);

	if (bDetect) {
		g_iTrigger = index;
		ClearSet_LED(LED8, LED_ON);
		g_bRetreive = true;
		sysreg_bit_set(sysreg_IMASK, SFT0I);
		sysreg_bit_set(sysreg_MODE1, NESTM);
		raise_interrupt(ADI_CID_SFT0I); //Interrupt to retrieve data
	}
//	}
	return bDetect;
}

void process_AD1939_samples_ISR(uint32_t sig_int, void *pCBParam) {

	/* Perform AD1939 Audio Processing Here Using 32-bit Floating-point Math
	 (Note: The ADC/DAC variables below are used to "double-buffer" the audio
	 samples with temporary variables, allowing active DMA completion of
	 rx0a_buf[] and tx1a_buf[]) */
	//SinTableInit();
	Receive_ADC_Samples_TDM();
	/* Loop back AD1939 ADC1 data to DAC1
	 * for test */
	//
	//	Transmit_DAC_Samples_I2S();
	g_fSineWaveIn1_Right[g_iSampleIndex] = Right_Channel_In1;
	g_fSineWaveIn1_Left[g_iSampleIndex] = Left_Channel_In1;
	g_fSineWaveIn2_Right[g_iSampleIndex] = Right_Channel_In2;
	g_fSineWaveIn2_Left[g_iSampleIndex] = Left_Channel_In2;

	//Pulse amplitude trigger
	if (!g_bRetreive) {
		CheckTrigger(g_iSampleIndex, (OutputResult *) pCBParam);
	}

	g_iSampleIndex++; // only increment the index when both channels have been sent.

	//Circulation buffer
	if (g_iSampleIndex > endCircle) {
		preventWDT();
		ClearSet_LED(LED6, LED_TOGGLE);
		g_iSampleIndex = 0;
	}
}

//TODO : Need to make formula for declaration any size
#define HEAD_SIZE	1200
#define BODY_SIZE	(AUDIO_MAX_SAMPLES - HEAD_SIZE)
#define FRAME_SIZE 	(HEAD_SIZE + BODY_SIZE)

void GetFrameHandler(uint32_t iid, void* callback_data) {
	int countBody = 0;
	int countHEAD = 0;
	int iSOF = 0;
	int iEOF = 0;
	int iRemain = 0;
	int iSize = 0;
	int *iDetectPoint = (int *) callback_data;
	float *S1 = g_fSineWaveIn1_Right;
	float *S2 = g_fSineWaveIn1_Left;
	float *S3 = g_fSineWaveIn2_Right;
	float *S4 = g_fSineWaveIn2_Left;

	//clear_interrupt(ADI_CID_SFT0I);

	if (*iDetectPoint < ((int) HEAD_SIZE - 1)) { //Case 1 :
		iSize = (int) HEAD_SIZE - *iDetectPoint - 1;
		iSOF = (int) AUDIO_REQUIRED_SAMPLES - (iSize);
	} else if (((int) AUDIO_REQUIRED_SAMPLES - *iDetectPoint) < (int) BODY_SIZE) { //Case 2;
		iSize = ((int) HEAD_SIZE
				+ ((int) AUDIO_REQUIRED_SAMPLES - *iDetectPoint));
		iSOF = *iDetectPoint - (int) HEAD_SIZE;
		while(g_iSampleIndex > *iDetectPoint)
			NOP;
	} else { //Case 3;
		iSize = (int) FRAME_SIZE;
		iSOF = *iDetectPoint - (int) HEAD_SIZE;
	}

	iRemain = (int) FRAME_SIZE - iSize;

	//Hold until fill up full frame
	iEOF = iRemain == 0 ? iSOF + (int) FRAME_SIZE : iRemain;
	while (g_iSampleIndex <= iEOF)
		NOP;

	__builtin_memcpyDD((void *) (In1_buf), (void *) (S1 + iSOF), iSize);
	__builtin_memcpyDD((void *) (In2_buf), (void *) (S2 + iSOF), iSize);
	__builtin_memcpyDD((void *) (In3_buf), (void *) (S3 + iSOF), iSize);
	__builtin_memcpyDD((void *) (In4_buf), (void *) (S4 + iSOF), iSize);

	if (iRemain > 0) {
		__builtin_memcpyDD((void *) (In1_buf + iSize), (void *) S1, iRemain);
		__builtin_memcpyDD((void *) (In2_buf + iSize), (void *) S2, iRemain);
		__builtin_memcpyDD((void *) (In3_buf + iSize), (void *) S3, iRemain);
		__builtin_memcpyDD((void *) (In4_buf + iSize), (void *) S4, iRemain);
	}

	//	*iDetectPoint = NON_TRIGGER;
	//	clear_interrupt(ADI_CID_SFT0I);
	ClearSet_LED(LED8, LED_OFF); //cpy data on led

	g_ReadyProcess = true;
}
