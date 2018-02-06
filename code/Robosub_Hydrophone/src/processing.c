/*****************************************************************************
 * processing.c
 * Author : Anol Paisal
 * Company : EmOne (Thailand) Co.,Ltd.
 * Email : anolpaisal@gmail.com
 * Copyright @ 2015
 * Maintainer : Tita
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <cmatrix.h>
#include <complex.h>
#include <filter.h>
#include <matrix.h>
#include <stats.h>

#include "param.h"
#include "process.h"
#include "common.h"

#include "hw_accel.h"

//extern bool gb_sw8_pushed;
//extern bool gb_sw9_pushed;
float x_loc[4] = { 0.18666667, -0.18666667, -0.18666667, 0.18666667 };
float y_loc[4] = { 0.18666667, 0.18666667, -0.18666667, -0.18666667 };
//float phase_err[4 * 4] = { 0.0, 2.34572, 3.31735, 2.34572, 2.34572, 0.0,
//		2.34572, 3.31735, 3.31735, 2.34572, 0.0, 2.34572, 2.34572, 3.31735,
//		2.34572, 0.0 };
float lstsqr[3 * 4] = { 0.213153941641, -0.213153941641, -0.213153941641,
		0.213153941641, 0.213153941641, 0.213153941641, -0.213153941641,
		-0.213153941641, 0.25, 0.25, 0.25, 0.25 };

extern pm InputParam input;
extern pm OutputResult output;

#define scale 5
#define size1 AUDIO_MAX_SAMPLES//2000
section("seg_dmda")float dm In1_buf[((int) AUDIO_MAX_SAMPLES)];
section("seg_dmda")float dm In2_buf[((int) AUDIO_MAX_SAMPLES)];
section("seg_dmda")float dm In3_buf[((int) AUDIO_MAX_SAMPLES)];
section("seg_dmda")float dm In4_buf[((int) AUDIO_MAX_SAMPLES)];
//output filter
float dm f_out1[(int) AUDIO_MAX_SAMPLES + WINDOW - 1];
float dm f_out2[(int) AUDIO_MAX_SAMPLES + WINDOW - 1];
float dm f_out3[(int) AUDIO_MAX_SAMPLES + WINDOW - 1];
float dm f_out4[(int) AUDIO_MAX_SAMPLES + WINDOW - 1];
float dm f_temp[(int) AUDIO_MAX_SAMPLES + WINDOW - 1];

//output sampling
#define size2 (AUDIO_MAX_SAMPLES / scale)
float dm s_out1[(int) size2];
float dm s_out2[(int) size2];
float dm s_out3[(int) size2];
float dm s_out4[(int) size2];
//output demod
#define size3 (size2 + 25)
complex_float dm d_out1[(int) size3];
complex_float dm d_out2[(int) size3];
complex_float dm d_out3[(int) size3];
complex_float dm d_out4[(int) size3];
float dm dw1[(int) size3];
float dm dw2[(int) size3];
float dm dw3[(int) size3];
float dm dw4[(int) size3];
float dm dx1[(int) size3];
float dm dx2[(int) size3];
float dm dx3[(int) size3];
float dm dx4[(int) size3];
float dm dy1[(int) size3];
float dm dy2[(int) size3];
float dm dy3[(int) size3];
float dm dy4[(int) size3];
float dm dz1[(int) size3];
float dm dz2[(int) size3];
float dm dz3[(int) size3];
float dm dz4[(int) size3];
//output pulse detection
#define size4 100
complex_float dm pd_out[4 * (int) size4]; // subPulse
////output delay time estimator
int dm time_output[(int) size4];
float dm eout[(int) size4];
////output angle estimator
complex_float pulse_tran[(int) size4 * 4]; //tranpose(subPulse)

////filter
//band pass
#ifdef BP
float filter_bp[100] = { 0.00102485, 0.00922742, 0.0170224, 0.02275171,
		0.02660491, 0.02845974, 0.02844666, 0.02666542, 0.02333023, 0.01866306,
		0.01294282, 0.00645333, -0.00050229, -0.00762952, -0.01464244,
		-0.02127817, -0.02730241, -0.03251485, -0.03675609, -0.0399064,
		-0.04189196, -0.04267854, -0.04227641, -0.04073026, -0.03812272,
		-0.03456182, -0.03018358, -0.02513813, -0.01959202, -0.01371403,
		-0.00767786, -0.00164848, 0.00421427, 0.00976813, 0.01488355,
		0.01945459, 0.02339259, 0.02663538, 0.02913953, 0.03088798, 0.03188109,
		0.03214286, 0.0317112, 0.03064312, 0.02900449, 0.02687469, 0.02433633,
		0.02147963, 0.01839253, 0.01516517, 0.0118806, 0.00861966, 0.00545248,
		0.00244391, -0.00035414, -0.00289666, -0.00515236, -0.00709709,
		-0.00871988, -0.010016, -0.01099234, -0.01166027, -0.01204055,
		-0.01215614, -0.01203689, -0.01171244, -0.01121683, -0.01058165,
		-0.00984073, -0.00902365, -0.00816052, -0.00727595, -0.00639401,
		-0.00553261, -0.00470865, -0.00393279, -0.00321474, -0.00255834,
		-0.00196702, -0.00143903, -0.00097295, -0.00056313, -0.0002051,
		0.00010889, 0.0003846, 0.00063017, 0.00085108, 0.00105453, 0.00124457,
		0.00142651, 0.0016023, 0.00177495, 0.00194411, 0.00211055, 0.00227185,
		0.00242691, 0.00257181, 0.00270429, 0.00281964, 0.00291519 };
#elif LP163
//low pass
float filter_lp[163] = { 0.0005819638815361733, 0.00019879010498615907,
		0.00022767092201437183, 0.00025531297065362334, 0.0002807488034690767,
		0.00030292728623379316, 0.00032068355810150776, 0.0003326983139099703,
		0.0003376460852589169, 0.0003341933695865011, 0.00032091548182295145,
		0.000296364539390445, 0.000259263944358662, 0.00020833024331851343,
		0.00014217611865575787, 0.000059953547475915676,
		-0.000039470701644621466, -0.00015669713367315324,
		-0.0002922990664530668, -0.0004464946086915844, -0.000619304397528378,
		-0.0008103639470064903, -0.0010190058527831626, -0.0012441505215466334,
		-0.0014843683522803351, -0.0017377808029476643, -0.0020021465480106215,
		-0.0022748378647111205, -0.0025527693576020624, -0.0028325328007029393,
		-0.0031102537798806855, -0.003381755263268949, -0.0036424503626797805,
		-0.0038875404279695115, -0.00411189352951525, -0.004310296297175892,
		-0.0044772105191336255, -0.004607233224198584, -0.00469468844377201,
		-0.004734075974129997, -0.004720012262095053, -0.004647233657207179,
		-0.0045108127678204785, -0.004306182522151814, -0.0040291501121243415,
		-0.003675964090637525, -0.003243486229290978, -0.0027291478897309915,
		-0.002131306629547152, -0.0014481165371384246, -0.0006811364656148641,
		0.00017174625451366992, 0.0011072473186550713, 0.002123252706000729,
		0.0032172284812014293, 0.004385081043245875, 0.005621536004483763,
		0.0069206867969490845, 0.008275955199116843, 0.00967993286022986,
		0.011124518170530928, 0.012600984467765383, 0.014099690637281328,
		0.015610374102465277, 0.01712319800721637, 0.01862698495772486,
		0.020111229971570197, 0.02156478705195722, 0.02297668061881249,
		0.024335930556454173, 0.025631855645659486, 0.026854092299222407,
		0.027992783062529045, 0.029038665941885658, 0.029983193774586546,
		0.0308185265267006, 0.03153769063955536, 0.032134669991468245,
		0.03260433072397987, 0.032942730497619886, 0.03314692061051216,
		0.033215192546999395, 0.03314692061051216, 0.032942730497619886,
		0.03260433072397987, 0.032134669991468245, 0.03153769063955536,
		0.0308185265267006, 0.029983193774586546, 0.029038665941885658,
		0.027992783062529045, 0.026854092299222407, 0.025631855645659486,
		0.024335930556454177, 0.02297668061881249, 0.02156478705195722,
		0.020111229971570197, 0.01862698495772486, 0.01712319800721637,
		0.015610374102465277, 0.014099690637281328, 0.012600984467765383,
		0.011124518170530928, 0.00967993286022986, 0.008275955199116843,
		0.0069206867969490845, 0.005621536004483763, 0.004385081043245875,
		0.0032172284812014293, 0.002123252706000729, 0.0011072473186550713,
		0.00017174625451366992, -0.0006811364656148641, -0.0014481165371384246,
		-0.002131306629547152, -0.00272914788973099, -0.003243486229290978,
		-0.003675964090637525, -0.0040291501121243415, -0.004306182522151814,
		-0.0045108127678204785, -0.004647233657207179, -0.004720012262095053,
		-0.004734075974129997, -0.004694688443772011, -0.004607233224198584,
		-0.0044772105191336255, -0.004310296297175892, -0.00411189352951525,
		-0.0038875404279695115, -0.0036424503626797805, -0.003381755263268949,
		-0.0031102537798806855, -0.0028325328007029393, -0.0025527693576020624,
		-0.0022748378647111205, -0.0020021465480106215, -0.0017377808029476643,
		-0.0014843683522803351, -0.0012441505215466334, -0.0010190058527831626,
		-0.0008103639470064903, -0.0006193043975283784, -0.0004464946086915844,
		-0.0002922990664530668, -0.00015669713367315324,
		-0.00003947070164462148, 0.000059953547475915676,
		0.00014217611865575787, 0.0002083302433185148, 0.000259263944358662,
		0.000296364539390445, 0.00032091548182295145, 0.0003341933695865011,
		0.0003376460852589169, 0.0003326983139099703, 0.0003206835581015091,
		0.00030292728623379316, 0.000280748803469076, 0.00025531297065362334,
		0.00022767092201437183, 0.00019879010498615907, 0.0005819638815361733 };
#elif LP20
float filter_lp[20]={
  -0.0008453470597592304,
  -0.002712473014466144,
  -0.005788634958659003,
  -0.009171023634709823,
  -0.010705955411809303,
  -0.007218961126548628,
  0.004526073044614337,
  0.02637759604805089,
  0.05743262361200088,
  0.09345642810292086,
  0.12755817815137688,
  0.15206931577086633,
  0.16099477910402013,
  0.15206931577086633,
  0.12755817815137688,
  0.09345642810292086,
  0.05743262361200088,
  0.026377596048050886,
  0.004526073044614337,
  -0.007218961126548632,
  -0.010705955411809303,
  -0.009171023634709823,
  -0.0057886349586590115,
  -0.0027124730144661396,
  -0.0008453470597592304};
#else
const float filter_lp[25] = { -0.0008453470597592304, -0.002712473014466144,
		-0.005788634958659003, -0.009171023634709823, -0.010705955411809303,
		-0.007218961126548628, 0.004526073044614337, 0.02637759604805089,
		0.05743262361200088, 0.09345642810292086, 0.12755817815137688,
		0.15206931577086633, 0.16099477910402013, 0.15206931577086633,
		0.12755817815137688, 0.09345642810292086, 0.05743262361200088,
		0.026377596048050886, 0.004526073044614337, -0.007218961126548632,
		-0.010705955411809303, -0.009171023634709823, -0.0057886349586590115,
		-0.0027124730144661396, -0.0008453470597592304 };
#endif

// TCB Structure
/*CP[18:0]          ---------------
 CP[18:0] -0x1     ---------------      II ---- should point to x(n-N-1) ---- x(0)
 CP[18:0] -0x2     ----------------     IM
 CP[18:0] -0x3     -----------------    IL/IC
 CP[18:0] -0x4     -----------------    IB  ---- Base address for input circular buffer
 CP[18:0] -0x5     -----------------    OI
 CP[18:0] -0x6     -----------------    OM
 CP[18:0] -0x7     -----------------    OL/OC
 CP[18:0] -0x8     -----------------    OB  ---- Base address for output circular buffer
 CP[18:0] -0x9     -----------------    CI  --- Coefficient Index should point to c(N-1)
 CP[18:0] -0xA     -----------------    CM
 CP[18:0] -0xB     -----------------    CL/CC ---- Coefficient buffer Length
 CP[18:0] -0xC     -----------------    FIRCTL2 */
