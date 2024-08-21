////*****************************************////
//  Name : motorDrive_servo.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "motorDrive.h" 

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif

void mDrv_servoIO_control(MOTORDRIVE_REGS *mDrvRegs)
{
	// if there is alarm happened, disable pwm output.
	if(mDrvRegs->alarmFlag != 0)
	{
		board_pwm_outputEnableSet(PWM_DISABLE);
		return;
	}

	if(mDrvRegs->warningFlag != 0)
	{
		board_pwm_outputEnableSet(PWM_DISABLE);
		return;
	}

	if(mDrvRegs->servoState == SERVO_STATE_OFF)
	{
		board_pwm_outputEnableSet(PWM_DISABLE);
		return;
	}

	if(mDrvRegs->servoState == SERVO_STATE_ON)
	{
		board_pwm_outputEnableSet(PWM_ENABLE);
		return;
	}
}


#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mDrv_servoOffClear(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs)
{
	if(mDrvRegs->servoState == SERVO_STATE_OFF)
	{
		mDrvRegs->ulP_ctrlCnt = 0;
		mDrvRegs->ulV_ctrlCnt = 0;
		mDrvRegs->ulI_ctrlCnt = 0;

		mDrvRegs->fPFbk = 0.0F;
		mDrvRegs->fPOut = 0.0F;

		mDrvRegs->ulVCmdStepTime = 0;
		mDrvRegs->fVfbk = 0.0F;
		mDrvRegs->fVOut = 0.0F;

		mDrvRegs->ulIqCmdStepTime = 0;
		mDrvRegs->fIqfbk = 0.0F;
		mDrvRegs->fIqOut = 0.0F;

		mDrvRegs->ulIdCmdStepTime = 0;
		mDrvRegs->fIdfbk = 0.0F;
		mDrvRegs->fIdOut = 0.0F;

		p_clear(&mDrvRegs->P_pRegs);

		pi_clear(&mDrvRegs->V_piRegs);

		pi_clear(&mDrvRegs->Id_piRegs);
		pi_clear(&mDrvRegs->Iq_piRegs);

		mDataRegs->fVd = 0.0F;
		mDataRegs->fVq = 0.0F;
		mDataRegs->fValpha = 0.0F;
		mDataRegs->fVbeta = 0.0F;
		mDataRegs->fVu = 0.0F;
		mDataRegs->fVv = 0.0F;
		mDataRegs->fVw = 0.0F;

		mDataRegs->fTa = 0.0F;
		mDataRegs->fTb = 0.0F;
		mDataRegs->fTc = 0.0F;
		mDataRegs->ulTa = 0;
		mDataRegs->ulTb = 0;
		mDataRegs->ulTc = 0;

		mDrvRegs->ulPFbkServoOff = mDataRegs->ulEncoderPositonData;

		switch(mDrvRegs->ctrlMode)
		{
			case MOTOR_CTRL_MODE_P :
				mDrvRegs->ulPCmd = mDrvRegs->ulPCmdCtrlr;
			break;
			case MOTOR_CTRL_MODE_P_TEST :
				mDrvRegs->ulPCmd = mDataRegs->ulEncoderPositonData;
			break;
			default :
				mDrvRegs->ulPCmd = mDrvRegs->ulPCmdCtrlr;
			break;
		}

		mDrvRegs->ulPCmdServoOff = mDrvRegs->ulPCmd;

		mDrvRegs->ulPCmdOld = mDrvRegs->ulPCmd;

	}
}

