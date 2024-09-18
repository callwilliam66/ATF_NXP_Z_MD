////*****************************************////
//  Name : parameter_define.h
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#ifndef _PARAMETER_DEFINE_H_
#define _PARAMETER_DEFINE_H_

#include "api.h"

// define
typedef enum
{
	paraMode_normal              = 0,
	paraMode_currentTest         = 1,   // only current direction
	paraMode_currentResponseTest = 2,
	paraMode_angleTest           = 3,
	paraMode_speedLoopTest       = 4,
	paraMode_positionLoopTest    = 5,
	paraMode_autoFocusSystemDefault = 6,
	paraMode_pulseDirDefault = 7,
	paraMode_nosewheelDefault = 8
}PARA_MODE;

typedef enum
{
	paraType_wr = 0,
	paraType_ro = 1,
	paraType_w_reserved = 2
}PARA_TYPE;

typedef enum
{
	para_servo_on_unlocked  = 0,
	para_servo_on_locked 	= 1,
	para_servo_on_homefined = 2
}PARA_LOCK;

typedef enum
{
	para_change_immediately  = 0,
	para_change_reboot 	= 1
}PARA_CHANGE_REBOOT;

typedef enum
{
	paraSign_signed   = 0,
	paraSign_unsigned = 1,
	paraSign_hex = 2
}PARA_SIGN;


// setting
#define MAX_PARAMETER 512

// parameter list
#define PARA_CTRL_MODE					0	// 0x0000_0000
#define PARA_SERVO_ON_MODE				1	// 0x0000_0001
#define PARA_CTRL_TYPE					2	// 0x0000_0002

#define PARA_DRIVER_NUMBER				8	// 0x0000_0008
#define PARA_FIRMWARE_VERSION			9	// 0x0000_0009

#define PARA_HOME_ENABLE				10	// 0x0000_000A
#define PARA_LIMIT_POS_ENABLE			11	// 0x0000_000B
#define PARA_LIMIT_NEG_ENABLE			12	// 0x0000_000C

#define PARA_P_KP						20  // 0x0000_0014
#define PARA_P_KD						21  // 0x0000_0015
#define PARA_P_COEFF					22  // 0x0000_0016



#define PARA_V_KP1						27  // 0x0000_001B
#define PARA_V_KI1						28  // 0x0000_001C

#define PARA_V_INDEX					29  // 0x0000_001D
#define PARA_V_KP						30  // 0x0000_001E
#define PARA_V_KI						31  // 0x0000_001F
#define PARA_V_KF						32  // 0x0000_0020
#define PARA_V_RKF						33  // 0x0000_0021
#define PARA_V_KP2						34  // 0x0000_0022
#define PARA_V_KI2						35  // 0x0000_0023
#define PARA_V_KP3						36  // 0x0000_0024
#define PARA_V_KI3						37  // 0x0000_0025
#define PARA_V_KP4						38  // 0x0000_0026
#define PARA_V_KI4                      39  // 0x0000_0027

#define PARA_I_KP						40  // 0x0000_0028
#define PARA_I_KI						41  // 0x0000_0029
#define PARA_I_BW						42  // 0x0000_002A
#define PARA_I_TC						43  // 0x0000_002B

#define PARA_P_CMD						50  // 0x0000_0032

#define PARA_V_CMD						60  // 0x0000_003C
#define PARA_V_STEP						61  // 0x0000_003D
#define PARA_V_ACC						62  // 0x0000_003E
#define PARA_V_DEC						63  // 0x0000_003F

#define PARA_IQ_CMD						70  // 0x0000_0046
#define PARA_IQ_STEP					71  // 0x0000_0047
#define PARA_IQ_THRESHOID				72  // 0x0000_0048
#define PARA_ID_CMD						75  // 0x0000_004B
#define PARA_ID_STEP					76  // 0x0000_004C
#define PARA_ID_HOLD					77  // 0x0000_004D

#define PARA_STATUP_METHOD				80	// 0x0000_0050
#define PARA_STATUP_START_ANGLE			81	// 0x0000_0051
#define PARA_STATUP_MOVE_TIME			82	// 0x0000_0052
#define PARA_STATUP_CHECK_ANGLE			83	// 0x0000_0053

#define PARA_LED_MODE			    	90	// 0x0000_005A
#define PARA_LED_LEVELMAX				91	// 0x0000_005B
#define PARA_LED_LEVEL					92	// 0x0000_005C


#define PARA_TCURVE_VINIT				100	// 0x0000_0064
#define PARA_TCURVE_VEND				101	// 0x0000_0065
#define PARA_TCURVE_VMAX				102	// 0x0000_0066
#define PARA_TCURVE_TACC				103	// 0x0000_0067
#define PARA_TCURVE_TDEC				104	// 0x0000_0068

#define PARA_CTRLR_MODE					300 // 0x0000_012C

#define PARA_CTRLR_HOME_MODE			310 // 0x0000_0136
#define PARA_CTRLR_HOME_SPEED			311 // 0x0000_0137
#define PARA_CTRLR_HOME_POS				312 // 0x0000_0138

#define PARA_CTRLR_IN_POSITION_RANGE	320 // 0x0000_0140
#define PARA_CTRLR_ZERO_SPEED_RANGE		321 // 0x0000_0141

#define PARA_CTRLR_SOFT_NEG_LIMIT_ENABLE	330 // 0x0000_014A
#define PARA_CTRLR_SOFT_NEG_LIMIT			331 // 0x0000_014B
#define PARA_CTRLR_SOFT_POS_LIMIT_ENABLE	332 // 0x0000_014C
#define PARA_CTRLR_SOFT_POS_LIMIT			333 // 0x0000_014D

#define PARA_PULSECOMMAND_TYPE     		340 // 0x0000_0154
#define PARA_PULSECOMMAND_REVERSE  		341 // 0x0000_0155

#define PARA_ADVCTRL0_ENABLE			350 // 0x0000_015E
#define PARA_ADVCTRL0_PARA0				351 // 0x0000_015F
#define PARA_ADVCTRL0_PARA1				352 // 0x0000_0160
#define PARA_ADVCTRL0_PARA2				353 // 0x0000_0161
#define PARA_ADVCTRL0_PARA3				354 // 0x0000_0162
#define PARA_ADVCTRL1_ENABLE			355 // 0x0000_0153
#define PARA_ADVCTRL1_PARA0				356 // 0x0000_0154
#define PARA_ADVCTRL1_PARA1				357 // 0x0000_0165
#define PARA_ADVCTRL1_PARA2				358 // 0x0000_0166
#define PARA_ADVCTRL1_PARA3				359 // 0x0000_0167
#define PARA_ADVCTRL2_ENABLE			360 // 0x0000_0168
#define PARA_ADVCTRL2_PARA0				361 // 0x0000_0169
#define PARA_ADVCTRL2_PARA1				362 // 0x0000_016A
#define PARA_ADVCTRL2_PARA2				363 // 0x0000_016B
#define PARA_ADVCTRL2_PARA3				364 // 0x0000_016C
#define PARA_ADVCTRL3_ENABLE			365 // 0x0000_015D
#define PARA_ADVCTRL3_PARA0				366 // 0x0000_015E
#define PARA_ADVCTRL3_PARA1				367 // 0x0000_016F
#define PARA_ADVCTRL3_PARA2				368 // 0x0000_0170
#define PARA_ADVCTRL3_PARA3				369 // 0x0000_0171
#define PARA_ADVCTRL4_ENABLE			370 // 0x0000_0172
#define PARA_ADVCTRL4_PARA0				371 // 0x0000_0173
#define PARA_ADVCTRL4_PARA1				372 // 0x0000_0174
#define PARA_ADVCTRL4_PARA2				373 // 0x0000_0175
#define PARA_ADVCTRL4_PARA3				374 // 0x0000_0176
#define PARA_ADVCTRL5_ENABLE			375 // 0x0000_0177
#define PARA_ADVCTRL5_PARA0				376 // 0x0000_0178
#define PARA_ADVCTRL5_PARA1				377 // 0x0000_0179
#define PARA_ADVCTRL5_PARA2				378 // 0x0000_017A
#define PARA_ADVCTRL5_PARA3				379 // 0x0000_017B
#define PARA_ADVCTRL6_ENABLE			380 // 0x0000_017C
#define PARA_ADVCTRL6_PARA0				381 // 0x0000_017D
#define PARA_ADVCTRL6_PARA1				382 // 0x0000_017E
#define PARA_ADVCTRL6_PARA2				383 // 0x0000_017F
#define PARA_ADVCTRL6_PARA3				384 // 0x0000_0180
#define PARA_ADVCTRL7_ENABLE			385 // 0x0000_0181
#define PARA_ADVCTRL7_PARA0				386 // 0x0000_0182
#define PARA_ADVCTRL7_PARA1				387 // 0x0000_0183
#define PARA_ADVCTRL7_PARA2				388 // 0x0000_0184
#define PARA_ADVCTRL7_PARA3				389 // 0x0000_0185
#define PARA_ADVCTRL8_ENABLE			390 // 0x0000_0186
#define PARA_ADVCTRL8_PARA0				391 // 0x0000_0187
#define PARA_ADVCTRL8_PARA1				392 // 0x0000_0188
#define PARA_ADVCTRL8_PARA2				393 // 0x0000_0189
#define PARA_ADVCTRL8_PARA3				394 // 0x0000_018A
#define PARA_ADVCTRL9_ENABLE			395 // 0x0000_018B
#define PARA_ADVCTRL9_PARA0				396 // 0x0000_018C
#define PARA_ADVCTRL9_PARA1				397 // 0x0000_018D
#define PARA_ADVCTRL9_PARA2				398 // 0x0000_018E
#define PARA_ADVCTRL9_PARA3				399 // 0x0000_018F

