////*****************************************////
//  Name : lib_crc_ext.h
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#ifndef _LIB_CRC_EXT_H_
#define _LIB_CRC_EXT_H_

#include "lib.h"

extern uint8 checksum_calc(uint8 *data,uint32 ulLengthBytes);
extern uint8 crc_crc8_0x31_calc(uint8 *data,uint32 ulLengthBytes);
extern uint8 crc_crc8_0x1D_initialValue_endValue_calc(uint8 *data,uint32 ulLengthBytes,uint8 initialValue,uint8 endValue);

#endif // end of file
