/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright (c) 2008-2013 Code Red Technologies Ltd,
 * Copyright 2015, 2018-2019 NXP
 * (c) NXP Semiconductors 2013-2021
 * Generated linker script file for MIMXRT1064xxxxA
 * Created from linkscript.ldt by FMCreateLinkLibraries
 * Using Freemarker v2.3.30
 * MCUXpresso IDE v11.3.1 [Build 5262] [2021-04-02] on Oct 18, 2021 2:31:46 PM
 */

INCLUDE "nxp_rt1064_motorDriver_Release_library.ld"
INCLUDE "nxp_rt1064_motorDriver_Release_memory.ld"

ENTRY(ResetISR)

SECTIONS
{
     .text_Flash2 : ALIGN(4)
    {
       FILL(0xff)
        *(.text_Flash2) /* for compatibility with previous releases */
        *(.text_PROGRAM_FLASH_SET0) /* for compatibility with previous releases */
        *(.text.$Flash2)
        *(.text.$PROGRAM_FLASH_SET0)
        *(.text_Flash2.*) /* for compatibility with previous releases */
        *(.text_PROGRAM_FLASH_SET0.*) /* for compatibility with previous releases */
        *(.text.$Flash2.*)
        *(.text.$PROGRAM_FLASH_SET0.*)
        *(.rodata.$Flash2)
        *(.rodata.$PROGRAM_FLASH_SET0)
        *(.rodata.$Flash2.*)
        *(.rodata.$PROGRAM_FLASH_SET0.*)            } > PROGRAM_FLASH_SET0

    .text_Flash3 : ALIGN(4)
    {
       FILL(0xff)
        *(.text_Flash3) /* for compatibility with previous releases */
        *(.text_PROGRAM_FLASH_SET1) /* for compatibility with previous releases */
        *(.text.$Flash3)
        *(.text.$PROGRAM_FLASH_SET1)
        *(.text_Flash3.*) /* for compatibility with previous releases */
        *(.text_PROGRAM_FLASH_SET1.*) /* for compatibility with previous releases */
        *(.text.$Flash3.*)
        *(.text.$PROGRAM_FLASH_SET1.*)
        *(.rodata.$Flash3)
        *(.rodata.$PROGRAM_FLASH_SET1)
        *(.rodata.$Flash3.*)
        *(.rodata.$PROGRAM_FLASH_SET1.*)            } > PROGRAM_FLASH_SET1

    .text_Flash4 : ALIGN(4)
    {
       FILL(0xff)
        *(.text_Flash4) /* for compatibility with previous releases */
        *(.text_PARAMETER_FLASH) /* for compatibility with previous releases */
        *(.text.$Flash4)
        *(.text.$PARAMETER_FLASH)
        *(.text_Flash4.*) /* for compatibility with previous releases */
        *(.text_PARAMETER_FLASH.*) /* for compatibility with previous releases */
        *(.text.$Flash4.*)
        *(.text.$PARAMETER_FLASH.*)
        *(.rodata.$Flash4)
        *(.rodata.$PARAMETER_FLASH)
        *(.rodata.$Flash4.*)
        *(.rodata.$PARAMETER_FLASH.*)            } > PARAMETER_FLASH

    /* MAIN TEXT SECTION */
    .text : ALIGN(4)
    {
        FILL(0xff)
        __vectors_start__ = ABSOLUTE(.) ;
        KEEP(*(.isr_vector))
        /* Global Section Table */
        . = ALIGN(4) ;
        __section_table_start = .;
        __data_section_table = .;
        LONG(LOADADDR(.data_RAM));
        LONG(    ADDR(.data_RAM));
        LONG(  SIZEOF(.data_RAM));
        LONG(LOADADDR(.data_RAM2));
        LONG(    ADDR(.data_RAM2));
        LONG(  SIZEOF(.data_RAM2));
        LONG(LOADADDR(.data));
        LONG(    ADDR(.data));
        LONG(  SIZEOF(.data));
        LONG(LOADADDR(.data_RAM4));
        LONG(    ADDR(.data_RAM4));
        LONG(  SIZEOF(.data_RAM4));
        __data_section_table_end = .;
        __bss_section_table = .;
        LONG(    ADDR(.bss_RAM));
        LONG(  SIZEOF(.bss_RAM));
        LONG(    ADDR(.bss_RAM2));
        LONG(  SIZEOF(.bss_RAM2));
        LONG(    ADDR(.bss));
        LONG(  SIZEOF(.bss));
        LONG(    ADDR(.bss_RAM4));
        LONG(  SIZEOF(.bss_RAM4));
        __bss_section_table_end = .;
        __section_table_end = . ;
        /* End of Global Section Table */

        *(.after_vectors*)

    } > SRAM_DTC

    .text : ALIGN(4)
    {
       *(.text*)
       . = ALIGN(4);
    } > SRAM_DTC
    
    .text_const : ALIGN(4)
    {
       *(.rodata .rodata.* .constdata .constdata.*)
       . = ALIGN(4);
    } > SRAM_OC_BANK0
    /*
     * for exception handling/unwind - some Newlib functions (in common
     * with C++ and STDC++) use this.
     */
    .ARM.extab : ALIGN(4)
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > SRAM_DTC

    .ARM.exidx : ALIGN(4)
    {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } > SRAM_DTC
 
    _etext = .;
        
    /* DATA section for SRAM_DTC */

    .data_RAM : ALIGN(4)
    {
        FILL(0xff)
        PROVIDE(__start_data_RAM = .) ;
        PROVIDE(__start_data_SRAM_DTC = .) ;
        *(.ramfunc.$RAM)
        *(.ramfunc.$SRAM_DTC)
        *(.data.$RAM)
        *(.data.$SRAM_DTC)
        *(.data.$RAM.*)
        *(.data.$SRAM_DTC.*)
        . = ALIGN(4) ;
        PROVIDE(__end_data_RAM = .) ;
        PROVIDE(__end_data_SRAM_DTC = .) ;
     } > SRAM_DTC AT>SRAM_DTC

    /* DATA section for SRAM_ITC */

    .data_RAM2 : ALIGN(4)
    {
        FILL(0xff)
        PROVIDE(__start_data_RAM2 = .) ;
        PROVIDE(__start_data_SRAM_ITC = .) ;
        *(.ramfunc.$RAM2)
        *(.ramfunc.$SRAM_ITC)
        *(.data.$RAM2)
        *(.data.$SRAM_ITC)
        *(.data.$RAM2.*)
        *(.data.$SRAM_ITC.*)
        . = ALIGN(4) ;
        PROVIDE(__end_data_RAM2 = .) ;
        PROVIDE(__end_data_SRAM_ITC = .) ;
     } > SRAM_ITC AT>SRAM_DTC

    /* DATA section for SRAM_OC_BANK1 */

    .data_RAM4 : ALIGN(4)
    {
        FILL(0xff)
        PROVIDE(__start_data_RAM4 = .) ;
        PROVIDE(__start_data_SRAM_OC_BANK1 = .) ;
        *(.ramfunc.$RAM4)
        *(.ramfunc.$SRAM_OC_BANK1)
        *(.data.$RAM4)
        *(.data.$SRAM_OC_BANK1)
        *(.data.$RAM4.*)
        *(.data.$SRAM_OC_BANK1.*)
        . = ALIGN(4) ;
        PROVIDE(__end_data_RAM4 = .) ;
        PROVIDE(__end_data_SRAM_OC_BANK1 = .) ;
     } > SRAM_OC_BANK1 AT>SRAM_DTC

    /* MAIN DATA SECTION */
    .uninit_RESERVED (NOLOAD) : ALIGN(4)
    {
        _start_uninit_RESERVED = .;
        KEEP(*(.bss.$RESERVED*))
       . = ALIGN(4) ;
        _end_uninit_RESERVED = .;
    } > SRAM_OC_BANK0 AT> SRAM_OC_BANK0

    /* Main DATA section (SRAM_OC_BANK0) */
    .data : ALIGN(4)
    {
       FILL(0xff)
       _data = . ;
       PROVIDE(__start_data_RAM3 = .) ;
       PROVIDE(__start_data_SRAM_OC_BANK0 = .) ;
       *(vtable)
       *(.ramfunc*)
       KEEP(*(CodeQuickAccess))
       KEEP(*(DataQuickAccess))
       *(RamFunction)
       *(NonCacheable.init)
       *(.data*)
       . = ALIGN(4) ;
       _edata = . ;
       PROVIDE(__end_data_RAM3 = .) ;
       PROVIDE(__end_data_SRAM_OC_BANK0 = .) ;
    } > SRAM_OC_BANK0 AT>SRAM_DTC

    /* BSS section for SRAM_DTC */
    .bss_RAM : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM = .) ;
       PROVIDE(__start_bss_SRAM_DTC = .) ;
       *(.bss.$RAM)
       *(.bss.$SRAM_DTC)
       *(.bss.$RAM.*)
       *(.bss.$SRAM_DTC.*)
       . = ALIGN (. != 0 ? 4 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM = .) ;
       PROVIDE(__end_bss_SRAM_DTC = .) ;
    } > SRAM_DTC AT> SRAM_DTC

    /* BSS section for SRAM_ITC */
    .bss_RAM2 : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM2 = .) ;
       PROVIDE(__start_bss_SRAM_ITC = .) ;
       *(.bss.$RAM2)
       *(.bss.$SRAM_ITC)
       *(.bss.$RAM2.*)
       *(.bss.$SRAM_ITC.*)
       . = ALIGN (. != 0 ? 4 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM2 = .) ;
       PROVIDE(__end_bss_SRAM_ITC = .) ;
    } > SRAM_ITC AT> SRAM_ITC

    /* BSS section for SRAM_OC_BANK1 */
    .bss_RAM4 : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM4 = .) ;
       PROVIDE(__start_bss_SRAM_OC_BANK1 = .) ;
       *(.bss.$RAM4)
       *(.bss.$SRAM_OC_BANK1)
       *(.bss.$RAM4.*)
       *(.bss.$SRAM_OC_BANK1.*)
       . = ALIGN (. != 0 ? 4 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM4 = .) ;
       PROVIDE(__end_bss_SRAM_OC_BANK1 = .) ;
    } > SRAM_OC_BANK1 AT> SRAM_OC_BANK1

    /* MAIN BSS SECTION */
    .bss : ALIGN(4)
    {
        _bss = .;
        PROVIDE(__start_bss_RAM3 = .) ;
        PROVIDE(__start_bss_SRAM_OC_BANK0 = .) ;
       *(NonCacheable)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4) ;
        _ebss = .;
        PROVIDE(__end_bss_RAM3 = .) ;
        PROVIDE(__end_bss_SRAM_OC_BANK0 = .) ;
        PROVIDE(end = .);
    } > SRAM_OC_BANK0 AT> SRAM_OC_BANK0

    /* NOINIT section for SRAM_DTC */
    .noinit_RAM (NOLOAD) : ALIGN(4)
    {
       PROVIDE(__start_noinit_RAM = .) ;
       PROVIDE(__start_noinit_SRAM_DTC = .) ;
       *(.noinit.$RAM)
       *(.noinit.$SRAM_DTC)
       *(.noinit.$RAM.*)
       *(.noinit.$SRAM_DTC.*)
       . = ALIGN(4) ;
       PROVIDE(__end_noinit_RAM = .) ;
       PROVIDE(__end_noinit_SRAM_DTC = .) ;
    } > SRAM_DTC AT> SRAM_DTC

    /* NOINIT section for SRAM_ITC */
    .noinit_RAM2 (NOLOAD) : ALIGN(4)
    {
       PROVIDE(__start_noinit_RAM2 = .) ;
       PROVIDE(__start_noinit_SRAM_ITC = .) ;
       *(.noinit.$RAM2)
       *(.noinit.$SRAM_ITC)
       *(.noinit.$RAM2.*)
       *(.noinit.$SRAM_ITC.*)
       . = ALIGN(4) ;
       PROVIDE(__end_noinit_RAM2 = .) ;
       PROVIDE(__end_noinit_SRAM_ITC = .) ;
    } > SRAM_ITC AT> SRAM_ITC

    /* NOINIT section for SRAM_OC_BANK1 */
    .noinit_RAM4 (NOLOAD) : ALIGN(4)
    {
       PROVIDE(__start_noinit_RAM4 = .) ;
       PROVIDE(__start_noinit_SRAM_OC_BANK1 = .) ;
       *(.noinit.$RAM4)
       *(.noinit.$SRAM_OC_BANK1)
       *(.noinit.$RAM4.*)
       *(.noinit.$SRAM_OC_BANK1.*)
       . = ALIGN(4) ;
       PROVIDE(__end_noinit_RAM4 = .) ;
       PROVIDE(__end_noinit_SRAM_OC_BANK1 = .) ;
    } > SRAM_OC_BANK1 AT> SRAM_OC_BANK1

    /* DEFAULT NOINIT SECTION */
    .noinit (NOLOAD): ALIGN(4)
    {
        _noinit = .;
        PROVIDE(__start_noinit_RAM3 = .) ;
        PROVIDE(__start_noinit_SRAM_OC_BANK0 = .) ;
        *(.noinit*)
         . = ALIGN(4) ;
        _end_noinit = .;
       PROVIDE(__end_noinit_RAM3 = .) ;
       PROVIDE(__end_noinit_SRAM_OC_BANK0 = .) ;        
    } > SRAM_OC_BANK0 AT> SRAM_OC_BANK0

    /* Reserve and place Heap within memory map */
    _HeapSize = 0x1000;
    .heap :  ALIGN(4)
    {
        _pvHeapStart = .;
        . += _HeapSize;
        . = ALIGN(4);
        _pvHeapLimit = .;
    } > SRAM_OC_BANK0

     _StackSize = 0x1000;
     /* Reserve space in memory for Stack */
    .heap2stackfill  :
    {
        . += _StackSize;
    } > SRAM_OC_BANK0
    /* Locate actual Stack in memory map */
    .stack ORIGIN(SRAM_OC_BANK0) + LENGTH(SRAM_OC_BANK0) - _StackSize - 0:  ALIGN(4)
    {
        _vStackBase = .;
        . = ALIGN(4);
        _vStackTop = . + _StackSize;
    } > SRAM_OC_BANK0

    /* Provide basic symbols giving location and size of main text
     * block, including initial values of RW data sections. Note that
     * these will need extending to give a complete picture with
     * complex images (e.g multiple Flash banks).
     */
    _image_start = LOADADDR(.text);
    _image_end = LOADADDR(.data) + SIZEOF(.data);
    _image_size = _image_end - _image_start;
}