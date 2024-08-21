////*****************************************////
//  Name : parameter_info.c
//  Data : 2021/10
//  Version : 0.0
////*****************************************////

#include "parameter.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_printInfo(void)
{
	if(para_valueGet_macro(PARA_SETTING_PRINTINFO) != 1) return;

	device_pwm_pause();

	uint32	data = 0;
	char* cData = "0x123456789";

	PRINTF_withNextLine("DRIVER information.....");

	uint32 dataFirmware0, dataFirmware1, dataFirmware2;

	data = para_valueGet_macro(PARA_FIRMWARE_VERSION);

	dataFirmware0 = (data & 0xF0000000) >> 28;
	dataFirmware1 = (((data >> 4) & 0x00FFFFFF) | 0x20000000);
	dataFirmware2 = data & 0x000F;

	PRINTF("FIRMWARE type : \t\t");
	switch(dataFirmware0)
	{
		case 0 :	PRINTF_withNextLine("three phase motor driver");	break;
		case 1 :	PRINTF_withNextLine("three phase motor driver");	break;
		default :	PRINTF_withNextLine("wrong setting");	break;
	}

	PRINTF("FIRMWARE date : \t\t");
	lib_dataType_uint32ToStringHex(cData, dataFirmware1);
	PRINTF_withNextLine(cData);

	PRINTF("FIRMWARE version : \t");
	lib_dataType_uint32ToStringHex(cData, dataFirmware2);
	PRINTF_withNextLine(cData);

	PRINTF("BOARD number : \t\t");
	lib_dataType_uint32ToStringHex(cData, para_valueGet_macro(PARA_DRIVER_NUMBER));
	PRINTF_withNextLine(cData);

	PRINTF("BOARD adc gain : \t\t");
	lib_dataType_int32ToString(cData, (POWERSTAGE_CURRENT_GAIN * 100));
	PRINTF(cData);
	PRINTF_withNextLine(" / 100");

	PRINTF("PARAMETER mode : \t");
	switch(para_valueGet_macro(PARA_SETTING_PARAMODE))
	{
		case paraMode_normal : 					PRINTF_withNextLine("normal"); break;
		case paraMode_currentTest :				PRINTF_withNextLine("current test"); break;
		case paraMode_currentResponseTest : 	PRINTF_withNextLine("current response test"); break;
		case paraMode_angleTest : 				PRINTF_withNextLine("angle test"); break;
		case paraMode_speedLoopTest : 			PRINTF_withNextLine("speed loop test"); break;
		case paraMode_positionLoopTest : 		PRINTF_withNextLine("position Loop test"); break;
		case paraMode_autoFocusSystemDefault : 	PRINTF_withNextLine("afs default"); break;
		case paraMode_pulseDirDefault :			PRINTF_withNextLine("PulseDir default"); break;
		case paraMode_nosewheelDefault:			PRINTF_withNextLine("paraMode_nosewheelDefault"); break;
		default : 								PRINTF_withNextLine("wrong setting"); break;
	}

	PRINTF("PARAMETER state : \t");
	if(para_paraServoOnLockGet_macro())
	{
		PRINTF_withNextLine("system parameter change, need to reboot system");
	}
	else
	{
		PRINTF_withNextLine("normal");
	}

	PRINTF("PARAMETER change : \t");
	if(para_paraChangeFlagGet_macro())
	{
		PRINTF_withNextLine("parameter have been changed in ram");
	}
	else
	{
		PRINTF_withNextLine("no");
	}

	PRINTF("PARAMETER update : \t");
	if(para_paraUpdateFlagGet_macro())
	{
		PRINTF_withNextLine("parameter have been updated to flash");
	}
	else
	{
		PRINTF_withNextLine("no");
	}

	PRINTF("MOTOR type : \t\t");
	switch(para_valueGet_macro(PARA_MOTOR_TYPE))
	{
		case MOTOR_DEFAULT : 				PRINTF_withNextLine("unknown"); break;
		case MOTOR_MDLV_3M68 :				PRINTF_withNextLine("3M68"); break;
		case MOTOR_SUMFU_17NE34BF3_300 : 	PRINTF_withNextLine("SUMFU_17NE34BF3_300"); break;
		case MOTOR_SM_1P2D50P500R4P6A : 	PRINTF_withNextLine("SM_1P2D50P500R4P6A"); break;
		case MOTOR_SUMFU_ML1513 : 			PRINTF_withNextLine("SUMFU_ML1513"); break;
		case MOTOR_GHC_S160D : 				PRINTF_withNextLine("GHC_S160D"); break;
		default : 							PRINTF_withNextLine("wrong setting"); break;
	}

	PRINTF("ENCODER resolution : \t");
	lib_dataType_int32ToString(cData, para_valueGet_macro(PARA_ENCODER_RESOLUTION));
	PRINTF_withNextLine(cData);

	PRINTF("ENCODER direction : \t");
	switch(para_valueGet_macro(PARA_ENCODER_DIR))
	{
		case ENCODER_DIR_CCW : 	PRINTF_withNextLine("ccw"); break;
		case ENCODER_DIR_CW :	PRINTF_withNextLine("cw"); break;
		default : 				PRINTF_withNextLine("wrong setting"); break;
	}

	PRINTF("ENCODER angle close : \t");
	switch(para_valueGet_macro(PARA_ENCODER_TYPE))
	{
		case ENCODER_TYPE_INC :						 	PRINTF_withNextLine("index close mode"); break;
		case ENCODER_TYPE_INC_ZERO_START :
			PRINTF("zero angle slow close mode : startup form angle ");
			lib_dataType_int32ToString(cData, para_valueGet_macro(PARA_STATUP_START_ANGLE));
			PRINTF(cData);
			PRINTF(" degree and check angle around ");
			lib_dataType_int32ToString(cData, para_valueGet_macro(PARA_STATUP_CHECK_ANGLE));
			PRINTF(cData);
			PRINTF(" degree with move time ");
			lib_dataType_int32ToString(cData, para_valueGet_macro(PARA_STATUP_MOVE_TIME));
			PRINTF(cData);
			PRINTF_withNextLine(" ms");
		break;
		case ENCODER_TYPE_INC_ZERO_ANGLE_SLOW_START: 	PRINTF_withNextLine("zero angle slow close mode"); break;
		default : 										PRINTF_withNextLine("index close mode"); break;
	}

	PRINTF("CONTROLLER mode: \t");
	switch(para_valueGet_macro(PARA_CTRLR_MODE))
	{
		case CTRLR_MODE_UART :	PRINTF_withNextLine("uart mode"); break;
		case CTRLR_MODE_SPI :	PRINTF_withNextLine("spi mode"); break;

		default : 				PRINTF_withNextLine("wrong setting"); break;
	}

	PRINTF("CONTROLLER servo on: \t");
	switch(para_valueGet_macro(PARA_SERVO_ON_MODE))
	{
		case SERVO_ON_MODE_CTLR :	PRINTF_withNextLine("controller"); break;
		case SERVO_ON_MODE_IO :	PRINTF_withNextLine("digital input"); break;
		case SERVO_ON_MODE_SW :	PRINTF_withNextLine("switch"); break;
		default : 				PRINTF_withNextLine("wrong setting"); break;
	}

	PRINTF("HOME mode: \t\t");
	switch(para_valueGet_macro(PARA_CTRLR_HOME_MODE))
	{
		case positive_noIndex :			PRINTF("positive no Index"); break;
		case negative_noIndex :			PRINTF("negative no Index"); break;
		case home_noIndex :				PRINTF("home no Index"); break;
		case home_noIndex_positive :	PRINTF("home no Index positive"); break;
		case only_negative:				PRINTF("only_negative"); break;
		case home_disable :				PRINTF("home disable"); break;
		default : 						PRINTF("wrong setting"); break;
	}

	if((para_valueGet_macro(PARA_CTRLR_HOME_MODE)) != home_disable)
	{
		PRINTF(" with speed ");
		lib_dataType_int32ToString(cData, (para_valueGet_macro(PARA_CTRLR_HOME_SPEED)));
		PRINTF(cData);
		PRINTF_withNextLine(" pulse / s");
	}
	else
	{
		PRINTF_withNextLine(" ");
	}

	if((para_valueGet_macro(PARA_CTRLR_SOFT_NEG_LIMIT_ENABLE)) == 1)
	{
		PRINTF("software negative limit :");
		lib_dataType_int32ToString(cData, (para_valueGet_macro(PARA_CTRLR_SOFT_NEG_LIMIT)));
		PRINTF_withNextLine(cData);
	}

	if((para_valueGet_macro(PARA_CTRLR_SOFT_POS_LIMIT_ENABLE)) == 1)
	{
		PRINTF("software positive limit :");
		lib_dataType_int32ToString(cData, (para_valueGet_macro(PARA_CTRLR_SOFT_POS_LIMIT)));
		PRINTF_withNextLine(cData);
	}


	PRINTF("COMMAND speed : \t");
	lib_dataType_int32ToString(cData, (para_valueGet_macro(PARA_V_CMD) * 60 / mPara_ulEncoderMaxPulseGet_macro()));
	PRINTF_withNextLine(cData);

	PRINTF("COMMAND IQ command: \t");
	lib_dataType_int32ToString(cData, para_valueGet_macro(PARA_IQ_CMD));
	PRINTF(cData);
	PRINTF_withNextLine(" / 10000");

	PRINTF("COMMAND ID command: \t");
	lib_dataType_int32ToString(cData, para_valueGet_macro(PARA_ID_CMD));
	PRINTF(cData);
	PRINTF_withNextLine(" / 10000");

	PRINTF("GAIN position KP: \t");
	lib_dataType_int32ToString(cData, para_valueGet_macro(PARA_P_KP));
	PRINTF(cData);
	PRINTF_withNextLine(" / 100000");

	PRINTF("GAIN speed KP: \t\t");
	lib_dataType_int32ToString(cData, para_valueGet_macro(PARA_V_KP));
	PRINTF(cData);
	PRINTF_withNextLine(" / 100");

	PRINTF("GAIN speed KI: \t\t");
	lib_dataType_int32ToString(cData, para_valueGet_macro(PARA_V_KI));
	PRINTF(cData);
	PRINTF_withNextLine(" / 100000");

	/*PRINTF("GAIN speed KF: \t\t");
	lib_dataType_int32ToString(cData, para_valueGet_macro(PARA_V_KF));
	PRINTF(cData);
	PRINTF_withNextLine(" / 1000");
	 */
	PRINTF("GAIN current KP: \t\t");
	lib_dataType_int32ToString(cData, para_valueGet_macro(PARA_I_KP));
	PRINTF(cData);
	PRINTF_withNextLine(" / 100");

	PRINTF("GAIN current KI: \t\t");
	lib_dataType_int32ToString(cData, para_valueGet_macro(PARA_I_KI));
	PRINTF(cData);
	PRINTF_withNextLine(" / 100");


	PRINTF("SWITCH home: \t\t");
	if(para_valueGet_macro(PARA_HOME_ENABLE) == HOME_LIMIT_DISABLE)
		PRINTF_withNextLine("disable");
	else
		PRINTF_withNextLine("enable");

	PRINTF("SWITCH positive limit: \t");
	if(para_valueGet_macro(PARA_LIMIT_POS_ENABLE) == POSITIVE_LIMIT_DISABLE)
		PRINTF_withNextLine("disable");
	else
		PRINTF_withNextLine("enable");

	PRINTF("SWITCH negative limit: \t");
	if(para_valueGet_macro(PARA_LIMIT_NEG_ENABLE) == NEGATIVE_LIMIT_DISABLE)
		PRINTF_withNextLine("disable");
	else
		PRINTF_withNextLine("enable");





	PRINTF("ADVANCE holding current: \t");
	lib_dataType_int32ToString(cData, para_valueGet_macro(PARA_ID_HOLD));
	PRINTF(cData);
	PRINTF_withNextLine(" / 10000");

	if(para_valueGet_macro(PARA_ADVCTRL0_ENABLE) == 1)
	{
		PRINTF_withNextLine("ADVANCE command smooth function enable");

		PRINTF("\t command smooth average times : \t");
		lib_dataType_int32ToString(cData, para_valueGet_macro(PARA_ADVCTRL0_PARA0));
		PRINTF_withNextLine(cData);

	}
	if(para_valueGet_macro(PARA_ADVCTRL1_ENABLE) == 1)
	{
		PRINTF_withNextLine("ADVANCE command angle hold function enable");

		PRINTF("\t ADVANCE command angle hold range rate of in position : \t");
		lib_dataType_int32ToString(cData, para_valueGet_macro(PARA_ADVCTRL1_PARA0));
		PRINTF(cData);
		PRINTF_withNextLine(" / 1000");

		PRINTF("\t ADVANCE command and angle hold wait time : \t\t");
		lib_dataType_int32ToString(cData, para_valueGet_macro(PARA_ADVCTRL1_PARA1));
		PRINTF(cData);
		PRINTF_withNextLine(" / 40K (s)");
	}
	if(para_valueGet_macro(PARA_ADVCTRL2_ENABLE) == 1)
	{
		PRINTF_withNextLine("ADVANCE field weakening function enable");
	}

	PRINTF_withNextLine(".....end of driver information");

	if(mDrv_mDrvAdjustFlagGet_macro() == true)
	{
		device_pwm_run();
	}
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void para_printAll(void)
{
	if(para_valueGet_macro(PARA_SETTING_PRINTALL) != 1) return;

	uint32 ulParaCnt;

	device_pwm_pause();

	PRINTF_nextLine();
	PRINTF("parameter list loading.");
	PRINTF_nextLine();
	PRINTF("parameter list loading..");
	PRINTF_nextLine();
	PRINTF("parameter list loading...");
	PRINTF_nextLine();
	PRINTF_nextLine();

	for(ulParaCnt = 0; ulParaCnt < MAX_PARAMETER; ulParaCnt++)
	{
		char* cDataPara = "";
		char* cData = "0x123456789";

		cDataPara = para_nameGet_macro(ulParaCnt);

		if(*cDataPara == '0')
		{
			continue;
		}

		cData = malloc(sizeof(char) * 4);
		*(cData + 0) = '0';
		*(cData + 1) = '0';
		*(cData + 2) = '0';
		*(cData + 3) = 0;

		lib_dataType_int32ToString(cData,ulParaCnt);

		if(ulParaCnt < 10)
		{
			*(cData + 2) = *(cData);
			*(cData + 1) = '0';
			*(cData + 0) = '0';
		}
		else if(ulParaCnt < 100)
		{
			*(cData + 2) = *(cData + 1);
			*(cData + 1) = *(cData);
			*(cData + 0) = '0';
		}


		PRINTF("Pr-");
		PRINTF(cData);
		PRINTF(": ");
		PRINTF(cDataPara);
		PRINTF_nextLine();

		if(para_signGet_macro(ulParaCnt) == paraSign_signed)
		{
			PRINTF("Value: ");
			lib_dataType_int32ToString(cData, para_valueGet_macro(ulParaCnt));
			PRINTF(cData);
			PRINTF_nextLine();
			PRINTF("Max: ");
			lib_dataType_int32ToString(cData, para_valueMaxGet_macro(ulParaCnt));
			PRINTF(cData);
			PRINTF("\t");
			PRINTF("Min: ");
			lib_dataType_int32ToString(cData, para_valueMinGet_macro(ulParaCnt));
			PRINTF(cData);
			PRINTF_nextLine();
		}
		else if(para_signGet_macro(ulParaCnt) == paraSign_hex)
		{
			PRINTF("Value: 0x");
			lib_dataType_uint32ToStringHex(cData, para_valueGet_macro(ulParaCnt));
			PRINTF(cData);
			PRINTF_nextLine();
			PRINTF("Max: 0x");
			lib_dataType_uint32ToStringHex(cData, para_valueMaxGet_macro(ulParaCnt));
			PRINTF(cData);
			PRINTF("\t");
			PRINTF("Min: 0x");
			lib_dataType_uint32ToStringHex(cData, para_valueMinGet_macro(ulParaCnt));
			PRINTF(cData);
			PRINTF_nextLine();
		}
		else
		{
			PRINTF("Value: ");
			lib_dataType_uint32ToString(cData, para_valueGet_macro(ulParaCnt));
			PRINTF(cData);
			PRINTF_nextLine();
			PRINTF("Max: ");
			lib_dataType_uint32ToString(cData, para_valueMaxGet_macro(ulParaCnt));
			PRINTF(cData);
			PRINTF("\t");
			PRINTF("Min: ");
			lib_dataType_uint32ToString(cData, para_valueMinGet_macro(ulParaCnt));
			PRINTF(cData);
			PRINTF_nextLine();
		}

		PRINTF("DataSign: ");
		if(para_signGet_macro(ulParaCnt) == paraSign_signed)
		{
			PRINTF("Signed data");
		}
		else if(para_signGet_macro(ulParaCnt) == paraSign_hex)
		{
			PRINTF("Hex data");
		}
		else
		{
			PRINTF("UnSigned data");
		}
		PRINTF_nextLine();
		PRINTF("ParaType: ");
		if(para_typeGet_macro(ulParaCnt) == paraType_wr)
		{
			PRINTF("Write and read");
		}
		else if(para_typeGet_macro(ulParaCnt) == paraType_ro)
		{
			PRINTF("Read only");
		}
		else
		{
			PRINTF("Write reserved");
		}
		PRINTF_nextLine();
		PRINTF("Lock: ");
		if(para_lockGet_macro(ulParaCnt) == para_servo_on_locked)
		{
			PRINTF("Servo on lock");
		}
		else
		{
			PRINTF("Servo on unlock");
		}
		PRINTF_nextLine();
		PRINTF("Change: ");
		if(para_changeGet_macro(ulParaCnt) == para_change_immediately)
		{
			PRINTF("Change immediately");
		}
		else
		{
			PRINTF("Change with reboot");
		}
		PRINTF_nextLine();
		PRINTF_nextLine();
	}

	PRINTF("end of parameter list");
	PRINTF_nextLine();

	if(mDrv_mDrvAdjustFlagGet_macro() == true)
	{
		device_pwm_run();
	}
}
