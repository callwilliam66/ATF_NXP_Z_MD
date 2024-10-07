/*
 * motorControl_curve.h
 *
 *  Created on: Sep 5, 2022
 *      Author: williamhsu
 */

#ifndef API_API_MOTORCONTROL_MOTORCONTROL_CURVE_H_
#define API_API_MOTORCONTROL_MOTORCONTROL_CURVE_H_


#include "api.h"


typedef struct
{
	//time-parameter
	uint32 ultacc;
	uint32 ultdec;
	uint32 ultmid;
	uint32 ultcc;
	uint32 ultime;
	//motion-parameter

	float32 fVmax;
	float32 fVinit;
	float32 lVinit;

	float32 fVend;
	float32 fAacc;
	float32 fAdec;

	int32 ldistance;
	uint32 uldistance;

	int32 lpcmd;
	float32 fAcmd;
	float32 fVcmd;
	float32 fPcmd;

	//control-parameter
	float32 fsqrtNum;
	float32 fsm;

	uint32 ulStartPcmd;
	uint32 ulcurveType;
	uint32 ultcurve_enable;

	uint32 ulfirsthome;
	//log-parameter

	float32 flogVinit;
	float32 flogPcmd;
}TCURVE_REGS;

#define 	TCURVETYPE        			0
#define 	DELTACURVETYPE        		1

extern void mCtrl_Tcurve_Setting(TCURVE_REGS *tcurveRegs,int32 lpcmd);
extern void mCtrl_Tcurve_Calc(TCURVE_REGS *tcurveRegs);
extern void mCtrl_Tcurve_Clear(TCURVE_REGS *tcurveRegs);
extern void mCtrl_Tcurve_Init(TCURVE_REGS *tcurveRegs);
extern void mCtrl_Tcurve_parameterUpdate(TCURVE_REGS *tcurveRegs);

#endif /* API_API_MOTORCONTROL_MOTORCONTROL_CURVE_H_ */
