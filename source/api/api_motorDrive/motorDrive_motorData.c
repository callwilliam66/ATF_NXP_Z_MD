////*****************************************////
//  Name : motorDrive_motorData.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "motorDrive.h" 

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mData_init(MOTORDRIVE_DATA_REGS *mDataRegs)
{
	mDataRegs->fIuOffset = 2047.0F;
	mDataRegs->fIvOffset = 2047.0F;
	mDataRegs->fIwOffset = 2047.0F;
}
