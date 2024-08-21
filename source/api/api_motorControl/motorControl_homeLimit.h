////*****************************************////
//  Name : motorControl_homeLimit.h
//  Data : 2021/07
//  Version : 0.0
////*****************************************////

#ifndef _MOTORCONTROL_HOMELIMIT_H_
#define _MOTORCONTROL_HOMELIMIT_H_

#include "api.h"

typedef uint32 (* ulFuncGetPtr) (void);

typedef enum
{
	positive_noIndex,
	negative_noIndex,
	home_noIndex,
	home_noIndex_positive,
	only_negative,
	home_disable,

}HOME_FIND_MODE;

#define HOME_FIND_SPEED_PUSLE 1
#define HOME_FIND_STOP_SPEED_PUSLE 1

typedef enum
{
	home_find_dir_positive,
	home_find_dir_negative,
}HOME_FIND_DIR;

#define HOME_LIMIT_ENABLE   0
#define HOME_LIMIT_DISABLE  1

#define HOME_LOW_ACTIVE		0
#define HOME_HIGH_ACTIVE	1

#define POSITIVE_LIMIT_ENABLE   0
#define POSITIVE_LIMIT_DISABLE  1

#define NEGATIVE_LIMIT_ENABLE   0
#define NEGATIVE_LIMIT_DISABLE  1

typedef struct
{
	uint32 homeFinding;
	uint32 homeFinded;
	uint32 homeFindFailed;

	uint32 ulPcmd;
	uint32 ulPfbk;
	uint32 ulPHome;

	uint32	homeEnable;
	uint32	limitPosEnable;
	uint32	limitNegEnable;
	uint32   ulhomePos;


	HOME_FIND_MODE	homeFindMode;
	float32			fHomeFindSpeed;

	uint32			homeData;
	SIGNAL_REGS		homeRegs;
	uint32			limitPosData;
	SIGNAL_REGS 	limitPosRegs;
	uint32			limitNegData;
	SIGNAL_REGS		limitNegRegs;

	uint32          ulimitindex_bit0;
	uint32          ulimitindex_bit1;


	uint32			ulLimitHomeSignalErr;
	float32			fHomeFindCmd;
	int32			lHomeFindCmd;
	uint32			ulHomeFindDir;
	uint32			ulHomeFindState;
	uint32			ulHomeFindAlarm;
	uint32			ulHomeBack;
	uint32			ulHomeStop;

	uint32		softPosLimitEnable;
	uint32		ulSoftPosLimit;
	uint32		softNegLimitEnable;
	uint32		ulSoftNegLimit;

}HOME_LIMIT_REGS;

extern void mCtrl_home(HOME_LIMIT_REGS *homeLimitRegs);
extern void mCtrl_homeLimitDataUpdate(HOME_LIMIT_REGS *homeLimitRegs);
extern void mCtrl_home_positive_noIndex(HOME_LIMIT_REGS *homeLimitRegs);
extern void mCtrl_home_negative_noIndex(HOME_LIMIT_REGS *homeLimitRegs);
extern void mCtrl_home_home_noIndex(HOME_LIMIT_REGS *homeLimitRegs);
extern void mCtrl_home_home_noIndex_positive(HOME_LIMIT_REGS *homeLimitRegs);
extern void mCtrl_home_only_negative(HOME_LIMIT_REGS *homeLimitRegs);

extern void mCtrl_home_cmd(HOME_LIMIT_REGS *homeLimitRegs);

extern void mCtrl_homeLimitSignalUpdate(uint32 enable,SIGNAL_REGS *homeLimitSignalRegs,uint32 dataIn);
extern void mCtrl_homeLimitSignalUpdateWithDataInUpdate(uint32 enable,SIGNAL_REGS *homeLimitSignalRegs);
#endif // end of file
