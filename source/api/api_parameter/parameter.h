///*****************************************////
//  Name : parameter.h
//  Data : 2020/10
//  Version : 0.0
////*****************************************////

#ifndef _PARAMETER_H_
#define _PARAMETER_H_

#include "parameter_ext.h"
#include "main.h"

extern const PARAMETER paraDefault[MAX_PARAMETER];

extern void para_updateByMode(PARA_MODE paraMode);
extern void para_updateMode_currentTest(void);
extern void para_updateMode_currentResponseTest(void);
extern void para_updateMode_angleTest(void);
extern void para_updateMode_speedLoopTest(void);
extern void para_updateMode_positionLoopTest(void);
extern void para_updateMode_autoFocusSystemDefault(void);
extern void para_updateMode_nose_wheelDefault(void);
extern void para_updateMode_pulseDirDefault(void);

extern void para_blank(void);
extern void para_readOnly(void);

extern void para_ctrlMode(void);
extern void para_servoOnMode(void);

extern void para_startUpMethod(void);
extern void para_startUpStartAngle(void);
extern void para_startUpMoveTime(void);
extern void para_startUpCheckAngle(void);

extern void para_ctrlType(void);

extern void para_homeEnable(void);
extern void para_limitPosEnable(void);
extern void para_limitNegEnable(void);

extern void para_pKp(void);
extern void para_pKd(void);
extern void para_pCoefficient(void);

extern void para_vindex(void);
extern void para_vKp(void);
extern void para_vKi(void);
extern void para_vKp1(void);
extern void para_vKi1(void);
extern void para_vKp2(void);
extern void para_vKi2(void);
extern void para_vKp3(void);
extern void para_vKi3(void);
extern void para_vKp4(void);
extern void para_vKi4(void);

extern void para_vKf(void);
extern void para_vRKf(void);

extern void para_iKp(void);
extern void para_iKi(void);
extern void para_iBw(void);
extern void para_iTc(void);
extern void para_pCmdPara(void);

extern void para_vCmdPara(void);
extern void para_vCmdStep(void);
extern void para_vCmdAcc(void);
extern void para_vCmdDec(void);

extern void para_iqCmdPara(void);
extern void para_iqCmdStep(void);
extern void para_iqthreshold(void);
extern void para_idCmdPara(void);
extern void para_idCmdStep(void);
extern void para_idCmdHold(void);

extern void para_angleCmd(void);

extern void para_pulseCommand_type(void);
extern void para_pulseCommand_reverse(void);
extern void para_hmi_aDispChannel0(void);
extern void para_hmi_aDispChannel1(void);
extern void para_hmi_aDispChannel2(void);
extern void para_hmi_aDispChannel3(void);
extern void para_hmi_aDispGain0(void);
extern void para_hmi_aDispGain1(void);
extern void para_hmi_aDispGain2(void);
extern void para_hmi_aDispGain3(void);
extern void para_hmi_aDispOffset0(void);
extern void para_hmi_aDispOffset1(void);
extern void para_hmi_aDispOffset2(void);
extern void para_hmi_aDispOffset3(void);

extern void para_controllerMode(void);
extern void para_controllerHomeMode(void);
extern void para_controllerHomeSpeed(void);
extern void para_controllerHomePos(void);
extern void para_controllerInPositionRange(void);
extern void para_controllerZeroSpeedRange(void);

extern void para_controllerSoftNegLimitEnable(void);
extern void para_controllerSoftNegLimit(void);
extern void para_controllerSoftPosLimitEnable(void);
extern void para_controllerSoftPosLimit(void);

extern void para_tcurve_vinit(void);
extern void para_tcurve_vmax(void);
extern void para_tcurve_vend(void);
extern void para_tcurve_tacc(void);
extern void para_tcurve_tdec(void);

extern void para_motorType(void);
extern void para_encoderType(void);
extern void para_encoderDir(void);
extern void para_angleOffset(void);
extern void para_encoderResolution(void);


