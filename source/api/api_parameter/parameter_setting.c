////*****************************************////
//  Name : parameter_setting.c
//  Data : 2022/01
//  Version : 0.0
////*****************************************////

#include "parameter.h"



#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_flashkey(void)
{
	uuint32 ProgramSet;
	uint8 *newProgramInfo;

	device_pwm_pause();

	mCtrlRegs.ulfirmwareflashkey = para_valueGet_macro(PARA_FLASH_KEY);

	if(mCtrlRegs.ulfirmwareflashkey == 0 || mCtrlRegs.ulfirmwareflashkey == 1)
	{

		newProgramInfo = (uint8*)&ProgramSet;

		ProgramSet.dword = mCtrlRegs.ulfirmwareflashkey;

		flexspi_nor_flash_erase_sector(NORFLASH_FLEXSPI, PROGRAM_INFO_SECTOR_START * SECTOR_SIZE);

		flexspi_nor_flash_program(NORFLASH_FLEXSPI, PROGRAM_INFO_SECTOR_START * SECTOR_SIZE, (const uint32_t *)newProgramInfo, 4);

	}

	device_pwm_run();

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_paraMode(void)
{
	para_modeSet_macro(para_valueGet_macro(PARA_SETTING_PARAMODE));
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_saveAll(void)
{
	if(para_valueGet_macro(PARA_SETTING_SAVEALL) != 1) return;

	uint32 ulMemoryWriteCnt;
	uuint32 uulMemoryWriteData;

	device_pwm_pause();

	uint32 paraMode;

	if(para_valueGet_macro(PARA_SETTING_SAVEALL) == 2)
	{
		paraMode = paraRegs.para[PARA_SETTING_PARAMODE].lValue;

		para_readAll();

		paraRegs.para[PARA_SETTING_PARAMODE].lValue = paraMode;
	}

	for(ulMemoryWriteCnt = 0; ulMemoryWriteCnt < MAX_PARAMETER; ulMemoryWriteCnt++)
	{
		uulMemoryWriteData.dword = paraRegs.para[ulMemoryWriteCnt].lValue;

		device_norFlash_SIP_dataMemoryWriteBufferSet_macro((ulMemoryWriteCnt * 4 + 0), uulMemoryWriteData.byte.byte3);
		device_norFlash_SIP_dataMemoryWriteBufferSet_macro((ulMemoryWriteCnt * 4 + 1), uulMemoryWriteData.byte.byte2);
		device_norFlash_SIP_dataMemoryWriteBufferSet_macro((ulMemoryWriteCnt * 4 + 2), uulMemoryWriteData.byte.byte1);
		device_norFlash_SIP_dataMemoryWriteBufferSet_macro((ulMemoryWriteCnt * 4 + 3), uulMemoryWriteData.byte.byte0);
	}

	device_norFlash_SIP_dataMemoryEraseAll();

	device_norFlash_SIP_dataMemoryWriteAll();

	paraRegs.changeFlag = 0;
	paraRegs.updateFlag = 1;

	if(mDrv_mDrvAdjustFlagGet_macro() == true)
	{
		device_pwm_run();
	}
}



#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_reset(void)
{
	if(para_valueGet_macro(PARA_SETTING_RESET) != 1) return;

	device_pwm_pause();

	para_reset_process();

	if(mDrv_mDrvAdjustFlagGet_macro() == true)
	{
		device_pwm_run();
	}
}
