////*****************************************////
//  Name : motorDrive_motorPara.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "motorDrive.h" 

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mPara_init(MOTORDRIVE_PARA_REGS *mParaRegs)
{
		mParaRegs->driverType = 0;
		mParaRegs->fPower = 0.0F;
		mParaRegs->fILoad = 0.0F;
		mParaRegs->fCurrentGain = (POWERSTAGE_CURRENT_ADC_MAX / (DRIVER_ADC_RESOLUTION / 2.0F));
		mParaRegs->fBusVoltageUnder = UNDER_VOLTAGE/DRIVER_OV_PARAMETER;
		mParaRegs->fBusVoltageOver = OVER_VOLTAGE/DRIVER_OV_PARAMETER;

		mPara_motorTypeConfig(&mParaRegs->motor, MOTOR_SUMFU_ML1513);

		mDrv_fIdLoopMaxVdSet_macro(0.99F);
		mDrv_fIdLoopMinVdSet_macro(-0.99F);

		mDrv_Id_pi_fMaxSet_macro(mDrv_fIdLoopMaxVdGet_macro());
		mDrv_Id_pi_fMinSet_macro(mDrv_fIdLoopMinVdGet_macro());

		mDrv_fIqLoopMaxVqSet_macro(0.99F);
		mDrv_fIqLoopMinVqSet_macro(-0.99F);

		mDrv_Iq_pi_fMaxSet_macro(mDrv_fIqLoopMaxVqGet_macro());
		mDrv_Iq_pi_fMinSet_macro(mDrv_fIqLoopMinVqGet_macro());
}
