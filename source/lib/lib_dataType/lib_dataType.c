////*****************************************////
//  Name : lib_dataType.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include <lib_dataType/lib_dataType.h>

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void lib_dataType_init(void)
{

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void lib_dataType_int32ToString(char* cData, int32 lData)
{
	uint32 ulLengthData = lData;
	uint32 ulDataSignIndex = 0;
	uint32 ulDataUnit = 1;
	uint32 ulLength = 1;
	uint32 ulLengthIndex = 0;

	if(lData < 0)
	{
		*cData = '-';
		cData++;
		ulDataSignIndex = 1;
		lData = lData * -1;
		ulLengthData = lData;
	}

	while(ulLengthData != 0)
	{
		ulLengthData /= 10;

		if(ulLengthData == 0)
			break;

		ulDataUnit *= 10;
		ulLength++;
	}

	ulLengthIndex = ulLength;


	while(ulLength != 0)
	{
		*(cData) = lData / ulDataUnit + '0';
		lData %= ulDataUnit;
		ulDataUnit /= 10;
		cData++;
		ulLength--;
	}

	*cData = 0;

	cData -= (ulLengthIndex + ulDataSignIndex);
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void lib_dataType_uint32ToString(char* cData, int32 lData)
{
	uint32 ulLengthData = lData;
	uint32 ulDataSignIndex = 0;
	uint32 ulDataUnit = 1;
	uint32 ulLength = 1;
	uint32 ulLengthIndex = 0;

	while(ulLengthData != 0)
	{
		ulLengthData /= 10;

		if(ulLengthData == 0)
			break;

		ulDataUnit *= 10;
		ulLength++;
	}

	ulLengthIndex = ulLength;


	while(ulLength != 0)
	{
		*(cData) = lData / ulDataUnit + '0';
		lData %= ulDataUnit;
		ulDataUnit /= 10;
		cData++;
		ulLength--;
	}

	*cData = 0;

	cData -= (ulLengthIndex + ulDataSignIndex);
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void lib_dataType_uint32ToStringHex(char* cData, int32 lData)
{
	uint32 ulLengthData = lData;
	uint32 ulDataSignIndex = 0;
	uint32 ulDataUnit = 1;
	uint32 ulLength = 1;
	uint32 ulLengthIndex = 0;

	while(ulLengthData != 0)
	{
		ulLengthData /= 16;

		if(ulLengthData == 0)
			break;

		ulDataUnit *= 16;
		ulLength++;
	}

	ulLengthIndex = ulLength;


	while(ulLength != 0)
	{
		if(lData / ulDataUnit < 10)
		{
			*(cData) = lData / ulDataUnit + '0';
		}
		else
		{
			*(cData) = (lData / ulDataUnit - 10) + 'A';
		}

		lData %= ulDataUnit;
		ulDataUnit /= 16;
		cData++;
		ulLength--;
	}

	*cData = 0;

	cData -= (ulLengthIndex + ulDataSignIndex);
}
