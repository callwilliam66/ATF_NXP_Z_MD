////*****************************************////
//  Name : motorDrive_isr.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "motorDrive.h"


#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void motorDrive_isr(void)
{
	// initialization

	if(mDrvRegs.adjustFlag == false)
	{
		 mDrv_adjust(&mDrvRegs, &mDataRegs);

		 mDrvRegs.servoState = SERVO_STATE_OFF;

		 // servo off clear
		 mDrv_servoOffClear(&mDrvRegs, &mDataRegs);

		 // pwm update
		 mDrv_pwmUpdate(&mDrvRegs, &mDataRegs);

		 // servo on IO control
		 mDrv_servoIO_control(&mDrvRegs);

		 speed_reset(&mDrvRegs.speedRegs, board_encoder_position_read_macro());

		 if(mDrvRegs.adjustFlag == true)
		 {
			 device_pwm_fault_isr_clear();
			 device_pwm_fault_isr_clear();
			 CMP_Enable(CMP1_PERIPHERAL, true);

			 board_encoder_index_happened_clear_macro();

			 mDataRegs.ulEncoderAngleNew = 0;
			 mDataRegs.ulEncoderAngleData = 0;
			 mDataRegs.ulEncoderAngleOld = 0;
		 }

		 return;
	 }

	 if(mDrvRegs.adcOffsetFlag == false)
	 {
		 mDrv_adjust(&mDrvRegs, &mDataRegs);

		 mDrvRegs.servoState = SERVO_STATE_OFF;

		 // servo off clear
		 mDrv_servoOffClear(&mDrvRegs, &mDataRegs);

		 // pwm update
		 mDrv_pwmUpdate(&mDrvRegs, &mDataRegs);

		 // servo on IO control
		 mDrv_servoIO_control(&mDrvRegs);

		 speed_reset(&mDrvRegs.speedRegs, board_encoder_position_read_macro());

		 return;
	 }



	// data update
	mDrv_dataUpdate(&mDrvRegs, &mDataRegs, &mParaRegs);

	// servo offer data clear
	mDrv_servoOffClear(&mDrvRegs, &mDataRegs);

	// control loop state
	mDrv_loopCtrl();

	// control loop
	mDrv_loopPosition(&mDrvRegs, &mDataRegs, &mParaRegs);

	mDrv_loopSpeed(&mDrvRegs, &mDataRegs);

	mDrv_loopCurrent(&mDrvRegs, &mDataRegs, &mParaRegs);

	mDrv_loopVoltage(&mDrvRegs, &mDataRegs, &mParaRegs);

	// pwm update
	mDrv_pwmUpdate(&mDrvRegs, &mDataRegs);

	// servo on IO control
	mDrv_servoIO_control(&mDrvRegs);



	// clear loop flag

	mDrv_loopClear();
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void motorDrive_overCurrent_isr(void)
{
	if(mDrv_servoStateGet_macro() == 1)
	{
		mDrv_mDrvAlarmOverCurrentSet_macro(1);
		mDrv_mDrvAlarmFlagSet_macro(true);
	}
	else
	{
		mDrv_mDrvWarningOverCurrentSet_macro(1);
		mDrv_mDrvWarningFlagSet_macro(true);
	}

	// servo off
	mDrv_servoStateSet_macro(SERVO_STATE_OFF);

	// servo off clear
	mDrv_servoOffClear(&mDrvRegs, &mDataRegs);

	// pwm update
	mDrv_pwmUpdate(&mDrvRegs, &mDataRegs);

	// servo on IO control
	mDrv_servoIO_control(&mDrvRegs);
}
