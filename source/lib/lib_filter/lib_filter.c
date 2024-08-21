////*****************************************////
//  Name : lib_filter.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "lib_filter.h"

void lib_filter_init(LOW_PASS_FILTER_REGS* lowPassFilterRegs)
{

}
/*
 *
 * G(f) = (1-alpha)/(sqrt( (1+a*a) - 2 * a *cos(2*pi* f/fs))
 * set f = cutoff frequency , and set alpha to get g(f)  =  0.5  (3db frequency)
 *
 * */
void lowPassFilter_config(LOW_PASS_FILTER_REGS* lowPassFilterRegs, float32 fcutoff,float32 fsample)
{
	lowPassFilterRegs->fDataOut = 0;
	lowPassFilterRegs->fDataOut1 = 0;

	if( fcutoff >=0.5*fsample || fcutoff <=0.0)
	{
		lowPassFilterRegs->fAlpha = 0.0f;
		return;
	}

	lowPassFilterRegs->fAlpha = (fsample - MATH_PI * fcutoff)/(fsample + MATH_PI * fcutoff);


}
void lowPassFilter(LOW_PASS_FILTER_REGS* lowPassFilterRegs,uint32 enable)
{
	if(enable == 0)
	{
		lowPassFilterRegs->fDataOut = lowPassFilterRegs->fDataIn;
		lowPassFilterRegs->fDataOut1 = lowPassFilterRegs->fDataIn1;
		return;
	}

	lowPassFilterRegs->fDataOut = (1-lowPassFilterRegs->fAlpha) * lowPassFilterRegs->fDataIn + lowPassFilterRegs->fAlpha * lowPassFilterRegs->fDataOut;
	lowPassFilterRegs->fDataOut1 = (1-lowPassFilterRegs->fAlpha) * lowPassFilterRegs->fDataIn1 + lowPassFilterRegs->fAlpha * lowPassFilterRegs->fDataOut1;

}

/*Notch filter*/
void NotchFilter_Init(NOTCHFILTER * filter)
{
	/*convert to angular frequency*/
	float32 fwcenter_rps = 2.0f * MATH_PI * filter->fcenter_freq;
	float32 fwwidth_rps = 2.0f * MATH_PI * filter->fnotchwidth_freq;

	/*pre-warp center frequency    w* = 2tan(wT/2)/T    */
	float32  fwstar = 2.0f * filter->fsample_rate * tanf(0.5f * fwcenter_rps /filter->fsample_rate);

	/*conpute filter coefficients*/
	filter->falpha = 4.0f + fwstar * fwstar / filter->fsample_rate / filter->fsample_rate;
	filter->fbeta = 2.0f * fwwidth_rps / filter->fsample_rate;

	for (int32 i = 0; i < 3; i++)
	{
		filter->x[i] = 0;
		filter->y[i] = 0;
	}
}

void Notchfiter_update(NOTCHFILTER* filter,uint32 enable)
{
	if(enable == 0 )
	{
		filter->fDataOut = filter->fDataIn;
		return;
	}


	/*shift sample*/
	filter->x[2] = filter->x[1];
	filter->x[1] = filter->x[0];

	filter->y[2] = filter->y[1];
	filter->y[1] = filter->y[0];

	/*store new input samples*/
	filter->x[0] = filter->fDataIn;
	filter->y[0] = ( filter->falpha * filter->x[0] + 2.0f * (filter->falpha-8.0f) * filter->x[1] + filter->falpha \
		* filter->x[2] - 2.0f* (filter->falpha - 8.0f) * filter->y[1] -  (filter->falpha - filter->fbeta) \
		* filter->y[2])/ (filter->falpha + filter->fbeta);

	filter->fDataOut = filter->y[0];
}
