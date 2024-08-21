////*****************************************////
//  Name : motorDrive_ILoop.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "motorDrive.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mDrv_loopCurrent(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs)
{
	if(mDrvRegs->i_ctrlflag == 0) return;

	// clarke
	mDrvRegs->clarkeRegs.fU = mDataRegs->fIu;
	mDrvRegs->clarkeRegs.fV = mDataRegs->fIv;
	mDrvRegs->clarkeRegs.fW = mDataRegs->fIw;

	clarke(&mDrvRegs->clarkeRegs);

	// current alpha beta
	mDataRegs->fIalpha = mDrvRegs->clarkeRegs.fAlpha;
	mDataRegs->fIbeta = mDrvRegs->clarkeRegs.fBeta;

	// park
	mDrvRegs->parkRegs.fAlpha = mDataRegs->fIalpha;
	mDrvRegs->parkRegs.fBeta = mDataRegs->fIbeta;


	if(mDrvRegs->ulAngleCloseFlag == true)
	{

		if(mCtrlRegs.statusRegs.data.homeFinding == 0 && mCtrlRegs.statusRegs.data.homeFinded == 0)
		{
			mDrvRegs->parkRegs.fTheta = mDrvRegs->parkRegs.fTheta ;
		}else
		{
			mDrvRegs->parkRegs.fTheta = mDrv_loopCurrent_advCtrl_AngleHold(para_valueGet_macro(PARA_ADVCTRL1_ENABLE), mDrvRegs, mDataRegs);
		}


	}
	else
	{
		mDrvRegs->parkRegs.fTheta = mDataRegs->fAngleVirtual;
	}

	park_theta(&mDrvRegs->parkRegs);

	// current dq
	mDataRegs->fId = mDrvRegs->parkRegs.fD;
	mDataRegs->fIq = mDrvRegs->parkRegs.fQ;

	if(mDrvRegs->servoState == SERVO_STATE_OFF) return;
	if(mDrvRegs->alarmFlag == true) return;

	// current command
	switch(mDrvRegs->ctrlMode)
	{
		case MOTOR_CTRL_MODE_P:
			if(mDrvRegs->ulAngleCloseFlag == true)
			{
				if(mCtrl_status_homeFindedGet_macro() == 1)
				{
					if(para_valueGet_macro(PARA_ADVCTRL2_ENABLE) == 1)
					{
						//mDrvRegs->idfWRegs.fSpeedCmd = mDrvRegs->fVCmd;
						//mDrv_loopCurrent_advCtrl_IdFWcalc(para_valueGet_macro(PARA_ADVCTRL2_ENABLE), &mDrvRegs->idfWRegs);
						//mDrvRegs->fIdCmd = mDrvRegs->idfWRegs.fIdFWCmd;
						mDrvRegs->fIdCmd = -0.04;
					}
					else
					{
						mDrvRegs->fIdCmd = mDrvRegs->fIdCmdHoldingPara;
					}

				}
				else
				{
					mDrvRegs->fIdCmd = mDrvRegs->fIdCmdHoldingPara;
				}


				mDrvRegs->fIqCmd = mDrvRegs->fVOut;

				if(mDrvRegs->startUpRegs.ulFirstCloselooptcnt<24000)
				{
					mDrvRegs->startUpRegs.ulFirstCloselooptcnt++;

				}else
				{
					if(mDrvRegs->startUpRegs.ulFirstCloseloopflag == 0)
					{
						if( math_abs_macro(mDataRegs->fIq)>mDrvRegs->fIqThreshold)
						{
							mDrvRegs->alarmCode.data.servoerror = 1;
						}
					}

					mDrvRegs->startUpRegs.ulFirstCloseloopflag = 1;
				}

			}
			else
			{
				mDrvRegs->fIdCmd = mDrvRegs->fIdCmdPara;

				mDrvRegs->fIqCmd = 0.0F;
			}
			break;
		case MOTOR_CTRL_MODE_V:
			if(mDrvRegs->ulAngleCloseFlag == true)
			{
				mDrvRegs->fIdCmd = 0.0F;
				mDrvRegs->fIqCmd = mDrvRegs->fVOut;
			}
			else
			{
				mDrvRegs->fIdCmd = mDrvRegs->fIdCmdPara;
				mDrvRegs->fIqCmd = 0.0F;
			}
		break;
		case MOTOR_CTRL_MODE_CURRENT_CLOSE_ANGLE_OPEN:
			mDrvRegs->fIdCmd = mDrvRegs->fIdCmdPara;
			mDrvRegs->fIqCmd = mDrvRegs->fIqCmdPara;
		break;
		case MOTOR_CTRL_MODE_CURRENT_CLOSE_ANGLE_OPEN_STEP:
			mDrvRegs->fIdCmd = mDrv_stepCmd(mDrvRegs->fIdCmdPara, &mDrvRegs->ulIdCmdStepTime, mDrvRegs->ulIdCmdStepTimeMax);
			mDrvRegs->fIqCmd = mDrv_stepCmd(mDrvRegs->fIqCmdPara, &mDrvRegs->ulIqCmdStepTime, mDrvRegs->ulIqCmdStepTimeMax);
		break;
		case MOTOR_CTRL_MODE_CURRENT_OPEN_ANGLE_OPEN_STEP:
			mDrvRegs->fIdCmd = mDrv_stepCmd(mDrvRegs->fIdCmdPara, &mDrvRegs->ulIdCmdStepTime, mDrvRegs->ulIdCmdStepTimeMax);
			mDrvRegs->fIqCmd = mDrv_stepCmd(mDrvRegs->fIqCmdPara, &mDrvRegs->ulIqCmdStepTime, mDrvRegs->ulIqCmdStepTimeMax);
		break;
		default :
			mDrvRegs->fIdCmd = 0.0F;
			mDrvRegs->fIqCmd = mDrvRegs->fVOut;
		break;
	}

	// pi reference
	mDrvRegs->Id_piRegs.fRef = mDrvRegs->fIdCmd;
	mDrvRegs->Iq_piRegs.fRef = mDrvRegs->fIqCmd;

	// pi feedback
	mDrvRegs->fIdfbk = mDataRegs->fId;
	mDrvRegs->fIqfbk = mDataRegs->fIq;

	if(mDrvRegs->ctrlMode == MOTOR_CTRL_MODE_CURRENT_OPEN_ANGLE_OPEN_STEP)
	{
		mDrvRegs->Id_piRegs.fFbk = 0;
		mDrvRegs->Iq_piRegs.fFbk = 0;
	}
	else
	{
		mDrvRegs->Id_piRegs.fFbk = mDrvRegs->fIdfbk;
		mDrvRegs->Iq_piRegs.fFbk = mDrvRegs->fIqfbk;
	}

	// pi
	pi(&mDrvRegs->Iq_piRegs);
	pi(&mDrvRegs->Id_piRegs);

	mDrvRegs->fIqOut = mDrvRegs->Iq_piRegs.fOut;
	mDrvRegs->fIdOut = mDrvRegs->Id_piRegs.fOut;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
float32 mDrv_loopCurrent_advCtrl_AngleHold(uint32 enable, MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs)
{
	if(enable == 0)
	{
		mDrvRegs->parkRegs.fTheta = mDataRegs->fAngleElec;
		return mDrvRegs->parkRegs.fTheta;
	}

	float32 fDataOutC;

	fDataOutC = mDataRegs->fAngleElec;

	if(mCtrl_status_homeFindedGet_macro() == 1)
	{
		if(mCtrl_ulCmdRenewFlagGet_macro() == 0)
		{
			fDataOutC = mDataRegs->fAngleElec;
		}
		else
		{
			// in the range of in position and renew flag rise => angle hold
			fDataOutC = mDrvRegs->parkRegs.fTheta;
		}
	}

	mDrvRegs->parkRegs.fTheta = fDataOutC;
	return mDrvRegs->parkRegs.fTheta;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mDrv_loopCurrent_advCtrl_IdFWcalc(uint32 enable, IDFW_REGS  *IDFWRegs)
{

	float32 Speedcmd_abs;
	float32 m1 , b1;

	if(enable == 0)
	{
		IDFWRegs->fIdFWCmd  = 0.0F;
		return;
	}
	if(mDrvRegs.fVCmdPara != IDFWRegs->fSpeedCmdBoundary)
	{

		m1 =(-IDFWRegs->fIdFWCmdMax)/(mDrvRegs.fVCmdPara-IDFWRegs->fSpeedCmdBoundary);
		b1 = -m1*IDFWRegs->fSpeedCmdBoundary;
	}else
	{
		IDFWRegs->fIdFWCmd = 0.0;
		return;
	}

	Speedcmd_abs =  math_abs_macro(IDFWRegs->fSpeedCmd);

	if(Speedcmd_abs<IDFWRegs->fSpeedCmdBoundary)//0.16667
	{
		IDFWRegs->fIdFWCmd = 0.0;
	}else
	{
		IDFWRegs->fIdFWCmd = m1*Speedcmd_abs+b1;

	}
	if(IDFWRegs->fIdFWCmd<(-IDFWRegs->fIdFWCmdMax) )//-0.08
		IDFWRegs->fIdFWCmd = -IDFWRegs->fIdFWCmdMax ;

}





