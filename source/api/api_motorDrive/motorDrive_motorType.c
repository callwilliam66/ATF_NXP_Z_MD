/*
 * motorDrive_define_motorType.c
 *
 *  Created on: Jun 24, 2021
 *      Author: williamhsu
 */
#include "motorDrive.h"

const PARA_MOTOR_REGS paraMotor_default =
{
	0,	//uint32 motorType;
	0,	//uint32 ulPoles;
	MOTOR_PHASE_DIR_CW,	//uint32 motorPhaseDir;

	0.0F,	//float32 fSpeedRated;
	0.0F,	//float32 fSpeedMax;
	0.0F,	//float32 fCurrentRated;
	0.0F,	//float32 fCurrentMax;

	0.0F,	//float32 fKe;
	0.0F,	//float32 fR;
	0.0F,	//float32 fL;
	0.0F,	//float32 fI;
};

const PARA_MOTOR_REGS paraMotor_MDLV_3M68 =
{
	1,	//uint32 motorType;
	100,	//uint32 ulPoles;
	MOTOR_PHASE_DIR_CW,	//uint32 motorPhaseDir;

	2500.0F,	//float32 fSpeedRated;
	3000.0F,	//float32 fSpeedMax;
	4.0F,	//float32 fCurrentRated;
	7.0F,	//float32 fCurrentMax;

	0.0F,	//float32 fKe;
	0.0F,	//float32 fR;
	0.0F,	//float32 fL;
	0.0F,	//float32 fI;
};

const PARA_MOTOR_REGS paraMotor_SUMFU_17NE34BF3_300 =
{
	3,	//uint32 motorType;
	100,	//uint32 ulPoles;
	MOTOR_PHASE_DIR_CW,	//uint32 motorPhaseDir;

	1000.0F,	//float32 fSpeedRated;
	3000.0F,	//float32 fSpeedMax;
	6.0F,	//float32 fCurrentRated;
	10.0F,	//float32 fCurrentMax;

	0.0F,	//float32 fKe;
	0.86F,	//float32 fR;
	0.37F,	//float32 fL;
	0.000053F,	//float32 fI;
};

const PARA_MOTOR_REGS paraMotor_SUMFU_ML1513   =
{
	4,	//uint32 motorType;
	8,	//uint32 ulPoles;
	MOTOR_PHASE_DIR_CCW,	//uint32 motorPhaseDir;

	2500.0F,	//float32 fSpeedRated;
	3000.0F,	//float32 fSpeedMax;
	3.0F,	//float32 fCurrentRated;
	5.0F,	//float32 fCurrentMax;

	0.0F,	//float32 fKe;
	0.0F,	//float32 fR;
	0.0F,	//float32 fL;
	0.0F,	//float32 fI;
};

const PARA_MOTOR_REGS paraMotor_SM_1P2D50P500R4P6A   =
{
	5,		//uint32 motorType;
	100,	//uint32 ulPoles;
	MOTOR_PHASE_DIR_CW,	//uint32 motorPhaseDir;

	3000.0F,	//float32 fSpeedRated;
	3000.0F,	//float32 fSpeedMax;
	3.0F,	//float32 fCurrentRated;
	7.5F,	//float32 fCurrentMax;

	0.0F,	//float32 fKe;
	0.0F,	//float32 fR;
	0.0F,	//float32 fL;
	0.0F,	//float32 fI;
};

const PARA_MOTOR_REGS paraMotor_S160D =
{
	6,		//uint32 motorType;
	2,		//uint32 ulPoles;
	MOTOR_PHASE_DIR_CW,	//uint32 motorPhaseDir;

	200.0F,	//float32 fSpeedRated;
	500.0F,	//float32 fSpeedMax;
	1.0F,	//float32 fCurrentRated;
	3.0F,	//float32 fCurrentMax;

	0.0F,	//float32 fKe;
	0.0F,	//float32 fR;
	0.0F,	//float32 fL;
	0.0F,	//float32 fI;
};

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mPara_motorTypeConfig(PARA_MOTOR_REGS *mParaMotorRegs,uint32 motortype)
{
	switch(motortype)
	{
		case MOTOR_MDLV_3M68 : 					*mParaMotorRegs = paraMotor_MDLV_3M68; 				break;
		case MOTOR_SUMFU_17NE34BF3_300: 		*mParaMotorRegs = paraMotor_SUMFU_17NE34BF3_300; 	break;
		case MOTOR_SM_1P2D50P500R4P6A: 			*mParaMotorRegs = paraMotor_SM_1P2D50P500R4P6A;		break;
		case MOTOR_SUMFU_ML1513: 				*mParaMotorRegs = paraMotor_SUMFU_ML1513; 			break;
		case MOTOR_GHC_S160D: 					*mParaMotorRegs = paraMotor_S160D;					break;
		case MOTOR_DEFAULT: 					*mParaMotorRegs = paraMotor_default;				break;
		default: 								*mParaMotorRegs = paraMotor_default;				break;
	}
}