#define PARA_MOTOR_TYPE					400 // 0x0000_0190

#define PARA_ENCODER_TYPE          		405 // 0x0000_0195
#define PARA_ENCODER_DIR				406 // 0x0000_0196
#define PARA_ENCODER_RESOLUTION			407 // 0x0000_0197
#define PARA_ANGLE_OFFSET	       		408 // 0x0000_0198

#define PARA_DOUT0	       		    	410 // 0x0000_019A



#define PARA_FLASH_KEY					499 // 0x0000_01F3
#define PARA_SETTING_PARAMODE			500 // 0x0000_01F4
#define PARA_SETTING_PRINTINFO			508 // 0x0000_01FC
#define PARA_SETTING_PRINTALL			509 // 0x0000_01FD
#define PARA_SETTING_RESET				510 // 0x0000_01FE
#define PARA_SETTING_SAVEALL			511 // 0x0000_01FF
//	default value

////    parameter				                    default     max         min         type            		lock                    sign             	change   					name                                	function
#define PARA_BLANK_DEFAULT						{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_blank,					para_blank}
#define PARA_CTRL_MODE_DEFAULT					{	0,			5,			0,			paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_controlMode,			para_ctrlMode}
#define PARA_SERVO_ON_MODE_DEFAULT              {	0,			2,			0,			paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_servoOnMode,			para_servoOnMode}
#define PARA_CTRL_TYPE_DEFAULT                  {	0,			1,			0,			paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_ctrlType,				para_ctrlType}
#define PARA_DRIVER_NUMBER_DEFAULT    {	DRIVER_NUMBER,			0xFFFFFFFF,	0,			paraType_ro,			para_servo_on_locked,	paraSign_hex,		para_change_immediately,	(char*)paraName_driverInfo,				para_driverNumber}
#define PARA_FIRMWARE_VERSION_DEFAULT {	FIRMWARE_VERSION,		0xFFFFFFFF,	0,			paraType_ro,			para_servo_on_locked,	paraSign_hex,		para_change_immediately,	(char*)paraName_firmwareVer,			para_firmwareVersion}
#define PARA_HOME_ENABLE_DEFAULT                {	0,			1,			0,			paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_homeEnable,				para_homeEnable}
#define PARA_LIMIT_POS_ENABLE_DEFAULT           {	0,			1,			0,			paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_limitPosEna,			para_limitPosEnable}
#define PARA_LIMIT_NEG_ENABLE_DEFAULT           {	0,			1,			0,			paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_limitNegEna,			para_limitNegEnable}
#define PARA_P_KP_DEFAULT                       {	30,			100000,		0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_positionKp,				para_pKp}
#define PARA_P_KD_DEFAULT                       {	0,			100000,		0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_positionKd,				para_pKd}
#define PARA_P_COEFF_DEFAULT					{	0,			100000,		0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_positionCoefficient,	para_pCoefficient}
#define PARA_V_INDEX_DEFAULT                    {	0,		    10,		    0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_speedindex,			para_vindex}
#define PARA_V_KP_DEFAULT                       {	330,		10000,		0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_speedKp,			para_vKp}
#define PARA_V_KI_DEFAULT                       {	350,		1000000,	0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_speedKi,			para_vKi}
#define PARA_V_KP1_DEFAULT                      {	330,		10000,		0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_speedKp1,			para_vKp1}
#define PARA_V_KI1_DEFAULT                      {	350,		1000000,	0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_speedKi1,			para_vKi1}
#define PARA_V_KP2_DEFAULT                      {	330,		10000,		0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_speedKp2,			para_vKp2}
#define PARA_V_KI2_DEFAULT                      {	350,		1000000,	0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_speedKi2,			para_vKi2}
#define PARA_V_KP3_DEFAULT                      {	330,		10000,		0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_speedKp3,			para_vKp3}
#define PARA_V_KI3_DEFAULT                      {	350,		1000000,	0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_speedKi3,			para_vKi3}
#define PARA_V_KP4_DEFAULT                      {	330,		10000,		0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_speedKp4,			para_vKp4}
#define PARA_V_KI4_DEFAULT                      {	350,		1000000,	0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_speedKi4,			para_vKi4}


#define PARA_V_KF_DEFAULT                       {	0,			1000000,	0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_speedKf,				para_vKf}
#define PARA_V_RKF_DEFAULT                      {	0,			1000000,	0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,(char*)paraName_speedRKf,			para_vRKf}
//#define PARA_V_TC_DEFAULT                     {	0,			0,			0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_speedTc,				para_vTc}
#define PARA_I_KP_DEFAULT                       {	63,			10000,		0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_currentKp,				para_iKp}
#define PARA_I_KI_DEFAULT                       {	66,			10000,		0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_currentKi,				para_iKi}
#define PARA_I_BW_DEFAULT                       {	10,			0,			0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_currentBw,				para_iBw}
#define PARA_I_TC_DEFAULT                       {	10,			0,			0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_currentTc,				para_iTc}
#define PARA_P_CMD_DEFAULT                      {	0,			0xFFFFFFFF,	0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_posCmdPara,				para_pCmdPara}
#define PARA_V_CMD_DEFAULT                      {	983040,		2147483647,-2147483648,	paraType_wr,			para_servo_on_unlocked,	paraSign_signed,	para_change_immediately,	(char*)paraName_spdCmdPara,				para_vCmdPara}
#define PARA_V_STEP_DEFAULT                     {	0,			1000,		0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_spdCmdStep,				para_vCmdStep}
#define PARA_V_ACC_DEFAULT					    {	0,			1000,		0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_speedAcc,				para_vCmdAcc}
#define PARA_V_DEC_DEFAULT                      {	0,			1000,		0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_speedDec,				para_vCmdDec}
#define PARA_IQ_CMD_DEFAULT                     {	8000,		10000,		-10000,		paraType_wr,			para_servo_on_unlocked,	paraSign_signed,	para_change_immediately,	(char*)paraName_curIqCmdPara,			para_iqCmdPara}
#define PARA_IQ_STEP_DEFAULT                    {	0,			100,		0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_curIqCmdStep,			para_iqCmdStep}
#define PARA_IQ_THRESHOID_DEFAULT				{	400,		10000,		0,			paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_iqthreshold,			para_iqthreshold}
#define PARA_ID_CMD_DEFAULT                     {	0,			10000,		-10000,		paraType_wr,			para_servo_on_unlocked,	paraSign_signed,	para_change_immediately,	(char*)paraName_curIdCmdPara,			para_idCmdPara}
#define PARA_ID_STEP_DEFAULT                    {	0,			100,		0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_curIdCmdStep,			para_idCmdStep}
#define PARA_ID_HOLD_DEFAULT                    {	800,		5000,	0,		paraType_wr,		para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_curIdCmdHold,			para_idCmdHold}
#define PARA_STATUP_METHOD_DEFAULT        		{	0,			1,			0,			paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_startUpMethod,			para_startUpMethod}
#define PARA_STATUP_START_ANGLE_DEFAULT      	{	0,			360,		0,			paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_startUpStartAngle,		para_startUpStartAngle}
#define PARA_STATUP_MOVE_TIME_DEFAULT        	{	1000,		10000,		0,			paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_startUpMoveTime,		para_startUpMoveTime}
#define PARA_STATUP_CHECK_ANGLE_DEFAULT        	{	90,			360,		0,			paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_startUpCheckAngle,		para_startUpCheckAngle}

