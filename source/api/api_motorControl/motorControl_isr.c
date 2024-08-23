////*****************************************////
//  Name : motorControl_isr.c
//  Data : 2020/10
//  Version : 0.0
////*****************************************////

#include "motorControl.h"
static uint32 ulpcmdold;

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void motorControl_isr(void)
{
	// state

	motorControl_statusUpdate();									//State Update

	mCtrl_homeLimitDataUpdate(&mCtrlRegs.homeLimitRegs);			//Limit Update

	// controller process
	mCtrl_uart_isr(&mCtrlRegs.uart1Regs);
	mCtrl_uart_isr(&mCtrlRegs.uart2Regs);
	//mCtrl_fpga_uart_isr(&mCtrlRegs.uart2Regs);
	mCtrl_inner_uart_isr(&mCtrlRegs.uart3Regs);
	// servo on control
	if((mCtrlRegs.uart1Regs.firmwareUpdateFlag == 1) || (mCtrlRegs.uart2Regs.firmwareUpdateFlag == 1)|| (mCtrlRegs.uart3Regs.firmwareUpdateFlag == 1))
	{
		mDrv_servoStateSet_macro(0);
		mDrv_servoStateSWSet_macro(0);
		mDrv_servoStateIOSet_macro(0);
		mDrv_servoStateCtrlrSet_macro(0);
	}
	else
	{
		if(mDrv_servoOnModeGet_macro() == SERVO_ON_MODE_CTLR)
		{
			mDrv_servoStateCtrlrSet_macro(mCtrlRegs.cmdRegs.data.servoOn);
		}
	}


	 //servo off process
	if(mCtrlRegs.statusRegs.data.servoState == 0)
	{
		mCtrlRegs.ulPcmd = mCtrlRegs.ulPfbk;
		mCtrlRegs.ulPcmdUart = mCtrlRegs.ulPfbk;
		mDrv_ulPCmdCtrlrSet_macro(mCtrlRegs.ulPcmd);
		mCtrlRegs.emgRegs.ulEmgState = 0;
		mCtrlRegs.homeLimitRegs.ulPcmd = mCtrlRegs.ulPfbk;
		mCtrl_homeFindingClear(&mCtrlRegs);
		return;
	}

	if(mDrv_ulAngleCloseFlagGet_macro() == 0)
	{
		mCtrlRegs.ulPcmd = mCtrlRegs.ulPfbk;
		mCtrlRegs.ulPcmdUart = mCtrlRegs.ulPfbk;
		mDrv_ulPCmdCtrlrSet_macro(mCtrlRegs.ulPcmd);
		mCtrlRegs.homeLimitRegs.ulPcmd = mCtrlRegs.ulPfbk;

	}

	//servo on process
	mCtrlRegs.commandReceiveEnableFlag = (mCtrlRegs.statusRegs.data.homeFinded == 1) || ((mCtrlRegs.homeLimitRegs.homeFindMode == home_disable) && (mDrv_ulAngleCloseFlagGet_macro() == 1));

	if(mCtrlRegs.commandReceiveEnableFlag == 1)
	{
		motorControl_advCtrl_commandRenew(para_valueGet_macro(PARA_ADVCTRL1_ENABLE), para_valueGet_macro(PARA_ADVCTRL1_PARA0), para_valueGet_macro(PARA_ADVCTRL1_PARA1), &mCtrlRegs);

		mCtrlRegs.ulPcmd = mCtrlRegs.ulPcmdUart;
		/*switch(mCtrlRegs.mode)
		{
			case CTRLR_MODE_UART	: mCtrlRegs.ulPcmd = mCtrlRegs.ulPcmdUart;	break;
			case CTRLR_MODE_SPI		: mCtrlRegs.ulPcmd = mCtrlRegs.ulPcmdSpi;	break;
			default					: mCtrlRegs.ulPcmd = mCtrlRegs.ulPcmdUart;	break;
		}
		*/
		if((mCtrlRegs.cmdRegs.data.homeFind == 1) && (mCtrlRegs.homeLimitRegs.homeFindMode != home_disable))
		{
			mCtrlRegs.homeLimitRegs.ulHomeStop = 0;
			mCtrlRegs.homeLimitRegs.ulHomeBack = 0;
			mCtrlRegs.homeLimitRegs.homeFindFailed = 0;
			mCtrlRegs.homeLimitRegs.ulHomeFindState = 0;
			mCtrlRegs.homeLimitRegs.homeFinded = 0;
			mCtrlRegs.homeLimitRegs.homeFinding = 1;
			mCtrlRegs.homeLimitRegs.ulPcmd = mCtrlRegs.ulPfbk;

			mCtrlRegs.statusRegs.data.homeFinding = mCtrlRegs.homeLimitRegs.homeFinding;
			mCtrlRegs.statusRegs.data.homeFinded = mCtrlRegs.homeLimitRegs.homeFinded;
			mCtrlRegs.statusRegs.data.homeFindFailed = mCtrlRegs.homeLimitRegs.homeFindFailed;
		}
	}
	else
	{
		if((mDrv_ulAngleCloseFlagGet_macro() == 1) && (mDrvRegs.startUpRegs.ulFirstCloseloopflag == 1))
		{
			mCtrl_findhome(&mCtrlRegs);
		}
	}
	if(mCtrlRegs.tcurveRegs.ultcurve_enable == 1)
	{

		mCtrl_Tcurve_Calc(&mCtrlRegs.tcurveRegs);
		mCtrl_ulPcmdUartSet_macro(mCtrlRegs.tcurveRegs.ulStartPcmd+mCtrlRegs.tcurveRegs.lpcmd);
		mCtrlRegs.ulPcmd = mCtrlRegs.ulPcmdUart;
	}


	//limit_protected
	if((mCtrlRegs.commandReceiveEnableFlag == 1) && (mCtrlRegs.homeLimitRegs.limitPosEnable == POSITIVE_LIMIT_ENABLE) && (mCtrlRegs.homeLimitRegs.limitPosRegs.data.dataNew == 1))
	{
		int32 posPosErr;
		if(mCtrlRegs.tcurveRegs.ultcurve_enable == 1)
		{
			if(mCtrlRegs.tcurveRegs.ldistance < 0 )
				posPosErr = 0;
			else
				posPosErr = 1;

		}else
		{
			posPosErr = (int32)mCtrlRegs.ulPcmd - mCtrlRegs.ulPfbk;
		}


		if(posPosErr > 0)
		{

			mCtrlRegs.ulPcmd = mCtrlRegs.ulPfbk;
			mCtrlRegs.ulPcmdUart = mCtrlRegs.ulPcmd;
			mCtrlRegs.tcurveRegs.ultcurve_enable = 0;
			mCtrl_Tcurve_Clear(&mCtrlRegs.tcurveRegs);
			/*switch(mCtrlRegs.mode)
			{
				case CTRLR_MODE_UART	: mCtrlRegs.ulPcmdUart  = mCtrlRegs.ulPcmd;	break;
				case CTRLR_MODE_SPI		: mCtrlRegs.ulPcmdSpi   = mCtrlRegs.ulPcmd;	break;
				default					: mCtrlRegs.ulPcmdUart  = mCtrlRegs.ulPcmd;	break;
			}*/
		}
	}

	if((mCtrlRegs.commandReceiveEnableFlag == 1) && (mCtrlRegs.homeLimitRegs.limitNegEnable == NEGATIVE_LIMIT_ENABLE) && (mCtrlRegs.homeLimitRegs.limitNegRegs.data.dataNew == 1))
	{
		int32 NegPosErr;
		if(mCtrlRegs.tcurveRegs.ultcurve_enable == 1)
		{
			if(mCtrlRegs.tcurveRegs.ldistance > 0 )
				NegPosErr = 0;
			else
				NegPosErr = -1;

		}else
		{
			NegPosErr = (int32)mCtrlRegs.ulPcmd - mCtrlRegs.ulPfbk;
		}

		if(NegPosErr < 0)
		{
			mCtrlRegs.ulPcmd = mCtrlRegs.ulPfbk;
			mCtrlRegs.ulPcmdUart  = mCtrlRegs.ulPcmd;
			mCtrlRegs.tcurveRegs.ultcurve_enable = 0;
			mCtrl_Tcurve_Clear(&mCtrlRegs.tcurveRegs);

			/*switch(mCtrlRegs.mode)
			{
				case CTRLR_MODE_UART	: mCtrlRegs.ulPcmdUart  = mCtrlRegs.ulPcmd;	break;
				case CTRLR_MODE_SPI		: mCtrlRegs.ulPcmdSpi   = mCtrlRegs.ulPcmd;	break;
				default					: mCtrlRegs.ulPcmdUart  = mCtrlRegs.ulPcmd;	break;
			}*/
		}
	}

	//software limit protect

	if((mCtrlRegs.homeLimitRegs.homeFindMode != home_disable) && ((mCtrlRegs.statusRegs.data.homeFinded == 1) && (mDrv_ulAngleCloseFlagGet_macro() == 1)))
	{
		if(mCtrlRegs.homeLimitRegs.softNegLimitEnable == 1)
		{
			if((int32)(mCtrlRegs.ulPcmd - mCtrlRegs.homeLimitRegs.ulPHome) < 0)
			{
				if(((int32)(mCtrlRegs.ulPcmd - mCtrlRegs.homeLimitRegs.ulPHome)) < ((int32)mCtrlRegs.homeLimitRegs.ulSoftNegLimit))
				{
					if(((int32)(mCtrlRegs.ulPfbk - mCtrlRegs.homeLimitRegs.ulPHome)) < ((int32)mCtrlRegs.homeLimitRegs.ulSoftNegLimit))
					{
						if(mCtrlRegs.ulPcmd < ulpcmdold)
							mCtrlRegs.ulPcmd = mCtrlRegs.ulPfbk;

					}else
					{
						mCtrlRegs.ulPcmd = mCtrlRegs.homeLimitRegs.ulPHome + mCtrlRegs.homeLimitRegs.ulSoftNegLimit;
					}

					switch(mCtrlRegs.mode)
					{
						case CTRLR_MODE_UART	: mCtrlRegs.ulPcmdUart  = mCtrlRegs.ulPcmd;	break;

						default					: mCtrlRegs.ulPcmdUart  = mCtrlRegs.ulPcmd;	break;
					}

				}
			}
		}


		if(mCtrlRegs.homeLimitRegs.softPosLimitEnable == 1)
		{
			if((int32)(mCtrlRegs.ulPcmd - mCtrlRegs.homeLimitRegs.ulPHome) > 0)
			{
				if(((int32)(mCtrlRegs.ulPcmd - mCtrlRegs.homeLimitRegs.ulPHome)) > ((int32)mCtrlRegs.homeLimitRegs.ulSoftPosLimit))
				{

					if(((int32)(mCtrlRegs.ulPfbk - mCtrlRegs.homeLimitRegs.ulPHome)) > ((int32)mCtrlRegs.homeLimitRegs.ulSoftPosLimit))
					{
						if(mCtrlRegs.ulPcmd > ulpcmdold)
							mCtrlRegs.ulPcmd = mCtrlRegs.ulPfbk;

					}else
					{
						mCtrlRegs.ulPcmd = mCtrlRegs.homeLimitRegs.ulPHome + mCtrlRegs.homeLimitRegs.ulSoftPosLimit;
					}


					//mCtrlRegs.ulPcmdUart = mCtrlRegs.ulPcmd;

					switch(mCtrlRegs.mode)
					{
						case CTRLR_MODE_UART	: mCtrlRegs.ulPcmdUart  = mCtrlRegs.ulPcmd;	break;

						default					: mCtrlRegs.ulPcmdUart  = mCtrlRegs.ulPcmd;	break;
					}

				}
			}
		}
	}

	ulpcmdold = mCtrlRegs.ulPcmd;

	// emg msd
	mCtrlRegs.emgRegs.ulPcmdIn = mCtrlRegs.ulPcmd;

	mCtrl_emg();
	mCtrlRegs.ulPcmd_emg = mCtrlRegs.emgRegs.ulPcmdOut;

	// Alarm
	if(mCtrlRegs.statusRegs.data.alarm != 0)
	{
		mCtrlRegs.ulPcmd_emg = mCtrlRegs.ulPfbk;
	}

	// motor drive position command update
	mDrv_ulPCmdCtrlrSet_macro(mCtrlRegs.ulPcmd_emg);

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void motorControl_statusUpdate(void)
{
	if( board_encoder_index_happened_read_macro()  && mDataRegs.ulEncoderIndexFlag == false )//(board_encoder_index_happened_read_macro()) && (mDataRegs->ulEncoderIndexFlag == false)
	{

		mDataRegs.ulEncoderIndexFlag = true;

		if(mDrv_ulAngleCloseFlagGet_macro() == 1)
		{

			mDrvRegs.startUpCheckRegs.fEncAngleElec = mDataRegs.fAngleElec;
			mDrvRegs.startUpCheckRegs.fEncAngElecdiff = math_abs_macro(mDrvRegs.startUpCheckRegs.fEncAngleElec -mDrvRegs.startUpCheckRegs.fEncAngleElecold);
			if(mDrvRegs.startUpCheckRegs.fEncAngElecdiff> 0.05f)
			{
				mDrvRegs.startUpCheckRegs.ulEncerrorcnt++;
				if(mDrvRegs.startUpCheckRegs.ulEncerrorcnt>1)
					mDrvRegs.alarmCode.data.encodererror = 1;

			}
			mDrvRegs.startUpCheckRegs.fEncAngleElecold = mDrvRegs.startUpCheckRegs.fEncAngleElec;
		}

		ENC1_PERIPHERAL->CTRL |= 1<<8;
	}

	//// state update
	mCtrlRegs.statusRegs.data.servoReady = mDrv_mDrvAdjustFlagGet_macro();
	mCtrlRegs.statusRegs.data.servoState = mDrv_servoStateGet_macro();
	mCtrlRegs.ulPfbk = mData_ulEncoderPositonDataGet_macro();

	//// alarm
	mDrv_mDrvAlarmfindHomeSet_macro(mCtrlRegs.homeLimitRegs.ulHomeFindAlarm);

	if(mDrv_servoStateGet_macro() == 1)
	{
		mDrv_mDrvAlarmlimitHomeSwitchSet_macro(mCtrlRegs.homeLimitRegs.ulLimitHomeSignalErr);
	}
	else
	{
		mDrv_mDrvWarninglimitHomeSwitchSet_macro(mCtrlRegs.homeLimitRegs.ulLimitHomeSignalErr);
	}

	mCtrlRegs.statusRegs.data.alarm = mDrv_mDrvAlarmFlagGet_macro() || mDrv_mDrvAlarmfindHomeGet_macro() || mDrv_mDrvAlarmlimitHomeSwitchGet_macro();

	//// in position
	int32 iPerr;
	iPerr = mCtrlRegs.ulPcmd - mCtrlRegs.ulPfbk;

	if(((math_abs_macro(iPerr) < mCtrlRegs.ulinPositionRange)) || (mCtrlRegs.statusRegs.data.homeFinded == 0))
	{
		mCtrlRegs.statusRegs.data.inPosition = 1;
	}
	else
	{
		mCtrlRegs.statusRegs.data.inPosition = 0;
	}

	//// zero speed
	if((math_abs_macro(mData_fV_RPMGet_macro()) < mCtrlRegs.fZeroSpeedRange) || (mCtrlRegs.statusRegs.data.homeFinded == 0))
	{
		mCtrlRegs.statusRegs.data.zeroSpeed = 1;
	}
	else
	{
		mCtrlRegs.statusRegs.data.zeroSpeed = 0;
	}

	if(mCtrlRegs.homeLimitRegs.homeFinding == 1)
	{
		mCtrlRegs.statusRegs.data.zeroSpeed  = 0;
		mCtrlRegs.statusRegs.data.inPosition = 0;

	}
	//// home limit
	mCtrlRegs.statusRegs.data.atCCWLimit = mCtrlRegs.homeLimitRegs.limitNegRegs.data.dataNew;
	mCtrlRegs.statusRegs.data.atCWLimit = mCtrlRegs.homeLimitRegs.limitPosRegs.data.dataNew;
	mCtrlRegs.statusRegs.data.atHome = mCtrlRegs.homeLimitRegs.homeRegs.data.dataNew;

	mCtrlRegs.statusServoOn = mCtrlRegs.statusRegs.data.servoState;
	mCtrlRegs.statusAlarm = mCtrlRegs.statusRegs.data.alarm;

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_homeFindingClear(MOTOR_CONTROL_REGS *mCtrlRegs)
{
	if(mCtrlRegs->homeLimitRegs.homeFinding == 1)
	{
		mCtrlRegs->cmdRegs.data.homeFind = 0;

		mCtrlRegs->homeLimitRegs.ulHomeStop = 0;
		mCtrlRegs->homeLimitRegs.ulHomeBack = 0;
		mCtrlRegs->homeLimitRegs.homeFindFailed = 0;

		mCtrlRegs->homeLimitRegs.ulHomeFindState = 0;
		mCtrlRegs->homeLimitRegs.homeFinded = 0;
		mCtrlRegs->homeLimitRegs.homeFinding = 0;
		mCtrlRegs->ulPcmd = mCtrlRegs->ulPfbk;

		mCtrlRegs->statusRegs.data.homeFinding = mCtrlRegs->homeLimitRegs.homeFinding;
		mCtrlRegs->statusRegs.data.homeFinded = mCtrlRegs->homeLimitRegs.homeFinded;
		mCtrlRegs->statusRegs.data.homeFindFailed = mCtrlRegs->homeLimitRegs.homeFindFailed;
	}
}
