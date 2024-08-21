///*****************************************////
//  Name : motorDrive.h
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#ifndef _MOTORDRIVE_H_
#define _MOTORDRIVE_H_

#include "motorDrive_ext.h"

#define ADC_ADJUST_TIMES 1000

extern void mData_init(MOTORDRIVE_DATA_REGS *mDataRegs);
extern void mPara_init(MOTORDRIVE_PARA_REGS *mParaRegs);

extern void mDrv_servoIO_control(MOTORDRIVE_REGS *mDrvRegs);
extern void mDrv_servoOffClear(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs);
extern void mDrv_adjust(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs);

extern void park_init(PARK_REGS *parkRegs);
extern void park_theta(PARK_REGS *parkRegs);
extern void park_sinCos(PARK_REGS *parkRegs);

extern void iPark_init(IPARK_REGS *iParkRegs);
extern void iPark_theta(IPARK_REGS *iParkRegs);
extern void iPark_sinCos(IPARK_REGS *iParkRegs);

extern void clarke_init(CLARKE_REGS *clarkeRegs);
extern void clarke(CLARKE_REGS *clarkeRegs);

extern void iClarke_init(ICLARKE_REGS *iClarkeRegs);
extern void iClarke(ICLARKE_REGS *iClarkeRegs);

extern void svm_init(SVM_REGS *svmRegs);
extern void svm(SVM_REGS *svmRegs);

extern void pi_init(PI_REGS *piRegs);
extern void pi(PI_REGS *piRegs);
extern void pi_advctrl_vloop(PI_REGS *piRegs);
extern void pi_vloop_gainset(PI_REGS *piRegs);
extern void pi_vloop(PI_REGS *piRegs);
extern void pi_clear(PI_REGS *piRegs);
extern void pi_feed_forward(PI_REGS *piRegs);


extern void p_init(P_REGS *pRegs);
extern void p(P_REGS *pRegs);
extern void p_fixPoint(P_REGS *pRegs);
extern void pd_fixPoint(P_REGS *pRegs);
extern void p_clear(P_REGS *pRegs);

extern void Pulse_pi(PULSEPI_REGS *piRegs);
extern void speed_init(SPEED_REGS *speedRegs);
extern void speed(SPEED_REGS *speedRegs);
extern void speed_reset(SPEED_REGS *speedRegs, uint32 ulResetData);

extern void accDec_init(ACCDEC_REGS *accDecRegs);
extern void accDec(ACCDEC_REGS *accDecRegs);

extern void startup(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs,MOTORDRIVE_PARA_REGS *mParaRegs);
extern void startup_init(STARTUP_REGS *startUpRegs,STARTCHECK_REGS	*startcheckRegs);
extern void startup_clear(STARTUP_REGS *startUpRegs);
extern void startup_angleOpenProcess_type2(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs,MOTORDRIVE_PARA_REGS *mParaRegs);
extern void startup_angleOpenProcess(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs,MOTORDRIVE_PARA_REGS *mParaRegs);
extern void startup_inc(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs);
extern void startup_zero(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs);
extern void startup_zero_slow(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs);
extern void startup_zero_test(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs);
extern void startup_check_zero(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs);
extern void mDrv_loopPosition(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs);
extern void mDrv_loopSpeed(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs);
extern void mDrv_loopCurrent(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs);
extern void mDrv_loopVoltage(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs);

extern uint32 mDrv_loopPosition_advCtrl_commandSmooth(uint32 enable,uint32 para0, MOTORDRIVE_REGS *mDrvRegs);
extern float32 mDrv_loopPosition_advCtrl_positionOutputZero(uint32 enable, MOTORDRIVE_REGS *mDrvRegs);
extern void mDrv_loopCurrent_advCtrl_IdFWcalc(uint32 enable, IDFW_REGS  *IDFWRegs);

extern float32 mDrv_loopCurrent_advCtrl_AngleHold(uint32 enable, MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs);

extern void mDrv_loopCtrl(void);
extern void mDrv_loopClear(void);

extern void mDrv_Emg_Msd(MOTORDRIVE_REGS *mDrvRegs,MOTOR_CONTROL_REGS *mCtrlRegs);

extern void mDrv_dataUpdate(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs);
extern void mDrv_dataUpdate_angle(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs);
extern void mDrv_dataUpdate_position(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs);
extern void mDrv_dataUpdate_speed(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs);
extern void mDrv_dataUpdate_analog(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs);
extern void mDrv_dataUpdate_servo_state(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs);
extern void mDrv_dataUpdate_alarmWarning(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs, MOTORDRIVE_PARA_REGS *mParaRegs);
extern void mDrv_databuff_Update(MOTORDRIVE_REGS *mDrvRegs ,MOTORDRIVE_DATA_REGS *mDataRegs);
extern void mDrv_pwmUpdate(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs);
extern uint32 mDrv_overloadCalc(MOTORDRIVE_REGS *mDrvRegs,MOTORDRIVE_PARA_REGS *mParaRegs,uint32 sec);
#endif // end of file
