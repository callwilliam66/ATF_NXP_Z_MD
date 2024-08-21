//  Name : motorDrive_p.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////
#include "motorDrive.h"

static float32 fAngleVirtual;
static uint32 ulstartup_mode = 0;
static uint32 ulstartup_posold;
static uint32 ulstartup_posnew;
static uint32 ulstartup_counter = 0;
static int32  lS1;
static int32  lS2;

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
// virtual angle
void startup_init(STARTUP_REGS *startUpRegs,STARTCHECK_REGS	*startcheckRegs)
{
	startUpRegs->state = STARTUP_ZERO_STATE_INIT;
	startUpRegs->fStartAngle = 0.25F;

	startUpRegs->fHoldCurrent = 0.3F;
	startUpRegs->ulHoldCnt = 0;
	startUpRegs->ulHoldCntMax = 80000;

	startUpRegs->ulHoldEncData = 0;
	startUpRegs->ulCheckPosEncData = 0;
	startUpRegs->ulCheckNegEncData = 0;

	startUpRegs->ulCheckCmd = 0;
	startUpRegs->fCheckAngle = 0.25F;

	startUpRegs->ulCheckPosEncData = 0;
	startUpRegs->ulCheckNegEncData = 0;

	startUpRegs->ulCheckPass = 0;

	startUpRegs->ulCheckCnt = 0;
	startUpRegs->ulCheckCntMax = 80000;

	startUpRegs->ulFinishCnt = 0;
	startUpRegs->ulFinishCntMax = 80000;

	startUpRegs->fFinishAngle = 0;
	startUpRegs->ulFinishEncData = 0;
	startUpRegs->ulFinishEncAdjustData = 0;

	startcheckRegs->ulstate = STARTUP_ENCODE_CHECK_HOLD;
	startcheckRegs->fHoldCurrent = 0.5F;
	startcheckRegs->fDeltaHoldCurrent = 0.00002F;
	startcheckRegs->fStartAngle = 0.0F;
	startcheckRegs->fVirtualSpeed = 0.003125F;
	startcheckRegs->ulHoldcnt = 0;
	startcheckRegs->ulHoldcnt_max = 4000;

	startcheckRegs->ulEncZCheckCnt = 0;
	startcheckRegs->fanglediff = 0.0f;
	startcheckRegs->fEndCurrent = 0.15f;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
// virtual angle
void startup_clear(STARTUP_REGS *startUpRegs)
{
	startUpRegs->state = STARTUP_ZERO_STATE_INIT;
	startUpRegs->fHoldCurrent = 0.2F;
	startUpRegs->ulHoldCnt = 0;

	startUpRegs->ulHoldEncData = 0;
	startUpRegs->ulCheckPosEncData = 0;
	startUpRegs->ulCheckNegEncData = 0;

	startUpRegs->ulCheckCmd = 0;

	startUpRegs->ulCheckPosEncData = 0;
	startUpRegs->ulCheckNegEncData = 0;

	startUpRegs->ulCheckPass = 0;

	startUpRegs->ulCheckCnt = 0;

	startUpRegs->ulFinishCnt = 0;

	startUpRegs->fFinishAngle = 0;
	startUpRegs->ulFinishEncData = 0;
	startUpRegs->ulFinishEncAdjustData = 0;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
// virtual angle
void startup(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs)
{
	// check if angle id in open loop mode
	if(mDrvRegs->ctrlMode == MOTOR_CTRL_MODE_CURRENT_CLOSE_ANGLE_OPEN)
	{
		startup_angleOpenProcess_type2(mDrvRegs, mDataRegs,mParaRegs);
		return;
	}

	if(mDrvRegs->ctrlMode == MOTOR_CTRL_MODE_CURRENT_CLOSE_ANGLE_OPEN_STEP)
	{
		return;
	}

	// check angle close finish
	if(mDrvRegs->ulAngleCloseFlag == true) return;

	// check servo state
	if(mDrvRegs->servoState == SERVO_STATE_OFF)
	{
		startup_clear(&mDrvRegs->startUpRegs);
		return;
	}

	// select angle close mode
	switch(mParaRegs->encoder.ulEncoderType)
	{

		case ENCODER_TYPE_INC_ZERO_ANGLE_SLOW_START:	startup_zero_slow(mDrvRegs, mDataRegs, mParaRegs);  break;
		case ENCODER_TYPE_ENCODER_CHECK_ZERO_START:		startup_check_zero(mDrvRegs, mDataRegs, mParaRegs);  break;
		case ENCODER_TYPE_INC_ZERO_START:				startup_zero(mDrvRegs, mDataRegs, mParaRegs);  break;
		case ENCODER_TYPE_INC : 						startup_inc(mDrvRegs, mDataRegs, mParaRegs);  break;
		default: break;
	}
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
// virtual angle
void startup_angleOpenProcess(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs,MOTORDRIVE_PARA_REGS *mParaRegs)
{
	mDrvRegs->fVCmd	= mDrvRegs->fVCmdPara;

	mDataRegs->fAngleVirtual += mDrvRegs->fVCmd * mParaRegs->motor.fSpeedMax / 60.0F / mDrvRegs->ulCtrlBaseFreq * (mParaRegs->motor.ulPoles >> 1);

	if(mDataRegs->fAngleVirtual >= 1.0F)
	{
		mDataRegs->fAngleVirtual -= 1.0F;
	}
	else if(mDataRegs->fAngleVirtual < 0.0F)
	{
		mDataRegs->fAngleVirtual += 1.0F;
	}
}
#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
// virtual angle
void startup_angleOpenProcess_type2(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs,MOTORDRIVE_PARA_REGS *mParaRegs)
{
	float32 fhome;
	static uint32 ulstate;
	switch(ulstate)
	{
	case 0:

		fhome = (float32) 1/40000;
		mDataRegs->fAngleVirtual += fhome;

		if(mCtrlRegs.homeLimitRegs.limitNegRegs.data.posEdge== 1 || mCtrlRegs.homeLimitRegs.limitNegRegs.data.dataNew == 1)
		{
			ulstate= 1;
		}
	break;
	case 1:
		fhome = (float32) 1/40000;
		mDataRegs->fAngleVirtual -= fhome;
		if(mCtrlRegs.homeLimitRegs.limitPosRegs.data.posEdge == 1 ||mCtrlRegs.homeLimitRegs.limitPosRegs.data.dataNew == 1)
		{
			ulstate = 0;
		}
	break;
	}

	if(mDataRegs->fAngleVirtual >= 1.0F)
	{
		mDataRegs->fAngleVirtual -= 1.0F;
	}
	else if(mDataRegs->fAngleVirtual < 0.0F)
	{
		mDataRegs->fAngleVirtual += 1.0F;
	}
}
#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void startup_inc(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs)
{
	switch(ulstartup_mode)
	{
	case 0 :
		if(mDrvRegs->fIdCmdPara < 0.4)
		{
			fAngleVirtual = 0;
			mDrvRegs->fIdCmdPara  = mDrvRegs->fIdCmdPara  + 0.0001;
		}
		else
		{
			ulstartup_counter++;
			mDrvRegs->fIdCmdPara  = 0.4;
			if(ulstartup_counter>4000)
			{
				ulstartup_mode = 1;
				ulstartup_counter = 0;
			}

		}
	break;
	case 1:
		ulstartup_counter++;
		if(ulstartup_counter>4000)
		{
			ulstartup_mode = 2;
			ulstartup_counter = 0;
		}
	break;
	case 2:
		mDataRegs->ulEncoderAngleData = 0.0;
		mDataRegs->ulEncoderAngleNew = 0.0;
		mDataRegs->ulEncoderAngleOld = 0.0;

		ENC_DoSoftwareLoadInitialPositionValue(ENC1_PERIPHERAL);
		ENC_DoSoftwareLoadInitialPositionValue(ENC3_PERIPHERAL);

		mParaRegs->encoder.ulEncoderIndexOffset = 0;
		mDrvRegs->ulAngleCloseFlag = true;
		ulstartup_mode = 3;
	break;

	}
	mDataRegs->fAngleVirtual = fAngleVirtual;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void startup_zero(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs)
{
	switch(mDrvRegs->startUpRegs.state)
	{
		case STARTUP_ZERO_STATE_INIT:
			mDataRegs->fAngleVirtual = mDrvRegs->startUpRegs.fStartAngle;

			mDrvRegs->fIdCmdPara = 0.0F;

			mDrvRegs->startUpRegs.fHoldCurrent = mParaRegs->motor.fCurrentRated / mParaRegs->motor.fCurrentMax;

			mDrvRegs->startUpRegs.state = STARTUP_ZERO_STATE_HOLD;

		break;
		case STARTUP_ZERO_STATE_HOLD:
			if(mDrvRegs->startUpRegs.ulHoldCnt < mDrvRegs->startUpRegs.ulHoldCntMax)
			{
				mDrvRegs->startUpRegs.ulHoldCnt++;

				mDrvRegs->fIdCmdPara = mDrvRegs->startUpRegs.fHoldCurrent * ((float32)mDrvRegs->startUpRegs.ulHoldCnt / (float32) mDrvRegs->startUpRegs.ulHoldCntMax);
			}
			else
			{
				mDrvRegs->startUpRegs.ulHoldCnt = 0;

				mDrvRegs->startUpRegs.ulHoldEncData = mDataRegs->ulEncoderAngleNew;

				mDrvRegs->startUpRegs.state = STARTUP_ZERO_STATE_CHECK_POS;
			}

		break;
		case STARTUP_ZERO_STATE_CHECK_POS:
			if(mDrvRegs->startUpRegs.ulCheckCnt < mDrvRegs->startUpRegs.ulCheckCntMax)
			{
				mDrvRegs->startUpRegs.ulCheckCnt++;

				mDataRegs->fAngleVirtual = mDrvRegs->startUpRegs.fStartAngle + mDrvRegs->startUpRegs.fCheckAngle * ((float32)mDrvRegs->startUpRegs.ulCheckCnt / (float32) mDrvRegs->startUpRegs.ulCheckCntMax);
			}
			else if(mDrvRegs->startUpRegs.ulCheckCnt == mDrvRegs->startUpRegs.ulCheckCntMax)
			{
				mDrvRegs->startUpRegs.ulCheckCnt++;

				mDrvRegs->startUpRegs.ulCheckPosEncData = mDataRegs->ulEncoderAngleNew;
			}
			else if(mDrvRegs->startUpRegs.ulCheckCnt < mDrvRegs->startUpRegs.ulCheckCntMax * 2)
			{
				mDrvRegs->startUpRegs.ulCheckCnt++;

				mDataRegs->fAngleVirtual = mDrvRegs->startUpRegs.fStartAngle + mDrvRegs->startUpRegs.fCheckAngle - mDrvRegs->startUpRegs.fCheckAngle * ((float32)(mDrvRegs->startUpRegs.ulCheckCnt - mDrvRegs->startUpRegs.ulCheckCntMax) / (float32) mDrvRegs->startUpRegs.ulCheckCntMax);
			}
			else
			{
				mDrvRegs->startUpRegs.ulCheckCnt = 0;

				mDrvRegs->startUpRegs.state = STARTUP_ZERO_STATE_CHECK_NEG;
			}

		break;
		case STARTUP_ZERO_STATE_CHECK_NEG:
			if(mDrvRegs->startUpRegs.ulCheckCnt < mDrvRegs->startUpRegs.ulCheckCntMax)
			{
				mDrvRegs->startUpRegs.ulCheckCnt++;

				mDataRegs->fAngleVirtual = mDrvRegs->startUpRegs.fStartAngle - mDrvRegs->startUpRegs.fCheckAngle * ((float32)mDrvRegs->startUpRegs.ulCheckCnt / (float32) mDrvRegs->startUpRegs.ulCheckCntMax);

			}
			else if(mDrvRegs->startUpRegs.ulCheckCnt == mDrvRegs->startUpRegs.ulCheckCntMax)
			{
				mDrvRegs->startUpRegs.ulCheckCnt++;

				mDrvRegs->startUpRegs.ulCheckNegEncData = mDataRegs->ulEncoderAngleNew;
			}
			else if(mDrvRegs->startUpRegs.ulCheckCnt < mDrvRegs->startUpRegs.ulCheckCntMax * 2)
			{
				mDrvRegs->startUpRegs.ulCheckCnt++;

				mDataRegs->fAngleVirtual = mDrvRegs->startUpRegs.fStartAngle - mDrvRegs->startUpRegs.fCheckAngle + mDrvRegs->startUpRegs.fCheckAngle * ((float32)(mDrvRegs->startUpRegs.ulCheckCnt - mDrvRegs->startUpRegs.ulCheckCntMax) / (float32) mDrvRegs->startUpRegs.ulCheckCntMax);
			}
			else
			{
				mDrvRegs->startUpRegs.ulCheckCnt = 0;

				mDrvRegs->startUpRegs.state = STARTUP_ZERO_STATE_CHECK;
			}
		break;
		case STARTUP_ZERO_STATE_CHECK:

			mDrvRegs->startUpRegs.ulCheckCmd = mDrvRegs->startUpRegs.fCheckAngle * (float32)mParaRegs->encoder.ulEncoderMaxPulse / (float32)(mParaRegs->motor.ulPoles >> 1);

			mDrvRegs->startUpRegs.ulCheckPass = mDrvRegs->startUpRegs.ulCheckCmd * 0.1F;

			int32 lPosCheckData;
			int32 lNegCheckData;
			int32 lPosCheckMoveData;
			int32 lNegCheckMoveData;

			lPosCheckData = (int32)mDrvRegs->startUpRegs.ulCheckPosEncData - (int32)mDrvRegs->startUpRegs.ulHoldEncData - (int32)mDrvRegs->startUpRegs.ulCheckCmd;
			lNegCheckData = (int32)mDrvRegs->startUpRegs.ulHoldEncData - (int32)mDrvRegs->startUpRegs.ulCheckNegEncData - (int32)mDrvRegs->startUpRegs.ulCheckCmd;
			lPosCheckMoveData = (int32)mDrvRegs->startUpRegs.ulCheckPosEncData - (int32)mDrvRegs->startUpRegs.ulHoldEncData;
			lNegCheckMoveData = (int32)mDrvRegs->startUpRegs.ulHoldEncData - (int32)mDrvRegs->startUpRegs.ulCheckNegEncData;

			if((math_abs_macro(lPosCheckData)) < mDrvRegs->startUpRegs.ulCheckPass)
			{
				if((math_abs_macro(lNegCheckData)) < mDrvRegs->startUpRegs.ulCheckPass)
				{
					mDrvRegs->startUpRegs.fFinishAngle = mDrvRegs->startUpRegs.fStartAngle;
					mDrvRegs->startUpRegs.ulFinishEncData = mDrvRegs->startUpRegs.ulHoldEncData;
				}
				else
				{
					mDrvRegs->startUpRegs.fFinishAngle = mDrvRegs->startUpRegs.fStartAngle + mDrvRegs->startUpRegs.fCheckAngle * 0.5F;
					mDrvRegs->startUpRegs.ulFinishEncData = mDrvRegs->startUpRegs.ulCheckPosEncData - (mDrvRegs->startUpRegs.fCheckAngle * 0.5F)  * (float32)mParaRegs->encoder.ulEncoderMaxPulse / (float32)(mParaRegs->motor.ulPoles >> 1);
				}
			}
			else
			{
				if((math_abs_macro(lNegCheckData)) < mDrvRegs->startUpRegs.ulCheckPass)
				{
					mDrvRegs->startUpRegs.fFinishAngle = mDrvRegs->startUpRegs.fStartAngle - mDrvRegs->startUpRegs.fCheckAngle * 0.5F;
					mDrvRegs->startUpRegs.ulFinishEncData = mDrvRegs->startUpRegs.ulCheckNegEncData + (mDrvRegs->startUpRegs.fCheckAngle * 0.5F)  * (float32)mParaRegs->encoder.ulEncoderMaxPulse / (float32)(mParaRegs->motor.ulPoles >> 1);
				}
				else
				{
					if((math_abs_macro(lPosCheckMoveData)) > (math_abs_macro(lNegCheckMoveData)))
					{
						mDrvRegs->startUpRegs.fFinishAngle = mDrvRegs->startUpRegs.fStartAngle + mDrvRegs->startUpRegs.fCheckAngle;
						mDrvRegs->startUpRegs.ulFinishEncData = mDrvRegs->startUpRegs.ulCheckPosEncData;
					}
					else if((math_abs_macro(lPosCheckMoveData)) < (math_abs_macro(lNegCheckMoveData)))
					{
						mDrvRegs->startUpRegs.fFinishAngle = mDrvRegs->startUpRegs.fStartAngle - mDrvRegs->startUpRegs.fCheckAngle;
						mDrvRegs->startUpRegs.ulFinishEncData = mDrvRegs->startUpRegs.ulCheckNegEncData;
					}
					else
					{
						mDrvRegs->startUpRegs.state = STARTUP_ZERO_STATE_INIT;
						mDrvRegs->startUpRegs.fCheckAngle = mDrvRegs->startUpRegs.fCheckAngle * 1.1F;
					}
				}
			}

			mDrvRegs->startUpRegs.ulFinishEncAdjustData = mDrvRegs->startUpRegs.fFinishAngle * (float32)mParaRegs->encoder.ulEncoderMaxPulse / (float32)(mParaRegs->motor.ulPoles >> 1);

			mDrvRegs->startUpRegs.state = STARTUP_ZERO_STATE_FINISH;
		break;
		case STARTUP_ZERO_STATE_FINISH:
			if(mDrvRegs->startUpRegs.ulFinishCnt < mDrvRegs->startUpRegs.ulFinishCntMax)
			{
				mDrvRegs->startUpRegs.ulFinishCnt++;

				mDataRegs->fAngleVirtual = mDrvRegs->startUpRegs.fStartAngle + (mDrvRegs->startUpRegs.fFinishAngle - mDrvRegs->startUpRegs.fStartAngle) * ((float32)mDrvRegs->startUpRegs.ulFinishCnt / (float32) mDrvRegs->startUpRegs.ulFinishCntMax);
			}
			else
			{
				mDrvRegs->startUpRegs.ulFinishCnt = 0;

				int32 lFinishCheckData;

				lFinishCheckData = (int32)mDrvRegs->startUpRegs.ulFinishEncData - (int32)mDataRegs->ulEncoderAngleNew;

				if((math_abs_macro(lFinishCheckData)) < mDrvRegs->startUpRegs.ulCheckPass)
				{
					mDataRegs->ulEncoderAngleNew = mDrvRegs->startUpRegs.ulFinishEncAdjustData;
					mDataRegs->ulEncoderAngleData = mDrvRegs->startUpRegs.ulFinishEncAdjustData;
					mDataRegs->ulEncoderAngleOld = mDrvRegs->startUpRegs.ulFinishEncAdjustData;

					ENC_SetInitialPositionValue(ENC1_PERIPHERAL,(mDrvRegs->startUpRegs.ulFinishEncAdjustData));
					ENC_DoSoftwareLoadInitialPositionValue(ENC1_PERIPHERAL);
					ENC_DoSoftwareLoadInitialPositionValue(ENC3_PERIPHERAL);
					mParaRegs->encoder.ulEncoderIndexOffset = 0;

					mDrvRegs->startUpRegs.state = STARTUP_ZERO_STATE_END;
				}
				else
				{
					mDrvRegs->startUpRegs.state = STARTUP_ZERO_STATE_INIT;

					mDrvRegs->startUpRegs.fCheckAngle = mDrvRegs->startUpRegs.fCheckAngle * 1.1F;
				}
			}
		break;
		case STARTUP_ZERO_STATE_END:
			if(mDrvRegs->startUpRegs.ulHoldCnt < mDrvRegs->startUpRegs.ulHoldCntMax)
			{
				mDrvRegs->startUpRegs.ulHoldCnt++;

				mDrvRegs->fIdCmdPara = mDrvRegs->startUpRegs.fHoldCurrent - mDrvRegs->startUpRegs.fHoldCurrent * ((float32)mDrvRegs->startUpRegs.ulHoldCnt / (float32) mDrvRegs->startUpRegs.ulHoldCntMax);
			}
			else
			{
				mDrvRegs->startUpRegs.ulHoldCnt = 0;

				mDrvRegs->ulAngleCloseFlag = true;

				mDrvRegs->startUpRegs.state = STARTUP_ZERO_STATE_INIT;
			}
		break;
		default:
			mDrvRegs->startUpRegs.state = STARTUP_ZERO_STATE_INIT;
		break;
	}

	if(mDataRegs->fAngleVirtual < 0.0F)
		mDataRegs->fAngleVirtual += 1.0F;

	if(mDataRegs->fAngleVirtual >= 1.0F)
		mDataRegs->fAngleVirtual -= 1.0F;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void startup_zero_slow(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs)
{
	switch(ulstartup_mode)
	{
	case 0 :
		if(mDrvRegs->fIdCmdPara < 0.6)
		{
			fAngleVirtual = 0;
			mDrvRegs->fIdCmdPara  = mDrvRegs->fIdCmdPara  + 0.00001;
		}
		else
		{
			ulstartup_counter++;
			mDrvRegs->fIdCmdPara  = 0.6;
			if(ulstartup_counter>10000)
			{
				ulstartup_mode = 1;
				ulstartup_counter = 0;
			}
			ulstartup_posold = mDataRegs->ulEncoderAngleNew;
		}
	break;
	case 1:
		fAngleVirtual = fAngleVirtual +  0.00005;
		if(fAngleVirtual>=0.5F)
		{
			fAngleVirtual = 0.5;
			ulstartup_counter++;
			if(ulstartup_counter>10000)
			{
				ulstartup_mode = 2;
				ulstartup_counter = 0;
			}

		}
	break;
	case 2:
		ulstartup_posnew = mDataRegs->ulEncoderAngleNew;
		lS1 = math_abs_macro( (int32) ulstartup_posnew - (int32)ulstartup_posold );
		ulstartup_mode = 3;
	break;
	case 3:
		fAngleVirtual = fAngleVirtual -  0.00005;
		if(fAngleVirtual<=0.0F)
		{
			fAngleVirtual = 0.0F;
			ulstartup_counter++;
			if(ulstartup_counter>10000)
			{
				ulstartup_mode = 4;
				ulstartup_counter = 0;
			}

		}
	break;
	case 4:
		fAngleVirtual = fAngleVirtual -  0.00005;
		if(fAngleVirtual<=-0.5F)
		{
			fAngleVirtual = -0.5F;
			ulstartup_counter++;
			if(ulstartup_counter>10000)
			{
				ulstartup_mode = 5;
				ulstartup_counter = 0;
			}
			ulstartup_posold = mDataRegs->ulEncoderAngleNew;
		}
	break;
	case 5:
		ulstartup_posnew = mDataRegs->ulEncoderAngleNew;
		lS2 = math_abs_macro( (int32)ulstartup_posnew - (int32)ulstartup_posold );
		if(lS1>=lS2)
		{
			ulstartup_mode = 6;
		}
		else
		{
			ulstartup_mode = 7;
		}
		break;
	case 6:
		fAngleVirtual = fAngleVirtual +	 0.00005;
		if(fAngleVirtual>0)
		{
			fAngleVirtual = 0;
			ulstartup_counter++;
			if(ulstartup_counter>10000)
			{
				ulstartup_mode = 8;
				ulstartup_counter = 0;
			}

		}
	break;
	case 7:
		fAngleVirtual = fAngleVirtual - 0.00005;
		if(fAngleVirtual<=-1.0)
		{
			fAngleVirtual = -1.0;
			ulstartup_counter++;
			if(ulstartup_counter>10000)
			{
				ulstartup_mode = 8;
				ulstartup_counter = 0;
			}
		}
	break;
	case 8:
		mDataRegs->ulEncoderAngleData = 0.0;
		mDataRegs->ulEncoderAngleNew = 0.0;
		mDataRegs->ulEncoderAngleOld = 0.0;

		ENC_DoSoftwareLoadInitialPositionValue(ENC1_PERIPHERAL);
		ENC_DoSoftwareLoadInitialPositionValue(ENC3_PERIPHERAL);

		mParaRegs->encoder.ulEncoderIndexOffset = 0;

		ulstartup_mode = 9;
	break;
	case 9:
		ulstartup_counter++;
		if(ulstartup_counter>12000)
		{
			ulstartup_mode = 10;
			ulstartup_counter = 0;
			mDrvRegs->ulAngleCloseFlag = true;
		}

	break;

	}
	mDataRegs->fAngleVirtual = fAngleVirtual;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void startup_check_zero(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs)
{
	uint32 ulfvirtualref;
	uint32 ulposref;
	int32  ldiff;
	switch(mDrvRegs->startUpCheckRegs.ulstate)
	{
		case STARTUP_ENCODE_CHECK_HOLD:
			if(mDrvRegs->fIdCmdPara < mDrvRegs->startUpCheckRegs.fHoldCurrent)
			{
				mDataRegs->fAngleVirtual = mDrvRegs->startUpCheckRegs.fStartAngle;
				mDrvRegs->fIdCmdPara = mDrvRegs->fIdCmdPara + mDrvRegs->startUpCheckRegs.fDeltaHoldCurrent;
			}else
			{
				if(mDrvRegs->startUpCheckRegs.ulHoldcnt < mDrvRegs->startUpCheckRegs.ulHoldcnt_max)
				{
					mDrvRegs->startUpCheckRegs.ulHoldcnt++;
				}else
				{
					mDrvRegs->startUpCheckRegs.ulstate = STARTUP_ENCODE_CHECK_NEG;
					mDrvRegs->startUpCheckRegs.ulHoldcnt = 0;
					mDrvRegs->startUpCheckRegs.ulEncPos_old = mDataRegs->ulEncoderAngleNew;

				}
			}
		break;
		case STARTUP_ENCODE_CHECK_NEG:
			mDrvRegs->startUpCheckRegs.lEncPos_check = (int32)mDataRegs->ulEncoderAngleNew-(int32)mDrvRegs->startUpCheckRegs.ulEncPos_old;

			if(mCtrlRegs.homeLimitRegs.limitNegRegs.data.posEdge == 1 || mCtrlRegs.homeLimitRegs.limitNegRegs.data.dataNew == 1)
			{
				mDrvRegs->startUpCheckRegs.ulstate = STARTUP_ENCODE_CHECK_POS;
				mDrvRegs->startUpCheckRegs.ulEncZCheckCnt = 0;
				mDrvRegs->startUpCheckRegs.ulHoldcnt = 0;
				mDrvRegs->startUpCheckRegs.ulEncPos_old = mDataRegs->ulEncoderAngleNew;
				mDrvRegs->startUpCheckRegs.fanglediff  = 0.0f;
				return;
			}
			ulfvirtualref = mDrvRegs->startUpCheckRegs.fanglediff * mParaRegs->encoder.ulEncoderMaxPulse /(mParaRegs->motor.ulPoles>>1);
			ulposref = math_abs_macro(mDrvRegs->startUpCheckRegs.lEncPos_check );
			ldiff = (int32)ulfvirtualref - (int32)ulposref;

			if(math_abs_macro(ldiff)> 400)
			{
				mDrvRegs->startUpCheckRegs.ulstate = STARTUP_ENCODE_CHECK_ERROR;
				mDrvRegs->startUpCheckRegs.ulEncZCheckCnt = 0;
				mDrvRegs->startUpCheckRegs.ulHoldcnt = 0;
				mDrvRegs->startUpCheckRegs.ulEncPos_old = mDataRegs->ulEncoderAngleNew;
				mDrvRegs->startUpCheckRegs.fanglediff  = 0.0f;
				return;

			}

			if(mDataRegs->ulEncoderIndexFlag == true)
			{
				mDrvRegs->startUpCheckRegs.ulEncZCheckCnt++;
				if(mDrvRegs->startUpCheckRegs.ulEncZCheckCnt == 1)
				{
					mDrvRegs->startUpCheckRegs.ulEncZPos1 =  mDataRegs->ulEncoderAngleNew;
				}else if(mDrvRegs->startUpCheckRegs.ulEncZCheckCnt == 2)
				{
					mDrvRegs->startUpCheckRegs.ulEncZPos2 =  mDataRegs->ulEncoderAngleNew;
					mDrvRegs->startUpCheckRegs.ulstate = STARTUP_ENCODE_CHECK_JUDGE;
				}

			}
			if(mDrvRegs->startUpCheckRegs.ulEncZCheckCnt != 2)
			{
				mDataRegs->fAngleVirtual = mDataRegs->fAngleVirtual - mDrvRegs->startUpCheckRegs.fVirtualSpeed;
				mDrvRegs->startUpCheckRegs.fanglediff += mDrvRegs->startUpCheckRegs.fVirtualSpeed;
			}
		break;
		case STARTUP_ENCODE_CHECK_POS:
			mDrvRegs->startUpCheckRegs.lEncPos_check = (int32)mDataRegs->ulEncoderAngleNew-(int32)mDrvRegs->startUpCheckRegs.ulEncPos_old;

			ulfvirtualref = mDrvRegs->startUpCheckRegs.fanglediff * mParaRegs->encoder.ulEncoderMaxPulse /(mParaRegs->motor.ulPoles>>1);
			ulposref = math_abs_macro(mDrvRegs->startUpCheckRegs.lEncPos_check );
			ldiff = (int32)ulfvirtualref - (int32)ulposref;
			if(math_abs_macro(ldiff)> 330)
			{
				mDrvRegs->startUpCheckRegs.ulstate = STARTUP_ENCODE_CHECK_ERROR;
				mDrvRegs->startUpCheckRegs.ulEncZCheckCnt = 0;
				mDrvRegs->startUpCheckRegs.ulHoldcnt = 0;
				mDrvRegs->startUpCheckRegs.ulEncPos_old = mDataRegs->ulEncoderAngleNew;
				mDrvRegs->startUpCheckRegs.fanglediff  = 0.0f;
				return;
			}
			if(mDrvRegs->startUpCheckRegs.fanglediff> 4*(mParaRegs->motor.ulPoles>>1))
			{
				if(mDrvRegs->startUpCheckRegs.ulEncZCheckCnt !=2)
				{
					mDrvRegs->startUpCheckRegs.ulstate = STARTUP_ENCODE_CHECK_ERROR;
					mDrvRegs->startUpCheckRegs.ulEncZCheckCnt = 0;
					mDrvRegs->startUpCheckRegs.ulHoldcnt = 0;
					mDrvRegs->startUpCheckRegs.ulEncPos_old = mDataRegs->ulEncoderAngleNew;
					mDrvRegs->startUpCheckRegs.fanglediff  = 0.0f;
					return;

				}

			}
			if(mDataRegs->ulEncoderIndexFlag == true)
			{
				mDrvRegs->startUpCheckRegs.ulEncZCheckCnt++;
				if(mDrvRegs->startUpCheckRegs.ulEncZCheckCnt == 1)
				{
					mDrvRegs->startUpCheckRegs.ulEncZPos1 =  mDataRegs->ulEncoderAngleNew;
				}else if(mDrvRegs->startUpCheckRegs.ulEncZCheckCnt == 2)
				{
					mDrvRegs->startUpCheckRegs.ulEncZPos2 =  mDataRegs->ulEncoderAngleNew;
					mDrvRegs->startUpCheckRegs.ulstate = STARTUP_ENCODE_CHECK_JUDGE;
				}

			}
			if(mDrvRegs->startUpCheckRegs.ulEncZCheckCnt != 2)
			{
				mDataRegs->fAngleVirtual = mDataRegs->fAngleVirtual + mDrvRegs->startUpCheckRegs.fVirtualSpeed;
				mDrvRegs->startUpCheckRegs.fanglediff += mDrvRegs->startUpCheckRegs.fVirtualSpeed;
			}

		break;
		case STARTUP_ENCODE_CHECK_JUDGE:
			mDrvRegs->startUpCheckRegs.lEncZPosDiff = (int32)(mDrvRegs->startUpCheckRegs.ulEncZPos2-mDrvRegs->startUpCheckRegs.ulEncZPos1);
			if( math_abs_macro( (int32) (math_abs_macro(mDrvRegs->startUpCheckRegs.lEncZPosDiff) - mParaRegs->encoder.ulEncoderMaxPulse) )  < 5 )
			{
				mDrvRegs->startUpCheckRegs.ulstate = STARTUP_ENCODE_CHECK_PASS;
			}else
			{
				mDrvRegs->startUpCheckRegs.ulstate = STARTUP_ENCODE_CHECK_ERROR;
			}
		break;
		case STARTUP_ENCODE_CHECK_PASS:
			mDataRegs->fAngleVirtual = 0.0F;
			if(mDrvRegs->startUpCheckRegs.ulHoldcnt < mDrvRegs->startUpCheckRegs.ulHoldcnt_max)
			{
				mDrvRegs->startUpCheckRegs.ulHoldcnt++;
			}else
			{
				mDrvRegs->startUpCheckRegs.ulstate = STARTUP_ENCODE_CHECK_FINISH;
				mDrvRegs->startUpCheckRegs.ulHoldcnt = 0;
			}
		break;
		case STARTUP_ENCODE_CHECK_FINISH:
			if(mDrvRegs->fIdCmdPara > mDrvRegs->startUpCheckRegs.fEndCurrent)
			{
				mDataRegs->fAngleVirtual = mDrvRegs->startUpCheckRegs.fStartAngle;
				mDrvRegs->fIdCmdPara = mDrvRegs->fIdCmdPara - 2*mDrvRegs->startUpCheckRegs.fDeltaHoldCurrent;
			}else
			{
				mDrvRegs->startUpCheckRegs.ulstate = STARTUP_ENCODE_CHECK_END;
			}
		break;
		case STARTUP_ENCODE_CHECK_END:
			mDataRegs->ulEncoderAngleNew = 0;
			mDataRegs->ulEncoderAngleData = 0;
			mDataRegs->ulEncoderAngleOld = 0;
			ENC_DoSoftwareLoadInitialPositionValue(ENC1_PERIPHERAL);
			ENC_DoSoftwareLoadInitialPositionValue(ENC3_PERIPHERAL);
			mParaRegs->encoder.ulEncoderIndexOffset = 0;
			mDrvRegs->ulAngleCloseFlag = true;
		break;
		case STARTUP_ENCODE_CHECK_ERROR:
			mDrvRegs->alarmCode.data.encodererror = 1;
		break;
		default:
			mDrvRegs->startUpCheckRegs.ulstate = STARTUP_ENCODE_CHECK_HOLD;
		break;
	}
	if(mDataRegs->fAngleVirtual < 0.0F)
		mDataRegs->fAngleVirtual += 1.0F;

	if(mDataRegs->fAngleVirtual >= 1.0F)
		mDataRegs->fAngleVirtual -= 1.0F;
}
