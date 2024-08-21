////*****************************************////
//  Name : motorDrive_PLoop.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "motorDrive.h"
#include "main.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mDrv_loopPosition(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs)
{
	if(mDrvRegs->p_ctrlflag == 0) return;
	if(mDrvRegs->servoState == SERVO_STATE_OFF) return;
	if(mDrvRegs->alarmFlag == true) return;
	if(mDrvRegs->ctrlMode >= MOTOR_CTRL_MODE_V) return;


	int32 offset_value = 0;
	static float32 fvibrationAngle = 0.0;
	static float32 fvibrationFrequency = 0.0;
	static uint32 ultime = 0;

	// position command
	switch(mDrvRegs->ctrlMode)
	{
		case MOTOR_CTRL_MODE_P :
			mDrvRegs->ulPCmd = mDrvRegs->ulPCmdCtrlr;
		break;
		case MOTOR_CTRL_MODE_P_TEST :
			mDrvRegs->ulPCmd = mDrvRegs->ulPCmdPara;
		break;
		default :
			mDrvRegs->ulPCmd = mDrvRegs->ulPCmdCtrlr;
		break;
	}

	if(para_valueGet_macro(PARA_ADVCTRL4_ENABLE) == 1)
	{
		fvibrationFrequency = 0.008;
		fvibrationAngle += fvibrationFrequency;

		if(fvibrationAngle >= 1)
			fvibrationAngle = fvibrationAngle - 1;

		offset_value = para_valueGet_macro(PARA_ADVCTRL4_PARA0) * sinf( fvibrationAngle * MATH_TWO_PI);
		ultime++;

	}else
	{
		offset_value =  0;
	}

	mDrvRegs->ulPCmd  = mDrvRegs->ulPCmd + offset_value;

	mDrvRegs->ulPCmdOut = mDrv_loopPosition_advCtrl_commandSmooth(para_valueGet_macro(PARA_ADVCTRL0_ENABLE), para_valueGet_macro(PARA_ADVCTRL0_PARA0), mDrvRegs);
	mDrvRegs->ulPFbk =  mCtrlRegs.ulPfbk ; // mCtrlRegs.ulPfbk

	// position control

	mDrvRegs->P_pRegs.ulRef = mDrvRegs->ulPCmdOut - mDrvRegs->ulPCmdServoOff;
	mDrvRegs->P_pRegs.ulFbk = mDrvRegs->ulPFbk - mDrvRegs->ulPFbkServoOff;
	mDrvRegs->P_pRegs.lErr = mDrvRegs->P_pRegs.ulRef - mDrvRegs->P_pRegs.ulFbk;

	p_fixPoint(&mDrvRegs->P_pRegs);

	mDrvRegs->fPOut = mDrv_loopPosition_advCtrl_positionOutputZero(para_valueGet_macro(PARA_ADVCTRL1_ENABLE), mDrvRegs);
	if(mCtrlRegs.statusRegs.data.homeFinding == 0 && mCtrlRegs.statusRegs.data.homeFinded == 0)
		mDrvRegs->fPOut = 0.0;

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
float32 mDrv_loopPosition_advCtrl_positionOutputZero(uint32 enable, MOTORDRIVE_REGS *mDrvRegs)
{
	if(enable == 0)
	{
		mDrvRegs->fPOut = mDrvRegs->P_pRegs.fOut;
		return mDrvRegs->fPOut;
	}

	float32 fDataOutP;

	fDataOutP = 1.0F;

	if(mCtrl_status_homeFindedGet_macro() == 1)
	{
		if(mCtrl_ulCmdRenewFlagGet_macro() == 0)
		{
			fDataOutP = 1.0F;
		}
		else
		{
			// in the range of in position and renew flag rise => position output zero
			fDataOutP = 0.0F;
		}
	}

	mDrvRegs->fPOut = mDrvRegs->P_pRegs.fOut * fDataOutP;
	return mDrvRegs->fPOut;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
uint32 mDrv_loopPosition_advCtrl_commandSmooth(uint32 enable,uint32 para0, MOTORDRIVE_REGS *mDrvRegs)
{
	if(enable == 0)
	{
		mDrvRegs->ulPCmdOut = mDrvRegs->ulPCmd;
		mDrvRegs->ulPCmdOld = mDrvRegs->ulPCmd;
		return mDrvRegs->ulPCmdOut;
	}

	if(mDrvRegs->ulPCmd != mDrvRegs->ulPCmdOld)
	{
		mDrvRegs->lPCmdUnit = ((int32)mDrvRegs->ulPCmd - (int32)mDrvRegs->ulPCmdOut) / para0;
		mDrvRegs->lPCmdFirst = ((int32)mDrvRegs->ulPCmd - (int32)mDrvRegs->ulPCmdOut) % para0;

		mDrvRegs->ulPCmdOut = mDrvRegs->ulPCmdOut + mDrvRegs->lPCmdUnit;

		if(mDrvRegs->lPCmdFirst > 0)
		{
			mDrvRegs->ulPCmdOut = mDrvRegs->ulPCmdOut + 1;
			mDrvRegs->lPCmdFirst--;
		}
		else if(mDrvRegs->lPCmdFirst < 0)
		{
			mDrvRegs->ulPCmdOut = mDrvRegs->ulPCmdOut - 1;
			mDrvRegs->lPCmdFirst++;
		}
	}
	else
	{
		if(mDrvRegs->ulPCmdOut != mDrvRegs->ulPCmd)
		{
			mDrvRegs->ulPCmdOut = mDrvRegs->ulPCmdOut + mDrvRegs->lPCmdUnit;

			if(mDrvRegs->lPCmdFirst > 0)
			{
				mDrvRegs->ulPCmdOut = mDrvRegs->ulPCmdOut + 1;
				mDrvRegs->lPCmdFirst--;
			}
			else if(mDrvRegs->lPCmdFirst < 0)
			{
				mDrvRegs->ulPCmdOut = mDrvRegs->ulPCmdOut - 1;
				mDrvRegs->lPCmdFirst++;
			}

			if(mDrvRegs->lPCmdUnit > 0)
			{
				if((int32)mDrvRegs->ulPCmd < (int32)mDrvRegs->ulPCmdOut)
				{
					mDrvRegs->ulPCmdOut = mDrvRegs->ulPCmd;
				}
			}
			else
			{
				if((int32)mDrvRegs->ulPCmd > (int32)mDrvRegs->ulPCmdOut)
				{
					mDrvRegs->ulPCmdOut = mDrvRegs->ulPCmd;
				}
			}
		}
	}
	mDrvRegs->ulPCmdOld = mDrvRegs->ulPCmd;

	return mDrvRegs->ulPCmdOut;
}
