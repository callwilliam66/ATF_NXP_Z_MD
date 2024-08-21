
////*****************************************////
//  Name : motorDrive_stepCmd.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "motorDrive.h" 

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
float32 mDrv_stepCmd(float32 fCmdIn, uint32* ulStepCnt, uint32 ulStepCntMax)
{
	if(ulStepCntMax == 0)
	{
		return fCmdIn;
	}

	float32 fData;

	if(*ulStepCnt < (ulStepCntMax >> 1))
	{
		fData = fCmdIn;

	}
	else
	{
		fData = fCmdIn;

	}

	*ulStepCnt = *ulStepCnt + 1;

	if(*ulStepCnt >= ulStepCntMax)
	{
		*ulStepCnt = 0;
	}

	return fData;
}
