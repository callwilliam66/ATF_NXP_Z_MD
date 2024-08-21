////*****************************************////
//  Name : lib_filter_ext.h
//  Data : 2020/10
//  Version : 0.0
////*****************************************////

#ifndef _LIB_FILTER_EXT_H_
#define _LIB_FILTER_EXT_H_

#include "lib.h"

typedef struct
{
	float32 fDataIn;
	float32 fAlpha;
	float32 fDataOut;
	float32 fDataIn1;
	float32 fDataOut1;
}LOW_PASS_FILTER_REGS;

typedef struct {
	float32 falpha;
	float32 fbeta;
	float32 fcenter_freq;
	float32 fnotchwidth_freq;
	float32 fsample_rate;

	//Input
	float32 x[3];
	//Output
	float32 y[3];

	float32 fDataOut;
	float32 fDataIn;
}NOTCHFILTER;
// extern function

extern void lib_filter_init(LOW_PASS_FILTER_REGS* lowPassFilterRegs);
extern void lowPassFilter_config(LOW_PASS_FILTER_REGS* lowPassFilterRegs, float32 fcutoff,float32 fsample);
extern void lowPassFilter(LOW_PASS_FILTER_REGS *lowPassFilterRegs,uint32 enable);

extern void NotchFilter_Init(NOTCHFILTER * filter);
extern void Notchfiter_update(NOTCHFILTER* filter,uint32 enable);
#endif // end of file
