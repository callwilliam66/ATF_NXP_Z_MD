////*****************************************////
//  Name : motorControl_uart_firmwareUpdate.c
//  Data : 2020/10
//  Version : 0.0
////*****************************************////

#include "motorControl.h"

#define SRAM_PROGRAM_ADDR 0x20260000

uuint32 firmwareSet;
uint8	checkSum;

uint8* programIndex = (uint8*)SRAM_PROGRAM_ADDR;

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_uart_firmwareUpdate_tx(UART_REGS *uartRegs)
{
	if(uartRegs->firmwareUpdateFlag == 0) return;

	uuint8 uucState;
	uucState.bit.bit0 = uartRegs->firmwareUpdateState.bit.bit0;
	uucState.bit.bit1 = uartRegs->firmwareUpdateState.bit.bit1;
	uucState.bit.bit2 = uartRegs->firmwareUpdateState.bit.bit2;
	uucState.bit.bit3 = uartRegs->firmwareUpdateState.bit.bit3;
	uucState.bit.bit4 = uartRegs->firmwareUpdateState.bit.bit4;
	uucState.bit.bit5 = uartRegs->firmwareUpdateState.bit.bit5;
	uucState.bit.bit6 = uartRegs->firmwareUpdateState.bit.bit6;
	uucState.bit.bit7 = uartRegs->firmwareUpdateState.bit.bit7;
	uartRegs->txRegs.packet.header = UART_HEADER_DATA;
	uartRegs->txRegs.packet.ctrl_st = uucState.uchar;
	uartRegs->txRegs.packet.packet = uartRegs->rxRegs.packet.packet;

	uartRegs->txRegs.packet.data0 = 0;
	uartRegs->txRegs.packet.data1 = 0;
	uartRegs->txRegs.packet.data2 = 0;
	uartRegs->txRegs.packet.data3 = uartRegs->firmwareUpdatePacketLength%256;
	uartRegs->txRegs.packet.data4 = uartRegs->rxRegs.packet.data4;
	uartRegs->txRegs.packet.data5 = uartRegs->rxRegs.packet.data5;

}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void mCtrl_uart_firmwareUpdate_rx(UART_REGS *uartRegs)
{
	if(uartRegs->firmwareUpdateFlag == 0) return;

	uuint32 uulData;
	uulData.byte.byte0 = uartRegs->rxRegs.packet.data3;
	uulData.byte.byte1 = uartRegs->rxRegs.packet.data2;
	uulData.byte.byte2 = uartRegs->rxRegs.packet.data1;
	uulData.byte.byte3 = uartRegs->rxRegs.packet.data0;

	uuint32 ProgramSet;
	uint32 ulSectorCnt;
	uint32 ulPageCnt;
	uint8 *newProgramInfo;
	uint32 PageCntMax;
	uint32 ulDataIndex;

	switch(uartRegs->rxRegs.packet.packet)
	{
		case UART_PACKET_FIRMWARE_UPDATE:
			uartRegs->firmwareUpdateState.bit.bit0 = 1;
		break;
		case UART_PACKET_FIRMWARE_LENGTH:
			checkSum = 0;
			uartRegs->firmwareUpdateLength = uulData.dword;

			if((uartRegs->firmwareUpdateLength > 10000000L))
			{
				uartRegs->firmwareUpdateLength = 0;
				uartRegs->firmwareUpdateState.bit.bit1 = 0;
				uartRegs->firmwareUpdateState.bit.bit2 = 0;
				uartRegs->firmwareUpdateState.bit.bit3 = 0;
				uartRegs->firmwareUpdateState.bit.bit5 = 1;
				uartRegs->firmwareUpdateState.bit.bit6 = 0;
				programIndex = (uint8*)SRAM_PROGRAM_ADDR;
			}
			else
			{
				uartRegs->firmwareUpdateState.bit.bit1 = 1;
				uartRegs->firmwareUpdateState.bit.bit2 = 0;
				uartRegs->firmwareUpdateState.bit.bit3 = 0;
				uartRegs->firmwareUpdateState.bit.bit5 = 0;
				uartRegs->firmwareUpdateState.bit.bit6 = 0;
				programIndex = (uint8*)SRAM_PROGRAM_ADDR;
			}
		break;
		case UART_PACKET_FIRMWARE_PACKET_LENGTH:
			if(uulData.dword > 0)
			{
				uartRegs->firmwareUpdatePacketLength = uulData.dword;
				uartRegs->firmwareUpdateState.bit.bit0 = 1;
				uartRegs->firmwareUpdateState.bit.bit1 = 1;

			}else
			{
				uartRegs->firmwareUpdateState.bit.bit0 = 0;
				uartRegs->firmwareUpdateState.bit.bit1 = 0;
			}
		break;
		case UART_PACKET_FIRMWARE_RECEIVE:
			uartRegs->firmwareUpdateState.bit.bit2 = 1;
		break;
		case UART_PACKET_FIRMWARE_START:
			if(uartRegs->firmwareUpdateState.bit.bit1 == 0) break;
			if(uartRegs->firmwareUpdateState.bit.bit2 == 0) break;

			uartRegs->firmwareUpdateState.bit.bit1 = 0;
			uartRegs->firmwareUpdateState.bit.bit2 = 0;

			if(uulData.dword != checkSum)
			{
				uartRegs->firmwareUpdateState.bit.bit6 = 1;
			}
			else
			{
				device_pwm_pause();



				newProgramInfo = (uint8*)&ProgramSet;

				programIndex = (uint8*)SRAM_PROGRAM_ADDR;

				PageCntMax = (uartRegs->firmwareUpdateLength >> 8) + 1;

				ProgramSet.dword = 0x00000000;

				flexspi_nor_flash_erase_sector(NORFLASH_FLEXSPI, PROGRAM_INFO_SECTOR_START * SECTOR_SIZE);

				flexspi_nor_flash_program(NORFLASH_FLEXSPI, PROGRAM_INFO_SECTOR_START * SECTOR_SIZE, (const uint32_t *)newProgramInfo, 4);

				if( mCtrlRegs.ulfirmwareflashkey == 1)
				{
					for(ulSectorCnt = 0; ulSectorCnt < PROGRAM_SECTOR_NUMBER; ulSectorCnt++)
					{
						flexspi_nor_flash_erase_sector(NORFLASH_FLEXSPI, (PROGRAM1_SECTOR_START + ulSectorCnt) * SECTOR_SIZE);
					}

					for(ulPageCnt = 0; ulPageCnt < PageCntMax; ulPageCnt++)
					{
						ulDataIndex = ulPageCnt * FLASH_PAGE_SIZE;

						flexspi_nor_flash_page_program(NORFLASH_FLEXSPI, PROGRAM1_SECTOR_START * SECTOR_SIZE + ulDataIndex, (uint32_t*)(programIndex + ulDataIndex));
					}

					/*
					ProgramSet.dword = 0x00000001;

					flexspi_nor_flash_erase_sector(NORFLASH_FLEXSPI, PROGRAM_INFO_SECTOR_START * SECTOR_SIZE);

					flexspi_nor_flash_program(NORFLASH_FLEXSPI, PROGRAM_INFO_SECTOR_START * SECTOR_SIZE, (const uint32_t *)newProgramInfo, 4);

					firmwareSet.dword = 1;
					*/

				}
				else
				{
					for(ulSectorCnt = 0; ulSectorCnt < PROGRAM_SECTOR_NUMBER; ulSectorCnt++)
					{
						flexspi_nor_flash_erase_sector(NORFLASH_FLEXSPI, (PROGRAM0_SECTOR_START + ulSectorCnt) * SECTOR_SIZE);
					}

					for(ulPageCnt = 0; ulPageCnt < PageCntMax; ulPageCnt++)
					{
						ulDataIndex = ulPageCnt * FLASH_PAGE_SIZE;

						flexspi_nor_flash_page_program(NORFLASH_FLEXSPI, PROGRAM0_SECTOR_START * SECTOR_SIZE + ulDataIndex, (uint32_t*)(programIndex + ulDataIndex));
					}

					/*
					ProgramSet.dword = 0x00000000;

					flexspi_nor_flash_erase_sector(NORFLASH_FLEXSPI, PROGRAM_INFO_SECTOR_START * SECTOR_SIZE);

					flexspi_nor_flash_program(NORFLASH_FLEXSPI, PROGRAM_INFO_SECTOR_START * SECTOR_SIZE, (const uint32_t *)newProgramInfo, 4);


					firmwareSet.dword = 0;
					*/

				}
				device_pwm_run();

				uartRegs->firmwareUpdateState.bit.bit3 = 1;
			}
		break;
		case UART_PACKET_FIRMWARE_CHECK:
			device_pwm_pause();

			newProgramInfo = (uint8*)&ProgramSet;

			ProgramSet.dword = 1;

			flexspi_nor_flash_erase_sector(NORFLASH_FLEXSPI, PROGRAM_INFO_SECTOR_START * SECTOR_SIZE);

			flexspi_nor_flash_program(NORFLASH_FLEXSPI, PROGRAM_INFO_SECTOR_START * SECTOR_SIZE, (const uint32_t *)newProgramInfo, 4);

			device_pwm_run();

		break;
		case UART_PACKET_FIRMWARE_RESET:
			if(uulData.dword == 0x55AA00FF)
			{
				uartRegs->ulrestflag = 1;
				uartRegs->firmwareUpdateState.bit.bit4 = 1;
//				NVIC_SystemReset();
			}
		break;
		default:
		break;
	}

}
