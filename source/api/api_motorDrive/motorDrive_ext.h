////*****************************************////
//  Name : motorDrive_ext.h
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#ifndef _MOTORDRIVE_EXT_H_
#define _MOTORDRIVE_EXT_H_

#include "api.h"

// alarm setting
#define ALARM_OVERLOAD_TIME_S 		4.0F 	// 2s
#define ALARM_OVERVOLTAGE_TIME_S 	0.01F 	// 10ms
#define ALARM_UNDERVOLTAGE_TIME_S 	0.01F 	// 10ms

// define
////uint32 ctrlMode;
#define	MOTOR_CTRL_MODE_P 								0
#define	MOTOR_CTRL_MODE_P_TEST 							1
#define	MOTOR_CTRL_MODE_V								2
#define	MOTOR_CTRL_MODE_CURRENT_CLOSE_ANGLE_OPEN		3
#define	MOTOR_CTRL_MODE_CURRENT_CLOSE_ANGLE_OPEN_STEP	4
#define	MOTOR_CTRL_MODE_CURRENT_OPEN_ANGLE_OPEN_STEP	5

////uint32 ctrlType;
#define MOTOR_CTRL_TYPE_SERVO	0
#define MOTOR_CTRL_TYPE_STEP	1

#define MUSIC_DO      0;
#define MUSIC_RE      1;
#define MUSIC_MI      2;
#define MUSIC_FA      3;
#define MUSIC_SO      4;
#define MUSIC_LA      5;
#define MUSIC_Si      6;
////uint32 servoOnMode;
#define SERVO_ON_MODE_CTLR	0
#define SERVO_ON_MODE_IO	1
#define SERVO_ON_MODE_SW	2

////uint32 servoState;
#define SERVO_STATE_OFF	0
#define SERVO_STATE_ON	1

////uint32 motorType;
#define	MOTOR_DEFAULT				0
#define	MOTOR_MDLV_3M68				1
#define	MOTOR_SUMFU_17NE34BF3_300	3
#define MOTOR_SM_1P2D50P500R4P6A    4
#define	MOTOR_SUMFU_ML1513			5
#define	MOTOR_GHC_S160D				6

////uint32 ulEncoderType;
#define ENCODER_TYPE_INC 						0 // A B Z
#define ENCODER_TYPE_ENCODER_CHECK_ZERO_START   1 // A B Z
#define ENCODER_TYPE_INC_ZERO_ANGLE_SLOW_START	2 // A B
#define ENCODER_TYPE_INC_ZERO_START				3 // A B


////uint32 motorPhaseDir;
#define MOTOR_PHASE_DIR_CCW	0
#define MOTOR_PHASE_DIR_CW	1

////uint32 encoderDir;
#define ENCODER_DIR_CCW	0
#define ENCODER_DIR_CW 	1

////uint32 startup;
#define STARTUP_ZERO_STATE_INIT 0
#define STARTUP_ZERO_STATE_HOLD 1
#define STARTUP_ZERO_STATE_CHECK_POS 2
#define STARTUP_ZERO_STATE_CHECK_NEG 3
#define STARTUP_ZERO_STATE_CHECK 4
#define STARTUP_ZERO_STATE_FINISH 5
#define STARTUP_ZERO_STATE_END 6


////uint32  checkup

#define STARTUP_ENCODE_CHECK_HOLD    	0
#define STARTUP_ENCODE_CHECK_NEG   	    1
#define STARTUP_ENCODE_CHECK_POS    	2
#define STARTUP_ENCODE_CHECK_JUDGE    	3
#define STARTUP_ENCODE_CHECK_PASS   	4
#define STARTUP_ENCODE_CHECK_ERROR      5
#define STARTUP_ENCODE_CHECK_FINISH     6
#define STARTUP_ENCODE_CHECK_END        7
// structure
typedef struct
{
	float32 fAlpha;
	float32 fBeta;
	float32 fTheta; // 0.0 -> 1.0 => 0 ~ 360 degree
	float32 fSine;
	float32 fCosine;
	float32 fD;
	float32 fQ;
}PARK_REGS;

typedef struct
{
	float32 fAlpha;
	float32 fBeta;
	float32 fTheta; // 0.0 -> 1.0 => 0 ~ 360 degree
	float32 fSine;
	float32 fCosine;
	float32 fD;
	float32 fQ;
}IPARK_REGS;

typedef struct
{
	float32 fU;
	float32 fV;
	float32 fW;
	float32 fAlpha;
	float32 fBeta;
}CLARKE_REGS;

typedef struct
{
	float32 fU;
	float32 fV;
	float32 fW;
	float32 fAlpha;
	float32 fBeta;
}ICLARKE_REGS;

typedef struct
{
	float32 fU;
	float32 fV;
	float32 fW;
	float32 fMax;
	float32 fMin;
	float32 fComm;
	float32 fA;
	float32 fB;
	float32 fC;
}SVM_REGS;

typedef struct
{
	float32 fTc;
	float32 fBw;
	float32 fRef;
	float32 fFbk;
	float32 fErr;

	float32 fKp;

	float32 fKf;
	float32 fRKf;

	float32 fUp;
	float32 fUf;
	float32 fURf;
	float32 fInt;

	float32 fKi;
	float32 fUi;

	float32 fMax;
	float32 fMin;

	//Input
	float32 x[2];
	//Output
	float32 y[2];
	float32 fsample_rate;
	float32 fOutSat;
	float32 fOut;
}PI_REGS;


typedef struct
{
	uint32  ulindex;
	float32 fTc;
	float32 fBw;
	float32 fRef;
	float32 fFbk;
	float32 fErr;
	float32 fKp;
	float32 fKp1;
	float32 fKp2;
	float32 fKp3;
	float32 fKp4;
	float32 fKf;
	float32 fUp;
	float32 fUf;
	float32 fInt;
	float32 fKi;
	float32 fKi1;
	float32 fKi2;
	float32 fKi3;
	float32 fKi4;
	float32 fUi;
	float32 fMax;
	float32 fMin;
	float32 fOutSat;
	float32 fOut;
}PULSEPI_REGS;


typedef struct
{
	float32 fBw;
	float32 fRef;
	float32 fFbk;
	float32 fErr;
	int32 	lPrevious_Error;

	uint32 	ulRef;
	uint32 	ulFbk;
	int32 	lErr;

	float32 fKp;
	float32 fKd;
	float32 fUp;
	float32 fUd;
	float32 fMax;
	float32 fMin;
	float32 fOutSat;
	float32 fOut;

}P_REGS;

typedef struct{

	float32 fSpeedCmd;
	float32 fSpeedCmdMax;
	float32 fSpeedCmdBoundary;
	float32 fIdFWCmd;
	float32 fIdFWCmdMax;
}IDFW_REGS;