int fir_right_in1_tcb[13] = {
		(int) fir_left_in1_tcb + 12, // CPFIR	 = Chain pointer register
#ifdef BP
		sizeof(filter_bp), // CCFIR/CL	 = Coefficient buffer length register
		1, // CMFIR	 = Coefficient modifier register
		(int) filter_bp, // CIFIR   	 = Coefficient index register
#else
		sizeof(filter_lp), // CCFIR/CL	 = Coefficient buffer length register
		1, // CMFIR	 = Coefficient modifier register
		(int) filter_lp, // CIFIR   	 = Coefficient index register
#endif
		(int) f_out1, // OBFIR   	 = Output data base register
		sizeof(f_out1), // OCFIR/OL  = Output buffer length register
		1, // OMFIR	 = Output modifier register
		(int) f_out1, // OIFIR 	 = Output data index register
		(int) In1_buf, // IBFIR	 = Input data base register
		sizeof(In1_buf), // IL/ICFIR  = Input buffer length register
		1, // IMFIR		 = Input buffer modifier register
		(int) In1_buf, // IIFIR		 = Input data index register
		(AUDIO_MAX_SAMPLES | WINDOW << 14) // FIRCTL2	 = Channel control register,
		};
int fir_left_in1_tcb[13] = {
		(int) fir_right_in2_tcb + 12, // CP		 = Chain pointer register
#ifdef BP
		sizeof(filter_bp), // CCFIR/CL	 = Coefficient buffer length register
		1, // CMFIR	 = Coefficient modifier register
		(int) filter_bp, // CIFIR   	 = Coefficient index register
#else
		sizeof(filter_lp), // CCFIR/CL	 = Coefficient buffer length register
		1, // CMFIR	 = Coefficient modifier register
		(int) filter_lp, // CIFIR   	 = Coefficient index register
#endif
		(int) f_out2, // OB   	 = Output data base register
		sizeof(f_out2), // OL/OC 	 = Output buffer length register
		1, // OM		 = Output modifier register
		(int) f_out2, // OI 		 = Output data index register
		(int) In2_buf, // IBUF		 = Input data base register
		sizeof(In2_buf), // IL/IC  	 = Input buffer length register
		1, // IM		 = Input buffer modifier register
		(int) In2_buf, // II		 = Input data index register
		(AUDIO_MAX_SAMPLES | WINDOW << 14) // FIRCTL2	 = Channel control register, no of biquads = 3, WINDOW SIZE=512
 };
int fir_right_in2_tcb[13]  = {
		(int) fir_left_in2_tcb + 12, // CP		 = Chain pointer register
#ifdef BP
		sizeof(filter_bp), // CCFIR/CL	 = Coefficient buffer length register
		1, // CMFIR	 = Coefficient modifier register
		(int) filter_bp, // CIFIR   	 = Coefficient index register
#else
		sizeof(filter_lp), // CCFIR/CL	 = Coefficient buffer length register
		1, // CMFIR	 = Coefficient modifier register
		(int) filter_lp, // CIFIR   	 = Coefficient index register
#endif
		(int) f_out3, // OB   	 = Output data base register
		sizeof(f_out3), // OL/OC 	 = Output buffer length register
		1, // OM		 = Output modifier register
		(int) f_out3, // OI 		 = Output data index register
		(int) In3_buf, // IB		 = Input data base register
		sizeof(In3_buf), // IL/IC  	 = Input buffer length register
		1, // IM		 = Input buffer modifier register
		(int) In3_buf, // II		 = Input data index register
		(AUDIO_MAX_SAMPLES | WINDOW << 14) // FIRCTL2	 = Channel control register, no of biquads = 3, WINDOW SIZE=512
 };
int fir_left_in2_tcb[13] = {
		(int) fir_right_in1_tcb + 12, // CP		 = Chain pointer register
#ifdef BP
		sizeof(filter_bp), // CCFIR/CL	 = Coefficient buffer length register
		1, // CMFIR	 = Coefficient modifier register
		(int) filter_bp, // CIFIR   	 = Coefficient index register
#else
		sizeof(filter_lp), // CCFIR/CL	 = Coefficient buffer length register
		1, // CMFIR	 = Coefficient modifier register
		(int) filter_lp, // CIFIR   	 = Coefficient index register
#endif
		(int) f_out4, // OB   	 = Output data base register
		sizeof(f_out4), // OL/OC 	 = Output buffer length register
		1, // OM		 = Output modifier register
		(int) f_out4, // OI 		 = Output data index register
		(int) In4_buf, // IB		 = Input data base register
		sizeof(In4_buf),	 // IL/IC  	 = Input buffer length register
		1, // IM		 = Input buffer modifier register
		(int) In4_buf, // II		 = Input data index register
		(AUDIO_MAX_SAMPLES | WINDOW << 14) // FIRCTL2	 = Channel control register, no of biquads = 3, WINDOW SIZE=512
		};

volatile bool pcount = 0;
volatile int acc_over;

#pragma section("seg_pmco",SW)
void lstsqrx(const float *x, const float *y, float *out) {
	float A[4][3] = { { 2 * PI * x[0], 2 * PI * y[0], 1.0 },
			{ 2 * PI * x[1], 2 * PI * y[1], 1.0 },
			{ 2 * PI * x[2], 2 * PI * y[2], 1.0 },
			{ 2 * PI * x[3], 2 * PI * y[3], 1.0 } };
	float At[3][4];
	float AA[3][3];
	float AA_inv[3][3];
//	mattran((float*) (At), (float*) (A), 4, 3);
	transpmf((float*) (At), (float*) (A), 4, 3);
	matmmltf((float*)(AA), (float*)(At), (float*)(A), 3, 4, 3);
	matinvf((float*) (AA_inv), (float*) (AA), 3);
	matmmltf((out), (float*)(AA_inv), (float*)(At), 3, 3, 4);

	free(A);
	free(AA);
	free(AA_inv);
}

