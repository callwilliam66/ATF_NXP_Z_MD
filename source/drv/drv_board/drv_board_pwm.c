////*****************************************////
//  Name : drv_board_pwm.c
//  Data : 2021/07
//  Version : 0.0
//  Author : Hill
////*****************************************////
#include "drv_board.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void board_pwm_outputEnableSet(boolen bEnable)
{
	if(bEnable == PWM_ENABLE)
	{
		board_pwm_outputEnable_enable_macro();
	}
	else
	{
		board_pwm_outputEnable_disable_macro();
	}
}
