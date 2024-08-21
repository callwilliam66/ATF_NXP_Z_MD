////*****************************************////
//  Name : motorDrive_pi.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "motorDrive.h"

void pi_init(PI_REGS *piRegs)
{
	piRegs->fRef = 0.0F;
	piRegs->fFbk = 0.0F;
	piRegs->fErr = 0.0F;
	piRegs->fKp = 0.0F;
	piRegs->fUp = 0.0F;
	piRegs->fInt = 0.0F;
	piRegs->fKi = 0.0F;
	piRegs->fUi = 0.0F;
	piRegs->fMax = 0.0F;
	piRegs->fMin = 0.0F;
	piRegs->fOutSat = 0.0F;
	piRegs->fOut = 0.0F;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif

void pi(PI_REGS *piRegs)
{
	piRegs->fErr = piRegs->fRef - piRegs->fFbk;
	piRegs->fUp = piRegs->fErr * piRegs->fKp;

	piRegs->fInt = piRegs->fInt + piRegs->fErr;
	piRegs->fUi = piRegs->fInt * piRegs->fKp * piRegs->fKi;

	piRegs->fOutSat = piRegs->fUp + piRegs->fUi;

	if(piRegs->fOutSat > piRegs->fMax)
	{
		piRegs->fOut = piRegs->fMax;
		piRegs->fInt = (piRegs->fOut - piRegs->fUp) / (piRegs->fKp * piRegs->fKi);
	}
	else if(piRegs->fOutSat < piRegs->fMin)
	{
		piRegs->fOut = piRegs->fMin;
		piRegs->fInt = (piRegs->fOut - piRegs->fUp) / (piRegs->fKp * piRegs->fKi);
	}
	else
	{
		piRegs->fOut = piRegs->fOutSat;

	}
}


#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif

void pi_advctrl_vloop(PI_REGS *piRegs)
{
		piRegs->fErr = piRegs->fRef - piRegs->fFbk;

		piRegs->fKf = 0;
		int32	lVerrV;
		uint32	ulVerrV;
		float32 fDataStartV;
		float32 fDataEndV;
		float32 fRangeStartV;
		float32 fRangeEndV;
		float32 fDataOutV;

		lVerrV 			= mCtrlRegs.ulPcmd - mCtrlRegs.ulPfbk;
		ulVerrV 		= math_abs_macro(lVerrV);
		fDataStartV 	= 1.0F;
		fDataEndV 		= 0.0F;
		fRangeStartV	= mCtrlRegs.ulinPositionRange * 1.0F;
		fRangeEndV 		= mCtrlRegs.ulinPositionRange * 0.5F;
		fDataOutV 		= 1.0F;

		if(mCtrl_status_homeFindedGet_macro() == 1)
		{
			if(ulVerrV > fRangeStartV)
			{
				fDataOutV = fDataStartV;
			}
			else if(ulVerrV > fRangeEndV)
			{
				fDataOutV = ((float32)ulVerrV - fRangeEndV) / (fRangeStartV  - fRangeEndV) * (fDataStartV - fDataEndV)  + fDataEndV;
			}
			else
			{
				fDataOutV = fDataEndV;
			}
		}
		piRegs->fUp = piRegs->fErr * piRegs->fKp;

		piRegs->fInt += piRegs->fErr * fDataOutV;

		piRegs->fUi = piRegs->fInt * piRegs->fKp * piRegs->fKi;

		piRegs->fUf = piRegs->fRef * piRegs->fKf;

		piRegs->fOutSat = piRegs->fUp + piRegs->fUi + piRegs->fUf - 0.04F;//

		if(piRegs->fOutSat > piRegs->fMax)
		{
			piRegs->fOut = piRegs->fMax;
			piRegs->fInt = (piRegs->fOut - piRegs->fUp - piRegs->fUf + 0.04) / (piRegs->fKp * piRegs->fKi);
		}
		else if(piRegs->fOutSat < piRegs->fMin)
		{
			piRegs->fOut = piRegs->fMin;
			piRegs->fInt = (piRegs->fOut - piRegs->fUp- piRegs->fUf + 0.04 ) / (piRegs->fKp * piRegs->fKi);
		}
		else
		{
			piRegs->fOut = piRegs->fOutSat;
		}

}


#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void pi_vloop_gainset(PI_REGS *piRegs)
{
	switch(piRegs->ulindex)
	{
	case 0:
		piRegs->fKp = piRegs->fKp;
		piRegs->fKi = piRegs->fKi;

		break;
	case 1:
		piRegs->fKp = piRegs->fKp1;
		piRegs->fKi = piRegs->fKi1;
		break;
	case 2:
		piRegs->fKp = piRegs->fKp2;
		piRegs->fKi = piRegs->fKi2;
		break;
	case 3:
		piRegs->fKp = piRegs->fKp3;
		piRegs->fKi = piRegs->fKi3;
		break;
	case 4:
		piRegs->fKp = piRegs->fKp4;
		piRegs->fKi = piRegs->fKi4;
		break;
	default:
		piRegs->fKp = piRegs->fKp;
		piRegs->fKi = piRegs->fKi;
		break;
	}
	para_valueSet_macro(PARA_V_KP,100*piRegs->fKp);
	para_valueSet_macro(PARA_V_KI,100000*piRegs->fKi);
}


#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif

void pi_feed_forward(PI_REGS *piRegs)
{
	piRegs->fErr = piRegs->fRef - piRegs->fFbk;

	piRegs->fUp = piRegs->fErr * piRegs->fKp;

	piRegs->fInt += piRegs->fErr;

	piRegs->fUi = piRegs->fInt * piRegs->fKp * piRegs->fKi;

	piRegs->fUf = piRegs->fRef * piRegs->fKf;

	piRegs->fURf = piRegs->fFbk * piRegs->fRKf * 0.25;

	piRegs->fOutSat = piRegs->fUp + piRegs->fUi + piRegs->fUf - piRegs->fURf;

	if(piRegs->fOutSat > piRegs->fMax)
	{
		piRegs->fOut = piRegs->fMax;
		piRegs->fInt = (piRegs->fOut - piRegs->fUp - piRegs->fUf +  piRegs->fURf) / (piRegs->fKp * piRegs->fKi);
	}
	else if(piRegs->fOutSat < piRegs->fMin)
	{
		piRegs->fOut = piRegs->fMin;
		piRegs->fInt = (piRegs->fOut - piRegs->fUp- piRegs->fUf +  piRegs->fURf) / (piRegs->fKp * piRegs->fKi);
	}
	else
	{
		piRegs->fOut = piRegs->fOutSat;
	}

}



#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void pi_vloop(PI_REGS *piRegs)
{
	piRegs->fErr = piRegs->fRef - piRegs->fFbk;

	piRegs->fUp = piRegs->fErr * piRegs->fKp;

	piRegs->fInt += piRegs->fErr;

	piRegs->fUi = piRegs->fInt * piRegs->fKp * piRegs->fKi;

	piRegs->fUf = piRegs->fRef * piRegs->fKf;

	piRegs->fOutSat = piRegs->fUp + piRegs->fUi + piRegs->fUf;

	if(piRegs->fOutSat > piRegs->fMax)
	{
		piRegs->fOut = piRegs->fMax;
		piRegs->fInt = (piRegs->fOut - piRegs->fUp - piRegs->fUf) / (piRegs->fKp * piRegs->fKi);
	}
	else if(piRegs->fOutSat < piRegs->fMin)
	{
		piRegs->fOut = piRegs->fMin;
		piRegs->fInt = (piRegs->fOut - piRegs->fUp- piRegs->fUf) / (piRegs->fKp * piRegs->fKi);
	}
	else
	{
		piRegs->fOut = piRegs->fOutSat;
	}

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void pi_clear(PI_REGS *piRegs)
{
	piRegs->fRef = 0.0F;
	piRegs->fFbk = 0.0F;
	piRegs->fErr = 0.0F;
	piRegs->fUp = 0.0F;
	piRegs->fInt = 0.0F;
	piRegs->fUi = 0.0F;
	piRegs->fOutSat = 0.0F;
	piRegs->fOut = 0.0F;
}
