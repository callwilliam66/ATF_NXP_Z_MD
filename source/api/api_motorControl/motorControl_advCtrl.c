////*****************************************////
//  Name : motorControl_advCtrl.c
//  Data : 2021/09
//  Version : 0.0
////*****************************************////

#include "motorControl.h"


#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void motorControl_advCtrl_commandRenew(uint32 enable,uint32 para0, uint32 para1, MOTOR_CONTROL_REGS *mCtrlRegs)
{
	if(enable == 0 ||mCtrlRegs->statusRegs.data.homeFinded == 0)
	{
		mCtrlRegs->ulCmdRenewFlag = 0;
		mCtrlRegs->ulCmdRenewCnt = 0;
		return;
	}

	if(mCtrlRegs->ulPcmdUart != mCtrlRegs->ulPcmd)
	{
		mCtrlRegs->ulCmdRenewFlag = 0;
		mCtrlRegs->ulCmdRenewCnt = 0;
	}
	else
	{
		int32	lPerr;
		uint32	ulPerr;
		float32 fRangeStart;

		lPerr 		= mCtrlRegs->ulPcmd-mCtrlRegs->ulPfbk;
		ulPerr 		= math_abs_macro(lPerr);
		fRangeStart	= (float32) mCtrlRegs->ulinPositionRange * (float32)para0 / 1000.0F;

		if(mCtrlRegs->homeLimitRegs.homeFinding == 0)
		{
			/*if(ulPerr < fRangeStart)
			{
				mCtrlRegs->ulCmdRenewCnt++;
			}else
			{
				mCtrlRegs->ulCmdRenewCnt = 0;

				mCtrlRegs->ulCmdRenewFlag = 0;

			}
			// 40kHz  =>  wait time
			if(mCtrlRegs->ulCmdRenewCnt >= para1)
			{
				mCtrlRegs->ulCmdRenewFlag = 1;
			}*/

			if(ulPerr < fRangeStart)
			{
				mCtrlRegs->ulCmdRenewFlag = 1;
			}else
			{
				mCtrlRegs->ulCmdRenewFlag = 0;
			}

		}
	 }
}

