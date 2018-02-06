/*
 * helper.c
 *
 *  Created on: Jan 26, 2015
 *	Author : Anol Paisal
 * 	Company : EmOne (Thailand) Co.,Ltd.
 * 	Email : anolpaisal@gmail.com
 * 	Copyright @ 2015
 */

#include "common.h"

/*******************************************************************
 *   Function:    Delay
 *   Description: executes a specified number of nops
 *******************************************************************/
void Delay(const int n) {
	int nDelay;
	for (nDelay = 0; nDelay < n; nDelay++) {
		NOP;
	}
}

void Block_Fixed_To_Float(int * Fixed_In, float * Float_Out_L,
		float * Float_Out_R) {
	float f = ((float) (*Fixed_In << 8)) * (1.0 / FLOAT_COFF);
	*Float_Out_L = f;
	*Float_Out_R = f;
}

void Block_Float_To_Fixed(int * Fixed_Out, float * Float_In_L,
		float * Float_In_R) {
	Fixed_Out[0] = ((int) (FLOAT_COFF * *Float_In_L)) >> 8;
	Fixed_Out[1] = ((int) (FLOAT_COFF * *Float_In_R)) >> 8;
}

//=============================================================================
//=  Compute Internet Checksum for count bytes beginning at location addr     =
//=============================================================================
word16 checksum(byte *addr, word32 count) {
	register word32 sum = 0;
	word16 * tmp = (word16 *) addr;
	// Main summing loop
	while (count > 1) {
		sum += *tmp;
		tmp++;
		count = count - 2;
	}

	// Add left-over byte, if any
	if (count > 0)
		sum += *addr;

	// Fold 32-bit sum to 16 bits
	while (sum >> 16)
		sum = (sum & 0xFFFF) + (sum >> 16);

	return (~sum);
}