#define PARA_LED_MODE_DEFAULT					{	0,			3,			0x00000000,	paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_led_mode,			para_led_mode}
#define PARA_LED_LEVEL_DEFAULT					{	0,			10000,		0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_led_level,			para_led_level}
#define PARA_LED_LEVELMAX_DEFAULT				{	7500,		10000,	    0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_led_levelmax,		para_led_levelmax}

#define PARA_TCURVE_VINIT_DEFAULT        		{	0,			3000000,	0,		paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_tcurveVinit,	para_tcurve_vinit}
#define PARA_TCURVE_VEND_DEFAULT      			{	0,			3000000,	0,		paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_tcurveVend,		para_tcurve_vend}
#define PARA_TCURVE_VMAX_DEFAULT        		{	983040,		3000000,	0,		paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_tcurveVmax,		para_tcurve_vmax}
#define PARA_TCURVE_TACC_DEFAULT        		{	14000,		0x7ffff,	0,		paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_tcurveTacc,		para_tcurve_tacc}
#define PARA_TCURVE_TDEC_DEFAULT        		{	14000,		0x7ffff,	0,		paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_tcurveTdec,		para_tcurve_tdec}

#define PARA_CTRLR_MODE_DEFAULT                 {	0,			10,			0,			paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_ctrlrMode,				para_controllerMode}
#define PARA_CTRLR_HOME_MODE_DEFAULT            {	2,			5,			0,			paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_homeMode,				para_controllerHomeMode}
#define PARA_CTRLR_HOME_SPEED_DEFAULT           {	327680,		2147483647,	0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_homeSpeed,				para_controllerHomeSpeed}
#define PARA_CTRLR_HOME_POS_DEFAULT				{	390000,		2147483647,	-2147483648,	paraType_wr,		para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_homePos,				para_controllerHomePos}
#define PARA_CTRLR_IN_POSITION_RANGE_DEFAULT    {	16,			10000,		0,			paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_inPosRange,				para_controllerInPositionRange}
#define PARA_CTRLR_ZERO_SPEED_RANGE_DEFAULT     {	2200,		10000,		0,			paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_zeroSpdRange,			para_controllerZeroSpeedRange}
#define PARA_CTRLR_SOFT_NEG_LIMIT_ENABLE_DEFAULT {	0,			1,			0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_soft_neg_limit_enable,	para_controllerSoftNegLimitEnable}
#define PARA_CTRLR_SOFT_NEG_LIMIT_DEFAULT    	{	-1,			2147483647,	-2147483648,paraType_wr,			para_servo_on_unlocked,	paraSign_signed,	para_change_immediately,	(char*)paraName_soft_neg_limit,			para_controllerSoftNegLimit}
#define PARA_CTRLR_SOFT_POS_LIMIT_ENABLE_DEFAULT {	0,			1,			0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_soft_pos_limit_enable,	para_controllerSoftPosLimitEnable}
#define PARA_CTRLR_SOFT_POS_LIMIT_DEFAULT     	{	1,			2147483647,	-2147483648,paraType_wr,			para_servo_on_unlocked,	paraSign_signed,	para_change_immediately,	(char*)paraName_soft_pos_limit,			para_controllerSoftPosLimit}
#define PARA_PULSECOMMAND_TYPE_DEFAULT          {	0,			2,			0,			paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_plsCmdType,				para_pulseCommand_type}
#define PARA_PULSECOMMAND_REVERSE_DEFAULT       {	0,			1,			0,			paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_plsCmdRev,				para_pulseCommand_reverse}
#define PARA_ADVCTRL0_ENABLE_DEFAULT			{	0x00000000,	1,			0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl0_enable,		para_advCtrl0_enable}
#define PARA_ADVCTRL0_PARA0_DEFAULT				{	0x00000000,	5,			0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl0_para0,			para_advCtrl0_para0}
#define PARA_ADVCTRL0_PARA1_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl0_para1,			para_advCtrl0_para1}
#define PARA_ADVCTRL0_PARA2_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl0_para2,			para_advCtrl0_para2}
#define PARA_ADVCTRL0_PARA3_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl0_para3,			para_advCtrl0_para3}
#define PARA_ADVCTRL1_ENABLE_DEFAULT			{	0x00000000,	1,			0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl1_enable,		para_advCtrl1_enable}
#define PARA_ADVCTRL1_PARA0_DEFAULT				{	500,		1000,		0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl1_para0,			para_advCtrl1_para0}
#define PARA_ADVCTRL1_PARA1_DEFAULT				{	300,		1000,	   0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl1_para1,			para_advCtrl1_para1}
#define PARA_ADVCTRL1_PARA2_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl1_para2,			para_advCtrl1_para2}
#define PARA_ADVCTRL1_PARA3_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl1_para3,			para_advCtrl1_para3}
#define PARA_ADVCTRL2_ENABLE_DEFAULT			{	0x00000000,	1,			0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl2_enable,		para_advCtrl2_enable}
#define PARA_ADVCTRL2_PARA0_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl2_para0,			para_advCtrl2_para0}
#define PARA_ADVCTRL2_PARA1_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl2_para1,			para_advCtrl2_para1}
#define PARA_ADVCTRL2_PARA2_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl2_para2,			para_advCtrl2_para2}
#define PARA_ADVCTRL2_PARA3_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl2_para3,			para_advCtrl2_para3}
#define PARA_ADVCTRL3_ENABLE_DEFAULT			{	0x00000000,	1,			0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl3_enable,		para_advCtrl3_enable}
#define PARA_ADVCTRL3_PARA0_DEFAULT				{	0x00000000,	0x10000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl3_para0,			para_advCtrl3_para0}
#define PARA_ADVCTRL3_PARA1_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl3_para1,			para_advCtrl3_para1}
#define PARA_ADVCTRL3_PARA2_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl3_para2,			para_advCtrl3_para2}
#define PARA_ADVCTRL3_PARA3_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl3_para3,			para_advCtrl3_para3}
#define PARA_ADVCTRL4_ENABLE_DEFAULT			{	0         ,	1         ,	0x00000000,	paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl4_enable,		para_advCtrl4_enable}
#define PARA_ADVCTRL4_PARA0_DEFAULT				{	0x00000000,	0x10000000,	0x00000000,	paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl4_para0,			para_advCtrl4_para0}
#define PARA_ADVCTRL4_PARA1_DEFAULT				{	0x00000000,	0x10000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl4_para1,			para_advCtrl4_para1}
#define PARA_ADVCTRL4_PARA2_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl4_para2,			para_advCtrl4_para2}
#define PARA_ADVCTRL4_PARA3_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl4_para3,			para_advCtrl4_para3}
#define PARA_ADVCTRL5_ENABLE_DEFAULT			{	0x00000000,	1,			0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl5_enable,		para_advCtrl5_enable}
#define PARA_ADVCTRL5_PARA0_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl5_para0,			para_advCtrl5_para0}
#define PARA_ADVCTRL5_PARA1_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl5_para1,			para_advCtrl5_para1}
#define PARA_ADVCTRL5_PARA2_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl5_para2,			para_advCtrl5_para2}
#define PARA_ADVCTRL5_PARA3_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl5_para3,			para_advCtrl5_para3}
#define PARA_ADVCTRL6_ENABLE_DEFAULT			{	0x00000000,	1,			0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl6_enable,		para_advCtrl6_enable}
#define PARA_ADVCTRL6_PARA0_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl6_para0,			para_advCtrl6_para0}
#define PARA_ADVCTRL6_PARA1_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl6_para1,			para_advCtrl6_para1}
#define PARA_ADVCTRL6_PARA2_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl6_para2,			para_advCtrl6_para2}
#define PARA_ADVCTRL6_PARA3_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl6_para3,			para_advCtrl6_para3}
#define PARA_ADVCTRL7_ENABLE_DEFAULT			{	0x00000000,	1,			0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl7_enable,		para_advCtrl7_enable}
#define PARA_ADVCTRL7_PARA0_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl7_para0,			para_advCtrl7_para0}
#define PARA_ADVCTRL7_PARA1_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl7_para1,			para_advCtrl7_para1}
#define PARA_ADVCTRL7_PARA2_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl7_para2,			para_advCtrl7_para2}
#define PARA_ADVCTRL7_PARA3_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl7_para3,			para_advCtrl7_para3}
#define PARA_ADVCTRL8_ENABLE_DEFAULT			{	0x00000000,	1,			0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl8_enable,		para_advCtrl8_enable}
#define PARA_ADVCTRL8_PARA0_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl8_para0,			para_advCtrl8_para0}
#define PARA_ADVCTRL8_PARA1_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl8_para1,			para_advCtrl8_para1}
#define PARA_ADVCTRL8_PARA2_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl8_para2,			para_advCtrl8_para2}
#define PARA_ADVCTRL8_PARA3_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl8_para3,			para_advCtrl8_para3}
#define PARA_ADVCTRL9_ENABLE_DEFAULT			{	0x00000000,	1,			0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl9_enable,		para_advCtrl9_enable}
#define PARA_ADVCTRL9_PARA0_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl9_para0,			para_advCtrl9_para0}
#define PARA_ADVCTRL9_PARA1_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl9_para1,			para_advCtrl9_para1}
#define PARA_ADVCTRL9_PARA2_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl9_para2,			para_advCtrl9_para2}
#define PARA_ADVCTRL9_PARA3_DEFAULT				{	0x00000000,	0x00000000,	0x00000000,	paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_advCtrl9_para3,			para_advCtrl9_para3}
#define PARA_MOTOR_TYPE_DEFAULT                 {	3,			100,		0,			paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_reboot,			(char*)paraName_motorType,				para_motorType}
#define PARA_ENCODER_TYPE_DEFAULT               {	2,			3,			0,			paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_reboot,			(char*)paraName_encoderType,			para_encoderType}
#define PARA_ENCODER_DIR_DEFAULT                {	0,			1,			0,			paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_reboot,			(char*)paraName_encoderDir,				para_encoderDir}
#define PARA_ENCODER_RESOLUTION_DEFAULT         {	65536,		0xFFFFFFFF,	0,			paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_reboot,			(char*)paraName_encoderResolution,		para_encoderResolution}
#define PARA_ANGLE_OFFSET_DEFAULT               {	0,			10000,		0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_angleOffset,			para_angleOffset}

