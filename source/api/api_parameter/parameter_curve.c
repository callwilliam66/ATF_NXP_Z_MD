/*
 * parameter_curve.c
 *
 *  Created on: Sep 5, 2022
 *      Author: williamhsu
 */


#include "parameter.h"


void para_tcurve_vinit(void)
{
	float32 fData;

	fData = para_valueGet_macro(PARA_TCURVE_VINIT)/40000;

	mCtrl_lVinitSet_macro(fData);
}

void para_tcurve_vmax(void)
{
	float32 fData;

	fData = (float32)para_valueGet_macro(PARA_TCURVE_VMAX)/40000;

	mCtrl_fVmaxSet_macro(fData);

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_tcurve_vend(void)
{

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_tcurve_tacc(void)
{
	uint32 ulData;

	ulData  = para_valueGet_macro(PARA_TCURVE_TACC);

	mCtrl_ulTaccSet_macro(ulData);

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_tcurve_tdec(void)
{
	uint32 ulData;

	ulData = para_valueGet_macro(PARA_TCURVE_TDEC);

	mCtrl_ulTdecSet_macro(ulData);

}

