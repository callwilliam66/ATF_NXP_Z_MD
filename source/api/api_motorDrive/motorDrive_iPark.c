////*****************************************////
//  Name : motorDrive_iPark.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "motorDrive.h"

void iPark_init(IPARK_REGS *iParkRegs)
{
	iParkRegs->fAlpha = 0.0F;
	iParkRegs->fBeta = 0.0F;

	iParkRegs->fTheta = 0.0F;
	iParkRegs->fSine = 0.0F;
	iParkRegs->fCosine = 0.0F;

	iParkRegs->fD = 0.0F;
	iParkRegs->fQ = 0.0F;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void iPark_theta(IPARK_REGS *iParkRegs)
{
	iParkRegs->fSine = sinf(iParkRegs->fTheta * MATH_TWO_PI);
	iParkRegs->fCosine = cosf(iParkRegs->fTheta * MATH_TWO_PI);

	iParkRegs->fAlpha = iParkRegs->fD * iParkRegs->fCosine - iParkRegs->fQ * iParkRegs->fSine;
	iParkRegs->fBeta = iParkRegs->fD * iParkRegs->fSine + iParkRegs->fQ * iParkRegs->fCosine;
}

void iPark_sinCos(IPARK_REGS *iParkRegs)
{
	iParkRegs->fAlpha = iParkRegs->fD * iParkRegs->fCosine - iParkRegs->fQ * iParkRegs->fSine;
	iParkRegs->fBeta = iParkRegs->fD * iParkRegs->fSine + iParkRegs->fQ * iParkRegs->fCosine;
}
