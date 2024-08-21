/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright (c) 2008-2013 Code Red Technologies Ltd,
 * Copyright 2015, 2018-2019 NXP
 * (c) NXP Semiconductors 2013-2021
 * Generated linker script file for MIMXRT1064xxxxA
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.30
 * MCUXpresso IDE v11.3.1 [Build 5262] [2021-04-02] on Oct 18, 2021 2:31:46 PM
 */

MEMORY
{
  /* Define each memory region */
  PROGRAM_FLASH (rx) : ORIGIN = 0x70000000, LENGTH = 0x100000 /* 1M bytes (alias Flash) */  
  PROGRAM_FLASH_SET0 (rx) : ORIGIN = 0x70100000, LENGTH = 0x100000 /* 1M bytes (alias Flash2) */  
  PROGRAM_FLASH_SET1 (rx) : ORIGIN = 0x70200000, LENGTH = 0x100000 /* 1M bytes (alias Flash3) */  
  PARAMETER_FLASH (rx) : ORIGIN = 0x70300000, LENGTH = 0x100000 /* 1M bytes (alias Flash4) */  
  SRAM_DTC (rwx) : ORIGIN = 0x20000000, LENGTH = 0x20000 /* 128K bytes (alias RAM) */  
  SRAM_ITC (rwx) : ORIGIN = 0x0, LENGTH = 0x20000 /* 128K bytes (alias RAM2) */  
  SRAM_OC_BANK0 (rwx) : ORIGIN = 0x20200000, LENGTH = 0x40000 /* 256K bytes (alias RAM3) */  
  SRAM_OC_BANK1 (rwx) : ORIGIN = 0x20260000, LENGTH = 0x80000 /* 512K bytes (alias RAM4) */  
}

  /* Define a symbol for the top of each memory region */
  __base_PROGRAM_FLASH = 0x70000000  ; /* PROGRAM_FLASH */  
  __base_Flash = 0x70000000 ; /* Flash */  
  __top_PROGRAM_FLASH = 0x70000000 + 0x100000 ; /* 1M bytes */  
  __top_Flash = 0x70000000 + 0x100000 ; /* 1M bytes */  
  __base_PROGRAM_FLASH_SET0 = 0x70100000  ; /* PROGRAM_FLASH_SET0 */  
  __base_Flash2 = 0x70100000 ; /* Flash2 */  
  __top_PROGRAM_FLASH_SET0 = 0x70100000 + 0x100000 ; /* 1M bytes */  
  __top_Flash2 = 0x70100000 + 0x100000 ; /* 1M bytes */  
  __base_PROGRAM_FLASH_SET1 = 0x70200000  ; /* PROGRAM_FLASH_SET1 */  
  __base_Flash3 = 0x70200000 ; /* Flash3 */  
  __top_PROGRAM_FLASH_SET1 = 0x70200000 + 0x100000 ; /* 1M bytes */  
  __top_Flash3 = 0x70200000 + 0x100000 ; /* 1M bytes */  
  __base_PARAMETER_FLASH = 0x70300000  ; /* PARAMETER_FLASH */  
  __base_Flash4 = 0x70300000 ; /* Flash4 */  
  __top_PARAMETER_FLASH = 0x70300000 + 0x100000 ; /* 1M bytes */  
  __top_Flash4 = 0x70300000 + 0x100000 ; /* 1M bytes */  
  __base_SRAM_DTC = 0x20000000  ; /* SRAM_DTC */  
  __base_RAM = 0x20000000 ; /* RAM */  
  __top_SRAM_DTC = 0x20000000 + 0x20000 ; /* 128K bytes */  
  __top_RAM = 0x20000000 + 0x20000 ; /* 128K bytes */  
  __base_SRAM_ITC = 0x0  ; /* SRAM_ITC */  
  __base_RAM2 = 0x0 ; /* RAM2 */  
  __top_SRAM_ITC = 0x0 + 0x20000 ; /* 128K bytes */  
  __top_RAM2 = 0x0 + 0x20000 ; /* 128K bytes */  
  __base_SRAM_OC_BANK0 = 0x20200000  ; /* SRAM_OC_BANK0 */  
  __base_RAM3 = 0x20200000 ; /* RAM3 */  
  __top_SRAM_OC_BANK0 = 0x20200000 + 0x40000 ; /* 256K bytes */  
  __top_RAM3 = 0x20200000 + 0x40000 ; /* 256K bytes */  
  __base_SRAM_OC_BANK1 = 0x20260000  ; /* SRAM_OC_BANK1 */  
  __base_RAM4 = 0x20260000 ; /* RAM4 */  
  __top_SRAM_OC_BANK1 = 0x20260000 + 0x80000 ; /* 512K bytes */  
  __top_RAM4 = 0x20260000 + 0x80000 ; /* 512K bytes */  