typedef struct
{
	uint32  uiDataNew;
	uint32  uiDataOld;
	int32  	lDataDiff;
	uint32	ulTimeCnt;
	float32 fFreq;
	float32 fMaxDataRev;
	float32 fMaxSpeed_RPM;
	float32 fScale;
	float32 fSpeed;
	float32 fSpeed_RPM;
	float32 fSpeed_max;
	float32 fSpeed_min;

	uint32 ultime;
	uint32 ultimemax;

}SPEED_REGS;


typedef struct
{
	float32 fAcc_Diff;
	float32 fAcc_New;
	float32 fAcc_Old;
	float32 fAcc;

}ACCELERATION_REGS;

typedef struct
{
	float32  fDataIn;
	float32	 fAcc;
	float32	 fDec;
	float32  fDataOut;
}ACCDEC_REGS;

typedef struct
{
	uint32	 state;
	float32	 fStartAngle;
	float32	 fHoldCurrent;
	uint32	 ulHoldCnt;
	uint32	 ulHoldCntMax;
	uint32	 ulHoldEncData;
	uint32	 ulCheckCmd;
	float32	 fCheckAngle;
	uint32	 ulCheckPosEncData;
	uint32	 ulCheckNegEncData;
	uint32	 ulCheckPass;
	uint32	 ulCheckCnt;
	uint32	 ulCheckCntMax;
	uint32	 ulFinishCnt;
	uint32	 ulFinishCntMax;
	float32	 fFinishAngle;
	uint32	 ulFinishEncData;
	uint32	 ulFinishEncAdjustData;


	uint32   ulFirstCloselooptcnt;
	uint32   ulFirstCloseloopflag;
}STARTUP_REGS;



typedef struct
{
	uint32	 ulstate;

	uint32	 ulEncZCheckCnt;
	uint32   ulHoldcnt;
	uint32   ulHoldcnt_max;
	float32	 fStartAngle;
	float32	 fHoldCurrent;
	float32	 fDeltaHoldCurrent;
	float32	 fEndCurrent;
	float32	 fVirtualSpeed;

	uint32   ulEncPos_old;
	int32    lEncPos_check;
	uint32	 ulEncZPos1;
	uint32	 ulEncZPos2;
	int32	 lEncZPosDiff;

	float32  fanglediff;
	float32  fEncAngleElec;
	float32  fEncAngleElecold;
	uint32    ulEncerrorcnt;
	float32  fEncAngElecdiff;
}STARTCHECK_REGS;



typedef struct
{
	uint32  overCurrent :1;
	uint32  overVoltage :1;
	uint32  underVoltage :1;
	uint32  overTemperature :1;
	uint32  findHome :1;
	uint32  limitHomeSwitch :1;
	uint32  overLoad :1;
	uint32  encodererror  :1;
	uint32  servoerror  :1;
	uint32  reserved8 :8;
	uint32  reserved16 :16;
}ALARM_REGS;

typedef union
{
	ALARM_REGS data;
	uint32 all;
}ALARM;

typedef struct
{
	uint32  overCurrent :1;
	uint32  reserved1 :1;
	uint32  underVoltage :1;
	uint32  reserved3 :1;
	uint32  reserved4 :1;
	uint32  limitHomeSwitch :1;
	uint32  reserved6 :1;
	uint32  reserved7 :1;
	uint32  reserved8 :8;
	uint32  reserved16 :16;
}WARNING_REGS;

typedef union
{
	WARNING_REGS data;
	uint32 all;
}WARNING;

typedef struct
{
	// driver basic
	uint32 ctrlMode;
	uint32 ctrlType;
	uint32 servoOnMode;

	// motor control alarm flag
	uint32	alarmFlag;
	uint32	alarmClearFlag;
	ALARM	alarmCode;

	// motor control warning flag
	uint32	warningFlag;
	uint32	warningClearFlag;
	uint32	warningClearBusyFlag;
	WARNING	warningCode;

	uint32	alarmUnderVoltageCnt;
	uint32	warningUnderVoltageCnt;
	uint32	alarmOverVoltageCnt;
	uint32	warningOverVoltageCnt;

	// motor control adjust flag
	uint32 adjustFlag;
	uint32 ulAdcAdjustCnt;
	uint32 adcOffsetFlag;

	// startup
	uint32 startUpMethod;

	// servo state
	uint32 servoState;
	uint32 servoStateCtrlr;
	uint32 servoStateIO;
	uint32 servoStateSW;

	// control loop
	uint32 ulCtrlBaseFreq;

	uint32 ulP_ctrlCnt;
	uint32 ulP_ctrlCntMax;
	uint32 p_ctrlflag;

	uint32 ulV_ctrlCnt;
	uint32 ulV_ctrlCntMax;
	uint32 v_ctrlflag;

	uint32 ulI_ctrlCnt;
	uint32 ulI_ctrlCntMax;
	uint32 i_ctrlflag;

	//LED
	uint32 uledmode;
	uint32 uledlevelmax;
	uint32 ulOver_Vled;

	// position loop
	uint32 	ulPCmd;
	uint32 	ulPCmdPara;
	uint32	ulPCmdCtrlr;
	uint32 	ulPCmdServoOff;
	float32 fPFbk;
	uint32  ulPFbk;
	uint32  ulPFbkServoOff;
	float32 fPLoopMaxV;
	float32 fPLoopMinV;
	float32 fPOut;
	uint32	ulPCmdOld;
	int32	lPCmdUnit;
	int32	lPCmdFirst;
	uint32	ulPCmdOut;

	// performance testing

	uint32   uloopcnt;
	uint32   ulfrequency;
	// speed loop
	float32 fVCmd;
	float32 fVCmdStep;
	float32 fVCmdAcc;
	float32 fVCmdDec;
	float32 fVCmdPara;
	uint32 	ulAngleCloseFlag;
	uint32  ulVCmdStepTime;
	int32  ulVCmdStepTimeMax;
	float32 fVfbk;
	float32 fVLoopMaxI;
	float32 fVLoopMinI;
	float32 fVOut;

	// current loop
	float32 fIqCmd;
	float32 fIqOffset;
	float32 fIqCmdPara;
	uint32  ulIqCmdStepTime;
	uint32  ulIqCmdStepTimeMax;
	float32 fIqfbk;
	float32 fIqLoopMaxVq;
	float32 fIqLoopMinVq;
	float32 fIqOut;
	float32 fIqThreshold;

	float32 fIdCmd;
	float32 fIdCmdPara;
	float32 fIdCmdHoldingPara;
	uint32  ulIdCmdStepTime;
	uint32  ulIdCmdStepTimeMax;
	float32 fIdfbk;
	float32 fIdLoopMaxVd;
	float32 fIdLoopMinVd;
	float32 fIdOut;

	// control module
	IDFW_REGS       idfWRegs;
	PARK_REGS		parkRegs;
	IPARK_REGS		iParkRegs;
	CLARKE_REGS		clarkeRegs;
	ICLARKE_REGS	iClarkeRegs;
	SVM_REGS		svmRegs;
	PI_REGS			Iq_piRegs;
	PI_REGS			Id_piRegs;
	PI_REGS			V_piRegs;
	P_REGS			P_pRegs;
	SPEED_REGS		speedRegs;
	ACCELERATION_REGS  accRegs;

	ACCDEC_REGS		speedAccDecRegs;
	STARTUP_REGS	startUpRegs;
	STARTCHECK_REGS	startUpCheckRegs;
}MOTORDRIVE_REGS;

