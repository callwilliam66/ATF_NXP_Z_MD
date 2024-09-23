////*****************************************////
//  Name : drv_board_ext.h
//  Data : 2021/01
//  Version : 0.0
////*****************************************////

#ifndef _DRV_BOARD_EXT_H_
#define _DRV_BOARD_EXT_H_

#include "drv.h"

// driver setting
#define DRIVER_B2000647 			0xB2000647
#define DRIVER_B2100703_B2100704	0xB2100703

#define DRIVER_NUMBER	DRIVER_B2100703_B2100704

// hardware setting
#if DRIVER_NUMBER == DRIVER_B2000647
	#define POWERSTAGE_CURRENT_SENSOR_MAX 	37.5F
	#define POWERSTAGE_CURRENT_GAIN 		-1.0F
	#define POWERSTAGE_VOLTAGE_RES_GAIN 	6.8F / 106.8F
	#define ADC_VOLTAGE 					3.3F
	#define OVER_VOLTAGE 					28.0F
	#define UNDER_VOLTAGE 					20.0F
	#define NORMAL_VOLTAGE 					24.0F
	#define MOTOR_CURRENTOVER 				7.5F
	#define DRIVER_ADC_RESOLUTION 			4096.0F
	#define DRIVER_OV_PARAMETER 			370.0F
	#define POWERSTAGE_CURRENT_ADC_MAX 		POWERSTAGE_CURRENT_SENSOR_MAX / POWERSTAGE_CURRENT_GAIN
	#define MOTOR_CURRENT_GAIN 				(POWERSTAGE_CURRENT_ADC_MAX / (DRIVER_ADC_RESOLUTION / 2.0F))
	#define BUS_VOLTAGE_GAIN 				(1.0F / DRIVER_ADC_RESOLUTION * ADC_VOLTAGE * POWERSTAGE_VOLTAGE_RES_GAIN)
	#define TEMP_MAX		 				ADC_VOLTAGE
	#define TEMP_LIMIT		 				1.3F
#endif

#if DRIVER_NUMBER == DRIVER_B2100703_B2100704
	#define POWERSTAGE_CURRENT_SENSOR_MAX 	33.0F
	#define POWERSTAGE_CURRENT_GAIN 		-2.35F
	#define ADC_VOLTAGE 					3.3F
	#define OVER_VOLTAGE 					28.0F
	#define UNDER_VOLTAGE 					18.0F
	#define NORMAL_VOLTAGE 					24.0F
	#define MOTOR_CURRENTOVER 				7.5F
	#define DRIVER_ADC_RESOLUTION 			4096.0F
	#define DRIVER_OV_PARAMETER 			(3.3F /3.0F * (30.0F + 3.0F))	// ADC MAX BUS VOLTAGE VALUE
	#define POWERSTAGE_CURRENT_ADC_MAX 		POWERSTAGE_CURRENT_SENSOR_MAX / POWERSTAGE_CURRENT_GAIN
	#define MOTOR_CURRENT_GAIN 				(POWERSTAGE_CURRENT_ADC_MAX / (DRIVER_ADC_RESOLUTION / 2.0F))
	#define BUS_VOLTAGE_GAIN 				(1.0F / DRIVER_ADC_RESOLUTION)
	#define LED_OV_PARAMETER                BUS_VOLTAGE_GAIN  * 3.3F * (10.0F + 1.0F) / 1.0F	// LED_ADCGAIN
	#define TEMP_MAX 						ADC_VOLTAGE
	#define TEMP_LIMIT		 				1.4F
#endif

typedef struct
{
	uint16 data:14;
	uint16 rw:1;
	uint16 Header:1;
}ENCODER_SPI;

typedef union
{
	ENCODER_SPI spiData;
	uuint16		ucData;
	uint16		all;
}ENCODER_DATA;

typedef struct
{
    uint32  ulch;
    uint32  ulmode;
}DI_STATUS;

typedef struct
{
    DI_STATUS Emg;
    DI_STATUS Servo_On;
    DI_STATUS Home;
    DI_STATUS Negative_Limit;
    DI_STATUS Positive_Limit;

}BOARD_DI_REGS;

