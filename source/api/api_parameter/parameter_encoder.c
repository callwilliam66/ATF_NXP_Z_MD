////*****************************************////
//  Name : parameter_encoder.c
//  Data : 2020/10
//  Version : 0.0
////*****************************************////

#include "parameter.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
//////uint32 encoderDir;
//#define ENCODER_DIR_CW    0
//#define ENCODER_DIR_CCW 	1
void para_encoderDir(void)
{
	mPara_encoderDirSet_macro(para_valueGet_macro(PARA_ENCODER_DIR));
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
//////uint32 ulEncoderType;
//#define ENCODER_TYPE_INC 				0 // A B Z
//#define ENCODER_TYPE_INC_UVW 			1 // A B Z U V W
//#define ENCODER_TYPE_SERIAL_INC		2 // serial
//#define ENCODER_TYPE_SERIAL_INC_UVW	3 // serial
void para_encoderType(void)
{
	mPara_encoderTypeSet_macro(para_valueGet_macro(PARA_ENCODER_TYPE));
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif


void para_encoderResolution(void)
{
	uint32 ulData;
	float32 fData;
	ulData = para_valueGet_macro(PARA_ENCODER_RESOLUTION);

	mPara_ulEncoderMaxPulseSet_macro(ulData);
	mDrv_speedScaleUpdate_macro();
	para_vCmdPara();

	fData = (float32) mCtrlRegs.fZeroSpeedRation * 60 * mCtrlRegs.ulinPositionRange * mDrvRegs.ulCtrlBaseFreq /mDrvRegs.ulV_ctrlCntMax/mParaRegs.encoder.ulEncoderMaxPulse;
	mCtrl_fZeroSpeedRangeSet_macro(fData);
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
// 10000 -> 1.0 => range 0.01 ~ 100 %
void para_angleOffset(void)
{
	uint32 ulData;

	ulData = para_valueGet_macro(PARA_ANGLE_OFFSET);

	mPara_ulEncoderIndexOffsetSet_macro(ulData);

}