extern void para_dout0(void);




extern void para_flashkey(void);
extern void para_paraMode(void);
extern void para_printAll(void);
extern void para_printInfo(void);
extern void para_reset(void);
extern void para_reset_process(void);
extern void para_saveAll(void);

extern void para_driverNumber(void);
extern void para_firmwareVersion(void);

extern void para_advCtrl0_enable(void);
extern void para_advCtrl0_para0(void);
extern void para_advCtrl0_para1(void);
extern void para_advCtrl0_para2(void);
extern void para_advCtrl0_para3(void);
extern void para_advCtrl1_enable(void);
extern void para_advCtrl1_para0(void);
extern void para_advCtrl1_para1(void);
extern void para_advCtrl1_para2(void);
extern void para_advCtrl1_para3(void);
extern void para_advCtrl2_enable(void);
extern void para_advCtrl2_para0(void);
extern void para_advCtrl2_para1(void);
extern void para_advCtrl2_para2(void);
extern void para_advCtrl2_para3(void);
extern void para_advCtrl3_enable(void);
extern void para_advCtrl3_para0(void);
extern void para_advCtrl3_para1(void);
extern void para_advCtrl3_para2(void);
extern void para_advCtrl3_para3(void);
extern void para_advCtrl4_enable(void);
extern void para_advCtrl4_para0(void);
extern void para_advCtrl4_para1(void);
extern void para_advCtrl4_para2(void);
extern void para_advCtrl4_para3(void);
extern void para_advCtrl5_enable(void);
extern void para_advCtrl5_para0(void);
extern void para_advCtrl5_para1(void);
extern void para_advCtrl5_para2(void);
extern void para_advCtrl5_para3(void);
extern void para_advCtrl6_enable(void);
extern void para_advCtrl6_para0(void);
extern void para_advCtrl6_para1(void);
extern void para_advCtrl6_para2(void);
extern void para_advCtrl6_para3(void);
extern void para_advCtrl7_enable(void);
extern void para_advCtrl7_para0(void);
extern void para_advCtrl7_para1(void);
extern void para_advCtrl7_para2(void);
extern void para_advCtrl7_para3(void);
extern void para_advCtrl8_enable(void);
extern void para_advCtrl8_para0(void);
extern void para_advCtrl8_para1(void);
extern void para_advCtrl8_para2(void);
extern void para_advCtrl8_para3(void);
extern void para_advCtrl9_enable(void);
extern void para_advCtrl9_para0(void);
extern void para_advCtrl9_para1(void);
extern void para_advCtrl9_para2(void);
extern void para_advCtrl9_para3(void);

extern void para_led_mode(void);
extern void para_led_level(void);
extern void para_led_levelmax(void);

extern void para_diActiveLevel(void);
extern void para_di0Ch(void);
extern void para_di1Ch(void);
extern void para_di2Ch(void);
extern void para_di3Ch(void);
extern void para_di4Ch(void);
extern void para_di5Ch(void);
extern void para_di6Ch(void);
extern void para_di7Ch(void);
extern void para_di8Ch(void);
extern void para_di9Ch(void);
extern void para_di10Ch(void);
extern void para_doActiveLevel(void);
extern void para_do0Ch(void);
extern void para_do1Ch(void);
extern void para_do2Ch(void);
extern void para_do3Ch(void);
extern void para_do4Ch(void);
extern void para_do5Ch(void);
extern void para_do6Ch(void);
extern void para_do7Ch(void);
extern void para_do8Ch(void);
extern void para_do9Ch(void);
extern void para_do10Ch(void);
extern void para_diSwActiveLevel(void);
extern void para_diSw0Ch(void);
extern void para_diSw1Ch(void);
extern void para_diSw2Ch(void);
extern void para_diSw3Ch(void);
extern void para_diSw4Ch(void);
extern void para_diSw5Ch(void);
extern void para_diSw6Ch(void);
extern void para_diSw7Ch(void);

#endif // end of file
