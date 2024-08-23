/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PERIPHERALS_H_
#define _PERIPHERALS_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "fsl_common.h"
#include "fsl_adc.h"
#include "fsl_adc_etc.h"
#include "fsl_cmp.h"
#include "fsl_clock.h"
#include "fsl_enc.h"
#include "fsl_gpio.h"
#include "fsl_lpuart.h"
#include "fsl_pwm.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/
/* Definitions for BOARD_InitPeripherals functional group */
/* BOARD_InitPeripherals defines for ADC1 */
/* Definition of peripheral ID */
#define ADC1_PERIPHERAL ADC1
/* Definition of special channel interconnected with ADC_ETC which takes real channel to be measured from ADC_ETC. */
#define ADC1_CHANNEL_DRIVEN_BY_ADC_ETC 16U
/* Definition of ADC1 channel from configuration #0 13 */
#define CUR_U_CH 13U
/* Definition of ADC1 channel from configuration #1 11 */
#define VOLT_BUS_CH 11U
/* Definition of ADC1 channel from configuration #2 12 */
#define SYS_TEMP_CH 12U
/* Channel 0 (IN.13) conversion control group. */
#define ADC1_CH0_CONTROL_GROUP 0U
/* Channel 1 (IN.11) conversion control group. */
#define ADC1_CH1_CONTROL_GROUP 1U
/* Channel 2 (IN.12) conversion control group. */
#define ADC1_CH2_CONTROL_GROUP 2U
/* BOARD_InitPeripherals defines for ADC2 */
/* Definition of peripheral ID */
#define ADC2_PERIPHERAL ADC2
/* Definition of special channel interconnected with ADC_ETC which takes real channel to be measured from ADC_ETC. */
#define ADC2_CHANNEL_DRIVEN_BY_ADC_ETC 16U
/* Definition of ADC2 channel from configuration #0 4 */
#define CUR_W_CH 4U
/* Definition of ADC2 channel from configuration #1 2 */
#define Light_V_Out_CH 2U
/* Channel 0 (IN.4) conversion control group. */
#define ADC2_CH0_CONTROL_GROUP 0U
/* Channel 1 (IN.2) conversion control group. */
#define ADC2_CH1_CONTROL_GROUP 1U
/* BOARD_InitPeripherals defines for ADC_ETC */
/* Definition of peripheral ID */
#define ADC_ETC_PERIPHERAL ADC_ETC
/* Definition of the names for trigger configurations. Used as index to ADC_ETC_trigger_config array. */
enum ADC_ETC_trigger_config_names
{
  ADC_ETC_TC_0 = 0U,
  ADC_ETC_TC_1 = 1U
};
/* Definition of the names for trigger group parameter of multiple functions, like ADC_ETC_SetTriggerConfig() and ADC_ETC_SetTriggerChainConfig(). */
enum ADC_ETC_trigger_config_trigger_group_names
{
  ADC_ETC_TC_0_TG = 0U,
  ADC_ETC_TC_1_TG = 4U
};
/* ADC_ETC interrupt vector ID (number). */
#define ADC_ETC_ADC_ETC_0_IRQN ADC_ETC_IRQ0_IRQn
/* ADC_ETC interrupt handler identifier. */
#define ADC_ETC_ADC_ETC_0_IRQHANDLER ADC_ETC_IRQ0_IRQHandler
/* ADC_ETC interrupt vector ID (number). */
#define ADC_ETC_ADC_ETC_1_IRQN ADC_ETC_IRQ1_IRQn
/* ADC_ETC interrupt vector ID (number). */
#define ADC_ETC_ADC_ETC_2_IRQN ADC_ETC_IRQ2_IRQn
/* ADC_ETC interrupt vector ID (number). */
#define ADC_ETC_ADC_ETC_3_IRQN noInt
/* ADC_ETC interrupt vector ID (number). */
#define ADC_ETC_ADC_ETC_ERROR_IRQN ADC_ETC_ERROR_IRQ_IRQn
/* ADC_ETC interrupt handler identifier. */
#define ADC_ETC_ADC_ETC_ERROR_IRQHANDLER ADC_ETC_ERROR_IRQ_IRQHandler
/* Definition of peripheral ID */
#define CMP1_PERIPHERAL CMP1
/* Definition of positive input source used in CMP_SetInputChannels() function */
#define CMP1_POSITIVE_INPUT_NUMBER 7U
/* Definition of negative input source used in CMP_SetInputChannels() function */
#define CMP1_NEGATIVE_INPUT_NUMBER 6U
/* Definition of peripheral ID */
#define ENC1_PERIPHERAL ENC1
/* Definition of peripheral ID */
#define ENC2_PERIPHERAL ENC2
/* GPIO1 interrupt vector ID (number). */
#define GPIO1_GPIO_COMB_0_15_IRQN GPIO1_Combined_0_15_IRQn
/* GPIO1 interrupt handler identifier. */
#define GPIO1_GPIO_COMB_0_15_IRQHANDLER GPIO1_Combined_0_15_IRQHandler
/* GPIO1 interrupt vector ID (number). */
#define GPIO1_GPIO_COMB_16_31_IRQN GPIO1_Combined_16_31_IRQn
/* GPIO1 interrupt handler identifier. */
#define GPIO1_GPIO_COMB_16_31_IRQHANDLER GPIO1_Combined_16_31_IRQHandler
/* GPIO2 interrupt vector ID (number). */
#define GPIO2_GPIO_COMB_0_15_IRQN GPIO2_Combined_0_15_IRQn
/* GPIO2 interrupt handler identifier. */
#define GPIO2_GPIO_COMB_0_15_IRQHANDLER GPIO2_Combined_0_15_IRQHandler
/* GPIO2 interrupt vector ID (number). */
#define GPIO2_GPIO_COMB_16_31_IRQN GPIO2_Combined_16_31_IRQn
/* GPIO2 interrupt handler identifier. */
#define GPIO2_GPIO_COMB_16_31_IRQHANDLER GPIO2_Combined_16_31_IRQHandler
/* Definition of peripheral ID */
#define LPUART1_PERIPHERAL LPUART1
/* Definition of the clock source frequency */
#define LPUART1_CLOCK_SOURCE 80000000UL
/* Definition of peripheral ID */
#define PWM1_PERIPHERAL PWM1
/* Definition of submodule 0 ID */
#define PWM1_PWM_U kPWM_Module_0
/* Definition of clock source of submodule 0 frequency in Hertz */
#define PWM1_PWM_U_SM_CLK_SOURCE_FREQ_HZ 150000000U
/* Definition of submodule 0 counter clock source frequency in Hertz - PWM1_PWM_U_SM_CLK_SOURCE_FREQ_HZ divided by prescaler */
#define PWM1_PWM_U_COUNTER_CLK_SOURCE_FREQ_HZ 150000000U
/* Definition of submodule 0 counter (PWM) frequency in Hertz */
#define PWM1_PWM_U_COUNTER_FREQ_HZ 20000U
/* Definition of submodule 0 channel A ID */
#define PWM1_PWM_U_PWM_UH kPWM_PwmA
/* Definition of submodule 0 channel B ID */
#define PWM1_PWM_U_PWM_UL kPWM_PwmB
/* Definition of submodule 0 channel X ID */
#define PWM1_PWM_U_X kPWM_PwmX
/* PWM1 interrupt vector ID (number). */
#define PWM1_COMMON_SM_0_IRQN PWM1_0_IRQn
/* PWM1 interrupt vector priority. */
#define PWM1_COMMON_SM_0_IRQ_PRIORITY 4
/* PWM1 interrupt handler identifier. */
#define PWM_MOTOR_ISR PWM1_0_IRQHandler
/* Definition of submodule 1 ID */
#define PWM1_PWM_V kPWM_Module_1
/* Definition of clock source of submodule 1 frequency in Hertz */
#define PWM1_PWM_V_SM_CLK_SOURCE_FREQ_HZ 150000000U
/* Definition of submodule 1 counter clock source frequency in Hertz - PWM1_PWM_V_SM_CLK_SOURCE_FREQ_HZ divided by prescaler */
#define PWM1_PWM_V_COUNTER_CLK_SOURCE_FREQ_HZ 150000000U
/* Definition of submodule 1 counter (PWM) frequency in Hertz */
#define PWM1_PWM_V_COUNTER_FREQ_HZ 20000U
/* Definition of submodule 1 channel A ID */
#define PWM1_PWM_V_PWM_VH kPWM_PwmA
/* Definition of submodule 1 channel B ID */
#define PWM1_PWM_V_PWM_VL kPWM_PwmB
/* Definition of submodule 1 channel X ID */
#define PWM1_PWM_V_X kPWM_PwmX
/* Definition of submodule 2 ID */
#define PWM1_PWM_W kPWM_Module_2
/* Definition of clock source of submodule 2 frequency in Hertz */
#define PWM1_PWM_W_SM_CLK_SOURCE_FREQ_HZ 150000000U
/* Definition of submodule 2 counter clock source frequency in Hertz - PWM1_PWM_W_SM_CLK_SOURCE_FREQ_HZ divided by prescaler */
#define PWM1_PWM_W_COUNTER_CLK_SOURCE_FREQ_HZ 150000000U
/* Definition of submodule 2 counter (PWM) frequency in Hertz */
#define PWM1_PWM_W_COUNTER_FREQ_HZ 20000U
/* Definition of submodule 2 channel A ID */
#define PWM1_PWM_W_PWM_WH kPWM_PwmA
/* Definition of submodule 2 channel B ID */
#define PWM1_PWM_W_PWM_WL kPWM_PwmB
/* Definition of submodule 2 channel X ID */
#define PWM1_PWM_W_X kPWM_PwmX
/* Definition of fault Fault0 ID */
#define PWM1_F0_FAULT0 kPWM_Fault_0
/* Definition of fault Fault1 ID */
#define PWM1_F0_FAULT1 kPWM_Fault_1
/* Definition of fault Fault2 ID */
#define PWM1_F0_FAULT2 kPWM_Fault_2
/* Definition of fault Fault3 ID */
#define PWM1_F0_FAULT3 kPWM_Fault_3
/* PWM1 interrupt vector ID (number). */
#define PWM1_FAULT_ERROR_IRQN PWM1_FAULT_IRQn
/* PWM1 interrupt vector priority. */
#define PWM1_FAULT_ERROR_IRQ_PRIORITY 0
/* PWM1 interrupt handler identifier. */
#define PWM_MOTOR_FAULT_ISR PWM1_FAULT_IRQHandler
/* GPIO4 interrupt vector ID (number). */
#define GPIO4_GPIO_COMB_0_15_IRQN GPIO4_Combined_0_15_IRQn
/* GPIO4 interrupt handler identifier. */
#define GPIO4_GPIO_COMB_0_15_IRQHANDLER GPIO4_Combined_0_15_IRQHandler
/* GPIO4 interrupt vector ID (number). */
#define GPIO4_GPIO_COMB_16_31_IRQN GPIO4_Combined_16_31_IRQn
/* GPIO4 interrupt handler identifier. */
#define GPIO4_GPIO_COMB_16_31_IRQHANDLER GPIO4_Combined_16_31_IRQHandler
/* Definition of peripheral ID */
#define ENC3_PERIPHERAL ENC3
/* Definition of peripheral ID */
#define ENC4_PERIPHERAL ENC4
/* GPIO3 interrupt vector ID (number). */
#define GPIO3_GPIO_COMB_0_15_IRQN GPIO3_Combined_0_15_IRQn
/* GPIO3 interrupt handler identifier. */
#define GPIO3_GPIO_COMB_0_15_IRQHANDLER GPIO3_Combined_0_15_IRQHandler
/* GPIO3 interrupt vector ID (number). */
#define GPIO3_GPIO_COMB_16_31_IRQN GPIO3_Combined_16_31_IRQn
/* GPIO3 interrupt handler identifier. */
#define GPIO3_GPIO_COMB_16_31_IRQHANDLER GPIO3_Combined_16_31_IRQHandler
/* Definition of peripheral ID */
#define LPUART3_PERIPHERAL LPUART3
/* Definition of the clock source frequency */
#define LPUART3_CLOCK_SOURCE 80000000UL
/* LPUART3 interrupt vector ID (number). */
#define LPUART3_SERIAL_RX_TX_IRQN LPUART3_IRQn
/* LPUART3 interrupt vector priority. */
#define LPUART3_SERIAL_RX_TX_IRQ_PRIORITY 1
/* LPUART3 interrupt handler identifier. */
#define LPUART3_SERIAL_RX_TX_IRQHANDLER LPUART3_IRQHandler
/* GPIO5 interrupt vector ID (number). */
#define GPIO5_GPIO_COMB_0_15_IRQN GPIO5_Combined_0_15_IRQn
/* GPIO5 interrupt handler identifier. */
#define GPIO5_GPIO_COMB_0_15_IRQHANDLER GPIO5_Combined_0_15_IRQHandler
/* GPIO5 interrupt vector ID (number). */
#define GPIO5_GPIO_COMB_16_31_IRQN GPIO5_Combined_16_31_IRQn
/* GPIO5 interrupt handler identifier. */
#define GPIO5_GPIO_COMB_16_31_IRQHANDLER GPIO5_Combined_16_31_IRQHandler
/* Definition of peripheral ID */
#define LPUART4_PERIPHERAL LPUART4
/* Definition of the clock source frequency */
#define LPUART4_CLOCK_SOURCE 80000000UL
/* LPUART4 interrupt vector ID (number). */
#define LPUART4_SERIAL_RX_TX_IRQN LPUART4_IRQn
/* LPUART4 interrupt vector priority. */
#define LPUART4_SERIAL_RX_TX_IRQ_PRIORITY 1
/* LPUART4 interrupt handler identifier. */
#define LPUART4_SERIAL_RX_TX_IRQHANDLER LPUART4_IRQHandler
/* Definition of peripheral ID */
#define PWM4_PERIPHERAL PWM4
/* Definition of submodule 2 ID */
#define PWM4_SM0 kPWM_Module_2
/* Definition of clock source of submodule 2 frequency in Hertz */
#define PWM4_SM0_SM_CLK_SOURCE_FREQ_HZ 150000000U
/* Definition of submodule 2 counter clock source frequency in Hertz - PWM4_SM0_SM_CLK_SOURCE_FREQ_HZ divided by prescaler */
#define PWM4_SM0_COUNTER_CLK_SOURCE_FREQ_HZ 150000000U
/* Definition of submodule 2 counter (PWM) frequency in Hertz */
#define PWM4_SM0_COUNTER_FREQ_HZ 10000U
/* Definition of submodule 2 channel A ID */
#define PWM4_SM0_A kPWM_PwmA
/* Definition of submodule 2 channel B ID */
#define PWM4_SM0_B kPWM_PwmB
/* Definition of submodule 2 channel X ID */
#define PWM4_SM0_X kPWM_PwmX
/* Definition of fault Fault0 ID */
#define PWM4_F0_FAULT0 kPWM_Fault_0
/* Definition of fault Fault1 ID */
#define PWM4_F0_FAULT1 kPWM_Fault_1
/* Definition of fault Fault2 ID */
#define PWM4_F0_FAULT2 kPWM_Fault_2
/* Definition of fault Fault3 ID */
#define PWM4_F0_FAULT3 kPWM_Fault_3
/* PWM4 interrupt vector ID (number). */
#define PWM4_FAULT_ERROR_IRQN PWM4_FAULT_IRQn
/* PWM4 interrupt vector priority. */
#define PWM4_FAULT_ERROR_IRQ_PRIORITY 5
/* PWM4 interrupt handler identifier. */
#define PWM4_FAULT_ERROR_IRQHANDLER PWM4_FAULT_IRQHandler
/* Definition of peripheral ID */
#define LPUART2_PERIPHERAL LPUART2
/* Definition of the clock source frequency */
#define LPUART2_CLOCK_SOURCE 80000000UL
/* LPUART2 interrupt vector ID (number). */
#define LPUART2_SERIAL_RX_TX_IRQN LPUART2_IRQn
/* LPUART2 interrupt handler identifier. */
#define LPUART2_SERIAL_RX_TX_IRQHANDLER LPUART2_IRQHandler

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
extern const adc_config_t ADC1_config;
extern const adc_channel_config_t ADC1_channels_config[3];
extern const adc_config_t ADC2_config;
extern const adc_channel_config_t ADC2_channels_config[2];
extern const adc_etc_config_t ADC_ETC_config;
extern const adc_etc_trigger_config_t ADC_ETC_trigger_config[2];
extern const adc_etc_trigger_chain_config_t ADC_ETC_TC_0_chain_config[3];
extern const adc_etc_trigger_chain_config_t ADC_ETC_TC_1_chain_config[2];
extern const cmp_config_t CMP1_config;
extern const cmp_dac_config_t CMP1_dac_config;
extern const cmp_filter_config_t CMP1_filter_config;
extern enc_config_t ENC1_config;
extern enc_config_t ENC2_config;
extern const lpuart_config_t LPUART1_config;
extern pwm_config_t PWM1_PWM_U_config;

