////*****************************************////
//  Name : parameter_ext.h
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#ifndef _PARAMETER_EXT_H_
#define _PARAMETER_EXT_H_

#include "api.h"
#include "parameter_define.h"

// define
typedef void (*ulParaFuncPtr)();

// structure
typedef struct
{
	int32				lValue;
	int32				lValueMax;
	int32				lValueMin;
	PARA_TYPE			type;
	PARA_LOCK   		lock;
	PARA_SIGN			sign;
	PARA_CHANGE_REBOOT	change;
	char* 				sName;
	ulParaFuncPtr		pFunc;
}PARAMETER;

typedef struct
{
	uint32 paraMode;
	uint32 changeFlag;
	uint32 updateFlag;
	uint32 servoOnLock;
	PARAMETER para[MAX_PARAMETER];
}PARAMETER_REGS;


// extern variable
extern PARAMETER_REGS paraRegs;

// extern function
extern void para_init(void);
#define parameter_init para_init // For api initialization standard

extern void para_update(PARAMETER_REGS *paraRegs, uint32 ulPara, int32 lData);
extern void para_updateAll(PARAMETER_REGS *paraRegs);
extern void para_readAll(void);
extern void para_printAll(void);

// macro
#define para_modeSet_macro(data) paraRegs.paraMode = data
#define para_modeGet_macro() paraRegs.paraMode
#define para_update_macro(ulPara, iData) para_update(&paraRegs, ulPara, iData)
#define para_updateAll_macro() para_updateAll(&paraRegs)

extern int32 para_valueGet(uint32 ulPara);
#define para_valueGet_macro(ulPara) paraRegs.para[ulPara].lValue

#define para_valueSet_macro(ulPara,iData) paraRegs.para[ulPara].lValue = iData
#define para_valueMaxGet_macro(ulPara) paraRegs.para[ulPara].lValueMax
#define para_valueMinGet_macro(ulPara) paraRegs.para[ulPara].lValueMin
#define para_typeGet_macro(ulPara) paraRegs.para[ulPara].type
#define para_signGet_macro(ulPara) paraRegs.para[ulPara].sign
#define para_lockGet_macro(ulPara) paraRegs.para[ulPara].lock
#define para_changeGet_macro(ulPara) paraRegs.para[ulPara].change
#define para_nameGet_macro(ulPara) paraRegs.para[ulPara].sName

#define para_paraMaxGet_macro() MAX_PARAMETER

#define para_paraServoOnLockGet_macro() paraRegs.servoOnLock
#define para_paraChangeFlagGet_macro()  paraRegs.changeFlag
#define para_paraUpdateFlagGet_macro()  paraRegs.updateFlag
#endif // end of file
