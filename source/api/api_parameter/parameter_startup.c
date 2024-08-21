////*****************************************////
//  Name : parameter_startup.c
//  Data : 2022/01
//  Version : 0.0
////*****************************************////

#include "parameter.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_startUpMethod(void)
{
	mDrv_mDrvStartUpMethodSet_macro(para_valueGet_macro(PARA_STATUP_METHOD));
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_startUpStartAngle(void)
{
	float32 fData;

	fData = para_valueGet_macro(PARA_STATUP_START_ANGLE) / 360.0F;

	mDrv_startup_fStartAngleSet_macro(fData);

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_startUpMoveTime(void)
{
	float32 fData;

	fData = para_valueGet_macro(PARA_STATUP_MOVE_TIME) * ISR_FREQ_PWM / 1000;

	mDrv_startup_ulHoldCntMaxSet_macro(fData);
	mDrv_startup_ulCheckCntMaxSet_macro(fData);
	mDrv_startup_ulFinishCntMaxSet_macro(fData);
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_startUpCheckAngle(void)
{
	float32 fData;

	fData = para_valueGet_macro(PARA_STATUP_CHECK_ANGLE) / 360.0F;

	mDrv_startup_fCheckAngleSet_macro(fData);
}