typedef struct
{

	float32 fIu_A;
	float32 fIv_A;
	float32 fIw_A;
	float32 fIuOffset;
	float32 fIvOffset;
	float32 fIwOffset;
	float32 fIu;
	float32 fIv;
	float32 fIw;
	float32 fIalpha;
	float32 fIbeta;
	float32 fId;
	float32 fIq;

	float32 fVd;
	float32 fVq;
	float32 fValpha;
	float32 fVbeta;
	float32 fVu;
	float32 fVv;
	float32 fVw;

	float32 fTa;
	float32 fTb;
	float32 fTc;

	float32 fLedVoltage;

	uint32  ulTa;
	uint32  ulTb;
	uint32  ulTc;

	uint32  ulDutyLed;

	float32 fV;
	float32 fV_RPM;
	float32 fV_scale;

	float32 fP;

	uint32 ulEncoderAngleNew;
	uint32 ulEncoderAngleOld;
	uint32 ulEncoderAngleData;
	uint32 ulEncoderPositonData;

	uint32 ulEncoderPosition_new;
	uint32 ulEncoderPosition_old;

	uint32 ulEncoderPosition_realpos;
	int32 lEncoderPosition_offset;

	uint32 ulEncoderIndexFlag;
	uint32 ulEncoderIndexData;

	uint32 ulEncoderZData;

	float32 fuvwindex;
	float32 fuvwflag;
	int32 iuvwangle;

	float32 fAngleVirtual;
	float32 fAngleMech;
	float32 fAngleMechOffset;
	float32 fAngleElec;

	float32 fBusVoltage;
	float32 fTemp;
	float32 fdatabuff[50];

	LOW_PASS_FILTER_REGS  LPF_IIR_1stOrder_REGS;
	NOTCHFILTER    NotchFilterRegs;
}MOTORDRIVE_DATA_REGS;

typedef struct
{
	uint32 motorType;
    uint32 ulPoles;
    uint32 motorPhaseDir;

    float32 fSpeedRated;
    float32 fSpeedMax;
	float32 fCurrentRated;
	float32 fCurrentMax;

	float32 fmotorAngleLead;
	float32 fmotorAngleLag;

	float32 fKe;
	float32 fR;
	float32 fL;
	float32 fI;

}PARA_MOTOR_REGS;

typedef struct
{
    uint32 ulEncoderType;
    uint32 ulEncoderMaxPulse;
    uint32 ulEncoderIndexOffset;
    uint32 encoderDir;
}PARA_ENCODER_REGS;

typedef struct
{
	// control
	uint32 pulseCommandType;
	uint32 pulseCommandReverse;

	// driver
	uint32 	driverType;
	float32 fPower;
	float32 fCurrentGain;
	float32 fCurrentScale;
	float32 fBusVoltageOver;
	float32 fBusVoltageUnder;

	// motor
	PARA_MOTOR_REGS motor;

	// encoder
	PARA_ENCODER_REGS encoder;

	// system
	float32 fILoad;
}MOTORDRIVE_PARA_REGS;

// extern variable
extern MOTORDRIVE_REGS mDrvRegs;
extern MOTORDRIVE_DATA_REGS mDataRegs;
extern MOTORDRIVE_PARA_REGS mParaRegs;


// extern function
extern void mDrv_init(void);
#define motorDrive_init mDrv_init // For api initialization standard

extern void motorDrive_isr(void);
extern void motorDrive_overCurrent_isr(void);

extern void speed_scaleUpdate(SPEED_REGS *speedRegs, float32 fFreq, float32 fMaxDataRev, float32 fMaxSpeed_RPM);
#define mDrv_speedScaleUpdate_macro()	speed_scaleUpdate(&mDrvRegs.speedRegs,\
										mDrvRegs.ulCtrlBaseFreq / mDrvRegs.ulV_ctrlCntMax,\
										mParaRegs.encoder.ulEncoderMaxPulse,\
										mParaRegs.motor.fSpeedMax);

extern void accDec_accDecUpdate(ACCDEC_REGS *accDecRegs, float32 fFreq, float32 fAccTime, float32 fDecTime);
#define mDrv_speedAccDecUpdate_macro() accDec_accDecUpdate(&mDrvRegs.speedAccDecRegs,\
										mDrvRegs.ulCtrlBaseFreq / mDrvRegs.ulV_ctrlCntMax,\
										mDrvRegs.fVCmdAcc,\
										mDrvRegs.fVCmdDec);

extern void mPara_motorTypeConfig(PARA_MOTOR_REGS *mParaMotorRegs,uint32 motorType);

#define mPara_motorTypeConfig_macro(motorType) 	mPara_motorTypeConfig(&mParaRegs.motor,motorType);


extern float32 mDrv_stepCmd(float32 fCmdIn, uint32* ulStepCnt, uint32 ulStepCntMax);

#define mDrv_mDrvAdjustFlagGet_macro()		mDrvRegs.adjustFlag

#define mDrv_mDrvAdcOffsetFlagGet_macro()		mDrvRegs.adcOffsetFlag

#define mDrv_mDrvAlarmFlagGet_macro()		mDrvRegs.alarmFlag
#define mDrv_mDrvAlarmFlagSet_macro(data)	mDrvRegs.alarmFlag = data

#define mDrv_mDrvAlarmClearFlagGet_macro()		mDrvRegs.alarmClearFlag
#define mDrv_mDrvAlarmClearFlagSet_macro(data)	mDrvRegs.alarmClearFlag = data

#define mDrv_mDrvAlarmGet_macro()						mDrvRegs.alarmCode.all
#define mDrv_mDrvAlarmOverCurrentSet_macro(dataIn)		mDrvRegs.alarmCode.data.overCurrent = dataIn
#define mDrv_mDrvAlarmfindHomeSet_macro(dataIn)			mDrvRegs.alarmCode.data.findHome = dataIn
#define mDrv_mDrvAlarmfindHomeGet_macro()	            mDrvRegs.alarmCode.data.findHome
#define mDrv_mDrvAlarmlimitHomeSwitchSet_macro(dataIn)	mDrvRegs.alarmCode.data.limitHomeSwitch = dataIn
#define mDrv_mDrvAlarmlimitHomeSwitchGet_macro()		mDrvRegs.alarmCode.data.limitHomeSwitch
#define mDrv_mDrvAlarmOverVoltageSet_macro(dataIn)		mDrvRegs.alarmCode.data.overVoltage = dataIn
#define mDrv_mDrvAlarmOverVoltageGet_macro()			mDrvRegs.alarmCode.data.overVoltage

#define mDrv_mDrvWarningFlagGet_macro()				mDrvRegs.warningFlag
#define mDrv_mDrvWarningFlagSet_macro(data)			mDrvRegs.warningFlag = data

