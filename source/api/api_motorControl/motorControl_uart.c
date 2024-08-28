////*****************************************////
//  Name : motorControl_uart.c
//  Data : 2020/10
//  Version : 0.0
////*****************************************////

#include "motorControl.h"

extern uint32 ulCurrentAdjustCnt;

void mCtrl_uart_init(UART_REGS *uartRegs,LPUART_Type *module)
{

	uartRegs->module = module;
	//module->FIFO |= 0xff;
	uartRegs->txState = UART_TX_STATE_IDLE;
	uartRegs->txUpdate = UART_TX_DATA_IDLE;

	uartRegs->rxState = UART_RX_STATE_IDLE;
	uartRegs->rxUpdate = UART_RX_DATA_IDLE;
	uartRegs->rxCheckFail = UART_RX_CHECK_PASS;

	uartRegs->txCnt = 9;
	uartRegs->rxCnt = 0;

	uartRegs->firmwareUpdateFlag = 0;
	uartRegs->firmwareUpdatePacketLength = 1;

	for(int32 iCnt = 0; iCnt < UART_TX_PACKET_LENGTH; iCnt++)
	{
		uartRegs->txRegs.data[iCnt] = 0;
		uartRegs->rxRegs.data[iCnt] = 0;
	}
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_uart_isr(UART_REGS *uartRegs)
{
	mCtrl_uart_rx(uartRegs);
	mCtrl_uart_rx_dataUpdate(uartRegs);
	mCtrl_uart_tx_dataUpdate(uartRegs);
	mCtrl_uart_tx(uartRegs);
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_fpga_uart_isr(UART_REGS *uartRegs)
{
	mCtrl_fpga_uart_rx(uartRegs);
	mCtrl_fpga_uart_rx_dataUpdate(uartRegs);
	mCtrl_fpga_uart_tx_dataUpdate(uartRegs);
	//mCtrl_fpga_uart_tx(uartRegs);
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_inner_uart_isr(UART_REGS *uartRegs)
{
	mCtrl_inner_uart_rx(uartRegs);
	//mCtrl_inner_uart_rx_dataUpdate(uartRegs);
	mCtrl_inner_uart_tx_dataUpdate(uartRegs);

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_inner_uart_rx_isr(UART_REGS *uartRegs)
{

}


#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_uart_tx_dataUpdate(UART_REGS *uartRegs)
{
	if(uartRegs->txpwmCnt == uartRegs->rxcmdCnt  || uartRegs->txpwmCnt != uartRegs->tx_expect_Cnt)
	{
		return;
	}

	if(uartRegs->firmwareUpdateFlag == 0)
	{
		uuint8 uucState;
		uartRegs->txRegs.packet.header = UART_HEADER_DATA;

		uartRegs->txRegs.packet.packet = uartRegs->RxPacket[uartRegs->txpwmCnt%2];

		uucState.bit.bit0 = board_HSIO5_read_macro();

		if(mDrvRegs.startUpRegs.ulFirstCloseloopflag == 1)
			uucState.bit.bit1 = mCtrl_status_servoStateGet_macro();
		else
			uucState.bit.bit1 = 0;

		uucState.bit.bit2 = mCtrl_homelimitbit0Get_macro();
		uucState.bit.bit3 = mCtrl_status_homeFindedGet_macro();
		uucState.bit.bit4 = mCtrl_homelimitbit1Get_macro();

		if(mCtrlRegs.tcurveRegs.ultcurve_enable == 0)
		{
			if(mCtrlRegs.tcurveRegs.ulfirsthome == 0)
			{
				uucState.bit.bit5 = 0;
				uucState.bit.bit6 = mCtrl_status_zeroSpeedGet_macro();
			}else
			{
				uucState.bit.bit5 = mCtrl_status_inPositioGet_macro();
				uucState.bit.bit6 = mCtrl_status_zeroSpeedGet_macro();
			}
		}else
		{
			uucState.bit.bit5 = 0;
			uucState.bit.bit6 = 0;
		}
		/*if(uucState.bit.bit5 == 1)
			board_HSIO1_on_macro();
		else
			board_HSIO1_off_macro();
		*/
		uucState.bit.bit7 = mCtrl_status_alarmGet_macro() || mCtrl_status_warningGet_macro();
		uuint32 uulData;

		uartRegs->txRegs.packet.ctrl_st = uucState.uchar;

		switch(uartRegs->txRegs.packet.packet)
		{
			case UART_PACKET_PARA_CH0_SET:
			case UART_PACKET_PARA_CH0_GET:
				uulData.dword = mCtrl_para_D0ChGet_macro();
			break;
			case UART_PACKET_PARA_CH0_DATA_SET:
			case UART_PACKET_PARA_CH0_DATA_GET:
				uulData.dword = para_valueGet(mCtrl_para_D0ChGet_macro());
			break;
			case UART_PACKET_PARA_CH1_SET:
			case UART_PACKET_PARA_CH1_GET:
				uulData.dword = mCtrl_para_D1ChGet_macro();
			break;
			case UART_PACKET_PARA_CH1_DATA_SET:
			case UART_PACKET_PARA_CH1_DATA_GET:
				uulData.dword = para_valueGet(mCtrl_para_D1ChGet_macro());
			break;
			case UART_PACKET_ALARM_SET:
			case UART_PACKET_ALARM_GET:
				uulData.dword = mDrv_mDrvAlarmGet_macro();
			break;

			case UART_PACKET_PCMD_ABS_SET:
			case UART_PACKET_PCMD_INC_SET:
			case UART_PACKET_INC_TCURVE_SET:
			case UART_PACKET_ABS_TCURVE_SET:
				if(mCtrl_status_homeFindedGet_macro() == 1)
				{
					uulData.dword = mCtrl_ulPcmdGet_macro() - mCtrl_ulPHomeGet_macro();
				}
				else
				{
					uulData.dword =	0;
				}
			break;
			case UART_PACKET_VERSION_GET:
				uulData.dword = para_valueGet_macro(PARA_FIRMWARE_VERSION);
			break;
			default:
				if(mCtrl_status_homeFindedGet_macro() == 1)
				{
					uulData.dword = mCtrl_ulPfbkGet_macro() - mCtrl_ulPHomeGet_macro();
				}
				else
				{
					uulData.dword =	mCtrl_ulPfbkGet_macro();
				}
			break;
		}

		uartRegs->txRegs.packet.data0 = uulData.byte.byte3;
		uartRegs->txRegs.packet.data1 = uulData.byte.byte2;
		uartRegs->txRegs.packet.data2 = uulData.byte.byte1;
		uartRegs->txRegs.packet.data3 = uulData.byte.byte0;
		uartRegs->txRegs.packet.data4 = uartRegs->rxRegs.packet.data4;
		uartRegs->txRegs.packet.data5 = uartRegs->rxRegs.packet.data5;
	}

	mCtrl_uart_firmwareUpdate_tx(uartRegs);

	uartRegs->tx_expect_Cnt++;

	LPUART_EnableInterrupts(uartRegs->module,kLPUART_TxDataRegEmptyInterruptEnable);

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_uart_tx(UART_REGS *uartRegs)
{

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_uart_rx(UART_REGS *uartRegs)
{
	int32 queue_size;
	int32 local_read_cnt;
	if(uartRegs->firmwareReceiveFlag == 0)
	{
		queue_size = Queue_GetSize(&uartRegs->Rx_Data_Queue);

		if(queue_size == 0 || uartRegs->global_read_cnt == uartRegs->rxisrCnt)	return;

		while( queue_size > 0)
		{
			uartRegs->rxRegs.data[uartRegs->rxCnt] = Queue_Pop(&uartRegs->Rx_Data_Queue);
			uartRegs->global_read_cnt++;
			local_read_cnt++;

			if(uartRegs->rxCnt == 0)
			{
				if(uartRegs->rxRegs.data[uartRegs->rxCnt] == UART_HEADER_DATA)
				{
					uartRegs->packetMode = UART_PACKET_MODE0_9BITS;
				}
				else if(uartRegs->rxRegs.data[uartRegs->rxCnt] == UART_NOSEWHEEL_HEADER_DATA )
				{
					uartRegs->packetMode = UART_PACKET_MODE2_NOSE;
				}
				else
				{
					return;
				}
			}

			uartRegs->rxCnt++;

			if(uartRegs->rxCnt == UART_TX_PACKET_LENGTH || local_read_cnt >= 4 || uartRegs->global_read_cnt == uartRegs->rxisrCnt)
			{
				break;
			}

		}
	}
	else
	{
		while(device_uart_module_rxFifoEmpty_macro(uartRegs->module) == 0)
		{
			*programIndex = device_uart_module_rxReadByte_macro(uartRegs->module);

			checkSum += *programIndex;

			uartRegs->rxCnt++;

			if(uartRegs->rxCnt >= uartRegs->firmwareUpdateLength)
			{
				uartRegs->rxCnt = 0;

				uartRegs->txUpdate = UART_TX_DATA_UPDATE;
				uartRegs->rxCheckFail = UART_RX_CHECK_PASS;
				uartRegs->rxUpdate = UART_RX_DATA_UPDATE;
				uartRegs->rxState = UART_RX_STATE_BUSY;

				uartRegs->firmwareReceiveFlag = 0;
			}else
			{
				programIndex++;
				if(uartRegs->rxCnt % uartRegs->firmwareUpdatePacketLength  == 0)
				{
					uartRegs->txUpdate = UART_TX_DATA_UPDATE;
					uartRegs->rxCheckFail = UART_RX_CHECK_PASS;
					uartRegs->rxUpdate = UART_RX_DATA_UPDATE;
					uartRegs->rxState = UART_RX_STATE_BUSY;
					return;
				}

				if(device_uart_module_rxFifoEmpty_macro(uartRegs->module)!=0)
					return;

			}
		}
		if(uartRegs->rxCnt >= 2)
		{
			if(uartRegs->rxRegs.packet.packet == UART_PACKET_FIRMWARE_RECEIVE)
			{
				uartRegs->firmwareReceiveFlag = 1;
				uartRegs->rxCnt = 0;
			}
		}

	}

	if(uartRegs->rxCnt < UART_TX_PACKET_LENGTH)
	{
		return;
	}

	uartRegs->RxPacket[uartRegs->rxcmdCnt % 2] = uartRegs->rxRegs.packet.packet;

	uartRegs->rxCnt = 0;
	// clear rx counter

	uartRegs->rxUpdate = UART_RX_DATA_UPDATE;

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_uart_rx_dataUpdate(UART_REGS *uartRegs)
{

	if(uartRegs->rxUpdate == UART_RX_DATA_IDLE) return; // check rx process finish

	uuint8 uucCtrl;
	uucCtrl.uchar = uartRegs->rxRegs.packet.ctrl_st;


	uartRegs->rxCheckFail = UART_RX_CHECK_PASS;

	if(uartRegs->firmwareUpdateFlag == 0)
	{
		if(uartRegs->rxRegs.packet.packet != 0x03)
		{
			mCtrl_cmd_servoOnSet_macro(uucCtrl.bit.bit1);
			mCtrl_cmd_homeSet_macro(uucCtrl.bit.bit3);
			mCtrl_cmd_homeFindSet_macro(uucCtrl.bit.bit2);
			mCtrl_cmd_alarm_clrSet_macro(uucCtrl.bit.bit7);
			mCtrl_cmd_emgSet_macro(uucCtrl.bit.bit4);
		}

		if(mCtrl_cmd_alarm_clrGet_macro() == 1)
		{
			mCtrlRegs.homeLimitRegs.ulHomeFindAlarm = 0;
			mCtrlRegs.homeLimitRegs.ulLimitHomeSignalErr = 0;

			mDrv_mDrvAlarmClearFlagSet_macro(true);
		}

		uuint32 uulData;
		uulData.byte.byte0 = uartRegs->rxRegs.packet.data3;
		uulData.byte.byte1 = uartRegs->rxRegs.packet.data2;
		uulData.byte.byte2 = uartRegs->rxRegs.packet.data1;
		uulData.byte.byte3 = uartRegs->rxRegs.packet.data0;

		mCtrlRegs.uartRxCmd[uartRegs->rxRegs.packet.packet](uulData.dword);

	}

	mCtrl_uart_firmwareUpdate_rx(uartRegs);

	uartRegs->rxcmdCnt++;
	uartRegs->rxUpdate = UART_RX_DATA_IDLE;

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_inner_uart_tx_dataUpdate(UART_REGS *uartRegs)
{
#ifdef TESTMODE

#else
	//if( mCtrlRegs.uart1Regs.txState == UART_TX_STATE_BUSY)	return;

	if(uartRegs->txUpdate == UART_TX_STATE_IDLE)		return;

	static uint32 TxXcmdUpdateFlag;

	if( TxXcmdUpdateFlag == 0)
	{
		mCtrlRegs.uart2Regs.txRegs.packet.header = 0x32;
		mCtrlRegs.uart2Regs.txRegs.packet.packet = uartRegs->rxRegs.packet.packet;
		mCtrlRegs.uart2Regs.txRegs.packet.ctrl_st = uartRegs->rxRegs.packet.ctrl_st;
		mCtrlRegs.uart2Regs.txRegs.packet.data0 = uartRegs->rxRegs.packet.data0;
		mCtrlRegs.uart2Regs.txRegs.packet.data1 = uartRegs->rxRegs.packet.data1;
		mCtrlRegs.uart2Regs.txRegs.packet.data2 = uartRegs->rxRegs.packet.data2;
		mCtrlRegs.uart2Regs.txRegs.packet.data3 = uartRegs->rxRegs.packet.data3;
		mCtrlRegs.uart2Regs.txRegs.packet.data4 = 0x0D;
		mCtrlRegs.uart2Regs.txRegs.packet.data5 = 0x0A;

		TxXcmdUpdateFlag = 1;
	}

	mCtrlRegs.uart2Regs.txState = UART_TX_STATE_BUSY;

	LPUART_EnableInterrupts(LPUART3, kLPUART_TxDataRegEmptyInterruptEnable);
	EnableIRQ(LPUART3_SERIAL_RX_TX_IRQN);

	TxXcmdUpdateFlag = 0;

	uartRegs->txUpdate = UART_TX_STATE_IDLE;
#endif
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_inner_uart_rx_dataUpdate(UART_REGS *uartRegs)
{

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_inner_uart_rx(UART_REGS *uartRegs)
{
#ifdef TESTMODE

#else
	int32 queue_size;
	int32 local_read_cnt;

	queue_size = Queue_GetSize(&uartRegs->Rx_Data_Queue);

	if(queue_size == 0 || uartRegs->global_read_cnt == uartRegs->rxisrCnt)	return;

	while( queue_size > 0 && uartRegs->rxCnt < UART_TX_REDUCE_PACKET_LENGTH  )
	{
		uartRegs->rxRegs.data[uartRegs->rxCnt] = Queue_Pop(&uartRegs->Rx_Data_Queue);

		uartRegs->global_read_cnt++;

		local_read_cnt++;

		if(uartRegs->rxCnt == 0)
		{
			if(uartRegs->rxRegs.data[uartRegs->rxCnt] == UART_REDUCE_HEADER_DATA)
			{
				uartRegs->packetMode = UART_PACKET_MODE1_7BITS;
			}
			else
			{
				return;
			}
		}

		uartRegs->rxCnt++;

		if(uartRegs->rxCnt >= UART_TX_REDUCE_PACKET_LENGTH || local_read_cnt >= 4 || uartRegs->global_read_cnt == uartRegs->rxisrCnt)
		{
			break;
		}

	}

	if(uartRegs->rxCnt < UART_TX_REDUCE_PACKET_LENGTH)
	{
		return;
	}

	uartRegs->txUpdate= UART_TX_DATA_UPDATE;
	// clear rx counter
	uartRegs->rxCnt = 0;

	DisableIRQ(LPUART4_SERIAL_RX_TX_IRQN);
#endif
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_fpga_uart_tx_dataUpdate(UART_REGS *uartRegs)
{
#ifdef TESTMODE

#else
	if(uartRegs->txpwmCnt == uartRegs->rxcmdCnt  || uartRegs->txpwmCnt != uartRegs->tx_expect_Cnt ||  uartRegs->firmwareReceiveFlag == 1)
	{
		return;
	}

	if(uartRegs->firmwareUpdateFlag == 0)
	{
		uuint8 uucState;
		uartRegs->txRegs.packet.header = UART_HEADER_DATA;

		uartRegs->txRegs.packet.packet = uartRegs->RxPacket[uartRegs->txpwmCnt%2];

		uucState.bit.bit0 = board_HSIO5_read_macro();

		if(mDrvRegs.startUpRegs.ulFirstCloseloopflag == 1)
			uucState.bit.bit1 = mCtrl_status_servoStateGet_macro();
		else
			uucState.bit.bit1 = 0;

		uucState.bit.bit2 = mCtrl_homelimitbit0Get_macro();
		uucState.bit.bit3 = mCtrl_status_homeFindedGet_macro();
		uucState.bit.bit4 = mCtrl_homelimitbit1Get_macro();

		if(mCtrlRegs.tcurveRegs.ultcurve_enable == 0)
		{
			if(mCtrlRegs.tcurveRegs.ulfirsthome == 0)
			{
				uucState.bit.bit5 = 0;
				uucState.bit.bit6 = mCtrl_status_zeroSpeedGet_macro();
			}else
			{
				uucState.bit.bit5 = mCtrl_status_inPositioGet_macro();
				uucState.bit.bit6 = mCtrl_status_zeroSpeedGet_macro();
			}
		}else
		{
			uucState.bit.bit5 = 0;
			uucState.bit.bit6 = 0;
		}
		/*if(uucState.bit.bit5 == 1)
			board_HSIO1_on_macro();
		else
			board_HSIO1_off_macro();
		*/
		uucState.bit.bit7 = mCtrl_status_alarmGet_macro() || mCtrl_status_warningGet_macro();
		uuint32 uulData;

		uartRegs->txRegs.packet.ctrl_st = uucState.uchar;

		switch(uartRegs->txRegs.packet.packet)
		{
			case UART_PACKET_PARA_CH0_SET:
			case UART_PACKET_PARA_CH0_GET:
				uulData.dword = mCtrl_para_D0ChGet_macro();
			break;
			case UART_PACKET_PARA_CH0_DATA_SET:
			case UART_PACKET_PARA_CH0_DATA_GET:
				uulData.dword = para_valueGet(mCtrl_para_D0ChGet_macro());
			break;
			case UART_PACKET_PARA_CH1_SET:
			case UART_PACKET_PARA_CH1_GET:
				uulData.dword = mCtrl_para_D1ChGet_macro();
			break;
			case UART_PACKET_PARA_CH1_DATA_SET:
			case UART_PACKET_PARA_CH1_DATA_GET:
				uulData.dword = para_valueGet(mCtrl_para_D1ChGet_macro());
			break;
			case UART_PACKET_ALARM_SET:
			case UART_PACKET_ALARM_GET:
				uulData.dword = mDrv_mDrvAlarmGet_macro();
			break;

			case UART_PACKET_PCMD_ABS_SET:
			case UART_PACKET_PCMD_INC_SET:
			case UART_PACKET_INC_TCURVE_SET:
			case UART_PACKET_ABS_TCURVE_SET:
				if(mCtrl_status_homeFindedGet_macro() == 1)
				{
					uulData.dword = mCtrl_ulPcmdGet_macro() - mCtrl_ulPHomeGet_macro();
				}
				else
				{
					uulData.dword =	0;
				}
			break;
			case UART_PACKET_VERSION_GET:
				uulData.dword = para_valueGet_macro(PARA_FIRMWARE_VERSION);
			break;
			default:
				if(mCtrl_status_homeFindedGet_macro() == 1)
				{
					uulData.dword = mCtrl_ulPfbkGet_macro() - mCtrl_ulPHomeGet_macro();
				}
				else
				{
					uulData.dword =	0;
				}
			break;
		}

		uartRegs->txRegs.packet.data0 = uulData.byte.byte3;
		uartRegs->txRegs.packet.data1 = uulData.byte.byte2;
		uartRegs->txRegs.packet.data2 = uulData.byte.byte1;
		uartRegs->txRegs.packet.data3 = uulData.byte.byte0;
		uartRegs->txRegs.packet.data4 = uartRegs->rxRegs.packet.data4;
		uartRegs->txRegs.packet.data5 = uartRegs->rxRegs.packet.data5;
	}

	mCtrl_uart_firmwareUpdate_tx(uartRegs);

	uartRegs->tx_expect_Cnt++;

	if( uartRegs->firmwareUpdateState.bit.bit7 == 1 )
	{
		LPUART_DisableInterrupts(uartRegs->module, kLPUART_RxDataRegFullInterruptEnable);
		LPUART_DisableInterrupts(uartRegs->module, kLPUART_IdleLineInterruptEnable);

		uartRegs->firmwareReceiveFlag = 1;
		uartRegs->rxCnt = 0;

	}

	LPUART_EnableInterrupts(uartRegs->module, kLPUART_TxDataRegEmptyInterruptEnable);

#endif
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_fpga_uart_tx(UART_REGS *uartRegs)
{

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_fpga_uart_rx(UART_REGS *uartRegs)
{
#ifdef TESTMODE

#else
	int32 queue_size;
	int32 local_read_cnt;
	static uint32 ulreset_cnt = 0;

	if(uartRegs->ulrestflag == 2)
	{
		ulreset_cnt++;
		if(ulreset_cnt > 10 )
			NVIC_SystemReset();
	}

	if(uartRegs->firmwareReceiveFlag == 0)
	{
		queue_size = Queue_GetSize(&uartRegs->Rx_Data_Queue);

		if(queue_size == 0 || uartRegs->global_read_cnt == uartRegs->rxisrCnt)	return;

		while( queue_size > 0)
		{
			uartRegs->rxRegs.data[uartRegs->rxCnt] = Queue_Pop(&uartRegs->Rx_Data_Queue);
			uartRegs->global_read_cnt++;
			local_read_cnt++;

			if(uartRegs->rxCnt == 0)
			{
				if(uartRegs->rxRegs.data[uartRegs->rxCnt] == UART_HEADER_DATA)
				{
					uartRegs->packetMode = UART_PACKET_MODE0_9BITS;
				}
				else if(uartRegs->rxRegs.data[uartRegs->rxCnt] == UART_NOSEWHEEL_HEADER_DATA )
				{
					uartRegs->packetMode = UART_PACKET_MODE2_NOSE;
				}
				else
				{
					return;
				}
			}

			uartRegs->rxCnt++;

			if(uartRegs->rxCnt == UART_TX_PACKET_LENGTH || local_read_cnt >= 4 || uartRegs->global_read_cnt == uartRegs->rxisrCnt)
			{
				break;
			}

		}
	}
	else
	{
		while(device_uart_module_rxFifoEmpty_macro(uartRegs->module) == 0)
		{
			*programIndex = device_uart_module_rxReadByte_macro(uartRegs->module);

			checkSum += *programIndex;

			uartRegs->rxCnt++;

			if(uartRegs->rxCnt >= uartRegs->firmwareUpdateLength)
			{
				uartRegs->rxCnt = 0;

				uartRegs->txUpdate = UART_TX_DATA_UPDATE;
				uartRegs->rxCheckFail = UART_RX_CHECK_PASS;
				uartRegs->rxUpdate = UART_RX_DATA_UPDATE;
				uartRegs->rxState = UART_RX_STATE_BUSY;

				uartRegs->tx_expect_Cnt = uartRegs->txpwmCnt;
				uartRegs->firmwareReceiveFlag = 0;
				uartRegs->firmwareRxDoneFlag = 1;

				LPUART_EnableInterrupts(uartRegs->module, kLPUART_RxDataRegFullInterruptEnable);
				LPUART_EnableInterrupts(uartRegs->module, kLPUART_IdleLineInterruptEnable);
			}else
			{
				programIndex++;
				if(uartRegs->rxCnt % uartRegs->firmwareUpdatePacketLength  == 0)
				{
					uartRegs->txUpdate = UART_TX_DATA_UPDATE;
					uartRegs->rxCheckFail = UART_RX_CHECK_PASS;
					uartRegs->rxUpdate = UART_RX_DATA_UPDATE;
					uartRegs->rxState = UART_RX_STATE_BUSY;

					mCtrl_uart_firmwareUpdate_tx(uartRegs);
					LPUART_EnableInterrupts(uartRegs->module, kLPUART_TxDataRegEmptyInterruptEnable);
					return;
				}

				//if(device_uart_module_rxFifoEmpty_macro(uartRegs->module)!=0)
					//return;

			}

		}
		return;
	}

	if(uartRegs->rxCnt < UART_TX_PACKET_LENGTH)
	{
		return;
	}


	uartRegs->rxdataReg_H = 0;
	uartRegs->rxdataReg_H |= ((uint32) uartRegs->rxRegs.data[1] << 16);
	uartRegs->rxdataReg_H |= ((uint32) uartRegs->rxRegs.data[2] << 8);
	uartRegs->rxdataReg_H |= ((uint32) uartRegs->rxRegs.data[3]);

	uartRegs->rxdataReg_L = 0;
	uartRegs->rxdataReg_L |= ((uint32) uartRegs->rxRegs.data[4] << 16);
	uartRegs->rxdataReg_L |= ((uint32) uartRegs->rxRegs.data[5] << 8);
	uartRegs->rxdataReg_L |= ((uint32) uartRegs->rxRegs.data[6]);

	uartRegs->XcmdPendStatus = 0;

	if(uartRegs->packetMode == UART_PACKET_MODE2_NOSE)
	{
		static uint32 XcmdUpdateFlag;

		if(XcmdUpdateFlag  == 0)
		{
			mCtrlRegs.uart3Regs.txRegs.packet.packet = (uartRegs->rxdataReg_H & 0x00ff0000) >> 16;
			mCtrlRegs.uart3Regs.txRegs.packet.ctrl_st = (uartRegs->rxdataReg_H & 0x0000ff00) >> 8;
			mCtrlRegs.uart3Regs.txRegs.packet.data0 = (uartRegs->rxdataReg_H & 0x000000ff);
			mCtrlRegs.uart3Regs.txRegs.packet.data1 = (uartRegs->rxdataReg_L & 0x00ff0000) >> 16;
			mCtrlRegs.uart3Regs.txRegs.packet.data2 = (uartRegs->rxdataReg_L & 0x0000ff00) >> 8;
			mCtrlRegs.uart3Regs.txRegs.packet.data3 = (uartRegs->rxdataReg_L & 0x000000ff);
			mCtrlRegs.uart3Regs.txRegs.packet.header = 0x51;
			XcmdUpdateFlag = 1;
		}

		if( mCtrlRegs.uart3Regs.txState == UART_TX_STATE_IDLE)
		{

			mCtrlRegs.uart3Regs.txState = UART_TX_STATE_BUSY;

			mCtrlRegs.uart3Regs.txCnt = UART_TX_REDUCE_PACKET_LENGTH;
			uartRegs->rxCnt = 0;
			XcmdUpdateFlag = 0;

			LPUART_EnableInterrupts(LPUART4,kLPUART_TxDataRegEmptyInterruptEnable);

		}

		uartRegs->XcmdPendStatus = 1;

		EnableIRQ(LPUART4_SERIAL_RX_TX_IRQN);

		return;

	}

	uartRegs->RxPacket[uartRegs->rxcmdCnt % 2] = (uartRegs->rxdataReg_H & 0x00ff0000) >> 16;

	uartRegs->rxCnt = 0;
	// clear rx counter

	uartRegs->rxUpdate = UART_RX_DATA_UPDATE;
#endif
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_fpga_uart_rx_dataUpdate(UART_REGS *uartRegs)
{
#ifdef TESTMODE

#else
	if(uartRegs->rxUpdate == UART_RX_DATA_IDLE) return; // check rx process finish

	uuint8 uucCtrl;

	uucCtrl.uchar = uartRegs->rxRegs.packet.ctrl_st;

	uartRegs->rxCheckFail = UART_RX_CHECK_PASS;

	if(uartRegs->firmwareUpdateFlag == 0)
	{
		if(uartRegs->rxRegs.packet.packet != 0x03)
		{
			mCtrl_cmd_servoOnSet_macro(uucCtrl.bit.bit1);
			mCtrl_cmd_homeSet_macro(uucCtrl.bit.bit3);
			mCtrl_cmd_homeFindSet_macro(uucCtrl.bit.bit2);
			mCtrl_cmd_alarm_clrSet_macro(uucCtrl.bit.bit7);
			mCtrl_cmd_emgSet_macro(uucCtrl.bit.bit4);
		}

		if(mCtrl_cmd_alarm_clrGet_macro() == 1)
		{
			mCtrlRegs.homeLimitRegs.ulHomeFindAlarm = 0;
			mCtrlRegs.homeLimitRegs.ulLimitHomeSignalErr = 0;

			mDrv_mDrvAlarmClearFlagSet_macro(true);
		}

		uuint32 uulData;
		uulData.byte.byte0 = uartRegs->rxRegs.packet.data3;
		uulData.byte.byte1 = uartRegs->rxRegs.packet.data2;
		uulData.byte.byte2 = uartRegs->rxRegs.packet.data1;
		uulData.byte.byte3 = uartRegs->rxRegs.packet.data0;

		mCtrlRegs.uartRxCmd[uartRegs->rxRegs.packet.packet](uulData.dword);

	}

	mCtrl_uart_firmwareUpdate_rx(uartRegs);

	uartRegs->rxcmdCnt++;
	uartRegs->rxUpdate = UART_RX_DATA_IDLE;
#endif
}


void uartPacketCmd0(uint32 uldata)
{

}
void uartPacketCmd1(uint32 uldata)
{

}
void uartPacketCmd2(uint32 uldata)
{

}
void uartPacketCmd3(uint32 uldata)
{

}
void uartPacketCmd4(uint32 uldata)
{

}
void uartPacketCmd5(uint32 uldata)
{

}
void uartPacketCmd6(uint32 uldata)
{

}
void uartPacketCmd7(uint32 uldata)
{

}
void uartPacketCmd8(uint32 uldata)
{

}
void uartPacketCmd9(uint32 uldata)
{

}
void uartPacketCmd10(uint32 uldata)
{

}
void uartPacketCmd11(uint32 uldata)
{

}
void uartPacketCmd12(uint32 uldata)
{

}
void uartPacketCmd13(uint32 uldata)
{

}
void uartPacketCmd14(uint32 uldata)
{

}
void uartPacketCmd15(uint32 uldata)
{

}
void uartPacketCmd16(uint32 uldata)
{

}
void uartPacketCmd17(uint32 uldata)
{
	uint32 ulABSPCMD = uldata;

	if((mCtrlRegs.homeLimitRegs.homeFindMode != home_disable) && ((mCtrlRegs.statusRegs.data.homeFinded == 1) && (mDrv_ulAngleCloseFlagGet_macro() == 1)))
	{
		if(mCtrlRegs.homeLimitRegs.softNegLimitEnable == 1)
		{
			if((int32)uldata <(int32)mCtrlRegs.homeLimitRegs.ulSoftNegLimit)
				ulABSPCMD  = mCtrlRegs.homeLimitRegs.ulSoftNegLimit;
		}
		if(mCtrlRegs.homeLimitRegs.softPosLimitEnable == 1)
		{
			if((int32)uldata >(int32)mCtrlRegs.homeLimitRegs.ulSoftPosLimit)
				ulABSPCMD  = mCtrlRegs.homeLimitRegs.ulSoftPosLimit;
		}
	}

	mCtrl_ulPcmdUartSet_macro(mCtrl_ulPHomeGet_macro() + ulABSPCMD);
}
void uartPacketCmd18(uint32 uldata)
{

}
void uartPacketCmd19(uint32 uldata)
{

	uint32 ulINCPCMD = uldata;

	if((mCtrlRegs.homeLimitRegs.homeFindMode != home_disable) && ((mCtrlRegs.statusRegs.data.homeFinded == 1) && (mDrv_ulAngleCloseFlagGet_macro() == 1)))
	{
		if(mCtrlRegs.homeLimitRegs.softNegLimitEnable == 1)
		{
			if(((int32)(mCtrlRegs.ulPcmdUart + uldata  - mCtrlRegs.homeLimitRegs.ulPHome)) < ((int32)mCtrlRegs.homeLimitRegs.ulSoftNegLimit))
				ulINCPCMD  = (uint32) ((int32)mCtrlRegs.homeLimitRegs.ulPHome + mCtrlRegs.homeLimitRegs.ulSoftNegLimit-mCtrlRegs.ulPcmdUart);

		}
		if(mCtrlRegs.homeLimitRegs.softPosLimitEnable == 1)// mCtrlRegs.ulPcmdUart = mCtrlRegs.homeLimitRegs.ulPHome + mCtrlRegs.homeLimitRegs.ulSoftPosLimit
		{
			if(((int32)(mCtrlRegs.ulPcmdUart + uldata- mCtrlRegs.homeLimitRegs.ulPHome)) > ((int32)mCtrlRegs.homeLimitRegs.ulSoftPosLimit))
				ulINCPCMD  = (uint32)((int32) mCtrlRegs.homeLimitRegs.ulPHome + mCtrlRegs.homeLimitRegs.ulSoftPosLimit-mCtrlRegs.ulPcmdUart);
		}
	}
	mCtrl_ulPcmdUartSet_macro(mCtrl_ulPcmdUartGet_macro() + ulINCPCMD );
}
void uartPacketCmd20(uint32 uldata)
{

}
void uartPacketCmd21(uint32 uldata)
{

	uint32 ulTABSPCMD = uldata;

	if((mCtrlRegs.homeLimitRegs.homeFindMode != home_disable) && ((mCtrlRegs.statusRegs.data.homeFinded == 1) && (mDrv_ulAngleCloseFlagGet_macro() == 1)))
	{
		if(mCtrlRegs.homeLimitRegs.softNegLimitEnable == 1)
		{
			if((int32)uldata <(int32)mCtrlRegs.homeLimitRegs.ulSoftNegLimit)
				ulTABSPCMD  = mCtrlRegs.homeLimitRegs.ulSoftNegLimit;
		}
		if(mCtrlRegs.homeLimitRegs.softPosLimitEnable == 1)
		{
			if((int32)uldata >(int32)mCtrlRegs.homeLimitRegs.ulSoftPosLimit)
				ulTABSPCMD  = mCtrlRegs.homeLimitRegs.ulSoftPosLimit;
		}
	}

	mCtrlRegs.tcurveRegs.ulStartPcmd = mCtrl_ulPcmdUartGet_macro();

	mCtrl_Tcurve_parameterUpdate(&mCtrlRegs.tcurveRegs);
	mCtrl_Tcurve_Clear(&mCtrlRegs.tcurveRegs);
	mCtrl_Tcurve_Setting(&mCtrlRegs.tcurveRegs,(int32)mCtrl_ulPHomeGet_macro() + ulTABSPCMD - mCtrlRegs.ulPcmdUart);

}
void uartPacketCmd22(uint32 uldata)
{

}
void uartPacketCmd23(uint32 uldata)
{

	uint32 ulTINCPCMD = uldata;

	if((mCtrlRegs.homeLimitRegs.homeFindMode != home_disable) && ((mCtrlRegs.statusRegs.data.homeFinded == 1) && (mDrv_ulAngleCloseFlagGet_macro() == 1)))
	{
		if(mCtrlRegs.homeLimitRegs.softNegLimitEnable == 1)
		{
			if(((int32)(mCtrlRegs.ulPcmdUart + uldata  - mCtrlRegs.homeLimitRegs.ulPHome)) < ((int32)mCtrlRegs.homeLimitRegs.ulSoftNegLimit))
				ulTINCPCMD  = (uint32) ((int32)mCtrlRegs.homeLimitRegs.ulPHome + mCtrlRegs.homeLimitRegs.ulSoftNegLimit-mCtrlRegs.ulPcmdUart);
		}
		if(mCtrlRegs.homeLimitRegs.softPosLimitEnable == 1)// mCtrlRegs.ulPcmdUart = mCtrlRegs.homeLimitRegs.ulPHome + mCtrlRegs.homeLimitRegs.ulSoftPosLimit
		{
			if(((int32)(mCtrlRegs.ulPcmdUart + uldata - mCtrlRegs.homeLimitRegs.ulPHome)) > ((int32)mCtrlRegs.homeLimitRegs.ulSoftPosLimit))
				ulTINCPCMD  = (uint32)((int32) mCtrlRegs.homeLimitRegs.ulPHome + mCtrlRegs.homeLimitRegs.ulSoftPosLimit-mCtrlRegs.ulPcmdUart);
		}
	}
	mCtrlRegs.tcurveRegs.ulStartPcmd = mCtrl_ulPcmdUartGet_macro();

	mCtrl_Tcurve_parameterUpdate(&mCtrlRegs.tcurveRegs);
	mCtrl_Tcurve_Clear(&mCtrlRegs.tcurveRegs);
	mCtrl_Tcurve_Setting(&mCtrlRegs.tcurveRegs,ulTINCPCMD);

}
void uartPacketCmd24(uint32 uldata)
{

}
void uartPacketCmd25(uint32 uldata)
{

}
void uartPacketCmd26(uint32 uldata)
{

}
void uartPacketCmd27(uint32 uldata)
{

}
void uartPacketCmd28(uint32 uldata)
{

}
void uartPacketCmd29(uint32 uldata)
{

}
void uartPacketCmd30(uint32 uldata)
{

}
void uartPacketCmd31(uint32 uldata)
{

}
void uartPacketCmd32(uint32 uldata)
{

}
void uartPacketCmd33(uint32 uldata)
{
	mCtrl_para_D0ChSet_macro(uldata);
}
void uartPacketCmd34(uint32 uldata)
{

}
void uartPacketCmd35(uint32 uldata)
{
	mCtrl_para_D0Set_macro(uldata);
	para_update_macro(mCtrl_para_D0ChGet_macro(), mCtrl_para_D0Get_macro());
}
void uartPacketCmd36(uint32 uldata)
{

}
void uartPacketCmd37(uint32 uldata)
{
	mCtrl_para_D1ChSet_macro(uldata);
}
void uartPacketCmd38(uint32 uldata)
{

}
void uartPacketCmd39(uint32 uldata)
{
	mCtrl_para_D1Set_macro(uldata);
	para_update_macro(mCtrl_para_D1ChGet_macro(), mCtrl_para_D1Get_macro());
}
void uartPacketCmd40(uint32 uldata)
{

}
void uartPacketCmd41(uint32 uldata)
{

}
void uartPacketCmd42(uint32 uldata)
{

}
void uartPacketCmd43(uint32 uldata)
{

}
void uartPacketCmd44(uint32 uldata)
{

}
void uartPacketCmd45(uint32 uldata)
{

}
void uartPacketCmd46(uint32 uldata)
{

}
void uartPacketCmd47(uint32 uldata)
{

}
void uartPacketCmd48(uint32 uldata)
{

}
void uartPacketCmd49(uint32 uldata)
{

}
void uartPacketCmd50(uint32 uldata)
{

}
void uartPacketCmd51(uint32 uldata)
{

}
void uartPacketCmd52(uint32 uldata)
{

}
void uartPacketCmd53(uint32 uldata)
{

}
void uartPacketCmd54(uint32 uldata)
{

}
void uartPacketCmd55(uint32 uldata)
{

}
void uartPacketCmd56(uint32 uldata)
{

}
void uartPacketCmd57(uint32 uldata)
{

}
void uartPacketCmd58(uint32 uldata)
{

}
void uartPacketCmd59(uint32 uldata)
{

}
void uartPacketCmd60(uint32 uldata)
{

}
void uartPacketCmd61(uint32 uldata)
{

}
void uartPacketCmd62(uint32 uldata)
{

}
void uartPacketCmd63(uint32 uldata)
{

}
void uartPacketCmd64(uint32 uldata)
{

}
void uartPacketCmd65(uint32 uldata)
{

}
void uartPacketCmd66(uint32 uldata)
{

}
void uartPacketCmd67(uint32 uldata)
{

}
void uartPacketCmd68(uint32 uldata)
{

}
void uartPacketCmd69(uint32 uldata)
{

}
void uartPacketCmd70(uint32 uldata)
{

}
void uartPacketCmd71(uint32 uldata)
{

}
void uartPacketCmd72(uint32 uldata)
{

}
void uartPacketCmd73(uint32 uldata)
{

}
void uartPacketCmd74(uint32 uldata)
{

}
void uartPacketCmd75(uint32 uldata)
{

}
void uartPacketCmd76(uint32 uldata)
{

}
void uartPacketCmd77(uint32 uldata)
{

}
void uartPacketCmd78(uint32 uldata)
{

}
void uartPacketCmd79(uint32 uldata)
{

}
void uartPacketCmd80(uint32 uldata)
{

}
void uartPacketCmd81(uint32 uldata)
{

}
void uartPacketCmd82(uint32 uldata)
{

}
void uartPacketCmd83(uint32 uldata)
{

}
void uartPacketCmd84(uint32 uldata)
{

}
void uartPacketCmd85(uint32 uldata)
{

}
void uartPacketCmd86(uint32 uldata)
{

}
void uartPacketCmd87(uint32 uldata)
{

}
void uartPacketCmd88(uint32 uldata)
{

}
void uartPacketCmd89(uint32 uldata)
{

}
void uartPacketCmd90(uint32 uldata)
{

}
void uartPacketCmd91(uint32 uldata)
{

}
void uartPacketCmd92(uint32 uldata)
{

}
void uartPacketCmd93(uint32 uldata)
{

}
void uartPacketCmd94(uint32 uldata)
{

}
void uartPacketCmd95(uint32 uldata)
{

}
void uartPacketCmd96(uint32 uldata)
{

}
void uartPacketCmd97(uint32 uldata)
{

}
void uartPacketCmd98(uint32 uldata)
{

}
void uartPacketCmd99(uint32 uldata)
{

}
void uartPacketCmd100(uint32 uldata)
{

}
void uartPacketCmd101(uint32 uldata)
{

}
void uartPacketCmd102(uint32 uldata)
{

}
void uartPacketCmd103(uint32 uldata)
{

}
void uartPacketCmd104(uint32 uldata)
{

}
void uartPacketCmd105(uint32 uldata)
{

}
void uartPacketCmd106(uint32 uldata)
{

}
void uartPacketCmd107(uint32 uldata)
{

}
void uartPacketCmd108(uint32 uldata)
{

}
void uartPacketCmd109(uint32 uldata)
{

}
void uartPacketCmd110(uint32 uldata)
{

}
void uartPacketCmd111(uint32 uldata)
{

}
void uartPacketCmd112(uint32 uldata)
{

}
void uartPacketCmd113(uint32 uldata)
{

}
void uartPacketCmd114(uint32 uldata)
{

}
void uartPacketCmd115(uint32 uldata)
{

}
void uartPacketCmd116(uint32 uldata)
{

}
void uartPacketCmd117(uint32 uldata)
{

}
void uartPacketCmd118(uint32 uldata)
{

}
void uartPacketCmd119(uint32 uldata)
{

}
void uartPacketCmd120(uint32 uldata)
{

}
void uartPacketCmd121(uint32 uldata)
{

}
void uartPacketCmd122(uint32 uldata)
{

}
void uartPacketCmd123(uint32 uldata)
{

}
void uartPacketCmd124(uint32 uldata)
{

}
void uartPacketCmd125(uint32 uldata)
{

}
void uartPacketCmd126(uint32 uldata)
{

}
void uartPacketCmd127(uint32 uldata)
{

}
void uartPacketCmd128(uint32 uldata)
{

}
void uartPacketCmd129(uint32 uldata)
{
	if(mCtrl_status_servoStateGet_macro() == 0)
	{
		if(uldata == 0x55AA00FF)
		{
			mCtrlRegs.uart1Regs.firmwareUpdateFlag = 1;
			mCtrlRegs.uart2Regs.firmwareUpdateFlag = 1;
			mCtrlRegs.uart3Regs.firmwareUpdateFlag = 1;
		}
	}
}
void uartPacketCmd130(uint32 uldata)
{

}
void uartPacketCmd131(uint32 uldata)
{

}
void uartPacketCmd132(uint32 uldata)
{

}
void uartPacketCmd133(uint32 uldata)
{

}
void uartPacketCmd134(uint32 uldata)
{
	if(mCtrl_status_servoStateGet_macro() == 0)
	{
		mCtrlRegs.ulfirmwareflashkey = uldata;
	}
}
void uartPacketCmd135(uint32 uldata)
{

}
void uartPacketCmd136(uint32 uldata)
{

}
void uartPacketCmd137(uint32 uldata)
{

}
void uartPacketCmd138(uint32 uldata)
{

}
void uartPacketCmd139(uint32 uldata)
{

}
void uartPacketCmd140(uint32 uldata)
{

}
void uartPacketCmd141(uint32 uldata)
{

}
void uartPacketCmd142(uint32 uldata)
{

}
void uartPacketCmd143(uint32 uldata)
{

}
void uartPacketCmd144(uint32 uldata)
{

}
void uartPacketCmd145(uint32 uldata)
{

}
void uartPacketCmd146(uint32 uldata)
{

}
void uartPacketCmd147(uint32 uldata)
{

}
void uartPacketCmd148(uint32 uldata)
{

}
void uartPacketCmd149(uint32 uldata)
{

}
void uartPacketCmd150(uint32 uldata)
{

}
void uartPacketCmd151(uint32 uldata)
{

}
void uartPacketCmd152(uint32 uldata)
{

}
void uartPacketCmd153(uint32 uldata)
{

}
void uartPacketCmd154(uint32 uldata)
{

}
void uartPacketCmd155(uint32 uldata)
{

}
void uartPacketCmd156(uint32 uldata)
{

}
void uartPacketCmd157(uint32 uldata)
{

}
void uartPacketCmd158(uint32 uldata)
{

}
void uartPacketCmd159(uint32 uldata)
{

}
void uartPacketCmd160(uint32 uldata)
{

}
void uartPacketCmd161(uint32 uldata)
{

}
void uartPacketCmd162(uint32 uldata)
{

}
void uartPacketCmd163(uint32 uldata)
{

}
void uartPacketCmd164(uint32 uldata)
{

}
void uartPacketCmd165(uint32 uldata)
{

}
void uartPacketCmd166(uint32 uldata)
{

}
void uartPacketCmd167(uint32 uldata)
{

}
void uartPacketCmd168(uint32 uldata)
{

}
void uartPacketCmd169(uint32 uldata)
{

}
void uartPacketCmd170(uint32 uldata)
{

}
void uartPacketCmd171(uint32 uldata)
{

}
void uartPacketCmd172(uint32 uldata)
{

}
void uartPacketCmd173(uint32 uldata)
{

}
void uartPacketCmd174(uint32 uldata)
{

}
void uartPacketCmd175(uint32 uldata)
{

}
void uartPacketCmd176(uint32 uldata)
{

}
void uartPacketCmd177(uint32 uldata)
{

}
void uartPacketCmd178(uint32 uldata)
{

}
void uartPacketCmd179(uint32 uldata)
{

}
void uartPacketCmd180(uint32 uldata)
{

}
void uartPacketCmd181(uint32 uldata)
{

}
void uartPacketCmd182(uint32 uldata)
{

}
void uartPacketCmd183(uint32 uldata)
{

}
void uartPacketCmd184(uint32 uldata)
{

}
void uartPacketCmd185(uint32 uldata)
{

}
void uartPacketCmd186(uint32 uldata)
{

}
void uartPacketCmd187(uint32 uldata)
{

}
void uartPacketCmd188(uint32 uldata)
{

}
void uartPacketCmd189(uint32 uldata)
{

}
void uartPacketCmd190(uint32 uldata)
{

}
void uartPacketCmd191(uint32 uldata)
{

}
void uartPacketCmd192(uint32 uldata)
{

}
void uartPacketCmd193(uint32 uldata)
{

}
void uartPacketCmd194(uint32 uldata)
{

}
void uartPacketCmd195(uint32 uldata)
{

}
void uartPacketCmd196(uint32 uldata)
{

}
void uartPacketCmd197(uint32 uldata)
{

}
void uartPacketCmd198(uint32 uldata)
{

}
void uartPacketCmd199(uint32 uldata)
{

}
void uartPacketCmd200(uint32 uldata)
{

}
void uartPacketCmd201(uint32 uldata)
{

}
void uartPacketCmd202(uint32 uldata)
{

}
void uartPacketCmd203(uint32 uldata)
{

}
void uartPacketCmd204(uint32 uldata)
{

}
void uartPacketCmd205(uint32 uldata)
{

}
void uartPacketCmd206(uint32 uldata)
{

}
void uartPacketCmd207(uint32 uldata)
{

}
void uartPacketCmd208(uint32 uldata)
{

}
void uartPacketCmd209(uint32 uldata)
{

}
void uartPacketCmd210(uint32 uldata)
{

}
void uartPacketCmd211(uint32 uldata)
{

}
void uartPacketCmd212(uint32 uldata)
{

}
void uartPacketCmd213(uint32 uldata)
{

}
void uartPacketCmd214(uint32 uldata)
{

}
void uartPacketCmd215(uint32 uldata)
{

}
void uartPacketCmd216(uint32 uldata)
{

}
void uartPacketCmd217(uint32 uldata)
{

}
void uartPacketCmd218(uint32 uldata)
{

}
void uartPacketCmd219(uint32 uldata)
{

}
void uartPacketCmd220(uint32 uldata)
{

}
void uartPacketCmd221(uint32 uldata)
{

}
void uartPacketCmd222(uint32 uldata)
{

}
void uartPacketCmd223(uint32 uldata)
{

}
void uartPacketCmd224(uint32 uldata)
{

}
void uartPacketCmd225(uint32 uldata)
{

}
void uartPacketCmd226(uint32 uldata)
{

}
void uartPacketCmd227(uint32 uldata)
{

}
void uartPacketCmd228(uint32 uldata)
{

}
void uartPacketCmd229(uint32 uldata)
{

}
void uartPacketCmd230(uint32 uldata)
{

}
void uartPacketCmd231(uint32 uldata)
{

}
void uartPacketCmd232(uint32 uldata)
{

}
void uartPacketCmd233(uint32 uldata)
{

}
void uartPacketCmd234(uint32 uldata)
{

}
void uartPacketCmd235(uint32 uldata)
{

}
void uartPacketCmd236(uint32 uldata)
{

}
void uartPacketCmd237(uint32 uldata)
{

}
void uartPacketCmd238(uint32 uldata)
{

}
void uartPacketCmd239(uint32 uldata)
{

}
void uartPacketCmd240(uint32 uldata)
{

}
void uartPacketCmd241(uint32 uldata)
{

}
void uartPacketCmd242(uint32 uldata)
{

}
void uartPacketCmd243(uint32 uldata)
{

}
void uartPacketCmd244(uint32 uldata)
{

}
void uartPacketCmd245(uint32 uldata)
{

}
void uartPacketCmd246(uint32 uldata)
{

}
void uartPacketCmd247(uint32 uldata)
{

}
void uartPacketCmd248(uint32 uldata)
{

}
void uartPacketCmd249(uint32 uldata)
{

}
void uartPacketCmd250(uint32 uldata)
{

}
void uartPacketCmd251(uint32 uldata)
{

}
void uartPacketCmd252(uint32 uldata)
{

}
void uartPacketCmd253(uint32 uldata)
{

}
void uartPacketCmd254(uint32 uldata)
{

}
void uartPacketCmd255(uint32 uldata)
{

}

