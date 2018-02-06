/*****************************************************************************
 * common.h
 * Author : Anol Paisal
 * Company : EmOne (Thailand) Co.,Ltd.
 * Email : anolpaisal@gmail.com
 * Copyright @ 2015
 *****************************************************************************/

#ifndef __COMMON_H__
#define __COMMON_H__

#ifdef __ECC__
/*
 ** The following definition is a good programming practice to follow,
 ** in order to prevent the compiler from optimizing out any instructions
 ** that it may think are non-essential.
 ** It also makes code MISRA rule 2.1 compliant.
 */
#define IDLE asm volatile("idle;")
#define NOP asm volatile("nop;")

#define TIME_MASK 0xFFFF
#define CH_MASK 0xF
#define CHAIN_MASK 0x7FFFF
#define COFFSEL (1 << 19)
/* Add your custom header content here */
#define HEADER 0xFFFF
#define NON_TRIGGER -1
#define FIR_TCB	13

/*******************************************************************
 *  global variables and defines
 *******************************************************************/
#ifdef BW16
#undef BW16
#define BW16	BIT_1
#endif

#if defined(__DEBUG_FILE__)
extern FILE *pDebugFile; /* debug file */
#endif

static unsigned int g_Frequency = 28000;
#define MAX_FREQ 50000
#define MIN_FREQ 25000

#define FLOAT_COFF (2147483648.0)
//----- Type defines ----------------------------------------------------------
typedef unsigned char byte; // Byte is a char
typedef unsigned short int word16; // 16-bit word is a short int
typedef unsigned int word32; // 32-bit word is an int

/*******************************************************************
 *  global variables
 *******************************************************************/
static int g_nNumLEDs = 8;
//bool gb_sw8_pushed = true;
//bool gb_sw9_pushed = false;

//#ifndef NULL
#define NULL	((void *)0)
//#endif

#define WINDOW	100
//#define SCOPE
//#define USE_UART

//#define NUM_POST_TESTS			32

//#define IGNORE_FAILURES			1
//#define DO_NOT_IGNORE_FAILURES	0
#define MILLISECOND(X) ((X) * 1000.0 / __PROCESSOR_SPEED__)
/* test paramaters */
#define MAX_SAMPLES	 				256
#define REQUIRED_SAMPLES			((MAX_SAMPLES) * 250)
#define DESIRED_FREQ 				((float)3000.0)
#define SAMPLE_RATE 				((float)48000.0)
#define AMPLITUDE					((float)12000)
#define PI							((float)3.141592765309)

#define ACCEPTABLE_DEVIATION_PCT	((float)0.015)
#define ACCEPTABLE_DEVIATION		(DESIRED_FREQ * ACCEPTABLE_DEVIATION_PCT)
#define MAX_DESIRED_FREQ			(DESIRED_FREQ + ACCEPTABLE_DEVIATION)
#define MIN_DESIRED_FREQ			(DESIRED_FREQ - ACCEPTABLE_DEVIATION)
#define MIN_SIGNAL_STRENGTH			(float)35.0
#define MAX_NOISE_THRESHOLD			(float)26

/* names for slots in codec audio frame */
#define INTERNAL_ADC_L0			0
#define INTERNAL_ADC_R0			1
#define INTERNAL_ADC_L1			2
#define INTERNAL_ADC_R1			3

#define INTERNAL_DAC_L0			0
#define INTERNAL_DAC_R0			1
#define INTERNAL_DAC_L1			2
#define INTERNAL_DAC_R1			3
#define INTERNAL_DAC_L2			4
#define INTERNAL_DAC_R2			5
#define INTERNAL_DAC_L3			6
#define INTERNAL_DAC_R3			7

// Block Size per Audio Channel
#define NUM_SAMPLES 256

// Number of stereo channels
#define NUM_RX_SLOTS 4
#define NUM_TX_SLOTS 1

#define SPIB_MODE (CPHASE | CLKPL)
#define AD1939_CS DS0EN
//#define AD1939_CS DS1EN

#define SELECT_SPI_SLAVE(select) (*pSPIFLG &= ~(spiselect<<8))
#define DESELECT_SPI_SLAVE(select) (*pSPIFLG |= (spiselect<<8))

