////*****************************************////
//  Name : parameter_cmd.c
//  Data : 2020/10
//  Version : 0.0
////*****************************************////

#include "parameter.h"


// 99999 -> -99999
// unit: pulse
void para_pCmdPara(void)
{
	uint32 ulData;

	ulData = para_valueGet_macro(PARA_P_CMD);

	mDrv_ulPCmdParaSet_macro(ulData);
}

// pulse/s
void para_vCmdPara(void)
{
	float32 fData;
	float32 fDataAbs;

	fData = para_valueGet_macro(PARA_V_CMD) / ((float32)mPara_ulEncoderMaxPulseGet_macro()) * 60.0F / mPara_fSpeedMaxGet_macro();

	mDrv_fVCmdParaSet_macro(fData);

	if( para_valueGet_macro(PARA_V_CMD) <= mCtrlRegs.homeLimitRegs.fHomeFindSpeed * mDrv_ulCtrlBaseFreqGet_macro())
	{
		mCtrlRegs.homeLimitRegs.fHomeFindSpeed = (float32) para_valueGet_macro(PARA_V_CMD) / ((float32)mDrv_ulCtrlBaseFreqGet_macro());
	}else
	{
		mCtrlRegs.homeLimitRegs.fHomeFindSpeed = (float32) para_valueGet_macro(PARA_CTRLR_HOME_SPEED) / ((float32)mDrv_ulCtrlBaseFreqGet_macro());
	}

	if(fData < 0)
	{
		fDataAbs = -fData;
	}
	else
	{
		fDataAbs = fData;
	}

	mDrv_fPLoopMaxVSet_macro(fDataAbs);
	mDrv_fPLoopMinVSet_macro(-fDataAbs);

	mDrv_P_p_fMaxSet_macro(mDrv_fPLoopMaxVGet_macro());
	mDrv_P_p_fMinSet_macro(mDrv_fPLoopMinVGet_macro());
}

// 1000 -> 10.0 => range 0.1 ~ 100
// unit: 0.1s
void para_vCmdStep(void)
{
	float32 fData;

	fData = para_valueGet_macro(PARA_V_STEP) / 10.0F;

	fData = fData * (float32)mDrv_ulCtrlBaseFreqGet_macro() / 	(float32)mDrv_ulV_ctrlCntMaxGet_macro();

	mDrv_ulVCmdStepTimeMaxSet_macro(fData);

}

// 1000 -> 1.0 => range 0.01 ~ 10
// unit: 0.01s
void para_vCmdAcc(void)
{
	float32 fData;

	fData = para_valueGet_macro(PARA_V_ACC) / 100.0F;

	mDrv_fVCmdAccSet_macro(fData);
	mDrv_speedAccDecUpdate_macro();
}

// 1000 -> 1.0 => range 0.01 ~ 10
// unit: 0.01s
void para_vCmdDec(void)
{
	float32 fData;

	fData = para_valueGet_macro(PARA_V_DEC) / 100.0F;

	mDrv_fVCmdDecSet_macro(fData);
	mDrv_speedAccDecUpdate_macro();
}

// 10000 -> 1.0 => range 0.01 ~ 100 %
// unit: 0.01%
void para_iqCmdPara(void)
{
	float32 fData;
	float32 fDataAbs;

	fData = para_valueGet_macro(PARA_IQ_CMD) / 10000.0F;

	if(fData < 0)
	{
		fDataAbs = -fData;
	}
	else
	{
		fDataAbs = fData;
	}

	mDrv_fIqCmdParaSet_macro(fData);

	mDrv_fVLoopMaxISet_macro(fDataAbs);
	mDrv_fVLoopMinISet_macro(-fDataAbs);

	mDrv_V_pi_fMaxSet_macro(mDrv_fVLoopMaxIGet_macro());
	mDrv_V_pi_fMinSet_macro(mDrv_fVLoopMinIGet_macro());

}

// 1000 -> 100 => range 100 ~ 0.1
// unit: 0.001s
void para_iqCmdStep(void)
{
	float32 fData;

	fData = para_valueGet_macro(PARA_IQ_STEP) / 10.0F * 0.001F;

	fData = fData * (float32)mDrv_ulCtrlBaseFreqGet_macro() / 	(float32)mDrv_ulI_ctrlCntMaxGet_macro();

	mDrv_ulIqCmdStepTimeMaxSet_macro(fData);
}

// 10000 -> 1.0 => range 0.1 ~ 100 %
// unit: 0.01%
void para_iqthreshold(void)
{
	float32 fData;

	fData = para_valueGet_macro(PARA_IQ_THRESHOID) / 10000.0F;

	mDrv_fIqThresholdSet_macro(fData);
}



// 10000 -> 1.0 => range 0.1 ~ 100 %
// unit: 0.01%
void para_idCmdPara(void)
{
	float32 fData;

	fData = para_valueGet_macro(PARA_ID_CMD) / 10000.0F;

	mDrv_fIdCmdParaSet_macro(fData);
}

// 1000 -> 100 => range 100 ~ 0.1
// unit: 0.001s
void para_idCmdStep(void)
{
	float32 fData;

	fData = para_valueGet_macro(PARA_ID_STEP) / 10.0F * 0.001F;

	fData = fData * (float32)mDrv_ulCtrlBaseFreqGet_macro() / (float32)mDrv_ulI_ctrlCntMaxGet_macro();

	mDrv_ulIdCmdStepTimeMaxSet_macro(fData);
}

// 10000 -> 1.0 => range 0.1 ~ 20 %
// unit: 1%
void para_idCmdHold(void)
{
	float32 fData;

	fData = para_valueGet_macro(PARA_ID_HOLD) / 10000.0F;

	mDrv_fIdCmdHoldingParaSet_macro(fData);
}
