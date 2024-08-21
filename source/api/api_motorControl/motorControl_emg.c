////*****************************************////
//  Name : motorControl_emg.c
//  Data : 2021/07
//  Version : 0.0
////*****************************************////

#include "motorControl.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif

void mCtrl_emg(void)
{
	//data
	mCtrlRegs.emgRegs.ulEmgState = mCtrlRegs.emgRegs.ulEmgStateIO | mCtrlRegs.cmdRegs.data.emg | mCtrlRegs.emgRegs.ulEmgStateSW;
	mCtrlRegs.emgRegs.ulEmgState = mCtrlRegs.cmdRegs.data.emg;
	   //normal
	if(mCtrlRegs.emgRegs.ulEmgState == 0)
	{
		mCtrlRegs.emgRegs.ulPcmdOut = mCtrlRegs.emgRegs.ulPcmdIn;
		return;
	}
	//EMG
	if(mCtrlRegs.emgRegs.ulEmgState == 1)
	{
		mCtrlRegs.ulPcmd = mCtrlRegs.ulPfbk;
		mCtrlRegs.emgRegs.ulPcmdOut = mCtrlRegs.ulPfbk;
		mCtrlRegs.ulPcmdPulse = mCtrlRegs.emgRegs.ulPcmdOut;
		mCtrlRegs.ulPcmdUart = mCtrlRegs.emgRegs.ulPcmdOut;

		// home finding clear
		mCtrl_homeFindingClear(&mCtrlRegs);

		return;
	}
}
