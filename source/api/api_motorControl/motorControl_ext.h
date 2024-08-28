////*****************************************////
//  Name : motorControl_ext.h
//  Data : 2020/10
//  Version : 0.0
////*****************************************////

#ifndef _MOTORCONTROL_EXT_H_
#define _MOTORCONTROL_EXT_H_


#include "motorControl_emg.h"
#include "api.h"
#include "motorControl_homeLimit.h"
#include "motorControl_uart.h"
#include "motorControl_curve.h"

#define CTRLR_MODE_UART		0
#define CTRLR_MODE_SPI		1


typedef struct
{
	uint32 servoOn : 1;
	uint32 home : 1;
	uint32 homeFind : 1;
	uint32 alarm_clr : 1;
	uint32 emg : 1;
	uint32 msd : 1;
	uint32 reserved : 26;
}CMD_BITS;

typedef union
{
	CMD_BITS data;
	uint32 all;
}CMD_REGS;

typedef struct
{
	uint32 servoState : 1;					// check the Motor system servo state
	uint32 servoReady : 1;					// check the adc which is corrected by program
	uint32 alarm : 1;						// when urgent events is occurred,alarm should be signal high
	uint32 warning : 1;						// when abnormal events is occurred,warning should be signal high
	uint32 homeFinding : 1;					// Indicates whether the motor is in home finding mode
	uint32 homeFinded : 1; 					// Indicates that the motor has found the home
	uint32 homeFindFailed : 1;				//Indicates that the motor origin assignment failed
	uint32 atHome : 1;						// Check if the motor position is at the home
	uint32 atCWLimit : 1;					// Check if the motor position is at the positive limit
	uint32 atCCWLimit : 1;					// Check if the motor position is at the negative limit
	uint32 zeroSpeed : 1;					// Indicates whether the motor is in the home position
	uint32 inPosition : 1;					// Indicates whether the motor is in the home position
	uint32 inPosition2 : 1;
	uint32 reserved : 20;
}STATUS_BITS;

typedef union
{
	STATUS_BITS data;
	uint32 all;
}STATUS_REGS;

typedef struct
{
	uint32			mode;
	CMD_REGS		cmdRegs;
	STATUS_REGS 	statusRegs;

	uint32			statusServoOn;
	uint32			statusAlarm;

	uint32			ulPcmd;
	uint32			ulPcmdUart;
	uint32			ulPcmdPulse;
	uint32			ulPcmdSpi;
	uint32			ulPcmd_emg;
	uint32			ulPcmdCmmp;
	uint32			ulPfbk;						//Position feedback
	int32           lPerr;

	uint32			ulinPositionRange;
	float32			fZeroSpeedRange;
	float32         fZeroSpeedRation;

	uint32			ulD0_ch;
	uint32			ulD0;
	uint32			ulD1_ch;
	uint32			ulD1;

	//Uart
	UART_REGS		uart1Regs;
	UART_REGS		uart2Regs;
	UART_REGS		uart3Regs;
	UART_REGS		uart4Regs;

	void (*uartRxCmd[256])(uint32);

	uint32         	ulNWINRX_cnt;
	uint32         	ulNWRX_cnt;
	uint32         	ulUNWRX_cnt;
	uint32         	ulNWTX_cnt;
	uint32         	ulZATX_cnt;
	uint32         	ulNW_cnt;
	uint32         	ulZA_cnt;
	uint32  		ulZA_packet;		//z-axis-buffer
	uint32          ulZA_packet1;
	uint32  		ulZATX_packet;		//z-axis-buffer
	uint32          ulZA_ctrl_st;		//z-axis-buffer

	uint32          ulZA_data0;			//z-axis-buffer
	uint32          ulZA_data1;			//z-axis-buffer
	uint32          ulZA_data2;			//z-axis-buffer
	uint32          ulZA_data3;			//z-axis-buffer

	int32       	lZAcmd_FPGA;		//Z-Axis-cmd comes from user
	int32       	lZAcmd_FPGA_old;	//old_Z-Axis-cmd comes from user
	int32           lNWcmd_FPGA;		//nose-wheel-cmd comes from user
	int32           lNWcmd_FPGA_old;	//old_nose-wheel-cmd comes from user
	int32           lNWcmd_BOARD;		//nose-wheel-cmd comes from inner-board


	HOME_LIMIT_REGS homeLimitRegs;
	EMG_REGS		emgRegs;
	TCURVE_REGS     tcurveRegs;
	uint32          ulledfr;
	uint32          ulledfg;


	uint32          timer100kcnt;
	uint32          timer40kcnt;

	uint32          ulCmdRenewFlag;
	uint32          ulCmdRenewCnt;
	uint32          ulTest;
	uint32 			commandReceiveEnableFlag;
	uint32 			ulfirmwareflashkey;

}MOTOR_CONTROL_REGS;

