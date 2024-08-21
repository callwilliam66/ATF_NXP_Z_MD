
////*****************************************////
//  Name : drv.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "drv.h" 


void drv_init(void)
{
	#if DRV_GLOBALVARIABLE_ENABLE == DRV_ENABLE
//		drv_globalVariable_init();
	#endif

	#if DRV_DEVICE_ENABLE == DRV_ENABLE
		drv_device_init();
	#endif

	#if DRV_BOARD_ENABLE == DRV_ENABLE
		drv_board_init();
	#endif

}
