////*****************************************////
//  Name : drv_globalVariable_ext.h
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#ifndef _DRV_GLOBALVARIABLE_EXT_H_
#define _DRV_GLOBALVARIABLE_EXT_H_

typedef long int32;
typedef short int16;
typedef char int8;

typedef unsigned long uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

typedef float float32;

typedef _Bool boolen;

typedef void (* ulFuncSetPtr) (uint32);
typedef uint32 (* ulFuncGetPtr) (void);

typedef struct
{
	uint16 byte0 : 8;
	uint16 byte1 : 8;
}UUINT16_BYTES;

typedef union
{
	UUINT16_BYTES byte;
	uint16 word;
}uuint16;

typedef struct
{
	uint32 bit0 : 1;
	uint32 bit1 : 1;
	uint32 bit2 : 1;
	uint32 bit3 : 1;
	uint32 bit4 : 1;
	uint32 bit5 : 1;
	uint32 bit6 : 1;
	uint32 bit7 : 1;
	uint32 bit8 : 1;
	uint32 bit9 : 1;
	uint32 bit10 : 1;
	uint32 bit11 : 1;
	uint32 bit12 : 1;
	uint32 bit13 : 1;
	uint32 bit14 : 1;
	uint32 bit15 : 1;
	uint32 bit16 : 1;
	uint32 bit17 : 1;
	uint32 bit18 : 1;
	uint32 bit19 : 1;
	uint32 bit20 : 1;
	uint32 bit21 : 1;
	uint32 bit22 : 1;
	uint32 bit23 : 1;
	uint32 bit24 : 1;
	uint32 bit25 : 1;
	uint32 bit26 : 1;
	uint32 bit27 : 1;
	uint32 bit28 : 1;
	uint32 bit29 : 1;
	uint32 bit30 : 1;
	uint32 bit31 : 1;
}UULONGBIT32_BITS;

typedef union
{
	UULONGBIT32_BITS bit;
	uint32 dword;
}uuint32b;

typedef struct
{
	uint32 byte0 : 8;
	uint32 byte1 : 8;
	uint32 byte2 : 8;
	uint32 byte3 : 8;
}UULONGBIT32_BYTES;

typedef union
{
	UULONGBIT32_BYTES byte;
	uint32 dword;
}uuint32;


typedef struct
{
	uint8 bit0 : 1;
	uint8 bit1 : 1;
	uint8 bit2 : 1;
	uint8 bit3 : 1;
	uint8 bit4 : 1;
	uint8 bit5 : 1;
	uint8 bit6 : 1;
	uint8 bit7 : 1;
}UC_BITS;

typedef union
{
	UC_BITS bit;
	uint8 uchar;
}uuint8;

// extern function
extern void drv_globalVariable_init(void);

#define BIT0 0
#define BIT1 1
#define BIT2 2
#define BIT3 3
#define BIT4 4
#define BIT5 5
#define BIT6 6
#define BIT7 7
#define BIT8 8
#define BIT9 9
#define BIT10 10
#define BIT11 11
#define BIT12 12
#define BIT13 13
#define BIT14 14
#define BIT15 15
#define BIT16 16
#define BIT17 17
#define BIT18 18
#define BIT19 19
#define BIT20 20
#define BIT21 21
#define BIT22 22
#define BIT23 23
#define BIT24 24
#define BIT25 25
#define BIT26 26
#define BIT27 27
#define BIT28 28
#define BIT29 29
#define BIT30 30
#define BIT31 31

#define bitDataRead_macro(data,bit) ((data & 0x00000001 << bit) >> bit)

typedef struct{
	uint32 dataNew : 1;
	uint32 dataOld : 1;
	uint32 edge : 1;
	uint32 posEdge : 1;
	uint32 negEdge : 1;
	uint32 flag    : 1;
	uint32 limit_value :1;
	uint32 reserved : 25;
}SIGNAL_BITS;

typedef union{
	SIGNAL_BITS data;
	uint32 all;
}SIGNAL_REGS;



#endif // end of file
