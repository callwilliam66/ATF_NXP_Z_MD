////*****************************************////
//  Name : main_isr.c
//  Data : 2021/01
//  Version : 0.0
////*****************************************////

#include "main.h"


uint32  test2 = 0;

uint32  testrxcnt;
uint32  testrxcnt_diff;
uint32  testrxcntwatch;



uint8 logtime[100] = {0};
uint32 log_index = 0;
#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void PWM_MOTOR_ISR(void)
{
	motorDrive_isr();

	software0_isr_trigger_macro();

	device_pwm_isr_clear_macro();
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void PWM_MOTOR_FAULT_ISR(void)
{
	motorDrive_overCurrent_isr();

	DisableIRQ(PWM1_FAULT_ERROR_IRQN);
}

/* PWM4_FAULT_IRQn interrupt handler */
#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void PWM4_FAULT_ERROR_IRQHANDLER(void) {




  #if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
  #endif
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
/* LPUART1_IRQn interrupt handler */
void LPUART1_SERIAL_RX_TX_IRQHANDLER(void) {

	uint8 u8rxisrtempdata;
#if  TESTMODE == UART_TEST_MODE
	if ((kLPUART_RxDataRegFullFlag) & LPUART_GetStatusFlags(LPUART1_PERIPHERAL))
	{
		mCtrlRegs.uart1Regs.rxisrCnt++;
		u8rxisrtempdata = device_uart_module_rxReadByte_macro(LPUART1_PERIPHERAL);
		Queue_Push(&mCtrlRegs.uart1Regs.Rx_Data_Queue, u8rxisrtempdata);

	}else if((kLPUART_IdleLineFlag ) & LPUART_GetStatusFlags(LPUART1_PERIPHERAL))
	{
		LPUART1_PERIPHERAL->STAT |= 0x1<<20;

		if(device_uart_module_rxFifoEmpty_macro(LPUART1_PERIPHERAL) == 0)
		{
			mCtrlRegs.uart1Regs.rxisrCnt++;
			u8rxisrtempdata = device_uart_module_rxReadByte_macro(LPUART1_PERIPHERAL);
			Queue_Push(&mCtrlRegs.uart1Regs.Rx_Data_Queue,u8rxisrtempdata);
		}

	}else if( (kLPUART_TxDataRegEmptyFlag ) & LPUART_GetStatusFlags(LPUART1_PERIPHERAL))
	{
		mCtrlRegs.uart1Regs.txState = UART_TX_STATE_BUSY;

		device_uart_module_txWriteByte_macro(LPUART1_PERIPHERAL, mCtrlRegs.uart1Regs.txRegs.data[UART_TX_PACKET_LENGTH - mCtrlRegs.uart1Regs.txCnt]);

		mCtrlRegs.uart1Regs.txCnt--;

		if(mCtrlRegs.uart1Regs.txCnt == 0)
		{
			if( mCtrlRegs.uart1Regs.XcmdPendStatus == 0)
				mCtrlRegs.uart1Regs.txpwmCnt++;

			mCtrlRegs.uart1Regs.txCnt = UART_TX_PACKET_LENGTH;
			mCtrlRegs.uart1Regs.txState = UART_TX_STATE_IDLE;
			LPUART_DisableInterrupts(LPUART1, kLPUART_TxDataRegEmptyInterruptEnable);
		}
	}
#else
	/* Reading all interrupt flags of status registers */
	if ((kLPUART_RxDataRegFullFlag) & LPUART_GetStatusFlags(LPUART1_PERIPHERAL))
	{
		mCtrlRegs.uart1Regs.rxisrCnt++;
		u8rxisrtempdata = device_uart_module_rxReadByte_macro(LPUART1_PERIPHERAL);
		Queue_Push(&mCtrlRegs.uart1Regs.Rx_Data_Queue,u8rxisrtempdata);

	}else if((kLPUART_IdleLineFlag ) & LPUART_GetStatusFlags(LPUART1_PERIPHERAL))
	{
		LPUART1_PERIPHERAL->STAT |= 0x1<<20;

		if(device_uart_module_rxFifoEmpty_macro(LPUART1_PERIPHERAL) == 0)
		{
			mCtrlRegs.uart1Regs.rxisrCnt++;
			u8rxisrtempdata = device_uart_module_rxReadByte_macro(LPUART1_PERIPHERAL);
			Queue_Push(&mCtrlRegs.uart1Regs.Rx_Data_Queue,u8rxisrtempdata);
		}

	}else if( (kLPUART_TxDataRegEmptyFlag ) & LPUART_GetStatusFlags(LPUART1_PERIPHERAL))
	{
		mCtrlRegs.uart1Regs.txState = UART_TX_STATE_BUSY;

		device_uart_module_txWriteByte_macro(LPUART1_PERIPHERAL, mCtrlRegs.uart1Regs.txRegs.data[UART_TX_PACKET_LENGTH - mCtrlRegs.uart1Regs.txCnt]);

		mCtrlRegs.uart1Regs.txCnt--;

		if(mCtrlRegs.uart1Regs.txCnt == 0)
		{
			LPUART_DisableInterrupts(LPUART1,kLPUART_TxDataRegEmptyInterruptEnable);

			mCtrlRegs.uart1Regs.txCnt = UART_TX_PACKET_LENGTH;
			mCtrlRegs.uart1Regs.txState = UART_TX_STATE_IDLE;
			mCtrlRegs.uart1Regs.txpwmCnt++;
		}
	}
#endif

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
/* LPUART3_IRQn interrupt handler */
void LPUART3_SERIAL_RX_TX_IRQHANDLER(void) {

	uint8 u8rxisrtempdata;

#if  TESTMODE == UART_TEST_MODE

	if ((kLPUART_RxDataRegFullFlag) & LPUART_GetStatusFlags(LPUART3_PERIPHERAL))
	{
		mCtrlRegs.uart2Regs.rxisrCnt++;
		u8rxisrtempdata = device_uart_module_rxReadByte_macro(LPUART3_PERIPHERAL);

		Queue_Push(&mCtrlRegs.uart2Regs.Rx_Data_Queue, u8rxisrtempdata);



		if( u8rxisrtempdata == 50)
		{
			testrxcnt = mCtrlRegs.uart2Regs.rxisrCnt;
			testrxcnt_diff = testrxcnt - testrxcntwatch;
			if( testrxcnt_diff < 9  )
				test2++;
			testrxcntwatch = testrxcnt;
		}


	}else if((kLPUART_IdleLineFlag ) & LPUART_GetStatusFlags(LPUART3_PERIPHERAL))
	{
		LPUART3_PERIPHERAL->STAT |= 0x1<<20;

		if(device_uart_module_rxFifoEmpty_macro(LPUART3_PERIPHERAL) == 0)
		{
			mCtrlRegs.uart2Regs.rxisrCnt++;
			u8rxisrtempdata = device_uart_module_rxReadByte_macro(LPUART3_PERIPHERAL);
			Queue_Push(&mCtrlRegs.uart2Regs.Rx_Data_Queue,u8rxisrtempdata);
		}

	}else if( (kLPUART_TxDataRegEmptyFlag ) & LPUART_GetStatusFlags(LPUART3_PERIPHERAL))
	{

		mCtrlRegs.uart2Regs.txState = UART_TX_STATE_BUSY;

		device_uart_module_txWriteByte_macro(LPUART3_PERIPHERAL, mCtrlRegs.uart2Regs.txRegs.data[UART_TX_PACKET_LENGTH - mCtrlRegs.uart2Regs.txCnt]);

		/*		if(mCtrlRegs.uart2Regs.txCnt == 9 )
		{
			if(mCtrlRegs.uart2Regs.txRegs.data[UART_TX_PACKET_LENGTH - mCtrlRegs.uart2Regs.txCnt] == 49)
			{
				mCtrlRegs.uart2Regs.ulZaxisTxcnt++;
			}else if(mCtrlRegs.uart2Regs.txRegs.data[UART_TX_PACKET_LENGTH - mCtrlRegs.uart2Regs.txCnt] == 50)
			{
				mCtrlRegs.uart2Regs.ulXaxisTxcnt++;
			}
		}
*/

		mCtrlRegs.uart2Regs.txCnt--;

		if(mCtrlRegs.uart2Regs.txCnt == 0)
		{
			LPUART_DisableInterrupts(LPUART3, kLPUART_TxDataRegEmptyInterruptEnable);

			if( mCtrlRegs.uart2Regs.XcmdPendStatus == 0)
			{
				mCtrlRegs.uart2Regs.txpwmCnt++;
			}


			mCtrlRegs.Testtxcnt = mCtrlRegs.uart2Regs.rxisrCnt;
			mCtrlRegs.Testtxcntdiff = mCtrlRegs.Testtxcnt - mCtrlRegs.Testtxcntwatch;

			if(mCtrlRegs.Testtxcntdiff != 9 )
			{
				board_led_g_on_macro();
				board_led_r_on_macro();

				logtime[0] = mCtrlRegs.uart2Regs.txRegs.data[0];
				logtime[1] = mCtrlRegs.uart2Regs.txRegs.data[1];
				logtime[2] = mCtrlRegs.uart2Regs.txRegs.data[2];
				logtime[3] = mCtrlRegs.uart2Regs.txRegs.data[3];
				logtime[4] = mCtrlRegs.uart2Regs.txRegs.data[4];
				logtime[5] = mCtrlRegs.uart2Regs.txRegs.data[5];
				logtime[6] = mCtrlRegs.uart2Regs.txRegs.data[6];
				logtime[7] = mCtrlRegs.uart2Regs.txRegs.data[7];
				logtime[8] = mCtrlRegs.uart2Regs.txRegs.data[8];

			}else
			{
				logtime[9] = mCtrlRegs.uart2Regs.txRegs.data[0];
				logtime[10] = mCtrlRegs.uart2Regs.txRegs.data[1];
				logtime[11] = mCtrlRegs.uart2Regs.txRegs.data[2];
				logtime[12] = mCtrlRegs.uart2Regs.txRegs.data[3];
				logtime[13] = mCtrlRegs.uart2Regs.txRegs.data[4];
				logtime[14] = mCtrlRegs.uart2Regs.txRegs.data[5];
				logtime[15] = mCtrlRegs.uart2Regs.txRegs.data[6];
				logtime[16] = mCtrlRegs.uart2Regs.txRegs.data[7];
				logtime[17] = mCtrlRegs.uart2Regs.txRegs.data[8];
			}

			mCtrlRegs.Testtxcntwatch = mCtrlRegs.Testtxcnt;

			mCtrlRegs.uart2Regs.txCnt = UART_TX_PACKET_LENGTH;
			mCtrlRegs.uart2Regs.txState = UART_TX_STATE_IDLE;

		}
	}
#else

	if ((kLPUART_RxDataRegFullFlag) & LPUART_GetStatusFlags(LPUART3_PERIPHERAL))
	{
		mCtrlRegs.uart2Regs.rxisrCnt++;
		u8rxisrtempdata = device_uart_module_rxReadByte_macro(LPUART3_PERIPHERAL);
		Queue_Push(&mCtrlRegs.uart2Regs.Rx_Data_Queue, u8rxisrtempdata);

	}else if((kLPUART_IdleLineFlag ) & LPUART_GetStatusFlags(LPUART3_PERIPHERAL))
	{
		LPUART3_PERIPHERAL->STAT |= 0x1<<20;

		if(device_uart_module_rxFifoEmpty_macro(LPUART3_PERIPHERAL) == 0)
		{
			mCtrlRegs.uart2Regs.rxisrCnt++;
			u8rxisrtempdata = device_uart_module_rxReadByte_macro(LPUART3_PERIPHERAL);
			Queue_Push(&mCtrlRegs.uart2Regs.Rx_Data_Queue, u8rxisrtempdata);
		}

	}else if( (kLPUART_TxDataRegEmptyFlag ) & LPUART_GetStatusFlags(LPUART3_PERIPHERAL))
	{

		mCtrlRegs.uart2Regs.txState = UART_TX_STATE_BUSY;

		device_uart_module_txWriteByte_macro(LPUART3_PERIPHERAL, mCtrlRegs.uart2Regs.txRegs.data[UART_TX_PACKET_LENGTH - mCtrlRegs.uart2Regs.txCnt]);

		mCtrlRegs.uart2Regs.txCnt--;

		if(mCtrlRegs.uart2Regs.txCnt == 0)
		{
			LPUART_DisableInterrupts(LPUART3, kLPUART_TxDataRegEmptyInterruptEnable);
			mCtrlRegs.uart2Regs.txpwmCnt++;
			mCtrlRegs.uart2Regs.txCnt = UART_TX_PACKET_LENGTH;
			mCtrlRegs.uart2Regs.txState = UART_TX_STATE_IDLE;
		}
	}
#endif
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
/* LPUART4_IRQn interrupt handler */
void LPUART4_SERIAL_RX_TX_IRQHANDLER(void) {
	uint8 u8rxisrtempdata;

	/* Reading all interrupt flags of status registers */
	if ((kLPUART_RxDataRegFullFlag)&LPUART_GetStatusFlags(LPUART4_PERIPHERAL))
	{
		mCtrlRegs.uart3Regs.rxisrCnt++;
		u8rxisrtempdata = device_uart_module_rxReadByte_macro(LPUART4_PERIPHERAL);
		Queue_Push(&mCtrlRegs.uart3Regs.Rx_Data_Queue,u8rxisrtempdata);

	}else if((kLPUART_IdleLineFlag )&LPUART_GetStatusFlags(LPUART4_PERIPHERAL))
	{
		LPUART4_PERIPHERAL->STAT |= 0x1<<20;

		if(device_uart_module_rxFifoEmpty_macro(LPUART4_PERIPHERAL) == 0)
		{
			mCtrlRegs.uart3Regs.rxisrCnt++;
			u8rxisrtempdata = device_uart_module_rxReadByte_macro(LPUART4_PERIPHERAL);
			Queue_Push(&mCtrlRegs.uart3Regs.Rx_Data_Queue,u8rxisrtempdata);
		}
	}else if((kLPUART_TxDataRegEmptyFlag ) & LPUART_GetStatusFlags(LPUART4_PERIPHERAL))
	{
		mCtrlRegs.uart3Regs.txState = UART_TX_STATE_BUSY;

		device_uart_module_txWriteByte_macro(LPUART4_PERIPHERAL, mCtrlRegs.uart3Regs.txRegs.data[UART_TX_REDUCE_PACKET_LENGTH - mCtrlRegs.uart3Regs.txCnt]);

		mCtrlRegs.uart3Regs.txCnt--;

		if(mCtrlRegs.uart3Regs.txCnt == 0)
		{
			LPUART_DisableInterrupts(LPUART4, kLPUART_TxDataRegEmptyInterruptEnable);

			mCtrlRegs.uart3Regs.txpwmCnt++;
			mCtrlRegs.uart3Regs.txCnt = UART_TX_REDUCE_PACKET_LENGTH;
			mCtrlRegs.uart3Regs.txState = UART_TX_STATE_IDLE;

		}
	}
}
#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
/* LPUART2_IRQn interrupt handler */
void LPUART2_SERIAL_RX_TX_IRQHANDLER(void) {
	uint8 u8rxisrtempdata;

	/* Reading all interrupt flags of status registers */
	if ((kLPUART_RxDataRegFullFlag)&LPUART_GetStatusFlags(LPUART2_PERIPHERAL))
	{
		mCtrlRegs.uart4Regs.rxisrCnt++;
		u8rxisrtempdata = device_uart_module_rxReadByte_macro(LPUART2_PERIPHERAL);
		Queue_Push(&mCtrlRegs.uart4Regs.Rx_Data_Queue,u8rxisrtempdata);

	}else if((kLPUART_IdleLineFlag )&LPUART_GetStatusFlags(LPUART2_PERIPHERAL))
	{
		LPUART2_PERIPHERAL->STAT |= 0x1<<20;

		if(device_uart_module_rxFifoEmpty_macro(LPUART2_PERIPHERAL) == 0)
		{
			mCtrlRegs.uart4Regs.rxisrCnt++;
			u8rxisrtempdata = device_uart_module_rxReadByte_macro(LPUART2_PERIPHERAL);
			Queue_Push(&mCtrlRegs.uart4Regs.Rx_Data_Queue,u8rxisrtempdata);
		}
	}else if((kLPUART_TxDataRegEmptyFlag ) & LPUART_GetStatusFlags(LPUART2_PERIPHERAL))
	{

		device_uart_module_txWriteByte_macro(LPUART4_PERIPHERAL, mCtrlRegs.uart4Regs.txRegs.data[UART_TX_REDUCE_PACKET_LENGTH - mCtrlRegs.uart4Regs.txCnt]);
		mCtrlRegs.uart4Regs.txCnt--;
		mCtrlRegs.uart4Regs.txpwmCnt++;
		if(mCtrlRegs.uart4Regs.txCnt == 0)
		{
			mCtrlRegs.uart4Regs.txState = UART_TX_STATE_IDLE;
			LPUART_DisableInterrupts(LPUART2, kLPUART_TxDataRegEmptyInterruptEnable);
		}
	}
}


