////*****************************************////
//  Name : lib_crc.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "lib_crc.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
uint8 checksum_calc(uint8 *data,uint32 ulLengthBytes)
{
	uint8 ucDataIn;
	uint8 ucDataCnt;
	uint8 ucDataResult;

	ucDataIn = 0;
	ucDataCnt = 0;
	ucDataResult = 0;

	for(ucDataCnt = 0; ucDataCnt < ulLengthBytes; ucDataCnt++)
	{
		ucDataIn = *(data + ucDataCnt);

		ucDataResult = ucDataIn + ucDataResult;
	}

	ucDataResult = 0xFF - ucDataResult;

	return ucDataResult;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
uint8 crc_crc8_0x31_calc(uint8 *data,uint32 ulLengthBytes)
{
	uint8 ucDataIn;
	uint8 ucDataCnt;
	uint8 ucDataResult;

	ucDataIn = 0;
	ucDataCnt = 0;
	ucDataResult = 0;

	for(ucDataCnt = 0; ucDataCnt < ulLengthBytes; ucDataCnt++)
	{
		ucDataIn = *(data + ucDataCnt);

		ucDataResult = ucDataIn ^ ucDataResult;

		ucDataResult = crc8_0x31_table[ucDataResult];
	}

	return ucDataResult;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
uint8 crc_crc8_0x1D_initialValue_endValue_calc(uint8 *data,uint32 ulLengthBytes,uint8 initialValue,uint8 endValue)
{
	uint8 ucDataIn;
	uint8 ucDataCnt;
	uint8 ucDataResult;

	ucDataIn = 0;
	ucDataCnt = 0;
	ucDataResult = initialValue;

	for(ucDataCnt = 0; ucDataCnt < ulLengthBytes; ucDataCnt++)
	{
		ucDataIn = *(data + ucDataCnt);

		ucDataResult = ucDataIn ^ ucDataResult;

		ucDataResult = crc8_0x1D_table[ucDataResult];
	}

	ucDataResult = ucDataResult ^ endValue;

	return ucDataResult;
}