//int pulse_detect2(complex_float*in1, complex_float*in2, complex_float*in3,
//		complex_float*in4, complex_float*out, int N, int Ns, float* pavr) {
//	int output = 0;
//	int i;
//	float power[N];
//	float sum = 0.0;
//	*pavr = 0.0;
//	float min = 100 * pow(10, -10);
//	for (i = 0; i < N; i++) {
//		power[i] = pow(in1[i].re, 2) + pow(in2[i].re, 2) + pow(in3[i].re, 2)
//				+ pow(in4[i].re, 2);
//#ifdef DEBUG
//		printf("%f  %f\n",min*pow(10,10),power[i]*pow(10,10));
//#endif
//		if (power[i] > min) {
//			output = i;
//#ifdef DEBUG
//			printf("detected position %d\n",i);
//#endif
//			break;
//		}
//	}
//
//	if (output != 0) {
//		output += 5;
//		for (i = output; i < output + Ns; i++) {
//			out[i - output] = in1[i];
//			out[Ns + i - output] = in2[i];
//			out[2 * Ns + i - output] = in3[i];
//			out[3 * Ns + i - output] = in4[i];
//		}
//		return (1);
//	} else
//		return (0);
//}

float gain(float* v1, float* v2, float* v3, float* v4, int N) {
	int i;
	float sum = 0;
	float pref = 2.5;
	for (i = 0; i < N; i++)
		sum += pow(v1[i], 2) + pow(v2[i], 2) + pow(v3[i], 2) + pow(v4[i], 2);
	float pavr = sum / N / 4;
#ifdef DEBUG
	printf("%f \n",pavr);
#endif
	float diff = pref - pavr;
	int ratio = (int) (diff / pavr * 10);
	if (ratio > 0)
		return (fmin(1, (float) (ratio) / 10));
	else
		return (fmax(-1, (float) (ratio) / 10));
}
float powerGain(float pavr) {
	float pref = 0.005; //pref for input that voltage is 3 Vpeak(0.005)
	float diff = pref - pavr;
	int ratio = (int) (diff / pavr * 10);
	return (fmax(1, (float) (ratio) / 10));
}

void ACC_DMA_ISR(void) {
	acc_over = 1;
}
void ACC_MAC_ISR(void) {
	acc_over = 1;
}

int processing(float pm* azimuth, float pm* elavator, float * pwr, complex_float *cout,
		const uint32_t signal_freq) {
	//operation parameters
	int i, j, k;

	//antenna info.
	//int num_mic = 4;
	float ant_length = 20; //mm
	float ant_dim[4 * 2] = { 0, 0, ant_length, 0, ant_length, ant_length, 0,
			ant_length };
	float phaseerrors[4][4] ={ 0.0, 2.34572, 3.31735, 2.34572, 2.34572, 0.0,
			2.34572, 3.31735, 3.31735, 2.34572, 0.0, 2.34572, 2.34572, 3.31735,
			2.34572, 0.0 };

	//float x_loc[4], y_loc[4];
	//output
	int chk;
	int time_esti;
	float az, az_t;
	float elv, elv_t;
	int PID_output_gain;
	////////////////////////////////////////////////////////
	////get data 4 channels/////////////////////////////////
	float time = AUDIO_MAX_SAMPLES / SAMPLE_RATE_192KHZ * 1000; //ms

	//hydrophone info.
	struct Hydro_info hy_info;
	hy_info.x = (float*) (x_loc);
	hy_info.y = (float*) (y_loc);
	hy_info.phase_err = (float*) (phaseerrors);
	hy_info.lstsqr = (float*) (lstsqr);

	//set struct for demoduration
	struct Temp dt;
	dt.w1 = (float*) (dw1);
	dt.w2 = (float*) (dw2);
	dt.w3 = (float*) (dw3);
	dt.w4 = (float*) (dw4);
	dt.x1 = (float*) (dx1);
	dt.x2 = (float*) (dx2);
	dt.x3 = (float*) (dx3);
	dt.x4 = (float*) (dx4);
	dt.y1 = (float*) (dy1);
	dt.y2 = (float*) (dy2);
	dt.y3 = (float*) (dy3);
	dt.y4 = (float*) (dy4);
	dt.z1 = (float*) (dz1);
	dt.z2 = (float*) (dz2);
	dt.z3 = (float*) (dz3);
	dt.z4 = (float*) (dz4);


	//    float time = 8; //ms
// 	time = getData((float*)(v1),(float*)(v2),(float*)(v3),(float*)(v4),"AA.csv",(int)size1);
// 	time = time/5;  //time/scale
#ifdef DEBUG
	printf("time %f\n", time);
#endif
	////////////////////////////////////////////////////////
	///set mode/////////////////////////////////////////////
	int mode;
	mode = 1;
	// mode == 1 : This code need to generate hydrophone location and all parameter that involve with it.
	// mode == 0 : In this case, you MUST sure that you have a hydroInfo.h matching with pulse frequency.
	////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////
	////hydrophone arrangement//////////////////////////////
	////////////////////////////////////////////////////////
	////gain////////////////////////////////////////////////
	//float G;
	//G = gain((float*)(v1),(float*)(v2),(float*)(v3),(float*)(v4),(int)size1);
	//printf("Gain for PID : %f\n",G);
	//////////////////////////////////////////////////////////////////////////////////////
	//// Processing //////////////////////////////////////////////////////////////////////
#ifdef DEBUG
	printf("*********Start Processing**********\n");
	// location arrangement
#endif

	if (mode) {
		//compute x y location
		hydrophone_arrangement((float *) (x_loc), (float *) (y_loc),
				(float*) (ant_dim), signal_freq);
		hy_info.x = (float*) (x_loc);
		hy_info.y = (float*) (y_loc);
		//compute phase error
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++) {
				phaseerrors[0][i * 4 + j] = sqrt(
						pow((x_loc[i] - x_loc[j]), 2)
								+ pow((y_loc[i] - y_loc[j]), 2)) * 2 * PI;
				//printf("%f\n",phaseerrors[0][i*4+j]);
			}
		hy_info.phase_err = (float*) (phaseerrors);
		//compute array for least square
		lstsqrx((float *) (x_loc), (float *) (y_loc), (float*) (lstsqr));
		hy_info.lstsqr = (float*) (lstsqr);
		//for (i=0;i<12;i++)
		//printf("%f\n",lstsqr[i]);
	}
	//////////////////////////////////////////////////////////////////////////////////////
	//// Processing //////////////////////////////////////////////////////////////////////
#ifdef DEBUG
	printf("Computation\n");
#endif
#if 0
	//Filter
	filtering(g_fSineWaveIn1_Right, g_fSineWaveIn1_Left,
			g_fSineWaveIn2_Right, g_fSineWaveIn2_Left,
			(float*) (f_out1), (float*) (f_out2), (float*) (f_out3),
			(float*) (f_out4), (float*) (filter_bp), (int) AUDIO_MAX_SAMPLES, WINDOW);

	//Sampling
	sampling((float*) (f_out1), (float*) (f_out2), (float*) (f_out3),
			(float*) (f_out4), (float*) (s_out1), (float*) (s_out2),
			(float*) (s_out3), (float*) (s_out4), scale, (int) size1);
#else
	//Filter
//	filtering(g_fSineWaveIn1_Right, g_fSineWaveIn1_Left,
//			g_fSineWaveIn2_Right, g_fSineWaveIn2_Left,
//			(float*) (f_out1), (float*) (f_out2), (float*) (f_out3),
//			(float*) (f_out4), (float*) (filter_bp), (int) AUDIO_MAX_SAMPLES, WINDOW);
	//no need function
	if(error_cut((float *)In1_buf, (float *)In2_buf, (float *)In3_buf, (float *)In4_buf))
		printf("not header\n");

	power_output((float *)In1_buf, (float *)In2_buf, (float *)In3_buf, (float *)In4_buf, (float*) pwr, (int) size1);


	//Sampling
	sampling((float *)In1_buf, (float *)In2_buf, (float *)In3_buf, (float *)In4_buf,
			(float*) (s_out1), (float*) (s_out2),
			(float*) (s_out3), (float*) (s_out4), scale, (int) size1);

#endif
	////Demod
	demod((float*) (s_out1), (float*) (s_out2), (float*) (s_out3),
			(float*) (s_out4), (complex_float*) (d_out1),
			(complex_float*) (d_out2), (complex_float*) (d_out3),
			(complex_float*) (d_out4), (int) size2, signal_freq,
#ifdef BP
			(float*) (filter_bp), 100, time, dt);
#elif LP163
			(float*) (filter_lp), 163, time, dt);
#elif LP20
			(float*) (filter_lp), 20, time, dt);
#else
			(float*) (filter_lp), 25, time, dt);
#endif
	////Pulse detection
