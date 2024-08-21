////*****************************************////
//  Name : hmi_ext.h
//  Data : 2020/10
//  Version : 0.0
////*****************************************////

#ifndef _HMI_EXT_H_
#define _HMI_EXT_H_

#include "api.h"
#include "hmi_analogDisplay_define.h"

#define HMI_ADISP_CHANNEL0 0
#define HMI_ADISP_CHANNEL1 1
#define HMI_ADISP_CHANNEL2 2
#define HMI_ADISP_CHANNEL3 3

#define HMI_ADISP_CHANNEL_MAX 4

typedef struct
{
	uint32 ulData;
	uint32 ulValue;
	float32 fValue;
	float32 fGain;
	float32 fOffset;
}HMI_ADISP_CHANNEL;

typedef struct
{
	HMI_ADISP_CHANNEL ch[HMI_ADISP_CHANNEL_MAX];
}HMI_ADISP_REGS;

extern HMI_ADISP_REGS hmi_aDispRegs;

extern void hmi_init(void);
extern void hmi_dac_isr(void);
extern void hmi_ui_isr(void);

extern float32 hmi_aDispTable(uint32 ulChannel);
extern void hmi_aDisp_channel_set(HMI_ADISP_REGS *hmi_aDispRegs,uint32 ulChannel,uint32 ulData);
extern void hmi_aDisp_gain_set(HMI_ADISP_REGS *hmi_aDisp,uint32 ulChannel,float32 fData);
extern void hmi_aDisp_offset_set(HMI_ADISP_REGS *hmi_aDisp,uint32 ulChannel,float32 fData);

#define hmi_aDisp_channel_set_macro(ulChannel,ulData)	hmi_aDisp_channel_set(&hmi_aDispRegs,ulChannel,ulData)
#define hmi_aDisp_gain_set_macro(ulChannel,fData)		hmi_aDisp_gain_set(&hmi_aDispRegs,ulChannel,fData)
#define hmi_aDisp_offset_set_macro(ulChannel,fData)		hmi_aDisp_offset_set(&hmi_aDispRegs,ulChannel,fData)

#endif // end of file
