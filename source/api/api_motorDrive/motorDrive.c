////*****************************************////
//  Name : motorDrive.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "motorDrive.h" 

MOTORDRIVE_REGS mDrvRegs;
MOTORDRIVE_DATA_REGS mDataRegs;
MOTORDRIVE_PARA_REGS mParaRegs;

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mDrv_init(void)
{
	mDrvRegs.adjustFlag = false;
	mDrvRegs.adcOffsetFlag = false;

	mDrvRegs.alarmUnderVoltageCnt = 0;
	mDrvRegs.warningUnderVoltageCnt = 0;
	mDrvRegs.alarmOverVoltageCnt = 0;
	mDrvRegs.warningOverVoltageCnt = 0;

	mDrvRegs.ulP_ctrlCnt = 0;
	mDrvRegs.ulP_ctrlCntMax = 8;//8
	mDrvRegs.p_ctrlflag = 0;

	mDrvRegs.ulV_ctrlCnt = 0;
	mDrvRegs.ulV_ctrlCntMax = 4;//4
	mDrvRegs.v_ctrlflag = 0;

	mDrvRegs.ulI_ctrlCnt = 0;
	mDrvRegs.ulI_ctrlCntMax = 1;
	mDrvRegs.i_ctrlflag = 0;

	park_init(&mDrvRegs.parkRegs);
	iPark_init(&mDrvRegs.iParkRegs);
	clarke_init(&mDrvRegs.clarkeRegs);
	iClarke_init(&mDrvRegs.iClarkeRegs);
	svm_init(&mDrvRegs.svmRegs);
	pi_init(&mDrvRegs.Iq_piRegs);
	pi_init(&mDrvRegs.Id_piRegs);
	pi_init(&mDrvRegs.V_piRegs);
	p_init(&mDrvRegs.P_pRegs);
	speed_init(&mDrvRegs.speedRegs);
	accDec_init(&mDrvRegs.speedAccDecRegs);

	startup_init(&mDrvRegs.startUpRegs,&mDrvRegs.startUpCheckRegs);
	mData_init(&mDataRegs);
	mPara_init(&mParaRegs);
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mDrv_servo_on_DI_update(uint32 data)
{
	mDrvRegs.servoStateIO = data;
}
