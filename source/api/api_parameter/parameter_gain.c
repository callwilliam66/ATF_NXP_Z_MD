
////*****************************************////
//  Name : parameter_gain.c
//  Data : 2020/10
//  Version : 0.0
////*****************************************////

#include "parameter.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
// 100000 -> 1.0 => range 0.00001 ~ 1
void para_pKp(void)
{
	float32 fData;

	fData = para_valueGet_macro(PARA_P_KP) / 100000.0F;

	mDrv_P_p_fKpSet_macro(fData);
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_pKd(void)
{
	float32 fData;

	fData = para_valueGet_macro(PARA_P_KD) / 100000.0F;

	mDrv_P_p_fKdSet_macro(fData);
}


#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_pCoefficient(void)
{

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
// 100 -> 1.0 => range 0.01 ~ 100
void para_vKp(void)
{
	float32 fData;

	fData = para_valueGet_macro(PARA_V_KP) / 100.0F;

	mDrv_V_pi_fKpSet_macro(fData);
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
// 100000 -> 1.0 => range 0.00001 ~ 10
void para_vKi(void)
{
	float32 fData;

	fData = para_valueGet_macro(PARA_V_KI) / 100000.0F;

	mDrv_V_pi_fKiSet_macro(fData);
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
// 100 -> 1.0 => range 0.01 ~ 100
void para_vKf(void)
{
	float32 fData;

	fData = para_valueGet_macro(PARA_V_KF) / 100.0F;

	mDrv_V_pi_fKfSet_macro(fData);

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_vRKf(void)
{
	float32 fData;

	fData = para_valueGet_macro(PARA_V_RKF) / 100.0F;

	mDrv_V_pi_fRKfSet_macro(fData);
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
// 100 -> 1.0 => range 0.01 ~ 100
void para_iKp(void)
{
	float32 fData;

	fData = para_valueGet_macro(PARA_I_KP) / 100.0F;

	mDrv_Iq_pi_fKpSet_macro(fData);
	mDrv_Id_pi_fKpSet_macro(fData);
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
// 1000 -> 1.0 => range 0.000 ~ 10
void para_iKi(void)
{
	float32 fData;

	fData = para_valueGet_macro(PARA_I_KI) / 1000.0F;

	mDrv_Iq_pi_fKiSet_macro(fData);
	mDrv_Id_pi_fKiSet_macro(fData);
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_iBw(void)
{
	uint32 fData;

	fData = para_valueGet_macro(PARA_I_BW) / 100000.0F;

	mDrv_Iq_pi_fBwSet_macro(fData);
	mDrv_Id_pi_fBwSet_macro(fData);
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_iTc(void)
{
	float32 fData;

	fData = para_valueGet_macro(PARA_I_TC) / 100000.0F;

	mDrv_Iq_pi_fTcSet_macro(fData);
	mDrv_Id_pi_fTcSet_macro(fData);
}