#define mDrv_mDrvWarningGet_macro()							mDrvRegs.warningCode.all
#define mDrv_mDrvWarningOverCurrentSet_macro(dataIn)		mDrvRegs.warningCode.data.overCurrent = dataIn
#define mDrv_mDrvWarningUnderVoltageSet_macro(dataIn)		mDrvRegs.warningCode.data.underVoltage = dataIn
#define mDrv_mDrvWarningUnderVoltageGet_macro()				mDrvRegs.warningCode.data.underVoltage
#define mDrv_mDrvWarninglimitHomeSwitchSet_macro(dataIn)	mDrvRegs.warningCode.data.limitHomeSwitch = dataIn
#define mDrv_mDrvWarninglimitHomeSwitchGet_macro()			mDrvRegs.warningCode.data.limitHomeSwitch


#define mDrv_mDrvStartUpMethodGet_macro()	mDrvRegs.startUpMethod
#define mDrv_mDrvStartUpMethodSet_macro(data)	mDrvRegs.startUpMethod = data

#define mDrv_ctrlModeGet_macro()   		mDrvRegs.ctrlMode
#define mDrv_ctrlModeSet_macro(data)	mDrvRegs.ctrlMode = data

#define mDrv_servoOnModeGet_macro()		mDrvRegs.servoOnMode
#define mDrv_servoOnModeSet_macro(data) mDrvRegs.servoOnMode = data

#define mDrv_ctrlTypeGet_macro()        mDrvRegs.ctrlType
#define mDrv_ctrlTypeSet_macro(data)	mDrvRegs.ctrlType = data

extern void mDrv_servo_on_DI_update(uint32 data);

#define mDrv_servoStateGet_macro()             mDrvRegs.servoState
#define mDrv_servoStateSet_macro(data)         mDrvRegs.servoState = data
#define mDrv_servoStateCtrlrSet_macro(data)    mDrvRegs.servoStateCtrlr = data
#define mDrv_servoStateIOSet_macro(data)       mDrvRegs.servoStateIO = data
#define mDrv_servoStateSWSet_macro(data)       mDrvRegs.servoStateSW = data
#define mDrv_servoStateIOGet_macro()		   mDrvRegs.servoStateIO
#define mDrv_servoStateIOAddrGet()			   &mDrvRegs.servoStateIO
#define mDrv_servoStateSWAddrGet()		   	   &mDrvRegs.servoStateSW

#define mDrv_ulCtrlBaseFreqGet_macro()         mDrvRegs.ulCtrlBaseFreq
#define mDrv_ulCtrlBaseFreqSet_macro(data)     mDrvRegs.ulCtrlBaseFreq = data

#define mDrv_ulP_ctrlCntGet_macro()            mDrvRegs.ulP_ctrlCnt
#define mDrv_ulP_ctrlCntMaxGet_macro()         mDrvRegs.ulP_ctrlCntMax
#define mDrv_p_ctrlflagGet_macro()           mDrvRegs.p_ctrlflag

#define mDrv_ulV_ctrlCntGet_macro()            mDrvRegs.ulV_ctrlCnt
#define mDrv_ulV_ctrlCntMaxGet_macro()         mDrvRegs.ulV_ctrlCntMax
#define mDrv_v_ctrlflagGet_macro()           mDrvRegs.v_ctrlflag

#define mDrv_ulI_ctrlCntGet_macro()            mDrvRegs.ulI_ctrlCnt
#define mDrv_ulI_ctrlCntMaxGet_macro()         mDrvRegs.ulI_ctrlCntMax
#define mDrv_i_ctrlflagGet_macro()           mDrvRegs.i_ctrlflag

#define mDrv_ulPCmdGet_macro()                 mDrvRegs.ulPCmd
#define mDrv_ulPCmdParaGet_macro()             mDrvRegs.ulPCmdPara
#define mDrv_ulPCmdParaSet_macro(data)		   mDrvRegs.ulPCmdPara = data
#define mDrv_ulPCmdCtrlrGet_macro()            mDrvRegs.ulPCmdCtrlr
#define mDrv_ulPCmdCtrlrSet_macro(data)		   mDrvRegs.ulPCmdCtrlr = data
#define mDrv_fPLoopMaxVGet_macro()             mDrvRegs.fPLoopMaxV
#define mDrv_fPLoopMaxVSet_macro(data)         mDrvRegs.fPLoopMaxV = data
#define mDrv_fPLoopMinVGet_macro()             mDrvRegs.fPLoopMinV
#define mDrv_fPLoopMinVSet_macro(data)         mDrvRegs.fPLoopMinV = data
#define mDrv_fPOutGet_macro()                  mDrvRegs.fPOut

#define mDrv_fVCmdGet_macro()                  mDrvRegs.fVCmd
#define mDrv_fVCmdAccGet_macro()               mDrvRegs.fVCmdAcc
#define mDrv_fVCmdAccSet_macro(data)           mDrvRegs.fVCmdAcc = data
#define mDrv_fVCmdDecGet_macro()               mDrvRegs.fVCmdDec
#define mDrv_fVCmdDecSet_macro(data)           mDrvRegs.fVCmdDec = data
#define mDrv_fVCmdParaGet_macro()              mDrvRegs.fVCmdPara
#define mDrv_fVCmdParaSet_macro(data)          mDrvRegs.fVCmdPara = data
#define mDrv_ulAngleCloseFlagGet_macro()       mDrvRegs.ulAngleCloseFlag
#define mDrv_ulVCmdStepTimeGet_macro()         mDrvRegs.ulVCmdStepTime
#define mDrv_ulVCmdStepTimeMaxGet_macro()      mDrvRegs.ulVCmdStepTimeMax
#define mDrv_ulVCmdStepTimeMaxSet_macro(data)  mDrvRegs.ulVCmdStepTimeMax = data
#define mDrv_fVfbkGet_macro()                  mDrvRegs.fVfbk
#define mDrv_fVLoopMaxIGet_macro()             mDrvRegs.fVLoopMaxI
#define mDrv_fVLoopMaxISet_macro(data)         mDrvRegs.fVLoopMaxI = data
#define mDrv_fVLoopMinIGet_macro()             mDrvRegs.fVLoopMinI
#define mDrv_fVLoopMinISet_macro(data)         mDrvRegs.fVLoopMinI = data
#define mDrv_fVOutGet_macro()                  mDrvRegs.fVOut

