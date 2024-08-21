////*****************************************////
//  Name : hmi_isr.c
//  Data : 2021/01
//  Version : 0.0
////*****************************************////

#include "hmi.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void hmi_dac_isr(void)
{
	hmi_aDisp_valueUpdate(&hmi_aDispRegs);
	hmi_aDisp_outputUpdate(&hmi_aDispRegs);

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void hmi_ui_isr(void)
{

}