#ifdef __ADSP21489__
#define PLL_MULT			PLLM16
#define RDIV				(0x4D8)
#else	/* 21479 */
#define PLL_MULT			PLLM16
#define RDIV				(0x406)
#endif
#include <signal.h>

typedef enum {
	I2S_48_KHZ_SAMPLE_RATE, // All channels are ON
	I2S_48_KHZ_SAMPLE_RATE_OUT12, // channel 1 and 2 are ON, 3 and 4 are OFF
	I2S_48_KHZ_SAMPLE_RATE_OUT34, // channel 1 and 2 are OFF, 3 and 4 are ON
	I2S_96_KHZ_SAMPLE_RATE,
	I2S_96_KHZ_SAMPLE_RATE_OUT12,
	I2S_96_KHZ_SAMPLE_RATE_OUT34,
	I2S_192_KHZ_SAMPLE_RATE,
	I2S_192_KHZ_SAMPLE_RATE_OUT12,
	I2S_192_KHZ_SAMPLE_RATE_OUT34,
	TDM_48_KHZ_SAMPLE_RATE,
	TDM_48_KHZ_SAMPLE_RATE_OUT12,
	TDM_48_KHZ_SAMPLE_RATE_OUT34,
	TDM_96_KHZ_SAMPLE_RATE,
	TDM_96_KHZ_SAMPLE_RATE_OUT12,
	TDM_96_KHZ_SAMPLE_RATE_OUT34,
	TDM_192_KHZ_SAMPLE_RATE,
	TDM_192_KHZ_SAMPLE_RATE_OUT12,
	TDM_192_KHZ_SAMPLE_RATE_OUT34,
	EXTA_TDM_192_KHZ_SAMPLE_RATE_OUT,
	EXTA_TDM_192_KHZ_SAMPLE_RATE_OUT12,
	EXTA_TDM_192_KHZ_SAMPLE_RATE_OUT34,
	EXTB_TDM_192_KHZ_SAMPLE_RATE_OUT,
	EXTB_TDM_192_KHZ_SAMPLE_RATE_OUT12,
	EXTB_TDM_192_KHZ_SAMPLE_RATE_OUT34,
	EXTC_TDM_192_KHZ_SAMPLE_RATE_OUT,
	EXTC_TDM_192_KHZ_SAMPLE_RATE_OUT12,
	EXTC_TDM_192_KHZ_SAMPLE_RATE_OUT34,
	EXTB_CODEC_OFF,
	EXTC_CODEC_OFF
} MODE_SAMPLE_RATE;

typedef enum {
	extender_codecA, extender_codecB, extender_codecC
} EXTENDER_CODEC;

#define AUDIO_MAX_SAMPLES	 			1024*2
#define AUDIO_REQUIRED_SAMPLES				((AUDIO_MAX_SAMPLES) * 100)
#define ACCEPTABLE_DEVIATION_PCT		((float)0.015)


/* input parameter*/
typedef struct ProcessParameter {
	float FrontThreshold;
	float PowerThreshold;
	float h;
	uint32_t Frequency;
	uint32_t DelayObserve;
	uint32_t SoundSpeed;
} InputParam;
/*
 * Output Protocol*/
typedef struct EstimateBearing {
	uint_fast16_t header;	//0xFF 0xFF 2 Bytes
	uint_fast16_t seq_num;	//2 Bytes
	float azimuth;	// 4 bytes
	float elavator;	//	4 bytes
	float c0r;	// 4 bytes
	float c0i;	//	4 bytes
	float c1r;	// 4 bytes
	float c1i;	//	4 bytes
	float c2r;	// 4 bytes
	float c2i;	//	4 bytes
	float c3r;	// 4 bytes
	float c3i;	//	4 bytes
	uint_fast16_t interval_time;	// 2 Bytes
	uint_fast16_t process_time;		// 2 Bytes
	float power[NUM_RX_SLOTS];	//4 Channel 16 bytes
	uint_fast8_t status;	//7~4=reserved, 3=HP4, 2=HP3, 1=HP2, 0=HP1 : 1 Bytes
	InputParam *input;
	uint_fast32_t phase[NUM_RX_SLOTS]; // 4 Bytes
	//complex_float c_out[4];
	uint_fast16_t chksum;	// 2 Bytes
} OutputResult;

///////////////////////////////////////
//I2S definitions
//////////////////////////////////////

