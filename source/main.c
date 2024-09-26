////*****************************************////
//  Name : main.c
//  Data : 2022/01
//  Version : 0.1
////*****************************************////
//	v0.0 : head revision
//	v0.1 : periodical inspection
////*****************************************////
#include "main.h"

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
int main(void)
{

	//SCB_EnableICache();
	//SCB_EnableDCache();
	//SCB->CACR|= 0x1<<2;

	// initialization
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    board_led_r_on_macro();

    drv_init();
    lib_init();
    api_init();

    board_HSIO2_off_macro();

    uint32 startcnt;
    for(startcnt = 0; startcnt < 240000000; startcnt++);

    board_led_r_off_macro();

    // configuration
    //// flash config
    device_norFlash_SIP_config();

    //// basic working frequency config
    mDrv_ulCtrlBaseFreqSet_macro(ISR_FREQ_PWM);

    //// parameter update
    para_updateAll_macro();

	//// encoder config
	board_encoder_config(mPara_encoderTypeGet_macro(), mPara_motorPhaseDirGet_macro(), mPara_encoderDirGet_macro());

    // start
    //// encoder enable

	board_encoder_enableSet(ENCODER_ENABLE);

    //// software interrupt config
    software_isr_config();

	//// power counter start
	device_pwm_start();

	board_HSIO2_on_macro();

	/// enable uart isr
	EnableIRQ(LPUART1_SERIAL_RX_TX_IRQN);
	EnableIRQ(LPUART3_SERIAL_RX_TX_IRQN);


    while(1)
    {

    }

    return 0;
}
