////*****************************************////
//  Name : motorDrive_ILoop.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "motorDrive.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mDrv_loopVoltage(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs)
{
	if(mDrvRegs->i_ctrlflag == 0) return;
	if(mDrvRegs->servoState == SERVO_STATE_OFF) return;
	if(mDrvRegs->alarmFlag == true) return;

//	 voltage dq
	mDataRegs->fVd = mDrvRegs->fIdOut;
	mDataRegs->fVq = mDrvRegs->fIqOut;

//	 inverse park
	mDrvRegs->iParkRegs.fD = mDataRegs->fVd;
	mDrvRegs->iParkRegs.fQ = mDataRegs->fVq;

	mDrvRegs->iParkRegs.fTheta = mDrvRegs->parkRegs.fTheta;

	iPark_theta(&mDrvRegs->iParkRegs);

	// voltage alpha beta
	mDataRegs->fValpha = mDrvRegs->iParkRegs.fAlpha;
	mDataRegs->fVbeta = mDrvRegs->iParkRegs.fBeta;

	// inverse clarke
	mDrvRegs->iClarkeRegs.fAlpha = mDataRegs->fValpha;
	mDrvRegs->iClarkeRegs.fBeta = mDataRegs->fVbeta;

	iClarke(&mDrvRegs->iClarkeRegs);

	// voltage uvw
	mDataRegs->fVu = mDrvRegs->iClarkeRegs.fU;
	mDataRegs->fVv = mDrvRegs->iClarkeRegs.fV;
	mDataRegs->fVw = mDrvRegs->iClarkeRegs.fW;

	// svpwm
	mDrvRegs->svmRegs.fU = mDataRegs->fVu;
	mDrvRegs->svmRegs.fV = mDataRegs->fVv;
	mDrvRegs->svmRegs.fW = mDataRegs->fVw;

	svm(&mDrvRegs->svmRegs);

	// duty ta tb tc
	mDataRegs->fTa = (mDrvRegs->svmRegs.fA * 0.5F) + 0.5F;
	mDataRegs->fTb = (mDrvRegs->svmRegs.fB * 0.5F) + 0.5F;
	mDataRegs->fTc = (mDrvRegs->svmRegs.fC * 0.5F) + 0.5F;

}
