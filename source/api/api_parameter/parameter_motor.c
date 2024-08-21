////*****************************************////
//  Name : parameter_notor.c
//  Data : 2020/10
//  Version : 0.0
////*****************************************////

#include "parameter.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
//////uint32 motorType;
//#define	MOTOR_DEFAULT				0
//#define	MOTOR_MDLV_3M68				1
//#define	MOTOR_SUMFU_17NE34BF3_300	2
//#define	MOTOR_SUMFU_ML1513			3
void para_motorType(void)
{
	mPara_motorTypeSet_macro(para_valueGet_macro(PARA_MOTOR_TYPE));

	mPara_motorTypeConfig_macro(mPara_motorTypeGet_macro());

	mDrv_speedScaleUpdate_macro();

	mPara_fCurrentScaleSet_macro((1.0F / mPara_fCurrentMaxGet_macro()));

	para_vCmdPara();
}
