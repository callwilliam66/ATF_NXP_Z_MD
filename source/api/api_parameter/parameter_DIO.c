////*****************************************////
//  Name : parameter_DIO.c
//  Data : 2021/12
//  Version : 0.0
////*****************************************////

#include "parameter.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_dout0(void)
{
	if(para_valueGet_macro(PARA_DOUT0) == 1)
	{
		board_DOUT0_on_macro();
	}else if(para_valueGet_macro(PARA_DOUT0) == 0)
	{
		board_DOUT0_off_macro();
	}
}
