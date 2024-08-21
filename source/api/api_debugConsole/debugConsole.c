////*****************************************////
//  Name : debugConsole.c
//  Data : 2021/08
//  Version : 0.0
////*****************************************////

#include "debugConsole.h"

void debugConsole_init(void)
{

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void PRINTF(char* cData)
{
	uint32 ullength = 0;

	while(*(cData + ullength) != 0)
	{
		while(device_uart_txFifoEmpty_macro() == 0){}

		device_uart_txWriteByte_macro(*(cData + ullength));
		ullength++;
	}
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void PRINTF_withNextLine(char* cData)
{
	uint32 ullength = 0;

	while(*(cData + ullength) != 0)
	{
		while(device_uart_txFifoEmpty_macro() == 0){}

		device_uart_txWriteByte_macro(*(cData + ullength));
		ullength++;
	}

	while(device_uart_txFifoEmpty_macro() == 0){}
	device_uart_txWriteByte_macro(0x0D);
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void PRINTF_withSpace(char* cData)
{
	uint32 ullength = 0;

	while(*(cData + ullength) != 0)
	{
		while(device_uart_txFifoEmpty_macro() == 0){}

		device_uart_txWriteByte_macro(*(cData + ullength));
		ullength++;
	}

	while(device_uart_txFifoEmpty_macro() == 0){}
	device_uart_txWriteByte_macro(0x20);
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void PRINTF_nextLine(void)
{
	char* cData = "\r";

	PRINTF(cData);
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void PRINTF_int32(int32 lData)
{
	char* cData = "";

	lib_dataType_int32ToString(cData, lData);

	PRINTF(cData);
}