#define PARA_DOUT0_DEFAULT						{	0,			1,		    0,			paraType_wr,			para_servo_on_unlocked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_dout0,					para_dout0}

#define PARA_FLASHKEY_DEFAULT          			{	1,			8,			0,			paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_flashkey,				para_flashkey}
#define PARA_SETTING_PARAMODE_DEFAULT          	{	0,			8,			0,			paraType_wr,			para_servo_on_locked,	paraSign_unsigned,	para_change_reboot,			(char*)paraName_paraMode,				para_paraMode}
#define PARA_SETTING_PRINTINFO_DEFAULT          {	0,			1,			0,			paraType_w_reserved,	para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_printInfo,				para_printInfo}
#define PARA_SETTING_PRINTALL_DEFAULT           {	0,			1,			0,			paraType_w_reserved,	para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_printAll,				para_printAll}
#define PARA_SETTING_RESET_DEFAULT              {	0,			1,			0,			paraType_w_reserved,	para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_reset,					para_reset}
#define PARA_SETTING_SAVEALL_DEFAULT            {	0,			2,			0,			paraType_w_reserved,	para_servo_on_locked,	paraSign_unsigned,	para_change_immediately,	(char*)paraName_saveAll,				para_saveAll}

#define PR_000_DEFAULT  PARA_CTRL_MODE_DEFAULT
#define PR_001_DEFAULT	PARA_SERVO_ON_MODE_DEFAULT
#define PR_002_DEFAULT	PARA_CTRL_TYPE_DEFAULT
#define PR_003_DEFAULT	PARA_BLANK_DEFAULT
#define PR_004_DEFAULT	PARA_BLANK_DEFAULT
#define PR_005_DEFAULT	PARA_BLANK_DEFAULT
#define PR_006_DEFAULT	PARA_BLANK_DEFAULT
#define PR_007_DEFAULT	PARA_BLANK_DEFAULT
#define PR_008_DEFAULT	PARA_DRIVER_NUMBER_DEFAULT
#define PR_009_DEFAULT	PARA_FIRMWARE_VERSION_DEFAULT
#define PR_010_DEFAULT	PARA_HOME_ENABLE_DEFAULT
#define PR_011_DEFAULT	PARA_LIMIT_POS_ENABLE_DEFAULT
#define PR_012_DEFAULT	PARA_LIMIT_NEG_ENABLE_DEFAULT
#define PR_013_DEFAULT	PARA_BLANK_DEFAULT
#define PR_014_DEFAULT	PARA_BLANK_DEFAULT
#define PR_015_DEFAULT	PARA_BLANK_DEFAULT
#define PR_016_DEFAULT	PARA_BLANK_DEFAULT
#define PR_017_DEFAULT	PARA_BLANK_DEFAULT
#define PR_018_DEFAULT	PARA_BLANK_DEFAULT
#define PR_019_DEFAULT	PARA_BLANK_DEFAULT
#define PR_020_DEFAULT	PARA_P_KP_DEFAULT
#define PR_021_DEFAULT	PARA_P_KD_DEFAULT
#define PR_022_DEFAULT	PARA_P_COEFF_DEFAULT
#define PR_023_DEFAULT	PARA_BLANK_DEFAULT
#define PR_024_DEFAULT	PARA_BLANK_DEFAULT
#define PR_025_DEFAULT	PARA_BLANK_DEFAULT
#define PR_026_DEFAULT	PARA_BLANK_DEFAULT
#define PR_027_DEFAULT	PARA_BLANK_DEFAULT
#define PR_028_DEFAULT	PARA_BLANK_DEFAULT

#define PR_029_DEFAULT	PARA_V_INDEX_DEFAULT
#define PR_030_DEFAULT	PARA_V_KP_DEFAULT
#define PR_031_DEFAULT	PARA_V_KI_DEFAULT
#define PR_032_DEFAULT	PARA_V_KF_DEFAULT
#define PR_033_DEFAULT	PARA_V_RKF_DEFAULT
#define PR_034_DEFAULT	PARA_V_KP2_DEFAULT
#define PR_035_DEFAULT	PARA_V_KI2_DEFAULT
#define PR_036_DEFAULT	PARA_V_KP3_DEFAULT
#define PR_037_DEFAULT	PARA_V_KI3_DEFAULT
#define PR_038_DEFAULT	PARA_V_KP4_DEFAULT
#define PR_039_DEFAULT	PARA_V_KI4_DEFAULT

#define PR_040_DEFAULT	PARA_I_KP_DEFAULT
#define PR_041_DEFAULT	PARA_I_KI_DEFAULT
#define PR_042_DEFAULT	PARA_I_BW_DEFAULT
#define PR_043_DEFAULT	PARA_I_TC_DEFAULT
#define PR_044_DEFAULT	PARA_BLANK_DEFAULT
#define PR_045_DEFAULT	PARA_BLANK_DEFAULT
#define PR_046_DEFAULT	PARA_BLANK_DEFAULT
#define PR_047_DEFAULT	PARA_BLANK_DEFAULT
#define PR_048_DEFAULT	PARA_BLANK_DEFAULT
#define PR_049_DEFAULT	PARA_BLANK_DEFAULT
#define PR_050_DEFAULT	PARA_P_CMD_DEFAULT
#define PR_051_DEFAULT	PARA_BLANK_DEFAULT
#define PR_052_DEFAULT	PARA_BLANK_DEFAULT
#define PR_053_DEFAULT	PARA_BLANK_DEFAULT
#define PR_054_DEFAULT	PARA_BLANK_DEFAULT
#define PR_055_DEFAULT	PARA_BLANK_DEFAULT
#define PR_056_DEFAULT	PARA_BLANK_DEFAULT
#define PR_057_DEFAULT	PARA_BLANK_DEFAULT
#define PR_058_DEFAULT	PARA_BLANK_DEFAULT
#define PR_059_DEFAULT	PARA_BLANK_DEFAULT
#define PR_060_DEFAULT	PARA_V_CMD_DEFAULT
#define PR_061_DEFAULT	PARA_V_STEP_DEFAULT
#define PR_062_DEFAULT	PARA_V_ACC_DEFAULT
#define PR_063_DEFAULT	PARA_V_DEC_DEFAULT
#define PR_064_DEFAULT	PARA_BLANK_DEFAULT
#define PR_065_DEFAULT	PARA_BLANK_DEFAULT
#define PR_066_DEFAULT	PARA_BLANK_DEFAULT
#define PR_067_DEFAULT	PARA_BLANK_DEFAULT
#define PR_068_DEFAULT	PARA_BLANK_DEFAULT
#define PR_069_DEFAULT	PARA_BLANK_DEFAULT
#define PR_070_DEFAULT	PARA_IQ_CMD_DEFAULT
#define PR_071_DEFAULT	PARA_IQ_STEP_DEFAULT
#define PR_072_DEFAULT	PARA_IQ_THRESHOID_DEFAULT
#define PR_073_DEFAULT	PARA_BLANK_DEFAULT
#define PR_074_DEFAULT	PARA_BLANK_DEFAULT
#define PR_075_DEFAULT	PARA_ID_CMD_DEFAULT
#define PR_076_DEFAULT	PARA_ID_STEP_DEFAULT
#define PR_077_DEFAULT	PARA_ID_HOLD_DEFAULT
#define PR_078_DEFAULT	PARA_BLANK_DEFAULT
#define PR_079_DEFAULT	PARA_BLANK_DEFAULT
#define PR_080_DEFAULT	PARA_STATUP_METHOD_DEFAULT
#define PR_081_DEFAULT	PARA_STATUP_START_ANGLE_DEFAULT
#define PR_082_DEFAULT	PARA_STATUP_MOVE_TIME_DEFAULT
#define PR_083_DEFAULT	PARA_STATUP_CHECK_ANGLE_DEFAULT
#define PR_084_DEFAULT	PARA_BLANK_DEFAULT
#define PR_085_DEFAULT	PARA_BLANK_DEFAULT
#define PR_086_DEFAULT	PARA_BLANK_DEFAULT
#define PR_087_DEFAULT	PARA_BLANK_DEFAULT
#define PR_088_DEFAULT	PARA_BLANK_DEFAULT
#define PR_089_DEFAULT	PARA_BLANK_DEFAULT
#define PR_090_DEFAULT	PARA_LED_MODE_DEFAULT
#define PR_091_DEFAULT	PARA_LED_LEVELMAX_DEFAULT
#define PR_092_DEFAULT	PARA_LED_LEVEL_DEFAULT
#define PR_093_DEFAULT	PARA_BLANK_DEFAULT
#define PR_094_DEFAULT	PARA_BLANK_DEFAULT
#define PR_095_DEFAULT	PARA_BLANK_DEFAULT
#define PR_096_DEFAULT	PARA_BLANK_DEFAULT
#define PR_097_DEFAULT	PARA_BLANK_DEFAULT
#define PR_098_DEFAULT	PARA_BLANK_DEFAULT
#define PR_099_DEFAULT	PARA_BLANK_DEFAULT