#if 0
	chk = pulse_detect((complex_float*) (d_out1), (complex_float*) (d_out2),
			(complex_float*) (d_out3), (complex_float*) (d_out4)
				,(complex_float*)(pd_out),(int)size3,(int)size4,&pavr);
	chk = pulse_detect2((complex_float*) (d_out1), (complex_float*) (d_out2),
			(complex_float*) (d_out3), (complex_float*) (d_out4),
			(complex_float*) (pd_out), (int) size3, (int) size4, &pavr);
#else
	chk = detect((complex_float*) (d_out1), (complex_float*) (d_out2),
			(complex_float*) (d_out3), (complex_float*) (d_out4),
			(complex_float*) (pd_out), (int) size3, (int) size4,
			&PID_output_gain);
#endif

#ifdef DEBUG
	printf("power average %f (k) \n", PID_output_gain * 1000000);
#endif
	if (chk) { ////time delay detection
		time_esti = delay_time_estimator((int*) (time_output),
				(complex_float*) (pd_out), (complex_float*) (pulse_tran),
				(float*) (eout), (int) size4);

		////bearing estimation
		bearingEstimator(&az, &elv, &az_t, &elv_t, (complex_float*) (pd_out),
				(int) size4, (complex_float*) (pulse_tran), signal_freq,
				(int*) (time_output), time_esti, cout, hy_info);
		////End of processing/////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////
		printf("%f %f\n", az, elv);
		printf("   %f %f %f %f\n",pwr[0],pwr[1],pwr[2],pwr[3]);
		*azimuth = az;
		*elavator = elv;
#ifdef DEBUG
		printf("********END*******");
#endif
	} else {
#ifdef DEBUG
		printf("cant detect pulse\n");
#endif
		*azimuth = -999;
		*elavator = -999;
	}
	return PID_output_gain;
}
#ifdef SIMULATION
float getData(float* v1, float* v2, float* v3, float* v4, char name[20], int N) {
	FILE *fp = fopen(name, "r");
	int i, j, n;
	int a = 0, b = 0, c = 0, d = 0, e = 0;
	char x1[10], x2[10], x3[10], x4[10], t[7];
	char txt[50];
	float t1, t2;
	//fp = fopen("C:\Users\Uset\Documents\VisualDSP Projects\SimHydro2\AA.csv","r"); // read mode
	if (fp == NULL) {
#ifdef DEBUG
		printf("Error while opening the file.\n");
#endif
		return (0);
	}
#ifdef DEBUG
	printf("Get Data\n");
#endif
	for (i = 0; i < N; i++) {
		//printf("%d run\n",i);
		fgets(txt, 50, fp);

		j = 0;
		n = 0;
		a = 0;
		b = 0;
		c = 0;
		d = 0;
		while (txt[j] != '\n') {

			//printf("%c",txt[j]);
			if (txt[j] == ',')
				n++;
			else if (n == 0) {
				x1[a] = txt[j];
				a++;
			} else if (n == 1) {
				x2[b] = txt[j];
				b++;
			} else if (n == 2) {
				x3[c] = txt[j];
				c++;
			} else if (n == 3) {
				x4[d] = txt[j];
				d++;
			}
			j++;
			if (j > 80) {
#ifdef DEBUG
				printf("%d", j);
#endif
				break;
			}
		}
		v1[i] = atof(x1);
		v2[i] = atof(x2);
		v3[i] = atof(x3);
		v4[i] = atof(x4);

		//printf("%f %f %f %f\n",v1[i],v2[i],v3[i],v4[i]);
	}
	fclose(fp);
	return (1);
}
#endif
//random noise
#ifdef DEBUG
float rand_normal(float mu, float sigma) {
	float u1, u2, w, mult;
	static float x1, x2;
	static int call = 0;
	if (call == 1) {
		call = !call;
		return (mu + sigma * (float) x2);
	}
	do {
		u1 = -1 + ((float) rand() / RAND_MAX) * 2;
		u2 = -1 + ((float) rand() / RAND_MAX) * 2;
		w = pow(u1, 2) + pow(u2, 2);
	}while (w >= 1 || w == 0);
	mult = sqrt((-2 * log(w)) / w);
	x1 = u1 * mult;
	x2 = u2 * mult;
	call = !call;
	return (mu + sigma * (float) x1);
}

// generate pulse
void generate_signal(complex_float* generated_signal, struct Signal S) {
	int i = 0;
	int num_samples = (int) S.ob * S.fs;
	//printf("%d %d %d",ts*num_samples/ob_time,(ts+tp)*num_samples/ob_time,num_samples);
	for (i = 0; i < num_samples; i++) {

		if (i * S.ob / num_samples >= S.ts
				&& i * S.ob / num_samples < (S.ts + S.tp)) {
			generated_signal[i].re = S.vp
			* cos(2 * PI * S.fo * i * S.ob / num_samples);
			generated_signal[i].im = S.vp
			* sin(2 * PI * S.fo * i * S.ob / num_samples);
			//printf("%d, %.4f , %.4f\n",i,generated_signal[i].re,generated_signal[i].im);
		} else {
			generated_signal[i].re = 0.0;
			generated_signal[i].im = 0.0;
		}

	}
}
#endif

int error_cut(float*in1, float*in2, float*in3, float*in4)
{
	for(int i=0;i<50;i++)
	{
		if(in1[i]>0.3 || in2[i]>0.3 || in3[i]>0.3 || in4[i]>0.3)
			return (1);
	}
	return(0);
}

//searching
int searching(float *sig, int N)
{
	int output = 0;
	int i = 0;
	float volt_thr = 1;
	float max = volt_thr;
	for(i = 0; i < N; i++) {
		if(sig[i] > max)
		{
			output = i;
			max = sig[i];
		}
	}
	if((output - 20 )< 0)
		output = 0;
	return output;
}

void sig_detect(float *in1, float *in2, float *in3, float *in4,
				float *out1, float *out2, float *out3, float *out4,
				int peak_pos, int N /*N should be 500*/) {
	int i;
	for(i = 0; i < N; i++) {
		out1[i]= in1[i+peak_pos];
		out2[i]= in2[i+peak_pos];
		out3[i]= in3[i+peak_pos];
		out4[i]= in4[i+peak_pos];
	}
	// If searching is good enough,we can omit detect function.
	// So far,we should test average searching time and function performance.
}

//hydrophone position
void hydrophone_arrangement(float *x, float *y, float* ant_loc, uint32_t signal_freq) {
	int i;
	float temp_x = 0, temp_y = 0;
	float lamb = (float)input.SoundSpeed / ((float)signal_freq / 1000);
	for (i = 0; i < 4; i++) {
		x[i] = ant_loc[i * 2] / lamb;
		y[i] = ant_loc[i * 2 + 1] / lamb;
		temp_x += x[i];
		temp_y += y[i];
	}
	temp_x /= 4;
	temp_y /= 4;
	//printf("%f\n",temp_x);
	for (i = 0; i < 4; i++) {
		x[i] = (temp_x) - x[i];
		y[i] = (temp_y) - y[i];
#ifdef DEBUG
		printf("%f %f\n", x[i], y[i]);
#endif
	}
}

void phase_delay(complex_float *complex_phase_shift, float azimuth,
		float elevation, float *x, float *y) {
	//output is matrix 4x4
	int k;
	float az = PI * azimuth / 180;
	float elv = PI * elevation / 180;
	float phase_shift;
	for (k = 0; k < 4; k++) {
		phase_shift = -2 * PI
				* (x[k] * sin(elv) * cos(az) + y[k] * sin(elv) * sin(az));
		complex_phase_shift[k * 5].re = cos(phase_shift);
		complex_phase_shift[k * 5].im = sin(phase_shift);
#ifdef DEBUG
		printf("%f %f", complex_phase_shift[k * 5].re,
				complex_phase_shift[k * 5].im);
#endif
	}
#ifdef DEBUG
	printf("\n");
#endif
}

