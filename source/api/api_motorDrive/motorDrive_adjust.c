////*****************************************////
//  Name : motorDrive_adjust.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "motorDrive.h"

#define ADC_ADJUST_TIMES 1000

float32 fIuDataSum;
float32 fIvDataSum;
float32 fIwDataSum;

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mDrv_adjust(MOTORDRIVE_REGS *mDrvRegs, MOTORDRIVE_DATA_REGS *mDataRegs)
{
	// current offset adjust
	uint32 ulAdcTimeOutCnt = 0;

	// adc update
	while(device_adc_status_eoc_get_macro() == false)
	{
		ulAdcTimeOutCnt++;

		if(ulAdcTimeOutCnt >= 3000) // about 5us in 600 MHz
		{
			break;
		}
	}

	ulAdcTimeOutCnt = 0;

	device_adc_status_clear_macro();

	// current u v w update
	float32 fIuData;
	float32 fIvData;
	float32 fIwData;

	fIuData = board_cur_u_read_macro();
	fIvData = board_cur_v_read_macro();
	fIwData = board_cur_w_read_macro();

	mDrvRegs->ulAdcAdjustCnt++;

	if(mDrvRegs->ulAdcAdjustCnt <= 100)
	{
		return;
	}

	fIuDataSum += fIuData;
	fIvDataSum += fIvData;
	fIwDataSum += fIwData;

	if(mDrvRegs->ulAdcAdjustCnt >= (ADC_ADJUST_TIMES + 100))
	{
		mDataRegs->fIuOffset = fIuDataSum / (float32)ADC_ADJUST_TIMES;
		mDataRegs->fIvOffset = fIvDataSum / (float32)ADC_ADJUST_TIMES;
		mDataRegs->fIwOffset = fIwDataSum / (float32)ADC_ADJUST_TIMES;

		mDrvRegs->adjustFlag = true;
		mDrvRegs->adcOffsetFlag = true;

		mDrvRegs->ulAdcAdjustCnt = 0;

		fIuDataSum = 0;
		fIvDataSum = 0;
		fIwDataSum = 0;
	}
}

