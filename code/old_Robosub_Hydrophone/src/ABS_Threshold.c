/*****************************************************************************
 * ABS_Threshold.c
 * Author : Anol Paisal
 * Company : EmOne (Thailand) Co.,Ltd.
 * Email : anolpaisal@gmail.com
 * Copyright @ 2015
 *****************************************************************************/

/* Include the header file that declares "myFunction()" */
#include <builtins.h>
#include <math.h>

#include "ABS_Threshold.h"
#include "common.h"

/**
 * This file contains the definition of the function "myFunction()". To
 * begin developing your library, it is strongly recommended that you
 * rename the declared function from "myFunction()" to something more
 * meaningful for your purposes. Then begin adding your code library code
 * where instructed. 
 */
bool ABS_Threshold( float *H1,  float *H2,  float *H3, float *H4,int index,float thres, uint_fast8_t* status)
{
#if 0
	int i;
	float sum = 0;
//	for (i = 0; i < len; ++i) {
//		//sum = fabsf(data[i]);
//		sum = data[i];
//		if(sum > thes)
//			return 1;
//	}
	//For debug
	i = idx % 2000;
	if (i == 1) {
		return true;
	}
#else
//	unsigned int old_idx;
	float tmp[4],power[4];
	int i,k;
	int num_samples = 50;
	float min_power = 0.01 ;
	int_fast8_t ch_status = *status;

	ch_status &=~ (BIT_3 | BIT_2 | BIT_1 | BIT_0);

//	if (idx == 0) {
//		old_idx = AUDIO_REQUIRED_SAMPLES;
//	} else {
//		old_idx = idx - 1;
//	}
	power[0] = H1[index]*H1[index];
	power[1] = H2[index]*H2[index];
	power[2] = H3[index]*H3[index];
	power[3] = H4[index]*H4[index];
	if ((power[0]>min_power ) && (power[1]>min_power ) && (power[2]>min_power ) && (power[3]>min_power )) {
		tmp[0] = 0;
		tmp[1] = 0;
		tmp[2] = 0;
		tmp[3] = 0;
		
		for (i = 1; i<=num_samples ; i++){
			k = index - i;
			if (k < 0 )
				k = AUDIO_REQUIRED_SAMPLES +k;
			tmp[0] += H1[k]*H1[k];
			tmp[1] += (*(H2+k))*(*(H2+k));
			tmp[2] += H3[k]*H3[k];
			tmp[3] += (*(H4+k))*(*(H4+k));
			
		}
		
		/*tmp[0] = fabsf(H1);
		tmp[1] = fabsf(H2);
		tmp[2] = fabsf(H3);
		tmp[3] = fabsf(H4);
		*/
		tmp[0] = tmp[0]/num_samples ;
		tmp[1] = tmp[1]/num_samples ;
		tmp[2] = tmp[2]/num_samples ;
		tmp[3] = tmp[3]/num_samples ;
		if (tmp[0] < thres*power[0]) {
			ch_status |= BIT_0;
		}
		if (tmp[1] < thres*power[1]) {
			ch_status |= BIT_1;
		}
		if (tmp[2] < thres*power[2]) {
			ch_status |= BIT_2;
		}
		if (tmp[3] < thres*power[3]) {
			ch_status |= BIT_3;
		}

	//	__builtin_memcpyPD( (void *) output.power, (void *) tmp, sizeof(tmp));

		*status = ch_status;
		if (ch_status & CH_MASK) {
			return true;
		}
	}

#endif
	return false;
}