// 48 khz sample rate
//#define SAMPLE_RATE_48KHZ 						((float)48000.0)
//#define DESIRED_FREQ1_I2S_48_OUT12 				((float)451.0)
//#define DESIRED_FREQ2_I2S_48_OUT12				((float)561.0)
//#define MAX_SIGNAL_STRENGTH1_I2S_48_OUT12		(float)270.0
//#define MAX_SIGNAL_STRENGTH2_I2S_48_OUT12		(float)850.0
//#define DESIRED_FREQ1_I2S_48_OUT34 				((float)671.0)
//#define DESIRED_FREQ2_I2S_48_OUT34				((float)902.0)
//#define MAX_SIGNAL_STRENGTH1_I2S_48_OUT34		(float)290.0
//#define MAX_SIGNAL_STRENGTH2_I2S_48_OUT34		(float)500.0

// 96 khz sample rate
//#define SAMPLE_RATE_96KHZ 						((float)96000.0)

// 192 kHz sample rate
#define SAMPLE_RATE_192KHZ 						((float)192000.0)
#define DESIRED_FREQ1_I2S_192_OUT12 			((float)1886.0)
#define DESIRED_FREQ2_I2S_192_OUT12 			((float)2346.0)
#define MAX_SIGNAL_STRENGTH1_I2S_192_OUT12		(float)650.0
#define MAX_SIGNAL_STRENGTH2_I2S_192_OUT12		(float)500.0
#define DESIRED_FREQ1_I2S_192_OUT34 			((float)2806.0)
#define DESIRED_FREQ2_I2S_192_OUT34 			((float)3772.0)
#define MAX_SIGNAL_STRENGTH1_I2S_192_OUT34		(float)600.0
#define MAX_SIGNAL_STRENGTH2_I2S_192_OUT34		(float)900.0

//TDM
// 48 khz sample rate
//#define DESIRED_FREQ1_TDM_48_OUT12 				((float)451.0)
//#define DESIRED_FREQ2_TDM_48_OUT12 				((float)561.0)
//#define MAX_SIGNAL_STRENGTH1_TDM_48_OUT12		(float)250.0
//#define MAX_SIGNAL_STRENGTH2_TDM_48_OUT12		(float)561.0
//
//#define DESIRED_FREQ1_TDM_48_OUT34 				((float)671.0)
//#define DESIRED_FREQ2_TDM_48_OUT34 				((float)902.0)
//#define MAX_SIGNAL_STRENGTH1_TDM_48_OUT34		(float)230.0
//#define MAX_SIGNAL_STRENGTH2_TDM_48_OUT34		(float)440.0

// 192 kHz sample rate
//#define DESIRED_FREQ1_TDM_192_OUT12 			((float)1886.0)
//#define DESIRED_FREQ2_TDM_192_OUT12 			((float)2346.0)
//#define MAX_SIGNAL_STRENGTH1_TDM_192_OUT12		(float)600.0
//#define MAX_SIGNAL_STRENGTH2_TDM_192_OUT12		(float)460.0
//
//#define DESIRED_FREQ1_TDM_192_OUT34 			((float)2806.0)
//#define DESIRED_FREQ2_TDM_192_OUT34 			((float)3772.0)
//#define MAX_SIGNAL_STRENGTH1_TDM_192_OUT34		(float)600.0
//#define MAX_SIGNAL_STRENGTH2_TDM_192_OUT34		(float)900.0

