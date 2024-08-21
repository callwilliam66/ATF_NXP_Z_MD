////*****************************************////
//  Name : motorDrive_accDec.c
//  Data : 2020/10
//  Version : 0.0
////*****************************************////

#include "motorDrive.h"

void accDec_init(ACCDEC_REGS *accDecRegs)
{
	accDecRegs->fDataIn = 0;
	accDecRegs->fAcc = 0;
	accDecRegs->fDec = 0;
	accDecRegs->fDataOut = 0;
}

void accDec_accDecUpdate(ACCDEC_REGS *accDecRegs, float32 fFreq, float32 fAccTime, float32 fDecTime)
{
	if(fAccTime != 0)
	{
		accDecRegs->fAcc = 1.0F / fAccTime / fFreq;
	}
	else
	{
		accDecRegs->fAcc = 0;
	}

	if(fDecTime != 0)
	{
		accDecRegs->fDec = 1.0F / fDecTime / fFreq;
	}
	else
	{
		accDecRegs->fDec = 0;
	}
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void accDec(ACCDEC_REGS *accDecRegs)
{
	if(accDecRegs->fDataIn == accDecRegs->fDataOut) return;

	uint32 ulAccDec;
	float32 fDataInSign;
	float32 fDataInValue;
	float32 fDataOutSign;
	float32 fDataOutValue;

	if(accDecRegs->fDataIn >= 0)
	{
		fDataInSign = 1;
		fDataInValue = accDecRegs->fDataIn;
	}
	else
	{
		fDataInSign = -1;
		fDataInValue = -accDecRegs->fDataIn;
	}

	if(accDecRegs->fDataOut >= 0)
	{
		fDataOutSign = 1;
		fDataOutValue = accDecRegs->fDataOut;
	}
	else
	{
		fDataOutSign = -1;
		fDataOutValue = -accDecRegs->fDataOut;
	}

	if(fDataInSign * fDataOutSign < 0)
	{
		ulAccDec = 0;
	}
	else
	{
		if(fDataInValue < fDataOutValue)
		{
			ulAccDec = 0;
		}
		else
		{
			ulAccDec = 1;
		}
	}

	if(fDataOutValue == 0)
	{
		ulAccDec = 1;
	}

	if(ulAccDec == 1) // acceleration
	{
		fDataOutSign = fDataInSign;

		if(accDecRegs->fAcc == 0)
		{
			fDataOutValue = fDataInValue;
		}
		else
		{
			fDataOutValue = fDataOutValue + accDecRegs->fAcc;

			if(fDataOutValue > fDataInValue) // limit
			{
				fDataOutValue = fDataInValue;
			}
		}
	}
	else // deceleration
	{

		if(accDecRegs->fDec == 0)
		{
			fDataOutValue = 0;
		}
		else
		{
			fDataOutValue = fDataOutValue - accDecRegs->fDec;

			if(fDataOutValue < 0) // cross zero stop
			{
				fDataOutSign = 0;

				fDataOutValue = 0;
			}
		}
	}

	accDecRegs->fDataOut = fDataOutValue * fDataOutSign;
}
