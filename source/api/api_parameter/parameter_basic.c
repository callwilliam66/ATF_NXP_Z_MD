
////*****************************************////
//  Name : parameter_basic.c
//  Data : 2020/10
//  Version : 0.0
////*****************************************////

#include "parameter.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_blank(void)
{
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
//////uint32 ctrlMode;
//#define	MOTOR_CTRL_MODE_P 								0
//#define	MOTOR_CTRL_MODE_V								1
//#define	MOTOR_CTRL_MODE_CURRENT_CLOSE_ANGLE_OPEN		2
//#define	MOTOR_CTRL_MODE_CURRENT_CLOSE_ANGLE_OPEN_STEP	3
//#define	MOTOR_CTRL_MODE_CURRENT_OPEN_ANGLE_OPEN_STEP	4
void para_ctrlMode(void)
{
	mDrv_ctrlModeSet_macro(para_valueGet_macro(PARA_CTRL_MODE));
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
//////uint32 ctrlType;
//#define MOTOR_CTRL_TYPE_SERVO	0
//#define MOTOR_CTRL_TYPE_STEP		1
void para_ctrlType(void)
{
	mDrv_ctrlTypeSet_macro(para_valueGet_macro(PARA_CTRL_TYPE));
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
//////uint32 servoOnMode;
//#define SERVO_ON_MODE_CTLR	0
//#define SERVO_ON_MODE_IO		1
void para_servoOnMode(void)
{
	mDrv_servoOnModeSet_macro(para_valueGet_macro(PARA_SERVO_ON_MODE));
}
