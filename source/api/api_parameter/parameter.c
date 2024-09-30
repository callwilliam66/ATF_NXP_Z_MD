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

//	if(ulPara == 60) return (int32) mPara_ulEncoderMaxPulseGet_macro() * mDrvRegs.fVCmdPara * mPara_fSpeedMaxGet_macro() / 60;

	if(ulPara == 90) return mDrvRegs.uledmode;
	if(ulPara == 91) return mDrvRegs.uledlevelmax;
	if(ulPara == 92) return mDataRegs.ulDutyLed;

//	if(ulPara == 311) return mCtrlRegs.homeLimitRegs.fHomeFindSpeed * mDrvRegs.ulCtrlBaseFreq;

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
		default :								break;
	}
}

