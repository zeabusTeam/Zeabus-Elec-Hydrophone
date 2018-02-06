/*
 * Author : Anol Paisal
 * Company : EmOne (Thailand) Co.,Ltd.
 * Email : anolpaisal@gmail.com
 * Copyright @ 2015
 * Maintainer : Tita
 */

struct Signal;
struct Channel;

struct Signal{
	int ts;			
	int tp;			
	int fo;
	int vp; 
	int period; 
	int ob; 
	int fs;
} Signal;

struct Channel{
	float azi;
	float elv;
	int size;
	float fs;
	float Np;  		//num_path
	float noise;  	//power
	float power;	//path power
	float* x;
	float* y;
}Channel;

struct Hydro_info{
	float* x;  	//[4]
 	float* y;	//[4]
 	float* phase_err;	//[4*4]
 	float* lstsqr;		//[3*4]
};

struct Temp{
	float* w1;	float* w2;	float* w3;	float* w4;
	float* x1;	float* x2;	float* x3;	float* x4;
	float* y1;	float* y2;	float* y3;	float* y4;
	float* z1;	float* z2;	float* z3;	float* z4;
};
