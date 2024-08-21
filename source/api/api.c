////*****************************************////
//  Name : api.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "api.h" 


 void api_init(void)
{
	#if API_MOTORDRIVE_ENABLE == API_ENABLE
		motorDrive_init();
	#endif

	#if API_MOTORCONTROL_ENABLE == API_ENABLE
		motorControl_init();
	#endif

	#if API_PARAMETER_ENABLE == API_ENABLE
		parameter_init();
	#endif

	#if API_DEBUGCONSOLE_ENABLE == API_ENABLE
		debugConsole_init();
	#endif


}