#ifdef SIMULATION
void generate_recieved_signal(complex_float *output_signal, complex_float *s,
		complex_float *transmitted_signal, struct Channel ch) {
	int n_mic = 4;
	int max_delay = 4;
	int i, j;
	int p_time_sample;
	float p_time, gain, phase, path_az, path_elv;
	complex_float complex_gain;
	//complex **reflected_sig;
	complex_float v[4][4];//phase shift of signal
	complex_float path_v[4][4];//phase shift of path signal

	float noise_mag = pow(10, (ch.noise / 20));
	float path_mag = pow(10, (ch.power / 20));

	//matShow(v,4,n_mic);
	//signal with phase delay depending on azi and elv
	for (i = 0; i < ch.size; i++) {
		s[0 * ch.size + i] = transmitted_signal[i];
		s[1 * ch.size + i] = transmitted_signal[i];
		s[2 * ch.size + i] = transmitted_signal[i];
		s[3 * ch.size + i] = transmitted_signal[i];
		//printf("%f\n",transmitted_signal[i]);
	}
	phase_delay((complex_float*) (v), ch.azi, ch.elv, ch.x, ch.y);
	cmatmmltf(output_signal, (complex_float*) (v), (complex_float*) (s), 4,
			n_mic, ch.size);

	//multipath
	srand(time(NULL));
	for (i = 0; i < ch.Np; i++) {
		////delay
		p_time = rand() % 4 + 1 + rand() % 1000 / 1000.0;
		p_time_sample = (int) (p_time * ch.fs);
		gain = (float) path_mag / (float) ch.Np;
		phase = (float) rand() / ((float) RAND_MAX / (2 * PI));
		complex_gain.re = gain * cos(phase);
		complex_gain.im = gain * sin(phase);
		path_az = rand() % 350 + rand() % 1000 / 1000.0 - 180;
		path_elv = rand() % 60 + rand() % 1000 / 1000.0 + 10;
#ifdef DEBUG
		printf("tmis delay %f, az = %f, ev = %f\n", p_time, path_az, path_elv);
#endif
		phase_delay((complex_float*) (path_v), path_az, path_elv, ch.x, ch.y);

		//printf("%d\n",p_time_sample);
		for (j = 0; j < ch.size; j++) { //printf("%d :",j);
			if (j >= p_time_sample) {
				s[j] = transmitted_signal[j - p_time_sample];
				s[j + 1 * ch.size] = transmitted_signal[j - p_time_sample];
				s[j + 2 * ch.size] = transmitted_signal[j - p_time_sample];
				s[j + 3 * ch.size] = transmitted_signal[j - p_time_sample];
			}

		}
		cmatsmltf((complex_float*) (s), (complex_float*) (s), complex_gain,
				n_mic, ch.size);
		cmatmmltf((complex_float*) (s), (complex_float*) (path_v),
				(complex_float*) (s), 4, n_mic, ch.size);
		cmatmaddf(output_signal, output_signal, (complex_float*) (s), 4,
				ch.size);
	}
	for (i = 0; i < n_mic; i++)
	for (j = 0; j < ch.size; j++)
	output_signal[i * ch.size + j].re += 0.1
	* rand_normal(0.0, noise_mag);
}
#endif

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void filtering(float dm*(v1), float dm*(v2), float dm*(v3), float dm*(v4),
		float dm*(out1), float dm*(out2), float dm*(out3), float dm*(out4),
		float dm*(filter), int n_sample, int n_filter) {
	int i;

	memcpy((void *)In1_buf, g_fSineWaveIn1_Right, AUDIO_MAX_SAMPLES);
	memcpy((void *)In2_buf, g_fSineWaveIn1_Left, AUDIO_MAX_SAMPLES);
	memcpy((void *)In3_buf, g_fSineWaveIn2_Right, AUDIO_MAX_SAMPLES);
	memcpy((void *)In4_buf, g_fSineWaveIn2_Left, AUDIO_MAX_SAMPLES);
#if 0
	convolve(In1_buf, n_sample, filter, n_filter, out1);
	convolve(In2_buf, n_sample, filter, n_filter, out2);
	convolve(In3_buf, n_sample, filter, n_filter, out3);
	convolve(In4_buf, n_sample, filter, n_filter, out4);
#else

	if (pcount == 0) {
		Init_FIR();
		pcount++;
	} else {
		*pFIRCTL1 &= ~FIR_DMAEN;
		*pFIRCTL1 |= FIR_DMAEN;
	}

	while ((*pFIRDMASTAT & BIT_6) > 0);
	//while (acc_over == 0);
	acc_over = 0;

//	for (i = 0; i < AUDIO_MAX_SAMPLES; ++i) {
//		out1[i] *= filter[sizeof(filter) - 1];
//		out2[i] *= filter[sizeof(filter) - 1];
//		out3[i] *= filter[sizeof(filter) - 1];
//		out4[i] *= filter[sizeof(filter) - 1];
//	}
#endif
}


void power_output(float*in1, float*in2, float*in3, float*in4, float* out_pwr, int N) {
	out_pwr[0] = 0;
	out_pwr[1] = 0;
	out_pwr[2] = 0;
	out_pwr[3] = 0;
	int wd_pulse =300;
	int str_pulse = 450;

	/*for (int i = 400; i < 500; i++) {
		if(in1[i] > out_pwr[0])
			out_pwr[0] = in1[i];
		if(in2[i] > out_pwr[1])
			out_pwr[1] = in2[i];
		if(in3[i] > out_pwr[2])
			out_pwr[2] = in3[i];
		if(in4[i] > out_pwr[3])
			out_pwr[3] = in4[i];

	}*/
	for (int i = str_pulse; i < str_pulse+wd_pulse; i++) {
		out_pwr[0] += pow(in1[i],2);
		out_pwr[1] += pow(in2[i],2);
		out_pwr[2] += pow(in3[i],2);
		out_pwr[3] += pow(in4[i],2);
	}
	out_pwr[0] = (out_pwr[0])/(wd_pulse);
	out_pwr[1] = (out_pwr[1])/(wd_pulse);
	out_pwr[2] = (out_pwr[2])/(wd_pulse);
	out_pwr[3] = (out_pwr[3])/(wd_pulse);

	//printf("   %f %f %f %f\n",out_pwr[0],out_pwr[1],out_pwr[2],out_pwr[3]);
}

void sampling(float*in1, float*in2, float*in3, float*in4, float *out1,
		float *out2, float *out3, float *out4, int sampling_rate, int N) {
	//Sampling
	int i;
	int idx;
	int max = N / sampling_rate;
	for (i = 0; i < max; i++) {
		idx = i * sampling_rate;
			out1[i] = in1[idx];
			out2[i] = in2[idx];
			out3[i] = in3[idx];
			out4[i] = in4[idx];
	}
}

void demod(float*in1, float*in2, float*in3, float*in4, complex_float *out1,
		complex_float *out2, complex_float *out3, complex_float *out4, int N,
		uint32_t fo, float *filter, int n_filter, float tm, struct Temp t) {
	int i = 0,n = 0;
	float wt = 0 , sin_wt, cos_wt;
	const float w = (2 * PI * (fo / 1000) * tm) / N;
	for (i = 0; i < N; i++) {
		wt = ((float)i * w);
		sin_wt = sinf(wt);
		cos_wt = cosf(wt);
		t.w1[i] = cos_wt * in1[i];
		t.w2[i] = sin_wt * in1[i];
		t.x1[i] = cos_wt * in2[i];
		t.x2[i] = sin_wt * in2[i];
		t.y1[i] = cos_wt * in3[i];
		t.y2[i] = sin_wt * in3[i];
		t.z1[i] = cos_wt * in4[i];
		t.z2[i] = sin_wt * in4[i];
	}
	convolve(t.w1, N, filter, n_filter, t.w3);
	convolve(t.w2, N, filter, n_filter, t.w4);
	convolve(t.x1, N, filter, n_filter, t.x3);
	convolve(t.x2, N, filter, n_filter, t.x4);
	convolve(t.y1, N, filter, n_filter, t.y3);
	convolve(t.y2, N, filter, n_filter, t.y4);
	convolve(t.z1, N, filter, n_filter, t.z3);
	convolve(t.z2, N, filter, n_filter, t.z4);
	
	for (i = 0; i < (N + n_filter); i++) {
		out1[i].re = t.w3[i]; out1[i].im = t.w4[i];
		out2[i].re = t.x3[i]; out2[i].im = t.x4[i];
		out3[i].re = t.y3[i]; out3[i].im = t.y4[i];
		out4[i].re = t.z3[i]; out4[i].im = t.z4[i];
	}
}

int pulse_detect(complex_float*in1, complex_float*in2, complex_float*in3,
		complex_float*in4, complex_float*out, int N, int Ns, float* pavr) {
	int output = 0;
	int i;
	float power[N];
	float pmin = pow(10, 10);
	float pref = 0.0;
	float h = 0.00002;
	float sum = 0.0;
	*pavr = 0.0;
	for (i = 0; i < N; i++) {
		power[i] = pow(in1[i].re, 2) + pow(in2[i].re, 2) + pow(in3[i].re, 2)
				+ pow(in4[i].re, 2);
		sum += power[i];
		//printf("%f\n",power[i]);
	}
	pref = sum / N;
	h = h / 0.000039 * pref;
	sum = 0.0;
	printf("power avr %f\n", pref * pow(10, 10));
	for (i = 30; i < N; i++) {
		//sum += power[i];
		//printf("%d,   %f,   pref:%f\n",i,sum/(i+1),pref);
		*pavr = *pavr * ((float) (i)) / ((float) (i + 1))
				+ power[i] * 1.0 / ((float) (i + 1));
		//printf("%d,   %f,   pref:%f\n",i,power[i],pavr);
		//if(sum/(i+1)>pref)
		if (power[i] > *pavr + h) {
			output = i;
#ifdef DEBUG
			printf("detected position %d\n", i);
#endif
			break;
		}
	}

	free(power);

	if (output != 0) {
		output += 5;
		for (i = output; i < output + Ns; i++) {
			out[i - output] = in1[i];
			out[Ns + i - output] = in2[i];
			out[2 * Ns + i - output] = in3[i];
			out[3 * Ns + i - output] = in4[i];
		}
		return (1);
	} else
		return (0);
}

