////*****************************************////
//  Name : drv_device_norFlash_SIP.c
//  Data : 2027/07
//  Version : 0.0
////*****************************************////

#include "drv_device.h"
#include "drv_device_norFlash_SIP.h"

/* Program data buffer should be 4-bytes alignment, which can avoid busfault due to this memory region is configured as
   Device Memory by MPU. */
SDK_ALIGN(uint8_t device_norFlash_SIP_dataMemoryWriteBuffer[DATA_SIZE], 4);
SDK_ALIGN(uint8_t device_norFlash_SIP_dataMemoryEraseBuffer[DATA_SIZE], 4);
uint8_t device_norFlash_SIP_dataMemoryReadBuffer[DATA_SIZE];
volatile unsigned int *appBootVector;
#define APPBOOT_VECTOR 0x20000000
const uint32_t customLUT[CUSTOM_LUT_LENGTH] = {
 /* Fast read quad mode - SDR */
 [4 * NOR_CMD_LUT_SEQ_IDX_READ_FAST_QUAD] =
 FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x6B, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x18),
 [4 * NOR_CMD_LUT_SEQ_IDX_READ_FAST_QUAD + 1] = FLEXSPI_LUT_SEQ(
 kFLEXSPI_Command_DUMMY_SDR, kFLEXSPI_4PAD, 0x08, kFLEXSPI_Command_READ_SDR, kFLEXSPI_4PAD, 0x04),

 /* Fast read mode - SDR */
 [4 * NOR_CMD_LUT_SEQ_IDX_READ_FAST] =
 FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x0B, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x18),
 [4 * NOR_CMD_LUT_SEQ_IDX_READ_FAST + 1] = FLEXSPI_LUT_SEQ(
 kFLEXSPI_Command_DUMMY_SDR, kFLEXSPI_1PAD, 0x08, kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x04),

 /* Normal read mode -SDR */
 [4 * NOR_CMD_LUT_SEQ_IDX_READ_NORMAL] =
 FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x03, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x18),
 [4 * NOR_CMD_LUT_SEQ_IDX_READ_NORMAL + 1] =
 FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x04, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

 /* Read extend parameters */
 [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUS] =
 FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x81, kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x04),

 /* Write Enable */
 [4 * NOR_CMD_LUT_SEQ_IDX_WRITEENABLE] =
 FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x06, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

 /* Erase Sector */
 [4 * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR] =
 FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x20, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x18),

 /* Page Program - single mode */
 [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_SINGLE] =
 FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x02, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x18),
 [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_SINGLE + 1] =
 FLEXSPI_LUT_SEQ(kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_1PAD, 0x04, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

 /* Page Program - quad mode */
 [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_QUAD] =
 FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x32, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x18),
 [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_QUAD + 1] =
 FLEXSPI_LUT_SEQ(kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_4PAD, 0x04, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

 /* Read ID */
 [4 * NOR_CMD_LUT_SEQ_IDX_READID] =
 FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x9F, kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x04),

 /* Enable Quad mode */
 [4 * NOR_CMD_LUT_SEQ_IDX_WRITESTATUSREG] =
 FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x01, kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_1PAD, 0x04),

 /* Enter QPI mode */
 [4 * NOR_CMD_LUT_SEQ_IDX_ENTERQPI] =
 FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x35, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

 /* Exit QPI mode */
 [4 * NOR_CMD_LUT_SEQ_IDX_EXITQPI] =
 FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_4PAD, 0xF5, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

 /* Read status register */
 [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUSREG] =
 FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x05, kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x04),

 /* Erase whole chip */
 [4 * NOR_CMD_LUT_SEQ_IDX_ERASECHIP] =
 FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0xC7, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),
};

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
status_t flexspi_nor_write_enable(FLEXSPI_Type *base, uint32_t baseAddr)
{
    flexspi_transfer_t flashXfer;
    status_t status;

    /* Write enable */
    flashXfer.deviceAddress = baseAddr;
    flashXfer.port          = kFLEXSPI_PortA1;
    flashXfer.cmdType       = kFLEXSPI_Command;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_WRITEENABLE;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);

    return status;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
