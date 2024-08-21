////*****************************************////
//  Name : drv_device_ext.h
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#ifndef _DRV_DEVICE_EXT_H_
#define _DRV_DEVICE_EXT_H_

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MIMXRT1064.h"
#include "cr_section_macros.h"
#include "fsl_xbara.h"
#include "fsl_flexspi.h"
#include "fsl_cache.h"
#include "drv_device_norFlash_SIP.h"

#include "drv.h"

// extern variable
//// encoder
extern enc_config_t stEncoder_config_pulseCommand_abMode;
extern enc_config_t stEncoder_config_pulseCommand_pulseDirMode;
extern enc_config_t stEncoder_config_encoder_zeroAngleCloseMode;

// extern function
extern void drv_device_init(void);

//// encoder
extern void device_encoder_reverse(ENC_Type *base);

extern void device_spi_master_tx_enable(LPSPI_Type *base);
extern void device_spi_master_tx_enable_cs(LPSPI_Type *base,uint32 psc);
extern void device_spi_master_tx_dataSet(LPSPI_Type *base,uint8 *Data,uint32 ulLengthBytes);
extern void device_spi_master_rx_dataGet(LPSPI_Type *base,uint8 *Data,uint32 ulLengthBytes);
extern void device_spi_frameSet(LPSPI_Type *base,uint32 frame);
extern int32 device_spi_txEmpty_waitTimeOut(LPSPI_Type *base,uint32 timeOut);
extern int32 device_spi_rxEmpty_waitTimeOut(LPSPI_Type *base,uint32 timeOut);

extern void device_pwm_start(void);
extern void device_pwm_pause(void);
extern void device_pwm_run(void);
extern void device_pwm_isr_clear(void);
extern void device_pwm_fault_isr_clear(void);
extern void device_pwm_en_update(boolen bEnable);

//// uart
extern uint32 device_uart_txFifoEmpty(LPUART_Type *base);
extern uint32 device_uart_rxFifoEmpty(LPUART_Type *base);
extern uint32 device_uart_rxErrorStateClear(LPUART_Type *base);

#define	device_uart_txFifoEmpty_macro() 			(LPUART1_PERIPHERAL->FIFO & LPUART_FIFO_TXEMPT_MASK)
#define	device_uart_rxFifoEmpty_macro() 			(LPUART1_PERIPHERAL->FIFO & LPUART_FIFO_RXEMPT_MASK)
#define	device_uart_txWriteByte_macro(data) 		LPUART_WriteByte(LPUART1_PERIPHERAL, data)
#define	device_uart_rxReadByte_macro() 				LPUART_ReadByte(LPUART1_PERIPHERAL)

#define	device_uart_module_txFifoEmpty_macro(uart) 			(uart->FIFO & LPUART_FIFO_TXEMPT_MASK)
#define	device_uart_module_rxFifoEmpty_macro(uart) 			(uart->FIFO & LPUART_FIFO_RXEMPT_MASK)
#define	device_uart_module_txWriteByte_macro(uart, data)	LPUART_WriteByte(uart, data)
#define	device_uart_module_rxReadByte_macro(uart) 			LPUART_ReadByte(uart)


//// macro
//// gpio

//// adc
#define device_adc_status_eoc_get_macro() ADC_ETC_GetInterruptStatusFlags(ADC_ETC_PERIPHERAL, kADC_ETC_Trg0TriggerSource)
#define	device_adc_status_clear_macro() ADC_ETC_ClearInterruptStatusFlags(ADC_ETC_PERIPHERAL, kADC_ETC_Trg0TriggerSource, true)

//// pwm
#define device_pwm_isr_clear_macro() PWM_ClearStatusFlags(PWM1_PERIPHERAL, PWM1_PWM_U, kPWM_CompareVal0Flag | kPWM_CompareVal1Flag)

#define device_pwm_u_update_macro(value) PWM_UpdatePwmDutycycleHighAccuracy(PWM1_PERIPHERAL, PWM1_PWM_U, PWM1_PWM_U_PWM_UH, kPWM_CenterAligned, (value))
#define device_pwm_v_update_macro(value) PWM_UpdatePwmDutycycleHighAccuracy(PWM1_PERIPHERAL, PWM1_PWM_V, PWM1_PWM_V_PWM_VH, kPWM_CenterAligned, (value))
#define device_pwm_w_update_macro(value) PWM_UpdatePwmDutycycleHighAccuracy(PWM1_PERIPHERAL, PWM1_PWM_W, PWM1_PWM_W_PWM_WH, kPWM_CenterAligned, (value))

#define device_pwm_update_enable_macro() PWM_SetPwmLdok(PWM1_PERIPHERAL, kPWM_Control_Module_0 | kPWM_Control_Module_1 | kPWM_Control_Module_2, true)

#define device_pwm_update_macro(valueU,valueV,valueW)	\
	device_pwm_u_update_macro(valueU);\
	device_pwm_v_update_macro(valueV);\
	device_pwm_w_update_macro(valueW);\
	device_pwm_update_enable_macro();

#define device_pwm_led_update_macro(value) PWM_UpdatePwmDutycycleHighAccuracy(PWM4_PERIPHERAL, PWM4_SM0,PWM4_SM0_A, kPWM_CenterAligned, (value))
#define device_pwm_led_update_enable_macro() PWM_SetPwmLdok(PWM4_PERIPHERAL,  kPWM_Control_Module_2, true)

#define device_pwmL_update_macro(valueL)\
		device_pwm_led_update_macro(valueL);\
		device_pwm_led_update_enable_macro();

#endif // end of file