#ifdef SIMULATION
void down_sampling(complex_float* input, complex_float* output,
		int downsampling_rate, int N) {
	int i;
	for (i = 0; i < N / downsampling_rate; i++) {
		input[i] = output[i * downsampling_rate];
		input[i] = output[i * downsampling_rate];
		input[i] = output[i * downsampling_rate];
		input[i] = output[i * downsampling_rate];
	}
}
#endif

void cmatH(complex_float* output, complex_float* input, int row, int col) {
	int c=0, d=0;
	//printf("cmatH");
	for (c = 0; c < col; c++)
		for (d = 0; d < row; d++)
			output[c * row + d] = conjf(input[d * col + c]);
}

void cmattran(complex_float* output, complex_float* input, int row, int col) {
	int c=0, d=0;
	//printf("cmattran");
	for (c = 0; c < col; c++)
		for (d = 0; d < row; d++)
			output[c * row + d] = input[d * col + c];
}

//void mattran(float* output, float* input, int row, int col) {
//	int c=0, d=0;
//	//printf("cmattran");
//	for (c = 0; c < col; c++)
//		for (d = 0; d < row; d++)
//			output[c * row + d] = input[d * col + c];
//}
complex_float cmattrace(complex_float* input, int size) {
	int i=0;
	complex_float out;
	//printf("cmattrace");
	out.re = 0.0;
	out.im = 0.0;
	for (i = 0; i < size; i++) {
		out.re += input[i * size + i].re;
		out.im += input[i * size + i].im;
	}
	//printf("%.2f %.2f",out.re,out.im);
	return (out);
}

void cmatmlt(complex_float* out, complex_float* in1, complex_float* in2,
		int row1, int col1, int col2) {
	int i=0, j=0, k=0;
	for (i = 0; i < row1; i++) {
		for (j = 0; j < col2; j++) {
			out[i * row1 + j].re = 0;
			out[i * row1 + j].im = 0;
			for (k = 0; k < col1; k++) {
				out[i * row1 + j].re += in1[i * row1 + k].re
						* in2[k * col1 + j].re
						- in1[i * row1 + k].im * in2[k * col1 + j].im;
				out[i * row1 + j].im += in1[i * row1 + k].im
						* in2[k * col1 + j].re
						+ in1[i * row1 + k].re * in2[k * col1 + j].im;
			}
		}
	}

}

int delay_time_estimator(int* output, complex_float *sub_pulse,
		complex_float *sub_pulse_tran, float* eout, int N) {
	int i = 0, j = 0;
	float P_real[2][2] = { 0 };
	float P_inv[2][2] = { 0 };
	complex_float P[2][2];
	complex_float P_tran[2][2];
	complex_float c1[2][4];
	complex_float c1_H[4][2];
	complex_float e_temp1[2][4];
	complex_float e_temp2[4][4];
    complex_float e2;
    int num = 0;
    complex_float sum[4];

	sum[0].re =0;	sum[0].im=0;
    sum[1].re =0;	sum[1].im=0;
    sum[2].re =0;	sum[2].im=0;
    sum[3].re =0;	sum[3].im=0;

    eout[0] = 0.0; eout[1] = 0.0; eout[2] = 0.0;
    output[0] = 0; output[1] = 0; output[2] = 0;

    for(i = 0; i < N; i++) {
    	sum[0].re += sub_pulse[i].re;
    	sum[1].re += sub_pulse[i+N].re;
    	sum[2].re += sub_pulse[i+2*N].re;
    	sum[3].re += sub_pulse[i+3*N].re;
		sum[0].im += sub_pulse[i].im;
    	sum[1].im += sub_pulse[i+N].im;
    	sum[2].im += sub_pulse[i+2*N].im;
    	sum[3].im += sub_pulse[i+3*N].im;
    }
    c1[0][0].re = 0;	c1[0][0].im = 0.0;
    c1[0][1].re = 0;	c1[0][1].im = 0.0;
    c1[0][2].re = 0;	c1[0][2].im = 0.0;
    c1[0][3].re = 0;	c1[0][3].im = 0.0;

    c1[1][0].re = sum[0].re-sub_pulse[0].re-sub_pulse[1].re;
    c1[1][1].re = sum[1].re-sub_pulse[N].re-sub_pulse[N+1].re;
    c1[1][2].re = sum[2].re-sub_pulse[N*2].re-sub_pulse[N*2+1].re;
    c1[1][3].re = sum[3].re-sub_pulse[N*3].re-sub_pulse[N*3+1].re;
    c1[1][0].im = sum[0].im-sub_pulse[0].im-sub_pulse[1].im;
    c1[1][1].im = sum[1].im-sub_pulse[N].im-sub_pulse[N+1].im;
    c1[1][2].im = sum[2].im-sub_pulse[N*2].im-sub_pulse[N*2+1].im;
    c1[1][3].im = sum[3].im-sub_pulse[N*3].im-sub_pulse[N*3+1].im;

    for(j = 0; j < 4; j++)
		P[0][j].im = 0.0;

	for(i = 3; i < N; i++) {
		P_real[0][0] = (float)N;
		P_real[0][1] = (float)N - i;
		P_real[1][0] = (float)N - i;
		P_real[1][1] = (float)N - i;

		matinvf((float*)(P_inv), (float*)(P_real), 2);
		for(j = 0; j < 4; j++)
			P[0][j].re = P_inv[0][j];
#if 0

       	c1[1][0].re -= sub_pulse[i-1].re;
        c1[1][1].re -= sub_pulse[i+N-1].re;
        c1[1][2].re -= sub_pulse[i+2*N-1].re;
        c1[1][3].re -= sub_pulse[i+3*N-1].re;
       	c1[1][0].im -= sub_pulse[i-1].im;
        c1[1][1].im -= sub_pulse[i+N-1].im;
        c1[1][2].im -= sub_pulse[i+2*N-1].im;
        c1[1][3].im -= sub_pulse[i+3*N-1].im;
#else
		c1[1][0] = csubf(c1[1][0], sub_pulse[i - 1]);
		c1[1][1] = csubf(c1[1][1], sub_pulse[i + N - 1]);
		c1[1][2] = csubf(c1[1][2], sub_pulse[i + 2 * N - 1]);
		c1[1][3] = csubf(c1[1][3], sub_pulse[i + 3 * N - 1]);
#endif
        c1[0][0] = sum[0];
	    c1[0][1] = sum[1];
        c1[0][2] = sum[2];
        c1[0][3] = sum[3];

        cmatH((complex_float*)(c1_H), (complex_float*)(c1), 2, 4);
        cmatmmltf((complex_float*)(e_temp1), (complex_float*)(P), 
			(complex_float*)(c1), 2, 2, 4);
        cmatmmltf((complex_float*)(e_temp2), (complex_float*)(c1_H),
			(complex_float*)(e_temp1), 4, 2, 4);
        e2 = cmattrace((complex_float*)(e_temp2), 4);
        eout[i] = e2.re;

        if((eout[i-1] > eout[i-2]) && (eout[i-1] > eout[i]) && (i > 3)) {
            output[i] = 1;
            num++;
	    } else
            output[i] = 0;
    }

	free(P_real);
	free(P_inv);
	free(P);
	free(P_tran);
	free(c1);
	free(c1_H);
	free(e_temp1);
	free(e_temp2);
	free(sum);

    return (num);
}

//void lstsqr(float *x, float *y, float *A, float *b) {
//	float At[3][4];
//	float AA[3][3];
//	float AA_inv[3][3];
//	float Ab[3][1];
//	float result[3][1];
//	float e1[3][1];
//	float error, error_n;
//	float diff_e = 0.0;
//	float alpha = 0.5;
//	int cnt = 0;
//	int i;
//	float sum;
//	float out[3];
//	float g[4];
//	float g1, g2, g3;
//	mattran((float*) (At), A, 4, 3);
//	matmmltf((float*) (AA), (float*) (At), A, 3, 4, 3);
//	matinvf((float*) (AA_inv), (float*) (AA), 3);
//	matmmltf((float*) (Ab), (float*) (At), b, 3, 4, 1);
//	matmmltf((float*) (out), (float*) (AA_inv), (float*) (Ab), 3, 3, 1);
//	*x = out[0];
//	*y = out[1];
//	//printf("%f  %f  %f",out[0],out[1],out[2]);
//}

float matnorm(float*array, int row, int col) {
	int i=0, j=0;
	float norm = 0.0;
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			norm += pow(array[i * col + j], 2);
	norm = sqrt(norm);
	return (norm);
}

