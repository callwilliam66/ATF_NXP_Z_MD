////*****************************************////
//  Name : motorControl_uart.h
//  Data : 2021/07
//  Version : 0.0
////*****************************************////

#ifndef _MOTORCONTROL_UART_H_
#define _MOTORCONTROL_UART_H_

#include "api.h"

#define UART_MODULE1
#define UART_MODULE2

#define UART_TX_PACKET_LENGTH 9
#define UART_TX_REDUCE_PACKET_LENGTH 7

#define UART_PACKET_MODE0_9BITS	0
#define UART_PACKET_MODE1_7BITS	1
#define UART_PACKET_MODE2_NOSE	2

#define UART_HEADER_DATA 0x31
#define UART_REDUCE_HEADER_DATA 0x51
#define UART_NOSEWHEEL_HEADER_DATA 0x32

#define UART_PACKET_VERSION_GET         0x07
#define UART_PACKET_ALARM_SET			0x09
#define UART_PACKET_DI_STATE_SET		0x0A
#define UART_PACKET_DO_STATE_SET		0x0B
#define UART_PACKET_SW_STATE_SET		0x0C
#define UART_PACKET_PCMD_ABS_SET		0x11
#define UART_PACKET_PCMD_INC_SET		0x13
#define UART_PACKET_ABS_TCURVE_SET		0x15
#define UART_PACKET_INC_TCURVE_SET		0x17
#define UART_PACKET_TEST_GET   			0x19
#define UART_PACKET_ALARM_GET			0x49
#define UART_PACKET_DI_STATE_GET		0x4A
#define UART_PACKET_DO_STATE_GET		0x4B
#define UART_PACKET_SW_STATE_GET		0x4C

#define UART_PACKET_PARA_CH0_SET		0x21
#define UART_PACKET_PARA_CH0_GET		0x61
#define UART_PACKET_PARA_CH0_DATA_SET	0x23
#define UART_PACKET_PARA_CH0_DATA_GET	0x63
#define UART_PACKET_PARA_CH1_SET		0x25
#define UART_PACKET_PARA_CH1_GET		0x65
#define UART_PACKET_PARA_CH1_DATA_SET	0x27
#define UART_PACKET_PARA_CH1_DATA_GET	0x67

#define UART_PACKET_FIRMWARE_UPDATE				0x81
#define UART_PACKET_FIRMWARE_BOOT				0x82
#define UART_PACKET_FIRMWARE_LENGTH				0x83
#define UART_PACKET_FIRMWARE_PACKET_LENGTH		0x84
#define UART_PACKET_FIRMWARE_RECEIVE			0x85
#define UART_PACKET_FIRMWARE_KEY                0x86
#define UART_PACKET_FIRMWARE_START				0x87
#define UART_PACKET_FIRMWARE_CHECK				0x89
#define UART_PACKET_FIRMWARE_RESET				0x8F

#define UART_PACKET_REPEATER			0X91


#define UART_TX_STATE_IDLE	0
#define UART_TX_STATE_BUSY	1

#define UART_TX_DATA_IDLE	0
#define UART_TX_DATA_UPDATE	1

#define UART_RX_STATE_IDLE 	0
#define UART_RX_STATE_BUSY	1

#define UART_RX_DATA_IDLE	0
#define UART_RX_DATA_UPDATE	1

#define UART_RX_CHECK_FAIL 	0
#define UART_RX_CHECK_PASS	1



typedef struct
{
	volatile uint32 header : 8;
	volatile uint32 packet : 8;
	volatile uint32 ctrl_st : 8;
	volatile uint32 data0 : 8;
	volatile uint32 data1 : 8;
	volatile uint32 data2 : 8;
	volatile uint32 data3 : 8;
	volatile uint32 data4 : 8;
	volatile uint32 data5 : 8;
}UART_PACKET;

typedef union
{
	UART_PACKET packet;
	volatile  uint8 data[UART_TX_PACKET_LENGTH];
}UART_PACKET_REGS;

