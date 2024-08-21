////*****************************************////
//  Name : motorControl_homeLimit.c
//  Data : 2020/11
//  Version : 0.0
////*****************************************////

#include "motorControl.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_findhome(MOTOR_CONTROL_REGS *mCtrlRegs)
{
	if(mCtrlRegs->homeLimitRegs.homeFindMode == home_disable)
	{
		mCtrlRegs->statusRegs.data.homeFinded = 1;
		return;
	}

	mCtrl_home(&mCtrlRegs->homeLimitRegs);
	if( (mCtrlRegs->statusRegs.data.servoState == 1) && (mCtrlRegs->statusRegs.data.homeFinding == 0) && (mCtrlRegs->cmdRegs.data.homeFind == 1) && (mCtrlRegs->statusRegs.data.homeFinded == 0))		//(mCtrlRegs->statusRegs.data.servoState == 1) &&
	{
		mCtrlRegs->homeLimitRegs.ulHomeStop = 0;
		mCtrlRegs->homeLimitRegs.ulHomeBack = 0;
		mCtrlRegs->homeLimitRegs.homeFinded = 0;
		mCtrlRegs->homeLimitRegs.homeFindFailed = 0;
		mCtrlRegs->homeLimitRegs.homeFinding = 1;
	}
	mCtrlRegs->statusRegs.data.homeFinding =mCtrlRegs->homeLimitRegs.homeFinding;
	mCtrlRegs->statusRegs.data.homeFinded = mCtrlRegs->homeLimitRegs.homeFinded;
	mCtrlRegs->statusRegs.data.homeFindFailed = mCtrlRegs->homeLimitRegs.homeFindFailed;
	mCtrlRegs->ulPcmd = mCtrlRegs->homeLimitRegs.ulPcmd;

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_home(HOME_LIMIT_REGS *homeLimitRegs)
{
	if(homeLimitRegs->homeFinding == 0)
	{
		if( homeLimitRegs->homeFindMode ==  home_noIndex || homeLimitRegs->homeFindMode == negative_noIndex || homeLimitRegs->homeFindMode == only_negative)
		{
			homeLimitRegs->ulHomeFindState = homeLimitRegs->limitNegRegs.data.dataNew; // 1: The motor is currently at the negative limit  0:The motor is not currently at the negative limit
		}
		if(homeLimitRegs->homeFindMode ==  home_noIndex_positive || homeLimitRegs->homeFindMode == positive_noIndex)
		{
			homeLimitRegs->ulHomeFindState = homeLimitRegs->limitPosRegs.data.dataNew;//  1: The motor is currently at the positive limit  0:The motor is not currently at the positive limit
		}

		return;
	}

	switch(homeLimitRegs->homeFindMode)
	{
	case positive_noIndex:	mCtrl_home_positive_noIndex(homeLimitRegs);	break;
	case negative_noIndex:	mCtrl_home_negative_noIndex(homeLimitRegs);	break;
	case home_noIndex:	mCtrl_home_home_noIndex(homeLimitRegs);	break;
	case home_noIndex_positive:	mCtrl_home_home_noIndex_positive(homeLimitRegs);break;
	case only_negative:  mCtrl_home_only_negative(homeLimitRegs);break;
	default :			mCtrl_home_home_noIndex(homeLimitRegs);	break;
	}

	mCtrl_home_cmd(homeLimitRegs);
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_home_cmd(HOME_LIMIT_REGS *homeLimitRegs)
{
	if(homeLimitRegs->ulHomeFindDir == home_find_dir_positive)
	{
		homeLimitRegs->ulPcmd += homeLimitRegs->lHomeFindCmd;
	}
	else
	{
		homeLimitRegs->ulPcmd -= homeLimitRegs->lHomeFindCmd;
	}

	if(homeLimitRegs->ulHomeStop == 1)
	{
		//homeLimitRegs->ulPcmd = homeLimitRegs->ulPfbk;
		homeLimitRegs->homeFinding = 0;
		homeLimitRegs->homeFinded = 1;
		mCtrlRegs.cmdRegs.data.homeFind = 0;
		mCtrlRegs.tcurveRegs.ulfirsthome = 0;
		mCtrlRegs.ulPcmdUart = homeLimitRegs->ulPcmd;
		mCtrlRegs.ulPcmdPulse = homeLimitRegs->ulPcmd;

		uint32 lhomePosPcmd;
		lhomePosPcmd = mCtrlRegs.homeLimitRegs.ulhomePos;

		if(mCtrlRegs.homeLimitRegs.softNegLimitEnable == 1)
		{
			if((int32)mCtrlRegs.homeLimitRegs.ulhomePos <(int32)mCtrlRegs.homeLimitRegs.ulSoftNegLimit)
				lhomePosPcmd  = mCtrlRegs.homeLimitRegs.ulSoftNegLimit;

		}
		if(mCtrlRegs.homeLimitRegs.softPosLimitEnable == 1)
		{
			if((int32)mCtrlRegs.homeLimitRegs.ulhomePos >(int32)mCtrlRegs.homeLimitRegs.ulSoftPosLimit)
				lhomePosPcmd  = mCtrlRegs.homeLimitRegs.ulSoftPosLimit;
		}

		if(mCtrlRegs.tcurveRegs.ultcurve_enable == 0  )
		{
			mCtrlRegs.tcurveRegs.ulStartPcmd = mCtrl_ulPcmdUartGet_macro();

			mCtrl_Tcurve_Setting(&mCtrlRegs.tcurveRegs,lhomePosPcmd);
		}
	}

	if(homeLimitRegs->ulHomeFindAlarm == 1)
	{
		homeLimitRegs->ulPcmd = homeLimitRegs->ulPfbk;
		homeLimitRegs->homeFinding = 0;
		homeLimitRegs->homeFindFailed = 1;
	}
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_home_positive_noIndex(HOME_LIMIT_REGS *homeLimitRegs)
{

	if(homeLimitRegs->limitNegRegs.data.posEdge == 1)
	{
		homeLimitRegs->ulHomeFindAlarm = 1;
		return;
	}


	switch(homeLimitRegs->ulHomeFindState){
	case 0:
		homeLimitRegs->ulHomeFindDir = home_find_dir_positive;

		homeLimitRegs->fHomeFindCmd += homeLimitRegs->fHomeFindSpeed - (float32)((int32)homeLimitRegs->fHomeFindSpeed);
		homeLimitRegs->lHomeFindCmd = (int32)homeLimitRegs->fHomeFindSpeed;
		if(homeLimitRegs->fHomeFindCmd >= 1.0F)
		{
			homeLimitRegs->fHomeFindCmd -= 1.0F;
			homeLimitRegs->lHomeFindCmd += 1;
		}
		if(homeLimitRegs->limitPosRegs.data.posEdge == 1)
		{

			homeLimitRegs->ulHomeFindState = 2;

			homeLimitRegs->fHomeFindCmd = 0;
			homeLimitRegs->ulHomeFindDir = home_find_dir_negative;
			homeLimitRegs->lHomeFindCmd = 0;
			homeLimitRegs->ulPcmd = mCtrlRegs.ulPfbk;
			return;

		}
		break;
	case 1:
		homeLimitRegs->ulHomeFindDir = home_find_dir_negative;
		homeLimitRegs->fHomeFindCmd += homeLimitRegs->fHomeFindSpeed - (float32)((int32)homeLimitRegs->fHomeFindSpeed);
		homeLimitRegs->lHomeFindCmd = (int32)homeLimitRegs->fHomeFindSpeed;
		if(homeLimitRegs->fHomeFindCmd >= 1.0F)
		{
			homeLimitRegs->fHomeFindCmd -= 1.0F;
			homeLimitRegs->lHomeFindCmd += 1;
		}
		if(homeLimitRegs->limitPosRegs.data.negEdge == 1)
		{
			homeLimitRegs->ulHomeFindState = 4;
			homeLimitRegs->ulPHome = mCtrlRegs.ulPfbk;
			homeLimitRegs->ulHomeStop = 1;
			homeLimitRegs->fHomeFindCmd = 0;
			homeLimitRegs->ulHomeFindDir = home_find_dir_positive;
			homeLimitRegs->lHomeFindCmd = 0;
			homeLimitRegs->ulPcmd = mCtrlRegs.ulPfbk;
			return;

		}

		break;
	case 2:
		homeLimitRegs->ulHomeFindDir = home_find_dir_negative;
		homeLimitRegs->fHomeFindCmd += homeLimitRegs->fHomeFindSpeed - (float32)((int32)homeLimitRegs->fHomeFindSpeed);
		homeLimitRegs->lHomeFindCmd = (int32)homeLimitRegs->fHomeFindSpeed;
		if(homeLimitRegs->fHomeFindCmd >= 1.0F)
		{
			homeLimitRegs->fHomeFindCmd -= 1.0F;
			homeLimitRegs->lHomeFindCmd += 1;
		}
		if(homeLimitRegs->limitPosRegs.data.negEdge == 1){
			homeLimitRegs->ulHomeFindState = 4;
			homeLimitRegs->ulHomeFindDir = home_find_dir_positive;
			homeLimitRegs->ulPHome = mCtrlRegs.ulPfbk;
			homeLimitRegs->ulHomeStop = 1;
			homeLimitRegs->fHomeFindCmd = 0;
			homeLimitRegs->lHomeFindCmd = 0;
			homeLimitRegs->ulPcmd = mCtrlRegs.ulPfbk;
			return;
		}
		break;
	}

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_home_negative_noIndex(HOME_LIMIT_REGS *homeLimitRegs)
{

	if(homeLimitRegs->limitPosRegs.data.posEdge == 1)
	{
		homeLimitRegs->ulHomeFindAlarm = 1;
		return;
	}

	switch(homeLimitRegs->ulHomeFindState){
	case 0:
		homeLimitRegs->ulHomeFindDir = home_find_dir_negative;

		homeLimitRegs->fHomeFindCmd += homeLimitRegs->fHomeFindSpeed - (float32)((int32)homeLimitRegs->fHomeFindSpeed);
		homeLimitRegs->lHomeFindCmd = (int32)homeLimitRegs->fHomeFindSpeed;
		if(homeLimitRegs->fHomeFindCmd >= 1.0F)
		{
			homeLimitRegs->fHomeFindCmd -= 1.0F;
			homeLimitRegs->lHomeFindCmd += 1;
		}
		if(homeLimitRegs->limitNegRegs.data.posEdge == 1 ||homeLimitRegs->limitNegRegs.data.dataNew == 1)
		{

			homeLimitRegs->ulHomeFindState = 2;
			homeLimitRegs->fHomeFindCmd = 0;
			homeLimitRegs->ulHomeFindDir = home_find_dir_positive;
			homeLimitRegs->lHomeFindCmd = 0;
			homeLimitRegs->ulPcmd = mCtrlRegs.ulPfbk;
			return;
		}
		break;
	case 1:
		homeLimitRegs->ulHomeFindDir = home_find_dir_positive;
		homeLimitRegs->fHomeFindCmd += homeLimitRegs->fHomeFindSpeed - (float32)((int32)homeLimitRegs->fHomeFindSpeed);
		homeLimitRegs->lHomeFindCmd = (int32)homeLimitRegs->fHomeFindSpeed;
		if(homeLimitRegs->fHomeFindCmd >= 1.0F)
		{
			homeLimitRegs->fHomeFindCmd -= 1.0F;
			homeLimitRegs->lHomeFindCmd += 1;
		}
		if(homeLimitRegs->limitNegRegs.data.negEdge == 1)
		{
			homeLimitRegs->ulHomeFindState = 4;
			homeLimitRegs->ulPHome = mCtrlRegs.ulPfbk;
			homeLimitRegs->ulHomeStop = 1;
			homeLimitRegs->fHomeFindCmd = 0;
			homeLimitRegs->ulHomeFindDir = home_find_dir_negative;
			homeLimitRegs->lHomeFindCmd = 0;
			homeLimitRegs->ulPcmd = mCtrlRegs.ulPfbk;
			return;
		}

		break;
	case 2:
		homeLimitRegs->ulHomeFindDir = home_find_dir_positive;
		homeLimitRegs->fHomeFindCmd += homeLimitRegs->fHomeFindSpeed - (float32)((int32)homeLimitRegs->fHomeFindSpeed);
		homeLimitRegs->lHomeFindCmd = (int32)homeLimitRegs->fHomeFindSpeed;
		if(homeLimitRegs->fHomeFindCmd >= 1.0F)
		{
			homeLimitRegs->fHomeFindCmd -= 1.0F;
			homeLimitRegs->lHomeFindCmd += 1;
		}
		if(homeLimitRegs->limitNegRegs.data.negEdge == 1){
			homeLimitRegs->ulHomeFindState = 4;
			homeLimitRegs->ulHomeFindDir = home_find_dir_negative;
			homeLimitRegs->ulPHome = mCtrlRegs.ulPfbk;
			homeLimitRegs->ulHomeStop = 1;
			homeLimitRegs->fHomeFindCmd = 0;
			homeLimitRegs->lHomeFindCmd = 0;
			homeLimitRegs->ulPcmd = mCtrlRegs.ulPfbk;
			return;
		}
		break;
	}

}
#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_home_home_noIndex_positive(HOME_LIMIT_REGS *homeLimitRegs)
{
	if(homeLimitRegs->limitNegRegs.data.posEdge == 1)
	{
		homeLimitRegs->ulHomeFindAlarm = 1;
		return;
	}

	switch(homeLimitRegs->ulHomeFindState)
	{
		case 0:
			homeLimitRegs->ulHomeFindDir = home_find_dir_positive;
			homeLimitRegs->fHomeFindCmd += homeLimitRegs->fHomeFindSpeed - (float32)((int32)homeLimitRegs->fHomeFindSpeed);
			homeLimitRegs->lHomeFindCmd = (int32)homeLimitRegs->fHomeFindSpeed;
			if(homeLimitRegs->fHomeFindCmd >= 1.0F)
			{
				homeLimitRegs->fHomeFindCmd -= 1.0F;
				homeLimitRegs->lHomeFindCmd += 1;
			}
			if(homeLimitRegs->limitPosRegs.data.posEdge == 1 ||homeLimitRegs->limitPosRegs.data.dataNew ==1)
			{
				homeLimitRegs->ulHomeFindState = 1;
				homeLimitRegs->ulHomeFindDir = home_find_dir_negative;
				homeLimitRegs->lHomeFindCmd = 0;
				homeLimitRegs->fHomeFindCmd = 0;
				homeLimitRegs->ulPcmd = mCtrlRegs.ulPfbk;
				return;
			}
			if(homeLimitRegs->homeRegs.data.posEdge == 1)
			{
				homeLimitRegs->ulHomeFindState = 4;
				homeLimitRegs->ulHomeFindDir = home_find_dir_positive;
				homeLimitRegs->ulPHome = mCtrlRegs.ulPfbk;
				homeLimitRegs->ulHomeStop = 1;
				homeLimitRegs->fHomeFindCmd = 0;
				homeLimitRegs->lHomeFindCmd = 0;
				homeLimitRegs->ulPcmd = mCtrlRegs.ulPfbk;
				return;
			}


		break;
		case 1:
			homeLimitRegs->ulHomeFindDir = home_find_dir_negative;
			homeLimitRegs->fHomeFindCmd += homeLimitRegs->fHomeFindSpeed - (float32)((int32)homeLimitRegs->fHomeFindSpeed);
			homeLimitRegs->lHomeFindCmd = (int32)homeLimitRegs->fHomeFindSpeed;
			if(homeLimitRegs->fHomeFindCmd >= 1.0F)
			{
				homeLimitRegs->fHomeFindCmd -= 1.0F;
				homeLimitRegs->lHomeFindCmd += 1;
			}

			if(homeLimitRegs->homeRegs.data.posEdge == 1 )
			{
				homeLimitRegs->ulHomeFindState = 2;
				homeLimitRegs->ulHomeFindDir = home_find_dir_positive;
				homeLimitRegs->lHomeFindCmd = 0;
				homeLimitRegs->fHomeFindCmd = 0;
				homeLimitRegs->ulPcmd = mCtrlRegs.ulPfbk;
				return;
			}

			if(homeLimitRegs->homeRegs.data.negEdge == 1)
			{
				homeLimitRegs->ulHomeFindState = 3;
				homeLimitRegs->ulHomeFindDir = home_find_dir_positive;
				homeLimitRegs->lHomeFindCmd = 0;
				homeLimitRegs->fHomeFindCmd = 0;
				homeLimitRegs->ulPcmd = mCtrlRegs.ulPfbk;

				return;

			}
		break;
		case 2:
			homeLimitRegs->ulHomeFindDir = home_find_dir_positive;
			homeLimitRegs->fHomeFindCmd += homeLimitRegs->fHomeFindSpeed - (float32)((int32)homeLimitRegs->fHomeFindSpeed);
			homeLimitRegs->lHomeFindCmd = (int32)homeLimitRegs->fHomeFindSpeed;
			if(homeLimitRegs->fHomeFindCmd >= 1.0F)
			{
				homeLimitRegs->fHomeFindCmd -= 1.0F;
				homeLimitRegs->lHomeFindCmd += 1;
			}

			if(homeLimitRegs->homeRegs.data.negEdge == 1)
			{
				homeLimitRegs->ulHomeFindState = 4;
				homeLimitRegs->ulHomeFindDir = home_find_dir_negative;
				homeLimitRegs->ulPHome = mCtrlRegs.ulPfbk;
				homeLimitRegs->ulHomeStop = 1;
				homeLimitRegs->fHomeFindCmd = 0;
				homeLimitRegs->lHomeFindCmd = 0;
				homeLimitRegs->ulPcmd = mCtrlRegs.ulPfbk;
				return;
			}
		break;
		case 3:
			homeLimitRegs->ulHomeFindDir = home_find_dir_positive;
			homeLimitRegs->fHomeFindCmd += homeLimitRegs->fHomeFindSpeed - (float32)((int32)homeLimitRegs->fHomeFindSpeed);
			homeLimitRegs->lHomeFindCmd = (int32)homeLimitRegs->fHomeFindSpeed;
			if(homeLimitRegs->fHomeFindCmd >= 1.0F)
			{
				homeLimitRegs->fHomeFindCmd -= 1.0F;
				homeLimitRegs->lHomeFindCmd += 1;
			}

			if(homeLimitRegs->homeRegs.data.negEdge == 1)
			{
				homeLimitRegs->ulHomeFindState = 4;
				homeLimitRegs->ulHomeFindDir = home_find_dir_positive;
				homeLimitRegs->ulPHome = mCtrlRegs.ulPfbk;
				homeLimitRegs->ulHomeStop = 1;
				homeLimitRegs->fHomeFindCmd = 0;
				homeLimitRegs->lHomeFindCmd = 0;
				homeLimitRegs->ulPcmd = mCtrlRegs.ulPfbk;
				return;
			}

			if(homeLimitRegs->limitPosRegs.data.posEdge == 1 || homeLimitRegs->limitPosRegs.data.dataNew == 1)
			{
				homeLimitRegs->ulHomeFindState = 1;
				homeLimitRegs->ulHomeFindDir = home_find_dir_negative;
				homeLimitRegs->lHomeFindCmd = 0;
				homeLimitRegs->fHomeFindCmd = 0;
				homeLimitRegs->ulPcmd = mCtrlRegs.ulPfbk;
				return;
			}

		break;
	}
}



#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_home_home_noIndex(HOME_LIMIT_REGS *homeLimitRegs)
{
	static uint32 ulstable_cnt;
	static float32 fhome_speed;
	static float32 fhome_speed_max;
	static uint32 ulpos_new;
	static uint32 ulpos_old;
	static int32  lpos_diff;


	if(homeLimitRegs->limitPosRegs.data.posEdge == 1)
	{
		homeLimitRegs->ulHomeFindAlarm = 1;
		return;
	}
	
	switch(homeLimitRegs->ulHomeFindState)
	{
		/*Turn counterclockwise, turn clockwise when you encounter the left limit*/
		case 0:
			homeLimitRegs->ulHomeFindDir = home_find_dir_negative;
			homeLimitRegs->fHomeFindCmd += homeLimitRegs->fHomeFindSpeed - (float32)((int32)homeLimitRegs->fHomeFindSpeed);
			homeLimitRegs->lHomeFindCmd = (int32)homeLimitRegs->fHomeFindSpeed;

			if(homeLimitRegs->fHomeFindCmd >= 1.0F)
			{
				homeLimitRegs->fHomeFindCmd -= 1.0F;
				homeLimitRegs->lHomeFindCmd += 1;
			}

			if(homeLimitRegs->limitNegRegs.data.posEdge == 1 || homeLimitRegs->limitNegRegs.data.dataNew == 1)
			{
				//mCtrlRegs.ulhomelimit_pos = mDataRegs.ulEncoderPositonData;
				homeLimitRegs->ulHomeFindState = 1;
				homeLimitRegs->ulHomeFindDir = home_find_dir_negative;//home_find_dir_positive
				homeLimitRegs->lHomeFindCmd = 0;
				homeLimitRegs->fHomeFindCmd = 0;
				//homeLimitRegs->ulPcmd = mDataRegs.ulEncoderPositonData;
				return;
			}
		break;
		case 1:
			homeLimitRegs->ulHomeFindDir = home_find_dir_negative;
			fhome_speed_max = homeLimitRegs->fHomeFindSpeed/2;
			fhome_speed = fhome_speed_max * (2000-ulstable_cnt)/2000;
			homeLimitRegs->fHomeFindCmd += fhome_speed - (float32)((int32)fhome_speed);
			homeLimitRegs->lHomeFindCmd = (int32)fhome_speed;
			if(homeLimitRegs->fHomeFindCmd >= 1.0F)
			{
				homeLimitRegs->fHomeFindCmd -= 1.0F;
				homeLimitRegs->lHomeFindCmd += 1;
			}
			ulstable_cnt++;
			if(ulstable_cnt> 2000 )
			{
				//mCtrlRegs.ulhomelimit_pos = mDataRegs.ulEncoderPositonData;
				homeLimitRegs->ulHomeFindState = 2;
				homeLimitRegs->ulHomeFindDir = home_find_dir_positive;//home_find_dir_positive
				homeLimitRegs->lHomeFindCmd = 0;
				homeLimitRegs->fHomeFindCmd = 0;
				//homeLimitRegs->ulPcmd = mDataRegs.ulEncoderPositonData;
				ulstable_cnt = 0;
				return;
			}
		break;
		/*Rotate towards home, and judge whether the excitation angle is locked when it hits home*/
		case 2:
			homeLimitRegs->ulHomeFindDir = home_find_dir_positive;
			homeLimitRegs->fHomeFindCmd += homeLimitRegs->fHomeFindSpeed - (float32)((int32)homeLimitRegs->fHomeFindSpeed);
			homeLimitRegs->lHomeFindCmd = (int32)homeLimitRegs->fHomeFindSpeed;

			if(homeLimitRegs->fHomeFindCmd >= 1.0F)
			{
				homeLimitRegs->fHomeFindCmd -= 1.0F;
				homeLimitRegs->lHomeFindCmd += 1;
			}

			if(homeLimitRegs->homeRegs.data.posEdge == 1 ||homeLimitRegs->homeRegs.data.dataNew == 1)
			{

				homeLimitRegs->ulHomeFindState = 3;
				homeLimitRegs->ulHomeFindDir = home_find_dir_positive;
				homeLimitRegs->lHomeFindCmd = 0;
				homeLimitRegs->fHomeFindCmd = 0;
				//homeLimitRegs->ulPcmd = mDataRegs.ulEncoderPositonData;
				ulpos_old = mDataRegs.ulEncoderPositonData;
				return;
			}
		break;
		case 3:
			homeLimitRegs->ulHomeFindDir = home_find_dir_positive;
			fhome_speed_max = homeLimitRegs->fHomeFindSpeed/2;
			fhome_speed = fhome_speed_max * (2000-ulstable_cnt)/2000;
			homeLimitRegs->fHomeFindCmd += fhome_speed - (float32)((int32)fhome_speed);
			homeLimitRegs->lHomeFindCmd = (int32)fhome_speed;
			if(homeLimitRegs->fHomeFindCmd >= 1.0F)
			{
				homeLimitRegs->fHomeFindCmd -= 1.0F;
				homeLimitRegs->lHomeFindCmd += 1;
			}
			ulstable_cnt++;
			if(ulstable_cnt> 2000 )
			{
				//mCtrlRegs.ulhomelimit_pos = mDataRegs.ulEncoderPositonData;
				homeLimitRegs->ulHomeFindState = 4;
				homeLimitRegs->ulHomeFindDir = home_find_dir_negative;//home_find_dir_positive
				homeLimitRegs->lHomeFindCmd = 0;
				homeLimitRegs->fHomeFindCmd = 0;
				//homeLimitRegs->ulPcmd = mDataRegs.ulEncoderPositonData;
				ulstable_cnt = 0;
				return;
			}
		break;
		case 4:
			homeLimitRegs->ulHomeFindDir = home_find_dir_negative;
			fhome_speed  = 1.275;
			homeLimitRegs->fHomeFindCmd += fhome_speed - (float32)((int32)fhome_speed);
			homeLimitRegs->lHomeFindCmd = (int32)fhome_speed;

			if(homeLimitRegs->fHomeFindCmd >= 1.0F)
			{
				homeLimitRegs->fHomeFindCmd -= 1.0F;
				homeLimitRegs->lHomeFindCmd += 1;
			}

			if(mDataRegs.ulEncoderIndexFlag == true )
			{
				mDataRegs.ulEncoderZData =  board_encoder_position_read_macro();
				homeLimitRegs->ulHomeFindState = 5;
				homeLimitRegs->ulHomeFindDir = home_find_dir_negative;
				homeLimitRegs->lHomeFindCmd = 0;
				homeLimitRegs->fHomeFindCmd = 0;
				homeLimitRegs->ulPcmd =  mDataRegs.ulEncoderZData ;
				ulpos_old = mDataRegs.ulEncoderZData ;

				return;
			}

		break;
		case 5:
			homeLimitRegs->ulHomeFindDir = home_find_dir_negative;
			homeLimitRegs->fHomeFindCmd = 0;
			homeLimitRegs->lHomeFindCmd = 0;
			ulpos_new  = board_encoder_position_read_macro();
			lpos_diff  = (int32)ulpos_new -ulpos_old;
			if(math_abs_macro(lpos_diff)<20)
			{
				ulstable_cnt++;
			}else
			{
				if(ulstable_cnt>0)
					ulstable_cnt--;
			}
			if(ulstable_cnt>8000)
			{

				homeLimitRegs->ulHomeFindState = 6;
				ulpos_old = ulpos_new;
				ulstable_cnt = 0;
				return;
			}
			ulpos_old = ulpos_new;

		break;
		case 6:
			homeLimitRegs->ulHomeFindState = 7;
			homeLimitRegs->ulPHome =  mDataRegs.ulEncoderZData;
			homeLimitRegs->ulHomeStop = 1;
			homeLimitRegs->ulHomeFindDir = home_find_dir_negative;
			homeLimitRegs->fHomeFindCmd = 0;
			homeLimitRegs->lHomeFindCmd = 0;
			return;
		break;
	}
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_home_only_negative(HOME_LIMIT_REGS *homeLimitRegs)
{
	if(homeLimitRegs->limitPosRegs.data.posEdge == 1)
	{
		homeLimitRegs->ulHomeFindAlarm = 1;
		return;
	}

	switch(homeLimitRegs->ulHomeFindState){
	case 0:
		homeLimitRegs->ulHomeFindDir = home_find_dir_negative;

		homeLimitRegs->fHomeFindCmd += homeLimitRegs->fHomeFindSpeed - (float32)((int32)homeLimitRegs->fHomeFindSpeed);
		homeLimitRegs->lHomeFindCmd = (int32)homeLimitRegs->fHomeFindSpeed;
		if(homeLimitRegs->fHomeFindCmd >= 1.0F)
		{
			homeLimitRegs->fHomeFindCmd -= 1.0F;
			homeLimitRegs->lHomeFindCmd += 1;
		}
		if(homeLimitRegs->limitNegRegs.data.posEdge == 1 ||homeLimitRegs->limitNegRegs.data.dataNew == 1)
		{
			if(mDrv_ulAngleCloseFlagGet_macro()== 1)
			{
				homeLimitRegs->ulHomeFindState = 1;

				homeLimitRegs->fHomeFindCmd = 0;
				homeLimitRegs->ulHomeFindDir = home_find_dir_positive;
				homeLimitRegs->lHomeFindCmd = 0;
				homeLimitRegs->ulPcmd = mCtrlRegs.ulPfbk;
				return;
			}
		}
		break;
	case 1:
		homeLimitRegs->ulHomeFindDir = home_find_dir_positive;
		homeLimitRegs->fHomeFindCmd += homeLimitRegs->fHomeFindSpeed - (float32)((int32)homeLimitRegs->fHomeFindSpeed);
		homeLimitRegs->lHomeFindCmd = (int32)homeLimitRegs->fHomeFindSpeed;
		if(homeLimitRegs->fHomeFindCmd >= 1.0F)
		{
			homeLimitRegs->fHomeFindCmd -= 1.0F;
			homeLimitRegs->lHomeFindCmd += 1;
		}
		if(homeLimitRegs->limitNegRegs.data.negEdge == 1)
		{
			if(mDrv_ulAngleCloseFlagGet_macro()== 1)
			{
				homeLimitRegs->ulHomeFindState = 4;
				homeLimitRegs->ulPHome = mCtrlRegs.ulPfbk;
				homeLimitRegs->ulHomeStop = 1;
				homeLimitRegs->fHomeFindCmd = 0;
				homeLimitRegs->ulHomeFindDir = home_find_dir_negative;
				homeLimitRegs->lHomeFindCmd = 0;
				homeLimitRegs->ulPcmd = mCtrlRegs.ulPfbk;
				return;
			}

		}

		break;
	}

}



#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_homeLimitDataUpdate(HOME_LIMIT_REGS *homeLimitRegs)
{
	homeLimitRegs->homeRegs.data.dataNew = board_DI0_read_macro();
	homeLimitRegs->limitPosRegs.data.dataNew = board_DI2_read_macro();
	homeLimitRegs->limitNegRegs.data.dataNew = board_DI1_read_macro();

	homeLimitRegs->ulimitindex_bit0 = (1-homeLimitRegs->limitPosRegs.data.dataNew)*(homeLimitRegs->homeRegs.data.dataNew+homeLimitRegs->limitNegRegs.data.dataNew-2*homeLimitRegs->limitNegRegs.data.dataNew*homeLimitRegs->homeRegs.data.dataNew);
	homeLimitRegs->ulimitindex_bit1 = (1-homeLimitRegs->limitNegRegs.data.dataNew)*(homeLimitRegs->homeRegs.data.dataNew+homeLimitRegs->limitPosRegs.data.dataNew-2*homeLimitRegs->limitPosRegs.data.dataNew*homeLimitRegs->homeRegs.data.dataNew);

	mCtrl_homeLimitSignalUpdateWithDataInUpdate(homeLimitRegs->homeEnable ,&homeLimitRegs->homeRegs);       	//HomeLimit
	mCtrl_homeLimitSignalUpdateWithDataInUpdate(homeLimitRegs->limitPosEnable ,&homeLimitRegs->limitPosRegs);	//PositiveLimit
	mCtrl_homeLimitSignalUpdateWithDataInUpdate(homeLimitRegs->limitNegEnable ,&homeLimitRegs->limitNegRegs);	//NegativeLimit

	uint32 ulData;

	ulData = 0;

	if(homeLimitRegs->homeEnable == 0)
		ulData += homeLimitRegs->homeRegs.data.dataNew;

	if(homeLimitRegs->limitPosEnable == 0)
		ulData += homeLimitRegs->limitPosRegs.data.dataNew;

	if(homeLimitRegs->limitNegEnable == 0)
		ulData += homeLimitRegs->limitNegRegs.data.dataNew;

	if(ulData > 1)
	{
		homeLimitRegs->ulLimitHomeSignalErr = 1;
	}
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_homeLimitSignalUpdate(uint32 enable,SIGNAL_REGS *homeLimitSignalRegs,uint32 dataIn)
{
	if(enable == 0)
	{
		homeLimitSignalRegs->data.dataNew = dataIn;
		homeLimitSignalRegs->data.posEdge = homeLimitSignalRegs->data.dataNew & ~homeLimitSignalRegs->data.dataOld;
		homeLimitSignalRegs->data.negEdge = ~homeLimitSignalRegs->data.dataNew & homeLimitSignalRegs->data.dataOld;
		homeLimitSignalRegs->data.edge 	= homeLimitSignalRegs->data.posEdge |  homeLimitSignalRegs->data.negEdge;
		homeLimitSignalRegs->data.dataOld = homeLimitSignalRegs->data.dataNew;
	}
	else
	{
		homeLimitSignalRegs->data.dataNew = 0;
		homeLimitSignalRegs->data.posEdge = 0;
		homeLimitSignalRegs->data.negEdge = 0;
		homeLimitSignalRegs->data.edge = 0;
		homeLimitSignalRegs->data.dataOld = 0;
	}
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_homeLimitSignalUpdateWithDataInUpdate(uint32 enable,SIGNAL_REGS *homeLimitSignalRegs)
{
	if(enable == 0)
	{
		homeLimitSignalRegs->data.posEdge = homeLimitSignalRegs->data.dataNew & ~homeLimitSignalRegs->data.dataOld;
		homeLimitSignalRegs->data.negEdge = ~homeLimitSignalRegs->data.dataNew & homeLimitSignalRegs->data.dataOld;
		homeLimitSignalRegs->data.edge 	= homeLimitSignalRegs->data.posEdge |  homeLimitSignalRegs->data.negEdge;
		homeLimitSignalRegs->data.dataOld = homeLimitSignalRegs->data.dataNew;
	}
	else
	{
		homeLimitSignalRegs->data.dataNew = 0;
		homeLimitSignalRegs->data.posEdge = 0;
		homeLimitSignalRegs->data.negEdge = 0;
		homeLimitSignalRegs->data.edge = 0;
		homeLimitSignalRegs->data.dataOld = 0;
	}
}