extern MOTOR_CONTROL_REGS mCtrlRegs;

extern void mCtrl_init(void);
extern void mCtrl_findhome(MOTOR_CONTROL_REGS *mCtrlRegs);
#define motorControl_init mCtrl_init // For api initialization standard

extern void motorControl_isr(void);

extern void mCtrl_homeFindingClear(MOTOR_CONTROL_REGS *mCtrlRegs);

#define mCtrl_emgStateIOGet_macro() 		mCtrlRegs.emgRegs.ulEmgStateIO
#define mCtrl_emgStateIOAddrGet_macro() 	&mCtrlRegs.emgRegs.ulEmgStateIO
#define mCtrl_emgStateSWAddrGet_macro() 	&mCtrlRegs.emgRegs.ulEmgStateSW

#define mCtrl_inposoutcounterGet_marco()  	mCtrlRegs.uloutofinposcounter
#define mCtrl_inposoutcounterSet_marco(data)  mCtrlRegs.uloutofinposcounter=data

#define mCtrl_modeGet_macro()		mCtrlRegs.mode
#define mCtrl_modeSet_macro(data)	mCtrlRegs.mode = data

#define mCtrl_cmd_servoOnSet_macro(cData)		mCtrlRegs.cmdRegs.data.servoOn = cData
#define mCtrl_cmd_homeSet_macro(cData)			mCtrlRegs.cmdRegs.data.home = cData
#define mCtrl_cmd_homeFindSet_macro(cData)		mCtrlRegs.cmdRegs.data.homeFind = cData
#define mCtrl_cmd_alarm_clrGet_macro()			mCtrlRegs.cmdRegs.data.alarm_clr
#define mCtrl_cmd_alarm_clrSet_macro(cData)		mCtrlRegs.cmdRegs.data.alarm_clr = cData
#define mCtrl_cmd_emgSet_macro(cData)			mCtrlRegs.cmdRegs.data.emg = cData
#define mCtrl_cmd_msdSet_macro(cData)			mCtrlRegs.cmdRegs.data.msd = cData

#define mCtrl_status_servoStateGet_macro()		mCtrlRegs.statusRegs.data.servoState
#define mCtrl_status_servoReadyGet_macro()		mCtrlRegs.statusRegs.data.servoReady

#define mCtrl_status_alarmGet_macro()			mCtrlRegs.statusRegs.data.alarm

#define mCtrl_status_servoStateAddrGet_macro()	&mCtrlRegs.statusServoOn
#define mCtrl_status_alarmAddrGet_macro()		&mCtrlRegs.statusAlarm

#define mCtrl_status_warningGet_macro()			mCtrlRegs.statusRegs.data.warning
#define mCtrl_status_homeFindingGet_macro()		mCtrlRegs.statusRegs.data.homeFinding
#define mCtrl_status_homeFindedGet_macro()		mCtrlRegs.statusRegs.data.homeFinded
#define mCtrl_status_homeFindFailedGet_macro()	mCtrlRegs.statusRegs.data.homeFindFailed
#define mCtrl_status_atHomeGet_macro()			mCtrlRegs.statusRegs.data.atHome
#define mCtrl_status_atCWLimitGet_macro()		mCtrlRegs.statusRegs.data.atCWLimit
#define mCtrl_status_atCCWLimiGett_macro()		mCtrlRegs.statusRegs.data.atCCWLimit
#define mCtrl_status_zeroSpeedGet_macro()		mCtrlRegs.statusRegs.data.zeroSpeed
#define mCtrl_status_inPositioGet_macro()		mCtrlRegs.statusRegs.data.inPosition

#define mCtrl_ulPcmdSet_macro(data)				mCtrlRegs.ulPcmd = data
#define mCtrl_ulPcmdGet_macro()					mCtrlRegs.ulPcmd
#define mCtrl_ulPcmdUartSet_macro(data)			mCtrlRegs.ulPcmdUart = data
#define mCtrl_ulPcmdUartGet_macro()				mCtrlRegs.ulPcmdUart
#define mCtrl_ulPfbkSet_macro(data)				mCtrlRegs.ulPfbk = data
#define mCtrl_ulPfbkGet_macro()					mCtrlRegs.ulPfbk

