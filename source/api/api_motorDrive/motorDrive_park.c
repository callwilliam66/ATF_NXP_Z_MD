////*****************************************////
//  Name : motorDrive_park.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "motorDrive.h"

void park_init(PARK_REGS *parkRegs)
{
	parkRegs->fAlpha = 0.0F;
	parkRegs->fBeta = 0.0F;

	parkRegs->fTheta = 0.0F;
	parkRegs->fSine = 0.0F;
	parkRegs->fCosine = 0.0F;

	parkRegs->fD = 0.0F;
	parkRegs->fQ = 0.0F;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void park_theta(PARK_REGS *parkRegs)
{
	parkRegs->fSine = sinf(parkRegs->fTheta * MATH_TWO_PI);
	parkRegs->fCosine = cosf(parkRegs->fTheta * MATH_TWO_PI);

	parkRegs->fD = parkRegs->fAlpha * parkRegs->fCosine + parkRegs->fBeta * parkRegs->fSine;
	parkRegs->fQ = -parkRegs->fAlpha * parkRegs->fSine + parkRegs->fBeta * parkRegs->fCosine;
}

void park_sinCos(PARK_REGS *parkRegs)
{
	parkRegs->fD = parkRegs->fAlpha * parkRegs->fCosine + parkRegs->fBeta * parkRegs->fSine;
	parkRegs->fQ = -parkRegs->fAlpha * parkRegs->fSine + parkRegs->fBeta * parkRegs->fCosine;
}
