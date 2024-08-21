////*****************************************////
//  Name : motorDrive_loopCtrl.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "motorDrive.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mDrv_loopCtrl(void)
{
	mDrvRegs.ulP_ctrlCnt++;
	mDrvRegs.ulV_ctrlCnt++;
	mDrvRegs.ulI_ctrlCnt++;

	if(mDrvRegs.ulP_ctrlCnt >= mDrvRegs.ulP_ctrlCntMax)
	{
		mDrvRegs.ulP_ctrlCnt = 0;
		mDrvRegs.p_ctrlflag = 1; // rise loop flag
	}

	if(mDrvRegs.ulV_ctrlCnt >= mDrvRegs.ulV_ctrlCntMax)
	{
		mDrvRegs.ulV_ctrlCnt = 0;
		mDrvRegs.v_ctrlflag = 1; // rise loop flag
	}

	if(mDrvRegs.ulI_ctrlCnt >= mDrvRegs.ulI_ctrlCntMax)
	{
		mDrvRegs.ulI_ctrlCnt = 0;
		mDrvRegs.i_ctrlflag = 1; // rise loop flag
	}
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mDrv_loopClear(void)
{
	mDrvRegs.p_ctrlflag = 0;
	mDrvRegs.v_ctrlflag = 0;
	mDrvRegs.i_ctrlflag = 0;
}
