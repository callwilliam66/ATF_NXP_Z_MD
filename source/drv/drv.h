////*****************************************////
//  Name : drv.h
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#ifndef _DRV_H_
#define _DRV_H_

#include "drv_cfg.h" // include configure file

#if DRV_GLOBALVARIABLE_ENABLE == DRV_ENABLE
	#include "drv_globalVariable_ext.h"
#endif

#if DRV_DEVICE_ENABLE == DRV_ENABLE
	#include "drv_device_ext.h"
#endif

#if DRV_BOARD_ENABLE == DRV_ENABLE
	#include "drv_board_ext.h"
#endif


extern void drv_init(void); // extern drv layer initialization function

#endif // end of file
