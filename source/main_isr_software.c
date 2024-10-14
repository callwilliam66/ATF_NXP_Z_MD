////*****************************************////
//  Name : main_isr_software.c
//  Data : 2021/01
//  Version : 0.0
////*****************************************////

#include "main.h"

MAIN_ISR_REGS mainIsrRegs;

// interrupt - software1
#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void software1_isr(void)
{
	motorControl_isr();
}

// interrupt - software2
#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void software2_isr(void)
{
}

// interrupt - software3
#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void software3_isr(void)
{
}

// interrupt - software4
#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void software4_isr(void)
{

}

// interrupt - software5
#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void software5_isr(void)
{

}

// interrupt - software6
#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void software6_isr(void)
{
#if  TESTMODE == NORMAL_MODE

	if((mCtrlRegs.uart2Regs.module->STAT & 0X80000) == 0X80000)
	{
		board_led_g_on_macro();
		board_led_r_on_macro();
		return;
	}


	// LED_G
	if(mCtrl_uart_firmwareUpdateFlagGet_macro() == 1 || mCtrl_emg_stateGet_macro() == 1)
	{
		board_led_g_toggle_macro();
	}
	else if(mDrv_servoStateGet_macro() == SERVO_STATE_ON)
	{
		board_led_g_on_macro();
	}
	else
	{
		board_led_g_toggle_macro();
	}

	// B2
	if(mCtrl_uart_firmwareUpdateFlagGet_macro() == 1)
	{
		board_led_r_toggle_macro();
	}
	else if(((mCtrl_status_alarmGet_macro() == 1) || (mCtrl_status_warningGet_macro() == 1)) && ((mDrvRegs.alarmCode.data.overCurrent == 1) || (mDrvRegs.warningCode.data.overCurrent == 1)))
	{
		board_led_r_toggle_macro();
		board_led_g_off_macro();
	}
	else if(((mCtrl_status_alarmGet_macro() == 1) || (mCtrl_status_warningGet_macro() == 1)) && ((mDrvRegs.alarmCode.data.overCurrent == 0) || (mDrvRegs.warningCode.data.overCurrent == 0)))
	{
		board_led_r_on_macro();
		board_led_g_off_macro();
	}
	else
	{
		board_led_r_off_macro();

	}

#elif TESTMODE  == UART_TEST_MODE
	board_led_g_toggle_macro();
	board_led_r_toggle_macro();
#endif

}

// interrupt - software7
#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void software7_isr(void)
{
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void software_isr_config(void)
{
	if(SOFTWARE0_ISR_ENABLE == ISR_ENABLE)
	{
		NVIC_SetPriority(SOFTWARE0_ISRn, 8);
		EnableIRQ(SOFTWARE0_ISRn);
	}
	if(SOFTWARE1_ISR_ENABLE == ISR_ENABLE)
	{
		NVIC_SetPriority(SOFTWARE1_ISRn, 9);
		EnableIRQ(SOFTWARE1_ISRn);
	}
	if(SOFTWARE2_ISR_ENABLE == ISR_ENABLE)
	{
		NVIC_SetPriority(SOFTWARE2_ISRn, 10);
		EnableIRQ(SOFTWARE2_ISRn);
	}
	if(SOFTWARE3_ISR_ENABLE == ISR_ENABLE)
	{
		NVIC_SetPriority(SOFTWARE3_ISRn, 11);
		EnableIRQ(SOFTWARE3_ISRn);
	}
	if(SOFTWARE4_ISR_ENABLE == ISR_ENABLE)
	{
		NVIC_SetPriority(SOFTWARE4_ISRn, 12);
		EnableIRQ(SOFTWARE4_ISRn);
	}
	if(SOFTWARE5_ISR_ENABLE == ISR_ENABLE)
	{
		NVIC_SetPriority(SOFTWARE5_ISRn, 13);
		EnableIRQ(SOFTWARE5_ISRn);
	}
	if(SOFTWARE6_ISR_ENABLE == ISR_ENABLE)
	{
		NVIC_SetPriority(SOFTWARE6_ISRn, 14);
		EnableIRQ(SOFTWARE6_ISRn);
	}
	if(SOFTWARE7_ISR_ENABLE == ISR_ENABLE)
	{
		NVIC_SetPriority(SOFTWARE7_ISRn, 15);
		EnableIRQ(SOFTWARE7_ISRn);
	}
}

// software interrupt control -software0
#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void software0_isr(void)
{

	// software1
	if(SOFTWARE1_ISR_ENABLE == ISR_ENABLE)
	{
		mainIsrRegs.ulIsrCnt_soft1++;
		if(mainIsrRegs.ulIsrCnt_soft1 == ISR_CNTMAX_SOFT1)
		{
			software1_isr_trigger_macro();
			mainIsrRegs.ulIsrCnt_soft1 = 0;
		}
	}

	// software2
	if(SOFTWARE2_ISR_ENABLE == ISR_ENABLE)
	{
		mainIsrRegs.ulIsrCnt_soft2++;
		if(mainIsrRegs.ulIsrCnt_soft2 == ISR_CNTMAX_SOFT2)
		{
			software2_isr_trigger_macro();
			mainIsrRegs.ulIsrCnt_soft2 = 0;
		}
	}

	// software3
	if(SOFTWARE3_ISR_ENABLE == ISR_ENABLE)
	{
		mainIsrRegs.ulIsrCnt_soft3++;
		if(mainIsrRegs.ulIsrCnt_soft3 == ISR_CNTMAX_SOFT3)
		{
			software3_isr_trigger_macro();
			mainIsrRegs.ulIsrCnt_soft3 = 0;
		}
	}

	// software4
	if(SOFTWARE4_ISR_ENABLE == ISR_ENABLE)
	{
		mainIsrRegs.ulIsrCnt_soft4++;
		if(mainIsrRegs.ulIsrCnt_soft4 == ISR_CNTMAX_SOFT4)
		{
			software4_isr_trigger_macro();
			mainIsrRegs.ulIsrCnt_soft4 = 0;
		}
	}

	// software5
	if(SOFTWARE5_ISR_ENABLE == ISR_ENABLE)
	{
		mainIsrRegs.ulIsrCnt_soft5++;
		if(mainIsrRegs.ulIsrCnt_soft5 == ISR_CNTMAX_SOFT5)
		{
			software5_isr_trigger_macro();
			mainIsrRegs.ulIsrCnt_soft5 = 0;
		}
	}

	// software6
	if(SOFTWARE6_ISR_ENABLE == ISR_ENABLE)
	{
		mainIsrRegs.ulIsrCnt_soft6++;
		if(mainIsrRegs.ulIsrCnt_soft6 == ISR_CNTMAX_SOFT6)
		{
			software6_isr_trigger_macro();
			mainIsrRegs.ulIsrCnt_soft6 = 0;
		}
	}

	// software7
	if(SOFTWARE7_ISR_ENABLE == ISR_ENABLE)
	{
		mainIsrRegs.ulIsrCnt_soft7++;
		if(mainIsrRegs.ulIsrCnt_soft7 == ISR_CNTMAX_SOFT7)
		{
			software7_isr_trigger_macro();
			mainIsrRegs.ulIsrCnt_soft7 = 0;
		}
	}
}
