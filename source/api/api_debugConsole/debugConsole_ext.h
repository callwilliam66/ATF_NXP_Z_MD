////*****************************************////
//  Name : debugConsole_ext.h
//  Data : 2021/08
//  Version : 0.0
////*****************************************////

#ifndef _DEBUGCONSOLE_EXT_H_
#define _DEBUGCONSOLE_EXT_H_

#include "api.h"

extern void debugConsole_init(void);

extern void PRINTF(char* cData);
extern void PRINTF_nextLine(void);
extern void PRINTF_withNextLine(char* cData);
extern void PRINTF_withSpace(char* cData);
extern void PRINTF_int32(int32 lData);

#endif // end of file
