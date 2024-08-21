////*****************************************////
//  Name : drv_device_pwm.c
//  Data : 2021/07
//  Version : 0.0
////*****************************************////

#include "drv_device.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void device_pwm_start(void)
{
    /* Set the load okay bit for all submodules to load registers from their buffer */
    PWM_SetPwmLdok(PWM1_PERIPHERAL, kPWM_Control_Module_0 | kPWM_Control_Module_1 | kPWM_Control_Module_2, true);

    /* Start the PWM generation from Submodules 0, 1 and 2 */
    PWM_StartTimer(PWM1_PERIPHERAL, kPWM_Control_Module_0 | kPWM_Control_Module_1 | kPWM_Control_Module_2);


    /* Set the load okay bit for all submodules to load registers from their buffer */
    PWM_SetPwmLdok(PWM4_PERIPHERAL, kPWM_Control_Module_2, true);

    /* Start the PWM generation from Submodules 0, 1 and 2 */
    PWM_StartTimer(PWM4_PERIPHERAL,kPWM_Control_Module_2);

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void device_pwm_pause(void)
{
    /* Set the load okay bit for all submodules to load registers from their buffer */
    PWM_SetPwmLdok(PWM1_PERIPHERAL, kPWM_Control_Module_0 | kPWM_Control_Module_1 | kPWM_Control_Module_2, true);

    /* Start the PWM generation from Submodules 0, 1 and 2 */
    PWM_StopTimer(PWM1_PERIPHERAL, kPWM_Control_Module_0 | kPWM_Control_Module_1 | kPWM_Control_Module_2);

    /* Set the load okay bit for all submodules to load registers from their buffer */
    PWM_SetPwmLdok(PWM4_PERIPHERAL,  kPWM_Control_Module_2, true);

    /* Start the PWM generation from Submodules 0, 1 and 2 */
    PWM_StopTimer(PWM4_PERIPHERAL,  kPWM_Control_Module_2);

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void device_pwm_run(void)
{
    /* Set the load okay bit for all submodules to load registers from their buffer */
    PWM_SetPwmLdok(PWM1_PERIPHERAL, kPWM_Control_Module_0 | kPWM_Control_Module_1 | kPWM_Control_Module_2, true);

    /* Start the PWM generation from Submodules 0, 1 and 2 */
    PWM_StartTimer(PWM1_PERIPHERAL, kPWM_Control_Module_0 | kPWM_Control_Module_1 | kPWM_Control_Module_2);

    /* Set the load okay bit for all submodules to load registers from their buffer */
    PWM_SetPwmLdok(PWM4_PERIPHERAL,  kPWM_Control_Module_2, true);

    /* Start the PWM generation from Submodules 0, 1 and 2 */
    PWM_StartTimer(PWM4_PERIPHERAL, kPWM_Control_Module_2);


}


#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void device_pwm_isr_clear(void)
{
	PWM_ClearStatusFlags(PWM1_PERIPHERAL, PWM1_PWM_U, kPWM_CompareVal0Flag | kPWM_CompareVal1Flag);
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void device_pwm_fault_isr_clear(void)
{
	PWM_ClearStatusFlags(PWM1_PERIPHERAL,PWM1_PWM_U,kPWM_Fault0Flag);
	PWM_ClearStatusFlags(PWM1_PERIPHERAL,PWM1_PWM_V,kPWM_Fault0Flag);
	PWM_ClearStatusFlags(PWM1_PERIPHERAL,PWM1_PWM_W,kPWM_Fault0Flag);
}


