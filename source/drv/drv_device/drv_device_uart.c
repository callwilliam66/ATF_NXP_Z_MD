////*****************************************////
//  Name : drv_device_uart.c
//  Data : 2021/07
//  Version : 0.0
////*****************************************////

#include "drv_device.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
uint32 device_uart_txFifoEmpty(LPUART_Type *base)
{
	if((base->FIFO & LPUART_FIFO_TXEMPT_MASK) == 0)
	{
		return 1;
	}

	return 0;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
uint32 device_uart_rxFifoEmpty(LPUART_Type *base)
{
	if((base->FIFO & LPUART_FIFO_RXEMPT_MASK) == 0)
	{
		return 1;
	}
	return 0;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
uint32 device_uart_rxErrorStateClear(LPUART_Type *base)
{
	if((LPUART_GetStatusFlags(base) & LPUART_STAT_OR_MASK) == LPUART_STAT_OR_MASK)
	{
		return LPUART_ClearStatusFlags(base,LPUART_STAT_OR_MASK);
	}

	return 0;
}