#define mDrv_fIqCmdGet_macro()                 mDrvRegs.fIqCmd
#define mDrv_fIqCmdParaGet_macro()             mDrvRegs.fIqCmdPara
#define mDrv_fIqCmdParaSet_macro(data) 		   mDrvRegs.fIqCmdPara = data
#define mDrv_ulIqCmdStepTimeGet_macro()        mDrvRegs.ulIqCmdStepTime
#define mDrv_ulIqCmdStepTimeMaxGet_macro()     mDrvRegs.ulIqCmdStepTimeMax
#define mDrv_ulIqCmdStepTimeMaxSet_macro(data) mDrvRegs.ulIqCmdStepTimeMax = data
#define mDrv_fIqfbkGet_macro()                 mDrvRegs.fIqfbk
#define mDrv_fIqLoopMaxVqGet_macro()           mDrvRegs.fIqLoopMaxVq
#define mDrv_fIqLoopMaxVqSet_macro(data)       mDrvRegs.fIqLoopMaxVq = data
#define mDrv_fIqLoopMinVqGet_macro()           mDrvRegs.fIqLoopMinVq
#define mDrv_fIqLoopMinVqSet_macro(data)       mDrvRegs.fIqLoopMinVq = data
#define mDrv_fIqOutGet_macro()                 mDrvRegs.fIqOut
#define mDrv_fIqThresholdSet_macro(data)       mDrvRegs.fIqThreshold = data
#define mDrv_fIqThresholdGet_macro()       	   mDrvRegs.fIqThreshold

#define mDrv_fIdCmdGet_macro()                 mDrvRegs.fIdCmd
#define mDrv_fIdCmdParaGet_macro()             mDrvRegs.fIdCmdPara
#define mDrv_fIdCmdParaSet_macro(data) 		   mDrvRegs.fIdCmdPara = data
#define mDrv_ulIdCmdStepTimeGet_macro()        mDrvRegs.ulIdCmdStepTime
#define mDrv_ulIdCmdStepTimeMaxGet_macro()     mDrvRegs.ulIdCmdStepTimeMax
#define mDrv_ulIdCmdStepTimeMaxSet_macro(data) mDrvRegs.ulIdCmdStepTimeMax = data
#define mDrv_fIdCmdHoldingParaGet_macro()      mDrvRegs.fIdCmdHoldingPara
#define mDrv_fIdCmdHoldingParaSet_macro(data)  mDrvRegs.fIdCmdHoldingPara = data
#define mDrv_fIdfbkGet_macro()                 mDrvRegs.fIdfbk
#define mDrv_fIdLoopMaxVdGet_macro()           mDrvRegs.fIdLoopMaxVd
#define mDrv_fIdLoopMaxVdSet_macro(data)       mDrvRegs.fIdLoopMaxVd = data
#define mDrv_fIdLoopMinVdGet_macro()           mDrvRegs.fIdLoopMinVd
#define mDrv_fIdLoopMinVdSet_macro(data)       mDrvRegs.fIdLoopMinVd = data
#define mDrv_fIdOutGet_macro()                 mDrvRegs.fIdOut

#define mDrv_fAngleCompGainGet_macro()         mDrvRegs.fAngleCompGain
#define mDrv_fAngleCompGainSet_macro(data) 	   mDrvRegs.fAngleCompGain = data
#define mDrv_ulAngleCompTimeGet_macro()        mDrvRegs.ulAngleCompTime
#define mDrv_ulAngleCompTimeSet_macro(data)    mDrvRegs.ulAngleCompTime = data

#define mDrv_park_fAlphaGet_macro()            mDrvRegs.parkRegs.fAlpha
#define mDrv_park_fBetaGet_macro()             mDrvRegs.parkRegs.fBeta
#define mDrv_park_fThetaGet_macro()            mDrvRegs.parkRegs.fTheta
#define mDrv_park_fSineGet_macro()             mDrvRegs.parkRegs.fSine
#define mDrv_park_fCosineGet_macro()           mDrvRegs.parkRegs.fCosine
#define mDrv_park_fDGet_macro()                mDrvRegs.parkRegs.fD
#define mDrv_park_fQGet_macro()                mDrvRegs.parkRegs.fQ

#define mDrv_iPark_fAlphaGet_macro()           mDrvRegs.iParkRegs.fAlpha
#define mDrv_iPark_fBetaGet_macro()            mDrvRegs.iParkRegs.fBeta
#define mDrv_iPark_fThetaGet_macro()           mDrvRegs.iParkRegs.fTheta
#define mDrv_iPark_fSineGet_macro()            mDrvRegs.iParkRegs.fSine
#define mDrv_iPark_fCosineGet_macro()          mDrvRegs.iParkRegs.fCosine
#define mDrv_iPark_fDGet_macro()               mDrvRegs.iParkRegs.fD
#define mDrv_iPark_fQGet_macro()               mDrvRegs.iParkRegs.fQ

#define mDrv_clarke_fUGet_macro()              mDrvRegs.clarkeRegs.fU
#define mDrv_clarke_fVGet_macro()              mDrvRegs.clarkeRegs.fV
#define mDrv_clarke_fWGet_macro()              mDrvRegs.clarkeRegs.fW
#define mDrv_clarke_fAlphaGet_macro()          mDrvRegs.clarkeRegs.fAlpha
#define mDrv_clarke_fBetaGet_macro()           mDrvRegs.clarkeRegs.fBeta

#define mDrv_iClarke_fUGet_macro()             mDrvRegs.iClarkeRegs.fU
#define mDrv_iClarke_fVGet_macro()             mDrvRegs.iClarkeRegs.fV
#define mDrv_iClarke_fWGet_macro()             mDrvRegs.iClarkeRegs.fW
#define mDrv_iClarke_fAlphaGet_macro()         mDrvRegs.iClarkeRegs.fAlpha
#define mDrv_iClarke_fBetaGet_macro()          mDrvRegs.iClarkeRegs.fBeta

#define mDrv_svm_fUGet_macro()                 mDrvRegs.svmRegs.fU
#define mDrv_svm_fVGet_macro()                 mDrvRegs.svmRegs.fV
#define mDrv_svm_fWGet_macro()                 mDrvRegs.svmRegs.fW
#define mDrv_svm_fMaxGet_macro()               mDrvRegs.svmRegs.fMax
#define mDrv_svm_fMinGet_macro()               mDrvRegs.svmRegs.fMin
#define mDrv_svm_fCommGet_macro()              mDrvRegs.svmRegs.fComm
#define mDrv_svm_fAGet_macro()                 mDrvRegs.svmRegs.fA
#define mDrv_svm_fBGet_macro()                 mDrvRegs.svmRegs.fB
#define mDrv_svm_fCGet_macro()                 mDrvRegs.svmRegs.fC