void gradient(float *gb, float *Bb, complex_float *c, float az, float ev,
		float *x, float *y) {
	//output gb,Bb
	int i, j;
	float sx = sin(ev) * cos(az);
	float sy = sin(ev) * sin(az);
	float const psi = 2 * PI;

	float da_dsx = 0.0;
	float da_dsy = 0.0;
	float d2a_dsx2 = 0.0;
	float d2a_dsy2 = 0.0;
	float d2a_dsx_dsy = 0.0;

	complex_float ch[4] = { 0 };
	float cr, ci;
	float dx, dy, dcr, dci, d2cr, d2ci;
	// convert to gradient vector wrt to phi and theta
	float dsx_daz = -1 * sin(ev) * sin(az);
	float dsx_dev = cos(ev) * cos(az);
	float dsy_daz = sin(ev) * cos(az);
	float dsy_dev = cos(ev) * sin(az);

	//convert to hassian vector wrt to phi and theta
	float d2sx_daz2 = -1 * sin(ev) * cos(az);
	float d2sx_dev2 = -1 * sin(ev) * cos(az);
	float d2sy_daz2 = -1 * sin(ev) * sin(az);
	float d2sy_dev2 = -1 * sin(ev) * sin(az);
	float d2sx_daz_dev = -1 * cos(ev) * sin(az);
	float d2sy_daz_dev = -1 * cos(ev) * cos(az);

	float jg[2][4] = { 0 };
	float gs[2][1] = { 0 };
	float hs[5][1] = { 0 };
	float jh[3][15] = { 0 };
	float hb[3][1] = { 0 };

	for (i = 0; i < 4; i++)
		ch[i] = conjf(c[i]);

	for (i = 0; i < 4; i++)
		for (j = i + 1; j < 4; j++) {
			cr = c[i].re * ch[j].re - c[i].im * ch[j].im;
			ci = c[i].re * ch[j].im + c[i].im * ch[j].re;
			dx = x[j] - x[i];
			dy = y[j] - y[i];
			dcr = cr * sin(2 * PI * (dx * sx + dy * sy));
			dci = -1 * ci * cos(2 * PI * (dx * sx + dy * sy));
			da_dsx += 2.0 * (-dcr * dx + dci * dx) * psi;
			da_dsy += 2.0 * (-dcr * dy + dci * dy) * psi;
			d2cr = cr * cos(2 * PI * (dx * sx + dy * sy));
			d2ci = -ci * sin(2 * PI * (dx * sx + dy * sy));
			d2a_dsx2 -= 2.0 * (d2cr * dx * dx + d2ci * dx * dx) * psi * psi;
			d2a_dsy2 -= 2.0 * (d2cr * dy * dy + d2ci * dy * dy) * psi * psi;
			d2a_dsx_dsy -= 2.0 * (d2cr * dx * dy + d2ci * dx * dy) * psi * psi;
		}
	// convert to gradient vector wrt to phi and theta
	gs[0][0] = da_dsx;
	gs[0][1] = da_dsy;
	jg[0][0] = dsx_daz;
	jg[0][1] = dsy_daz;
	jg[0][2] = dsx_dev;
	jg[0][3] = dsy_dev;
	matmmltf(gb, (float*) (jg), (float*) (gs), 2, 2, 1);
	//convert to hassian vector wrt to phi and theta
	hs[0][0] = d2a_dsx2;
	hs[0][1] = d2a_dsx_dsy;
	hs[0][2] = d2a_dsy2;
	hs[0][3] = da_dsx;
	hs[0][4] = da_dsy;

	jh[0][0] = pow(dsx_daz, 2);
	jh[0][1] = dsx_daz * dsy_daz;
	jh[0][2] = pow(dsy_daz, 2);
	jh[0][3] = d2sx_daz2;
	jh[0][4] = d2sy_daz2;
	jh[0][5] = dsx_daz * dsx_dev;
	jh[0][6] = dsx_daz * dsy_dev;
	jh[0][7] = dsy_daz * dsy_dev;
	jh[0][8] = d2sx_daz_dev;
	jh[0][9] = d2sy_daz_dev;
	jh[0][10] = pow(dsx_dev, 2);
	jh[0][11] = dsx_dev * dsy_dev;
	jh[0][12] = pow(dsy_dev, 2);
	jh[0][13] = d2sx_dev2;
	jh[0][14] = d2sy_dev2;
	//hs[5][1]      = { {d2a_dsx2      },{d2a_dsx_dsy          },{d2a_dsy2         },{da_dsx       },{ da_dsy       }}
	//jh[3][5]      = { {pow(dsx_daz,2) , d_sx_d_az*d_sy_d_az   , pow(d_sy_d_az,2)  , d2sx_daz2     , d2sy_daz2     }
	//                      ,{dsx_daz*dsx_dev, dsx_daz*dsy_dev       , dsy_daz*dsy_dev   , d2sx_daz_dev  , d2sy_daz_dev  }
	//                     ,{pow(dsx_dev,2) , dsx_dev*dsy_dev       , pow(dsy_dev,2)    , d2sx_dev2     , d2sy_dev2     }}
	matmmltf((float*) (hb), (float*) (jh), (float*) (hs), 3, 5, 1);
	//otMat(jh,hs,hb,3,5,5,1);
	Bb[0] = hb[0][2] / (hb[0][2] * hb[0][0] - pow(hb[0][1], 2));
	Bb[1] = -1 * hb[0][1] / (hb[0][2] * hb[0][0] - pow(hb[0][1], 2));
	Bb[2] = -1 * hb[0][1] / (hb[0][2] * hb[0][0] - pow(hb[0][1], 2));
	Bb[3] = hb[0][0] / (hb[0][2] * hb[0][0] - pow(hb[0][1], 2));

	free(jg);
	free(gs);
	free(hs);
	free(jh);
	free(hb);
	free(ch);
}

void bearingEstimator(float *az, float *ev, float *az_t0, float *elv_t0,
		complex_float* sub_pulse, int Npulse, complex_float* sub_pulse_tran,
		uint32_t signal_freq, int *delay_time, int Ndelay, complex_float *c_out, struct Hydro_info hy)
