////*****************************************////
//  Name : parameter_controller.c
//  Data : 2020/10
//  Version : 0.0
////*****************************************////

#include "parameter.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_controllerMode(void)
{
	uint32 ulData;

	ulData = para_valueGet_macro(PARA_CTRLR_MODE);

	mCtrl_modeSet_macro(ulData);
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_controllerHomeMode(void)
{
	uint32 ulData;

	ulData = para_valueGet_macro(PARA_CTRLR_HOME_MODE);

	mCtrl_homeFindModeSet_macro(ulData);

	if(para_valueGet_macro(PARA_HOME_ENABLE) == 1)
	{

	}
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_controllerHomeSpeed(void)
{

	float32 fData;

	fData = (float32)  para_valueGet_macro(PARA_CTRLR_HOME_SPEED)  / ((float32)mDrv_ulCtrlBaseFreqGet_macro());

	if( para_valueGet_macro(PARA_V_CMD) < para_valueGet_macro( PARA_CTRLR_HOME_SPEED) )
	{
		return;
	}

	mCtrl_fHomeFindSpeedSet_macro(fData);
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_controllerHomePos(void)
{
	int32 lData;

	lData = para_valueGet_macro(PARA_CTRLR_HOME_POS);

	mCtrl_homePosSet_macro(lData);

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_controllerInPositionRange(void)
{
	uint32 ulData;
	float32 fData;

	ulData = para_valueGet_macro(PARA_CTRLR_IN_POSITION_RANGE);

	mCtrl_ulInPositionRangeSet_macro(ulData);

	fData = (float32)mCtrlRegs.fZeroSpeedRation * 60 * mCtrlRegs.ulinPositionRange * mDrvRegs.ulCtrlBaseFreq /mDrvRegs.ulV_ctrlCntMax/mParaRegs.encoder.ulEncoderMaxPulse;
	mCtrl_fZeroSpeedRangeSet_macro(fData);
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_controllerZeroSpeedRange(void)
{
	float32 fData;

	fData = para_valueGet_macro(PARA_CTRLR_ZERO_SPEED_RANGE) * 0.01;

	mCtrl_fZeroSpeedRationSet_macro(fData);

	fData = (float32)mCtrlRegs.fZeroSpeedRation * 60 * mCtrlRegs.ulinPositionRange * mDrvRegs.ulCtrlBaseFreq /mDrvRegs.ulV_ctrlCntMax/mParaRegs.encoder.ulEncoderMaxPulse;
	mCtrl_fZeroSpeedRangeSet_macro(fData);
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
//enable 	= 0,
//disable	= 1,
void para_homeEnable(void)
{
	mCtrl_homeEnableSet_macro(para_valueGet_macro(PARA_HOME_ENABLE));
}


#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
//enable 	= 0,
//disable	= 1,
void para_limitPosEnable(void)
{
	mCtrl_limitPosEnableSet_macro(para_valueGet_macro(PARA_LIMIT_POS_ENABLE));
}


#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
//enable 	= 0,
//disable	= 1,
void para_limitNegEnable(void)
{
	mCtrl_limitNegEnableSet_macro(para_valueGet_macro(PARA_LIMIT_NEG_ENABLE));
}


#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
//enable 	= 1,
//disable	= 0,
void para_controllerSoftNegLimitEnable(void)
{

	mCtrl_softNegLimitEnableSet_macro(para_valueGet_macro(PARA_CTRLR_SOFT_NEG_LIMIT_ENABLE));

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_controllerSoftNegLimit(void)
{
	mCtrl_lSoftNegLimitSet_macro(para_valueGet_macro(PARA_CTRLR_SOFT_NEG_LIMIT));
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
//enable 	= 1,
//disable	= 0,
void para_controllerSoftPosLimitEnable(void)
{

	mCtrl_softPosLimitEnableSet_macro(para_valueGet_macro(PARA_CTRLR_SOFT_POS_LIMIT_ENABLE));

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_controllerSoftPosLimit(void)
{
	mCtrl_lSoftPosLimitSet_macro(para_valueGet_macro(PARA_CTRLR_SOFT_POS_LIMIT));
}
