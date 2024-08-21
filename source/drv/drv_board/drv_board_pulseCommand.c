////*****************************************////
//  Name : drv_board_pulseCommand.c
//  Data : 2021/07
//  Version : 0.0
//  Author : Hill
////*****************************************////
#include "drv_board.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void board_pulseCommand_config(uint32 uiMode,boolen bReverse)
{
	ENC_Deinit(ENC3_PERIPHERAL);
	ENC_Deinit(ENC4_PERIPHERAL);

	stEncoder_config_pulseCommand_pulseDirMode.enableReverseDirection = bReverse;
	stEncoder_config_pulseCommand_pulseDirMode.enableReverseDirection = bReverse;

	if(uiMode == 0)
	{
		ENC_Init(ENC3_PERIPHERAL, &stEncoder_config_pulseCommand_pulseDirMode);
	}
	else if(uiMode == 1)
	{
		XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicLow, kXBARA1_OutputEnc3PhaseBInput);

		ENC_Init(ENC4_PERIPHERAL, &stEncoder_config_pulseCommand_pulseDirMode);
		ENC_Init(ENC3_PERIPHERAL, &stEncoder_config_pulseCommand_pulseDirMode);
	}
	else if(uiMode == 2)
	{
		ENC_Init(ENC3_PERIPHERAL, &stEncoder_config_pulseCommand_abMode);
	}
}

