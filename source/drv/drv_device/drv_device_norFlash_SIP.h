////*****************************************////
//  Name : drv_device_norFlash_SIP.h
//  Data : 2021/07
//  Version : 0.0
////*****************************************////

#ifndef _DRV_DEVICE_NORFLASH_SIP_H_
#define _DRV_DEVICE_NORFLASH_SIP_H_

//define
#define EXAMPLE_FLEXSPI           FLEXSPI2
#define FLASH_SIZE                0x200 /* 4Mb/KByte */
#define EXAMPLE_FLEXSPI_AMBA_BASE FlexSPI2_AMBA_BASE
#define FLASH_PAGE_SIZE           256
#define EXAMPLE_SECTOR            1023
#define SECTOR_SIZE               0x1000 /* 4K */

#define NORFLASH_FLEXSPI			FLEXSPI2
#define NORFLASH_FLEXSPI_AMBA_BASE	FlexSPI2_AMBA_BASE
#define PROGRAM_INFO_SECTOR_START	0x0FF
#define PROGRAM_INFO_SECTOR_END		0x100
#define PROGRAM0_SECTOR_START		0x100
#define PROGRAM0_SECTOR_END			0x1FF
#define PROGRAM1_SECTOR_START		0x200
#define PROGRAM1_SECTOR_END			0x2FF
#define PROGRAM_SECTOR_NUMBER		(PROGRAM0_SECTOR_END - PROGRAM0_SECTOR_START + 1)
#define DATA_SECTOR_START			0x300
#define DATA_SECTOR_END				0x301
#define DATA_SECTOR_NUMBER			(DATA_SECTOR_END - DATA_SECTOR_START + 1)
#define DATA_PAGE_NUMBER			(DATA_SECTOR_NUMBER * 16)
#define DATA_SIZE					(DATA_SECTOR_NUMBER * SECTOR_SIZE)

#define NOR_CMD_LUT_SEQ_IDX_READ_NORMAL        0
#define NOR_CMD_LUT_SEQ_IDX_READ_FAST          1
#define NOR_CMD_LUT_SEQ_IDX_READ_FAST_QUAD     2
#define NOR_CMD_LUT_SEQ_IDX_READSTATUS         3
#define NOR_CMD_LUT_SEQ_IDX_WRITEENABLE        4
#define NOR_CMD_LUT_SEQ_IDX_ERASESECTOR        5
#define NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_SINGLE 6
#define NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_QUAD   7
#define NOR_CMD_LUT_SEQ_IDX_READID             8
#define NOR_CMD_LUT_SEQ_IDX_WRITESTATUSREG     9
#define NOR_CMD_LUT_SEQ_IDX_ENTERQPI           10
#define NOR_CMD_LUT_SEQ_IDX_EXITQPI            11
#define NOR_CMD_LUT_SEQ_IDX_READSTATUSREG      12
#define NOR_CMD_LUT_SEQ_IDX_ERASECHIP          13

#define CUSTOM_LUT_LENGTH        60
#define FLASH_QUAD_ENABLE        0x40
#define FLASH_BUSY_STATUS_POL    1
#define FLASH_BUSY_STATUS_OFFSET 0

extern const uint32_t customLUT[CUSTOM_LUT_LENGTH];

extern status_t flexspi_nor_flash_program(FLEXSPI_Type *base, uint32_t dstAddr, const uint32_t *src, uint32_t length);
extern status_t flexspi_nor_flash_erase_sector(FLEXSPI_Type *base, uint32_t address);
extern status_t flexspi_nor_flash_page_program(FLEXSPI_Type *base, uint32_t dstAddr, const uint32_t *src);
extern status_t flexspi_nor_get_vendor_id(FLEXSPI_Type *base, uint8_t *vendorId);
extern status_t flexspi_nor_enable_quad_mode(FLEXSPI_Type *base);
extern status_t flexspi_nor_erase_chip(FLEXSPI_Type *base);
extern void flexspi_nor_flash_init(FLEXSPI_Type *base);

extern SDK_ALIGN(uint8_t device_norFlash_SIP_dataMemoryWriteBuffer[DATA_SIZE], 4);
extern SDK_ALIGN(uint8_t device_norFlash_SIP_dataMemoryEraseBuffer[DATA_SIZE], 4);
extern uint8_t device_norFlash_SIP_dataMemoryReadBuffer[DATA_SIZE];

extern status_t device_norFlash_SIP_config(void);
extern void device_norFlash_SIP_dataMemoryReadAll(void);
extern status_t device_norFlash_SIP_dataMemoryEraseAll(void);
extern status_t device_norFlash_SIP_dataMemoryWriteAll(void);

#define device_norFlash_SIP_dataMemoryWriteBufferSet_macro(lIndex, cDataByte) device_norFlash_SIP_dataMemoryWriteBuffer[lIndex] = cDataByte
#define device_norFlash_SIP_dataMemoryEraseBufferSet_macro(lIndex, cDataByte) device_norFlash_SIP_dataMemoryEraseBuffer[lIndex] = cDataByte
#define device_norFlash_SIP_dataMemoryReadBufferGet_macro(lIndex) device_norFlash_SIP_dataMemoryReadBuffer[lIndex]
extern uint32 device_norFlash_SIP_dataMemoryRead_32bits(uint32 lIndex);
extern void bootloader_programCopy(uint32 PROGRAM_SECTOR_START);

#endif
