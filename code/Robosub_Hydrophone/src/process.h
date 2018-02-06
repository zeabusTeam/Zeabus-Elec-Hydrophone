/*
 * Author : Anol Paisal
 * Company : EmOne (Thailand) Co.,Ltd.
 * Email : anolpaisal@gmail.com
 * Copyright @ 2015
 * Maintainer : Tita
 */

#include <stdint.h>

float rand_normal(float mu, float sigma);
void generate_signal(complex_float* generated_signal, struct Signal s);
void hydrophone_arrangement(float *x, float *y, float* ant_loc, uint32_t signal_freq);
void phase_delay(complex_float *complex_phase_shift, float azimuth,
		float elevation, float *x, float *y);
void generate_recieved_signal(complex_float *output_signal, complex_float *s,
		complex_float *transmitted_signal, struct Channel ch);
void filtering(float dm*(v1), float dm*(v2), float dm*(v3), float dm*(v4),
		float dm*(out1), float dm*(out2), float dm*(out3), float dm*(out4),
		float dm*(filter), int n_sample, int n_filter);
void sampling(float*in1, float*in2, float*in3, float*in4, float *out1,
		float *out2, float *out3, float *out4, int sampling_rate, int N);
void demod(float*in1, float*in2, float*in3, float*in4, complex_float *out1,
		complex_float *out2, complex_float *out3, complex_float *out4, int N,
		uint32_t fo, float *filter, int n_filter, float tm, struct Temp t);
int pulse_detect(complex_float*in1,complex_float*in2,complex_float*in3,complex_float*in4
				,complex_float*out,int N,int Ns,float* pavr);
void down_sampling(complex_float* input, complex_float* output,
		int downsampling_rate, int N);
void cmatH(complex_float* output, complex_float* input, int row, int col);
void cmattran(complex_float* output, complex_float* input, int row, int col);
void mattran(float* output, float* input, int row, int col);
complex_float cmattrace(complex_float* input, int size);
int delay_time_estimator(int* output, complex_float *sub_pulse,
		complex_float *sub_pulse_tran, float* eout, int N);
//void lstsqr(float *x, float *y, float *A, float *b);
void gradient(float *gb, float *Bb, complex_float *c, float az, float ev,
		float *x, float *y);
void bearingEstimator(float *az, float *ev, float *az_t0, float *elv_t0,
		complex_float* sub_pulse, int Npulse, complex_float* sub_pulse_tran,
		uint32_t signal_freq, int *delay_time, int Ndelay, complex_float *c_out, struct Hydro_info hy);
void cmatmlt(complex_float* output, complex_float* in1, complex_float* in2,
		int row1, int col1, int col2);
float getData(float* v1, float* v2, float* v3, float* v4, char name[20], int N);

float powerGain(float pavr);
float gain(float* v1,float* v2,float* v3,float* v4,int N);
//int pulse_detect2(complex_float*in1,complex_float*in2,complex_float*in3,complex_float*in4
//				,complex_float*out,int N,int Ns,float* pavr);
void lstsqrx(const float *x,const float *y, float *out);
int PID_gain(float Psig,float Pnoise);
int detect(complex_float*in1,complex_float*in2,complex_float*in3,complex_float*in4
				,complex_float*out,int N,int Ns,int* G);
				void Power(complex_float*in1,complex_float*in2,complex_float*in3,complex_float*in4
				,complex_float*out,int N);

void power_output(float*in1, float*in2, float*in3, float*in4, float* out_pwr, int N);
int error_cut(float*in1, float*in2, float*in3, float*in4);