extern pwm_signal_param_t PWM1_PWM_U_pwm_function_config[2];
extern pwm_config_t PWM1_PWM_V_config;

extern pwm_signal_param_t PWM1_PWM_V_pwm_function_config[2];
extern pwm_config_t PWM1_PWM_W_config;

extern pwm_signal_param_t PWM1_PWM_W_pwm_function_config[2];
extern const pwm_fault_input_filter_param_t PWM1_faultInputFilter_config;
extern const pwm_fault_param_t PWM1_Fault0_fault_config;
extern const pwm_fault_param_t PWM1_Fault1_fault_config;
extern const pwm_fault_param_t PWM1_Fault2_fault_config;
extern const pwm_fault_param_t PWM1_Fault3_fault_config;
extern enc_config_t ENC3_config;
extern enc_config_t ENC4_config;
extern const lpuart_config_t LPUART3_config;
extern const lpuart_config_t LPUART4_config;
extern pwm_config_t PWM4_SM0_config;

extern pwm_signal_param_t PWM4_SM0_pwm_function_config[1];
extern const pwm_fault_input_filter_param_t PWM4_faultInputFilter_config;
extern const pwm_fault_param_t PWM4_Fault0_fault_config;
extern const pwm_fault_param_t PWM4_Fault1_fault_config;
extern const pwm_fault_param_t PWM4_Fault2_fault_config;
extern const pwm_fault_param_t PWM4_Fault3_fault_config;
extern const lpuart_config_t LPUART2_config;

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/

void BOARD_InitPeripherals(void);

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void);

#if defined(__cplusplus)
}
#endif

#endif /* _PERIPHERALS_H_ */