typedef struct
{
	LPUART_Type *module;
	volatile uint32	txState;
	volatile uint32	txUpdate;

	volatile uint32 rxState;
	volatile uint32 rxUpdate;
	volatile uint32 rxCheckFail;

	volatile uint32	txCnt;
	volatile uint32	txpwmCnt;
	volatile uint32	tx_expect_Cnt;

	volatile uint32	rxCnt;
	volatile uint32	rxisrCnt;
	volatile uint32	rxcmdCnt;
	volatile uint32	global_read_cnt;
	volatile uint32 ulCheckCnt;

	volatile uint32 ulZaxisTxcnt;
	volatile uint32 ulXaxisTxcnt;
	volatile uint32 ulZaxisRxcnt;
	volatile uint32 ulXaxisRxcnt;

	volatile  uint32 packetMode;
	volatile  uint32 rxpacketMode;
	volatile  uint32 txpacketMode;

	volatile  uint32 RxPacket[2];

	volatile uint32 XcmdPendStatus;
	volatile uint32 XcmdPendTime;

	UART_PACKET_REGS txRegs;
	UART_PACKET_REGS rxRegs;

	uint32 rxdataReg_H;
	uint32 rxdataReg_L;

	uint32   Rx_Isr_Status;
	CcQueue  Rx_Data_Queue;

	uuint8 firmwareUpdateState;
	uint32 firmwareUpdateFlag;
	uint32 firmwareUpdateLength;
	uint32 firmwareReceiveFlag;
	uint32 firmwareRxDoneFlag;
	uint32 firmwareUpdatePacketLength;


	uint32 ulrestflag;

}UART_REGS;


extern void mCtrl_uart_init(UART_REGS *uartRegs,LPUART_Type *module);
extern void mCtrl_uart_isr(UART_REGS *uartRegs);


extern void mCtrl_uart_tx_dataUpdate(UART_REGS *uartRegs);
extern void mCtrl_uart_tx(UART_REGS *uartRegs);
extern void mCtrl_uart_rx(UART_REGS *uartRegs);
extern void mCtrl_uart_rx_dataUpdate(UART_REGS *uartRegs);

extern void mCtrl_fpga_uart_isr(UART_REGS *uartRegs);
extern void mCtrl_fpga_uart_tx_dataUpdate(UART_REGS *uartRegs);
extern void mCtrl_fpga_uart_tx(UART_REGS *uartRegs);
extern void mCtrl_fpga_uart_rx(UART_REGS *uartRegs);
extern void mCtrl_fpga_uart_rx_dataUpdate(UART_REGS *uartRegs);

//inner uart
extern void mCtrl_inner_uart_isr(UART_REGS *uartRegs);
extern void mCtrl_inner_uart_rx(UART_REGS *uartRegs);
extern void mCtrl_inner_uart_tx_dataUpdate(UART_REGS *uartRegs);

extern uint8	checkSum;
extern uuint32	firmwareSet;
extern uint8*	programIndex;

extern void mCtrl_uart_firmwareUpdate_tx(UART_REGS *uartRegs);
extern void mCtrl_uart_firmwareUpdate_rx(UART_REGS *uartRegs);
extern void mCtrl_uart_firmwareUpdate_programReceive(UART_REGS *uartRegs);

