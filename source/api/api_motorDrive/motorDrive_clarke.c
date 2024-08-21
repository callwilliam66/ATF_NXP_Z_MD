////*****************************************////
//  Name : motorDrive_clarke.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "motorDrive.h"

void clarke_init(CLARKE_REGS *clarkeRegs)
{
	clarkeRegs->fU = 0.0F;
	clarkeRegs->fV = 0.0F;
	clarkeRegs->fW = 0.0F;

	clarkeRegs->fAlpha = 0.0F;
	clarkeRegs->fBeta = 0.0F;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void clarke(CLARKE_REGS *clarkeRegs)
{
	clarkeRegs->fAlpha = clarkeRegs->fU;
	clarkeRegs->fBeta = (clarkeRegs->fU + 2.0F * clarkeRegs->fV) * MATH_ONE__SQRT3;
}
