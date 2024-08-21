 ////*****************************************////
//  Name : motorDrive_dataUpdate.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "motorDrive.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif

void mDrv_dataUpdate(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs)
{
	mDrv_dataUpdate_analog(mDrvRegs,mDataRegs,mParaRegs);

	mDrv_dataUpdate_angle(mDrvRegs,mDataRegs,mParaRegs);

	mDrv_dataUpdate_position(mDrvRegs,mDataRegs,mParaRegs);

	mDrv_dataUpdate_speed(mDrvRegs,mDataRegs,mParaRegs);

	mDrv_dataUpdate_alarmWarning(mDrvRegs,mDataRegs,mParaRegs);

	mDrv_dataUpdate_servo_state(mDrvRegs,mDataRegs,mParaRegs);

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif

void mDrv_dataUpdate_angle(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs)
{
	// qep update

	mDataRegs->ulEncoderAngleNew = board_encoder_angle_read_macro();

	startup(mDrvRegs,mDataRegs,mParaRegs);

	if(mDrvRegs->ulAngleCloseFlag == false)  return;

	mDataRegs->ulEncoderAngleData = mDataRegs->ulEncoderAngleData + (int32)(mDataRegs->ulEncoderAngleNew - mDataRegs->ulEncoderAngleOld);

	if(((int32)mDataRegs->ulEncoderAngleData) < 0)
	{
		mDataRegs->ulEncoderAngleData += mParaRegs->encoder.ulEncoderMaxPulse;
	}

	if(((int32)mDataRegs->ulEncoderAngleData) > mParaRegs->encoder.ulEncoderMaxPulse)
	{
		mDataRegs->ulEncoderAngleData -= mParaRegs->encoder.ulEncoderMaxPulse;
	}

	mDataRegs->ulEncoderAngleOld = mDataRegs->ulEncoderAngleNew;

	//if(board_encoder_index_happened_read_macro() )//(board_encoder_index_happened_read_macro()) && (mDataRegs->ulEncoderIndexFlag == false)
	//{
		/*if(mDrvRegs->ctrlMode == MOTOR_CTRL_MODE_CURRENT_CLOSE_ANGLE_OPEN)
		{
			mDataRegs->ulEncoderIndexFlag = true;
		}
		else if(mDrvRegs->ctrlMode == MOTOR_CTRL_MODE_CURRENT_CLOSE_ANGLE_OPEN_STEP)
		{
			mDataRegs->ulEncoderIndexFlag = false;
		}
		else if(mDrvRegs->ctrlMode == MOTOR_CTRL_MODE_CURRENT_OPEN_ANGLE_OPEN_STEP)
		{
			mDataRegs->ulEncoderIndexFlag = false;
		}
		else
		{
			mDataRegs->ulEncoderIndexFlag = true;
		}
		mDataRegs->ulEncoderZData = board_encoder_angle_read_macro();
		ENC1_PERIPHERAL->CTRL |= 1<<8;
		*/
	//}

	// angle update
	int32 iAngleData;
	float32 fAngleMechData;
	float32 fAngleElecData;

	iAngleData = (int32)mDataRegs->ulEncoderAngleData;
	/*if(mDataRegs->ulEncoderIndexFlag == true)
	{
		iAngleData = (int32)mDataRegs->ulEncoderAngleData + mParaRegs->encoder.ulEncoderIndexOffset;
	}
	else
	{
		iAngleData = (int32)mDataRegs->ulEncoderAngleData;
	}
	*/
	if(iAngleData > mParaRegs->encoder.ulEncoderMaxPulse)
		iAngleData -= mParaRegs->encoder.ulEncoderMaxPulse;
	if(iAngleData < 0)
		iAngleData += mParaRegs->encoder.ulEncoderMaxPulse;


	fAngleMechData = (float32)iAngleData / (float32)mParaRegs->encoder.ulEncoderMaxPulse + mDataRegs->fAngleMechOffset;

	if(fAngleMechData < 0.0F)
	{
		mDataRegs->fAngleMech = fAngleMechData + 1.0F;
	}
	else if(fAngleMechData >= 1.0F)
	{
		mDataRegs->fAngleMech = fAngleMechData - 1.0F;
	}
	else
	{
		mDataRegs->fAngleMech = fAngleMechData;
	}

	fAngleElecData = mDataRegs->fAngleMech * (mParaRegs->motor.ulPoles >> 1);

	mDataRegs->fAngleElec = fAngleElecData - (uint32)(fAngleElecData);


}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif

void mDrv_dataUpdate_position(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs)
{
	//static uint32 dataUpdate_cnt;
	//static uint32 dataUpdate_cnt1;
	// qep data
	mDataRegs->ulEncoderPositonData = board_encoder_position_read_macro();
	mDataRegs->ulEncoderPosition_new = mDataRegs->ulEncoderPositonData;

	/*if(mCtrlRegs.ulpcmd_flag == 1)
	{

		if(mDataRegs->ulEncoderPosition_new == mDataRegs->ulEncoderPosition_old )
		{
			dataUpdate_cnt1++;
		}else
		{
			dataUpdate_cnt1 = 0;
		}
		if(dataUpdate_cnt1>8000)
		{
			mCtrlRegs.ulPfbk = mDataRegs->ulEncoderPositonData;
			mCtrlRegs.homeLimitRegs.ulPcmd = mCtrlRegs.ulPfbk;
			mCtrlRegs.homeLimitRegs.ulPHome = mCtrlRegs.ulPfbk;
			mCtrlRegs.ulPcmdUart = mCtrlRegs.homeLimitRegs.ulPcmd;
			mCtrlRegs.ulPcmdPulse = mCtrlRegs.homeLimitRegs.ulPcmd;
			mCtrlRegs.ulPcmd = mCtrlRegs.homeLimitRegs.ulPcmd;
			mDrvRegs->ulPCmdCtrlr = mCtrlRegs.homeLimitRegs.ulPcmd;
			mCtrlRegs.ulpcmd_flag = 2;
			dataUpdate_cnt1 = 0;
		}
	}else if(mCtrlRegs.ulpcmd_flag == 3)
	{

		if(mDataRegs->ulEncoderPosition_new == mDataRegs->ulEncoderPosition_old )
		{
			dataUpdate_cnt++;
		}else
		{
			dataUpdate_cnt = 0;
		}
		if( dataUpdate_cnt > 8000)
		{
			mCtrlRegs.ulPfbk = mDataRegs->ulEncoderPositonData;
			mCtrlRegs.homeLimitRegs.ulPcmd = mCtrlRegs.ulPfbk;
			mCtrlRegs.homeLimitRegs.ulPHome = mCtrlRegs.ulPfbk;
			mCtrlRegs.ulPcmdUart = mCtrlRegs.homeLimitRegs.ulPcmd;
			mCtrlRegs.ulPcmdPulse = mCtrlRegs.homeLimitRegs.ulPcmd;
			mCtrlRegs.ulPcmd = mCtrlRegs.homeLimitRegs.ulPcmd;
			mDrvRegs->ulPCmdCtrlr = mCtrlRegs.homeLimitRegs.ulPcmd;
			mCtrlRegs.ulpcmd_flag = 4;
			dataUpdate_cnt  = 0;
		}
	}
	*/
	mDataRegs->ulEncoderPosition_old = mDataRegs->ulEncoderPosition_new;


}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mDrv_dataUpdate_speed(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs)
{
	// speed update
	if(mDrvRegs->ulV_ctrlCnt == mDrvRegs->ulV_ctrlCntMax - 1)
	{

		mDrvRegs->speedRegs.uiDataNew = mDataRegs->ulEncoderPositonData;
		speed(&mDrvRegs->speedRegs);

		mDrvRegs->fVfbk = mDrvRegs->speedRegs.fSpeed;
		mDataRegs->fV = mDrvRegs->fVfbk;
		mDataRegs->fV_RPM = mDrvRegs->speedRegs.fSpeed_RPM;

	}
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif

void mDrv_dataUpdate_analog(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs)
{
	// adc update
	uint32 ulAdcTimeOutCnt = 0;

	while(device_adc_status_eoc_get_macro() == false)
	{
		ulAdcTimeOutCnt++;

		if(ulAdcTimeOutCnt >= 3000) // about 5us in 600 MHz
		{
			break;
		}
	}

	device_adc_status_clear_macro();

	// current u v w update
	float32 fIuData;
	//	float32 fIvData;
	float32 fIwData;

	fIuData = board_cur_u_read_macro();
	//	fIvData = board_cur_v_read_macro();
	fIwData = board_cur_w_read_macro();

	mDataRegs->fLedVoltage = board_ldvo_read_macro() * LED_OV_PARAMETER;


	mDataRegs->LPF_IIR_1stOrder_REGS.fDataIn = fIuData;
	mDataRegs->LPF_IIR_1stOrder_REGS.fDataIn1 = fIwData;

	lowPassFilter(&mDataRegs->LPF_IIR_1stOrder_REGS, para_valueGet_macro(PARA_ADVCTRL3_ENABLE));

	mDataRegs->fIu_A = (mDataRegs->LPF_IIR_1stOrder_REGS.fDataOut - mDataRegs->fIuOffset) * mParaRegs->fCurrentGain;
	//	mDataRegs->fIv_A = (fIvData - mDataRegs->fIvOffset) * mParaRegs->fCurrentGain;
	mDataRegs->fIw_A = (mDataRegs->LPF_IIR_1stOrder_REGS.fDataOut1- mDataRegs->fIwOffset) * mParaRegs->fCurrentGain;

	mDataRegs->fIv_A = -mDataRegs->fIu_A - mDataRegs->fIw_A;

	mDataRegs->fIu = mDataRegs->fIu_A * mParaRegs->fCurrentScale;
	//	mDataRegs->fIv = mDataRegs->fIv_A * mParaRegs->fCurrentScale;
	mDataRegs->fIw = mDataRegs->fIw_A * mParaRegs->fCurrentScale;

	mDataRegs->fIv = -mDataRegs->fIu - mDataRegs->fIw;

	mDataRegs->fBusVoltage = board_volt_bus_read_macro() * BUS_VOLTAGE_GAIN;

	mDataRegs->fTemp = board_temp_read_macro();

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif


void mDrv_dataUpdate_alarmWarning(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs)
{
	// alarm clear process
	if(mDrvRegs->alarmClearFlag == true)
	{

		mDrvRegs->alarmClearFlag = false;

		mDrvRegs->alarmFlag = false;
		mDrvRegs->alarmCode.all = 0;
		mCtrlRegs.statusRegs.data.alarm = 0;

		mDrvRegs->warningFlag = false;
		mDrvRegs->warningCode.all = 0;
		mCtrlRegs.statusRegs.data.warning = 0;

		// check over current state
		if((CMP_GetStatusFlags(CMP1_PERIPHERAL) & CMP_SCR_COUT_MASK) == CMP_SCR_COUT_MASK)
		{
			mDrvRegs->alarmCode.data.overCurrent = 1;
			mDrvRegs->alarmFlag = true;
		}
		else
		{
			CMP_ClearStatusFlags(CMP1_PERIPHERAL, CMP_SCR_CFR_MASK);
			CMP_ClearStatusFlags(CMP1_PERIPHERAL, CMP_SCR_CFF_MASK);
			device_pwm_fault_isr_clear();
			mCtrl_cmd_alarm_clrSet_macro(0);
			__NVIC_ClearPendingIRQ(PWM1_FAULT_ERROR_IRQN);
			EnableIRQ(PWM1_FAULT_ERROR_IRQN);
			mDrvRegs->ulAdcAdjustCnt = 0;
			mDrvRegs->adcOffsetFlag = false;
		}
	}

	/// alarm code update

	// over temperature
	mDataRegs->fTemp = board_temp_read_macro();

//	if(mDataRegs->fTemp > TEMP_LIMIT / TEMP_MAX * DRIVER_ADC_RESOLUTION)
//		mDrvRegs->alarmCode.data.overTemperature = 1;

	// over voltage
	if(mDataRegs->fBusVoltage > mParaRegs->fBusVoltageOver)
	{
		mDrvRegs->alarmOverVoltageCnt++;
	}
	else
	{
		mDrvRegs->alarmOverVoltageCnt = 0;
	}

	if(mDrvRegs->alarmOverVoltageCnt >= mDrvRegs->ulCtrlBaseFreq * ALARM_OVERVOLTAGE_TIME_S)
	{
		mDrvRegs->alarmCode.data.overVoltage = 1;
	}

	// over load
	if(mCtrlRegs.statusRegs.data.alarm == 0)
	{
		if(mDrv_overloadCalc(mDrvRegs,mParaRegs,ALARM_OVERLOAD_TIME_S) == 1)
		{
			mDrvRegs->alarmCode.data.overLoad = 1;
		}
	}

	// under voltage
	// trigger warning in servo off state, recover just when voltage back to normal
	// trigger alarm in servo on state, need alarm to clear alarm state
	if(mDrvRegs->servoState == SERVO_STATE_OFF)
	{
		// warning code update
		if(mDataRegs->fBusVoltage < mParaRegs->fBusVoltageUnder)
		{
			if(mDrvRegs->warningUnderVoltageCnt < mDrvRegs->ulCtrlBaseFreq * ALARM_UNDERVOLTAGE_TIME_S)
			{
				mDrvRegs->warningUnderVoltageCnt++;
			}
			else
			{
				mDrvRegs->warningUnderVoltageCnt = mDrvRegs->ulCtrlBaseFreq * ALARM_UNDERVOLTAGE_TIME_S;
			}
		}
		else
		{
			if(mDrvRegs->warningUnderVoltageCnt > 0)
			{
				mDrvRegs->warningUnderVoltageCnt--;
			}
			else
			{
				mDrvRegs->warningUnderVoltageCnt = 0;
			}
		}

		if(mDrvRegs->warningUnderVoltageCnt == 0)
		{
			if((mDrvRegs->warningCode.all == 0x0025) | (mDrvRegs->warningCode.all == 0x0005)) // only under voltage made warning make the warning auto clear
			{
				mDrvRegs->warningClearFlag = true;

			}

			mDrvRegs->warningCode.data.underVoltage = 0;
		}

		if(mDrvRegs->warningUnderVoltageCnt >= mDrvRegs->ulCtrlBaseFreq * ALARM_UNDERVOLTAGE_TIME_S)
		{
			mDrvRegs->warningCode.data.underVoltage = 1;
		}

		mDrvRegs->alarmUnderVoltageCnt = 0;
	}
	else
	{
		if(mDataRegs->fBusVoltage < mParaRegs->fBusVoltageUnder)
		{
			mDrvRegs->alarmUnderVoltageCnt++;
		}
		else
		{
			mDrvRegs->alarmUnderVoltageCnt = 0;
		}

		if(mDrvRegs->alarmUnderVoltageCnt >= mDrvRegs->ulCtrlBaseFreq * ALARM_UNDERVOLTAGE_TIME_S)
		{
			mDrvRegs->alarmCode.data.underVoltage = 1;
		}

		mDrvRegs->warningUnderVoltageCnt = 0;
	}
	//Led mode
	if(mDataRegs->fLedVoltage > 11.0F)
	{
		mDrvRegs->ulOver_Vled = 1;
		mDrvRegs->uledmode = 0;
	}
	else
	{
		mDrvRegs->ulOver_Vled = 0;
	}


	if(mDrvRegs->uledmode == 1)
	{

		if(mDataRegs->ulDutyLed == 0)
		{
			lightdriver_off;
			lightsink_off;
		}
		else
		{
			lightdriver_on;
			lightsink_on;
		}

	}else
	{
		lightdriver_off;
		lightsink_off;
	}
		// alarm flag update
	if(mDrvRegs->alarmCode.all != 0x0000)
	{
		// get alarm
		mDrvRegs->alarmFlag = true;
		mCtrlRegs.statusRegs.data.alarm = 1;
	}

	// warning flag update
	if(mDrvRegs->warningCode.all != 0x0000)
	{
		// get warning
		mDrvRegs->warningFlag = true;
		mCtrlRegs.statusRegs.data.warning = 1;
	}

	// warning code under voltage recover
	if((mDrvRegs->warningClearFlag == true) && (mDrvRegs->warningClearBusyFlag == false))
	{
		mDrvRegs->warningClearFlag = false;

		if(mDrvRegs->alarmCode.data.underVoltage == 1) return;

		mDrvRegs->warningClearBusyFlag = true;
		mDrvRegs->ulAdcAdjustCnt = 0;
		mDrvRegs->adcOffsetFlag = false;
	}

	if((mDrvRegs->warningClearBusyFlag == true) && (mDrvRegs->adcOffsetFlag == true))
	{
		// clear warning flag and finish waring clear process
		mDrvRegs->warningFlag = false;
		mDrvRegs->warningClearFlag = false;
		mDrvRegs->warningClearBusyFlag = false;
		mCtrlRegs.statusRegs.data.warning = 0;

		// clear over current alarm that caused by under voltage warning
		if((CMP_GetStatusFlags(CMP1_PERIPHERAL) & CMP_SCR_COUT_MASK) != CMP_SCR_COUT_MASK)
		{
			CMP_ClearStatusFlags(CMP1_PERIPHERAL, CMP_SCR_CFR_MASK);
			CMP_ClearStatusFlags(CMP1_PERIPHERAL, CMP_SCR_CFF_MASK);
			device_pwm_fault_isr_clear();
			mCtrl_cmd_alarm_clrSet_macro(0);
			__NVIC_ClearPendingIRQ(PWM1_FAULT_ERROR_IRQN);
			EnableIRQ(PWM1_FAULT_ERROR_IRQN);

			mCtrlRegs.homeLimitRegs.ulLimitHomeSignalErr = 0;
			mDrvRegs->warningCode.data.overCurrent = 0;
			mDrvRegs->warningCode.data.limitHomeSwitch = 0;
		}
	}
}


#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mDrv_dataUpdate_servo_state(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs)
{
	if((mDrvRegs->alarmFlag == false) && (mDrvRegs->warningFlag == false))
	{
		switch(mDrvRegs->servoOnMode)
		{
			case SERVO_ON_MODE_CTLR :
				mDrvRegs->servoState = mDrvRegs->servoStateCtrlr;
			break;
			case SERVO_ON_MODE_IO :
				mDrvRegs->servoState = mDrvRegs->servoStateIO;
			break;
			case SERVO_ON_MODE_SW :
				mDrvRegs->servoState = mDrvRegs->servoStateSW;
			break;
			default:
			break;
		}
	}
	else
	{
		mDrvRegs->servoState = SERVO_STATE_OFF;
	}

	if(para_paraServoOnLockGet_macro())
	{
		mDrvRegs->servoState = SERVO_STATE_OFF;
	}
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif

void mDrv_pwmUpdate(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs)
{
	uint32 ulTa_16bits;
	uint32 ulTb_16bits;
	uint32 ulTc_16bits;

	mDataRegs->ulTa = (uint32)(mDataRegs->fTa * 0xFFFFFFFF);
	mDataRegs->ulTb = (uint32)(mDataRegs->fTb * 0xFFFFFFFF);
	mDataRegs->ulTc = (uint32)(mDataRegs->fTc * 0xFFFFFFFF);

	if((mDrvRegs->servoState == SERVO_STATE_OFF) || (mDrvRegs->alarmFlag == true) ||  (mDrvRegs->warningFlag == true))
	{
		ulTa_16bits = 0;
		ulTb_16bits = 0;
		ulTc_16bits = 0;
	}
	else
	{
		ulTa_16bits = mDataRegs->ulTa >> 16;
		ulTb_16bits = mDataRegs->ulTb >> 16;
		ulTc_16bits = mDataRegs->ulTc >> 16;
	}

	device_pwm_update_macro(ulTa_16bits,ulTb_16bits,ulTc_16bits);


	if( mDrvRegs->uledmode == 0 )
	{
		device_pwmL_update_macro(0);
	}
	else
	{
		if( mDataRegs->ulDutyLed > mDrvRegs->uledlevelmax)
		{
			device_pwmL_update_macro(mDrvRegs->uledlevelmax * 6.5535);
		}
		else
		{
			device_pwmL_update_macro(mDataRegs->ulDutyLed * 6.5535);
		}

	}

}


#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(SRAM_DTC)
#endif
void mDrv_paraUpdate(MOTORDRIVE_REGS *mDrvRegs)
{
	// control mode
	mDrvRegs->ctrlMode = 0;

	// servo mode
	mDrvRegs->servoOnMode = 0;

	// position command
	mDrvRegs->ulPCmdPara = 0;

	// speed command
	mDrvRegs->fVCmdPara = 0;

	// current command
	mDrvRegs->fIdCmdPara = 0;
	mDrvRegs->ulIdCmdStepTimeMax = 0;
	mDrvRegs->fIqCmdPara = 0;
	mDrvRegs->ulIqCmdStepTimeMax = 0;

	// max speed
	mDrvRegs->fPLoopMaxV = 0;
	mDrvRegs->fPLoopMinV = 0;

	mDrvRegs->P_pRegs.fMax = mDrvRegs->fPLoopMaxV;
	mDrvRegs->P_pRegs.fMin = mDrvRegs->fPLoopMinV;

	// max current
	mDrvRegs->fVLoopMaxI = 0;
	mDrvRegs->fVLoopMinI = 0;
	mDrvRegs->V_piRegs.fMax = mDrvRegs->fVLoopMaxI;
	mDrvRegs->V_piRegs.fMin = mDrvRegs->fVLoopMinI;

	// max voltage
	mDrvRegs->fIdLoopMaxVd = 1.0F;
	mDrvRegs->fIdLoopMinVd = 1.0F;
	mDrvRegs->Id_piRegs.fMax = mDrvRegs->fIdLoopMaxVd;
	mDrvRegs->Id_piRegs.fMin = mDrvRegs->fIdLoopMaxVd;

	mDrvRegs->fIqLoopMaxVq = 1.0F;
	mDrvRegs->fIqLoopMinVq = 1.0F;
	mDrvRegs->Iq_piRegs.fMax = mDrvRegs->fIqLoopMaxVq;
	mDrvRegs->Iq_piRegs.fMin = mDrvRegs->fIqLoopMaxVq;

	// position control gain
	mDrvRegs->P_pRegs.fKp = 0;

	// speed control gain
	mDrvRegs->V_piRegs.fKp = 0;
	mDrvRegs->V_piRegs.fKi = 0;

	// current control gain
	mDrvRegs->Iq_piRegs.fKp = 0;
	mDrvRegs->Iq_piRegs.fKi = 0;

	mDrvRegs->Id_piRegs.fKp = 0;
	mDrvRegs->Id_piRegs.fKi = 0;

}


#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(SRAM_DTC)
#endif
uint32 mDrv_overloadCalc(MOTORDRIVE_REGS *mDrvRegs,MOTORDRIVE_PARA_REGS *mParaRegs,uint32 sec)
{
	static float32 fCalories_R;
	static uint32 ulOverLoadCnt = 0;


	if(mDrvRegs->servoState == SERVO_STATE_OFF)
	{
		ulOverLoadCnt = 0;
		return 0;
	}


	fCalories_R = 100*(mDrvRegs->fIdCmd*mDrvRegs->fIdCmd + mDrvRegs->fIqCmd*mDrvRegs->fIqCmd);

	if( fCalories_R >  mParaRegs->motor.fCurrentRated * mParaRegs->motor.fCurrentRated)
	{
		ulOverLoadCnt++;
	}
	else
	{
		if(ulOverLoadCnt>0)
			ulOverLoadCnt--;
		else
			ulOverLoadCnt = 0;
	}


	if(ulOverLoadCnt >sec * mDrvRegs->ulCtrlBaseFreq  )
		return 1;
	else
		return 0;

}



#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(SRAM_DTC)
#endif
void mDrv_databuff_Update(MOTORDRIVE_REGS *mDrvRegs ,MOTORDRIVE_DATA_REGS *mDataRegs)
{
	mDataRegs->fdatabuff[0] =  mDataRegs->fIu;
	mDataRegs->fdatabuff[1] =  mDataRegs->fIv;
	mDataRegs->fdatabuff[2] =  mDataRegs->fIw;
	mDataRegs->fdatabuff[3] =  mDataRegs->fAngleVirtual;
	mDataRegs->fdatabuff[4] =  mDataRegs->fAngleElec;
	mDataRegs->fdatabuff[5] =  mDataRegs->fIalpha;
	mDataRegs->fdatabuff[6] =  mDataRegs->fIbeta;
	mDataRegs->fdatabuff[7] =  mDataRegs->fId;
	mDataRegs->fdatabuff[8] =  mDataRegs->fIq;
	mDataRegs->fdatabuff[9] =  mDataRegs->fVd;

	mDataRegs->fdatabuff[10] =  mDataRegs->fVq;
	mDataRegs->fdatabuff[11] =  mDataRegs->fValpha;
	mDataRegs->fdatabuff[12] =  mDataRegs->fVbeta;
	mDataRegs->fdatabuff[13] =  mDataRegs->fVu;
	mDataRegs->fdatabuff[14] =  mDataRegs->fVv;
	mDataRegs->fdatabuff[15] =  mDataRegs->fVw;
	mDataRegs->fdatabuff[16] =  mDataRegs->fTa;
	mDataRegs->fdatabuff[17] =  mDataRegs->fTb;
	mDataRegs->fdatabuff[18] =  mDataRegs->fTc;
	mDataRegs->fdatabuff[19] =  mDataRegs->fV;

	mDataRegs->fdatabuff[20] = mDrvRegs->P_pRegs.fUp;
	mDataRegs->fdatabuff[21] = mDrvRegs->P_pRegs.fOut;
	mDataRegs->fdatabuff[22] = mDrvRegs->V_piRegs.fRef;
	mDataRegs->fdatabuff[23] = mDrvRegs->V_piRegs.fFbk;
	mDataRegs->fdatabuff[24] = mDrvRegs->Id_piRegs.fRef;
	mDataRegs->fdatabuff[25] = mDrvRegs->Id_piRegs.fFbk;

}
