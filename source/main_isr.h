////*****************************************////
//  Name : main_isr.h
//  Data : 2021/01
//  Version : 0.0
////*****************************************////

#ifndef _MAIN_ISR_H_
#define _MAIN_ISR_H_

#include "main.h"

#define ISR_ENABLE	1
#define ISR_DISABLE	0

#define SOFTWARE0_ISR_ENABLE ISR_ENABLE
#define SOFTWARE1_ISR_ENABLE ISR_ENABLE
#define SOFTWARE2_ISR_ENABLE ISR_DISABLE
#define SOFTWARE3_ISR_ENABLE ISR_DISABLE
#define SOFTWARE4_ISR_ENABLE ISR_DISABLE
#define SOFTWARE5_ISR_ENABLE ISR_DISABLE
#define SOFTWARE6_ISR_ENABLE ISR_ENABLE
#define SOFTWARE7_ISR_ENABLE ISR_DISABLE

#define ISR_FREQ_PWM	40000
#define BASE_ISR 		ISR_FREQ_PWM
#define ISR_FREQ_HMI	ISR_FREQ_PWM

#define ISR_FREQ_SOFT0	BASE_ISR
#define ISR_FREQ_SOFT1	BASE_ISR
#define ISR_FREQ_SOFT2	BASE_ISR
#define ISR_FREQ_SOFT3	1000
#define ISR_FREQ_SOFT4	BASE_ISR
#define ISR_FREQ_SOFT5	2
#define ISR_FREQ_SOFT6	2
#define ISR_FREQ_SOFT7	1

#define ISR_CNTMAX_SOFT1	ISR_FREQ_SOFT0 / ISR_FREQ_SOFT1
#define ISR_CNTMAX_SOFT2	ISR_FREQ_SOFT0 / ISR_FREQ_SOFT2
#define ISR_CNTMAX_SOFT3	ISR_FREQ_SOFT0 / ISR_FREQ_SOFT3
#define ISR_CNTMAX_SOFT4	ISR_FREQ_SOFT0 / ISR_FREQ_SOFT4
#define ISR_CNTMAX_SOFT5	ISR_FREQ_SOFT0 / ISR_FREQ_SOFT5
#define ISR_CNTMAX_SOFT6	ISR_FREQ_SOFT0 / ISR_FREQ_SOFT6
#define ISR_CNTMAX_SOFT7	ISR_FREQ_SOFT0 / ISR_FREQ_SOFT7

#define software0_isr Reserved68_IRQHandler
#define software1_isr Reserved78_IRQHandler
#define software2_isr Reserved86_IRQHandler
#define software3_isr Reserved87_IRQHandler
#define software4_isr Reserved115_IRQHandler
#define software5_isr Reserved143_IRQHandler
#define software6_isr Reserved144_IRQHandler
#define software7_isr Reserved171_IRQHandler



#define SOFTWARE0_ISRn Reserved68_IRQn
#define SOFTWARE1_ISRn Reserved78_IRQn
#define SOFTWARE2_ISRn Reserved86_IRQn
#define SOFTWARE3_ISRn Reserved87_IRQn
#define SOFTWARE4_ISRn Reserved115_IRQn
#define SOFTWARE5_ISRn Reserved143_IRQn
#define SOFTWARE6_ISRn Reserved144_IRQn
#define SOFTWARE7_ISRn Reserved171_IRQn

#define software0_isr_trigger_macro() NVIC_SetPendingIRQ(SOFTWARE0_ISRn)
#define software1_isr_trigger_macro() NVIC_SetPendingIRQ(SOFTWARE1_ISRn)
#define software2_isr_trigger_macro() NVIC_SetPendingIRQ(SOFTWARE2_ISRn)
#define software3_isr_trigger_macro() NVIC_SetPendingIRQ(SOFTWARE3_ISRn)
#define software4_isr_trigger_macro() NVIC_SetPendingIRQ(SOFTWARE4_ISRn)
#define software5_isr_trigger_macro() NVIC_SetPendingIRQ(SOFTWARE5_ISRn)
#define software6_isr_trigger_macro() NVIC_SetPendingIRQ(SOFTWARE6_ISRn)
#define software7_isr_trigger_macro() NVIC_SetPendingIRQ(SOFTWARE7_ISRn)

typedef struct
{
	uint32 ulIsrCnt_soft1;
	uint32 ulIsrCnt_soft2;
	uint32 ulIsrCnt_soft3;
	uint32 ulIsrCnt_soft4;
	uint32 ulIsrCnt_soft5;
	uint32 ulIsrCnt_soft6;
	uint32 ulIsrCnt_soft7;
}MAIN_ISR_REGS;

extern MAIN_ISR_REGS mainIsrRegs;

// extern
extern void software_isr_config(void);

extern void dac_isr(void);

#endif // end of file
