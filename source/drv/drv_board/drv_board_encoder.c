////*****************************************////
//  Name : drv_board_encoder.c
//  Data : 2021/07
//  Version : 0.1
//  Author : Hill
////*****************************************////
#include "drv_board.h"

#include "lib_crc_ext.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void board_encoder_config(uint32 angleCloseMode,boolen bMotorPhaseDir, boolen bEncoderDir)
{
	if(angleCloseMode != 0)
	{
		ENC_Deinit(ENCODER_ANGLE_PERIPHERAL);
		ENC_Init(ENCODER_ANGLE_PERIPHERAL, &stEncoder_config_encoder_zeroAngleCloseMode);
	}

    if(bMotorPhaseDir != bEncoderDir)
    {
    	device_encoder_reverse(ENCODER_ANGLE_PERIPHERAL);
    	device_encoder_reverse(ENCODER_POSITION_PERIPHERAL);
    }
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void board_encoder_enableSet(boolen bEnable)
{
	if(bEnable == ENCODER_ENABLE)
	{
		board_encoder_power_enable_macro();
	}
	else
	{
		board_encoder_power_disable_macro();
	}
}
