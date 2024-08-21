////*****************************************////
//  Name : motorControl_emg.h
//  Data : 2021/07
//  Version : 0.0
////*****************************************////

#ifndef _MOTORCONTROL_EMG_H_
#define _MOTORCONTROL_EMG_H_

#include "api.h"

typedef struct
{
	uint32 	ulPcmdIn;
	uint32 	ulPcmdOut;
	uint32  ulEmgState;
	uint32  ulEmgStateIO;
	uint32  ulEmgStateSW;
}EMG_REGS;

extern void mCtrl_emg(void);

#endif // end of file