#define mCtrl_ulInPositionRangeSet_macro(data)	mCtrlRegs.ulinPositionRange = data
#define mCtrl_fZeroSpeedRangeSet_macro(data)	mCtrlRegs.fZeroSpeedRange = data
#define mCtrl_fZeroSpeedRationSet_macro(data)	mCtrlRegs.fZeroSpeedRation = data
#define mCtrl_para_D0ChSet_macro(data) 			mCtrlRegs.ulD0_ch = data
#define mCtrl_para_D0ChGet_macro() 				mCtrlRegs.ulD0_ch
#define mCtrl_para_D0Set_macro(data) 			mCtrlRegs.ulD0 = data
#define mCtrl_para_D0Get_macro() 				mCtrlRegs.ulD0
#define mCtrl_para_D1ChSet_macro(data) 			mCtrlRegs.ulD1_ch = data
#define mCtrl_para_D1ChGet_macro() 				mCtrlRegs.ulD1_ch
#define mCtrl_para_D1Set_macro(data) 			mCtrlRegs.ulD1 = data
#define mCtrl_para_D1Get_macro() 				mCtrlRegs.ulD1

//// home limit
#define mCtrl_homeFindModeSet_macro(data)		mCtrlRegs.homeLimitRegs.homeFindMode = data
#define mCtrl_fHomeFindSpeedSet_macro(data)		mCtrlRegs.homeLimitRegs.fHomeFindSpeed = data
#define mCtrl_homeEnableGet_macro()				mCtrlRegs.homeLimitRegs.homeEnable
#define mCtrl_homeEnableSet_macro(data)			mCtrlRegs.homeLimitRegs.homeEnable = data
#define mCtrl_homePosSet_macro(data)            mCtrlRegs.homeLimitRegs.ulhomePos = data

#define mCtrl_homelimitbit0Get_macro()          mCtrlRegs.homeLimitRegs.ulimitindex_bit0
#define mCtrl_homelimitbit1Get_macro()          mCtrlRegs.homeLimitRegs.ulimitindex_bit1



#define mCtrl_limitPosEnableGet_macro()			mCtrlRegs.homeLimitRegs.limitPosEnable
#define mCtrl_limitPosEnableSet_macro(data)		mCtrlRegs.homeLimitRegs.limitPosEnable = data
#define mCtrl_limitNegEnableGet_macro()			mCtrlRegs.homeLimitRegs.limitNegEnable
#define mCtrl_limitNegEnableSet_macro(data)		mCtrlRegs.homeLimitRegs.limitNegEnable = data

#define mCtrl_ulPHomeGet_macro()				mCtrlRegs.homeLimitRegs.ulPHome

#define mCtrl_homeLimit_homeDataGet_macro()		mCtrlRegs.homeLimitRegs.homeRegs.data.dataNew
#define mCtrl_homeLimit_posLimitDataGet_macro()	mCtrlRegs.homeLimitRegs.limitPosRegs.data.dataNew
#define mCtrl_homeLimit_negLimitDataGet_macro()	mCtrlRegs.homeLimitRegs.limitNegRegs.data.dataNew

#define mCtrl_homeLimit_homeAddrGet_macro()		&mCtrlRegs.homeLimitRegs.homeData
#define mCtrl_homeLimit_posLimitAddrGet_macro()	&mCtrlRegs.homeLimitRegs.limitPosData
#define mCtrl_homeLimit_negLimitAddrGet_macro()	&mCtrlRegs.homeLimitRegs.limitNegData


#define mCtrl_softPosLimitEnableSet_macro(data)		mCtrlRegs.homeLimitRegs.softPosLimitEnable = data
#define mCtrl_ulSoftPosLimitSet_macro(data)			mCtrlRegs.homeLimitRegs.ulSoftPosLimit = data
#define mCtrl_softNegLimitEnableSet_macro(data)		mCtrlRegs.homeLimitRegs.softNegLimitEnable = data
#define mCtrl_ulSoftNegLimitSet_macro(data)			mCtrlRegs.homeLimitRegs.ulSoftNegLimit = data

//// emg
#define mCtrl_emg_stateGet_macro() 	mCtrlRegs.emgRegs.ulEmgState

//// uart
#define mCtrl_uart_firmwareUpdateFlagGet_macro()	(mCtrlRegs.uart1Regs.firmwareUpdateFlag | mCtrlRegs.uart2Regs.firmwareUpdateFlag)

//// cmd renew
#define mCtrl_ulCmdRenewFlagGet_macro()			mCtrlRegs.ulCmdRenewFlag


////tcurve

#define 	mCtrl_ulTaccSet_macro(data)   			mCtrlRegs.tcurveRegs.ultacc = data;
#define 	mCtrl_ulTdecSet_macro(data)   			mCtrlRegs.tcurveRegs.ultdec = data;
#define 	mCtrl_lVinitSet_macro(data)           	mCtrlRegs.tcurveRegs.lVinit = data;
#define 	mCtrl_fVmaxSet_macro(data)				mCtrlRegs.tcurveRegs.fVmax = data;

#endif // end of file