//,complex_float*V,,complex_float*VH
//,complex_float*P,complex_float*P_real,complex_float*P_inv,complex_float*c
{
	int i=0, j=0, k=0;
	int col = Ndelay + 1;
	int input[Ndelay];
	complex_float V[Npulse][col];
	complex_float VH[col][Npulse];
	complex_float P[col][col];
	float P_real[col][col];
	float P_inv[col][col];

	complex_float c0[4] = { 0 };
	complex_float c[col][4];
	complex_float c1[col][4];
	float cphase[4] = { 0 };

	float sin_elv = 0, elv_t_r = 0, az_t_r = 0, 
			az_t = 0, elv_t = 0, az0 = 0, ev0 = 0;

	bool fine_tune = true, finding_root = true;

	float gb[2][1] = { 0 }, g[2][1] = { 0 }, gn[2][1] = { 0 };
	float Bb[2][2] = { 0 }, B[2][2] = { 0 }, Bn[2][2] = { 0 };
	float d[2][1] = { 0 };
	float alpha = pow(10, -2);
	float norm_gold = 0, norm_gnew = 0;
	int cnt = 0;
	float azn = 0, evn = 0;
	float error = 0;
	float a1 = 0, b1 = 0;
	float errorThreshold = pow(10, -6);

	/////////Variable for new code/////////
	float error_min = pow(10, 20);
	float err[4][4] = { 0 };
	float phase_diff[4] = { 0 }, phasetemp[4] = { 0 };
	float err_sum = 0.0;
	int idx[4] = { 0 };
	float phase_use[4] = { 0 };
	int temp = 0;
	float tempf = 0;
	float out1[3] = { 0 };
	///////////////////////////////////////
	int count_finetune = 200;
	///////////////////////////////////////
	j = 0;
	for (i = 0; i < Npulse; i++) {
		V[0][i * col].re = 1.0;
		V[0][i * col].im = 0.0;

		if (delay_time[i] == 1) {
			input[j] = i + 1;
			j++;
		}
	}
	for (i = 0; i < Npulse; i++)
		for (j = 0; j < Ndelay; j++) {
			if (input[j] > i) {
				V[0][i * col + (j + 1)].re = 0.0;
				V[0][i * col + (j + 1)].im = 0.0;
			} else {
				V[0][i * col + (j + 1)].re = 1.0;
				V[0][i * col + (j + 1)].im = 0.0;
			}
		}

	cmatH((complex_float*) (VH), (complex_float*) (V), Npulse, col);
	cmatmmltf((complex_float*) (P), (complex_float*) (VH), (complex_float*) (V),
			col, Npulse, col);
	for (i = 0; i < col; i++)
		for (j = 0; j < col; j++)
			P_real[0][i * col + j] = P[0][i * col + j].re;
	matinvf((float*) (P_inv), (float*) (P_real), col);
	for (i = 0; i < col; i++)
		for (j = 0; j < col; j++)
			P[0][i * col + j].re = P_inv[0][i * col + j];

	cmattran(sub_pulse_tran, sub_pulse, 4, Npulse);
	cmatmmltf((complex_float*) (c1), (complex_float*) (VH), sub_pulse_tran, col,
			Npulse, 4);
	cmatmmltf((complex_float*) (c), (complex_float*) (P), (complex_float*) (c1),
			col, col, 4);
	// use first row of main pulse
	c0[0] = c[0][0];
	c0[1] = c[0][1];
	c0[2] = c[0][2];
	c0[3] = c[0][3];

	for (i = 0; i < 4; i++) {
		cphase[i] = atan2(c0[i].im, c0[i].re);
		c_out[i].re = c[0][i].re;
		c_out[i].im = c[0][i].im;
	}

	////New code//////////////////////////////
	for (i = 0; i < 4; i++) {
		err_sum = 0;
		for (j = 0; j < 4; j++) {
			if ((cphase[j] - cphase[i]) < 0)
				phase_diff[j] = (cphase[j] - cphase[i])
						- ((int) ((cphase[j] - cphase[i]) / (2 * PI)) - 1)
								* (2 * PI);
			else
				phase_diff[j] =
						(cphase[j] - cphase[i])
								- ((int) ((cphase[j] - cphase[i]) / (2 * PI))
										* (2 * PI));
			phasetemp[j] = phase_diff[j];
		}

		idx[0] = 0;
		idx[1] = 1;
		idx[2] = 2;
		idx[3] = 3;

		for (j = 0; j < (4 - 1); ++j) {
			for (k = 0; k < 4 - 1 - j; ++k) {
				if (phasetemp[k] > phasetemp[k + 1]) {
					tempf = phasetemp[k + 1];
					phasetemp[k + 1] = phasetemp[k];
					phasetemp[k] = tempf;
					temp = idx[k + 1];
					idx[k + 1] = idx[k];
					idx[k] = temp;
				}
			}
		}

		for (j = 0; j < 4; j++) {
			if (phase_diff[0] - hy.phase_err[4 * j] > 0)
				err[0][4 * j] = phase_diff[0] - hy.phase_err[4 * j];
			else
				err[0][4 * j] = 0;
			if (phase_diff[1] - hy.phase_err[4 * j + 1] > 0)
				err[0][4 * j + 1] = phase_diff[1] - hy.phase_err[4 * j + 1];
			else
				err[0][4 * j + 1] = 0;
			if (phase_diff[2] - hy.phase_err[4 * j + 2] > 0)
				err[0][4 * j + 2] = phase_diff[2] - hy.phase_err[4 * j + 2];
			else
				err[0][4 * j + 2] = 0;
			if (phase_diff[3] - hy.phase_err[4 * j + 3] > 0)
				err[0][4 * j + 3] = phase_diff[3] - hy.phase_err[4 * j + 3];
			else
				err[0][4 * j + 3] = 0;
			err_sum += err[0][4 * j] + err[0][4 * j + 1] + err[0][4 * j + 2]
					+ err[0][4 * j + 3];
		}
		//printf("sum %f\n",err_sum);

		if ((idx[0] == 0) && (idx[3] != 2))
			err_sum += pow(10, 13);
		else if ((idx[0] == 2) && (idx[3] != 0))
			err_sum += pow(10, 13);
		else if ((idx[0] == 1) && (idx[3] != 3))
			err_sum += pow(10, 13);
		else if ((idx[0] == 3) && (idx[3] != 1))
			err_sum += pow(10, 13);

		if (err_sum < error_min) {
			error_min = err_sum;
			for (j = 0; j < 4; j++)
				phase_use[j] = phase_diff[j];
		}

	}

	////End of new code///////////////////////
	//apply leastsqrt with const.array
	matmmltf((float*)(out1), hy.lstsqr, (float *)(phase_use), 3, 4, 1);
	a1 = out1[0];
	b1 = out1[1];


	//printf("a,b: %f  %f\n",a1,b1);
	if (sqrt(pow(a1, 2) + pow(b1, 2)) < 1.0)
		sin_elv = sqrt(pow(a1, 2) + pow(b1, 2));
	else
		sin_elv = 1.0;
	elv_t_r = asin(sin_elv);
	//azimuth = arctan(sy/sx)
	az_t_r = atan2(b1, a1);
	az_t = az_t_r * 180 / PI;
	elv_t = elv_t_r * 180 / PI;
	//perform newton method to find the nearest local maximum point
	//printf("t_r:az = %f, ev = %f\n",az_t_r,elv_t_r);
	//printf("t:az = %f, ev = %f\n",az_t,elv_t);
	if (fine_tune) {
		finding_root = true;
		while (finding_root) {
			az0 = az_t_r;
			ev0 = elv_t_r;
			gradient((float*) (g), (float*) (B), (complex_float*) (c0), az0,
					ev0, hy.x, hy.y);
			if (matnorm((float*) (g), 2, 1) < pow(10, -4)) {
				finding_root = false;
				break;
			}
			matmmltf((float*)(d), (float*)(B), (float*)(g), 2, 2, 1);
			//d[0][0] = B[0][0]*g[0][0];  d[0][1] = B[0][1]*g[0][0];
			norm_gold = matnorm((float*) (g), 2, 1);
			norm_gnew = norm_gold + 1;
			cnt = 0;
			while (((norm_gold < norm_gnew)) && (cnt < 20)) {
				cnt += 1;
				alpha = alpha / 2.0;
				azn = az0 - alpha * d[0][0];
				evn = ev0 - alpha * d[0][1];
				if (azn > PI)
					azn = PI - azn;
				else if (azn < -PI)
					azn = PI + azn;
				if (evn > PI / 2.0)
					evn = PI - evn;
				else if (evn < 0.0)
					evn = -evn;
				gradient((float*) (gn), (float*) (Bn), (complex_float*) (c0),
						azn, evn, hy.x, hy.y);
				norm_gnew = matnorm((float*) (gn), 2, 1);
			}
			if (cnt < 20) {
				error = sqrt(pow((az0 - azn), 2) + pow(ev0 - evn, 2));
				az0 = azn;
				ev0 = evn;
			} else
				error = 0.0;
			if (error < errorThreshold)
				finding_root = false;
			if (count_finetune-- <= 0)
				finding_root = false;
		}
		*az = az0 * 180 / PI;
		*ev = ev0 * 180 / PI;
		*az_t0 = az_t;
		*elv_t0 = elv_t;
		//return az, ev, az_t , elv_t

	} else {
		*az = az_t;
		*ev = elv_t;
		*az_t0 = az_t;
		*elv_t0 = elv_t;
	}
	//return az_t, elv_t, az_t , elv_t
#ifdef DEBUG
	printf("Before Norton : %f %f \nAfter Norton : %f %f\n", *az_t0, *elv_t0,
			*az, *ev);
#endif
	free(V);
	free(VH);
	free(P);
	free(P_real);
	free(P_inv);

	free(c0);
	free(c);
	free(c1);
	free(cphase);

	free(gb);
	free(g);
	free(gn);
	free(Bb);
	free(B);
	free(Bn);
	free(d);

	free(err);
	free(phase_diff);
	free(phasetemp);
	free(idx);
	free(phase_use);
	free(out1);
}

int detect(complex_float*in1, complex_float*in2, complex_float*in3,
		complex_float*in4, complex_float*out, int N, int Ns, int* G) {
	int iOut = 0;
	int i = 0;
	float power = 0;
	float sum_noise = 0.0;
	float sum_sig = 0.0;
	float threshold = input.PowerThreshold;
	int chk_noise = 1;

	output.power[0] = 0;
	output.power[1] = 0;
	output.power[2] = 0;
	output.power[3] = 0;

	for (i = 0; i < N; i++) {
		power = pow(in1[i].re, 2) + pow(in2[i].re, 2) + pow(in3[i].re, 2)
				+ pow(in4[i].re, 2);
		output.power[0] += sqrtf(powf(in1[i].re,2) + powf(in1[i].im, 2));
		output.power[1] += sqrtf(powf(in2[i].re,2) + powf(in2[i].im, 2));
		output.power[2] += sqrtf(powf(in3[i].re,2) + powf(in3[i].im, 2));
		output.power[3] += sqrtf(powf(in4[i].re,2) + powf(in4[i].im, 2));
		//if (chk_noise)
		//	sum_noise += power;
		//else
		//	sum_sig += power;
		
		if (sqrt(power) > threshold) {
			if(i < 30) {
				return(0);
			}
			if(N-i > 105) {
				iOut = i+5;
				//chk_noise = 0;
				break;
			}
			//treshold = 1;
		}
	}
	//printf("SNR %.4f\n",sqrt(sum_sig/N)/sqrt(sum_noise/N));
	if(iOut != 0)
	{
		//printf("detect pulse");
		//output += 5;
		for (i = iOut; i < iOut + Ns; i++) {
			out[i-iOut] = in1[i];
			out[Ns+i-iOut] = in2[i];
			out[2*Ns+i-iOut] = in3[i];
			out[3*Ns+i-iOut] = in4[i];
		}
		return(1);
	}
	else
		return (0);
}

int PID_gain(float Psig, float Pnoise) {
	static int gain = 0;
	if (Psig == 0)
		gain += 1;
	else if (Pnoise == 0)
		gain -= 1;
	else if (Psig / Pnoise > 0 && Psig / Pnoise < 100)
		gain += 1;
	else if (Psig / Pnoise > 500)
		gain -= 1;
	else
		gain = 0;
	if (gain < 0)
		gain = max(-5, gain);
	else
		gain = min(5, gain);

	return (gain);
}