// define
//// PWM
#define PWM_ENABLE	true // pwm  module enable
#define PWM_DISABLE	false // pwm  module disable

//// encoder
#define ENCODER_DIR_CCW	0
#define ENCODER_DIR_CW 	1

#define ENCODER_ENABLE	1 // encoder module enable
#define ENCODER_DISABLE	0 // encoder module disable

//// pulse command
#define PULSE_COMMAND_TYPE_PULSE_DIR 0
#define PULSE_COMMAND_TYPE_CW_CCW	 1
#define PULSE_COMMAND_TYPE_AB		 2

//// dac
#define DAC_CH0 0 // dac channel 0
#define DAC_CH1 1 // dac channel 1
#define DAC_CH2 2 // dac channel 2
#define DAC_CH3 3 // dac channel 3

// define setting
#define ENCODER_ANGLE_PERIPHERAL	ENC1_PERIPHERAL // angle encoder peripheral
#define ENCODER_POSITION_PERIPHERAL ENC2_PERIPHERAL // position encoder peripheral
//#define ENCODER_SPI_PERIPHERAL		LPSPI1_PERIPHERAL // position encoder peripheral
//#define ENCODER_CS 					kLPSPI_MasterPcs1 // encoder cs

//#define DAC_PERIPHERAL LPSPI4_PERIPHERAL // dac peripheral
//#define DAC_CS 	kLPSPI_MasterPcs0 // dac cs

// extern function
extern void drv_board_init(void);

//// pwm
extern void board_pwm_outputEnableSet(boolen bEnable);

//// encoder
extern void board_encoder_enableSet(boolen bEnable);
extern void board_encoder_config(uint32 angleCloseMode, boolen bMotorPhaseDir, boolen bEncoderDir);
extern void board_encoder_sendRequest(uint32 rw,uint32 addr);
extern uint32 board_encoder_readData(void);

//// pulse command
extern void board_pulseCommand_config(uint32 uiType,boolen bReverse);
extern uint32 board_pulseCommand_cmdGet(uint16 uiMode);

//// dac
extern void board_dac_dataUpdate(uint32 ulDacChannel,uint32 ulData);

// macro
//// MCU  boot io
#define board_boot0_read_macro() GPIO_PinRead(BOARD_INITPINS_MCU_BOOT0_GPIO,BOARD_INITPINS_MCU_BOOT0_GPIO_PIN)
#define board_boot1_read_macro() GPIO_PinRead(BOARD_INITPINS_MCU_BOOT1_GPIO,BOARD_INITPINS_MCU_BOOT1_GPIO_PIN)

//// LED
#define board_led_g_off_macro() GPIO_PortSet(BOARD_INITPINS_LED_G_GPIO,BOARD_INITPINS_LED_G_GPIO_PIN_MASK )
#define board_led_r_off_macro() GPIO_PortSet(BOARD_INITPINS_LED_RED_GPIO,BOARD_INITPINS_LED_RED_GPIO_PIN_MASK)

#define board_led_g_on_macro() GPIO_PortClear(BOARD_INITPINS_LED_G_GPIO,BOARD_INITPINS_LED_G_GPIO_PIN_MASK )
#define board_led_r_on_macro() GPIO_PortClear(BOARD_INITPINS_LED_RED_GPIO,BOARD_INITPINS_LED_RED_GPIO_PIN_MASK)

#define board_led_g_toggle_macro() GPIO_PortToggle(BOARD_INITPINS_LED_G_GPIO,BOARD_INITPINS_LED_G_GPIO_PIN_MASK )
#define board_led_r_toggle_macro() GPIO_PortToggle(BOARD_INITPINS_LED_RED_GPIO,BOARD_INITPINS_LED_RED_GPIO_PIN_MASK)

//LED_DRIVER
#define lightdriver_on 		GPIO_PortSet(BOARD_INITPINS_LD_ENABLE_GPIO ,BOARD_INITPINS_LD_ENABLE_GPIO_PIN_MASK )
#define lightdriver_off 	GPIO_PortClear(BOARD_INITPINS_LD_ENABLE_GPIO ,BOARD_INITPINS_LD_ENABLE_GPIO_PIN_MASK)