//Sharc audio extender board
//
//#define EXTA_DESIRED_FREQ1_TDM_192_OUT12 			((float)46.0)
//#define EXTA_DESIRED_FREQ2_TDM_192_OUT12 			((float)92.0)
//#define EXTA_MAX_SIGNAL_STRENGTH1_TDM_192_OUT12		(float)800.0
//#define EXTA_MAX_SIGNAL_STRENGTH2_TDM_192_OUT12		(float)1200.0
//
//#define EXTA_DESIRED_FREQ1_TDM_192_OUT34 			((float)138.0)
//#define EXTA_DESIRED_FREQ2_TDM_192_OUT34 			((float)184.0)
//#define EXTA_MAX_SIGNAL_STRENGTH1_TDM_192_OUT34		(float)1000.0
//#define EXTA_MAX_SIGNAL_STRENGTH2_TDM_192_OUT34		(float)800.0
//
//#define EXTB_DESIRED_FREQ1_TDM_192_OUT12 			((float)460.0)
//#define EXTB_DESIRED_FREQ2_TDM_192_OUT12 			((float)920.0)
//#define EXTB_MAX_SIGNAL_STRENGTH1_TDM_192_OUT12		(float)600.0
//#define EXTB_MAX_SIGNAL_STRENGTH2_TDM_192_OUT12		(float)300.0
//
//#define EXTB_DESIRED_FREQ1_TDM_192_OUT34 			((float)1426.0)
//#define EXTB_DESIRED_FREQ2_TDM_192_OUT34 			((float)1886.0)
//#define EXTB_MAX_SIGNAL_STRENGTH1_TDM_192_OUT34		(float)900.0
//#define EXTB_MAX_SIGNAL_STRENGTH2_TDM_192_OUT34		(float)800.0
//
//#define EXTC_DESIRED_FREQ1_TDM_192_OUT12 			((float)2346.0)
//#define EXTC_DESIRED_FREQ2_TDM_192_OUT12 			((float)2806.0)
//#define EXTC_MAX_SIGNAL_STRENGTH1_TDM_192_OUT12		(float)500.0
//#define EXTC_MAX_SIGNAL_STRENGTH2_TDM_192_OUT12		(float)600.0
//
//#define EXTC_DESIRED_FREQ1_TDM_192_OUT34 			((float)3312.0)
//#define EXTC_DESIRED_FREQ2_TDM_192_OUT34 			((float)3772.0)
//#define EXTC_MAX_SIGNAL_STRENGTH1_TDM_192_OUT34		(float)200.0
//#define EXTC_MAX_SIGNAL_STRENGTH2_TDM_192_OUT34		(float)900.0
//
//#define EXTB_DESIRED_FREQ1_TDM_192_OUT34_DIFF 			((float)138.0)
//#define EXTB_DESIRED_FREQ2_TDM_192_OUT34_DIFF 			((float)184.0)
//#define EXTB_MAX_SIGNAL_STRENGTH1_TDM_192_OUT34_DIFF	(float)1400.0
//#define EXTB_MAX_SIGNAL_STRENGTH2_TDM_192_OUT34_DIFF	(float)1000.0
//
//#define EXTC_DESIRED_FREQ1_TDM_192_OUT12_DIFF 			((float)460.0)
//#define EXTC_DESIRED_FREQ2_TDM_192_OUT12_DIFF 			((float)920.0)
//#define EXTC_MAX_SIGNAL_STRENGTH1_TDM_192_OUT12_DIFF	(float)1500.0
//#define EXTC_MAX_SIGNAL_STRENGTH2_TDM_192_OUT12_DIFF	(float)400.0

/* global variable definitions */

extern void Delay(int i);
void SinTableInit(void);
void SinTableInit_Ext(void);
extern int Test_Channel(float* pfRealIn, const int iMaxSamples,
		const int iSampleRate, const float fExpFreq, const float fFreqTol,
		const float fExpAmp, const float fAmpTol);
//void Clear_DAI_Pins(void);

void Receive_ADC_Samples_I2S(void);
void Transmit_DAC_Samples_I2S(void);
void Receive_ADC_Samples_TDM(void);
void Transmit_DAC_Samples_TDM(void);
//void Receive_ADC_Samples_TDM_4896KHZ(void);
//void Transmit_DAC_Samples_TDM_4896KHZ(void);
//void Receive_ADC_Samples_TDM_4896KHZ(void);
//void Transmit_DAC_Samples_TDM_4896KHZ(void);
//void Receive_ADC_Samples_Ext_TDM(void);
//void Transmit_DAC_Samples_Ext_TDM(void);

int I2S_rx1a_buf[2]; /* SPORT1 receive buffer A (DMA) */
int I2S_rx1b_buf[2]; /* SPORT1 receive buffer B (DMA) */
int I2S_tx0a_buf[2]; /* SPORT0 transmit buffer A (DMA) */
int I2S_tx0b_buf[2]; /* SPORT0 transmit buffer B (DMA) */
int I2S_tx2a_buf[2]; /* SPORT2 transmit buffer A (DMA) */
int I2S_tx2b_buf[2]; /* SPORT2 transmit buffer B (DMA) */

int TDM_rx1a_buf[4];
int TDM_tx0a_buf[4];
int TDM_tx0b_buf[4];
int TDM_tx2a_buf[4];
int TDM_tx2b_buf[4];