status_t flexspi_nor_wait_bus_busy(FLEXSPI_Type *base)
{
    /* Wait status ready. */
    bool isBusy;
    uint32_t readValue;
    status_t status;
    flexspi_transfer_t flashXfer;

    flashXfer.deviceAddress = 0;
    flashXfer.port          = kFLEXSPI_PortA1;
    flashXfer.cmdType       = kFLEXSPI_Read;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_READSTATUSREG;
    flashXfer.data          = &readValue;
    flashXfer.dataSize      = 1;

    do
    {
        status = FLEXSPI_TransferBlocking(base, &flashXfer);

        if (status != kStatus_Success)
        {
            return status;
        }
        if (FLASH_BUSY_STATUS_POL)
        {
            if (readValue & (1U << FLASH_BUSY_STATUS_OFFSET))
            {
                isBusy = true;
            }
            else
            {
                isBusy = false;
            }
        }
        else
        {
            if (readValue & (1U << FLASH_BUSY_STATUS_OFFSET))
            {
                isBusy = false;
            }
            else
            {
                isBusy = true;
            }
        }

    } while (isBusy);

    return status;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
status_t flexspi_nor_enable_quad_mode(FLEXSPI_Type *base)
{
    flexspi_transfer_t flashXfer;
    status_t status;
    uint32_t writeValue = FLASH_QUAD_ENABLE;

    /* Write enable */
    status = flexspi_nor_write_enable(base, 0);

    if (status != kStatus_Success)
    {
        return status;
    }

    /* Enable quad mode. */
    flashXfer.deviceAddress = 0;
    flashXfer.port          = kFLEXSPI_PortA1;
    flashXfer.cmdType       = kFLEXSPI_Write;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_WRITESTATUSREG;
    flashXfer.data          = &writeValue;
    flashXfer.dataSize      = 1;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);
    if (status != kStatus_Success)
    {
        return status;
    }

    status = flexspi_nor_wait_bus_busy(base);

    /* Do software reset. */
    FLEXSPI_SoftwareReset(base);

    return status;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
status_t flexspi_nor_flash_erase_sector(FLEXSPI_Type *base, uint32_t address)
{
    status_t status;
    flexspi_transfer_t flashXfer;

    /* Write enable */
    flashXfer.deviceAddress = address;
    flashXfer.port          = kFLEXSPI_PortA1;
    flashXfer.cmdType       = kFLEXSPI_Command;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_WRITEENABLE;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);

    if (status != kStatus_Success)
    {
        return status;
    }

    flashXfer.deviceAddress = address;
    flashXfer.port          = kFLEXSPI_PortA1;
    flashXfer.cmdType       = kFLEXSPI_Command;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_ERASESECTOR;
    status                  = FLEXSPI_TransferBlocking(base, &flashXfer);

    if (status != kStatus_Success)
    {
        return status;
    }

    status = flexspi_nor_wait_bus_busy(base);

    /* Do software reset. */
    FLEXSPI_SoftwareReset(base);

    return status;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
status_t flexspi_nor_flash_program(FLEXSPI_Type *base, uint32_t dstAddr, const uint32_t *src, uint32_t length)
{
    status_t status;
    flexspi_transfer_t flashXfer;

    /* Write enable */
    status = flexspi_nor_write_enable(base, dstAddr);

    if (status != kStatus_Success)
    {
        return status;
    }

    /* Prepare page program command */
    flashXfer.deviceAddress = dstAddr;
    flashXfer.port          = kFLEXSPI_PortA1;
    flashXfer.cmdType       = kFLEXSPI_Write;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_QUAD;
    flashXfer.data          = (uint32_t *)src;
    flashXfer.dataSize      = length;
    status                  = FLEXSPI_TransferBlocking(base, &flashXfer);

    if (status != kStatus_Success)
    {
        return status;
    }

    status = flexspi_nor_wait_bus_busy(base);

    /* Do software reset. */
#if defined(FSL_FEATURE_SOC_OTFAD_COUNT) && defined(FLEXSPI_AHBCR_CLRAHBRXBUF_MASK)
    base->AHBCR |= FLEXSPI_AHBCR_CLRAHBRXBUF_MASK | FLEXSPI_AHBCR_CLRAHBTXBUF_MASK;
    base->AHBCR &= ~(FLEXSPI_AHBCR_CLRAHBRXBUF_MASK | FLEXSPI_AHBCR_CLRAHBTXBUF_MASK);
#else
    FLEXSPI_SoftwareReset(base);
#endif

    return status;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
status_t flexspi_nor_flash_page_program(FLEXSPI_Type *base, uint32_t dstAddr, const uint32_t *src)
{
    status_t status;
    flexspi_transfer_t flashXfer;

    /* To make sure external flash be in idle status, added wait for busy before program data for
        an external flash without RWW(read while write) attribute.*/
    status = flexspi_nor_wait_bus_busy(base);

    if (kStatus_Success != status)
    {
        return status;
    }

    /* Write enable. */
    status = flexspi_nor_write_enable(base, dstAddr);

    if (status != kStatus_Success)
    {
        return status;
    }

    /* Prepare page program command */
    flashXfer.deviceAddress = dstAddr;
    flashXfer.port          = kFLEXSPI_PortA1;
    flashXfer.cmdType       = kFLEXSPI_Write;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_QUAD;
    flashXfer.data          = (uint32_t *)src;
    flashXfer.dataSize      = FLASH_PAGE_SIZE;
    status                  = FLEXSPI_TransferBlocking(base, &flashXfer);

    if (status != kStatus_Success)
    {
        return status;
    }

    status = flexspi_nor_wait_bus_busy(base);

    /* Do software reset. */
#if defined(FSL_FEATURE_SOC_OTFAD_COUNT) && defined(FLEXSPI_AHBCR_CLRAHBRXBUF_MASK)
    base->AHBCR |= FLEXSPI_AHBCR_CLRAHBRXBUF_MASK | FLEXSPI_AHBCR_CLRAHBTXBUF_MASK;
    base->AHBCR &= ~(FLEXSPI_AHBCR_CLRAHBRXBUF_MASK | FLEXSPI_AHBCR_CLRAHBTXBUF_MASK);
#else
    FLEXSPI_SoftwareReset(base);
#endif

    return status;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
status_t flexspi_nor_get_vendor_id(FLEXSPI_Type *base, uint8_t *vendorId)
{
    uint32_t temp;
    flexspi_transfer_t flashXfer;
    flashXfer.deviceAddress = 0;
    flashXfer.port          = kFLEXSPI_PortA1;
    flashXfer.cmdType       = kFLEXSPI_Read;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_READID;
    flashXfer.data          = &temp;
    flashXfer.dataSize      = 1;

    status_t status = FLEXSPI_TransferBlocking(base, &flashXfer);

    *vendorId = temp;

    /* Do software reset. */
#if defined(FSL_FEATURE_SOC_OTFAD_COUNT) && defined(FLEXSPI_AHBCR_CLRAHBRXBUF_MASK)
    base->AHBCR |= FLEXSPI_AHBCR_CLRAHBRXBUF_MASK | FLEXSPI_AHBCR_CLRAHBTXBUF_MASK;
    base->AHBCR &= ~(FLEXSPI_AHBCR_CLRAHBRXBUF_MASK | FLEXSPI_AHBCR_CLRAHBTXBUF_MASK);
#else
    FLEXSPI_SoftwareReset(base);
#endif

    return status;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
status_t flexspi_nor_erase_chip(FLEXSPI_Type *base)
{
    status_t status;
    flexspi_transfer_t flashXfer;

    /* Write enable */
    status = flexspi_nor_write_enable(base, 0);

    if (status != kStatus_Success)
    {
        return status;
    }

    flashXfer.deviceAddress = 0;
    flashXfer.port          = kFLEXSPI_PortA1;
    flashXfer.cmdType       = kFLEXSPI_Command;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_ERASECHIP;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);

    if (status != kStatus_Success)
    {
        return status;
    }

    status = flexspi_nor_wait_bus_busy(base);

    return status;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void flexspi_nor_flash_init(FLEXSPI_Type *base)
{
	 /* Update LUT table. */
	 FLEXSPI_UpdateLUT(base, 0, customLUT, CUSTOM_LUT_LENGTH);

	 /* Do software reset. */
	 FLEXSPI_SoftwareReset(base);//flash reset
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
status_t device_norFlash_SIP_config(void)
{
    status_t status;

    for(int32 i = 0; i < 1000000; i++){}

	flexspi_nor_flash_init(NORFLASH_FLEXSPI);

	status = flexspi_nor_enable_quad_mode(NORFLASH_FLEXSPI);

	return status;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void device_norFlash_SIP_dataMemoryReadAll(void)
{
	DCACHE_InvalidateByRange(NORFLASH_FLEXSPI_AMBA_BASE + DATA_SECTOR_START * SECTOR_SIZE, DATA_SIZE);

	memcpy(device_norFlash_SIP_dataMemoryReadBuffer,
			(void *)(NORFLASH_FLEXSPI_AMBA_BASE + DATA_SECTOR_START * SECTOR_SIZE),
	        sizeof(device_norFlash_SIP_dataMemoryReadBuffer));
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
status_t device_norFlash_SIP_dataMemoryEraseAll(void)
{
    status_t status;
    uint32 ulSectorCnt;
	for(ulSectorCnt = 0; ulSectorCnt < DATA_SECTOR_NUMBER; ulSectorCnt++)
	{
		status = flexspi_nor_flash_erase_sector(NORFLASH_FLEXSPI, (DATA_SECTOR_START + ulSectorCnt) * SECTOR_SIZE);

	    if (status != kStatus_Success)
	    {
	        return status;
	    }
	}

	memset(device_norFlash_SIP_dataMemoryEraseBuffer, 0xFFU, sizeof(device_norFlash_SIP_dataMemoryEraseBuffer));

	device_norFlash_SIP_dataMemoryReadAll();

	if (memcmp(device_norFlash_SIP_dataMemoryEraseBuffer, device_norFlash_SIP_dataMemoryReadBuffer, sizeof(device_norFlash_SIP_dataMemoryEraseBuffer)))
	{
		return kStatus_Fail;
	}

	return status;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
status_t device_norFlash_SIP_dataMemoryWriteAll(void)
{
	status_t status;

    uint32 ulPageCnt;
    uint32 ulDataIndex;
	uint32* pWriteData;
	for(ulPageCnt = 0; ulPageCnt < DATA_PAGE_NUMBER; ulPageCnt++)
	{

		ulDataIndex = ulPageCnt * FLASH_PAGE_SIZE;

		pWriteData = (uint32*)&device_norFlash_SIP_dataMemoryWriteBuffer[ulDataIndex];

		status = flexspi_nor_flash_page_program(NORFLASH_FLEXSPI, DATA_SECTOR_START * SECTOR_SIZE + ulDataIndex, (uint32_t*)pWriteData);

	    if (status != kStatus_Success)
	    {
	        return status;
	    }
	}

    if (status != kStatus_Success)
    {
        return kStatus_Fail;
    }

    device_norFlash_SIP_dataMemoryReadAll();

    if (memcmp(device_norFlash_SIP_dataMemoryWriteBuffer, device_norFlash_SIP_dataMemoryReadBuffer, sizeof(device_norFlash_SIP_dataMemoryWriteBuffer)))
    {
    	return kStatus_Fail;
    }

	return status;
}

#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
uint32 device_norFlash_SIP_dataMemoryRead_32bits(uint32 lIndex)
{
	uuint32 uulData;

	uulData.byte.byte3 = device_norFlash_SIP_dataMemoryReadBufferGet_macro(lIndex * 4 + 0);
	uulData.byte.byte2 = device_norFlash_SIP_dataMemoryReadBufferGet_macro(lIndex * 4 + 1);
	uulData.byte.byte1 = device_norFlash_SIP_dataMemoryReadBufferGet_macro(lIndex * 4 + 2);
	uulData.byte.byte0 = device_norFlash_SIP_dataMemoryReadBufferGet_macro(lIndex * 4 + 3);
	return uulData.dword;
}




#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void bootloader_programCopy(uint32 PROGRAM_SECTOR_START)
{
	uint32 programIndex;

	uint8 programBlockInfoReadBuffer[8];

	uuint32 totalLength;

	uuint32 blockCntMax;
	uint32 blockCnt;

	uuint32 blockAddr;
	uint8 *blockAddtPtr;
	uuint32 blocklength;

	programIndex = 0;

	DCACHE_InvalidateByRange(NORFLASH_FLEXSPI_AMBA_BASE + PROGRAM_SECTOR_START * SECTOR_SIZE, 8);
	memcpy(programBlockInfoReadBuffer, (void *)(NORFLASH_FLEXSPI_AMBA_BASE + PROGRAM_SECTOR_START * SECTOR_SIZE), 8);

	totalLength.byte.byte3 = programBlockInfoReadBuffer[0];
	totalLength.byte.byte2 = programBlockInfoReadBuffer[1];
	totalLength.byte.byte1 = programBlockInfoReadBuffer[2];
	totalLength.byte.byte0 = programBlockInfoReadBuffer[3];

	// total length check
	if(totalLength.dword >= 0x00100000)
	{
		return;
	}

	blockCntMax.byte.byte3 = programBlockInfoReadBuffer[4];
	blockCntMax.byte.byte2 = programBlockInfoReadBuffer[5];
	blockCntMax.byte.byte1 = programBlockInfoReadBuffer[6];
	blockCntMax.byte.byte0 = programBlockInfoReadBuffer[7];

	for(blockCnt = 0; blockCnt < blockCntMax.dword; blockCnt++)
	{
		programIndex += 8; // dummy Index

		DCACHE_InvalidateByRange(NORFLASH_FLEXSPI_AMBA_BASE + PROGRAM_SECTOR_START * SECTOR_SIZE + programIndex, 8);
		memcpy(programBlockInfoReadBuffer, (void *)(NORFLASH_FLEXSPI_AMBA_BASE + PROGRAM_SECTOR_START * SECTOR_SIZE + programIndex), 8);
		programIndex += 8;

		blockAddr.byte.byte3 = programBlockInfoReadBuffer[0];
		blockAddr.byte.byte2 = programBlockInfoReadBuffer[1];
		blockAddr.byte.byte1 = programBlockInfoReadBuffer[2];
		blockAddr.byte.byte0 = programBlockInfoReadBuffer[3];
		blocklength.byte.byte3 = programBlockInfoReadBuffer[4];
		blocklength.byte.byte2 = programBlockInfoReadBuffer[5];
		blocklength.byte.byte1 = programBlockInfoReadBuffer[6];
		blocklength.byte.byte0 = programBlockInfoReadBuffer[7];

		blockAddtPtr = (uint8 *)blockAddr.dword;

		DCACHE_InvalidateByRange(NORFLASH_FLEXSPI_AMBA_BASE + PROGRAM_SECTOR_START * SECTOR_SIZE + programIndex, 8);
		memcpy(blockAddtPtr, (void *)(NORFLASH_FLEXSPI_AMBA_BASE + PROGRAM_SECTOR_START * SECTOR_SIZE + programIndex), blocklength.dword);
		programIndex += blocklength.dword;

	}

	appBootVector = (unsigned int *)(APPBOOT_VECTOR + 4);

	void (*bootAddress)(void);
	bootAddress = (void(*)(void))(*appBootVector);

	uint32_t appStack = (uint32_t)(APPBOOT_VECTOR);

	__disable_irq();
	SCB->VTOR = appStack;

	bootAddress();

}

