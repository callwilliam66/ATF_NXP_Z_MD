////*****************************************////
//  Name : motorDrive_VLoop.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "motorDrive.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mDrv_loopSpeed(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs)
{
	if(mDrvRegs->v_ctrlflag == 0) return;
	if(mDrvRegs->servoState == SERVO_STATE_OFF) return;
	if(mDrvRegs->alarmFlag == true) return;
	if(mDrvRegs->ctrlMode > MOTOR_CTRL_MODE_V) return;

	// speed command
	switch(mDrvRegs->ctrlMode)
	{
		case MOTOR_CTRL_MODE_P :
			mDrvRegs->fVCmd = mDrvRegs->fPOut;
		break;
		case MOTOR_CTRL_MODE_V :
			if(mDrvRegs->ulAngleCloseFlag == true  )
			{

				mDrvRegs->fVCmdStep = mDrv_stepCmd(mDrvRegs->fVCmdPara, &mDrvRegs->ulVCmdStepTime, mDrvRegs->ulVCmdStepTimeMax);

				mDrvRegs->speedAccDecRegs.fDataIn = mDrvRegs->fVCmdStep;

				accDec(&mDrvRegs->speedAccDecRegs);

				mDrvRegs->fVCmd = mDrvRegs->speedAccDecRegs.fDataOut;
				//mDrvRegs->fVCmd = 0.4;
			}
		break;
		default :
			mDrvRegs->fVCmd = mDrvRegs->fPOut;
		break;
	}
	mDrvRegs->V_piRegs.fRef = mDrvRegs->fVCmd;
	mDrvRegs->V_piRegs.fFbk = mDataRegs->fV;
	if(para_valueGet_macro(PARA_ADVCTRL1_ENABLE) == 0)
	{
		//pi_advctrl_vloop(&mDrvRegs->V_piRegs);
		pi_feed_forward(&mDrvRegs->V_piRegs);
	}
	else
	{
		pi_vloop_gainset(&mDrvRegs->V_piRegs);
		pi_advctrl_vloop(&mDrvRegs->V_piRegs);

	}
	mDrvRegs->fVOut = mDrvRegs->V_piRegs.fOut;
}
