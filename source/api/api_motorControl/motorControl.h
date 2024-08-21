///*****************************************////
//  Name : motorDrive.h
//  Data : 2020/10
//  Version : 0.0
////*****************************************////

#ifndef _MOTORCOTROL_H_
#define _MOTORCONTROL_H_

#include "motorControl_ext.h"

extern void motorControl_statusUpdate(void);

extern void motorControl_testBench(uint32 enable);

extern void motorControl_advCtrl_commandRenew(uint32 enable, uint32 para0, uint32 para1, MOTOR_CONTROL_REGS *mCtrlRegs);


#endif // end of file
