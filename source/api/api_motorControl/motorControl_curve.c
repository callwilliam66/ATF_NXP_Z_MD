/*
 * motorControl_curve.c
 *
 *  Created on: Sep 17, 2022
 *      Author: user
 */
#include "motorControl.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_Tcurve_Setting(TCURVE_REGS *tcurveRegs,int32 lpcmd)
{
	if(tcurveRegs->ultcurve_enable == 1)           return;

	float32 fAacc = 0.0F;
	float32 fAdec = 0.0F;
	float32 fVinit = math_abs_macro(tcurveRegs->fVinit);
	float32 fVend = 0;

#if	HOMEMODE == HOMEMODE_ENABLE
	float32 fData;
	float32 fDataAbs;

	fData = para_valueGet_macro(PARA_TCURVE_VMAX) / ( (float32) mPara_ulEncoderMaxPulseGet_macro() ) * 60.0F / mPara_fSpeedMaxGet_macro();

	mDrv_fVCmdParaSet_macro(fData);

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
#endif

	tcurveRegs->ldistance = lpcmd;
	tcurveRegs->uldistance = math_abs_macro(tcurveRegs->ldistance);

	if(tcurveRegs->ldistance >= 0)
	{
		tcurveRegs->fVcmd  = fVinit;
	}else
	{
		tcurveRegs->fVcmd  = -fVinit;
	}

	fAacc = (float32)(tcurveRegs->fVmax - math_abs_macro(fVinit)) / tcurveRegs->ultacc;
	fAdec = (float32)(tcurveRegs->fVmax - math_abs_macro(fVend))  / tcurveRegs->ultdec;

	tcurveRegs->fsm = math_abs_macro(fVinit) * tcurveRegs->ultacc + math_abs_macro(fVend) * tcurveRegs->ultdec;
	tcurveRegs->fsm += math_abs_macro(fAacc) * (tcurveRegs->ultacc * tcurveRegs->ultacc + tcurveRegs->ultacc) / 2;
	tcurveRegs->fsm += math_abs_macro(fAdec) * (tcurveRegs->ultdec * tcurveRegs->ultdec + tcurveRegs->ultdec) / 2;

	if(tcurveRegs->uldistance >= tcurveRegs->fsm)
	{
		tcurveRegs->ulcurveType = TCURVETYPE;

		if(tcurveRegs->ldistance >= 0)
		{
			tcurveRegs->fAacc = fAacc;
			tcurveRegs->fAdec = -fAdec;
		}else
		{
			tcurveRegs->fAacc = -fAacc;
			tcurveRegs->fAdec = fAdec;
		}

		tcurveRegs->ultcc = (tcurveRegs->uldistance - tcurveRegs->fsm) / tcurveRegs->fVmax;
	}else
	{
		tcurveRegs->ulcurveType = DELTACURVETYPE;
		tcurveRegs->fsqrtNum = sqrtf( (2*fVinit + fAacc) * (2*fVinit + fAacc) + 4 * tcurveRegs->uldistance * fAacc);

		if( tcurveRegs->fsqrtNum > 0)
			tcurveRegs->ultmid = (uint32) (-(2*fVinit + fAacc) + tcurveRegs->fsqrtNum) / (2 * fAacc);
		else
			tcurveRegs->ultmid = (uint32) (-(2*fVinit + fAacc) - tcurveRegs->fsqrtNum) / (2 * fAacc);
		if(tcurveRegs->ldistance >= 0)
		{
			tcurveRegs->fAacc = fAacc;
		}else
		{
			tcurveRegs->fAacc = -fAacc;
		}
	}

	tcurveRegs->ultcurve_enable = 1;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_Tcurve_Calc(TCURVE_REGS *tcurveRegs)
{
	if(tcurveRegs->ultcurve_enable == 0 )      			return;

	if(tcurveRegs->ulcurveType == TCURVETYPE)
	{
		if(tcurveRegs->ultime < tcurveRegs->ultacc)
		{
			tcurveRegs->fAcmd = tcurveRegs->fAacc;
		}else if(tcurveRegs->ultime < (tcurveRegs->ultacc + tcurveRegs->ultcc) )
		{
			tcurveRegs->fAcmd = 0;
		}else if(tcurveRegs->ultime < (tcurveRegs->ultacc + tcurveRegs->ultdec + tcurveRegs->ultcc) )
		{
			tcurveRegs->fAcmd = tcurveRegs->fAdec;
		}else
		{
			tcurveRegs->ulfirsthome = 1;
			tcurveRegs->lpcmd = tcurveRegs->ldistance;
			tcurveRegs->ultcurve_enable = 0;
#if  HOMEMODE == HOMEMODE_ENABLE
			float32 fData;
			float32 fDataAbs;

			fData = para_valueGet_macro(PARA_V_CMD) / ( (float32) mPara_ulEncoderMaxPulseGet_macro() ) * 60.0F / mPara_fSpeedMaxGet_macro();

			mDrv_fVCmdParaSet_macro(fData);

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
#endif
			return ;
		}
	}else
	{
		if(tcurveRegs->ultime < tcurveRegs->ultmid)
		{
			tcurveRegs->fAcmd = tcurveRegs->fAacc;
		}else if(tcurveRegs->ultime < 2 * tcurveRegs->ultmid )
		{
			tcurveRegs->fAcmd = -tcurveRegs->fAacc;
		}else
		{
			tcurveRegs->ulfirsthome = 1;
			tcurveRegs->lpcmd = tcurveRegs->ldistance;
			tcurveRegs->ultcurve_enable = 0;
#if HOMEMODE == HOMEMODE_ENABLE
			float32 fData;
			float32 fDataAbs;

			fData = para_valueGet_macro(PARA_V_CMD) / ( (float32) mPara_ulEncoderMaxPulseGet_macro() ) * 60.0F / mPara_fSpeedMaxGet_macro();

			mDrv_fVCmdParaSet_macro(fData);

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
#endif
			return ;
		}
	}

	tcurveRegs->fPcmd = tcurveRegs->fPcmd + tcurveRegs->fVcmd;
	tcurveRegs->fVcmd = tcurveRegs->fVcmd + tcurveRegs->fAcmd;
	tcurveRegs->lpcmd = (int32)tcurveRegs->fPcmd ;

	tcurveRegs->flogPcmd = tcurveRegs->fPcmd;
	tcurveRegs->flogVinit = tcurveRegs->fVcmd;

	tcurveRegs->ultime++;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_Tcurve_parameterUpdate(TCURVE_REGS *tcurveRegs)
{
	if( tcurveRegs->ultcurve_enable ==  0)
	{
		tcurveRegs->fVinit = tcurveRegs->lVinit;
		return;
	}

	tcurveRegs->ultcurve_enable = 0;
	tcurveRegs->fVinit = tcurveRegs->flogVinit;
	tcurveRegs->fPcmd = tcurveRegs->flogPcmd;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_Tcurve_Init(TCURVE_REGS *tcurveRegs)
{

	tcurveRegs->ultmid = 0;
	tcurveRegs->ultcc = 0;
	tcurveRegs->ultime = 0;

	tcurveRegs->fVinit = 0.0F;
	tcurveRegs->lVinit = 0.0F;

	tcurveRegs->fVend = 0.0F;
	tcurveRegs->fAacc = 0.0F;
	tcurveRegs->fAdec = 0.0F;

	tcurveRegs->ldistance = 0;
	tcurveRegs->uldistance = 0;

	tcurveRegs->lpcmd = 0;
	tcurveRegs->fAcmd = 0.0F;
	tcurveRegs->fVcmd = 0.0F;
	tcurveRegs->fPcmd = 0.0F;


	tcurveRegs->fsqrtNum = 0.0F;
	tcurveRegs->fsm = 0.0F;

	tcurveRegs->ulStartPcmd = 0;
	tcurveRegs->ulcurveType = 0;
	tcurveRegs->ultcurve_enable = 0;

	tcurveRegs->ulfirsthome = 0;

	tcurveRegs->flogVinit = 0.0F;
	tcurveRegs->flogPcmd = 0.0F;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_Tcurve_Clear(TCURVE_REGS *tcurveRegs)
{
	tcurveRegs->ultime = 0;
	tcurveRegs->fVcmd = 0.0;
	tcurveRegs->fPcmd = 0.0;
	tcurveRegs->fAcmd = 0.0;
}