#define lightsink_on 		GPIO_PortSet(BOARD_INITPINS_LD_STB_GPIO ,BOARD_INITPINS_LD_STB_GPIO_PIN_MASK )
#define lightsink_off 		GPIO_PortClear(BOARD_INITPINS_LD_STB_GPIO ,BOARD_INITPINS_LD_STB_GPIO_PIN_MASK)

//// ADC
#define board_cur_u_read_macro() ADC_ETC_GetADCConversionValue(ADC_ETC_PERIPHERAL, ADC_ETC_TC_0_TG,0U)
#define board_cur_v_read_macro() 0
#define board_cur_w_read_macro() ADC_ETC_GetADCConversionValue(ADC_ETC_PERIPHERAL, ADC_ETC_TC_1_TG,0U)
#define board_volt_bus_read_macro() ADC_ETC_GetADCConversionValue(ADC_ETC_PERIPHERAL, ADC_ETC_TC_0_TG,1U)
#define board_temp_read_macro() ADC_ETC_GetADCConversionValue(ADC_ETC_PERIPHERAL, ADC_ETC_TC_0_TG,2U)
#define board_ldvo_read_macro() ADC_ETC_GetADCConversionValue(ADC_ETC_PERIPHERAL, ADC_ETC_TC_1_TG,1U)

//// DI
#define board_DI0_read_macro() (((BOARD_INITPINS_DIN_0_GPIO->DR) >> (BOARD_INITPINS_DIN_0_GPIO_PIN)) & 0x1U)
#define board_DI1_read_macro() (((BOARD_INITPINS_DIN_1_GPIO->DR) >> (BOARD_INITPINS_DIN_1_GPIO_PIN)) & 0x1U)
#define board_DI2_read_macro() (((BOARD_INITPINS_DIN_2_GPIO->DR) >> (BOARD_INITPINS_DIN_2_GPIO_PIN)) & 0x1U)
#define board_DIA_read_macro() (((BOARD_INITPINS_DI_A_GPIO->DR) >> (BOARD_INITPINS_DI_A_GPIO_PIN)) & 0x1U)

////DO
#define board_DOUT0_on_macro()  GPIO_PortSet(BOARD_INITPINS_DO_0_GPIO ,BOARD_INITPINS_DO_0_GPIO_PIN_MASK)
#define board_DOUT0_off_macro() GPIO_PortClear(BOARD_INITPINS_DO_0_GPIO ,BOARD_INITPINS_DO_0_GPIO_PIN_MASK)
#define board_DOUT0_toggle_macro() GPIO_PortToggle(BOARD_INITPINS_DO_0_GPIO ,BOARD_INITPINS_DO_0_GPIO_PIN_MASK)
#define board_DOUT0_set_macro(data) if(data == 0U) { BOARD_INITPINS_DO_0_GPIO->DR &= ~(1UL << BOARD_INITPINS_DO_0_GPIO_PIN); }else {BOARD_INITPINS_DO_0_GPIO->DR |= (1UL << BOARD_INITPINS_DO_0_GPIO_PIN);}

//INNER IO
#define board_HSIO5_read_macro()   ((( BOARD_INITPINS_HSIO5_GPIO->DR) >> (BOARD_INITPINS_HSIO5_GPIO_PIN )) & 0x1U)
#define board_HSIO1_on_macro()   GPIO_PortSet(BOARD_INITPINS_HSIO1_GPIO,BOARD_INITPINS_HSIO1_GPIO_PIN_MASK)
#define board_HSIO1_off_macro()  GPIO_PortClear(BOARD_INITPINS_HSIO1_GPIO,BOARD_INITPINS_HSIO1_GPIO_PIN_MASK )

#define board_HSIO2_on_macro()   GPIO_PortSet(BOARD_INITPINS_HSIO2_GPIO,BOARD_INITPINS_HSIO2_GPIO_PIN_MASK)
#define board_HSIO2_off_macro()  GPIO_PortClear(BOARD_INITPINS_HSIO2_GPIO,BOARD_INITPINS_HSIO2_GPIO_PIN_MASK )

