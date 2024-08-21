////*****************************************////
//  Name : lib.h
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#ifndef _LIB_H_
#define _LIB_H_

#include "drv.h" // include drv layer
#include "lib_cfg.h" // include configure file

#if LIB_MATH_ENABLE == LIB_ENABLE
	#include "lib_math_ext.h"
#endif

#if LIB_CRC_ENABLE == LIB_ENABLE
	#include "lib_crc_ext.h"
#endif

#if LIB_FILTER_ENABLE == LIB_ENABLE
	#include "lib_filter_ext.h"
#endif

#if LIB_DATATYPE_ENABLE == LIB_ENABLE
	#include "lib_dataType_ext.h"
#endif

extern void lib_init(void); // extern lib layer initialization function

#endif // end of file