//TDM
extern int TDM_rcv1a_tcb[8]; /* SPORT1 receive tcb */
extern int TDM_xmit0a_tcb[8]; /* SPORT0 transmit A tcb */
extern int TDM_xmit0b_tcb[8]; /* SPORT0 transmit B tcb */
extern int TDM_xmit2a_tcb[8]; /* SPORT2 transmit A tcb */
extern int TDM_xmit2b_tcb[8]; /* SPORT2 transmit B tcb */

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

extern int I2S_rcv1a_tcb[8]; /* SPORT1 receive a tcb */
extern int I2S_rcv1b_tcb[8]; /* SPORT1 receive b tcb */
extern int I2S_xmit0a_tcb[8]; /* SPORT0 transmit a tcb */
extern int I2S_xmit0b_tcb[8]; /* SPORT0 transmit a tcb */
extern int I2S_xmit2a_tcb[8]; /* SPORT2 transmit a tcb */
extern int I2S_xmit2b_tcb[8]; /* SPORT2 transmit a tcb */

extern volatile int pm g_iTrigger;
//extern volatile int pm g_iSampleIndex;

extern float dm g_fSineWaveIn1_Left[];
extern float dm g_fSineWaveIn1_Right[];
extern float dm g_fSineWaveIn2_Left[];
extern float dm g_fSineWaveIn2_Right[];
//extern volatile float g_fSineWaveInB1_Left[AUDIO_MAX_SAMPLES];
//extern volatile float g_fSineWaveInB1_Right[AUDIO_MAX_SAMPLES];
//extern volatile float g_fSineWaveInB2_Left[AUDIO_MAX_SAMPLES];
//extern volatile float g_fSineWaveInB2_Right[AUDIO_MAX_SAMPLES];
//extern volatile float g_fSineWaveInC1_Left[AUDIO_MAX_SAMPLES];
//extern volatile float g_fSineWaveInC1_Right[AUDIO_MAX_SAMPLES];
//extern volatile float g_fSineWaveInC2_Left[AUDIO_MAX_SAMPLES];
//extern volatile float g_fSineWaveInC2_Right[AUDIO_MAX_SAMPLES];

//int ext_tx0a_buf[4];
//int ext_rx1a_buf[4];
//int ext_rx1b_buf[4];
extern float Sine_Table[4000];
extern int Sine_Index;

//extern float * DelayLine;
//extern int Index;

/* input audio channels */
/* input values from the AD1939 internal stereo ADCs */
extern float Left_Channel_In1;
extern float Right_Channel_In1;
extern float Left_Channel_In2;
extern float Right_Channel_In2;
//extern float Left_Channel_In3; /* Input values from the AD1939 internal stereo ADCs */
//extern float Right_Channel_In3;
//extern float Left_Channel_In4;
//extern float Right_Channel_In4;
//extern float Left_Channel_In5; /* Input values from the AD1939 internal stereo ADCs */
//extern float Right_Channel_In5;
//extern float Left_Channel_In6;
//extern float Right_Channel_In6;

/* output audio channels */
/* output values for the 4 AD1939 internal stereo DACs */
extern float Left_Channel_Out1;
extern float Left_Channel_Out2;
extern float Left_Channel_Out3;
extern float Left_Channel_Out4;
extern float Right_Channel_Out1;
extern float Right_Channel_Out2;
extern float Right_Channel_Out3;
extern float Right_Channel_Out4;
//extern float Left_Channel_Out5; /* Output values for the 4 AD1939 internal stereo DACs */
//extern float Left_Channel_Out6;
//extern float Left_Channel_Out7;
//extern float Left_Channel_Out8;
//extern float Right_Channel_Out5;
//extern float Right_Channel_Out6;
//extern float Right_Channel_Out7;
//extern float Right_Channel_Out8;
//extern float Left_Channel_Out9; /* Output values for the 4 AD1939 internal stereo DACs */
//extern float Left_Channel_Out10;
//extern float Left_Channel_Out11;
//extern float Left_Channel_Out12;
//extern float Right_Channel_Out9;
//extern float Right_Channel_Out10;
//extern float Right_Channel_Out11;
//extern float Right_Channel_Out12;

