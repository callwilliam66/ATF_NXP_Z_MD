////*****************************************////
//  Name : drv_board.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "drv_board.h"

void drv_board_init(void)
{
	board_pwm_outputEnableSet(PWM_DISABLE);
}
