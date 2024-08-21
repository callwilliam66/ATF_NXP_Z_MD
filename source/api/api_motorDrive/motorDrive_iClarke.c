////*****************************************////
//  Name : motorDrive_iClarke.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "motorDrive.h"

void iClarke_init(ICLARKE_REGS *iClarkeRegs)
{
	iClarkeRegs->fU = 0.0F;
	iClarkeRegs->fV = 0.0F;
	iClarkeRegs->fW = 0.0F;

	iClarkeRegs->fAlpha = 0.0F;
	iClarkeRegs->fBeta = 0.0F;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void iClarke(ICLARKE_REGS *iClarkeRegs)
{
	iClarkeRegs->fU = iClarkeRegs->fAlpha;
	iClarkeRegs->fV = -iClarkeRegs->fAlpha *0.5F + iClarkeRegs->fBeta * MATH_SQRT3__TWO;
	iClarkeRegs->fW = -iClarkeRegs->fAlpha *0.5F - iClarkeRegs->fBeta * MATH_SQRT3__TWO;
}
