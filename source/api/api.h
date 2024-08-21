////*****************************************////
//  Name : api.h
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#ifndef _API_H_
#define _API_H_

#include "lib.h" // include lib layer
#include "api_cfg.h" // include configure file

#if API_MOTORDRIVE_ENABLE == API_ENABLE
	#include "motorDrive_ext.h"
#endif

#if API_MOTORCONTROL_ENABLE == API_ENABLE
	#include "motorControl_ext.h"
#endif

#if API_PARAMETER_ENABLE == API_ENABLE
	#include "parameter_ext.h"
#endif


#if API_DEBUGCONSOLE_ENABLE == API_ENABLE
	#include "debugConsole_ext.h"
#endif



extern void api_init(void); // extern api layer initialization function

#endif // end of file
