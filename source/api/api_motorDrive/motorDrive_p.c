////*****************************************////
//  Name : motorDrive_p.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "motorDrive.h"

void p_init(P_REGS *pRegs)
{

	pRegs->fRef = 0.0F;
	pRegs->fFbk = 0.0F;
	pRegs->fErr = 0.0F;
	pRegs->fKp = 0.0F;
	pRegs->fKd = 0.0F;
	pRegs->fUp = 0.0F;
	pRegs->fUd = 0.0F;

	pRegs->fMax = 0.0F;
	pRegs->fMin = 0.0F;
	pRegs->fOutSat = 0.0F;
	pRegs->fOut = 0.0F;


}

void p(P_REGS *pRegs)
{
	pRegs->fErr = pRegs->fRef - pRegs->fFbk;
	pRegs->fUp = pRegs->fErr * pRegs->fKp;

	pRegs->fOutSat = pRegs->fUp;

	if(pRegs->fOutSat > pRegs->fMax)
	{
		pRegs->fOut = pRegs->fOutSat;
	}
	else if(pRegs->fOutSat < pRegs->fMin)
	{
		pRegs->fOut = pRegs->fOutSat;
	}
	else
	{
		pRegs->fOut = pRegs->fOutSat;
	}
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void p_fixPoint(P_REGS *pRegs)
{

	pRegs->lErr = pRegs->ulRef - pRegs->ulFbk;

	pRegs->fUp = pRegs->lErr * pRegs->fKp;

	pRegs->fOutSat = pRegs->fUp;

	if(pRegs->fOutSat > pRegs->fMax)
	{
		pRegs->fOut = pRegs->fMax;
	}
	else if(pRegs->fOutSat < pRegs->fMin)
	{
		pRegs->fOut = pRegs->fMin;
	}
	else
	{
		pRegs->fOut = pRegs->fOutSat;
	}
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void pd_fixPoint(P_REGS *pRegs)
{
	pRegs->lErr = pRegs->ulRef - pRegs->ulFbk;

	pRegs->fUp = pRegs->lErr * pRegs->fKp;

	pRegs->fUd = pRegs->fKd * (pRegs->lErr -pRegs->lPrevious_Error);

	pRegs->lPrevious_Error = pRegs->lErr;

	pRegs->fOutSat = pRegs->fUp + pRegs->fUd;

	if(pRegs->fOutSat > pRegs->fMax)
	{
		pRegs->fOut = pRegs->fMax;
	}
	else if(pRegs->fOutSat < pRegs->fMin)
	{
		pRegs->fOut = pRegs->fMin;
	}
	else
	{
		pRegs->fOut = pRegs->fOutSat;
	}
}


#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void p_clear(P_REGS *pRegs)
{
	pRegs->fRef = 0.0F;
	pRegs->fFbk = 0.0F;
	pRegs->fErr = 0.0F;
	pRegs->fUp = 0.0F;
	pRegs->fOutSat = 0.0F;
	pRegs->fOut = 0.0F;
}

