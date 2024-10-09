////*****************************************////
//  Name : main.h
//  Data : 2022/01
//  Version : 0.1
////*****************************************////
//	v0.0 : head revision
//	v0.1 : version information expand
////*****************************************////

#ifndef _MAIN_H_
#define _MAIN_H_

#include "drv.h"
#include "lib.h"
#include "api.h"

#include "main_isr.h"


#define  NORMAL_MODE        0
#define  UART_TEST_MODE		1

#define TESTMODE    UART_TEST_MODE

// drive type
// **** form 0x0 to 0xf ****//
#define FIRMWARE_TYPE_THREE_PHASE	0x0
#define FIRMWARE_TYPE_TWO_PHASE		0x1

#define FIRMWARE_TYPE	FIRMWARE_TYPE_THREE_PHASE

// firmware update date
#define UPDATE_DATA	0x20241009
// firmware revision
// **** form 0x0 to 0xf ****//
// **** 16 revision available in one day ****//
#define REVISION	0x01

// firmware version information
// **** bit 7     driver type         ****//
// **** bit 6 ~ 1 driver update date  ****//
// **** bit 0     driver sub-revision ****//
#define FIRMWARE_VERSION (FIRMWARE_TYPE << 28 | ((UPDATE_DATA &0x00FFFFFF) << 4) | REVISION)


#endif // end of file
