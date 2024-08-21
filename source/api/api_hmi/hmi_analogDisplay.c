////*****************************************////
//  Name : hmi_analogDisplay.c
//  Data : 2020/10
//  Version : 0.0
////*****************************************////

#include "hmi.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void hmi_aDisp_Clear(HMI_ADISP_REGS *hmi_aDispRegs)
{
	uint32 ulChannelCnt = 0;

	for(ulChannelCnt = 0; ulChannelCnt < HMI_ADISP_CHANNEL_MAX; ulChannelCnt++)
	{
		hmi_aDispRegs->ch[ulChannelCnt].fGain = 1.0F;
		hmi_aDispRegs->ch[ulChannelCnt].fOffset = 0.0F;
		hmi_aDispRegs->ch[ulChannelCnt].fValue = 0.0F;
		hmi_aDispRegs->ch[ulChannelCnt].ulData = 0;
		hmi_aDispRegs->ch[ulChannelCnt].ulValue = 0;
	}
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void hmi_aDisp_outputUpdate(HMI_ADISP_REGS *hmi_aDispRegs)
{
	board_dac_dataUpdate(DAC_CH0, hmi_aDispRegs->ch[0].ulValue);
	board_dac_dataUpdate(DAC_CH1, hmi_aDispRegs->ch[1].ulValue);
	board_dac_dataUpdate(DAC_CH2, hmi_aDispRegs->ch[2].ulValue);
	board_dac_dataUpdate(DAC_CH3, hmi_aDispRegs->ch[3].ulValue);
}


#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void hmi_aDisp_valueUpdate(HMI_ADISP_REGS *hmi_aDispRegs)
{
	uint32 ulChannelCnt = 0;

	for(ulChannelCnt = 0; ulChannelCnt < HMI_ADISP_CHANNEL_MAX; ulChannelCnt++)
	{
		hmi_aDispRegs->ch[ulChannelCnt].fValue = hmi_aDispTable(hmi_aDispRegs->ch[ulChannelCnt].ulData);

		float32 fValue;
		int32 iValue;

		fValue = (hmi_aDispRegs->ch[ulChannelCnt].fValue);

		fValue = fValue * hmi_aDispRegs->ch[ulChannelCnt].fGain - hmi_aDispRegs->ch[ulChannelCnt].fOffset;

		fValue = fValue * 0.5F + 0.5F;

		iValue = fValue * HMI_ADISP_VALUE_MAX;


		if(iValue < 0)
		{
			hmi_aDispRegs->ch[ulChannelCnt].ulValue = 0;
		}
		else if(iValue > HMI_ADISP_VALUE_MAX)
		{
			hmi_aDispRegs->ch[ulChannelCnt].ulValue = HMI_ADISP_VALUE_MAX;
		}
		else
		{
			hmi_aDispRegs->ch[ulChannelCnt].ulValue = iValue;
		}
	}
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void hmi_aDisp_channel_set(HMI_ADISP_REGS *hmi_aDispRegs,uint32 ulChannel,uint32 ulData)
{
	hmi_aDispRegs->ch[ulChannel].ulData = ulData;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void hmi_aDisp_gain_set(HMI_ADISP_REGS *hmi_aDispRegs,uint32 ulChannel,float32 fData)
{
	hmi_aDispRegs->ch[ulChannel].fGain = fData;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void hmi_aDisp_offset_set(HMI_ADISP_REGS *hmi_aDispRegs,uint32 ulChannel,float32 fData)
{
	hmi_aDispRegs->ch[ulChannel].fOffset = fData;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
float32 hmi_aDispTable(uint32 ulChannel)
{
	float32 fValue;

	switch(ulChannel)
	{
		case  AD_HMI_ADISP_TESTDATA        	:	fValue = 0;			break;
		case AD_MCTRLDATA_FTEMP			:  fValue = mData_fTempGet_macro();			break;
		case  AD_MCTRLDATA_FIU          :	fValue = mData_fIuGet_macro();			break;
		case  AD_MCTRLDATA_FIV          :	fValue = mData_fIvGet_macro();			break;
		case  AD_MCTRLDATA_FIW          :	fValue = mData_fIwGet_macro();			break;
		case  AD_MCTRLDATA_FIALPHA      :	fValue = mData_fIalphaGet_macro();		break;
		case  AD_MCTRLDATA_FIBETA       :	fValue = mData_fIbetaGet_macro();		break;
		case  AD_MCTRLDATA_FID          :	fValue = mData_fIdGet_macro();			break;
		case  AD_MCTRLDATA_FIQ          :	fValue = mData_fIqGet_macro();			break;

		case  AD_MCTRLDATA_FVD          :	fValue = mData_fVdGet_macro();			break;
		case  AD_MCTRLDATA_FVQ          :	fValue = mData_fVqGet_macro();			break;
		case  AD_MCTRLDATA_FVALPHA      :	fValue = mData_fValphaGet_macro();		break;
		case  AD_MCTRLDATA_FVBETA       :	fValue = mData_fVbetaGet_macro();		break;
		case  AD_MCTRLDATA_FVU          :	fValue = mData_fVuGet_macro();			break;
		case  AD_MCTRLDATA_FVV          :	fValue = mData_fVvGet_macro();			break;
		case  AD_MCTRLDATA_FVW          :	fValue = mData_fVwGet_macro();			break;

		case  AD_MCTRLDATA_FTA          :	fValue = mData_fTaGet_macro();			break;
		case  AD_MCTRLDATA_FTB          :	fValue = mData_fTbGet_macro();			break;
		case  AD_MCTRLDATA_FTC          :	fValue = mData_fTcGet_macro();			break;

		case  AD_MCTRLDATA_FV           :	fValue = mData_fVGet_macro();			break;

		case  AD_MCTRLDATA_FP           :	fValue = mData_fPGet_macro();			break;

		case  AD_MCTRLDATA_FAANGLEVIRTUAL	:	fValue = mData_fAangleVirtualGet_macro();	break;
		case  AD_MCTRLDATA_FANGLEMECH   :	fValue = mData_fAngleMechGet_macro();	break;
		case  AD_MCTRLDATA_FANGLEELEC   :	fValue = mData_fAngleElecGet_macro();	break;
		case  AD_MCTRLDATA_UVWINDEX 	: 	fValue = mData_UVWindexGet_macro();		break;


		case  AD_MCTRL_FPLOOPMAXV       :	fValue = mDrv_fPLoopMaxVGet_macro();		break;
		case  AD_MCTRL_FPLOOPMINV       :	fValue = mDrv_fPLoopMinVGet_macro();		break;
		case  AD_MCTRL_FPOUT            :	fValue = mDrv_fPOutGet_macro();			break;

		case  AD_MCTRL_FVCMD            :	fValue = mDrv_fVCmdGet_macro();			break;
		case  AD_MCTRL_FVCMDPARA        :	fValue = mDrv_fVCmdParaGet_macro();		break;
		case  AD_MCTRL_FVFBK            :	fValue = mDrv_fVfbkGet_macro();			break;
		case  AD_MCTRL_FVLOOPMAXI       :	fValue = mDrv_fVLoopMaxIGet_macro();		break;
		case  AD_MCTRL_FVLOOPMINI       :	fValue = mDrv_fVLoopMinIGet_macro();		break;
		case  AD_MCTRL_FVOUT            :	fValue = mDrv_fVOutGet_macro();			break;

		case  AD_MCTRL_FIQCMD           :	fValue = mDrv_fIqCmdGet_macro();			break;
		case  AD_MCTRL_FIQCMDPARA       :	fValue = mDrv_fIqCmdParaGet_macro();		break;
		case  AD_MCTRL_FIQFBK           :	fValue = mDrv_fIqfbkGet_macro();			break;
		case  AD_MCTRL_FIQLOOPMAXVQ     :	fValue = mDrv_fIqLoopMaxVqGet_macro();		break;
		case  AD_MCTRL_FIQLOOPMINVQ     :	fValue = mDrv_fIqLoopMinVqGet_macro();		break;
		case  AD_MCTRL_FIQOUT           :	fValue = mDrv_fIqOutGet_macro();			break;

		case  AD_MCTRL_FIDCMD           :	fValue = mDrv_fIdCmdGet_macro();		break;
		case  AD_MCTRL_FIDCMDPARA       :	fValue = mDrv_fIdCmdParaGet_macro();		break;
		case  AD_MCTRL_FIDFBK           :	fValue = mDrv_fIdfbkGet_macro();			break;
		case  AD_MCTRL_FIDLOOPMAXVD     :	fValue = mDrv_fIdLoopMaxVdGet_macro();		break;
		case  AD_MCTRL_FIDLOOPMINVD     :	fValue = mDrv_fIdLoopMinVdGet_macro();		break;
		case  AD_MCTRL_FIDOUT           :	fValue = mDrv_fIdOutGet_macro();			break;

		case  AD_MCTRL_PARK_FALPHA      :	fValue = mDrv_park_fAlphaGet_macro();		break;
		case  AD_MCTRL_PARK_FBETA       :	fValue = mDrv_park_fBetaGet_macro();		break;
		case  AD_MCTRL_PARK_FTHETA      :	fValue = mDrv_park_fThetaGet_macro();		break;
		case  AD_MCTRL_PARK_FSINE       :	fValue = mDrv_park_fSineGet_macro();		break;
		case  AD_MCTRL_PARK_FCOSINE     :	fValue = mDrv_park_fCosineGet_macro();		break;
		case  AD_MCTRL_PARK_FD          :	fValue = mDrv_park_fDGet_macro();			break;
		case  AD_MCTRL_PARK_FQ          :	fValue = mDrv_park_fQGet_macro();			break;

		case  AD_MCTRL_IPARK_FALPHA     :	fValue = mDrv_iPark_fAlphaGet_macro();		break;
		case  AD_MCTRL_IPARK_FBETA      :	fValue = mDrv_iPark_fBetaGet_macro();		break;
		case  AD_MCTRL_IPARK_FTHETA     :	fValue = mDrv_iPark_fThetaGet_macro();		break;
		case  AD_MCTRL_IPARK_FSINE      :	fValue = mDrv_iPark_fSineGet_macro();		break;
		case  AD_MCTRL_IPARK_FCOSINE    :	fValue = mDrv_iPark_fCosineGet_macro();	break;
		case  AD_MCTRL_IPARK_FD         :	fValue = mDrv_iPark_fDGet_macro();			break;
		case  AD_MCTRL_IPARK_FQ         :	fValue = mDrv_iPark_fQGet_macro();			break;

		case  AD_MCTRL_CLARKE_FU        :	fValue = mDrv_clarke_fUGet_macro();		break;
		case  AD_MCTRL_CLARKE_FV        :	fValue = mDrv_clarke_fVGet_macro();		break;
		case  AD_MCTRL_CLARKE_FW        :	fValue = mDrv_clarke_fWGet_macro();		break;
		case  AD_MCTRL_CLARKE_FALPHA    :	fValue = mDrv_clarke_fAlphaGet_macro();	break;
		case  AD_MCTRL_CLARKE_FBETA     :	fValue = mDrv_clarke_fBetaGet_macro();		break;

		case  AD_MCTRL_ICLARKE_FU       :	fValue = mDrv_iClarke_fUGet_macro();		break;
		case  AD_MCTRL_ICLARKE_FV       :	fValue = mDrv_iClarke_fVGet_macro();		break;
		case  AD_MCTRL_ICLARKE_FW       :	fValue = mDrv_iClarke_fWGet_macro();		break;
		case  AD_MCTRL_ICLARKE_FALPHA   :	fValue = mDrv_iClarke_fAlphaGet_macro();	break;
		case  AD_MCTRL_ICLARKE_FBETA    :	fValue = mDrv_iClarke_fBetaGet_macro();	break;

		case  AD_MCTRL_SVM_FU           :	fValue = mDrv_svm_fUGet_macro();			break;
		case  AD_MCTRL_SVM_FV           :	fValue = mDrv_svm_fVGet_macro();			break;
		case  AD_MCTRL_SVM_FW           :	fValue = mDrv_svm_fWGet_macro();			break;
		case  AD_MCTRL_SVM_FA           :	fValue = mDrv_svm_fAGet_macro();			break;
		case  AD_MCTRL_SVM_FB           :	fValue = mDrv_svm_fBGet_macro();			break;
		case  AD_MCTRL_SVM_FC           :	fValue = mDrv_svm_fCGet_macro();			break;

		case  AD_MCTRL_IQ_PI_FREF       :	fValue = mDrv_Iq_pi_fRefGet_macro();		break;
		case  AD_MCTRL_IQ_PI_FFBK       :	fValue = mDrv_Iq_pi_fFbkGet_macro();		break;
		case  AD_MCTRL_IQ_PI_FERR       :	fValue = mDrv_Iq_pi_fErrGet_macro();		break;
		case  AD_MCTRL_IQ_PI_FUP        :	fValue = mDrv_Iq_pi_fUpGet_macro();		break;
		case  AD_MCTRL_IQ_PI_FINT       :	fValue = mDrv_Iq_pi_fIntGet_macro();		break;
		case  AD_MCTRL_IQ_PI_FUI        :	fValue = mDrv_Iq_pi_fUiGet_macro();		break;
		case  AD_MCTRL_IQ_PI_FMAX       :	fValue = mDrv_Iq_pi_fMaxGet_macro();		break;
		case  AD_MCTRL_IQ_PI_FMIN       :	fValue = mDrv_Iq_pi_fMinGet_macro();		break;
		case  AD_MCTRL_IQ_PI_FOUTSAT    :	fValue = mDrv_Iq_pi_fOutSatGet_macro();	break;
		case  AD_MCTRL_IQ_PI_FOUT       :	fValue = mDrv_Iq_pi_fOutGet_macro();		break;

		case  AD_MCTRL_ID_PI_FREF       :	fValue = mDrv_Id_pi_fRefGet_macro();		break;
		case  AD_MCTRL_ID_PI_FFBK       :	fValue = mDrv_Id_pi_fFbkGet_macro();		break;
		case  AD_MCTRL_ID_PI_FERR       :	fValue = mDrv_Id_pi_fErrGet_macro();		break;
		case  AD_MCTRL_ID_PI_FUP        :	fValue = mDrv_Id_pi_fUpGet_macro();		break;
		case  AD_MCTRL_ID_PI_FINT       :	fValue = mDrv_Id_pi_fIntGet_macro();		break;
		case  AD_MCTRL_ID_PI_FUI        :	fValue = mDrv_Id_pi_fUiGet_macro();		break;
		case  AD_MCTRL_ID_PI_FMAX       :	fValue = mDrv_Id_pi_fMaxGet_macro();		break;
		case  AD_MCTRL_ID_PI_FMIN       :	fValue = mDrv_Id_pi_fMinGet_macro();		break;
		case  AD_MCTRL_ID_PI_FOUTSAT    :	fValue = mDrv_Id_pi_fOutSatGet_macro();	break;
		case  AD_MCTRL_ID_PI_FOUT       :	fValue = mDrv_Id_pi_fOutGet_macro();		break;

		case  AD_MCTRL_V_PI_FREF        :	fValue = mDrv_V_pi_fRefGet_macro();		break;
		case  AD_MCTRL_V_PI_FFBK        :	fValue = mDrv_V_pi_fFbkGet_macro();		break;
		case  AD_MCTRL_V_PI_FERR        :	fValue = mDrv_V_pi_fErrGet_macro();		break;
		case  AD_MCTRL_V_PI_FUP         :	fValue = mDrv_V_pi_fUpGet_macro();			break;
		case  AD_MCTRL_V_PI_FINT        :	fValue = mDrv_V_pi_fIntGet_macro();		break;
		case  AD_MCTRL_V_PI_FUI         :	fValue = mDrv_V_pi_fUiGet_macro();		break;
		case  AD_MCTRL_V_PI_FMAX        :	fValue = mDrv_V_pi_fMaxGet_macro();		break;
		case  AD_MCTRL_V_PI_FMIN        :	fValue = mDrv_V_pi_fMinGet_macro();		break;
		case  AD_MCTRL_V_PI_FOUTSAT     :	fValue = mDrv_V_pi_fOutSatGet_macro();		break;
		case  AD_MCTRL_V_PI_FOUT        :	fValue = mDrv_V_pi_fOutGet_macro();		break;

		case  AD_MCTRL_P_P_FREF         :	fValue = mDrv_P_p_fRefGet_macro();			break;
		case  AD_MCTRL_P_P_FFBK         :	fValue = mDrv_P_p_fFbkGet_macro();			break;
		case  AD_MCTRL_P_P_FERR         :	fValue = mDrv_P_p_fErrGet_macro();			break;
		case  AD_MCTRL_P_P_FUP          :	fValue = mDrv_P_p_fUpGet_macro();			break;
		case  AD_MCTRL_P_P_FMAX         :	fValue = mDrv_P_p_fMaxGet_macro();			break;
		case  AD_MCTRL_P_P_FMIN         :	fValue = mDrv_P_p_fMinGet_macro();			break;
		case  AD_MCTRL_P_P_FOUTSAT      :	fValue = mDrv_P_p_fOutSatGet_macro();		break;
		case  AD_MCTRL_P_P_FOUT         :	fValue = mDrv_P_p_fOutGet_macro();			break;

		default							:	fValue = 0;									break;
	}
	return fValue;
}