#define mDrv_Iq_pi_fBwGet_macro()              mDrvRegs.Iq_piRegs.fBw
#define mDrv_Iq_pi_fBwSet_macro(data)          mDrvRegs.Iq_piRegs.fBw = data
#define mDrv_Iq_pi_fTcGet_macro()              mDrvRegs.Iq_piRegs.fTc
#define mDrv_Iq_pi_fTcSet_macro(data)          mDrvRegs.Iq_piRegs.fTc = data
#define mDrv_Iq_pi_fRefGet_macro()             mDrvRegs.Iq_piRegs.fRef
#define mDrv_Iq_pi_fFbkGet_macro()             mDrvRegs.Iq_piRegs.fFbk
#define mDrv_Iq_pi_fErrGet_macro()             mDrvRegs.Iq_piRegs.fErr
#define mDrv_Iq_pi_fKpGet_macro()              mDrvRegs.Iq_piRegs.fKp
#define mDrv_Iq_pi_fKpSet_macro(data) 		   mDrvRegs.Iq_piRegs.fKp = data
#define mDrv_Iq_pi_fUpGet_macro()              mDrvRegs.Iq_piRegs.fUp
#define mDrv_Iq_pi_fIntGet_macro()             mDrvRegs.Iq_piRegs.fInt
#define mDrv_Iq_pi_fKiGet_macro()              mDrvRegs.Iq_piRegs.fKi
#define mDrv_Iq_pi_fKiSet_macro(data) 		   mDrvRegs.Iq_piRegs.fKi = data
#define mDrv_Iq_pi_fUiGet_macro()              mDrvRegs.Iq_piRegs.fUi
#define mDrv_Iq_pi_fMaxGet_macro()             mDrvRegs.Iq_piRegs.fMax
#define mDrv_Iq_pi_fMaxSet_macro(data)         mDrvRegs.Iq_piRegs.fMax = data
#define mDrv_Iq_pi_fMinGet_macro()             mDrvRegs.Iq_piRegs.fMin
#define mDrv_Iq_pi_fMinSet_macro(data)         mDrvRegs.Iq_piRegs.fMin = data
#define mDrv_Iq_pi_fOutSatGet_macro()          mDrvRegs.Iq_piRegs.fOutSat
#define mDrv_Iq_pi_fOutGet_macro()             mDrvRegs.Iq_piRegs.fOut

#define mDrv_Id_pi_fBwGet_macro()              mDrvRegs.Id_piRegs.fBw
#define mDrv_Id_pi_fBwSet_macro(data)          mDrvRegs.Id_piRegs.fBw = data
#define mDrv_Id_pi_fTcGet_macro()              mDrvRegs.Id_piRegs.fTc
#define mDrv_Id_pi_fTcSet_macro(data)          mDrvRegs.Id_piRegs.fTc = data
#define mDrv_Id_pi_fRefGet_macro()             mDrvRegs.Id_piRegs.fRef
#define mDrv_Id_pi_fFbkGet_macro()             mDrvRegs.Id_piRegs.fFbk
#define mDrv_Id_pi_fErrGet_macro()             mDrvRegs.Id_piRegs.fErr
#define mDrv_Id_pi_fKpGet_macro()              mDrvRegs.Id_piRegs.fKp
#define mDrv_Id_pi_fKpSet_macro(data)		   mDrvRegs.Id_piRegs.fKp = data
#define mDrv_Id_pi_fUpGet_macro()              mDrvRegs.Id_piRegs.fUp
#define mDrv_Id_pi_fIntGet_macro()             mDrvRegs.Id_piRegs.fInt
#define mDrv_Id_pi_fKiGet_macro()              mDrvRegs.Id_piRegs.fKi
#define mDrv_Id_pi_fKiSet_macro(data)		   mDrvRegs.Id_piRegs.fKi = data
#define mDrv_Id_pi_fUiGet_macro()              mDrvRegs.Id_piRegs.fUi
#define mDrv_Id_pi_fMaxGet_macro()             mDrvRegs.Id_piRegs.fMax
#define mDrv_Id_pi_fMaxSet_macro(data)         mDrvRegs.Id_piRegs.fMax = data
#define mDrv_Id_pi_fMinGet_macro()             mDrvRegs.Id_piRegs.fMin
#define mDrv_Id_pi_fMinSet_macro(data)         mDrvRegs.Id_piRegs.fMin = data
#define mDrv_Id_pi_fOutSatGet_macro()          mDrvRegs.Id_piRegs.fOutSat
#define mDrv_Id_pi_fOutGet_macro()             mDrvRegs.Id_piRegs.fOut

#define mDrv_V_pi_ulindexGet_macro()  		   mDrvRegs.V_piRegs.ulindex
#define mDrv_V_pi_ulindexSet_macro(data)  	   mDrvRegs.V_piRegs.ulindex = data


#define mDrv_V_pi_fRefGet_macro()              mDrvRegs.V_piRegs.fRef
#define mDrv_V_pi_fFbkGet_macro()              mDrvRegs.V_piRegs.fFbk
#define mDrv_V_pi_fErrGet_macro()              mDrvRegs.V_piRegs.fErr
#define mDrv_V_pi_fKpGet_macro()               mDrvRegs.V_piRegs.fKp
#define mDrv_V_pi_fKpSet_macro(data) 			mDrvRegs.V_piRegs.fKp = data
#define mDrv_V_pi_fUpGet_macro()               mDrvRegs.V_piRegs.fUp
#define mDrv_V_pi_fIntGet_macro()              mDrvRegs.V_piRegs.fInt
#define mDrv_V_pi_fKiGet_macro()               mDrvRegs.V_piRegs.fKi
#define mDrv_V_pi_fKiSet_macro(data) 			mDrvRegs.V_piRegs.fKi = data
#define mDrv_V_pi_fUiGet_macro()               mDrvRegs.V_piRegs.fUi
#define mDrv_V_pi_fMaxGet_macro()              mDrvRegs.V_piRegs.fMax
#define mDrv_V_pi_fMaxSet_macro(data)          mDrvRegs.V_piRegs.fMax = data
#define mDrv_V_pi_fMinGet_macro()              mDrvRegs.V_piRegs.fMin
#define mDrv_V_pi_fMinSet_macro(data)          mDrvRegs.V_piRegs.fMin = data
#define mDrv_V_pi_fOutSatGet_macro()           mDrvRegs.V_piRegs.fOutSat
#define mDrv_V_pi_fOutGet_macro()              mDrvRegs.V_piRegs.fOut
#define mDrv_V_pi_fBwGet_macro()               mDrvRegs.V_piRegs.fBw
#define mDrv_V_pi_fBwSet_macro(data) 		   mDrvRegs.V_piRegs.fBw = data
#define mDrv_V_pi_fTcGet_macro()               mDrvRegs.V_piRegs.fTc
#define mDrv_V_pi_fTcSet_macro(data) 		   mDrvRegs.V_piRegs.fTc = data
#define mDrv_V_pi_fKfGet_macro()               mDrvRegs.V_piRegs.fKf
#define mDrv_V_pi_fKfSet_macro(data) 		   mDrvRegs.V_piRegs.fKf = data
#define mDrv_V_pi_fRKfGet_macro()              mDrvRegs.V_piRegs.fRKf
#define mDrv_V_pi_fRKfSet_macro(data) 		   mDrvRegs.V_piRegs.fRKf = data