#define board_HSIO3_on_macro()   GPIO_PortSet(BOARD_INITPINS_HSIO3_GPIO,BOARD_INITPINS_HSIO3_GPIO_PIN_MASK)
#define board_HSIO3_off_macro()  GPIO_PortClear(BOARD_INITPINS_HSIO3_GPIO,BOARD_INITPINS_HSIO3_GPIO_PIN_MASK )


#define board_HSIO5_on_macro()   GPIO_PortSet(BOARD_INITPINS_HSIO5_GPIO,BOARD_INITPINS_HSIO5_GPIO_PIN_MASK)
#define board_HSIO5_off_macro()  GPIO_PortClear(BOARD_INITPINS_HSIO5_GPIO,BOARD_INITPINS_HSIO5_GPIO_PIN_MASK)

//// ENCODER
#define board_encoder_angle_read_macro() ENC_GetHoldPositionValue(ENC1_PERIPHERAL)
#define board_encoder_index_happened_read_macro() (((ENC_GetStatusFlags(ENC1_PERIPHERAL) & kENC_INDEXPulseFlag) == kENC_INDEXPulseFlag) ? true : false)
#define board_encoder_index_happened_clear_macro() ENC_ClearStatusFlags(ENC1_PERIPHERAL,kENC_INDEXPulseFlag)

#define board_encoder_position_read_macro() ENC_GetHoldPositionValue(ENC2_PERIPHERAL)

#define board_encoder_power_enable_macro() GPIO_PortSet(BOARD_INITPINS_ENC_EN_GPIO,BOARD_INITPINS_ENC_EN_GPIO_PIN_MASK)
#define board_encoder_power_disable_macro() GPIO_PortClear(BOARD_INITPINS_ENC_EN_GPIO,BOARD_INITPINS_ENC_EN_GPIO_PIN_MASK)

/// LDIO
#define board_ld_stb_macro() GPIO_PortSet(BOARD_INITPINS_LD_STB_GPIO_PIN,BOARD_INITPINS_LD_STB_GPIO_PIN_MASK )
#define board_ld_en_macro() GPIO_PortSet(BOARD_INITPINS_LD_ENABLE_GPIO_PIN,BOARD_INITPINS_LD_ENABLE_GPIO_PIN_MASK )

#define board_ld_stb_on_macro() GPIO_PortClear(BOARD_INITPINS_LD_STB_GPIO_PIN,BOARD_INITPINS_LD_STB_GPIO_PIN_MASK )
#define board_ld_en_on_macro() GPIO_PortClear(BOARD_INITPINS_LD_ENABLE_GPIO_PIN,BOARD_INITPINS_LD_ENABLE_GPIO_PIN_MASK )

/// PMW
#define board_pwm_outputEnable_enable_macro()
#define board_pwm_outputEnable_disable_macro()

//// UART
#define board_uart_en_on_macro()    GPIO_PortClear(BOARD_INITPINS_USB_UART_RST_GPIO,BOARD_INITPINS_USB_UART_RST_GPIO_PIN_MASK)
#define board_uart_en_off_macro()   GPIO_PortSet(BOARD_INITPINS_USB_UART_RST_GPIO,BOARD_INITPINS_USB_UART_RST_GPIO_PIN_MASK)
#define board_uart_det_read_macro() GPIO_PinRead(BOARD_INITPINS_USB_UART_RST_GPIO,BOARD_INITPINS_USB_UART_RST_GPIO_PIN)

#define board_uart2_sel_on_macro()  GPIO_PortSet(BOARD_INITPINS_UART2_SEL_GPIO, BOARD_INITPINS_UART2_SEL_GPIO_PIN_MASK)
#define board_uart2_sel_off_macro() GPIO_PortClear(BOARD_INITPINS_UART2_SEL_GPIO, BOARD_INITPINS_UART2_SEL_GPIO_PIN_MASK)


#endif // end of file
