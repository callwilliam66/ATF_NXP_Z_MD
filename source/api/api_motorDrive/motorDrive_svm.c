////*****************************************////
//  Name : motorDrive_svm.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "motorDrive.h"

void svm_init(SVM_REGS *svmRegs)
{
	svmRegs->fU = 0.0F;
	svmRegs->fV = 0.0F;
	svmRegs->fW = 0.0F;

	svmRegs->fMax = 0.0F;
	svmRegs->fMin = 0.0F;

	svmRegs->fComm = 0.0F;

	svmRegs->fA = 0.0F;
	svmRegs->fB = 0.0F;
	svmRegs->fC = 0.0F;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void svm(SVM_REGS *svmRegs)
{
	if(svmRegs->fU > svmRegs->fV)
	{
		svmRegs->fMax = svmRegs->fU;
		svmRegs->fMin = svmRegs->fV;
	}
	else
	{
		svmRegs->fMax = svmRegs->fV;
		svmRegs->fMin = svmRegs->fU;
	}

	if(svmRegs->fW > svmRegs->fMax)
	{
		svmRegs->fMax = svmRegs->fW;
	}

	if(svmRegs->fW < svmRegs->fMin)
	{
		svmRegs->fMin = svmRegs->fW;
	}

	svmRegs->fComm = (svmRegs->fMax + svmRegs->fMin) * 0.5F;

	svmRegs->fA = svmRegs->fU - svmRegs->fComm;
	svmRegs->fB = svmRegs->fV - svmRegs->fComm;
	svmRegs->fC = svmRegs->fW - svmRegs->fComm;
}