#define mDrv_P_p_fRefGet_macro()               mDrvRegs.P_pRegs.fRef
#define mDrv_P_p_fFbkGet_macro()               mDrvRegs.P_pRegs.fFbk
#define mDrv_P_p_fErrGet_macro()               mDrvRegs.P_pRegs.fErr
#define mDrv_P_p_fKpGet_macro()                mDrvRegs.P_pRegs.fKp
#define mDrv_P_p_fKpSet_macro(data) 		   mDrvRegs.P_pRegs.fKp = data
#define mDrv_P_p_fUpGet_macro()                mDrvRegs.P_pRegs.fUp
#define mDrv_P_p_fMaxGet_macro()               mDrvRegs.P_pRegs.fMax
#define mDrv_P_p_fMaxSet_macro(data)           mDrvRegs.P_pRegs.fMax = data
#define mDrv_P_p_fMinGet_macro()               mDrvRegs.P_pRegs.fMin
#define mDrv_P_p_fMinSet_macro(data)           mDrvRegs.P_pRegs.fMin = data
#define mDrv_P_p_fOutSatGet_macro()            mDrvRegs.P_pRegs.fOutSat
#define mDrv_P_p_fOutGet_macro()               mDrvRegs.P_pRegs.fOut
#define mDrv_P_p_fKdGet_macro()                mDrvRegs.P_pRegs.fKd
#define mDrv_P_p_fKdSet_macro(data) 		   mDrvRegs.P_pRegs.fKd = data

#define mDrv_idfW_fIdFWSet_macro(data)        mDrvRegs.idfWRegs.fIdFWCmdMax = data
#define mDrv_idfW_fIdFWGet_macro()            mDrvRegs.idfWRegs.fIdFWCmdMax
#define mDrv_idfW_fSpeedSet_macro(data)       mDrvRegs.idfWRegs.fSpeedCmdBoundary = data
#define mDrv_idfW_fSpeedGet_macro()           mDrvRegs.idfWRegs.fSpeedCmdBoundary

#define mDrv_startup_stateGet_macro()                   mDrvRegs.startUpRegs.state
#define mDrv_startup_fStartAngleGet_macro()             mDrvRegs.startUpRegs.fStartAngle
#define mDrv_startup_fHoldCurrentGet_macro()            mDrvRegs.startUpRegs.fHoldCurrent
#define mDrv_startup_ulHoldCntGet_macro()               mDrvRegs.startUpRegs.ulHoldCnt
#define mDrv_startup_ulHoldCntMaxGet_mar_macro()        mDrvRegs.startUpRegs.ulHoldCntMax
#define mDrv_startup_ulHoldEncDataGet_macro()           mDrvRegs.startUpRegs.ulHoldEncData
#define mDrv_startup_ulCheckCmdGet_macro()              mDrvRegs.startUpRegs.ulCheckCmd
#define mDrv_startup_fCheckAngleGet_macro()             mDrvRegs.startUpRegs.fCheckAngle
#define mDrv_startup_ulCheckPosEncDataGet_macro()       mDrvRegs.startUpRegs.ulCheckPosEncData
#define mDrv_startup_ulCheckNegEncDataGet_macro()       mDrvRegs.startUpRegs.ulCheckNegEncData
#define mDrv_startup_ulCheckPassGet_macro()             mDrvRegs.startUpRegs.ulCheckPass
#define mDrv_startup_ulCheckCntGet_macro()              mDrvRegs.startUpRegs.ulCheckCnt
#define mDrv_startup_ulCheckCntMaxGet_macro()           mDrvRegs.startUpRegs.ulCheckCntMax
#define mDrv_startup_ulFinishCntGet_macro()             mDrvRegs.startUpRegs.ulFinishCnt
#define mDrv_startup_ulFinishCntMaxGet_macro()          mDrvRegs.startUpRegs.ulFinishCntMax
#define mDrv_startup_fFinishAngleGet_macro()            mDrvRegs.startUpRegs.fFinishAngle
#define mDrv_startup_ulFinishEncDataGet_macro()         mDrvRegs.startUpRegs.ulFinishEncData
#define mDrv_startup_ulFinishEncAdjustDataGet_macro()	mDrvRegs.startUpRegs.ulFinishEncAdjustData

#define mDrv_startup_stateSet_macro(data)                   mDrvRegs.startUpRegs.state = data
#define mDrv_startup_fStartAngleSet_macro(data)             mDrvRegs.startUpRegs.fStartAngle = data
#define mDrv_startup_fHoldCurrentSet_macro(data)            mDrvRegs.startUpRegs.fHoldCurrent = data
#define mDrv_startup_ulHoldCntSet_macro(data)               mDrvRegs.startUpRegs.ulHoldCnt = data
#define mDrv_startup_ulHoldCntMaxSet_macro(data)            mDrvRegs.startUpRegs.ulHoldCntMax = data
#define mDrv_startup_ulHoldEncDataSet_macro(data)           mDrvRegs.startUpRegs.ulHoldEncData = data
#define mDrv_startup_ulCheckCmdSet_macro(data)              mDrvRegs.startUpRegs.ulCheckCmd = data
#define mDrv_startup_fCheckAngleSet_macro(data)             mDrvRegs.startUpRegs.fCheckAngle = data
#define mDrv_startup_ulCheckPosEncDataSet_macro(data)       mDrvRegs.startUpRegs.ulCheckPosEncData = data
#define mDrv_startup_ulCheckNegEncDataSet_macro(data)       mDrvRegs.startUpRegs.ulCheckNegEncData = data
#define mDrv_startup_ulCheckPassSet_macro(data)             mDrvRegs.startUpRegs.ulCheckPass = data
#define mDrv_startup_ulCheckCntSet_macro(data)              mDrvRegs.startUpRegs.ulCheckCnt = data
#define mDrv_startup_ulCheckCntMaxSet_macro(data)           mDrvRegs.startUpRegs.ulCheckCntMax = data
#define mDrv_startup_ulFinishCntSet_macro(data)             mDrvRegs.startUpRegs.ulFinishCnt = data
#define mDrv_startup_ulFinishCntMaxSet_macro(data)          mDrvRegs.startUpRegs.ulFinishCntMax = data
#define mDrv_startup_fFinishAngleSet_macro(data)            mDrvRegs.startUpRegs.fFinishAngle = data
#define mDrv_startup_ulFinishEncDataSet_macro(data)         mDrvRegs.startUpRegs.ulFinishEncData = data
#define mDrv_startup_ulFinishEncAdjustDataSet_macro(data)	mDrvRegs.startUpRegs.ulFinishEncAdjustData = data

#define mDrv_ledmode_Set_macro(data)  						mDrvRegs.uledmode = data
#define mDrv_ledlevelmax_Set_macro(data)  					mDrvRegs.uledlevelmax = data
#define mDrv_ledlevelmax_Get_macro()  						mDrvRegs.uledlevelmax


#define mData_ulMotor_IDGet_macro()			mDataRegs.ulMotor_ID
#define mData_ulMotor_IDSet_macro(data)		mDataRegs.ulMotor_ID = data