//#define SPIB_MODE (CPHASE | CLKPL)
//#define AD1939_CS DS0EN
/* #define AD1939_CS DS1EN */

//#define SELECT_SPI_SLAVE(select) (*pSPIFLG &= ~(spiselect<<8))
//#define DESELECT_SPI_SLAVE(select) (*pSPIFLG |= (spiselect<<8))
//////////////////////////////////////////////////////
// I2S definitions
//
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
// TDM definitions
//
//////////////////////////////////////////////////////
void Init_System(void);

void process_AD1939_samples_ISR(uint32_t sig_int, void *pCBParam);

void Delay(const int n);

void Block_Fixed_To_Float(int * Fixed_In, float * Float_Out_L,
		float * Float_Out_R);
void Block_Float_To_Fixed(int * Fixed_Out, float * Float_In_L,
		float * Float_In_R);
word16 checksum(byte *addr, word32 count);

#else
/* insert assembly definitions here.... */

#endif
/* AD1939 I2S Timeslot Definitions */
#define     I2S_Internal_ADC_L1    0
#define     I2S_Internal_ADC_R1    1
#define     I2S_Internal_ADC_L2    0
#define     I2S_Internal_ADC_R2    1

#define     I2S_Internal_DAC_L1    0
#define     I2S_Internal_DAC_R1    1
#define     I2S_Internal_DAC_L2    0
#define     I2S_Internal_DAC_R2    1
#define     I2S_Internal_DAC_L3    0
#define     I2S_Internal_DAC_R3    1
#define     I2S_Internal_DAC_L4    0
#define     I2S_Internal_DAC_R4    1
//
///* AD1939 TDM Timeslot Definitions for Dual-Line 192 kHz DAC TDM Mode */
#define     TDM_Internal_ADC_L1    0
#define     TDM_Internal_ADC_R1    1
#define     TDM_Internal_ADC_L2    2
#define     TDM_Internal_ADC_R2    3

#define     TDM_Internal_DAC_L1    0
#define     TDM_Internal_DAC_R1    1
#define     TDM_Internal_DAC_L2    2
#define     TDM_Internal_DAC_R2    3
#define     TDM_192_Internal_DAC_L3    0
#define     TDM_192_Internal_DAC_R3    1
#define     TDM_192_Internal_DAC_L4    2
#define     TDM_192_Internal_DAC_R4    3
//
///* TDM 48-96 kHz DAC mode */
//#define     TDM_4896_Internal_DAC_L3    4
//#define     TDM_4896_Internal_DAC_R3    5
//#define     TDM_4896_Internal_DAC_L4    6
//#define     TDM_4896_Internal_DAC_R4    7

// used by Sharc audio extender test
/* AD1939 TDM Timeslot Definitions for Dual-Line 192 kHz DAC TDM Mode */
#define     Internal_ADC_L1    0
#define     Internal_ADC_R1    1
#define     Internal_ADC_L2    2
#define     Internal_ADC_R2    3

//#define     Internal_ADC_L3    0
//#define     Internal_ADC_R3    1
//#define     Internal_ADC_L4    2
//#define     Internal_ADC_R4    3

//#define     Internal_ADC_L5    0
//#define     Internal_ADC_R5    1
//#define     Internal_ADC_L6    2
//#define     Internal_ADC_R6    3

#define     Internal_DAC_L1    0
#define     Internal_DAC_R1    1
#define     Internal_DAC_L2    2
#define     Internal_DAC_R2    3
#define     Internal_DAC_L3    0
#define     Internal_DAC_R3    1
#define     Internal_DAC_L4    2
#define     Internal_DAC_R4    3

//#define     Internal_DAC_L5    0
//#define     Internal_DAC_R5    1
//#define     Internal_DAC_L6    2
//#define     Internal_DAC_R6    3
//#define     Internal_DAC_L7    0
//#define     Internal_DAC_R7    1
//#define     Internal_DAC_L8    2
//#define     Internal_DAC_R8    3
//
//#define     Internal_DAC_L9    0
//#define     Internal_DAC_R9    1
//#define     Internal_DAC_L10   2
//#define     Internal_DAC_R10   3
//#define     Internal_DAC_L11   0
//#define     Internal_DAC_R11   1
//#define     Internal_DAC_L12   2
//#define     Internal_DAC_R12   3


#endif /* __HYDROPHONE_H__ */
