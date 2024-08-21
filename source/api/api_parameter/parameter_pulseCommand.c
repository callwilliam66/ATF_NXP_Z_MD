////*****************************************////
//  Name : parameter_pulseCommand.c
//  Data : 2021/07
//  Version : 0.0
////*****************************************////

#include "parameter.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_pulseCommand_type(void)
{
	mPara_pulseCommandTypeSet_macro(para_valueGet_macro(PARA_PULSECOMMAND_TYPE));
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_pulseCommand_reverse(void)
{
	mPara_pulseCommandReverseSet_macro(para_valueGet_macro(PARA_PULSECOMMAND_REVERSE));
}

