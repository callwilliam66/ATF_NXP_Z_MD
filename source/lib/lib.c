
////*****************************************////
//  Name : lib.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "lib.h" 

void lib_init(void)
{
	#if LIB_MATH_ENABLE == LIB_ENABLE
//		lib_math_init();
	#endif

	#if LIB_FILTER_ENABLE == LIB_ENABLE
	//		lib_filter_init();
	#endif

	#if LIB_CRC_ENABLE == LIB_ENABLE
	//		lib_crc_init();
	#endif

	#if LIB_DATATYPE_ENABLE == LIB_ENABLE
//		lib_dataType_init();
	#endif
}