#define PR_100_DEFAULT	PARA_TCURVE_VINIT_DEFAULT
#define PR_101_DEFAULT	PARA_TCURVE_VEND_DEFAULT
#define PR_102_DEFAULT	PARA_TCURVE_VMAX_DEFAULT
#define PR_103_DEFAULT	PARA_TCURVE_TACC_DEFAULT
#define PR_104_DEFAULT	PARA_TCURVE_TDEC_DEFAULT

#define PR_105_DEFAULT	PARA_BLANK_DEFAULT
#define PR_106_DEFAULT	PARA_BLANK_DEFAULT
#define PR_107_DEFAULT	PARA_BLANK_DEFAULT
#define PR_108_DEFAULT	PARA_BLANK_DEFAULT
#define PR_109_DEFAULT	PARA_BLANK_DEFAULT
#define PR_110_DEFAULT	PARA_BLANK_DEFAULT
#define PR_111_DEFAULT	PARA_BLANK_DEFAULT
#define PR_112_DEFAULT	PARA_BLANK_DEFAULT
#define PR_113_DEFAULT	PARA_BLANK_DEFAULT
#define PR_114_DEFAULT	PARA_BLANK_DEFAULT
#define PR_115_DEFAULT	PARA_BLANK_DEFAULT
#define PR_116_DEFAULT	PARA_BLANK_DEFAULT
#define PR_117_DEFAULT	PARA_BLANK_DEFAULT
#define PR_118_DEFAULT	PARA_BLANK_DEFAULT
#define PR_119_DEFAULT	PARA_BLANK_DEFAULT
#define PR_120_DEFAULT	PARA_BLANK_DEFAULT
#define PR_121_DEFAULT	PARA_BLANK_DEFAULT
#define PR_122_DEFAULT	PARA_BLANK_DEFAULT
#define PR_123_DEFAULT	PARA_BLANK_DEFAULT
#define PR_124_DEFAULT	PARA_BLANK_DEFAULT
#define PR_125_DEFAULT	PARA_BLANK_DEFAULT
#define PR_126_DEFAULT	PARA_BLANK_DEFAULT
#define PR_127_DEFAULT	PARA_BLANK_DEFAULT
#define PR_128_DEFAULT	PARA_BLANK_DEFAULT
#define PR_129_DEFAULT	PARA_BLANK_DEFAULT
#define PR_130_DEFAULT	PARA_BLANK_DEFAULT
#define PR_131_DEFAULT	PARA_BLANK_DEFAULT
#define PR_132_DEFAULT	PARA_BLANK_DEFAULT
#define PR_133_DEFAULT	PARA_BLANK_DEFAULT
#define PR_134_DEFAULT	PARA_BLANK_DEFAULT
#define PR_135_DEFAULT	PARA_BLANK_DEFAULT
#define PR_136_DEFAULT	PARA_BLANK_DEFAULT
#define PR_137_DEFAULT	PARA_BLANK_DEFAULT
#define PR_138_DEFAULT	PARA_BLANK_DEFAULT
#define PR_139_DEFAULT	PARA_BLANK_DEFAULT
#define PR_140_DEFAULT	PARA_BLANK_DEFAULT
#define PR_141_DEFAULT	PARA_BLANK_DEFAULT
#define PR_142_DEFAULT	PARA_BLANK_DEFAULT
#define PR_143_DEFAULT	PARA_BLANK_DEFAULT
#define PR_144_DEFAULT	PARA_BLANK_DEFAULT
#define PR_145_DEFAULT	PARA_BLANK_DEFAULT
#define PR_146_DEFAULT	PARA_BLANK_DEFAULT
#define PR_147_DEFAULT	PARA_BLANK_DEFAULT
#define PR_148_DEFAULT	PARA_BLANK_DEFAULT
#define PR_149_DEFAULT	PARA_BLANK_DEFAULT
#define PR_150_DEFAULT	PARA_BLANK_DEFAULT
#define PR_151_DEFAULT	PARA_BLANK_DEFAULT
#define PR_152_DEFAULT	PARA_BLANK_DEFAULT
#define PR_153_DEFAULT	PARA_BLANK_DEFAULT
#define PR_154_DEFAULT	PARA_BLANK_DEFAULT
#define PR_155_DEFAULT	PARA_BLANK_DEFAULT
#define PR_156_DEFAULT	PARA_BLANK_DEFAULT
#define PR_157_DEFAULT	PARA_BLANK_DEFAULT
#define PR_158_DEFAULT	PARA_BLANK_DEFAULT
#define PR_159_DEFAULT	PARA_BLANK_DEFAULT
#define PR_160_DEFAULT	PARA_BLANK_DEFAULT
#define PR_161_DEFAULT	PARA_BLANK_DEFAULT
#define PR_162_DEFAULT	PARA_BLANK_DEFAULT
#define PR_163_DEFAULT	PARA_BLANK_DEFAULT
#define PR_164_DEFAULT	PARA_BLANK_DEFAULT
#define PR_165_DEFAULT	PARA_BLANK_DEFAULT
#define PR_166_DEFAULT	PARA_BLANK_DEFAULT
#define PR_167_DEFAULT	PARA_BLANK_DEFAULT
#define PR_168_DEFAULT	PARA_BLANK_DEFAULT
#define PR_169_DEFAULT	PARA_BLANK_DEFAULT
#define PR_170_DEFAULT	PARA_BLANK_DEFAULT
#define PR_171_DEFAULT	PARA_BLANK_DEFAULT
#define PR_172_DEFAULT	PARA_BLANK_DEFAULT
#define PR_173_DEFAULT	PARA_BLANK_DEFAULT
#define PR_174_DEFAULT	PARA_BLANK_DEFAULT
#define PR_175_DEFAULT	PARA_BLANK_DEFAULT
#define PR_176_DEFAULT	PARA_BLANK_DEFAULT
#define PR_177_DEFAULT	PARA_BLANK_DEFAULT
#define PR_178_DEFAULT	PARA_BLANK_DEFAULT
#define PR_179_DEFAULT	PARA_BLANK_DEFAULT
#define PR_180_DEFAULT	PARA_BLANK_DEFAULT
#define PR_181_DEFAULT	PARA_BLANK_DEFAULT
#define PR_182_DEFAULT	PARA_BLANK_DEFAULT
#define PR_183_DEFAULT	PARA_BLANK_DEFAULT
#define PR_184_DEFAULT	PARA_BLANK_DEFAULT
#define PR_185_DEFAULT	PARA_BLANK_DEFAULT
#define PR_186_DEFAULT	PARA_BLANK_DEFAULT
#define PR_187_DEFAULT	PARA_BLANK_DEFAULT
#define PR_188_DEFAULT	PARA_BLANK_DEFAULT
#define PR_189_DEFAULT	PARA_BLANK_DEFAULT
#define PR_190_DEFAULT	PARA_BLANK_DEFAULT
#define PR_191_DEFAULT	PARA_BLANK_DEFAULT
#define PR_192_DEFAULT	PARA_BLANK_DEFAULT
#define PR_193_DEFAULT	PARA_BLANK_DEFAULT
#define PR_194_DEFAULT	PARA_BLANK_DEFAULT
#define PR_195_DEFAULT	PARA_BLANK_DEFAULT
#define PR_196_DEFAULT	PARA_BLANK_DEFAULT
#define PR_197_DEFAULT	PARA_BLANK_DEFAULT
#define PR_198_DEFAULT	PARA_BLANK_DEFAULT
#define PR_199_DEFAULT	PARA_BLANK_DEFAULT
#define PR_200_DEFAULT	PARA_BLANK_DEFAULT
#define PR_201_DEFAULT	PARA_BLANK_DEFAULT
#define PR_202_DEFAULT	PARA_BLANK_DEFAULT
#define PR_203_DEFAULT	PARA_BLANK_DEFAULT
#define PR_204_DEFAULT	PARA_BLANK_DEFAULT
#define PR_205_DEFAULT	PARA_BLANK_DEFAULT
#define PR_206_DEFAULT	PARA_BLANK_DEFAULT
#define PR_207_DEFAULT	PARA_BLANK_DEFAULT
#define PR_208_DEFAULT	PARA_BLANK_DEFAULT
#define PR_209_DEFAULT	PARA_BLANK_DEFAULT
#define PR_210_DEFAULT	PARA_BLANK_DEFAULT
#define PR_211_DEFAULT	PARA_BLANK_DEFAULT
#define PR_212_DEFAULT	PARA_BLANK_DEFAULT
#define PR_213_DEFAULT	PARA_BLANK_DEFAULT
#define PR_214_DEFAULT	PARA_BLANK_DEFAULT
#define PR_215_DEFAULT	PARA_BLANK_DEFAULT
#define PR_216_DEFAULT	PARA_BLANK_DEFAULT
#define PR_217_DEFAULT	PARA_BLANK_DEFAULT
#define PR_218_DEFAULT	PARA_BLANK_DEFAULT
#define PR_219_DEFAULT	PARA_BLANK_DEFAULT
#define PR_220_DEFAULT	PARA_BLANK_DEFAULT
#define PR_221_DEFAULT	PARA_BLANK_DEFAULT
#define PR_222_DEFAULT	PARA_BLANK_DEFAULT
#define PR_223_DEFAULT	PARA_BLANK_DEFAULT
#define PR_224_DEFAULT	PARA_BLANK_DEFAULT
#define PR_225_DEFAULT	PARA_BLANK_DEFAULT
#define PR_226_DEFAULT	PARA_BLANK_DEFAULT
#define PR_227_DEFAULT	PARA_BLANK_DEFAULT
#define PR_228_DEFAULT	PARA_BLANK_DEFAULT
#define PR_229_DEFAULT	PARA_BLANK_DEFAULT
#define PR_230_DEFAULT	PARA_BLANK_DEFAULT
#define PR_231_DEFAULT	PARA_BLANK_DEFAULT
#define PR_232_DEFAULT	PARA_BLANK_DEFAULT
#define PR_233_DEFAULT	PARA_BLANK_DEFAULT
#define PR_234_DEFAULT	PARA_BLANK_DEFAULT
#define PR_235_DEFAULT	PARA_BLANK_DEFAULT
#define PR_236_DEFAULT	PARA_BLANK_DEFAULT
#define PR_237_DEFAULT	PARA_BLANK_DEFAULT
#define PR_238_DEFAULT	PARA_BLANK_DEFAULT
#define PR_239_DEFAULT	PARA_BLANK_DEFAULT
#define PR_240_DEFAULT	PARA_BLANK_DEFAULT
#define PR_241_DEFAULT	PARA_BLANK_DEFAULT
#define PR_242_DEFAULT	PARA_BLANK_DEFAULT
#define PR_243_DEFAULT	PARA_BLANK_DEFAULT
#define PR_244_DEFAULT	PARA_BLANK_DEFAULT
#define PR_245_DEFAULT	PARA_BLANK_DEFAULT
#define PR_246_DEFAULT	PARA_BLANK_DEFAULT
#define PR_247_DEFAULT	PARA_BLANK_DEFAULT
#define PR_248_DEFAULT	PARA_BLANK_DEFAULT
#define PR_249_DEFAULT	PARA_BLANK_DEFAULT
#define PR_250_DEFAULT	PARA_BLANK_DEFAULT
#define PR_251_DEFAULT	PARA_BLANK_DEFAULT
#define PR_252_DEFAULT	PARA_BLANK_DEFAULT
#define PR_253_DEFAULT	PARA_BLANK_DEFAULT
#define PR_254_DEFAULT	PARA_BLANK_DEFAULT
#define PR_255_DEFAULT	PARA_BLANK_DEFAULT
#define PR_256_DEFAULT	PARA_BLANK_DEFAULT
#define PR_257_DEFAULT	PARA_BLANK_DEFAULT
#define PR_258_DEFAULT	PARA_BLANK_DEFAULT
#define PR_259_DEFAULT	PARA_BLANK_DEFAULT
#define PR_260_DEFAULT	PARA_BLANK_DEFAULT
#define PR_261_DEFAULT	PARA_BLANK_DEFAULT
#define PR_262_DEFAULT	PARA_BLANK_DEFAULT
#define PR_263_DEFAULT	PARA_BLANK_DEFAULT
#define PR_264_DEFAULT	PARA_BLANK_DEFAULT
#define PR_265_DEFAULT	PARA_BLANK_DEFAULT
#define PR_266_DEFAULT	PARA_BLANK_DEFAULT
#define PR_267_DEFAULT	PARA_BLANK_DEFAULT
#define PR_268_DEFAULT	PARA_BLANK_DEFAULT
#define PR_269_DEFAULT	PARA_BLANK_DEFAULT
#define PR_270_DEFAULT	PARA_BLANK_DEFAULT
#define PR_271_DEFAULT	PARA_BLANK_DEFAULT
#define PR_272_DEFAULT	PARA_BLANK_DEFAULT
#define PR_273_DEFAULT	PARA_BLANK_DEFAULT
#define PR_274_DEFAULT	PARA_BLANK_DEFAULT
#define PR_275_DEFAULT	PARA_BLANK_DEFAULT
#define PR_276_DEFAULT	PARA_BLANK_DEFAULT
#define PR_277_DEFAULT	PARA_BLANK_DEFAULT
#define PR_278_DEFAULT	PARA_BLANK_DEFAULT
#define PR_279_DEFAULT	PARA_BLANK_DEFAULT
#define PR_280_DEFAULT	PARA_BLANK_DEFAULT
#define PR_281_DEFAULT	PARA_BLANK_DEFAULT
#define PR_282_DEFAULT	PARA_BLANK_DEFAULT
#define PR_283_DEFAULT	PARA_BLANK_DEFAULT
#define PR_284_DEFAULT	PARA_BLANK_DEFAULT
#define PR_285_DEFAULT	PARA_BLANK_DEFAULT
#define PR_286_DEFAULT	PARA_BLANK_DEFAULT
#define PR_287_DEFAULT	PARA_BLANK_DEFAULT
#define PR_288_DEFAULT	PARA_BLANK_DEFAULT
#define PR_289_DEFAULT	PARA_BLANK_DEFAULT
#define PR_290_DEFAULT	PARA_BLANK_DEFAULT
#define PR_291_DEFAULT	PARA_BLANK_DEFAULT
#define PR_292_DEFAULT	PARA_BLANK_DEFAULT
#define PR_293_DEFAULT	PARA_BLANK_DEFAULT
#define PR_294_DEFAULT	PARA_BLANK_DEFAULT
#define PR_295_DEFAULT	PARA_BLANK_DEFAULT
#define PR_296_DEFAULT	PARA_BLANK_DEFAULT
#define PR_297_DEFAULT	PARA_BLANK_DEFAULT
#define PR_298_DEFAULT	PARA_BLANK_DEFAULT
#define PR_299_DEFAULT	PARA_BLANK_DEFAULT
#define PR_300_DEFAULT	PARA_CTRLR_MODE_DEFAULT
#define PR_301_DEFAULT	PARA_BLANK_DEFAULT
#define PR_302_DEFAULT	PARA_BLANK_DEFAULT
#define PR_303_DEFAULT	PARA_BLANK_DEFAULT
#define PR_304_DEFAULT	PARA_BLANK_DEFAULT
#define PR_305_DEFAULT	PARA_BLANK_DEFAULT
#define PR_306_DEFAULT	PARA_BLANK_DEFAULT
#define PR_307_DEFAULT	PARA_BLANK_DEFAULT
#define PR_308_DEFAULT	PARA_BLANK_DEFAULT
#define PR_309_DEFAULT	PARA_BLANK_DEFAULT
#define PR_310_DEFAULT	PARA_CTRLR_HOME_MODE_DEFAULT
#define PR_311_DEFAULT	PARA_CTRLR_HOME_SPEED_DEFAULT
#define PR_312_DEFAULT	PARA_CTRLR_HOME_POS_DEFAULT
#define PR_313_DEFAULT	PARA_BLANK_DEFAULT
#define PR_314_DEFAULT	PARA_BLANK_DEFAULT
#define PR_315_DEFAULT	PARA_BLANK_DEFAULT
#define PR_316_DEFAULT	PARA_BLANK_DEFAULT
#define PR_317_DEFAULT	PARA_BLANK_DEFAULT
#define PR_318_DEFAULT	PARA_BLANK_DEFAULT
#define PR_319_DEFAULT	PARA_BLANK_DEFAULT
#define PR_320_DEFAULT	PARA_CTRLR_IN_POSITION_RANGE_DEFAULT
#define PR_321_DEFAULT	PARA_CTRLR_ZERO_SPEED_RANGE_DEFAULT
#define PR_322_DEFAULT	PARA_BLANK_DEFAULT
#define PR_323_DEFAULT	PARA_BLANK_DEFAULT
#define PR_324_DEFAULT	PARA_BLANK_DEFAULT
#define PR_325_DEFAULT	PARA_BLANK_DEFAULT
#define PR_326_DEFAULT	PARA_BLANK_DEFAULT
#define PR_327_DEFAULT	PARA_BLANK_DEFAULT
#define PR_328_DEFAULT	PARA_BLANK_DEFAULT
#define PR_329_DEFAULT	PARA_BLANK_DEFAULT
#define PR_330_DEFAULT	PARA_CTRLR_SOFT_NEG_LIMIT_ENABLE_DEFAULT
#define PR_331_DEFAULT	PARA_CTRLR_SOFT_NEG_LIMIT_DEFAULT
#define PR_332_DEFAULT	PARA_CTRLR_SOFT_POS_LIMIT_ENABLE_DEFAULT
#define PR_333_DEFAULT	PARA_CTRLR_SOFT_POS_LIMIT_DEFAULT
#define PR_334_DEFAULT	PARA_BLANK_DEFAULT
#define PR_335_DEFAULT	PARA_BLANK_DEFAULT
#define PR_336_DEFAULT	PARA_BLANK_DEFAULT
#define PR_337_DEFAULT	PARA_BLANK_DEFAULT
#define PR_338_DEFAULT	PARA_BLANK_DEFAULT
#define PR_339_DEFAULT	PARA_BLANK_DEFAULT
#define PR_340_DEFAULT	PARA_PULSECOMMAND_TYPE_DEFAULT
#define PR_341_DEFAULT	PARA_PULSECOMMAND_REVERSE_DEFAULT
#define PR_342_DEFAULT	PARA_BLANK_DEFAULT
#define PR_343_DEFAULT	PARA_BLANK_DEFAULT
#define PR_344_DEFAULT	PARA_BLANK_DEFAULT
#define PR_345_DEFAULT	PARA_BLANK_DEFAULT
#define PR_346_DEFAULT	PARA_BLANK_DEFAULT
#define PR_347_DEFAULT	PARA_BLANK_DEFAULT
#define PR_348_DEFAULT	PARA_BLANK_DEFAULT
#define PR_349_DEFAULT	PARA_BLANK_DEFAULT
#define PR_350_DEFAULT	PARA_ADVCTRL0_ENABLE_DEFAULT
#define PR_351_DEFAULT	PARA_ADVCTRL0_PARA0_DEFAULT
#define PR_352_DEFAULT	PARA_ADVCTRL0_PARA1_DEFAULT
#define PR_353_DEFAULT	PARA_ADVCTRL0_PARA2_DEFAULT
#define PR_354_DEFAULT	PARA_ADVCTRL0_PARA3_DEFAULT
#define PR_355_DEFAULT	PARA_ADVCTRL1_ENABLE_DEFAULT
#define PR_356_DEFAULT	PARA_ADVCTRL1_PARA0_DEFAULT
#define PR_357_DEFAULT	PARA_ADVCTRL1_PARA1_DEFAULT
#define PR_358_DEFAULT	PARA_ADVCTRL1_PARA2_DEFAULT
#define PR_359_DEFAULT	PARA_ADVCTRL1_PARA3_DEFAULT
#define PR_360_DEFAULT	PARA_ADVCTRL2_ENABLE_DEFAULT
#define PR_361_DEFAULT	PARA_ADVCTRL2_PARA0_DEFAULT
#define PR_362_DEFAULT	PARA_ADVCTRL2_PARA1_DEFAULT
#define PR_363_DEFAULT	PARA_ADVCTRL2_PARA2_DEFAULT
#define PR_364_DEFAULT	PARA_ADVCTRL2_PARA3_DEFAULT
#define PR_365_DEFAULT	PARA_ADVCTRL3_ENABLE_DEFAULT
#define PR_366_DEFAULT	PARA_ADVCTRL3_PARA0_DEFAULT
#define PR_367_DEFAULT	PARA_ADVCTRL3_PARA1_DEFAULT
#define PR_368_DEFAULT	PARA_ADVCTRL3_PARA2_DEFAULT
#define PR_369_DEFAULT	PARA_ADVCTRL3_PARA3_DEFAULT
#define PR_370_DEFAULT	PARA_ADVCTRL4_ENABLE_DEFAULT
#define PR_371_DEFAULT	PARA_ADVCTRL4_PARA0_DEFAULT
#define PR_372_DEFAULT	PARA_ADVCTRL4_PARA1_DEFAULT
#define PR_373_DEFAULT	PARA_ADVCTRL4_PARA2_DEFAULT
#define PR_374_DEFAULT	PARA_ADVCTRL4_PARA3_DEFAULT
#define PR_375_DEFAULT	PARA_ADVCTRL5_ENABLE_DEFAULT
#define PR_376_DEFAULT	PARA_ADVCTRL5_PARA0_DEFAULT
#define PR_377_DEFAULT	PARA_ADVCTRL5_PARA1_DEFAULT
#define PR_378_DEFAULT	PARA_ADVCTRL5_PARA2_DEFAULT
#define PR_379_DEFAULT	PARA_ADVCTRL5_PARA3_DEFAULT
#define PR_380_DEFAULT	PARA_ADVCTRL6_ENABLE_DEFAULT
#define PR_381_DEFAULT	PARA_ADVCTRL6_PARA0_DEFAULT
#define PR_382_DEFAULT	PARA_ADVCTRL6_PARA1_DEFAULT
#define PR_383_DEFAULT	PARA_ADVCTRL6_PARA2_DEFAULT
#define PR_384_DEFAULT	PARA_ADVCTRL6_PARA3_DEFAULT
#define PR_385_DEFAULT	PARA_ADVCTRL7_ENABLE_DEFAULT
#define PR_386_DEFAULT	PARA_ADVCTRL7_PARA0_DEFAULT
#define PR_387_DEFAULT	PARA_ADVCTRL7_PARA1_DEFAULT
#define PR_388_DEFAULT	PARA_ADVCTRL7_PARA2_DEFAULT
#define PR_389_DEFAULT	PARA_ADVCTRL7_PARA3_DEFAULT
#define PR_390_DEFAULT	PARA_ADVCTRL8_ENABLE_DEFAULT
#define PR_391_DEFAULT	PARA_ADVCTRL8_PARA0_DEFAULT
#define PR_392_DEFAULT	PARA_ADVCTRL8_PARA1_DEFAULT
#define PR_393_DEFAULT	PARA_ADVCTRL8_PARA2_DEFAULT
#define PR_394_DEFAULT	PARA_ADVCTRL8_PARA3_DEFAULT
#define PR_395_DEFAULT	PARA_ADVCTRL9_ENABLE_DEFAULT
#define PR_396_DEFAULT	PARA_ADVCTRL9_PARA0_DEFAULT
#define PR_397_DEFAULT	PARA_ADVCTRL9_PARA1_DEFAULT
#define PR_398_DEFAULT	PARA_ADVCTRL9_PARA2_DEFAULT
#define PR_399_DEFAULT	PARA_ADVCTRL9_PARA3_DEFAULT
#define PR_400_DEFAULT	PARA_MOTOR_TYPE_DEFAULT
#define PR_401_DEFAULT	PARA_BLANK_DEFAULT
#define PR_402_DEFAULT	PARA_BLANK_DEFAULT
#define PR_403_DEFAULT	PARA_BLANK_DEFAULT
#define PR_404_DEFAULT	PARA_BLANK_DEFAULT
#define PR_405_DEFAULT	PARA_ENCODER_TYPE_DEFAULT
#define PR_406_DEFAULT	PARA_ENCODER_DIR_DEFAULT
#define PR_407_DEFAULT	PARA_ENCODER_RESOLUTION_DEFAULT
#define PR_408_DEFAULT	PARA_ANGLE_OFFSET_DEFAULT
#define PR_409_DEFAULT	PARA_BLANK_DEFAULT
#define PR_410_DEFAULT	PARA_DOUT0_DEFAULT
#define PR_411_DEFAULT	PARA_BLANK_DEFAULT
#define PR_412_DEFAULT	PARA_BLANK_DEFAULT
#define PR_413_DEFAULT	PARA_BLANK_DEFAULT
#define PR_414_DEFAULT	PARA_BLANK_DEFAULT
#define PR_415_DEFAULT	PARA_BLANK_DEFAULT
#define PR_416_DEFAULT	PARA_BLANK_DEFAULT
#define PR_417_DEFAULT	PARA_BLANK_DEFAULT
#define PR_418_DEFAULT	PARA_BLANK_DEFAULT
#define PR_419_DEFAULT	PARA_BLANK_DEFAULT
#define PR_420_DEFAULT	PARA_BLANK_DEFAULT
#define PR_421_DEFAULT	PARA_BLANK_DEFAULT
#define PR_422_DEFAULT	PARA_BLANK_DEFAULT
#define PR_423_DEFAULT	PARA_BLANK_DEFAULT
#define PR_424_DEFAULT	PARA_BLANK_DEFAULT
#define PR_425_DEFAULT	PARA_BLANK_DEFAULT
#define PR_426_DEFAULT	PARA_BLANK_DEFAULT
#define PR_427_DEFAULT	PARA_BLANK_DEFAULT
#define PR_428_DEFAULT	PARA_BLANK_DEFAULT
#define PR_429_DEFAULT	PARA_BLANK_DEFAULT
#define PR_430_DEFAULT	PARA_BLANK_DEFAULT
#define PR_431_DEFAULT	PARA_BLANK_DEFAULT
#define PR_432_DEFAULT	PARA_BLANK_DEFAULT
#define PR_433_DEFAULT	PARA_BLANK_DEFAULT
#define PR_434_DEFAULT	PARA_BLANK_DEFAULT
#define PR_435_DEFAULT	PARA_BLANK_DEFAULT
#define PR_436_DEFAULT	PARA_BLANK_DEFAULT
#define PR_437_DEFAULT	PARA_BLANK_DEFAULT
#define PR_438_DEFAULT	PARA_BLANK_DEFAULT
#define PR_439_DEFAULT	PARA_BLANK_DEFAULT
#define PR_440_DEFAULT	PARA_BLANK_DEFAULT
#define PR_441_DEFAULT	PARA_BLANK_DEFAULT
#define PR_442_DEFAULT	PARA_BLANK_DEFAULT
#define PR_443_DEFAULT	PARA_BLANK_DEFAULT
#define PR_444_DEFAULT	PARA_BLANK_DEFAULT
#define PR_445_DEFAULT	PARA_BLANK_DEFAULT
#define PR_446_DEFAULT	PARA_BLANK_DEFAULT
#define PR_447_DEFAULT	PARA_BLANK_DEFAULT
#define PR_448_DEFAULT	PARA_BLANK_DEFAULT
#define PR_449_DEFAULT	PARA_BLANK_DEFAULT
#define PR_450_DEFAULT	PARA_BLANK_DEFAULT
#define PR_451_DEFAULT	PARA_BLANK_DEFAULT
#define PR_452_DEFAULT	PARA_BLANK_DEFAULT
#define PR_453_DEFAULT	PARA_BLANK_DEFAULT
#define PR_454_DEFAULT	PARA_BLANK_DEFAULT
#define PR_455_DEFAULT	PARA_BLANK_DEFAULT
#define PR_456_DEFAULT	PARA_BLANK_DEFAULT
#define PR_457_DEFAULT	PARA_BLANK_DEFAULT
#define PR_458_DEFAULT	PARA_BLANK_DEFAULT
#define PR_459_DEFAULT	PARA_BLANK_DEFAULT
#define PR_460_DEFAULT	PARA_BLANK_DEFAULT
#define PR_461_DEFAULT	PARA_BLANK_DEFAULT
#define PR_462_DEFAULT	PARA_BLANK_DEFAULT
#define PR_463_DEFAULT	PARA_BLANK_DEFAULT
#define PR_464_DEFAULT	PARA_BLANK_DEFAULT
#define PR_465_DEFAULT	PARA_BLANK_DEFAULT
#define PR_466_DEFAULT	PARA_BLANK_DEFAULT
#define PR_467_DEFAULT	PARA_BLANK_DEFAULT
#define PR_468_DEFAULT	PARA_BLANK_DEFAULT
#define PR_469_DEFAULT	PARA_BLANK_DEFAULT
#define PR_470_DEFAULT	PARA_BLANK_DEFAULT
#define PR_471_DEFAULT	PARA_BLANK_DEFAULT
#define PR_472_DEFAULT	PARA_BLANK_DEFAULT
#define PR_473_DEFAULT	PARA_BLANK_DEFAULT
#define PR_474_DEFAULT	PARA_BLANK_DEFAULT
#define PR_475_DEFAULT	PARA_BLANK_DEFAULT
#define PR_476_DEFAULT	PARA_BLANK_DEFAULT
#define PR_477_DEFAULT	PARA_BLANK_DEFAULT
#define PR_478_DEFAULT	PARA_BLANK_DEFAULT
#define PR_479_DEFAULT	PARA_BLANK_DEFAULT
#define PR_480_DEFAULT	PARA_BLANK_DEFAULT
#define PR_481_DEFAULT	PARA_BLANK_DEFAULT
#define PR_482_DEFAULT	PARA_BLANK_DEFAULT
#define PR_483_DEFAULT	PARA_BLANK_DEFAULT
#define PR_484_DEFAULT	PARA_BLANK_DEFAULT
#define PR_485_DEFAULT	PARA_BLANK_DEFAULT
#define PR_486_DEFAULT	PARA_BLANK_DEFAULT
#define PR_487_DEFAULT	PARA_BLANK_DEFAULT
#define PR_488_DEFAULT	PARA_BLANK_DEFAULT
#define PR_489_DEFAULT	PARA_BLANK_DEFAULT
#define PR_490_DEFAULT	PARA_BLANK_DEFAULT
#define PR_491_DEFAULT	PARA_BLANK_DEFAULT
#define PR_492_DEFAULT	PARA_BLANK_DEFAULT
#define PR_493_DEFAULT	PARA_BLANK_DEFAULT
#define PR_494_DEFAULT	PARA_BLANK_DEFAULT
#define PR_495_DEFAULT	PARA_BLANK_DEFAULT
#define PR_496_DEFAULT	PARA_BLANK_DEFAULT
#define PR_497_DEFAULT	PARA_BLANK_DEFAULT
#define PR_498_DEFAULT	PARA_BLANK_DEFAULT
#define PR_499_DEFAULT	PARA_FLASHKEY_DEFAULT
#define PR_500_DEFAULT	PARA_SETTING_PARAMODE_DEFAULT
#define PR_501_DEFAULT	PARA_BLANK_DEFAULT
#define PR_502_DEFAULT	PARA_BLANK_DEFAULT
#define PR_503_DEFAULT	PARA_BLANK_DEFAULT
#define PR_504_DEFAULT	PARA_BLANK_DEFAULT
#define PR_505_DEFAULT	PARA_BLANK_DEFAULT
#define PR_506_DEFAULT	PARA_BLANK_DEFAULT
#define PR_507_DEFAULT	PARA_BLANK_DEFAULT
#define PR_508_DEFAULT	PARA_SETTING_PRINTINFO_DEFAULT
#define PR_509_DEFAULT	PARA_SETTING_PRINTALL_DEFAULT
#define PR_510_DEFAULT	PARA_SETTING_RESET_DEFAULT
#define PR_511_DEFAULT	PARA_SETTING_SAVEALL_DEFAULT

#endif // end of file
