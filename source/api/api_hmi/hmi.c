////*****************************************////
//  Name : hmi.c
//  Data : 2020/10
//  Version : 0.0
////*****************************************////

#include "hmi.h"

HMI_ADISP_REGS hmi_aDispRegs;

void hmi_init(void)
{
	hmi_aDisp_Clear(&hmi_aDispRegs);
}

