////*****************************************////
//  Name : parameter.c
//  Data : 2020/10
//  Version : 0.0
////*****************************************////

#include "parameter.h"

PARAMETER_REGS paraRegs;

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_setDefault(PARAMETER_REGS *paraRegs, uint32 ulPara);

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_init(void)
{
	int16 iCnt;

	for(iCnt = 0; iCnt < MAX_PARAMETER; iCnt++)
	{
		para_setDefault(&paraRegs, iCnt);
	}
	paraRegs.changeFlag = 0;
	paraRegs.updateFlag = 0;
	paraRegs.servoOnLock = 0;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
int32 para_valueGet(uint32 ulPara)
{
	if(ulPara >= MAX_PARAMETER) return 0;

	if(ulPara == 90) return mDrvRegs.uledmode;
	if(ulPara == 91) return mDrvRegs.uledlevelmax;
	if(ulPara == 92) return mDataRegs.ulDutyLed;
	if(ulPara == 330) return mCtrlRegs.homeLimitRegs.softNegLimitEnable;
	if(ulPara == 331) return mCtrlRegs.homeLimitRegs.lSoftNegLimit;
	if(ulPara == 332) return mCtrlRegs.homeLimitRegs.softPosLimitEnable;
	if(ulPara == 333) return mCtrlRegs.homeLimitRegs.lSoftPosLimit;
	if(ulPara == 22)  return (uint32) 60 * 100000 / mParaRegs.motor.fSpeedMax;

	return paraRegs.para[ulPara].lValue;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_setDefault(PARAMETER_REGS *paraRegs, uint32 ulPara)
{
	paraRegs->para[ulPara].lValue = paraDefault[ulPara].lValue;
	paraRegs->para[ulPara].lValueMax = paraDefault[ulPara].lValueMax;
	paraRegs->para[ulPara].lValueMin = paraDefault[ulPara].lValueMin;
	paraRegs->para[ulPara].sign = paraDefault[ulPara].sign;
	paraRegs->para[ulPara].type = paraDefault[ulPara].type;
	paraRegs->para[ulPara].lock = paraDefault[ulPara].lock;
	paraRegs->para[ulPara].change = paraDefault[ulPara].change;
	paraRegs->para[ulPara].sName = paraDefault[ulPara].sName;
	paraRegs->para[ulPara].pFunc = paraDefault[ulPara].pFunc;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_update(PARAMETER_REGS *paraRegs, uint32 ulPara, int32 lData)
{
	if((mDrv_servoStateGet_macro() == SERVO_STATE_ON) && (paraRegs->para[ulPara].lock == para_servo_on_locked))
		return;

	if(ulPara >= MAX_PARAMETER)
		return;

	if(paraRegs->para[ulPara].change == para_change_reboot)
	{
		paraRegs->servoOnLock = 1;
	}

	if(paraRegs->para[ulPara].type != paraType_ro)
	{
		paraRegs->para[ulPara].lValue = lData;
	}

	if(paraRegs->para[ulPara].type == paraType_wr)
	{
		paraRegs->changeFlag = 1;
		paraRegs->updateFlag = 0;
	}

	paraRegs->para[ulPara].pFunc();

	if(paraRegs->para[ulPara].type == paraType_w_reserved)
	{
		paraRegs->para[ulPara].lValue = 0;
	}

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_reset_process(void)
{
	uint32 ulMemoryWriteCnt;
	uuint32 uulMemoryWriteData;

	// read
	for(ulMemoryWriteCnt = 0; ulMemoryWriteCnt < MAX_PARAMETER; ulMemoryWriteCnt++)
	{
		uulMemoryWriteData.dword = paraDefault[ulMemoryWriteCnt].lValue;

		device_norFlash_SIP_dataMemoryWriteBufferSet_macro((ulMemoryWriteCnt * 4 + 0), uulMemoryWriteData.byte.byte3);
		device_norFlash_SIP_dataMemoryWriteBufferSet_macro((ulMemoryWriteCnt * 4 + 1), uulMemoryWriteData.byte.byte2);
		device_norFlash_SIP_dataMemoryWriteBufferSet_macro((ulMemoryWriteCnt * 4 + 2), uulMemoryWriteData.byte.byte1);
		device_norFlash_SIP_dataMemoryWriteBufferSet_macro((ulMemoryWriteCnt * 4 + 3), uulMemoryWriteData.byte.byte0);
	}

	device_norFlash_SIP_dataMemoryEraseAll();

	device_norFlash_SIP_dataMemoryWriteAll();

	para_readAll();

	paraRegs.changeFlag = 0;
	paraRegs.updateFlag = 1;
}



#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_readAll(void)
{
	uint32 ulMemoryReadCnt;
	uuint32 uulMemoryReadData;

	device_pwm_pause();

	device_norFlash_SIP_dataMemoryReadAll();

	for(ulMemoryReadCnt = 0; ulMemoryReadCnt < MAX_PARAMETER; ulMemoryReadCnt++)
	{
		uulMemoryReadData.byte.byte3 = device_norFlash_SIP_dataMemoryReadBufferGet_macro(ulMemoryReadCnt * 4 + 0);
		uulMemoryReadData.byte.byte2 = device_norFlash_SIP_dataMemoryReadBufferGet_macro(ulMemoryReadCnt * 4 + 1);
		uulMemoryReadData.byte.byte1 = device_norFlash_SIP_dataMemoryReadBufferGet_macro(ulMemoryReadCnt * 4 + 2);
		uulMemoryReadData.byte.byte0 = device_norFlash_SIP_dataMemoryReadBufferGet_macro(ulMemoryReadCnt * 4 + 3);

		para_update_macro(ulMemoryReadCnt, uulMemoryReadData.dword);
	}

	paraRegs.changeFlag = 1;
	paraRegs.updateFlag = 0;

	device_pwm_run();
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_updateAll(PARAMETER_REGS *paraRegs)
{
	// read parameter from flash
	para_readAll();

	uint32 ulDriverNumber;
	uint32 ulFirmwareVersion;

	// read driver hardware information
	ulDriverNumber = device_norFlash_SIP_dataMemoryRead_32bits(PARA_DRIVER_NUMBER);

	// read driver firmware information
	ulFirmwareVersion = device_norFlash_SIP_dataMemoryRead_32bits(PARA_FIRMWARE_VERSION);

	// check flash area blank
	if((ulDriverNumber == 0xFFFFFFFF) || (ulFirmwareVersion == 0xFFFFFFFF))
	{
		// stop pwm
		device_pwm_pause();

		// reset parameter
		para_reset_process();

		// read parameter again
		para_readAll();

		// enable pwm
		device_pwm_run();
	}

	// if parameter not in normal mode, read pararmeter with test mode function
	if(paraRegs->paraMode != paraMode_normal)
	{
		para_updateByMode(paraRegs->paraMode);
	}

	// clear flag after initialization
	paraRegs->servoOnLock = 0;
	paraRegs->changeFlag = 0;
	paraRegs->updateFlag = 0;

}



#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_updateByMode(PARA_MODE paraMode)
{
	// setting by Mode
	switch(paraMode)
	{
		case paraMode_normal: 					break;
		case paraMode_currentTest:				para_updateMode_currentTest();				break;
		case paraMode_currentResponseTest:		para_updateMode_currentResponseTest(); 		break;
		case paraMode_angleTest:				para_updateMode_angleTest();				break;
		case paraMode_speedLoopTest:			para_updateMode_speedLoopTest();			break;
		case paraMode_positionLoopTest:			para_updateMode_positionLoopTest();			break;
		case paraMode_autoFocusSystemDefault:	para_updateMode_autoFocusSystemDefault();	break;
		case paraMode_nosewheelDefault:         para_updateMode_nose_wheelDefault();        break;

		default :								break;
	}
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_updateMode_currentTest(void)
{
	// current test
	// current step response with holding angle
	// test current feedback direction
	para_update_macro(PARA_CTRL_MODE, MOTOR_CTRL_MODE_CURRENT_OPEN_ANGLE_OPEN_STEP);

	para_update_macro(PARA_ID_CMD, 1000);
	para_update_macro(PARA_ID_STEP, 50);
	para_update_macro(PARA_IQ_CMD, 0);
	para_update_macro(PARA_I_KP, 50);
	para_update_macro(PARA_I_KI, 0);


}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_updateMode_currentResponseTest(void)
{
	// current response test
	// current step response with holding angle
	// test current response
	para_update_macro(PARA_CTRL_MODE, MOTOR_CTRL_MODE_CURRENT_CLOSE_ANGLE_OPEN_STEP);
	//motortype
	para_update_macro(PARA_MOTOR_TYPE,MOTOR_SUMFU_ML1513);

	para_update_macro(PARA_ID_CMD, 1000);
	para_update_macro(PARA_ID_STEP, 50);
	para_update_macro(PARA_IQ_CMD, 0);
	para_update_macro(PARA_I_KP, 50);
	para_update_macro(PARA_I_KI, 100);

	//SW
	para_update_macro(PARA_SERVO_ON_MODE, SERVO_ON_MODE_SW);


	para_update_macro(PARA_CTRLR_HOME_MODE,home_disable);
	para_update_macro(PARA_CTRLR_HOME_SPEED, mPara_ulEncoderMaxPulseGet_macro() * 1.0F);

	para_update_macro(PARA_HOME_ENABLE,HOME_LIMIT_DISABLE);
	para_update_macro(PARA_LIMIT_POS_ENABLE,POSITIVE_LIMIT_DISABLE);
	para_update_macro(PARA_LIMIT_NEG_ENABLE,NEGATIVE_LIMIT_DISABLE);



}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_updateMode_angleTest(void)
{
	// angle test
	// current close loop angle open loop with virtual angle increase
	// test angle direction and counter
	para_update_macro(PARA_CTRL_MODE, MOTOR_CTRL_MODE_CURRENT_CLOSE_ANGLE_OPEN);

	//motortype
	para_update_macro(PARA_MOTOR_TYPE,MOTOR_SUMFU_17NE34BF3_300);

	para_update_macro(PARA_ID_CMD, 2000); // 20%
	para_update_macro(PARA_IQ_CMD, 0); // 0%
	para_update_macro(PARA_I_KP, 40); // 1.0
	para_update_macro(PARA_I_KI, 64); // 0.3
	para_update_macro(PARA_V_CMD, 5000); // 100 RPM

	//SW
	para_update_macro(PARA_SERVO_ON_MODE, SERVO_ON_MODE_CTLR);


	//Home
	para_update_macro(PARA_CTRLR_HOME_MODE,home_disable);
	para_update_macro(PARA_CTRLR_HOME_SPEED, mPara_ulEncoderMaxPulseGet_macro() * 1.0F);

	para_update_macro(PARA_HOME_ENABLE,HOME_LIMIT_DISABLE);
	para_update_macro(PARA_LIMIT_POS_ENABLE,POSITIVE_LIMIT_DISABLE);
	para_update_macro(PARA_LIMIT_NEG_ENABLE,NEGATIVE_LIMIT_DISABLE);

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_updateMode_speedLoopTest(void)
{
	// speed loop test
	// speed loop test with acceleration and deceleration
	para_update_macro(PARA_CTRL_MODE, MOTOR_CTRL_MODE_V);

	float32 Vrpm;
	Vrpm = 0.06F;

	para_update_macro(PARA_V_CMD, Vrpm* mPara_ulEncoderMaxPulseGet_macro() / 60); // 1500RPM
	para_update_macro(PARA_V_STEP, 50); // 5s
	para_update_macro(PARA_V_ACC, 100); // 1s
	para_update_macro(PARA_V_DEC, 100); // 1s
	para_update_macro(PARA_V_KP, 500); // 1.0
	para_update_macro(PARA_V_KI, 600); // 0.001

	para_update_macro(PARA_ID_CMD, 2000); // 30%
	para_update_macro(PARA_IQ_CMD, 4000); // 50%
	para_update_macro(PARA_I_KP, 50); // 1.0
	para_update_macro(PARA_I_KI, 100); // 0.001



}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_updateMode_positionLoopTest(void)
{
	// position loop test
	para_update_macro(PARA_CTRL_MODE, MOTOR_CTRL_MODE_P);

	para_update_macro(PARA_CTRLR_IN_POSITION_RANGE,16);
	para_update_macro(PARA_CTRLR_ZERO_SPEED_RANGE,100); // 10 RPM

	para_update_macro(PARA_CTRLR_HOME_MODE,home_noIndex);

	para_update_macro(PARA_CTRLR_HOME_SPEED, 16384);//ENCODER_TYPE_PULSE

	para_update_macro(PARA_CTRLR_MODE,  CTRLR_MODE_UART);

	if(mCtrl_modeGet_macro() == 0)
		para_update_macro(PARA_SERVO_ON_MODE, SERVO_ON_MODE_CTLR);

	para_update_macro(PARA_P_CMD, 333333);

	para_update_macro(PARA_P_KP,40);

	float32 Vrpm;
	Vrpm = 800.0F;
	para_update_macro(PARA_V_CMD, Vrpm* mPara_ulEncoderMaxPulseGet_macro() / 60); // 1500RPM

	para_update_macro(PARA_V_STEP, 50); // 5s
	para_update_macro(PARA_V_ACC, 100); // 1s
	para_update_macro(PARA_V_DEC, 100); // 1s
	para_update_macro(PARA_V_KP, 400); // 1.0
	para_update_macro(PARA_V_KI, 500); // 0.001


	para_update_macro(PARA_ID_CMD, 800); // 50%

	para_update_macro(PARA_IQ_CMD, 3500); // 30%
	para_update_macro(PARA_ID_HOLD, 0); // 30% 1500
	para_update_macro(PARA_I_KP, 100);
	para_update_macro(PARA_I_KI, 200);

	// advance control
	para_update_macro(PARA_ADVCTRL0_ENABLE, 0); // command smooth enable
	para_update_macro(PARA_ADVCTRL0_PARA0, 5);	// command average time

	para_update_macro(PARA_ADVCTRL1_ENABLE, 0);  // command renew enable
	para_update_macro(PARA_ADVCTRL1_PARA0, 500); // range of in position 500 => 0.5 ==> 16*0.5 = 8
	para_update_macro(PARA_ADVCTRL1_PARA1, 80); // 40Khz => 200 => 5ms

	para_update_macro(PARA_ADVCTRL2_ENABLE, 1);  // field weakening enable
	para_update_macro(PARA_ADVCTRL2_PARA0, 8000);
	para_update_macro(PARA_ADVCTRL2_PARA1, 16667);


}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_updateMode_autoFocusSystemDefault(void)
{
	// control type
	para_update_macro(PARA_CTRL_TYPE, MOTOR_CTRL_TYPE_SERVO);

	// controller mode
	para_update_macro(PARA_CTRLR_MODE,  CTRLR_MODE_UART);

	// driver control mode
	para_update_macro(PARA_CTRL_MODE, MOTOR_CTRL_MODE_P);

	// servo on mode
	para_update_macro(PARA_SERVO_ON_MODE, SERVO_ON_MODE_CTLR);

	// motor type
	para_update_macro(PARA_MOTOR_TYPE,MOTOR_SUMFU_17NE34BF3_300);

	// encoder type
	para_update_macro(PARA_ENCODER_TYPE,ENCODER_TYPE_INC_ZERO_ANGLE_SLOW_START);
	para_update_macro(PARA_ENCODER_DIR,ENCODER_DIR_CCW);
	para_update_macro(PARA_ENCODER_RESOLUTION,65536);
	para_update_macro(PARA_ANGLE_OFFSET,0);

	// pulse command
	para_update_macro(PARA_PULSECOMMAND_TYPE,PULSE_COMMAND_TYPE_PULSE_DIR);
	para_update_macro(PARA_PULSECOMMAND_REVERSE, 1);



	// home limit
	para_update_macro(PARA_CTRLR_HOME_MODE,home_noIndex);
	para_update_macro(PARA_CTRLR_HOME_SPEED, mPara_ulEncoderMaxPulseGet_macro() * 5.0F);

	para_update_macro(PARA_HOME_ENABLE,HOME_LIMIT_ENABLE);
	para_update_macro(PARA_LIMIT_POS_ENABLE,POSITIVE_LIMIT_ENABLE);
	para_update_macro(PARA_LIMIT_NEG_ENABLE,NEGATIVE_LIMIT_ENABLE);

	// in position range
	para_update_macro(PARA_CTRLR_IN_POSITION_RANGE,16);

	// zero speed range
	para_update_macro(PARA_CTRLR_ZERO_SPEED_RANGE,100); // 10 RPM


	// position loop parameter
	para_update_macro(PARA_P_CMD, 0);

	para_update_macro(PARA_P_KP,30);


	// speed loop parameter
	float32 Vrpm;
	Vrpm = 900.0F;
	para_update_macro(PARA_V_CMD, Vrpm* mPara_ulEncoderMaxPulseGet_macro() / 60); // 1500RPM

	para_update_macro(PARA_V_STEP, 50); // 5s
	para_update_macro(PARA_V_ACC, 100); // 1s
	para_update_macro(PARA_V_DEC, 100); // 1s

	//Speed Gain
	para_update_macro(PARA_V_INDEX, 0);
	para_update_macro(PARA_V_KP, 330);  // 1.0
	para_update_macro(PARA_V_KI, 350);  // 200000

	para_update_macro(PARA_V_KP1, 330); // 0.9
	para_update_macro(PARA_V_KI1, 350); // 200000

	para_update_macro(PARA_V_KP2, 850); // 0.8
	para_update_macro(PARA_V_KI2, 600); // 200000

	para_update_macro(PARA_V_KP3, 320); // 0.7
	para_update_macro(PARA_V_KI3, 625); // 200000

	para_update_macro(PARA_V_KP4, 280); // 0.6
	para_update_macro(PARA_V_KI4, 714); // 200000

	// current loop parameter
	para_update_macro(PARA_ID_CMD, 0); // 50%
	para_update_macro(PARA_IQ_CMD, 8000); // 30%
	para_update_macro(PARA_ID_HOLD, 800); // 30% 1500

	para_update_macro(PARA_I_KP, 85);
	para_update_macro(PARA_I_KI, 35);

	// voltage limit
	/*Afs: 0.8F */
	mDrv_fIdLoopMaxVdSet_macro(0.9F);
	mDrv_fIdLoopMinVdSet_macro(-0.9F);

	mDrv_Id_pi_fMaxSet_macro(mDrv_fIdLoopMaxVdGet_macro());
	mDrv_Id_pi_fMinSet_macro(mDrv_fIdLoopMinVdGet_macro());

	mDrv_fIqLoopMaxVqSet_macro(0.9F);
	mDrv_fIqLoopMinVqSet_macro(-0.9F);

	mDrv_Iq_pi_fMaxSet_macro(mDrv_fIqLoopMaxVqGet_macro());
	mDrv_Iq_pi_fMinSet_macro(mDrv_fIqLoopMinVqGet_macro());

	// advance control
	para_update_macro(PARA_ADVCTRL0_ENABLE, 0); // command smooth enable
	para_update_macro(PARA_ADVCTRL0_PARA0, 5);	// command average time

	para_update_macro(PARA_ADVCTRL1_ENABLE, 0);  // command renew enable
	para_update_macro(PARA_ADVCTRL1_PARA0, 500); // range of in position 500 => 0.5 ==> 16*0.5 = 8
	para_update_macro(PARA_ADVCTRL1_PARA1, 300); // 40Khz => 200 => 5ms

	para_update_macro(PARA_ADVCTRL2_ENABLE, 0);  // field weakening enable
	para_update_macro(PARA_ADVCTRL2_PARA0, 8000);
	para_update_macro(PARA_ADVCTRL2_PARA1, 16667);


}


#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_updateMode_nose_wheelDefault(void)
{
	// control type
	para_update_macro(PARA_CTRL_TYPE, MOTOR_CTRL_TYPE_SERVO);

	// controller mode
	para_update_macro(PARA_CTRLR_MODE,  CTRLR_MODE_UART);

	// driver control mode
	para_update_macro(PARA_CTRL_MODE, MOTOR_CTRL_MODE_P);

	// servo on mode
	para_update_macro(PARA_SERVO_ON_MODE, SERVO_ON_MODE_CTLR);

	// motor type
	para_update_macro(PARA_MOTOR_TYPE, MOTOR_GHC_S160D);

	// encoder type
	para_update_macro(PARA_ENCODER_TYPE,ENCODER_TYPE_INC_ZERO_START);
	para_update_macro(PARA_ENCODER_DIR,ENCODER_DIR_CCW);
	para_update_macro(PARA_ENCODER_RESOLUTION,61000);
	para_update_macro(PARA_ANGLE_OFFSET,0);

	// pulse command
	para_update_macro(PARA_PULSECOMMAND_TYPE,PULSE_COMMAND_TYPE_PULSE_DIR);
	para_update_macro(PARA_PULSECOMMAND_REVERSE, 1);



	// home limit
	para_update_macro(PARA_CTRLR_HOME_MODE,negative_noIndex);
	para_update_macro(PARA_CTRLR_HOME_SPEED, mPara_ulEncoderMaxPulseGet_macro() * 1.0F);

	para_update_macro(PARA_HOME_ENABLE,HOME_LIMIT_DISABLE);
	para_update_macro(PARA_LIMIT_POS_ENABLE,POSITIVE_LIMIT_DISABLE);
	para_update_macro(PARA_LIMIT_NEG_ENABLE,NEGATIVE_LIMIT_ENABLE);

	//software limit
	para_update_macro(PARA_CTRLR_SOFT_POS_LIMIT_ENABLE,1);
	para_update_macro(PARA_CTRLR_SOFT_POS_LIMIT,110592);


	// in position range
	para_update_macro(PARA_CTRLR_IN_POSITION_RANGE,16);

	// zero speed range
	para_update_macro(PARA_CTRLR_ZERO_SPEED_RANGE,100); // 10 RPM


	// position loop parameter
	para_update_macro(PARA_P_CMD, 0);

	para_update_macro(PARA_P_KP,20);


	// speed loop parameter
	float32 Vrpm;
	Vrpm = 3000.0F;
	para_update_macro(PARA_V_CMD, Vrpm* mPara_ulEncoderMaxPulseGet_macro() / 60); // 1500RPM

	para_update_macro(PARA_V_STEP, 50); // 5s
	para_update_macro(PARA_V_ACC, 100); // 1s
	para_update_macro(PARA_V_DEC, 100); // 1s

	//Speed Gain
	para_update_macro(PARA_V_INDEX, 0);
	para_update_macro(PARA_V_KP, 400);  // 1.0
	para_update_macro(PARA_V_KI, 400);  // 200000

	para_update_macro(PARA_V_KP1, 400); // 0.9
	para_update_macro(PARA_V_KI1, 400); // 200000

	para_update_macro(PARA_V_KP2, 360); // 0.8
	para_update_macro(PARA_V_KI2, 555); // 200000

	para_update_macro(PARA_V_KP3, 320); // 0.7
	para_update_macro(PARA_V_KI3, 625); // 200000

	para_update_macro(PARA_V_KP4, 280); // 0.6
	para_update_macro(PARA_V_KI4, 714); // 200000



	// current loop parameter
	para_update_macro(PARA_ID_CMD, 0); // 50%
	para_update_macro(PARA_IQ_CMD, 5000); // 30%
	para_update_macro(PARA_ID_HOLD, 0); // 30% 1500

	para_update_macro(PARA_I_KP, 20);
	para_update_macro(PARA_I_KI, 64);


	// voltage limit
	/*Afs: 0.8F */
	mDrv_fIdLoopMaxVdSet_macro(0.9F);
	mDrv_fIdLoopMinVdSet_macro(-0.9F);

	mDrv_Id_pi_fMaxSet_macro(mDrv_fIdLoopMaxVdGet_macro());
	mDrv_Id_pi_fMinSet_macro(mDrv_fIdLoopMinVdGet_macro());

	mDrv_fIqLoopMaxVqSet_macro(0.9F);
	mDrv_fIqLoopMinVqSet_macro(-0.9F);

	mDrv_Iq_pi_fMaxSet_macro(mDrv_fIqLoopMaxVqGet_macro());
	mDrv_Iq_pi_fMinSet_macro(mDrv_fIqLoopMinVqGet_macro());


	// advance control
	para_update_macro(PARA_ADVCTRL0_ENABLE, 0); // command smooth enable
	para_update_macro(PARA_ADVCTRL0_PARA0, 5);	// command average time

	para_update_macro(PARA_ADVCTRL1_ENABLE, 0);  // command renew enable
	para_update_macro(PARA_ADVCTRL1_PARA0, 500); // range of in position 500 => 0.5 ==> 16*0.5 = 8
	para_update_macro(PARA_ADVCTRL1_PARA1, 300); // 40Khz => 200 => 5ms

	para_update_macro(PARA_ADVCTRL2_ENABLE, 0);  // field weakening enable
	para_update_macro(PARA_ADVCTRL2_PARA0, 8000);
	para_update_macro(PARA_ADVCTRL2_PARA1, 16667);


}

