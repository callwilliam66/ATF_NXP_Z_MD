///*****************************************////
//  Name : hmi.h
//  Data : 2020/10
//  Version : 0.0
////*****************************************////

#ifndef _HMI_H_
#define _HMI_H_

#include "hmi_ext.h"
#include "hmi_analogDisplay_define.h"

#define HMI_ADISP_VALUE_MAX 65535

// extern
extern void hmi_init(void);
extern void hmi_aDisp_outputUpdate(HMI_ADISP_REGS *hmi_aDispRegs);
extern void hmi_aDisp_valueUpdate(HMI_ADISP_REGS *hmi_aDispRegs);
extern void hmi_aDisp_Clear(HMI_ADISP_REGS *hmi_aDispRegs);
extern float32 hmi_aDispTable(uint32 ulChannel);


#define hmi_aDisp_valueGet_macro(ulChannel) hmi_aDispRegs.ch[ulChannel].ulValue

#endif // end of file
