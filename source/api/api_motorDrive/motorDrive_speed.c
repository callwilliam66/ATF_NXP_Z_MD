////*****************************************////
//  Name : motorDrive_speed.c
//  Data : 2020/10
//  Version : 0.0
////*****************************************////

#include "motorDrive.h"

void speed_init(SPEED_REGS *speedRegs)
{
	speedRegs->uiDataNew = 0;
	speedRegs->uiDataOld = 0;
	speedRegs->lDataDiff = 0;
	speedRegs->ulTimeCnt = 0;
	speedRegs->fFreq = 0;
	speedRegs->fMaxDataRev = 0;
	speedRegs->fMaxSpeed_RPM = 0;
	speedRegs->fScale = 0;
	speedRegs->fSpeed = 0;
	speedRegs->fSpeed_RPM = 0;
}

void speed_scaleUpdate(SPEED_REGS *speedRegs, float32 fFreq, float32 fMaxDataRev, float32 fMaxSpeed_RPM)
{
	speedRegs->fFreq = fFreq;
	speedRegs->fMaxDataRev = fMaxDataRev;
	speedRegs->fMaxSpeed_RPM = fMaxSpeed_RPM;
	speedRegs->fScale = 60.0F * speedRegs->fFreq / speedRegs->fMaxDataRev;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void speed(SPEED_REGS *speedRegs)
{

	speedRegs->lDataDiff = speedRegs->uiDataNew - speedRegs->uiDataOld;

	speedRegs->uiDataOld = speedRegs->uiDataNew;

	speedRegs->fSpeed_RPM = (float32)speedRegs->lDataDiff * speedRegs->fScale;




//	if(speedRegs->lDataDiff == 0)
//	{
//		if(speedRegs->ulTimeCnt < 10000) // speed resolution 0.0001
//		{
//			speedRegs->ulTimeCnt++;
//		}
//
//		speedRegs->fSpeed_RPM =  speedRegs->fScale /speedRegs->ulTimeCnt;
//	}
//	else
//	{
//
//		speedRegs->ulTimeCnt = 0;
//	}

	speedRegs->fSpeed = speedRegs->fSpeed_RPM / speedRegs->fMaxSpeed_RPM;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void speed_reset(SPEED_REGS *speedRegs, uint32 ulResetData)
{
	speedRegs->uiDataNew = ulResetData;
	speedRegs->uiDataOld = ulResetData;
	speedRegs->lDataDiff = 0;
	speedRegs->ulTimeCnt = 0;
	speedRegs->fSpeed = 0.0F;
	speedRegs->fSpeed_RPM = 0.0F;
}