extern void uartPacketCmd0(uint32 uldata);
extern void uartPacketCmd1(uint32 uldata);
extern void uartPacketCmd2(uint32 uldata);
extern void uartPacketCmd3(uint32 uldata);
extern void uartPacketCmd4(uint32 uldata);
extern void uartPacketCmd5(uint32 uldata);
extern void uartPacketCmd6(uint32 uldata);
extern void uartPacketCmd7(uint32 uldata);
extern void uartPacketCmd8(uint32 uldata);
extern void uartPacketCmd9(uint32 uldata);
extern void uartPacketCmd10(uint32 uldata);
extern void uartPacketCmd11(uint32 uldata);
extern void uartPacketCmd12(uint32 uldata);
extern void uartPacketCmd13(uint32 uldata);
extern void uartPacketCmd14(uint32 uldata);
extern void uartPacketCmd15(uint32 uldata);
extern void uartPacketCmd16(uint32 uldata);
extern void uartPacketCmd17(uint32 uldata);
extern void uartPacketCmd18(uint32 uldata);
extern void uartPacketCmd19(uint32 uldata);
extern void uartPacketCmd20(uint32 uldata);
extern void uartPacketCmd21(uint32 uldata);
extern void uartPacketCmd22(uint32 uldata);
extern void uartPacketCmd23(uint32 uldata);
extern void uartPacketCmd24(uint32 uldata);
extern void uartPacketCmd25(uint32 uldata);
extern void uartPacketCmd26(uint32 uldata);
extern void uartPacketCmd27(uint32 uldata);
extern void uartPacketCmd28(uint32 uldata);
extern void uartPacketCmd29(uint32 uldata);
extern void uartPacketCmd30(uint32 uldata);
extern void uartPacketCmd31(uint32 uldata);
extern void uartPacketCmd32(uint32 uldata);
extern void uartPacketCmd33(uint32 uldata);
extern void uartPacketCmd34(uint32 uldata);
extern void uartPacketCmd35(uint32 uldata);
extern void uartPacketCmd36(uint32 uldata);
extern void uartPacketCmd37(uint32 uldata);
extern void uartPacketCmd38(uint32 uldata);
extern void uartPacketCmd39(uint32 uldata);
extern void uartPacketCmd40(uint32 uldata);
extern void uartPacketCmd41(uint32 uldata);
extern void uartPacketCmd42(uint32 uldata);
extern void uartPacketCmd43(uint32 uldata);
extern void uartPacketCmd44(uint32 uldata);
extern void uartPacketCmd45(uint32 uldata);
extern void uartPacketCmd46(uint32 uldata);
extern void uartPacketCmd47(uint32 uldata);
extern void uartPacketCmd48(uint32 uldata);
extern void uartPacketCmd49(uint32 uldata);
extern void uartPacketCmd50(uint32 uldata);
extern void uartPacketCmd51(uint32 uldata);
extern void uartPacketCmd52(uint32 uldata);
extern void uartPacketCmd53(uint32 uldata);
extern void uartPacketCmd54(uint32 uldata);
extern void uartPacketCmd55(uint32 uldata);
extern void uartPacketCmd56(uint32 uldata);
extern void uartPacketCmd57(uint32 uldata);
extern void uartPacketCmd58(uint32 uldata);
extern void uartPacketCmd59(uint32 uldata);
extern void uartPacketCmd60(uint32 uldata);
extern void uartPacketCmd61(uint32 uldata);
extern void uartPacketCmd62(uint32 uldata);
extern void uartPacketCmd63(uint32 uldata);
extern void uartPacketCmd64(uint32 uldata);
extern void uartPacketCmd65(uint32 uldata);
extern void uartPacketCmd66(uint32 uldata);
extern void uartPacketCmd67(uint32 uldata);
extern void uartPacketCmd68(uint32 uldata);
extern void uartPacketCmd69(uint32 uldata);
extern void uartPacketCmd70(uint32 uldata);
extern void uartPacketCmd71(uint32 uldata);
extern void uartPacketCmd72(uint32 uldata);
extern void uartPacketCmd73(uint32 uldata);
extern void uartPacketCmd74(uint32 uldata);
extern void uartPacketCmd75(uint32 uldata);
extern void uartPacketCmd76(uint32 uldata);
extern void uartPacketCmd77(uint32 uldata);
extern void uartPacketCmd78(uint32 uldata);
extern void uartPacketCmd79(uint32 uldata);
extern void uartPacketCmd80(uint32 uldata);
extern void uartPacketCmd81(uint32 uldata);
extern void uartPacketCmd82(uint32 uldata);
extern void uartPacketCmd83(uint32 uldata);
extern void uartPacketCmd84(uint32 uldata);
extern void uartPacketCmd85(uint32 uldata);
extern void uartPacketCmd86(uint32 uldata);
extern void uartPacketCmd87(uint32 uldata);
extern void uartPacketCmd88(uint32 uldata);
extern void uartPacketCmd89(uint32 uldata);
extern void uartPacketCmd90(uint32 uldata);
extern void uartPacketCmd91(uint32 uldata);
extern void uartPacketCmd92(uint32 uldata);
extern void uartPacketCmd93(uint32 uldata);
extern void uartPacketCmd94(uint32 uldata);
extern void uartPacketCmd95(uint32 uldata);
extern void uartPacketCmd96(uint32 uldata);
extern void uartPacketCmd97(uint32 uldata);
extern void uartPacketCmd98(uint32 uldata);
extern void uartPacketCmd99(uint32 uldata);
extern void uartPacketCmd100(uint32 uldata);
extern void uartPacketCmd101(uint32 uldata);
extern void uartPacketCmd102(uint32 uldata);
extern void uartPacketCmd103(uint32 uldata);
extern void uartPacketCmd104(uint32 uldata);
extern void uartPacketCmd105(uint32 uldata);
extern void uartPacketCmd106(uint32 uldata);
extern void uartPacketCmd107(uint32 uldata);
extern void uartPacketCmd108(uint32 uldata);
extern void uartPacketCmd109(uint32 uldata);
extern void uartPacketCmd110(uint32 uldata);
extern void uartPacketCmd111(uint32 uldata);
extern void uartPacketCmd112(uint32 uldata);
extern void uartPacketCmd113(uint32 uldata);
extern void uartPacketCmd114(uint32 uldata);
extern void uartPacketCmd115(uint32 uldata);
extern void uartPacketCmd116(uint32 uldata);
extern void uartPacketCmd117(uint32 uldata);
extern void uartPacketCmd118(uint32 uldata);
extern void uartPacketCmd119(uint32 uldata);
extern void uartPacketCmd120(uint32 uldata);
extern void uartPacketCmd121(uint32 uldata);
extern void uartPacketCmd122(uint32 uldata);
extern void uartPacketCmd123(uint32 uldata);
extern void uartPacketCmd124(uint32 uldata);
extern void uartPacketCmd125(uint32 uldata);
extern void uartPacketCmd126(uint32 uldata);
extern void uartPacketCmd127(uint32 uldata);
extern void uartPacketCmd128(uint32 uldata);
extern void uartPacketCmd129(uint32 uldata);
extern void uartPacketCmd130(uint32 uldata);
extern void uartPacketCmd131(uint32 uldata);
extern void uartPacketCmd132(uint32 uldata);
extern void uartPacketCmd133(uint32 uldata);
extern void uartPacketCmd134(uint32 uldata);
extern void uartPacketCmd135(uint32 uldata);
extern void uartPacketCmd136(uint32 uldata);
extern void uartPacketCmd137(uint32 uldata);
extern void uartPacketCmd138(uint32 uldata);
extern void uartPacketCmd139(uint32 uldata);
extern void uartPacketCmd140(uint32 uldata);
extern void uartPacketCmd141(uint32 uldata);
extern void uartPacketCmd142(uint32 uldata);
extern void uartPacketCmd143(uint32 uldata);
extern void uartPacketCmd144(uint32 uldata);
extern void uartPacketCmd145(uint32 uldata);
extern void uartPacketCmd146(uint32 uldata);
extern void uartPacketCmd147(uint32 uldata);
extern void uartPacketCmd148(uint32 uldata);
extern void uartPacketCmd149(uint32 uldata);
extern void uartPacketCmd150(uint32 uldata);
extern void uartPacketCmd151(uint32 uldata);
extern void uartPacketCmd152(uint32 uldata);
extern void uartPacketCmd153(uint32 uldata);
extern void uartPacketCmd154(uint32 uldata);
extern void uartPacketCmd155(uint32 uldata);
extern void uartPacketCmd156(uint32 uldata);
extern void uartPacketCmd157(uint32 uldata);
extern void uartPacketCmd158(uint32 uldata);
extern void uartPacketCmd159(uint32 uldata);
extern void uartPacketCmd160(uint32 uldata);
extern void uartPacketCmd161(uint32 uldata);
extern void uartPacketCmd162(uint32 uldata);
extern void uartPacketCmd163(uint32 uldata);
extern void uartPacketCmd164(uint32 uldata);
extern void uartPacketCmd165(uint32 uldata);
extern void uartPacketCmd166(uint32 uldata);
extern void uartPacketCmd167(uint32 uldata);
extern void uartPacketCmd168(uint32 uldata);
extern void uartPacketCmd169(uint32 uldata);
extern void uartPacketCmd170(uint32 uldata);
extern void uartPacketCmd171(uint32 uldata);
extern void uartPacketCmd172(uint32 uldata);
extern void uartPacketCmd173(uint32 uldata);
extern void uartPacketCmd174(uint32 uldata);
extern void uartPacketCmd175(uint32 uldata);
extern void uartPacketCmd176(uint32 uldata);
extern void uartPacketCmd177(uint32 uldata);
extern void uartPacketCmd178(uint32 uldata);
extern void uartPacketCmd179(uint32 uldata);
extern void uartPacketCmd180(uint32 uldata);
extern void uartPacketCmd181(uint32 uldata);
extern void uartPacketCmd182(uint32 uldata);
extern void uartPacketCmd183(uint32 uldata);
extern void uartPacketCmd184(uint32 uldata);
extern void uartPacketCmd185(uint32 uldata);
extern void uartPacketCmd186(uint32 uldata);
extern void uartPacketCmd187(uint32 uldata);
extern void uartPacketCmd188(uint32 uldata);
extern void uartPacketCmd189(uint32 uldata);
extern void uartPacketCmd190(uint32 uldata);
extern void uartPacketCmd191(uint32 uldata);
extern void uartPacketCmd192(uint32 uldata);
extern void uartPacketCmd193(uint32 uldata);
extern void uartPacketCmd194(uint32 uldata);
extern void uartPacketCmd195(uint32 uldata);
extern void uartPacketCmd196(uint32 uldata);
extern void uartPacketCmd197(uint32 uldata);
extern void uartPacketCmd198(uint32 uldata);
extern void uartPacketCmd199(uint32 uldata);
extern void uartPacketCmd200(uint32 uldata);
extern void uartPacketCmd201(uint32 uldata);
extern void uartPacketCmd202(uint32 uldata);
extern void uartPacketCmd203(uint32 uldata);
extern void uartPacketCmd204(uint32 uldata);
extern void uartPacketCmd205(uint32 uldata);
extern void uartPacketCmd206(uint32 uldata);
extern void uartPacketCmd207(uint32 uldata);
extern void uartPacketCmd208(uint32 uldata);
extern void uartPacketCmd209(uint32 uldata);
extern void uartPacketCmd210(uint32 uldata);
extern void uartPacketCmd211(uint32 uldata);
extern void uartPacketCmd212(uint32 uldata);
extern void uartPacketCmd213(uint32 uldata);
extern void uartPacketCmd214(uint32 uldata);
extern void uartPacketCmd215(uint32 uldata);
extern void uartPacketCmd216(uint32 uldata);
extern void uartPacketCmd217(uint32 uldata);
extern void uartPacketCmd218(uint32 uldata);
extern void uartPacketCmd219(uint32 uldata);
extern void uartPacketCmd220(uint32 uldata);
extern void uartPacketCmd221(uint32 uldata);
extern void uartPacketCmd222(uint32 uldata);
extern void uartPacketCmd223(uint32 uldata);
extern void uartPacketCmd224(uint32 uldata);
extern void uartPacketCmd225(uint32 uldata);
extern void uartPacketCmd226(uint32 uldata);
extern void uartPacketCmd227(uint32 uldata);
extern void uartPacketCmd228(uint32 uldata);
extern void uartPacketCmd229(uint32 uldata);
extern void uartPacketCmd230(uint32 uldata);
extern void uartPacketCmd231(uint32 uldata);
extern void uartPacketCmd232(uint32 uldata);
extern void uartPacketCmd233(uint32 uldata);
extern void uartPacketCmd234(uint32 uldata);
extern void uartPacketCmd235(uint32 uldata);
extern void uartPacketCmd236(uint32 uldata);
extern void uartPacketCmd237(uint32 uldata);
extern void uartPacketCmd238(uint32 uldata);
extern void uartPacketCmd239(uint32 uldata);
extern void uartPacketCmd240(uint32 uldata);
extern void uartPacketCmd241(uint32 uldata);
extern void uartPacketCmd242(uint32 uldata);
extern void uartPacketCmd243(uint32 uldata);
extern void uartPacketCmd244(uint32 uldata);
extern void uartPacketCmd245(uint32 uldata);
extern void uartPacketCmd246(uint32 uldata);
extern void uartPacketCmd247(uint32 uldata);
extern void uartPacketCmd248(uint32 uldata);
extern void uartPacketCmd249(uint32 uldata);
extern void uartPacketCmd250(uint32 uldata);
extern void uartPacketCmd251(uint32 uldata);
extern void uartPacketCmd252(uint32 uldata);
extern void uartPacketCmd253(uint32 uldata);
extern void uartPacketCmd254(uint32 uldata);
extern void uartPacketCmd255(uint32 uldata);


#endif // end of file