#define mData_fIu_AGet_macro()				mDataRegs.fIu_A
#define mData_fIu_ASet_macro(data)			mDataRegs.fIu_A = data
#define mData_fIv_AGet_macro()				mDataRegs.fIv_A
#define mData_fIv_ASet_macro(data)			mDataRegs.fIv_A = data
#define mData_fIw_AGet_macro()				mDataRegs.fIw_A
#define mData_fIw_ASet_macro(data)			mDataRegs.fIw_A = data
#define mData_fIu_OffsetGet_macro()			mDataRegs.fIu_Offset
#define mData_fIu_OffsetSet_macro(data)		mDataRegs.fIu_Offset = data
#define mData_fIv_OffsetGet_macro()			mDataRegs.fIv_Offset
#define mData_fIv_OffsetSet_macro(data)		mDataRegs.fIv_Offset = data
#define mData_fIw_OffsetGet_macro()			mDataRegs.fIw_Offset
#define mData_fIw_OffsetSet_macro(data)		mDataRegs.fIw_Offset = data
#define mData_fIuGet_macro()				mDataRegs.fIu
#define mData_fIvGet_macro()				mDataRegs.fIv
#define mData_fIwGet_macro()				mDataRegs.fIw
#define mData_fIu_AGet_macro()				mDataRegs.fIu_A
#define mData_fIv_AGet_macro()				mDataRegs.fIv_A
#define mData_fIw_AGet_macro()				mDataRegs.fIw_A
#define mData_fIalphaGet_macro()			mDataRegs.fIalpha
#define mData_fIbetaGet_macro()				mDataRegs.fIbeta
#define mData_fIdGet_macro()				mDataRegs.fId
#define mData_fIqGet_macro()				mDataRegs.fIq

#define mData_fVdGet_macro()				mDataRegs.fVd
#define mData_fVqGet_macro()				mDataRegs.fVq
#define mData_fValphaGet_macro()			mDataRegs.fValpha
#define mData_fVbetaGet_macro()				mDataRegs.fVbeta
#define mData_fVuGet_macro()				mDataRegs.fVu
#define mData_fVvGet_macro()				mDataRegs.fVv
#define mData_fVwGet_macro()				mDataRegs.fVw

#define mData_fTaGet_macro()				mDataRegs.fTa
#define mData_fTbGet_macro()				mDataRegs.fTb
#define mData_fTcGet_macro()				mDataRegs.fTc
#define mData_ulTaGet_macro()				mDataRegs.ulTa
#define mData_ulTbGet_macro()				mDataRegs.ulTb
#define mData_ulTcGet_macro()				mDataRegs.ulTc

#define mData_fVGet_macro()					mDataRegs.fV
#define mData_fV_RPMGet_macro()				mDataRegs.fV_RPM
#define mData_fV_scaleGet_macro()			mDataRegs.fV_scale
#define mData_fV_scaleSet_macro(data)		mDataRegs.fV_scale = data

#define mData_fPGet_macro()					mDataRegs.fP

#define mData_fAangleVirtualGet_macro()			mDataRegs.fAngleVirtual
#define mData_fAngleMechGet_macro()				mDataRegs.fAngleMech
#define mData_fAngleMechOffsetGet_macro()		mDataRegs.fAngleMechOffset
#define mData_fAngleMechOffsetSet_macro(data)	mDataRegs.fAngleMechOffset = data
#define mData_fAngleElecGet_macro()				mDataRegs.fAngleElec
#define mData_UVWindexGet_macro()				mDataRegs.fuvwindex

#define mData_ulEncoderAngleDataGet_macro()		mDataRegs.ulEncoderAngleData
#define mData_ulEncoderPositonDataGet_macro()	mDataRegs.ulEncoderPositonData
#define mData_ulEncoderIndexFlagGet_macro()				mDataRegs.ulEncoderIndexFlag
#define mData_ulEncoderIndexDispPulseGet_macro()		mDataRegs.ulEncoderIndexDispPulse
#define mData_ulEncoderIndexDispPulseSet_macro(data)	mDataRegs.ulEncoderIndexDispPulse = data
#define mData_ulEncoderIndexDispPulseClear_macro()		mDataRegs.ulEncoderIndexDispPulse = 0
#define mData_ulEncoderIndexDataGet_macro()				mDataRegs.ulEncoderIndexData
#define mData_fTempGet_macro()						mDataRegs.fTemp

#define mData_ulLedDutySet_macro(data)              mDataRegs.ulDutyLed = data
#define mData_ulLedDutyGet_macro()              	mDataRegs.ulDutyLed

// motor parameter register
#define mPara_motorTypeGet_macro() 		mParaRegs.motor.motorType
#define mPara_motorTypeSet_macro(data) 	mParaRegs.motor.motorType = data

#define mPara_fSpeedMaxGet_macro()		mParaRegs.motor.fSpeedMax
#define mPara_fSpeedMaxSet_macro(data)	mParaRegs.motor.fSpeedMax = data

#define mPara_fCurrentMaxGet_macro()		mParaRegs.motor.fCurrentMax
#define mPara_fCurrentMaxSet_macro(data)	mParaRegs.motor.fCurrentMax = data

#define mPara_ulEncoderMaxPulseGet_macro()		mParaRegs.encoder.ulEncoderMaxPulse
#define mPara_ulEncoderMaxPulseSet_macro(data)	mParaRegs.encoder.ulEncoderMaxPulse = data

#define mPara_ulEncoderIndexOffsetGet_macro()		mParaRegs.encoder.ulEncoderIndexOffset
#define mPara_ulEncoderIndexOffsetSet_macro(data)	mParaRegs.encoder.ulEncoderIndexOffset = data

#define mPara_motorAngleLeadGet_macro()              mParaRegs.motor.fmotorAngleLead
#define mPara_motorAngleLeadSet_macro(data) 		mParaRegs.motor.fmotorAngleLead = data

#define mPara_motorAngleLagGet_macro()              mParaRegs.motor.fmotorAngleLag
#define mPara_motorAngleLagSet_macro(data) 			mParaRegs.motor.fmotorAngleLag = data

#define mPara_motorPhaseDirGet_macro()              mParaRegs.motor.motorPhaseDir
#define mPara_motorPhaseDirSet_macro(data) 			mParaRegs.motor.motorPhaseDir = data

#define mPara_encoderDirGet_macro()              mParaRegs.encoder.encoderDir
#define mPara_encoderDirSet_macro(data) 			mParaRegs.encoder.encoderDir = data

#define mPara_encoderTypeGet_macro()		mParaRegs.encoder.ulEncoderType
#define mPara_encoderTypeSet_macro(data)	mParaRegs.encoder.ulEncoderType = data

#define mPara_pulseCommandTypeGet_macro()       mParaRegs.pulseCommandType
#define mPara_pulseCommandTypeSet_macro(data)	mParaRegs.pulseCommandType = data

#define mPara_pulseCommandReverseGet_macro()		mParaRegs.pulseCommandReverse
#define mPara_pulseCommandReverseSet_macro(data)	mParaRegs.pulseCommandReverse = data

#define mPara_fCurrentScaleGet_macro() 		mParaRegs.fCurrentScale
#define mPara_fCurrentScaleSet_macro(data)	mParaRegs.fCurrentScale = data

#endif // end of file
