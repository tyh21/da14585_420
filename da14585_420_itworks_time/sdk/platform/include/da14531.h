/**
 ****************************************************************************************
 *
 * @file da14531.h
 *
 * @brief DA14531 register definitions header file.
 *
 * Copyright (C) 2019 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */

#ifndef _DA14531_H_
#define _DA14531_H_

#include <stdint.h>

/*===========================================================================*/ 
/*========================== Start of header part ===========================*/ 
/*===========================================================================*/ 
/*
* ===============================================================================================
* ---------- Interrupt ReQuest number definitions (see also CMSDK_CM0plus.h) --------------------
* ===============================================================================================
*/

/*
* -----------------------------------------------------------------------------------------------
* The Cortex-M0+ Processor Exceptions Numbers and Device Specific Interrupt Request Numbers.    -
* -----------------------------------------------------------------------------------------------
*/
typedef enum IRQn
{
/****** Cortex-M0+ Processor Exceptions Numbers ************************************************/
NonMaskableInt_IRQn  = -14, /*  2 Non Maskable Interrupt Request.                              */
HardFault_IRQn       = -13, /*  3 Cortex-M0 Hard Fault Interrupt Request.                      */
SVCall_IRQn          = -5,  /* 11 Cortex-M0 SV Call Interrupt Request.                         */
PendSV_IRQn          = -2,  /* 14 Cortex-M0 Pend SV Interrupt Request.                         */
SysTick_IRQn         = -1,  /* 15 Cortex-M0 System Tick Interrupt Request.                     */

/****** D2632 Specific Interrupt Numbers *******************************************************/
BLE_WAKEUP_LP_IRQn   =  0,  /* Wakeup from Low Power Interrupt Request from BLE.               */
BLE_GEN_IRQn         =  1,  /* BLE Interrupt Request. Sources:                                 */
                            /*   - finetgtim_irq  : Fine Target Timer interrupt generated when */
                            /*                      Fine Target timer expired. Timer           */
                            /*                      resolution is 625us base time reference.   */
                            /*   - grosstgtim_irq : Gross Target Timer interrupt generated     */
                            /*                      when Gross Target timer expired. Timer     */
                            /*                      resolution is 16 times 625us base time     */
                            /*                      reference.                                 */
                            /*   - cscnt_irq      : 625us base time reference interrupt,       */
                            /*                      available in active modes.                 */
                            /*   - slp_irq        : End of Sleep mode interrupt.               */
                            /*   - error_irq      : Error interrupt, generated when undesired  */
                            /*                      behavior or bad programming occurs in the  */
                            /*                      BLE Core.                                  */
                            /*   - rx_irq         : Receipt interrupt at the end of each       */
                            /*                      received packets.                          */
                            /*   - event_irq      : End of Advertising / Scanning / Connection */
                            /*                      events interrupt.                          */
                            /*   - crypt_irq      : Encryption / Decryption interrupt,         */
                            /*                      generated either when AES and/or CCM       */
                            /*                      processing is finished.                    */
                            /*   - sw_irq         : SW triggered interrupt, generated on SW    */
                            /*                      request.                                   */
UART_IRQn            =  2,  /* UART Interrupt Request.                                         */
UART2_IRQn           =  3,  /* UART2 Interrupt Request.                                        */
I2C_IRQn             =  4,  /* I2C Interrupt Request.                                          */
SPI_IRQn             =  5,  /* SPI Interrupt Request.                                          */
ADC_IRQn             =  6,  /* Analog-Digital Converter Interrupt Request.                     */
KEYBRD_IRQn          =  7,  /* Keyboard Interrupt Request.                                     */
BLE_RF_DIAG_IRQn     =  8,  /* Baseband or Radio Diagnostics Interrupt Request. Required for   */
                            /* signaling Radio or Baseband internal events.                    */
                            /* 2 signals per Radio and 2 per BB                                */
RF_CAL_IRQn          =  9,  /* Radio Calibration Interrupt Request.                            */
GPIO0_IRQn           = 10,  /* GPIO Interrupt Request through debounce.                        */
GPIO1_IRQn           = 11,  /* GPIO Interrupt Request through debounce.                        */
GPIO2_IRQn           = 12,  /* GPIO Interrupt Request through debounce.                        */
GPIO3_IRQn           = 13,  /* GPIO Interrupt Request through debounce.                        */
GPIO4_IRQn           = 14,  /* GPIO Interrupt Request through debounce.                        */
SWTIM_IRQn           = 15,  /* Software Timer (Timer0) Interrupt Request.                      */
WKUP_QUADEC_IRQn     = 16,  /* Combines the Wake up Capture Timer Interrupt Request,           */
                            /* the GPIO Interrupt and the QuadDecoder Interrupt Request.       */
SWTIM1_IRQn          = 17,  /* Software Timer (Timer1) Interrupt Request.                      */
RTC_IRQn             = 18,  /* RTC Alarm Interrupt Request.                                    */
DMA_IRQn             = 19,  /* DMA Interrupt Request.                                          */
XTAL32M_RDY_IRQn     = 20,  /* XTAL 32M settling Interrupt Request.                            */
RESERVED21_IRQn      = 21,  /* SoftWare Interrupt Request.                                     */
RESERVED22_IRQn      = 22,  /* SoftWare Interrupt Request.                                     */
RESERVED23_IRQn      = 23,  /* SoftWare Interrupt Request.                                     */
} IRQn_Type;


/*---------------------------------------------------------------------------------------------*/
/* Configuration of the Cortex-M0+ Processor and Core Peripherals (see also CMSDK_CM0plus.h).  */
/*---------------------------------------------------------------------------------------------*/
/* Note: The next 4 defines are used in the global included "core_cm0plus.h".                  */
#define __NVIC_PRIO_BITS       (2) /* Number of Bits used for Priority Levels.                 */
#define __Vendor_SysTickConfig (0) /* Set to 1 if different SysTick Config is used.            */
#define __MPU_PRESENT           0  /* MPU present or not.                                      */
/* Allow a different '__VTOR_PRESENT' value for e.g. the CM0+ config check test.               */
#ifndef __VTOR_PRESENT
  #define __VTOR_PRESENT        0  /* Cortex-M0+ can support the VTOR.                         */
#endif

/*--GPIO PID functions-------------------------------------------------------------------------*/
#define FUNC_GPIO          ( 0)
#define FUNC_UART_RX       ( 1)
#define FUNC_UART_TX       ( 2)
#define FUNC_UART2_RX      ( 3)
#define FUNC_UART2_TX      ( 4)
#define FUNC_SYS_CLK       ( 5)
#define FUNC_LP_CLK        ( 6)
#define FUNC_I2C_SCL       ( 9)
#define FUNC_I2C_SDA       (10)
#define FUNC_PWM5          (11)
#define FUNC_PWM6          (12)
#define FUNC_PWM7          (13)
#define FUNC_ADC           (15)
#define FUNC_PWM0          (16)
#define FUNC_PWM1          (17)
#define FUNC_BLE_DIAG      (18)
#define FUNC_UART_CTSN     (19)
#define FUNC_UART_RTSN     (20)
#define FUNC_PWM2          (23)
#define FUNC_PWM3          (24)
#define FUNC_PWM4          (25)
#define FUNC_SPI_DI        (26)
#define FUNC_SPI_DO        (27)
#define FUNC_SPI_CLK       (28)
#define FUNC_SPI_CSN0      (29)
#define FUNC_SPI_CSN1      (30)
/*--GPIO Direction settings--------------------------------------------------------------------*/
#define DIR_INPUT          0x000
#define DIR_PULLUP         0x100
#define DIR_PULLDOWN       0x200
#define DIR_OUTPUT         0x300


/*===========================================================================*/ 
/*=========================== End of header part ============================*/ 
/*===========================================================================*/ 



/*===========================================================================*/ 
/*==================== Start of automatic generated code ====================*/ 
/*===========================================================================*/ 



/*===========================================================================*/
/* memory map ADPLLDIG */
/*===========================================================================*/
//reserved only



/*===========================================================================*/
/* memory map anamisc2632_bif_00 */
/*===========================================================================*/



#define CLK_REF_SEL_REG                      (0x50001600) /* Select clock for oscillator calibration */
#define CLK_REF_SEL_REG_RESET                (0x00000000)

/*=============================*/
struct __CLK_REF_SEL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_REF_CLK_SEL                       : 2;
    volatile uint16_t BITFLD_REF_CAL_START                     : 1;
    volatile uint16_t BITFLD_EXT_CNT_EN_SEL                    : 1;
};
#define REF_CLK_SEL                           (0x0003)
#define REF_CAL_START                         (0x0004)
#define EXT_CNT_EN_SEL                        (0x0008)



#define CLK_REF_CNT_REG                      (0x50001602) /* Count value for oscillator calibration */
#define CLK_REF_CNT_REG_RESET                (0x00000000)

/*=============================*/
struct __CLK_REF_CNT_REG
/*=============================*/
{
    volatile uint16_t BITFLD_REF_CNT_VAL                       : 16;
};
#define REF_CNT_VAL                           (0xFFFF)



#define CLK_REF_VAL_L_REG                    (0x50001604) /* XTAL32M reference cycles, lower 16 bits */
#define CLK_REF_VAL_L_REG_RESET              (0x00000000)

/*=============================*/
struct __CLK_REF_VAL_L_REG
/*=============================*/
{
    volatile uint16_t BITFLD_XTAL_CNT_VAL                      : 16;
};
#define XTAL_CNT_VAL                          (0xFFFF)



#define CLK_REF_VAL_H_REG                    (0x50001606) /* XTAL32M reference cycles, higher 16 bits */
#define CLK_REF_VAL_H_REG_RESET              (0x00000000)

/*=============================*/
struct __CLK_REF_VAL_H_REG
/*=============================*/
{
    volatile uint16_t BITFLD_XTAL_CNT_VAL                      : 16;
};
#define XTAL_CNT_VAL                          (0xFFFF)



/*===========================================================================*/
/* memory map bistctrl2632_ram_00 */
/*===========================================================================*/



#define MBIST_SRAM12_ADDR_REG                (0x50003700) /*  */
#define MBIST_SRAM12_ADDR_REG_RESET          (0x00000000)

/*=============================*/
struct __MBIST_SRAM12_ADDR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_MBIST_ADDR                        : 1;
};
#define MBIST_ADDR                            (0x0001)



#define MBIST_SRAM12_STATE_REG               (0x50003702) /*  */
#define MBIST_SRAM12_STATE_REG_RESET         (0x00000000)

/*=============================*/
struct __MBIST_SRAM12_STATE_REG
/*=============================*/
{
    volatile uint16_t BITFLD_MBIST_STATE                       : 1;
};
#define MBIST_STATE                           (0x0001)



#define MBIST_SRAM12_RD_MSB_REG              (0x50003704) /*  */
#define MBIST_SRAM12_RD_MSB_REG_RESET        (0x00000000)

/*=============================*/
struct __MBIST_SRAM12_RD_MSB_REG
/*=============================*/
{
    volatile uint16_t BITFLD_MBIST_MSB_DATA                    : 1;
};
#define MBIST_MSB_DATA                        (0x0001)



#define MBIST_SRAM12_RD_LSB_REG              (0x50003706) /*  */
#define MBIST_SRAM12_RD_LSB_REG_RESET        (0x00000000)

/*=============================*/
struct __MBIST_SRAM12_RD_LSB_REG
/*=============================*/
{
    volatile uint16_t BITFLD_MBIST_LSB_DATA                    : 1;
};
#define MBIST_LSB_DATA                        (0x0001)



#define MBIST_SRAM3_ADDR_REG                 (0x50003800) /*  */
#define MBIST_SRAM3_ADDR_REG_RESET           (0x00000000)

/*=============================*/
struct __MBIST_SRAM3_ADDR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_MBIST_ADDR                        : 1;
};
#define MBIST_ADDR                            (0x0001)



#define MBIST_SRAM3_STATE_REG                (0x50003802) /*  */
#define MBIST_SRAM3_STATE_REG_RESET          (0x00000000)

/*=============================*/
struct __MBIST_SRAM3_STATE_REG
/*=============================*/
{
    volatile uint16_t BITFLD_MBIST_STATE                       : 1;
};
#define MBIST_STATE                           (0x0001)



#define MBIST_SRAM3_RD_MSB_REG               (0x50003804) /*  */
#define MBIST_SRAM3_RD_MSB_REG_RESET         (0x00000000)

/*=============================*/
struct __MBIST_SRAM3_RD_MSB_REG
/*=============================*/
{
    volatile uint16_t BITFLD_MBIST_MSB_DATA                    : 1;
};
#define MBIST_MSB_DATA                        (0x0001)



#define MBIST_SRAM3_RD_LSB_REG               (0x50003806) /*  */
#define MBIST_SRAM3_RD_LSB_REG_RESET         (0x00000000)

/*=============================*/
struct __MBIST_SRAM3_RD_LSB_REG
/*=============================*/
{
    volatile uint16_t BITFLD_MBIST_LSB_DATA                    : 1;
};
#define MBIST_LSB_DATA                        (0x0001)



/*===========================================================================*/
/* memory map BLE */
/*===========================================================================*/



#define BLE_RWBLECNTL_REG                    (0x40000000) /* BLE Control register */
#define BLE_RWBLECNTL_REG_RESET              (0x00000000)

/*=============================*/
struct __BLE_RWBLECNTL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SYNCERR                           : 3;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_RXWINSZDEF                        : 4;
    volatile uint32_t BITFLD_RWBLE_EN                          : 1;
    volatile uint32_t BITFLD_ADVERTFILT_EN                     : 1;
    volatile uint32_t                                          : 2;
    volatile uint32_t                                          : 2;
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_HOP_REMAP_DSB                     : 1;
    volatile uint32_t BITFLD_CRC_DSB                           : 1;
    volatile uint32_t BITFLD_WHIT_DSB                          : 1;
    volatile uint32_t BITFLD_CRYPT_DSB                         : 1;
    volatile uint32_t BITFLD_NESN_DSB                          : 1;
    volatile uint32_t BITFLD_SN_DSB                            : 1;
    volatile uint32_t BITFLD_MD_DSB                            : 1;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_SCAN_ABORT                        : 1;
    volatile uint32_t BITFLD_ADVERT_ABORT                      : 1;
    volatile uint32_t BITFLD_RFTEST_ABORT                      : 1;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_SWINT_REQ                         : 1;
    volatile uint32_t BITFLD_REG_SOFT_RST                      : 1;
    volatile uint32_t BITFLD_MASTER_TGSOFT_RST                 : 1;
    volatile uint32_t BITFLD_MASTER_SOFT_RST                   : 1;
};
#define SYNCERR                               (0x0007)
#define RXWINSZDEF                            (0x00F0)
#define RWBLE_EN                              (0x0100)
#define ADVERTFILT_EN                         (0x0200)
#define HOP_REMAP_DSB                         (0x10000)
#define CRC_DSB                               (0x20000)
#define WHIT_DSB                              (0x40000)
#define CRYPT_DSB                             (0x80000)
#define NESN_DSB                              (0x100000)
#define SN_DSB                                (0x200000)
#define MD_DSB                                (0x400000)
#define SCAN_ABORT                            (0x1000000)
#define ADVERT_ABORT                          (0x2000000)
#define RFTEST_ABORT                          (0x4000000)
#define SWINT_REQ                             (0x10000000)
#define REG_SOFT_RST                          (0x20000000)
#define MASTER_TGSOFT_RST                     (0x40000000)
#define MASTER_SOFT_RST                       (0x80000000)



#define BLE_VERSION_REG                      (0x40000004) /* Version register */
#define BLE_VERSION_REG_RESET                (0x07010000)

/*=============================*/
struct __BLE_VERSION_REG
/*=============================*/
{
    volatile uint32_t BITFLD_BUILD                             : 8;
    volatile uint32_t BITFLD_UPG                               : 8;
    volatile uint32_t BITFLD_REL                               : 8;
    volatile uint32_t BITFLD_TYP                               : 8;
};
#define BUILD                                 (0x00FF)
#define UPG                                   (0xFF00)
#define REL                                   (0xFF0000)
#define TYP                                   (0xFF000000)



#define BLE_RWBLECONF_REG                    (0x40000008) /* Configuration register */
#define BLE_RWBLECONF_REG_RESET              (0x0F02001F)

/*=============================*/
struct __BLE_RWBLECONF_REG
/*=============================*/
{
    volatile uint32_t BITFLD_BUSWIDTH                          : 1;
    volatile uint32_t BITFLD_USECRYPT                          : 1;
    volatile uint32_t BITFLD_USEDBG                            : 1;
    volatile uint32_t BITFLD_COEX                              : 1;
    volatile uint32_t BITFLD_INTMODE                           : 1;
    volatile uint32_t BITFLD_DMMODE                            : 1;
    volatile uint32_t BITFLD_DECIPHER                          : 1;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_CLK_SEL                           : 6;
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_RFIF                              : 7;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_ADD_WIDTH                         : 6;
};
#define BUSWIDTH                              (0x0001)
#define USECRYPT                              (0x0002)
#define USEDBG                                (0x0004)
#define COEX                                  (0x0008)
#define INTMODE                               (0x0010)
#define DMMODE                                (0x0020)
#define DECIPHER                              (0x0040)
#define CLK_SEL                               (0x3F00)
#define RFIF                                  (0x7F0000)
#define ADD_WIDTH                             (0x3F000000)



#define BLE_INTCNTL_REG                      (0x4000000C) /* Interrupt controller register */
#define BLE_INTCNTL_REG_RESET                (0x0000811F)

/*=============================*/
struct __BLE_INTCNTL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_CSCNTINTMSK                       : 1;
    volatile uint32_t BITFLD_RXINTMSK                          : 1;
    volatile uint32_t BITFLD_SLPINTMSK                         : 1;
    volatile uint32_t BITFLD_EVENTINTMSK                       : 1;
    volatile uint32_t BITFLD_CRYPTINTMSK                       : 1;
    volatile uint32_t BITFLD_ERRORINTMSK                       : 1;
    volatile uint32_t BITFLD_GROSSTGTIMINTMSK                  : 1;
    volatile uint32_t BITFLD_FINETGTIMINTMSK                   : 1;
    volatile uint32_t BITFLD_EVENTAPFAINTMSK                   : 1;
    volatile uint32_t BITFLD_SWINTMSK                          : 1;
    volatile uint32_t                                          : 5;
    volatile uint32_t BITFLD_CSCNTDEVMSK                       : 1;
};
#define CSCNTINTMSK                           (0x0001)
#define RXINTMSK                              (0x0002)
#define SLPINTMSK                             (0x0004)
#define EVENTINTMSK                           (0x0008)
#define CRYPTINTMSK                           (0x0010)
#define ERRORINTMSK                           (0x0020)
#define GROSSTGTIMINTMSK                      (0x0040)
#define FINETGTIMINTMSK                       (0x0080)
#define EVENTAPFAINTMSK                       (0x0100)
#define SWINTMSK                              (0x0200)
#define CSCNTDEVMSK                           (0x8000)



#define BLE_INTSTAT_REG                      (0x40000010) /* Interrupt status register */
#define BLE_INTSTAT_REG_RESET                (0x00000000)

/*=============================*/
struct __BLE_INTSTAT_REG
/*=============================*/
{
    volatile uint32_t BITFLD_CSCNTINTSTAT                      : 1;
    volatile uint32_t BITFLD_RXINTSTAT                         : 1;
    volatile uint32_t BITFLD_SLPINTSTAT                        : 1;
    volatile uint32_t BITFLD_EVENTINTSTAT                      : 1;
    volatile uint32_t BITFLD_CRYPTINTSTAT                      : 1;
    volatile uint32_t BITFLD_ERRORINTSTAT                      : 1;
    volatile uint32_t BITFLD_GROSSTGTIMINTSTAT                 : 1;
    volatile uint32_t BITFLD_FINETGTIMINTSTAT                  : 1;
    volatile uint32_t BITFLD_EVENTAPFAINTSTAT                  : 1;
    volatile uint32_t BITFLD_SWINTSTAT                         : 1;
};
#define CSCNTINTSTAT                          (0x0001)
#define RXINTSTAT                             (0x0002)
#define SLPINTSTAT                            (0x0004)
#define EVENTINTSTAT                          (0x0008)
#define CRYPTINTSTAT                          (0x0010)
#define ERRORINTSTAT                          (0x0020)
#define GROSSTGTIMINTSTAT                     (0x0040)
#define FINETGTIMINTSTAT                      (0x0080)
#define EVENTAPFAINTSTAT                      (0x0100)
#define SWINTSTAT                             (0x0200)



#define BLE_INTRAWSTAT_REG                   (0x40000014) /* Interrupt raw status register */
#define BLE_INTRAWSTAT_REG_RESET             (0x00000000)

/*=============================*/
struct __BLE_INTRAWSTAT_REG
/*=============================*/
{
    volatile uint32_t BITFLD_CSCNTINTRAWSTAT                   : 1;
    volatile uint32_t BITFLD_RXINTRAWSTAT                      : 1;
    volatile uint32_t BITFLD_SLPINTRAWSTAT                     : 1;
    volatile uint32_t BITFLD_EVENTINTRAWSTAT                   : 1;
    volatile uint32_t BITFLD_CRYPTINTRAWSTAT                   : 1;
    volatile uint32_t BITFLD_ERRORINTRAWSTAT                   : 1;
    volatile uint32_t BITFLD_GROSSTGTIMINTRAWSTAT              : 1;
    volatile uint32_t BITFLD_FINETGTIMINTRAWSTAT               : 1;
    volatile uint32_t BITFLD_EVENTAPFAINTRAWSTAT               : 1;
    volatile uint32_t BITFLD_SWINTRAWSTAT                      : 1;
};
#define CSCNTINTRAWSTAT                       (0x0001)
#define RXINTRAWSTAT                          (0x0002)
#define SLPINTRAWSTAT                         (0x0004)
#define EVENTINTRAWSTAT                       (0x0008)
#define CRYPTINTRAWSTAT                       (0x0010)
#define ERRORINTRAWSTAT                       (0x0020)
#define GROSSTGTIMINTRAWSTAT                  (0x0040)
#define FINETGTIMINTRAWSTAT                   (0x0080)
#define EVENTAPFAINTRAWSTAT                   (0x0100)
#define SWINTRAWSTAT                          (0x0200)



#define BLE_INTACK_REG                       (0x40000018) /* Interrupt acknowledge register */
#define BLE_INTACK_REG_RESET                 (0x00000000)

/*=============================*/
struct __BLE_INTACK_REG
/*=============================*/
{
    volatile uint32_t BITFLD_CSCNTINTACK                       : 1;
    volatile uint32_t BITFLD_RXINTACK                          : 1;
    volatile uint32_t BITFLD_SLPINTACK                         : 1;
    volatile uint32_t BITFLD_EVENTINTACK                       : 1;
    volatile uint32_t BITFLD_CRYPTINTACK                       : 1;
    volatile uint32_t BITFLD_ERRORINTACK                       : 1;
    volatile uint32_t BITFLD_GROSSTGTIMINTACK                  : 1;
    volatile uint32_t BITFLD_FINETGTIMINTACK                   : 1;
    volatile uint32_t BITFLD_EVENTAPFAINTACK                   : 1;
    volatile uint32_t BITFLD_SWINTACK                          : 1;
};
#define CSCNTINTACK                           (0x0001)
#define RXINTACK                              (0x0002)
#define SLPINTACK                             (0x0004)
#define EVENTINTACK                           (0x0008)
#define CRYPTINTACK                           (0x0010)
#define ERRORINTACK                           (0x0020)
#define GROSSTGTIMINTACK                      (0x0040)
#define FINETGTIMINTACK                       (0x0080)
#define EVENTAPFAINTACK                       (0x0100)
#define SWINTACK                              (0x0200)



#define BLE_BASETIMECNT_REG                  (0x4000001C) /* Base time reference counter */
#define BLE_BASETIMECNT_REG_RESET            (0x00000000)

/*=============================*/
struct __BLE_BASETIMECNT_REG
/*=============================*/
{
    volatile uint32_t BITFLD_BASETIMECNT                       : 27;
};
#define BASETIMECNT                           (0x7FFFFFF)



#define BLE_FINETIMECNT_REG                  (0x40000020) /* Fine time reference counter */
#define BLE_FINETIMECNT_REG_RESET            (0x00000000)

/*=============================*/
struct __BLE_FINETIMECNT_REG
/*=============================*/
{
    volatile uint32_t BITFLD_FINECNT                           : 10;
};
#define FINECNT                               (0x03FF)



#define BLE_BDADDRL_REG                      (0x40000024) /* BLE device address LSB register */
#define BLE_BDADDRL_REG_RESET                (0x00000000)

/*=============================*/
struct __BLE_BDADDRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_BDADDRL                           : 32;
};
#define BDADDRL                               (0xFFFFFFFF)



#define BLE_BDADDRU_REG                      (0x40000028) /* BLE device address MSB register */
#define BLE_BDADDRU_REG_RESET                (0x00000000)

/*=============================*/
struct __BLE_BDADDRU_REG
/*=============================*/
{
    volatile uint32_t BITFLD_BDADDRU                           : 16;
    volatile uint32_t BITFLD_PRIV_NPUB                         : 1;
};
#define BDADDRU                               (0xFFFF)
#define PRIV_NPUB                             (0x10000)



#define BLE_CURRENTRXDESCPTR_REG             (0x4000002C) /* Rx Descriptor Pointer for the Receive Buffer Chained List */
#define BLE_CURRENTRXDESCPTR_REG_RESET       (0x00000000)

/*=============================*/
struct __BLE_CURRENTRXDESCPTR_REG
/*=============================*/
{
    volatile uint32_t BITFLD_CURRENTRXDESCPTR                  : 15;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_ETPTR                             : 16;
};
#define CURRENTRXDESCPTR                      (0x7FFF)
#define ETPTR                                 (0xFFFF0000)



#define BLE_DEEPSLCNTL_REG                   (0x40000030) /* Deep-Sleep control register */
#define BLE_DEEPSLCNTL_REG_RESET             (0x00000000)

/*=============================*/
struct __BLE_DEEPSLCNTL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_DEEP_SLEEP_IRQ_EN                 : 2;
    volatile uint32_t BITFLD_DEEP_SLEEP_ON                     : 1;
    volatile uint32_t BITFLD_DEEP_SLEEP_CORR_EN                : 1;
    volatile uint32_t BITFLD_SOFT_WAKEUP_REQ                   : 1;
    volatile uint32_t                                          : 10;
    volatile uint32_t BITFLD_DEEP_SLEEP_STAT                   : 1;
    volatile uint32_t                                          : 15;
    volatile uint32_t BITFLD_EXTWKUPDSB                        : 1;
};
#define DEEP_SLEEP_IRQ_EN                     (0x0003)
#define DEEP_SLEEP_ON                         (0x0004)
#define DEEP_SLEEP_CORR_EN                    (0x0008)
#define SOFT_WAKEUP_REQ                       (0x0010)
#define DEEP_SLEEP_STAT                       (0x8000)
#define EXTWKUPDSB                            (0x80000000)



#define BLE_DEEPSLWKUP_REG                   (0x40000034) /* Time (measured in Low Power clock cycles) in Deep Sleep Mode before waking-up the device */
#define BLE_DEEPSLWKUP_REG_RESET             (0x00000000)

/*=============================*/
struct __BLE_DEEPSLWKUP_REG
/*=============================*/
{
    volatile uint32_t BITFLD_DEEPSLTIME                        : 32;
};
#define DEEPSLTIME                            (0xFFFFFFFF)



#define BLE_DEEPSLSTAT_REG                   (0x40000038) /* Duration of the last deep sleep phase register */
#define BLE_DEEPSLSTAT_REG_RESET             (0x00000000)

/*=============================*/
struct __BLE_DEEPSLSTAT_REG
/*=============================*/
{
    volatile uint32_t BITFLD_DEEPSLDUR                         : 32;
};
#define DEEPSLDUR                             (0xFFFFFFFF)



#define BLE_ENBPRESET_REG                    (0x4000003C) /* Time in low power oscillator cycles register */
#define BLE_ENBPRESET_REG_RESET              (0x00000000)

/*=============================*/
struct __BLE_ENBPRESET_REG
/*=============================*/
{
    volatile uint32_t BITFLD_TWIRQ_RESET                       : 10;
    volatile uint32_t BITFLD_TWIRQ_SET                         : 11;
    volatile uint32_t BITFLD_TWEXT                             : 11;
};
#define TWIRQ_RESET                           (0x03FF)
#define TWIRQ_SET                             (0x1FFC00)
#define TWEXT                                 (0xFFE00000)



#define BLE_FINECNTCORR_REG                  (0x40000040) /* Phase correction value register */
#define BLE_FINECNTCORR_REG_RESET            (0x00000000)

/*=============================*/
struct __BLE_FINECNTCORR_REG
/*=============================*/
{
    volatile uint32_t BITFLD_FINECNTCORR                       : 10;
};
#define FINECNTCORR                           (0x03FF)



#define BLE_BASETIMECNTCORR_REG              (0x40000044) /* Base Time Counter */
#define BLE_BASETIMECNTCORR_REG_RESET        (0x00000000)

/*=============================*/
struct __BLE_BASETIMECNTCORR_REG
/*=============================*/
{
    volatile uint32_t BITFLD_BASETIMECNTCORR                   : 27;
};
#define BASETIMECNTCORR                       (0x7FFFFFF)



#define BLE_DIAGCNTL_REG                     (0x40000050) /* Diagnostics Register */
#define BLE_DIAGCNTL_REG_RESET               (0x00000000)

/*=============================*/
struct __BLE_DIAGCNTL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_DIAG0                             : 6;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_DIAG0_EN                          : 1;
    volatile uint32_t BITFLD_DIAG1                             : 6;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_DIAG1_EN                          : 1;
    volatile uint32_t BITFLD_DIAG2                             : 6;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_DIAG2_EN                          : 1;
    volatile uint32_t BITFLD_DIAG3                             : 6;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_DIAG3_EN                          : 1;
};
#define DIAG0                                 (0x003F)
#define DIAG0_EN                              (0x0080)
#define DIAG1                                 (0x3F00)
#define DIAG1_EN                              (0x8000)
#define DIAG2                                 (0x3F0000)
#define DIAG2_EN                              (0x800000)
#define DIAG3                                 (0x3F000000)
#define DIAG3_EN                              (0x80000000)



#define BLE_DIAGSTAT_REG                     (0x40000054) /* Debug use only */
#define BLE_DIAGSTAT_REG_RESET               (0x00000000)

/*=============================*/
struct __BLE_DIAGSTAT_REG
/*=============================*/
{
    volatile uint32_t BITFLD_DIAG0STAT                         : 8;
    volatile uint32_t BITFLD_DIAG1STAT                         : 8;
    volatile uint32_t BITFLD_DIAG2STAT                         : 8;
    volatile uint32_t BITFLD_DIAG3STAT                         : 8;
};
#define DIAG0STAT                             (0x00FF)
#define DIAG1STAT                             (0xFF00)
#define DIAG2STAT                             (0xFF0000)
#define DIAG3STAT                             (0xFF000000)



#define BLE_DEBUGADDMAX_REG                  (0x40000058) /* Upper limit for the memory zone */
#define BLE_DEBUGADDMAX_REG_RESET            (0x00000000)

/*=============================*/
struct __BLE_DEBUGADDMAX_REG
/*=============================*/
{
    volatile uint32_t BITFLD_EM_ADDMAX                         : 16;
    volatile uint32_t BITFLD_REG_ADDMAX                        : 16;
};
#define EM_ADDMAX                             (0xFFFF)
#define REG_ADDMAX                            (0xFFFF0000)



#define BLE_DEBUGADDMIN_REG                  (0x4000005C) /* Lower limit for the memory zone */
#define BLE_DEBUGADDMIN_REG_RESET            (0x00000000)

/*=============================*/
struct __BLE_DEBUGADDMIN_REG
/*=============================*/
{
    volatile uint32_t BITFLD_EM_ADDMIN                         : 16;
    volatile uint32_t BITFLD_REG_ADDMIN                        : 16;
};
#define EM_ADDMIN                             (0xFFFF)
#define REG_ADDMIN                            (0xFFFF0000)



#define BLE_ERRORTYPESTAT_REG                (0x40000060) /* Error Type Status registers */
#define BLE_ERRORTYPESTAT_REG_RESET          (0x00000000)

/*=============================*/
struct __BLE_ERRORTYPESTAT_REG
/*=============================*/
{
    volatile uint32_t BITFLD_TXCRYPT_ERROR                     : 1;
    volatile uint32_t BITFLD_RXCRYPT_ERROR                     : 1;
    volatile uint32_t BITFLD_PKTCNTL_EMACC_ERROR               : 1;
    volatile uint32_t BITFLD_RADIO_EMACC_ERROR                 : 1;
    volatile uint32_t BITFLD_EVT_SCHDL_EMACC_ERROR             : 1;
    volatile uint32_t BITFLD_EVT_SCHDL_ENTRY_ERROR             : 1;
    volatile uint32_t BITFLD_EVT_SCHDL_APFM_ERROR              : 1;
    volatile uint32_t BITFLD_EVT_CNTL_APFM_ERROR               : 1;
    volatile uint32_t BITFLD_WHITELIST_ERROR                   : 1;
    volatile uint32_t BITFLD_IFS_UNDERRUN                      : 1;
    volatile uint32_t BITFLD_ADV_UNDERRUN                      : 1;
    volatile uint32_t BITFLD_LLCHMAP_ERROR                     : 1;
    volatile uint32_t BITFLD_CSFORMAT_ERROR                    : 1;
    volatile uint32_t BITFLD_TXDESC_EMPTY_ERROR                : 1;
    volatile uint32_t BITFLD_RXDESC_EMPTY_ERROR                : 1;
    volatile uint32_t BITFLD_TXDATA_PTR_ERROR                  : 1;
    volatile uint32_t BITFLD_RXDATA_PTR_ERROR                  : 1;
    volatile uint32_t BITFLD_CONCEVTIRQ_ERROR                  : 1;
};
#define TXCRYPT_ERROR                         (0x0001)
#define RXCRYPT_ERROR                         (0x0002)
#define PKTCNTL_EMACC_ERROR                   (0x0004)
#define RADIO_EMACC_ERROR                     (0x0008)
#define EVT_SCHDL_EMACC_ERROR                 (0x0010)
#define EVT_SCHDL_ENTRY_ERROR                 (0x0020)
#define EVT_SCHDL_APFM_ERROR                  (0x0040)
#define EVT_CNTL_APFM_ERROR                   (0x0080)
#define WHITELIST_ERROR                       (0x0100)
#define IFS_UNDERRUN                          (0x0200)
#define ADV_UNDERRUN                          (0x0400)
#define LLCHMAP_ERROR                         (0x0800)
#define CSFORMAT_ERROR                        (0x1000)
#define TXDESC_EMPTY_ERROR                    (0x2000)
#define RXDESC_EMPTY_ERROR                    (0x4000)
#define TXDATA_PTR_ERROR                      (0x8000)
#define RXDATA_PTR_ERROR                      (0x10000)
#define CONCEVTIRQ_ERROR                      (0x20000)



#define BLE_SWPROFILING_REG                  (0x40000064) /* Software Profiling register */
#define BLE_SWPROFILING_REG_RESET            (0x00000000)

/*=============================*/
struct __BLE_SWPROFILING_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SWPROFVAL                         : 32;
};
#define SWPROFVAL                             (0xFFFFFFFF)



#define BLE_RADIOCNTL0_REG                   (0x40000070) /* Radio interface control register */
#define BLE_RADIOCNTL0_REG_RESET             (0x00000002)
//register BLE_RADIOCNTL0_REG found for which all fields are reserved, omitting.



#define BLE_RADIOCNTL1_REG                   (0x40000074) /* Radio interface control register */
#define BLE_RADIOCNTL1_REG_RESET             (0x00000000)

/*=============================*/
struct __BLE_RADIOCNTL1_REG
/*=============================*/
{
    volatile uint32_t                                          : 16;
    volatile uint32_t BITFLD_XRFSEL                            : 5;
};
#define XRFSEL                                (0x1F0000)



#define BLE_RADIOCNTL2_REG                   (0x40000078) /* Radio interface control register */
#define BLE_RADIOCNTL2_REG_RESET             (0x00000000)
//register BLE_RADIOCNTL2_REG found for which all fields are reserved, omitting.



#define BLE_RADIOCNTL3_REG                   (0x4000007C) /* Radio interface control register */
#define BLE_RADIOCNTL3_REG_RESET             (0x00000040)
//register BLE_RADIOCNTL3_REG found for which all fields are reserved, omitting.



#define BLE_RADIOPWRUPDN_REG                 (0x40000080) /* RX/TX power up/down phase register */
#define BLE_RADIOPWRUPDN_REG_RESET           (0x00D203D2)

/*=============================*/
struct __BLE_RADIOPWRUPDN_REG
/*=============================*/
{
    volatile uint32_t BITFLD_TXPWRUP                           : 8;
    volatile uint32_t BITFLD_TXPWRDN                           : 4;
    volatile uint32_t                                          : 4;
    volatile uint32_t BITFLD_RXPWRUP                           : 8;
    volatile uint32_t BITFLD_RTRIP_DELAY                       : 7;
};
#define TXPWRUP                               (0x00FF)
#define TXPWRDN                               (0x0F00)
#define RXPWRUP                               (0xFF0000)
#define RTRIP_DELAY                           (0x7F000000)



#define BLE_ADVTIM_REG                       (0x400000A0) /* Advertising Packet Interval */
#define BLE_ADVTIM_REG_RESET                 (0x00000000)

/*=============================*/
struct __BLE_ADVTIM_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ADVINT                            : 14;
};
#define ADVINT                                (0x3FFF)



#define BLE_ACTSCANSTAT_REG                  (0x400000A4) /* Active scan register */
#define BLE_ACTSCANSTAT_REG_RESET            (0x00010001)

/*=============================*/
struct __BLE_ACTSCANSTAT_REG
/*=============================*/
{
    volatile uint32_t BITFLD_UPPERLIMIT                        : 9;
    volatile uint32_t                                          : 7;
    volatile uint32_t BITFLD_BACKOFF                           : 9;
};
#define UPPERLIMIT                            (0x01FF)
#define BACKOFF                               (0x1FF0000)



#define BLE_WLPUBADDPTR_REG                  (0x400000B0) /* Start address of public devices list */
#define BLE_WLPUBADDPTR_REG_RESET            (0x00000000)

/*=============================*/
struct __BLE_WLPUBADDPTR_REG
/*=============================*/
{
    volatile uint32_t BITFLD_WLPUBADDPTR                       : 16;
};
#define WLPUBADDPTR                           (0xFFFF)



#define BLE_WLPRIVADDPTR_REG                 (0x400000B4) /* Start address of private devices list */
#define BLE_WLPRIVADDPTR_REG_RESET           (0x00000000)

/*=============================*/
struct __BLE_WLPRIVADDPTR_REG
/*=============================*/
{
    volatile uint32_t BITFLD_WLPRIVADDPTR                      : 16;
};
#define WLPRIVADDPTR                          (0xFFFF)



#define BLE_WLNBDEV_REG                      (0x400000B8) /* Devices in white list */
#define BLE_WLNBDEV_REG_RESET                (0x00000000)

/*=============================*/
struct __BLE_WLNBDEV_REG
/*=============================*/
{
    volatile uint32_t BITFLD_NBPUBDEV                          : 8;
    volatile uint32_t BITFLD_NBPRIVDEV                         : 8;
};
#define NBPUBDEV                              (0x00FF)
#define NBPRIVDEV                             (0xFF00)



#define BLE_AESCNTL_REG                      (0x400000C0) /* Start AES register */
#define BLE_AESCNTL_REG_RESET                (0x00000000)

/*=============================*/
struct __BLE_AESCNTL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_AES_START                         : 1;
    volatile uint32_t BITFLD_AES_MODE                          : 1;
};
#define AES_START                             (0x0001)
#define AES_MODE                              (0x0002)



#define BLE_AESKEY31_0_REG                   (0x400000C4) /* AES encryption key */
#define BLE_AESKEY31_0_REG_RESET             (0x00000000)

/*=============================*/
struct __BLE_AESKEY31_0_REG
/*=============================*/
{
    volatile uint32_t BITFLD_AESKEY31_0                        : 32;
};
#define AESKEY31_0                            (0xFFFFFFFF)



#define BLE_AESKEY63_32_REG                  (0x400000C8) /* AES encryption key */
#define BLE_AESKEY63_32_REG_RESET            (0x00000000)

/*=============================*/
struct __BLE_AESKEY63_32_REG
/*=============================*/
{
    volatile uint32_t BITFLD_AESKEY63_32                       : 32;
};
#define AESKEY63_32                           (0xFFFFFFFF)



#define BLE_AESKEY95_64_REG                  (0x400000CC) /* AES encryption key */
#define BLE_AESKEY95_64_REG_RESET            (0x00000000)

/*=============================*/
struct __BLE_AESKEY95_64_REG
/*=============================*/
{
    volatile uint32_t BITFLD_AESKEY95_64                       : 32;
};
#define AESKEY95_64                           (0xFFFFFFFF)



#define BLE_AESKEY127_96_REG                 (0x400000D0) /* AES encryption key */
#define BLE_AESKEY127_96_REG_RESET           (0x00000000)

/*=============================*/
struct __BLE_AESKEY127_96_REG
/*=============================*/
{
    volatile uint32_t BITFLD_AESKEY127_96                      : 32;
};
#define AESKEY127_96                          (0xFFFFFFFF)



#define BLE_AESPTR_REG                       (0x400000D4) /* Pointer to the block to encrypt/decrypt */
#define BLE_AESPTR_REG_RESET                 (0x00000000)

/*=============================*/
struct __BLE_AESPTR_REG
/*=============================*/
{
    volatile uint32_t BITFLD_AESPTR                            : 16;
};
#define AESPTR                                (0xFFFF)



#define BLE_TXMICVAL_REG                     (0x400000D8) /* AES / CCM plain MIC value */
#define BLE_TXMICVAL_REG_RESET               (0x00000000)

/*=============================*/
struct __BLE_TXMICVAL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_TXMICVAL                          : 32;
};
#define TXMICVAL                              (0xFFFFFFFF)



#define BLE_RXMICVAL_REG                     (0x400000DC) /* AES / CCM plain MIC value */
#define BLE_RXMICVAL_REG_RESET               (0x00000000)

/*=============================*/
struct __BLE_RXMICVAL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RXMICVAL                          : 32;
};
#define RXMICVAL                              (0xFFFFFFFF)



#define BLE_RFTESTCNTL_REG                   (0x400000E0) /* RF Testing Register */
#define BLE_RFTESTCNTL_REG_RESET             (0x00000000)

/*=============================*/
struct __BLE_RFTESTCNTL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_TXLENGTH                          : 9;
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_TXPKTCNTEN                        : 1;
    volatile uint32_t BITFLD_TXPLDSRC                          : 1;
    volatile uint32_t BITFLD_PRBSTYPE                          : 1;
    volatile uint32_t BITFLD_TXLENGTHSRC                       : 1;
    volatile uint32_t BITFLD_INFINITETX                        : 1;
    volatile uint32_t                                          : 11;
    volatile uint32_t BITFLD_RXPKTCNTEN                        : 1;
    volatile uint32_t                                          : 3;
    volatile uint32_t BITFLD_INFINITERX                        : 1;
};
#define TXLENGTH                              (0x01FF)
#define TXPKTCNTEN                            (0x0800)
#define TXPLDSRC                              (0x1000)
#define PRBSTYPE                              (0x2000)
#define TXLENGTHSRC                           (0x4000)
#define INFINITETX                            (0x8000)
#define RXPKTCNTEN                            (0x8000000)
#define INFINITERX                            (0x80000000)



#define BLE_RFTESTTXSTAT_REG                 (0x400000E4) /* RF Testing Register */
#define BLE_RFTESTTXSTAT_REG_RESET           (0x00000000)

/*=============================*/
struct __BLE_RFTESTTXSTAT_REG
/*=============================*/
{
    volatile uint32_t BITFLD_TXPKTCNT                          : 32;
};
#define TXPKTCNT                              (0xFFFFFFFF)



#define BLE_RFTESTRXSTAT_REG                 (0x400000E8) /* RF Testing Register */
#define BLE_RFTESTRXSTAT_REG_RESET           (0x00000000)

/*=============================*/
struct __BLE_RFTESTRXSTAT_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RXPKTCNT                          : 32;
};
#define RXPKTCNT                              (0xFFFFFFFF)



#define BLE_TIMGENCNTL_REG                   (0x400000F0) /* Timing Generator Register */
#define BLE_TIMGENCNTL_REG_RESET             (0x81FE0096)

/*=============================*/
struct __BLE_TIMGENCNTL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_PREFETCH_TIME                     : 9;
    volatile uint32_t                                          : 7;
    volatile uint32_t BITFLD_PREFETCHABORT_TIME                : 10;
    volatile uint32_t                                          : 5;
    volatile uint32_t BITFLD_APFM_EN                           : 1;
};
#define PREFETCH_TIME                         (0x01FF)
#define PREFETCHABORT_TIME                    (0x3FF0000)
#define APFM_EN                               (0x80000000)



#define BLE_GROSSTIMTGT_REG                  (0x400000F4) /* Gross Timer Target value */
#define BLE_GROSSTIMTGT_REG_RESET            (0x00000000)

/*=============================*/
struct __BLE_GROSSTIMTGT_REG
/*=============================*/
{
    volatile uint32_t BITFLD_GROSSTARGET                       : 23;
};
#define GROSSTARGET                           (0x7FFFFF)



#define BLE_FINETIMTGT_REG                   (0x400000F8) /* Fine Timer Target value */
#define BLE_FINETIMTGT_REG_RESET             (0x00000000)

/*=============================*/
struct __BLE_FINETIMTGT_REG
/*=============================*/
{
    volatile uint32_t BITFLD_FINETARGET                        : 27;
};
#define FINETARGET                            (0x7FFFFFF)



#define BLE_SAMPLECLK_REG                    (0x400000FC) /* Samples the Base Time Counter */
#define BLE_SAMPLECLK_REG_RESET              (0x00000000)

/*=============================*/
struct __BLE_SAMPLECLK_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SAMP                              : 1;
};
#define SAMP                                  (0x0001)



#define BLE_COEXIFCNTL0_REG                  (0x40000100) /* Coexistence interface Control 0 Register */
#define BLE_COEXIFCNTL0_REG_RESET            (0x00000010)

/*=============================*/
struct __BLE_COEXIFCNTL0_REG
/*=============================*/
{
    volatile uint32_t BITFLD_COEX_EN                           : 1;
    volatile uint32_t BITFLD_SYNCGEN_EN                        : 1;
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_WLANRXMSK                         : 2;
    volatile uint32_t BITFLD_WLANTXMSK                         : 2;
    volatile uint32_t                                          : 8;
    volatile uint32_t BITFLD_WLCTXPRIOMODE                     : 2;
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_WLCRXPRIOMODE                     : 2;
};
#define COEX_EN                               (0x0001)
#define SYNCGEN_EN                            (0x0002)
#define WLANRXMSK                             (0x0030)
#define WLANTXMSK                             (0x00C0)
#define WLCTXPRIOMODE                         (0x30000)
#define WLCRXPRIOMODE                         (0x300000)



#define BLE_COEXIFCNTL1_REG                  (0x40000104) /* Coexistence interface Control 1 Register */
#define BLE_COEXIFCNTL1_REG_RESET            (0x00000000)

/*=============================*/
struct __BLE_COEXIFCNTL1_REG
/*=============================*/
{
    volatile uint32_t BITFLD_WLCPDELAY                         : 7;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_WLCPDURATION                      : 7;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_WLCPTXTHR                         : 5;
    volatile uint32_t                                          : 3;
    volatile uint32_t BITFLD_WLCPRXTHR                         : 5;
};
#define WLCPDELAY                             (0x007F)
#define WLCPDURATION                          (0x7F00)
#define WLCPTXTHR                             (0x1F0000)
#define WLCPRXTHR                             (0x1F000000)



#define BLE_BLEMPRIO0_REG                    (0x40000108) /* Coexistence interface Priority 0 Register */
#define BLE_BLEMPRIO0_REG_RESET              (0x3489ADEF)

/*=============================*/
struct __BLE_BLEMPRIO0_REG
/*=============================*/
{
    volatile uint32_t BITFLD_BLEM0                             : 4;
    volatile uint32_t BITFLD_BLEM1                             : 4;
    volatile uint32_t BITFLD_BLEM2                             : 4;
    volatile uint32_t BITFLD_BLEM3                             : 4;
    volatile uint32_t BITFLD_BLEM4                             : 4;
    volatile uint32_t BITFLD_BLEM5                             : 4;
    volatile uint32_t BITFLD_BLEM6                             : 4;
    volatile uint32_t BITFLD_BLEM7                             : 4;
};
#define BLEM0                                 (0x000F)
#define BLEM1                                 (0x00F0)
#define BLEM2                                 (0x0F00)
#define BLEM3                                 (0xF000)
#define BLEM4                                 (0xF0000)
#define BLEM5                                 (0xF00000)
#define BLEM6                                 (0xF000000)
#define BLEM7                                 (0xF0000000)



#define BLE_BLEMPRIO1_REG                    (0x4000010C) /* Coexistence interface Priority 1 Register */
#define BLE_BLEMPRIO1_REG_RESET              (0x30000000)

/*=============================*/
struct __BLE_BLEMPRIO1_REG
/*=============================*/
{
    volatile uint32_t                                          : 28;
    volatile uint32_t BITFLD_BLEMDEFAULT                       : 4;
};
#define BLEMDEFAULT                           (0xF0000000)



#define BLE_CNTL2_REG                        (0x40000200) /* BLE Control Register 2 */
#define BLE_CNTL2_REG_RESET                  (0x00000004)

/*=============================*/
struct __BLE_CNTL2_REG
/*=============================*/
{
    volatile uint32_t BITFLD_EMACCERRSTAT                      : 1;
    volatile uint32_t BITFLD_EMACCERRACK                       : 1;
    volatile uint32_t BITFLD_EMACCERRMSK                       : 1;
    volatile uint32_t BITFLD_BLE_DIAG_OVR                      : 1;
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_BLE_CLK_STAT                      : 1;
    volatile uint32_t BITFLD_MON_LP_CLK                        : 1;
    volatile uint32_t BITFLD_RADIO_PWRDN_ALLOW                 : 1;
    volatile uint32_t BITFLD_BLE_CLK_SEL                       : 6;
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_BLE_PTI_SOURCE_SEL                : 1;
    volatile uint32_t BITFLD_BB_ONLY                           : 1;
    volatile uint32_t BITFLD_SW_RPL_SPI                        : 1;
    volatile uint32_t BITFLD_WAKEUPLPSTAT                      : 1;
    volatile uint32_t BITFLD_BLE_RSSI_SEL                      : 1;
    volatile uint32_t BITFLD_BLE_ARP_PHY_ERR_STAT              : 1;
    volatile uint32_t BITFLD_BLE_ARP_ERR_MSK_N                 : 1;
    volatile uint32_t BITFLD_BLE_PHY_ERR_MSK_N                 : 1;
};
#define EMACCERRSTAT                          (0x0001)
#define EMACCERRACK                           (0x0002)
#define EMACCERRMSK                           (0x0004)
#define BLE_DIAG_OVR                          (0x0008)
#define BLE_CLK_STAT                          (0x0040)
#define MON_LP_CLK                            (0x0080)
#define RADIO_PWRDN_ALLOW                     (0x0100)
#define BLE_CLK_SEL                           (0x7E00)
#define BLE_PTI_SOURCE_SEL                    (0x20000)
#define BB_ONLY                               (0x40000)
#define SW_RPL_SPI                            (0x80000)
#define WAKEUPLPSTAT                          (0x100000)
#define BLE_RSSI_SEL                          (0x200000)
#define BLE_ARP_PHY_ERR_STAT                  (0x400000)
#define BLE_ARP_ERR_MSK_N                     (0x800000)
#define BLE_PHY_ERR_MSK_N                     (0x1000000)



#define BLE_EM_BASE_REG                      (0x40000208) /* Exchange Memory Base Register */
#define BLE_EM_BASE_REG_RESET                (0x00000000)

/*=============================*/
struct __BLE_EM_BASE_REG
/*=============================*/
{
    volatile uint32_t                                          : 10;
    volatile uint32_t BITFLD_BLE_EM_BASE_16_10                 : 7;
};
#define BLE_EM_BASE_16_10                     (0x1FC00)



#define BLE_DIAGCNTL2_REG                    (0x4000020C) /* Debug use only */
#define BLE_DIAGCNTL2_REG_RESET              (0x00000000)

/*=============================*/
struct __BLE_DIAGCNTL2_REG
/*=============================*/
{
    volatile uint32_t BITFLD_DIAG4                             : 6;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_DIAG4_EN                          : 1;
    volatile uint32_t BITFLD_DIAG5                             : 6;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_DIAG5_EN                          : 1;
    volatile uint32_t BITFLD_DIAG6                             : 6;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_DIAG6_EN                          : 1;
    volatile uint32_t BITFLD_DIAG7                             : 6;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_DIAG7_EN                          : 1;
};
#define DIAG4                                 (0x003F)
#define DIAG4_EN                              (0x0080)
#define DIAG5                                 (0x3F00)
#define DIAG5_EN                              (0x8000)
#define DIAG6                                 (0x3F0000)
#define DIAG6_EN                              (0x800000)
#define DIAG7                                 (0x3F000000)
#define DIAG7_EN                              (0x80000000)



#define BLE_DIAGCNTL3_REG                    (0x40000210) /* Debug use only */
#define BLE_DIAGCNTL3_REG_RESET              (0x00000000)

/*=============================*/
struct __BLE_DIAGCNTL3_REG
/*=============================*/
{
    volatile uint32_t BITFLD_DIAG0_BIT                         : 3;
    volatile uint32_t BITFLD_DIAG0_INV                         : 1;
    volatile uint32_t BITFLD_DIAG1_BIT                         : 3;
    volatile uint32_t BITFLD_DIAG1_INV                         : 1;
    volatile uint32_t BITFLD_DIAG2_BIT                         : 3;
    volatile uint32_t BITFLD_DIAG2_INV                         : 1;
    volatile uint32_t BITFLD_DIAG3_BIT                         : 3;
    volatile uint32_t BITFLD_DIAG3_INV                         : 1;
    volatile uint32_t BITFLD_DIAG4_BIT                         : 3;
    volatile uint32_t BITFLD_DIAG4_INV                         : 1;
    volatile uint32_t BITFLD_DIAG5_BIT                         : 3;
    volatile uint32_t BITFLD_DIAG5_INV                         : 1;
    volatile uint32_t BITFLD_DIAG6_BIT                         : 3;
    volatile uint32_t BITFLD_DIAG6_INV                         : 1;
    volatile uint32_t BITFLD_DIAG7_BIT                         : 3;
    volatile uint32_t BITFLD_DIAG7_INV                         : 1;
};
#define DIAG0_BIT                             (0x0007)
#define DIAG0_INV                             (0x0008)
#define DIAG1_BIT                             (0x0070)
#define DIAG1_INV                             (0x0080)
#define DIAG2_BIT                             (0x0700)
#define DIAG2_INV                             (0x0800)
#define DIAG3_BIT                             (0x7000)
#define DIAG3_INV                             (0x8000)
#define DIAG4_BIT                             (0x70000)
#define DIAG4_INV                             (0x80000)
#define DIAG5_BIT                             (0x700000)
#define DIAG5_INV                             (0x800000)
#define DIAG6_BIT                             (0x7000000)
#define DIAG6_INV                             (0x8000000)
#define DIAG7_BIT                             (0x70000000)
#define DIAG7_INV                             (0x80000000)



/*===========================================================================*/
/* memory map CRG */
/*===========================================================================*/



#define CLK_AMBA_REG                         (0x50000000) /* HCLK, PCLK, divider and clock gates */
#define CLK_AMBA_REG_RESET                   (0x00000000)

/*=============================*/
struct __CLK_AMBA_REG
/*=============================*/
{
    volatile uint16_t BITFLD_HCLK_DIV                          : 2;
    volatile uint16_t                                          : 2;
    volatile uint16_t BITFLD_PCLK_DIV                          : 2;
    volatile uint16_t                                          : 1;
    volatile uint16_t BITFLD_OTP_ENABLE                        : 1;
};
#define HCLK_DIV                              (0x0003)
#define PCLK_DIV                              (0x0030)
#define OTP_ENABLE                            (0x0080)



#define CLK_FREQ_TRIM_REG                    (0x50000002) /* Xtal frequency trimming register */
#define CLK_FREQ_TRIM_REG_RESET              (0x00000080)

/*=============================*/
struct __CLK_FREQ_TRIM_REG
/*=============================*/
{
    volatile uint16_t BITFLD_XTAL32M_TRIM                      : 8;
};
#define XTAL32M_TRIM                          (0x00FF)



#define CLK_PER_REG                          (0x50000004) /* Peripheral divider register */
#define CLK_PER_REG_RESET                    (0x00000800)

/*=============================*/
struct __CLK_PER_REG
/*=============================*/
{
    volatile uint16_t BITFLD_TMR_DIV                           : 2;
    volatile uint16_t                                          : 1;
    volatile uint16_t BITFLD_TMR_ENABLE                        : 1;
    volatile uint16_t BITFLD_WAKEUPCT_ENABLE                   : 1;
    volatile uint16_t BITFLD_I2C_ENABLE                        : 1;
    volatile uint16_t BITFLD_UART2_ENABLE                      : 1;
    volatile uint16_t BITFLD_UART1_ENABLE                      : 1;
    volatile uint16_t                                          : 2;
    volatile uint16_t BITFLD_SPI_ENABLE                        : 1;
    volatile uint16_t BITFLD_QUAD_ENABLE                       : 1;
};
#define TMR_DIV                               (0x0003)
#define TMR_ENABLE                            (0x0008)
#define WAKEUPCT_ENABLE                       (0x0010)
#define I2C_ENABLE                            (0x0020)
#define UART2_ENABLE                          (0x0040)
#define UART1_ENABLE                          (0x0080)
#define SPI_ENABLE                            (0x0400)
#define QUAD_ENABLE                           (0x0800)



#define CLK_RADIO_REG                        (0x50000008) /* Radio PLL control register */
#define CLK_RADIO_REG_RESET                  (0x00000040)

/*=============================*/
struct __CLK_RADIO_REG
/*=============================*/
{
    volatile uint16_t                                          : 2;
    volatile uint16_t                                          : 1;
    volatile uint16_t BITFLD_RFCU_ENABLE                       : 1;
    volatile uint16_t BITFLD_BLE_DIV                           : 2;
    volatile uint16_t BITFLD_BLE_LP_RESET                      : 1;
    volatile uint16_t BITFLD_BLE_ENABLE                        : 1;
};
#define RFCU_ENABLE                           (0x0008)
#define BLE_DIV                               (0x0030)
#define BLE_LP_RESET                          (0x0040)
#define BLE_ENABLE                            (0x0080)



#define CLK_CTRL_REG                         (0x5000000A) /* Clock control register */
#define CLK_CTRL_REG_RESET                   (0x00000041)

/*=============================*/
struct __CLK_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SYS_CLK_SEL                       : 2;
    volatile uint16_t BITFLD_XTAL32M_DISABLE                   : 1;
    volatile uint16_t BITFLD_LP_CLK_SEL                        : 2;
    volatile uint16_t BITFLD_RUNNING_AT_LP_CLK                 : 1;
    volatile uint16_t BITFLD_RUNNING_AT_RC32M                  : 1;
    volatile uint16_t BITFLD_RUNNING_AT_XTAL32M                : 1;
};
#define SYS_CLK_SEL                           (0x0003)
#define XTAL32M_DISABLE                       (0x0004)
#define LP_CLK_SEL                            (0x0018)
#define RUNNING_AT_LP_CLK                     (0x0020)
#define RUNNING_AT_RC32M                      (0x0040)
#define RUNNING_AT_XTAL32M                    (0x0080)



#define PMU_CTRL_REG                         (0x50000010) /* Power Management Unit control register */
#define PMU_CTRL_REG_RESET                   (0x00000006)

/*=============================*/
struct __PMU_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_RESET_ON_WAKEUP                   : 1;
    volatile uint16_t BITFLD_TIM_SLEEP                         : 1;
    volatile uint16_t BITFLD_RADIO_SLEEP                       : 1;
    volatile uint16_t                                          : 1;
    volatile uint16_t BITFLD_OTP_COPY_DIV                      : 2;
    volatile uint16_t BITFLD_MAP_BANDGAP_EN                    : 1;
};
#define RESET_ON_WAKEUP                       (0x0001)
#define TIM_SLEEP                             (0x0002)
#define RADIO_SLEEP                           (0x0004)
#define OTP_COPY_DIV                          (0x0030)
#define MAP_BANDGAP_EN                        (0x0040)



#define SYS_CTRL_REG                         (0x50000012) /* System Control register */
#define SYS_CTRL_REG_RESET                   (0x00000020)

/*=============================*/
struct __SYS_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_REMAP_ADR0                        : 2;
    volatile uint16_t BITFLD_DEV_PHASE                         : 1;
    volatile uint16_t                                          : 1;
    volatile uint16_t BITFLD_OTP_COPY                          : 1;
    volatile uint16_t                                          : 1;
    volatile uint16_t BITFLD_OTPC_RESET_REQ                    : 1;
    volatile uint16_t BITFLD_DEBUGGER_ENABLE                   : 2;
    volatile uint16_t                                          : 1;
    volatile uint16_t BITFLD_TIMEOUT_DISABLE                   : 1;
    volatile uint16_t                                          : 4;
    volatile uint16_t BITFLD_SW_RESET                          : 1;
};
#define REMAP_ADR0                            (0x0003)
#define DEV_PHASE                             (0x0004)
#define OTP_COPY                              (0x0010)
#define OTPC_RESET_REQ                        (0x0040)
#define DEBUGGER_ENABLE                       (0x0180)
#define TIMEOUT_DISABLE                       (0x0400)
#define SW_RESET                              (0x8000)



#define SYS_STAT_REG                         (0x50000014) /* System status register */
#define SYS_STAT_REG_RESET                   (0x00000045)

/*=============================*/
struct __SYS_STAT_REG
/*=============================*/
{
    volatile uint16_t BITFLD_RAD_IS_DOWN                       : 1;
    volatile uint16_t BITFLD_RAD_IS_UP                         : 1;
    volatile uint16_t BITFLD_TIM_IS_DOWN                       : 1;
    volatile uint16_t BITFLD_TIM_IS_UP                         : 1;
    volatile uint16_t BITFLD_DBG_IS_UP                         : 1;
    volatile uint16_t                                          : 1;
    volatile uint16_t BITFLD_XTAL32M_TRIM_READY                : 1;
    volatile uint16_t BITFLD_XTAL32M_SETTLED                   : 1;
};
#define RAD_IS_DOWN                           (0x0001)
#define RAD_IS_UP                             (0x0002)
#define TIM_IS_DOWN                           (0x0004)
#define TIM_IS_UP                             (0x0008)
#define DBG_IS_UP                             (0x0010)
#define XTAL32M_TRIM_READY                    (0x0040)
#define XTAL32M_SETTLED                       (0x0080)



#define TRIM_CTRL_REG                        (0x50000016) /* Control trimming of the XTAL32M */
#define TRIM_CTRL_REG_RESET                  (0x00003F22)

/*=============================*/
struct __TRIM_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_XTAL_COUNT_N                      : 6;
    volatile uint16_t BITFLD_XTAL_TRIM_SELECT                  : 2;
    volatile uint16_t BITFLD_XTAL_SETTLE_N                     : 6;
};
#define XTAL_COUNT_N                          (0x003F)
#define XTAL_TRIM_SELECT                      (0x00C0)
#define XTAL_SETTLE_N                         (0x3F00)



#define RAM_PWR_CTRL_REG                     (0x50000018) /* Control power state of System RAMS */
#define RAM_PWR_CTRL_REG_RESET               (0x00000000)

/*=============================*/
struct __RAM_PWR_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_RAM1_PWR_CTRL                     : 2;
    volatile uint16_t BITFLD_RAM2_PWR_CTRL                     : 2;
    volatile uint16_t BITFLD_RAM3_PWR_CTRL                     : 2;
};
#define RAM1_PWR_CTRL                         (0x0003)
#define RAM2_PWR_CTRL                         (0x000C)
#define RAM3_PWR_CTRL                         (0x0030)



#define CLK_RC32K_REG                        (0x50000020) /* 32 kHz RC oscillator register */
#define CLK_RC32K_REG_RESET                  (0x0000000E)

/*=============================*/
struct __CLK_RC32K_REG
/*=============================*/
{
    volatile uint16_t BITFLD_RC32K_DISABLE                     : 1;
    volatile uint16_t BITFLD_RC32K_TRIM                        : 4;
};
#define RC32K_DISABLE                         (0x0001)
#define RC32K_TRIM                            (0x001E)



#define CLK_RC32M_REG                        (0x50000024) /* Fast RC control register */
#define CLK_RC32M_REG_RESET                  (0x0000078E)

/*=============================*/
struct __CLK_RC32M_REG
/*=============================*/
{
    volatile uint16_t BITFLD_RC32M_DISABLE                     : 1;
    volatile uint16_t BITFLD_RC32M_BIAS                        : 4;
    volatile uint16_t BITFLD_RC32M_RANGE                       : 2;
    volatile uint16_t BITFLD_RC32M_COSC                        : 4;
};
#define RC32M_DISABLE                         (0x0001)
#define RC32M_BIAS                            (0x001E)
#define RC32M_RANGE                           (0x0060)
#define RC32M_COSC                            (0x0780)



#define CLK_RCX_REG                          (0x50000026) /* RCX-oscillator control register */
#define CLK_RCX_REG_RESET                    (0x00000AFC)

/*=============================*/
struct __CLK_RCX_REG
/*=============================*/
{
    volatile uint16_t BITFLD_RCX_ENABLE                        : 1;
    volatile uint16_t BITFLD_RCX_RADJUST                       : 1;
    volatile uint16_t BITFLD_RCX_CADJUST                       : 5;
    volatile uint16_t BITFLD_RCX_C0                            : 1;
    volatile uint16_t BITFLD_RCX_BIAS                          : 4;
};
#define RCX_ENABLE                            (0x0001)
#define RCX_RADJUST                           (0x0002)
#define RCX_CADJUST                           (0x007C)
#define RCX_C0                                (0x0080)
#define RCX_BIAS                              (0x0F00)



#define BANDGAP_REG                          (0x50000028) /* Bandgap trimming */
#define BANDGAP_REG_RESET                    (0x00000000)

/*=============================*/
struct __BANDGAP_REG
/*=============================*/
{
    volatile uint16_t BITFLD_BGR_TRIM                          : 5;
    volatile uint16_t BITFLD_BGR_ITRIM                         : 5;
};
#define BGR_TRIM                              (0x001F)
#define BGR_ITRIM                             (0x03E0)



#define XTAL32M_START_REG                    (0x50000030) /* Trim values for XTAL32M */
#define XTAL32M_START_REG_RESET              (0x000000AA)

/*=============================*/
struct __XTAL32M_START_REG
/*=============================*/
{
    volatile uint16_t BITFLD_XTAL32M_START                     : 8;
    volatile uint16_t BITFLD_XTAL32M_RAMP                      : 8;
};
#define XTAL32M_START                         (0x00FF)
#define XTAL32M_RAMP                          (0xFF00)



#define XTAL32M_TRSTAT_REG                   (0x50000032) /* Read back value of current XTAL trimming */
#define XTAL32M_TRSTAT_REG_RESET             (0x00000000)

/*=============================*/
struct __XTAL32M_TRSTAT_REG
/*=============================*/
{
    volatile uint16_t BITFLD_XTAL32M_TRSTAT                    : 8;
};
#define XTAL32M_TRSTAT                        (0x00FF)



#define XTALRDY_CTRL_REG                     (0x50000034) /* Control register for XTALRDY IRQ */
#define XTALRDY_CTRL_REG_RESET               (0x00000000)

/*=============================*/
struct __XTALRDY_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_XTALRDY_CNT                       : 8;
};
#define XTALRDY_CNT                           (0x00FF)



#define POR_PIN_REG                          (0x50000040) /* Selects a GPIO pin for POR generation */
#define POR_PIN_REG_RESET                    (0x00000000)

/*=============================*/
struct __POR_PIN_REG
/*=============================*/
{
    volatile uint16_t BITFLD_POR_PIN_SELECT                    : 4;
    volatile uint16_t                                          : 3;
    volatile uint16_t BITFLD_POR_PIN_POLARITY                  : 1;
};
#define POR_PIN_SELECT                        (0x000F)
#define POR_PIN_POLARITY                      (0x0080)



#define POR_TIMER_REG                        (0x50000042) /* Time for POR to happen */
#define POR_TIMER_REG_RESET                  (0x00000018)

/*=============================*/
struct __POR_TIMER_REG
/*=============================*/
{
    volatile uint16_t BITFLD_POR_TIME                          : 7;
};
#define POR_TIME                              (0x007F)



#define PMU_SLEEP_REG                        (0x50000050) /* Bandgap refresh interval during sleep */
#define PMU_SLEEP_REG_RESET                  (0x00000080)

/*=============================*/
struct __PMU_SLEEP_REG
/*=============================*/
{
    volatile uint16_t BITFLD_BG_REFRESH_INTERVAL               : 12;
};
#define BG_REFRESH_INTERVAL                   (0x0FFF)



#define POWER_CTRL_REG                       (0x50000052) /* Power management control */
#define POWER_CTRL_REG_RESET                 (0x00004000)

/*=============================*/
struct __POWER_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_CMP_VBAT_HIGH_NOK_ENABLE          : 1;
    volatile uint16_t BITFLD_CMP_VBAT_HIGH_OK_ENABLE           : 1;
    volatile uint16_t BITFLD_VBAT_HL_CONNECT                   : 1;
    volatile uint16_t BITFLD_LDO_CORE_RET_ENABLE               : 1;
    volatile uint16_t BITFLD_LDO_CORE_DISABLE                  : 1;
    volatile uint16_t BITFLD_LDO_LOW_CTRL_REG                  : 2;
    volatile uint16_t BITFLD_LDO_VREF_HOLD_FORCE               : 1;
    volatile uint16_t BITFLD_CP_DISABLE                        : 1;
    volatile uint16_t BITFLD_POR_VBAT_LOW_DISABLE              : 1;
    volatile uint16_t BITFLD_POR_VBAT_LOW_HYST_SEL             : 1;
    volatile uint16_t BITFLD_POR_VBAT_LOW_HYST_DIS             : 1;
    volatile uint16_t BITFLD_POR_VBAT_HIGH_DISABLE             : 1;
    volatile uint16_t BITFLD_POR_VBAT_HIGH_HYST_SEL            : 1;
    volatile uint16_t BITFLD_POR_VBAT_HIGH_HYST_DIS            : 1;
    volatile uint16_t BITFLD_VBAT_HL_CONNECT_MODE              : 1;
};
#define CMP_VBAT_HIGH_NOK_ENABLE              (0x0001)
#define CMP_VBAT_HIGH_OK_ENABLE               (0x0002)
#define VBAT_HL_CONNECT                       (0x0004)
#define LDO_CORE_RET_ENABLE                   (0x0008)
#define LDO_CORE_DISABLE                      (0x0010)
#define LDO_LOW_CTRL_REG                      (0x0060)
#define LDO_VREF_HOLD_FORCE                   (0x0080)
#define CP_DISABLE                            (0x0100)
#define POR_VBAT_LOW_DISABLE                  (0x0200)
#define POR_VBAT_LOW_HYST_SEL                 (0x0400)
#define POR_VBAT_LOW_HYST_DIS                 (0x0800)
#define POR_VBAT_HIGH_DISABLE                 (0x1000)
#define POR_VBAT_HIGH_HYST_SEL                (0x2000)
#define POR_VBAT_HIGH_HYST_DIS                (0x4000)
#define VBAT_HL_CONNECT_MODE                  (0x8000)



/*===========================================================================*/
/* memory map crg2632_dcdc_dig_00 */
/*===========================================================================*/



#define DCDC_CTRL_REG                        (0x50000080) /*  */
#define DCDC_CTRL_REG_RESET                  (0x000084A2)

/*=============================*/
struct __DCDC_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DCDC_ENABLE                       : 1;
    volatile uint16_t BITFLD_DCDC_CLK_DIV                      : 2;
    volatile uint16_t BITFLD_DCDC_TIMEOUT                      : 3;
    volatile uint16_t BITFLD_DCDC_OK_CLR_CNT                   : 2;
    volatile uint16_t BITFLD_DCDC_ILIM_MIN                     : 4;
    volatile uint16_t BITFLD_DCDC_ILIM_MAX                     : 4;
};
#define DCDC_ENABLE                           (0x0001)
#define DCDC_CLK_DIV                          (0x0006)
#define DCDC_TIMEOUT                          (0x0038)
#define DCDC_OK_CLR_CNT                       (0x00C0)
#define DCDC_ILIM_MIN                         (0x0F00)
#define DCDC_ILIM_MAX                         (0xF000)



/*===========================================================================*/
/* memory map crg2632_preg_aon_00 */
/*===========================================================================*/



#define HWR_CTRL_REG                         (0x50000300) /* Hardware Reset control register */
#define HWR_CTRL_REG_RESET                   (0x00000000)

/*=============================*/
struct __HWR_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DISABLE_HWR                       : 1;
};
#define DISABLE_HWR                           (0x0001)



#define RESET_STAT_REG                       (0x50000304) /* Reset status register */
#define RESET_STAT_REG_RESET                 (0x0000000F)

/*=============================*/
struct __RESET_STAT_REG
/*=============================*/
{
    volatile uint16_t BITFLD_PORESET_STAT                      : 1;
    volatile uint16_t BITFLD_HWRESET_STAT                      : 1;
    volatile uint16_t BITFLD_SWRESET_STAT                      : 1;
    volatile uint16_t BITFLD_WDOGRESET_STAT                    : 1;
};
#define PORESET_STAT                          (0x0001)
#define HWRESET_STAT                          (0x0002)
#define SWRESET_STAT                          (0x0004)
#define WDOGRESET_STAT                        (0x0008)



#define RAM_LPMX_REG                         (0x50000308) /*  */
#define RAM_LPMX_REG_RESET                   (0x00000007)

/*=============================*/
struct __RAM_LPMX_REG
/*=============================*/
{
    volatile uint16_t BITFLD_RAMx_LPMX                         : 3;
};
#define RAMx_LPMX                             (0x0007)



#define PAD_LATCH_REG                        (0x5000030C) /* Control the state retention of the GPIO ports */
#define PAD_LATCH_REG_RESET                  (0x00000001)

/*=============================*/
struct __PAD_LATCH_REG
/*=============================*/
{
    volatile uint16_t BITFLD_PAD_LATCH_EN                      : 1;
};
#define PAD_LATCH_EN                          (0x0001)



#define HIBERN_CTRL_REG                      (0x50000310) /* Hibernation control register */
#define HIBERN_CTRL_REG_RESET                (0x00000000)

/*=============================*/
struct __HIBERN_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_HIBERNATION_ENABLE                : 1;
    volatile uint16_t BITFLD_HIBERN_WKUP_POLARITY              : 1;
    volatile uint16_t BITFLD_HIBERN_WKUP_MASK                  : 5;
};
#define HIBERNATION_ENABLE                    (0x0001)
#define HIBERN_WKUP_POLARITY                  (0x0002)
#define HIBERN_WKUP_MASK                      (0x007C)



/*===========================================================================*/
/* memory map crg2632_preg_tim_00 */
/*===========================================================================*/
//reserved only



/*===========================================================================*/
/* memory map DEM */
/*===========================================================================*/
//reserved only



/*===========================================================================*/
/* memory map DMA */
/*===========================================================================*/



#define DMA0_A_STARTL_REG                    (0x50003600) /* Start address Low A of DMA channel 0 */
#define DMA0_A_STARTL_REG_RESET              (0x00000000)

/*=============================*/
struct __DMA0_A_STARTL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA0_A_STARTL                     : 16;
};
#define DMA0_A_STARTL                         (0xFFFF)



#define DMA0_A_STARTH_REG                    (0x50003602) /* Start address High A of DMA channel 0 */
#define DMA0_A_STARTH_REG_RESET              (0x00000000)

/*=============================*/
struct __DMA0_A_STARTH_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA0_A_STARTH                     : 16;
};
#define DMA0_A_STARTH                         (0xFFFF)



#define DMA0_B_STARTL_REG                    (0x50003604) /* Start address Low B of DMA channel 0 */
#define DMA0_B_STARTL_REG_RESET              (0x00000000)

/*=============================*/
struct __DMA0_B_STARTL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA0_B_STARTL                     : 16;
};
#define DMA0_B_STARTL                         (0xFFFF)



#define DMA0_B_STARTH_REG                    (0x50003606) /* Start address High B of DMA channel 0 */
#define DMA0_B_STARTH_REG_RESET              (0x00000000)

/*=============================*/
struct __DMA0_B_STARTH_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA0_B_STARTH                     : 16;
};
#define DMA0_B_STARTH                         (0xFFFF)



#define DMA0_INT_REG                         (0x50003608) /* DMA receive interrupt register channel 0 */
#define DMA0_INT_REG_RESET                   (0x00000000)

/*=============================*/
struct __DMA0_INT_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA0_INT                          : 16;
};
#define DMA0_INT                              (0xFFFF)



#define DMA0_LEN_REG                         (0x5000360A) /* DMA receive length register channel 0 */
#define DMA0_LEN_REG_RESET                   (0x00000000)

/*=============================*/
struct __DMA0_LEN_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA0_LEN                          : 16;
};
#define DMA0_LEN                              (0xFFFF)



#define DMA0_CTRL_REG                        (0x5000360C) /* Control register for the DMA channel 0 */
#define DMA0_CTRL_REG_RESET                  (0x00000000)

/*=============================*/
struct __DMA0_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA_ON                            : 1;
    volatile uint16_t BITFLD_BW                                : 2;
    volatile uint16_t BITFLD_IRQ_ENABLE                        : 1;
    volatile uint16_t BITFLD_DREQ_MODE                         : 1;
    volatile uint16_t BITFLD_BINC                              : 1;
    volatile uint16_t BITFLD_AINC                              : 1;
    volatile uint16_t BITFLD_CIRCULAR                          : 1;
    volatile uint16_t BITFLD_DMA_PRIO                          : 3;
    volatile uint16_t BITFLD_DMA_IDLE                          : 1;
    volatile uint16_t BITFLD_DMA_INIT                          : 1;
    volatile uint16_t BITFLD_REQ_SENSE                         : 1;
};
#define DMA_ON                                (0x0001)
#define BW                                    (0x0006)
#define IRQ_ENABLE                            (0x0008)
#define DREQ_MODE                             (0x0010)
#define BINC                                  (0x0020)
#define AINC                                  (0x0040)
#define CIRCULAR                              (0x0080)
#define DMA_PRIO                              (0x0700)
#define DMA_IDLE                              (0x0800)
#define DMA_INIT                              (0x1000)
#define REQ_SENSE                             (0x2000)



#define DMA0_IDX_REG                         (0x5000360E) /* Index value of DMA channel 0 */
#define DMA0_IDX_REG_RESET                   (0x00000000)

/*=============================*/
struct __DMA0_IDX_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA0_IDX                          : 16;
};
#define DMA0_IDX                              (0xFFFF)



#define DMA1_A_STARTL_REG                    (0x50003610) /* Start address Low A of DMA channel 1 */
#define DMA1_A_STARTL_REG_RESET              (0x00000000)

/*=============================*/
struct __DMA1_A_STARTL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA1_A_STARTL                     : 16;
};
#define DMA1_A_STARTL                         (0xFFFF)



#define DMA1_A_STARTH_REG                    (0x50003612) /* Start address High A of DMA channel 1 */
#define DMA1_A_STARTH_REG_RESET              (0x00000000)

/*=============================*/
struct __DMA1_A_STARTH_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA1_A_STARTH                     : 16;
};
#define DMA1_A_STARTH                         (0xFFFF)



#define DMA1_B_STARTL_REG                    (0x50003614) /* Start address Low B of DMA channel 1 */
#define DMA1_B_STARTL_REG_RESET              (0x00000000)

/*=============================*/
struct __DMA1_B_STARTL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA1_B_STARTL                     : 16;
};
#define DMA1_B_STARTL                         (0xFFFF)



#define DMA1_B_STARTH_REG                    (0x50003616) /* Start address High B of DMA channel 1 */
#define DMA1_B_STARTH_REG_RESET              (0x00000000)

/*=============================*/
struct __DMA1_B_STARTH_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA1_B_STARTH                     : 16;
};
#define DMA1_B_STARTH                         (0xFFFF)



#define DMA1_INT_REG                         (0x50003618) /* DMA receive interrupt register channel 1 */
#define DMA1_INT_REG_RESET                   (0x00000000)

/*=============================*/
struct __DMA1_INT_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA1_INT                          : 16;
};
#define DMA1_INT                              (0xFFFF)



#define DMA1_LEN_REG                         (0x5000361A) /* DMA receive length register channel 1 */
#define DMA1_LEN_REG_RESET                   (0x00000000)

/*=============================*/
struct __DMA1_LEN_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA1_LEN                          : 16;
};
#define DMA1_LEN                              (0xFFFF)



#define DMA1_CTRL_REG                        (0x5000361C) /* Control register for the DMA channel 1 */
#define DMA1_CTRL_REG_RESET                  (0x00000000)

/*=============================*/
struct __DMA1_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA_ON                            : 1;
    volatile uint16_t BITFLD_BW                                : 2;
    volatile uint16_t BITFLD_IRQ_ENABLE                        : 1;
    volatile uint16_t BITFLD_DREQ_MODE                         : 1;
    volatile uint16_t BITFLD_BINC                              : 1;
    volatile uint16_t BITFLD_AINC                              : 1;
    volatile uint16_t BITFLD_CIRCULAR                          : 1;
    volatile uint16_t BITFLD_DMA_PRIO                          : 3;
    volatile uint16_t BITFLD_DMA_IDLE                          : 1;
    volatile uint16_t BITFLD_DMA_INIT                          : 1;
    volatile uint16_t BITFLD_REQ_SENSE                         : 1;
};
#define DMA_ON                                (0x0001)
#define BW                                    (0x0006)
#define IRQ_ENABLE                            (0x0008)
#define DREQ_MODE                             (0x0010)
#define BINC                                  (0x0020)
#define AINC                                  (0x0040)
#define CIRCULAR                              (0x0080)
#define DMA_PRIO                              (0x0700)
#define DMA_IDLE                              (0x0800)
#define DMA_INIT                              (0x1000)
#define REQ_SENSE                             (0x2000)



#define DMA1_IDX_REG                         (0x5000361E) /* Index value of DMA channel 1 */
#define DMA1_IDX_REG_RESET                   (0x00000000)

/*=============================*/
struct __DMA1_IDX_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA1_IDX                          : 16;
};
#define DMA1_IDX                              (0xFFFF)



#define DMA2_A_STARTL_REG                    (0x50003620) /* Start address Low A of DMA channel 2 */
#define DMA2_A_STARTL_REG_RESET              (0x00000000)

/*=============================*/
struct __DMA2_A_STARTL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA2_A_STARTL                     : 16;
};
#define DMA2_A_STARTL                         (0xFFFF)



#define DMA2_A_STARTH_REG                    (0x50003622) /* Start address High A of DMA channel 2 */
#define DMA2_A_STARTH_REG_RESET              (0x00000000)

/*=============================*/
struct __DMA2_A_STARTH_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA2_A_STARTH                     : 16;
};
#define DMA2_A_STARTH                         (0xFFFF)



#define DMA2_B_STARTL_REG                    (0x50003624) /* Start address Low B of DMA channel 2 */
#define DMA2_B_STARTL_REG_RESET              (0x00000000)

/*=============================*/
struct __DMA2_B_STARTL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA2_B_STARTL                     : 16;
};
#define DMA2_B_STARTL                         (0xFFFF)



#define DMA2_B_STARTH_REG                    (0x50003626) /* Start address High B of DMA channel 2 */
#define DMA2_B_STARTH_REG_RESET              (0x00000000)

/*=============================*/
struct __DMA2_B_STARTH_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA2_B_STARTH                     : 16;
};
#define DMA2_B_STARTH                         (0xFFFF)



#define DMA2_INT_REG                         (0x50003628) /* DMA receive interrupt register channel 2 */
#define DMA2_INT_REG_RESET                   (0x00000000)

/*=============================*/
struct __DMA2_INT_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA2_INT                          : 16;
};
#define DMA2_INT                              (0xFFFF)



#define DMA2_LEN_REG                         (0x5000362A) /* DMA receive length register channel 2 */
#define DMA2_LEN_REG_RESET                   (0x00000000)

/*=============================*/
struct __DMA2_LEN_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA2_LEN                          : 16;
};
#define DMA2_LEN                              (0xFFFF)



#define DMA2_CTRL_REG                        (0x5000362C) /* Control register for the DMA channel 2 */
#define DMA2_CTRL_REG_RESET                  (0x00000000)

/*=============================*/
struct __DMA2_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA_ON                            : 1;
    volatile uint16_t BITFLD_BW                                : 2;
    volatile uint16_t BITFLD_IRQ_ENABLE                        : 1;
    volatile uint16_t BITFLD_DREQ_MODE                         : 1;
    volatile uint16_t BITFLD_BINC                              : 1;
    volatile uint16_t BITFLD_AINC                              : 1;
    volatile uint16_t BITFLD_CIRCULAR                          : 1;
    volatile uint16_t BITFLD_DMA_PRIO                          : 3;
    volatile uint16_t BITFLD_DMA_IDLE                          : 1;
    volatile uint16_t BITFLD_DMA_INIT                          : 1;
    volatile uint16_t BITFLD_REQ_SENSE                         : 1;
};
#define DMA_ON                                (0x0001)
#define BW                                    (0x0006)
#define IRQ_ENABLE                            (0x0008)
#define DREQ_MODE                             (0x0010)
#define BINC                                  (0x0020)
#define AINC                                  (0x0040)
#define CIRCULAR                              (0x0080)
#define DMA_PRIO                              (0x0700)
#define DMA_IDLE                              (0x0800)
#define DMA_INIT                              (0x1000)
#define REQ_SENSE                             (0x2000)



#define DMA2_IDX_REG                         (0x5000362E) /* Index value of DMA channel 2 */
#define DMA2_IDX_REG_RESET                   (0x00000000)

/*=============================*/
struct __DMA2_IDX_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA2_IDX                          : 16;
};
#define DMA2_IDX                              (0xFFFF)



#define DMA3_A_STARTL_REG                    (0x50003630) /* Start address Low A of DMA channel 3 */
#define DMA3_A_STARTL_REG_RESET              (0x00000000)

/*=============================*/
struct __DMA3_A_STARTL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA3_A_STARTL                     : 16;
};
#define DMA3_A_STARTL                         (0xFFFF)



#define DMA3_A_STARTH_REG                    (0x50003632) /* Start address High A of DMA channel 3 */
#define DMA3_A_STARTH_REG_RESET              (0x00000000)

/*=============================*/
struct __DMA3_A_STARTH_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA3_A_STARTH                     : 16;
};
#define DMA3_A_STARTH                         (0xFFFF)



#define DMA3_B_STARTL_REG                    (0x50003634) /* Start address Low B of DMA channel 3 */
#define DMA3_B_STARTL_REG_RESET              (0x00000000)

/*=============================*/
struct __DMA3_B_STARTL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA3_B_STARTL                     : 16;
};
#define DMA3_B_STARTL                         (0xFFFF)



#define DMA3_B_STARTH_REG                    (0x50003636) /* Start address High B of DMA channel 3 */
#define DMA3_B_STARTH_REG_RESET              (0x00000000)

/*=============================*/
struct __DMA3_B_STARTH_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA3_B_STARTH                     : 16;
};
#define DMA3_B_STARTH                         (0xFFFF)



#define DMA3_INT_REG                         (0x50003638) /* DMA receive interrupt register channel 3 */
#define DMA3_INT_REG_RESET                   (0x00000000)

/*=============================*/
struct __DMA3_INT_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA3_INT                          : 16;
};
#define DMA3_INT                              (0xFFFF)



#define DMA3_LEN_REG                         (0x5000363A) /* DMA receive length register channel 3 */
#define DMA3_LEN_REG_RESET                   (0x00000000)

/*=============================*/
struct __DMA3_LEN_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA3_LEN                          : 16;
};
#define DMA3_LEN                              (0xFFFF)



#define DMA3_CTRL_REG                        (0x5000363C) /* Control register for the DMA channel 3 */
#define DMA3_CTRL_REG_RESET                  (0x00000000)

/*=============================*/
struct __DMA3_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA_ON                            : 1;
    volatile uint16_t BITFLD_BW                                : 2;
    volatile uint16_t BITFLD_IRQ_ENABLE                        : 1;
    volatile uint16_t BITFLD_DREQ_MODE                         : 1;
    volatile uint16_t BITFLD_BINC                              : 1;
    volatile uint16_t BITFLD_AINC                              : 1;
    volatile uint16_t BITFLD_CIRCULAR                          : 1;
    volatile uint16_t BITFLD_DMA_PRIO                          : 3;
    volatile uint16_t BITFLD_DMA_IDLE                          : 1;
    volatile uint16_t BITFLD_DMA_INIT                          : 1;
    volatile uint16_t BITFLD_REQ_SENSE                         : 1;
};
#define DMA_ON                                (0x0001)
#define BW                                    (0x0006)
#define IRQ_ENABLE                            (0x0008)
#define DREQ_MODE                             (0x0010)
#define BINC                                  (0x0020)
#define AINC                                  (0x0040)
#define CIRCULAR                              (0x0080)
#define DMA_PRIO                              (0x0700)
#define DMA_IDLE                              (0x0800)
#define DMA_INIT                              (0x1000)
#define REQ_SENSE                             (0x2000)



#define DMA3_IDX_REG                         (0x5000363E) /* Index value of DMA channel 3 */
#define DMA3_IDX_REG_RESET                   (0x00000000)

/*=============================*/
struct __DMA3_IDX_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA3_IDX                          : 16;
};
#define DMA3_IDX                              (0xFFFF)



#define DMA_REQ_MUX_REG                      (0x50003680) /* DMA channel assignments */
#define DMA_REQ_MUX_REG_RESET                (0x0000FFFF)

/*=============================*/
struct __DMA_REQ_MUX_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA01_SEL                         : 4;
    volatile uint16_t BITFLD_DMA23_SEL                         : 4;
    volatile uint16_t                                          : 4;
};
#define DMA01_SEL                             (0x000F)
#define DMA23_SEL                             (0x00F0)



#define DMA_INT_STATUS_REG                   (0x50003682) /* DMA interrupt status register */
#define DMA_INT_STATUS_REG_RESET             (0x00000000)

/*=============================*/
struct __DMA_INT_STATUS_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA_IRQ_CH0                       : 1;
    volatile uint16_t BITFLD_DMA_IRQ_CH1                       : 1;
    volatile uint16_t BITFLD_DMA_IRQ_CH2                       : 1;
    volatile uint16_t BITFLD_DMA_IRQ_CH3                       : 1;
    volatile uint16_t                                          : 1;
    volatile uint16_t                                          : 1;
    volatile uint16_t                                          : 1;
    volatile uint16_t                                          : 1;
};
#define DMA_IRQ_CH0                           (0x0001)
#define DMA_IRQ_CH1                           (0x0002)
#define DMA_IRQ_CH2                           (0x0004)
#define DMA_IRQ_CH3                           (0x0008)



#define DMA_CLEAR_INT_REG                    (0x50003684) /* DMA clear interrupt register */
#define DMA_CLEAR_INT_REG_RESET              (0x00000000)

/*=============================*/
struct __DMA_CLEAR_INT_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMA_RST_IRQ_CH0                   : 1;
    volatile uint16_t BITFLD_DMA_RST_IRQ_CH1                   : 1;
    volatile uint16_t BITFLD_DMA_RST_IRQ_CH2                   : 1;
    volatile uint16_t BITFLD_DMA_RST_IRQ_CH3                   : 1;
    volatile uint16_t                                          : 1;
    volatile uint16_t                                          : 1;
    volatile uint16_t                                          : 1;
    volatile uint16_t                                          : 1;
};
#define DMA_RST_IRQ_CH0                       (0x0001)
#define DMA_RST_IRQ_CH1                       (0x0002)
#define DMA_RST_IRQ_CH2                       (0x0004)
#define DMA_RST_IRQ_CH3                       (0x0008)



/*===========================================================================*/
/* memory map GPADC */
/*===========================================================================*/



#define GP_ADC_CTRL2_REG                     (0x50001502) /* General Purpose ADC Second Control Register */
#define GP_ADC_CTRL2_REG_RESET               (0x00000210)

/*=============================*/
struct __GP_ADC_CTRL2_REG
/*=============================*/
{
    volatile uint16_t BITFLD_GP_ADC_ATTN                       : 2;
    volatile uint16_t BITFLD_GP_ADC_I20U                       : 1;
    volatile uint16_t BITFLD_GP_ADC_OFFS_SH_EN                 : 1;
    volatile uint16_t BITFLD_GP_ADC_OFFS_SH_CM                 : 2;
    volatile uint16_t BITFLD_GP_ADC_CONV_NRS                   : 3;
    volatile uint16_t BITFLD_GP_ADC_SMPL_TIME                  : 4;
    volatile uint16_t BITFLD_GP_ADC_STORE_DEL                  : 3;
};
#define GP_ADC_ATTN                           (0x0003)
#define GP_ADC_I20U                           (0x0004)
#define GP_ADC_OFFS_SH_EN                     (0x0008)
#define GP_ADC_OFFS_SH_CM                     (0x0030)
#define GP_ADC_CONV_NRS                       (0x01C0)
#define GP_ADC_SMPL_TIME                      (0x1E00)
#define GP_ADC_STORE_DEL                      (0xE000)



#define GP_ADC_CTRL3_REG                     (0x50001504) /* General Purpose ADC Third Control Register */
#define GP_ADC_CTRL3_REG_RESET               (0x00000040)

/*=============================*/
struct __GP_ADC_CTRL3_REG
/*=============================*/
{
    volatile uint16_t BITFLD_GP_ADC_EN_DEL                     : 8;
    volatile uint16_t BITFLD_GP_ADC_INTERVAL                   : 8;
};
#define GP_ADC_EN_DEL                         (0x00FF)
#define GP_ADC_INTERVAL                       (0xFF00)



#define GP_ADC_OFFP_REG                      (0x50001508) /* General Purpose ADC Positive Offset Register */
#define GP_ADC_OFFP_REG_RESET                (0x00000200)

/*=============================*/
struct __GP_ADC_OFFP_REG
/*=============================*/
{
    volatile uint16_t BITFLD_GP_ADC_OFFP                       : 10;
};
#define GP_ADC_OFFP                           (0x03FF)



#define GP_ADC_OFFN_REG                      (0x5000150A) /* General Purpose ADC Negative Offset Register */
#define GP_ADC_OFFN_REG_RESET                (0x00000200)

/*=============================*/
struct __GP_ADC_OFFN_REG
/*=============================*/
{
    volatile uint16_t BITFLD_GP_ADC_OFFN                       : 10;
};
#define GP_ADC_OFFN                           (0x03FF)



#define GP_ADC_TRIM_REG                      (0x5000150C) /* General Purpose ADC Trim Register */
#define GP_ADC_TRIM_REG_RESET                (0x00000038)

/*=============================*/
struct __GP_ADC_TRIM_REG
/*=============================*/
{
    volatile uint16_t BITFLD_GP_ADC_OFFS_SH_VREF               : 4;
    volatile uint16_t BITFLD_GP_ADC_LDO_LEVEL                  : 3;
};
#define GP_ADC_OFFS_SH_VREF                   (0x000F)
#define GP_ADC_LDO_LEVEL                      (0x0070)



#define GP_ADC_CLEAR_INT_REG                 (0x5000150E) /* General Purpose ADC Clear Interrupt Register */
#define GP_ADC_CLEAR_INT_REG_RESET           (0x00000000)

/*=============================*/
struct __GP_ADC_CLEAR_INT_REG
/*=============================*/
{
    volatile uint16_t BITFLD_GP_ADC_CLR_INT                    : 16;
};
#define GP_ADC_CLR_INT                        (0xFFFF)



#define GP_ADC_RESULT_REG                    (0x50001510) /* General Purpose ADC Result Register */
#define GP_ADC_RESULT_REG_RESET              (0x00000000)

/*=============================*/
struct __GP_ADC_RESULT_REG
/*=============================*/
{
    volatile uint16_t BITFLD_GP_ADC_VAL                        : 16;
};
#define GP_ADC_VAL                            (0xFFFF)



/*===========================================================================*/
/* memory map GPIO */
/*===========================================================================*/



#define P0_DATA_REG                          (0x50003000) /* P0 Data input/output Register */
#define P0_DATA_REG_RESET                    (0x00000000)

/*=============================*/
struct __P0_DATA_REG
/*=============================*/
{
    volatile uint16_t BITFLD_P0_DATA                           : 12;
};
#define P0_DATA                               (0x0FFF)



#define P0_SET_DATA_REG                      (0x50003002) /* P0 Set port pins Register */
#define P0_SET_DATA_REG_RESET                (0x00000000)

/*=============================*/
struct __P0_SET_DATA_REG
/*=============================*/
{
    volatile uint16_t BITFLD_P0_SET                            : 12;
};
#define P0_SET                                (0x0FFF)



#define P0_RESET_DATA_REG                    (0x50003004) /* P0 Reset port pins Register */
#define P0_RESET_DATA_REG_RESET              (0x00000000)

/*=============================*/
struct __P0_RESET_DATA_REG
/*=============================*/
{
    volatile uint16_t BITFLD_P0_RESET                          : 12;
};
#define P0_RESET                              (0x0FFF)



#define P00_MODE_REG                         (0x50003006) /* P00 Mode Register */
#define P00_MODE_REG_RESET                   (0x00000200)

/*=============================*/
struct __P00_MODE_REG
/*=============================*/
{
    volatile uint16_t BITFLD_PID                               : 5;
    volatile uint16_t                                          : 3;
    volatile uint16_t BITFLD_PUPD                              : 2;
};
#define PID                                   (0x001F)
#define PUPD                                  (0x0300)



#define P01_MODE_REG                         (0x50003008) /* P01 Mode Register */
#define P01_MODE_REG_RESET                   (0x00000200)

/*=============================*/
struct __P01_MODE_REG
/*=============================*/
{
    volatile uint16_t BITFLD_PID                               : 5;
    volatile uint16_t                                          : 3;
    volatile uint16_t BITFLD_PUPD                              : 2;
};
#define PID                                   (0x001F)
#define PUPD                                  (0x0300)



#define P02_MODE_REG                         (0x5000300A) /* P02 Mode Register */
#define P02_MODE_REG_RESET                   (0x00000200)

/*=============================*/
struct __P02_MODE_REG
/*=============================*/
{
    volatile uint16_t BITFLD_PID                               : 5;
    volatile uint16_t                                          : 3;
    volatile uint16_t BITFLD_PUPD                              : 2;
};
#define PID                                   (0x001F)
#define PUPD                                  (0x0300)



#define P03_MODE_REG                         (0x5000300C) /* P03 Mode Register */
#define P03_MODE_REG_RESET                   (0x00000200)

/*=============================*/
struct __P03_MODE_REG
/*=============================*/
{
    volatile uint16_t BITFLD_PID                               : 5;
    volatile uint16_t                                          : 3;
    volatile uint16_t BITFLD_PUPD                              : 2;
};
#define PID                                   (0x001F)
#define PUPD                                  (0x0300)



#define P04_MODE_REG                         (0x5000300E) /* P04 Mode Register */
#define P04_MODE_REG_RESET                   (0x00000200)

/*=============================*/
struct __P04_MODE_REG
/*=============================*/
{
    volatile uint16_t BITFLD_PID                               : 5;
    volatile uint16_t                                          : 3;
    volatile uint16_t BITFLD_PUPD                              : 2;
};
#define PID                                   (0x001F)
#define PUPD                                  (0x0300)



#define P05_MODE_REG                         (0x50003010) /* P05 Mode Register */
#define P05_MODE_REG_RESET                   (0x00000200)

/*=============================*/
struct __P05_MODE_REG
/*=============================*/
{
    volatile uint16_t BITFLD_PID                               : 5;
    volatile uint16_t                                          : 3;
    volatile uint16_t BITFLD_PUPD                              : 2;
};
#define PID                                   (0x001F)
#define PUPD                                  (0x0300)



#define P06_MODE_REG                         (0x50003012) /* P06 Mode Register */
#define P06_MODE_REG_RESET                   (0x00000200)

/*=============================*/
struct __P06_MODE_REG
/*=============================*/
{
    volatile uint16_t BITFLD_PID                               : 5;
    volatile uint16_t                                          : 3;
    volatile uint16_t BITFLD_PUPD                              : 2;
};
#define PID                                   (0x001F)
#define PUPD                                  (0x0300)



#define P07_MODE_REG                         (0x50003014) /* P07 Mode Register */
#define P07_MODE_REG_RESET                   (0x00000200)

/*=============================*/
struct __P07_MODE_REG
/*=============================*/
{
    volatile uint16_t BITFLD_PID                               : 5;
    volatile uint16_t                                          : 3;
    volatile uint16_t BITFLD_PUPD                              : 2;
};
#define PID                                   (0x001F)
#define PUPD                                  (0x0300)



#define P08_MODE_REG                         (0x50003016) /* P08 Mode Register */
#define P08_MODE_REG_RESET                   (0x00000200)

/*=============================*/
struct __P08_MODE_REG
/*=============================*/
{
    volatile uint16_t BITFLD_PID                               : 5;
    volatile uint16_t                                          : 3;
    volatile uint16_t BITFLD_PUPD                              : 2;
};
#define PID                                   (0x001F)
#define PUPD                                  (0x0300)



#define P09_MODE_REG                         (0x50003018) /* P09 Mode Register */
#define P09_MODE_REG_RESET                   (0x00000200)

/*=============================*/
struct __P09_MODE_REG
/*=============================*/
{
    volatile uint16_t BITFLD_PID                               : 5;
    volatile uint16_t                                          : 3;
    volatile uint16_t BITFLD_PUPD                              : 2;
};
#define PID                                   (0x001F)
#define PUPD                                  (0x0300)



#define P010_MODE_REG                        (0x5000301A) /* P010 Mode Register */
#define P010_MODE_REG_RESET                  (0x00000200)

/*=============================*/
struct __P010_MODE_REG
/*=============================*/
{
    volatile uint16_t BITFLD_PID                               : 5;
    volatile uint16_t                                          : 3;
    volatile uint16_t BITFLD_PUPD                              : 2;
};
#define PID                                   (0x001F)
#define PUPD                                  (0x0300)



#define P011_MODE_REG                        (0x5000301C) /* P011 Mode Register */
#define P011_MODE_REG_RESET                  (0x00000200)

/*=============================*/
struct __P011_MODE_REG
/*=============================*/
{
    volatile uint16_t BITFLD_PID                               : 5;
    volatile uint16_t                                          : 3;
    volatile uint16_t BITFLD_PUPD                              : 2;
};
#define PID                                   (0x001F)
#define PUPD                                  (0x0300)



#define PAD_WEAK_CTRL_REG                    (0x5000301E) /* Pad driving strength control Register */
#define PAD_WEAK_CTRL_REG_RESET              (0x00000000)

/*=============================*/
struct __PAD_WEAK_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_PAD_LOW_DRV                       : 12;
};
#define PAD_LOW_DRV                           (0x0FFF)



/*===========================================================================*/
/* memory map GPREG */
/*===========================================================================*/



#define SET_FREEZE_REG                       (0x50003300) /* Controls freezing of various timers/counters. */
#define SET_FREEZE_REG_RESET                 (0x00000000)

/*=============================*/
struct __SET_FREEZE_REG
/*=============================*/
{
    volatile uint16_t BITFLD_FRZ_WKUPTIM                       : 1;
    volatile uint16_t BITFLD_FRZ_SWTIM                         : 1;
    volatile uint16_t BITFLD_FRZ_BLETIM                        : 1;
    volatile uint16_t BITFLD_FRZ_WDOG                          : 1;
    volatile uint16_t BITFLD_FRZ_DMA                           : 1;
};
#define FRZ_WKUPTIM                           (0x0001)
#define FRZ_SWTIM                             (0x0002)
#define FRZ_BLETIM                            (0x0004)
#define FRZ_WDOG                              (0x0008)
#define FRZ_DMA                               (0x0010)



#define RESET_FREEZE_REG                     (0x50003302) /* Controls unfreezing of various timers/counters. */
#define RESET_FREEZE_REG_RESET               (0x00000000)

/*=============================*/
struct __RESET_FREEZE_REG
/*=============================*/
{
    volatile uint16_t BITFLD_FRZ_WKUPTIM                       : 1;
    volatile uint16_t BITFLD_FRZ_SWTIM                         : 1;
    volatile uint16_t BITFLD_FRZ_BLETIM                        : 1;
    volatile uint16_t BITFLD_FRZ_WDOG                          : 1;
    volatile uint16_t BITFLD_FRZ_DMA                           : 1;
};
#define FRZ_WKUPTIM                           (0x0001)
#define FRZ_SWTIM                             (0x0002)
#define FRZ_BLETIM                            (0x0004)
#define FRZ_WDOG                              (0x0008)
#define FRZ_DMA                               (0x0010)



#define DEBUG_REG                            (0x50003304) /* Various debug information register. */
#define DEBUG_REG_RESET                      (0x00000001)

/*=============================*/
struct __DEBUG_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DEBUGS_FREEZE_EN                  : 1;
};
#define DEBUGS_FREEZE_EN                      (0x0001)



#define GP_STATUS_REG                        (0x50003306) /* General purpose system status register. */
#define GP_STATUS_REG_RESET                  (0x00000000)

/*=============================*/
struct __GP_STATUS_REG
/*=============================*/
{
    volatile uint16_t BITFLD_CAL_PHASE                         : 1;
    volatile uint16_t                                          : 1;
};
#define CAL_PHASE                             (0x0001)



#define GP_CONTROL_REG                       (0x50003308) /* General purpose system control register. */
#define GP_CONTROL_REG_RESET                 (0x00000000)

/*=============================*/
struct __GP_CONTROL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_BLE_WAKEUP_REQ                    : 1;
    volatile uint16_t                                          : 1;
    volatile uint16_t BITFLD_BLE_WAKEUP_LP_IRQ                 : 1;
    volatile uint16_t                                          : 1;
    volatile uint16_t BITFLD_CPU_DMA_BUS_PRIO                  : 1;
    volatile uint16_t BITFLD_BLE_TIMER_DATA_CTRL               : 2;
};
#define BLE_WAKEUP_REQ                        (0x0001)
#define BLE_WAKEUP_LP_IRQ                     (0x0004)
#define CPU_DMA_BUS_PRIO                      (0x0010)
#define BLE_TIMER_DATA_CTRL                   (0x0060)



#define BLE_TIMER_REG                        (0x5000330A) /* BLE FINECNT sampled value while in deep sleep state. */
#define BLE_TIMER_REG_RESET                  (0x00000000)

/*=============================*/
struct __BLE_TIMER_REG
/*=============================*/
{
    volatile uint16_t BITFLD_BLE_TIMER_DATA                    : 10;
};
#define BLE_TIMER_DATA                        (0x03FF)



/*===========================================================================*/
/* memory map I2C */
/*===========================================================================*/



#define I2C_CON_REG                          (0x50001300) /* I2C Control Register */
#define I2C_CON_REG_RESET                    (0x0000007D)

/*=============================*/
struct __I2C_CON_REG
/*=============================*/
{
    volatile uint16_t BITFLD_I2C_MASTER_MODE                   : 1;
    volatile uint16_t BITFLD_I2C_SPEED                         : 2;
    volatile uint16_t BITFLD_I2C_10BITADDR_SLAVE               : 1;
    volatile uint16_t BITFLD_I2C_10BITADDR_MASTER              : 1;
    volatile uint16_t BITFLD_I2C_RESTART_EN                    : 1;
    volatile uint16_t BITFLD_I2C_SLAVE_DISABLE                 : 1;
};
#define I2C_MASTER_MODE                       (0x0001)
#define I2C_SPEED                             (0x0006)
#define I2C_10BITADDR_SLAVE                   (0x0008)
#define I2C_10BITADDR_MASTER                  (0x0010)
#define I2C_RESTART_EN                        (0x0020)
#define I2C_SLAVE_DISABLE                     (0x0040)



#define I2C_TAR_REG                          (0x50001304) /* I2C Target Address Register */
#define I2C_TAR_REG_RESET                    (0x00000055)

/*=============================*/
struct __I2C_TAR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_IC_TAR                            : 10;
    volatile uint16_t BITFLD_GC_OR_START                       : 1;
    volatile uint16_t BITFLD_SPECIAL                           : 1;
};
#define IC_TAR                                (0x03FF)
#define GC_OR_START                           (0x0400)
#define SPECIAL                               (0x0800)



#define I2C_SAR_REG                          (0x50001308) /* I2C Slave Address Register */
#define I2C_SAR_REG_RESET                    (0x00000055)

/*=============================*/
struct __I2C_SAR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_IC_SAR                            : 10;
};
#define IC_SAR                                (0x03FF)



#define I2C_DATA_CMD_REG                     (0x50001310) /* I2C Rx/Tx Data Buffer and Command Register */
#define I2C_DATA_CMD_REG_RESET               (0x00000000)

/*=============================*/
struct __I2C_DATA_CMD_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DAT                               : 8;
    volatile uint16_t BITFLD_I2C_CMD                           : 1;
    volatile uint16_t BITFLD_I2C_STOP                          : 1;
    volatile uint16_t BITFLD_I2C_RESTART                       : 1;
};
#define DAT                                   (0x00FF)
#define I2C_CMD                               (0x0100)
#define I2C_STOP                              (0x0200)
#define I2C_RESTART                           (0x0400)



#define I2C_SS_SCL_HCNT_REG                  (0x50001314) /* Standard Speed I2C Clock SCL High Count Register */
#define I2C_SS_SCL_HCNT_REG_RESET            (0x00000048)

/*=============================*/
struct __I2C_SS_SCL_HCNT_REG
/*=============================*/
{
    volatile uint16_t BITFLD_IC_SS_SCL_HCNT                    : 16;
};
#define IC_SS_SCL_HCNT                        (0xFFFF)



#define I2C_SS_SCL_LCNT_REG                  (0x50001318) /* Standard Speed I2C Clock SCL Low Count Register */
#define I2C_SS_SCL_LCNT_REG_RESET            (0x0000004F)

/*=============================*/
struct __I2C_SS_SCL_LCNT_REG
/*=============================*/
{
    volatile uint16_t BITFLD_IC_SS_SCL_LCNT                    : 16;
};
#define IC_SS_SCL_LCNT                        (0xFFFF)



#define I2C_FS_SCL_HCNT_REG                  (0x5000131C) /* Fast Speed I2C Clock SCL High Count Register */
#define I2C_FS_SCL_HCNT_REG_RESET            (0x00000008)

/*=============================*/
struct __I2C_FS_SCL_HCNT_REG
/*=============================*/
{
    volatile uint16_t BITFLD_IC_FS_SCL_HCNT                    : 16;
};
#define IC_FS_SCL_HCNT                        (0xFFFF)



#define I2C_FS_SCL_LCNT_REG                  (0x50001320) /* Fast Speed I2C Clock SCL Low Count Register */
#define I2C_FS_SCL_LCNT_REG_RESET            (0x00000017)

/*=============================*/
struct __I2C_FS_SCL_LCNT_REG
/*=============================*/
{
    volatile uint16_t BITFLD_IC_FS_SCL_LCNT                    : 16;
};
#define IC_FS_SCL_LCNT                        (0xFFFF)



#define I2C_INTR_STAT_REG                    (0x5000132C) /* I2C Interrupt Status Register */
#define I2C_INTR_STAT_REG_RESET              (0x00000000)

/*=============================*/
struct __I2C_INTR_STAT_REG
/*=============================*/
{
    volatile uint16_t BITFLD_R_RX_UNDER                        : 1;
    volatile uint16_t BITFLD_R_RX_OVER                         : 1;
    volatile uint16_t BITFLD_R_RX_FULL                         : 1;
    volatile uint16_t BITFLD_R_TX_OVER                         : 1;
    volatile uint16_t BITFLD_R_TX_EMPTY                        : 1;
    volatile uint16_t BITFLD_R_RD_REQ                          : 1;
    volatile uint16_t BITFLD_R_TX_ABRT                         : 1;
    volatile uint16_t BITFLD_R_RX_DONE                         : 1;
    volatile uint16_t BITFLD_R_ACTIVITY                        : 1;
    volatile uint16_t BITFLD_R_STOP_DET                        : 1;
    volatile uint16_t BITFLD_R_START_DET                       : 1;
    volatile uint16_t BITFLD_R_GEN_CALL                        : 1;
};
#define R_RX_UNDER                            (0x0001)
#define R_RX_OVER                             (0x0002)
#define R_RX_FULL                             (0x0004)
#define R_TX_OVER                             (0x0008)
#define R_TX_EMPTY                            (0x0010)
#define R_RD_REQ                              (0x0020)
#define R_TX_ABRT                             (0x0040)
#define R_RX_DONE                             (0x0080)
#define R_ACTIVITY                            (0x0100)
#define R_STOP_DET                            (0x0200)
#define R_START_DET                           (0x0400)
#define R_GEN_CALL                            (0x0800)



#define I2C_INTR_MASK_REG                    (0x50001330) /* I2C Interrupt Mask Register */
#define I2C_INTR_MASK_REG_RESET              (0x000008FF)

/*=============================*/
struct __I2C_INTR_MASK_REG
/*=============================*/
{
    volatile uint16_t BITFLD_M_RX_UNDER                        : 1;
    volatile uint16_t BITFLD_M_RX_OVER                         : 1;
    volatile uint16_t BITFLD_M_RX_FULL                         : 1;
    volatile uint16_t BITFLD_M_TX_OVER                         : 1;
    volatile uint16_t BITFLD_M_TX_EMPTY                        : 1;
    volatile uint16_t BITFLD_M_RD_REQ                          : 1;
    volatile uint16_t BITFLD_M_TX_ABRT                         : 1;
    volatile uint16_t BITFLD_M_RX_DONE                         : 1;
    volatile uint16_t BITFLD_M_ACTIVITY                        : 1;
    volatile uint16_t BITFLD_M_STOP_DET                        : 1;
    volatile uint16_t BITFLD_M_START_DET                       : 1;
    volatile uint16_t BITFLD_M_GEN_CALL                        : 1;
};
#define M_RX_UNDER                            (0x0001)
#define M_RX_OVER                             (0x0002)
#define M_RX_FULL                             (0x0004)
#define M_TX_OVER                             (0x0008)
#define M_TX_EMPTY                            (0x0010)
#define M_RD_REQ                              (0x0020)
#define M_TX_ABRT                             (0x0040)
#define M_RX_DONE                             (0x0080)
#define M_ACTIVITY                            (0x0100)
#define M_STOP_DET                            (0x0200)
#define M_START_DET                           (0x0400)
#define M_GEN_CALL                            (0x0800)



#define I2C_RAW_INTR_STAT_REG                (0x50001334) /* I2C Raw Interrupt Status Register */
#define I2C_RAW_INTR_STAT_REG_RESET          (0x00000000)

/*=============================*/
struct __I2C_RAW_INTR_STAT_REG
/*=============================*/
{
    volatile uint16_t BITFLD_RX_UNDER                          : 1;
    volatile uint16_t BITFLD_RX_OVER                           : 1;
    volatile uint16_t BITFLD_RX_FULL                           : 1;
    volatile uint16_t BITFLD_TX_OVER                           : 1;
    volatile uint16_t BITFLD_TX_EMPTY                          : 1;
    volatile uint16_t BITFLD_RD_REQ                            : 1;
    volatile uint16_t BITFLD_TX_ABRT                           : 1;
    volatile uint16_t BITFLD_RX_DONE                           : 1;
    volatile uint16_t BITFLD_ACTIVITY                          : 1;
    volatile uint16_t BITFLD_STOP_DET                          : 1;
    volatile uint16_t BITFLD_START_DET                         : 1;
    volatile uint16_t BITFLD_GEN_CALL                          : 1;
};
#define RX_UNDER                              (0x0001)
#define RX_OVER                               (0x0002)
#define RX_FULL                               (0x0004)
#define TX_OVER                               (0x0008)
#define TX_EMPTY                              (0x0010)
#define RD_REQ                                (0x0020)
#define TX_ABRT                               (0x0040)
#define RX_DONE                               (0x0080)
#define ACTIVITY                              (0x0100)
#define STOP_DET                              (0x0200)
#define START_DET                             (0x0400)
#define GEN_CALL                              (0x0800)



#define I2C_RX_TL_REG                        (0x50001338) /* I2C Receive FIFO Threshold Register */
#define I2C_RX_TL_REG_RESET                  (0x00000000)

/*=============================*/
struct __I2C_RX_TL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_RX_TL                             : 5;
};
#define RX_TL                                 (0x001F)



#define I2C_TX_TL_REG                        (0x5000133C) /* I2C Transmit FIFO Threshold Register */
#define I2C_TX_TL_REG_RESET                  (0x00000000)

/*=============================*/
struct __I2C_TX_TL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_RX_TL                             : 5;
};
#define RX_TL                                 (0x001F)



#define I2C_CLR_INTR_REG                     (0x50001340) /* Clear Combined and Individual Interrupt Register */
#define I2C_CLR_INTR_REG_RESET               (0x00000000)

/*=============================*/
struct __I2C_CLR_INTR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_CLR_INTR                          : 1;
};
#define CLR_INTR                              (0x0001)



#define I2C_CLR_RX_UNDER_REG                 (0x50001344) /* Clear RX_UNDER Interrupt Register */
#define I2C_CLR_RX_UNDER_REG_RESET           (0x00000000)

/*=============================*/
struct __I2C_CLR_RX_UNDER_REG
/*=============================*/
{
    volatile uint16_t BITFLD_CLR_RX_UNDER                      : 1;
};
#define CLR_RX_UNDER                          (0x0001)



#define I2C_CLR_RX_OVER_REG                  (0x50001348) /* Clear RX_OVER Interrupt Register */
#define I2C_CLR_RX_OVER_REG_RESET            (0x00000000)

/*=============================*/
struct __I2C_CLR_RX_OVER_REG
/*=============================*/
{
    volatile uint16_t BITFLD_CLR_RX_OVER                       : 1;
};
#define CLR_RX_OVER                           (0x0001)



#define I2C_CLR_TX_OVER_REG                  (0x5000134C) /* Clear TX_OVER Interrupt Register */
#define I2C_CLR_TX_OVER_REG_RESET            (0x00000000)

/*=============================*/
struct __I2C_CLR_TX_OVER_REG
/*=============================*/
{
    volatile uint16_t BITFLD_CLR_TX_OVER                       : 1;
};
#define CLR_TX_OVER                           (0x0001)



#define I2C_CLR_RD_REQ_REG                   (0x50001350) /* Clear RD_REQ Interrupt Register */
#define I2C_CLR_RD_REQ_REG_RESET             (0x00000000)

/*=============================*/
struct __I2C_CLR_RD_REQ_REG
/*=============================*/
{
    volatile uint16_t BITFLD_CLR_RD_REQ                        : 1;
};
#define CLR_RD_REQ                            (0x0001)



#define I2C_CLR_TX_ABRT_REG                  (0x50001354) /* Clear TX_ABRT Interrupt Register */
#define I2C_CLR_TX_ABRT_REG_RESET            (0x00000000)

/*=============================*/
struct __I2C_CLR_TX_ABRT_REG
/*=============================*/
{
    volatile uint16_t BITFLD_CLR_TX_ABRT                       : 1;
};
#define CLR_TX_ABRT                           (0x0001)



#define I2C_CLR_RX_DONE_REG                  (0x50001358) /* Clear RX_DONE Interrupt Register */
#define I2C_CLR_RX_DONE_REG_RESET            (0x00000000)

/*=============================*/
struct __I2C_CLR_RX_DONE_REG
/*=============================*/
{
    volatile uint16_t BITFLD_CLR_RX_DONE                       : 1;
};
#define CLR_RX_DONE                           (0x0001)



#define I2C_CLR_ACTIVITY_REG                 (0x5000135C) /* Clear ACTIVITY Interrupt Register */
#define I2C_CLR_ACTIVITY_REG_RESET           (0x00000000)

/*=============================*/
struct __I2C_CLR_ACTIVITY_REG
/*=============================*/
{
    volatile uint16_t BITFLD_CLR_ACTIVITY                      : 1;
};
#define CLR_ACTIVITY                          (0x0001)



#define I2C_CLR_STOP_DET_REG                 (0x50001360) /* Clear STOP_DET Interrupt Register */
#define I2C_CLR_STOP_DET_REG_RESET           (0x00000000)

/*=============================*/
struct __I2C_CLR_STOP_DET_REG
/*=============================*/
{
    volatile uint16_t BITFLD_CLR_STOP_DET                      : 1;
};
#define CLR_STOP_DET                          (0x0001)



#define I2C_CLR_START_DET_REG                (0x50001364) /* Clear START_DET Interrupt Register */
#define I2C_CLR_START_DET_REG_RESET          (0x00000000)

/*=============================*/
struct __I2C_CLR_START_DET_REG
/*=============================*/
{
    volatile uint16_t BITFLD_CLR_START_DET                     : 1;
};
#define CLR_START_DET                         (0x0001)



#define I2C_CLR_GEN_CALL_REG                 (0x50001368) /* Clear GEN_CALL Interrupt Register */
#define I2C_CLR_GEN_CALL_REG_RESET           (0x00000000)

/*=============================*/
struct __I2C_CLR_GEN_CALL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_CLR_GEN_CALL                      : 1;
};
#define CLR_GEN_CALL                          (0x0001)



#define I2C_ENABLE_REG                       (0x5000136C) /* I2C Enable Register */
#define I2C_ENABLE_REG_RESET                 (0x00000000)

/*=============================*/
struct __I2C_ENABLE_REG
/*=============================*/
{
    volatile uint16_t BITFLD_CTRL_ENABLE                       : 1;
    volatile uint16_t BITFLD_I2C_ABORT                         : 1;
};
#define CTRL_ENABLE                           (0x0001)
#define I2C_ABORT                             (0x0002)



#define I2C_STATUS_REG                       (0x50001370) /* I2C Status Register */
#define I2C_STATUS_REG_RESET                 (0x00000006)

/*=============================*/
struct __I2C_STATUS_REG
/*=============================*/
{
    volatile uint16_t BITFLD_I2C_ACTIVITY                      : 1;
    volatile uint16_t BITFLD_TFNF                              : 1;
    volatile uint16_t BITFLD_TFE                               : 1;
    volatile uint16_t BITFLD_RFNE                              : 1;
    volatile uint16_t BITFLD_RFF                               : 1;
    volatile uint16_t BITFLD_MST_ACTIVITY                      : 1;
    volatile uint16_t BITFLD_SLV_ACTIVITY                      : 1;
};
#define I2C_ACTIVITY                          (0x0001)
#define TFNF                                  (0x0002)
#define TFE                                   (0x0004)
#define RFNE                                  (0x0008)
#define RFF                                   (0x0010)
#define MST_ACTIVITY                          (0x0020)
#define SLV_ACTIVITY                          (0x0040)



#define I2C_TXFLR_REG                        (0x50001374) /* I2C Transmit FIFO Level Register */
#define I2C_TXFLR_REG_RESET                  (0x00000000)

/*=============================*/
struct __I2C_TXFLR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_TXFLR                             : 6;
};
#define TXFLR                                 (0x003F)



#define I2C_RXFLR_REG                        (0x50001378) /* I2C Receive FIFO Level Register */
#define I2C_RXFLR_REG_RESET                  (0x00000000)

/*=============================*/
struct __I2C_RXFLR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_RXFLR                             : 6;
};
#define RXFLR                                 (0x003F)



#define I2C_SDA_HOLD_REG                     (0x5000137C) /* I2C SDA Hold Time Length Register */
#define I2C_SDA_HOLD_REG_RESET               (0x00000001)

/*=============================*/
struct __I2C_SDA_HOLD_REG
/*=============================*/
{
    volatile uint16_t BITFLD_IC_SDA_HOLD                       : 16;
};
#define IC_SDA_HOLD                           (0xFFFF)



#define I2C_TX_ABRT_SOURCE_REG               (0x50001380) /* I2C Transmit Abort Source Register */
#define I2C_TX_ABRT_SOURCE_REG_RESET         (0x00000000)

/*=============================*/
struct __I2C_TX_ABRT_SOURCE_REG
/*=============================*/
{
    volatile uint16_t BITFLD_ABRT_7B_ADDR_NOACK                : 1;
    volatile uint16_t BITFLD_ABRT_10ADDR1_NOACK                : 1;
    volatile uint16_t BITFLD_ABRT_10ADDR2_NOACK                : 1;
    volatile uint16_t BITFLD_ABRT_TXDATA_NOACK                 : 1;
    volatile uint16_t BITFLD_ABRT_GCALL_NOACK                  : 1;
    volatile uint16_t BITFLD_ABRT_GCALL_READ                   : 1;
    volatile uint16_t BITFLD_ABRT_HS_ACKDET                    : 1;
    volatile uint16_t BITFLD_ABRT_SBYTE_ACKDET                 : 1;
    volatile uint16_t BITFLD_ABRT_HS_NORSTRT                   : 1;
    volatile uint16_t BITFLD_ABRT_SBYTE_NORSTRT                : 1;
    volatile uint16_t BITFLD_ABRT_10B_RD_NORSTRT               : 1;
    volatile uint16_t BITFLD_ABRT_MASTER_DIS                   : 1;
    volatile uint16_t BITFLD_ARB_LOST                          : 1;
    volatile uint16_t BITFLD_ABRT_SLVFLUSH_TXFIFO              : 1;
    volatile uint16_t BITFLD_ABRT_SLV_ARBLOST                  : 1;
    volatile uint16_t BITFLD_ABRT_SLVRD_INTX                   : 1;
};
#define ABRT_7B_ADDR_NOACK                    (0x0001)
#define ABRT_10ADDR1_NOACK                    (0x0002)
#define ABRT_10ADDR2_NOACK                    (0x0004)
#define ABRT_TXDATA_NOACK                     (0x0008)
#define ABRT_GCALL_NOACK                      (0x0010)
#define ABRT_GCALL_READ                       (0x0020)
#define ABRT_HS_ACKDET                        (0x0040)
#define ABRT_SBYTE_ACKDET                     (0x0080)
#define ABRT_HS_NORSTRT                       (0x0100)
#define ABRT_SBYTE_NORSTRT                    (0x0200)
#define ABRT_10B_RD_NORSTRT                   (0x0400)
#define ABRT_MASTER_DIS                       (0x0800)
#define ARB_LOST                              (0x1000)
#define ABRT_SLVFLUSH_TXFIFO                  (0x2000)
#define ABRT_SLV_ARBLOST                      (0x4000)
#define ABRT_SLVRD_INTX                       (0x8000)



#define I2C_DMA_CR_REG                       (0x50001388) /* DMA Control Register */
#define I2C_DMA_CR_REG_RESET                 (0x00000000)

/*=============================*/
struct __I2C_DMA_CR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_RDMAE                             : 1;
    volatile uint16_t BITFLD_TDMAE                             : 1;
};
#define RDMAE                                 (0x0001)
#define TDMAE                                 (0x0002)



#define I2C_DMA_TDLR_REG                     (0x5000138C) /* DMA Transmit Data Level Register */
#define I2C_DMA_TDLR_REG_RESET               (0x00000000)

/*=============================*/
struct __I2C_DMA_TDLR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMATDL                            : 5;
};
#define DMATDL                                (0x001F)



#define I2C_DMA_RDLR_REG                     (0x50001390) /* I2C Receive Data Level Register */
#define I2C_DMA_RDLR_REG_RESET               (0x00000000)

/*=============================*/
struct __I2C_DMA_RDLR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMARDL                            : 5;
};
#define DMARDL                                (0x001F)



#define I2C_SDA_SETUP_REG                    (0x50001394) /* I2C SDA Setup Register */
#define I2C_SDA_SETUP_REG_RESET              (0x00000064)

/*=============================*/
struct __I2C_SDA_SETUP_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SDA_SETUP                         : 8;
};
#define SDA_SETUP                             (0x00FF)



#define I2C_ACK_GENERAL_CALL_REG             (0x50001398) /* I2C ACK General Call Register */
#define I2C_ACK_GENERAL_CALL_REG_RESET       (0x00000000)

/*=============================*/
struct __I2C_ACK_GENERAL_CALL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_ACK_GEN_CALL                      : 1;
};
#define ACK_GEN_CALL                          (0x0001)



#define I2C_ENABLE_STATUS_REG                (0x5000139C) /* I2C Enable Status Register */
#define I2C_ENABLE_STATUS_REG_RESET          (0x00000000)

/*=============================*/
struct __I2C_ENABLE_STATUS_REG
/*=============================*/
{
    volatile uint16_t BITFLD_IC_EN                             : 1;
    volatile uint16_t BITFLD_SLV_DISABLED_WHILE_BUSY           : 1;
    volatile uint16_t BITFLD_SLV_RX_DATA_LOST                  : 1;
};
#define IC_EN                                 (0x0001)
#define SLV_DISABLED_WHILE_BUSY               (0x0002)
#define SLV_RX_DATA_LOST                      (0x0004)



#define I2C_IC_FS_SPKLEN_REG                 (0x500013A0) /* I2C SS and FS spike suppression limit Size */
#define I2C_IC_FS_SPKLEN_REG_RESET           (0x00000001)

/*=============================*/
struct __I2C_IC_FS_SPKLEN_REG
/*=============================*/
{
    volatile uint16_t BITFLD_IC_FS_SPKLEN                      : 8;
};
#define IC_FS_SPKLEN                          (0x00FF)



#define I2C_COMP_PARAM1_REG                  (0x500013F4)
#define I2C_COMP_PARAM1_REG_RESET            (0x00000000)

/*=============================*/
struct __I2C_COMP_PARAM1_REG
/*=============================*/
{
    volatile uint16_t BITFLD_IC_COMP_PARAM1                    : 16;
};
#define IC_COMP_PARAM1                        (0xFFFF)



#define I2C_COMP_PARAM2_REG                  (0x500013F6)
#define I2C_COMP_PARAM2_REG_RESET            (0x00000000)

/*=============================*/
struct __I2C_COMP_PARAM2_REG
/*=============================*/
{
    volatile uint16_t BITFLD_IC_COMP_PARAM2                    : 16;
};
#define IC_COMP_PARAM2                        (0xFFFF)



#define I2C_COMP_VERSION_REG                 (0x500013F8)
#define I2C_COMP_VERSION_REG_RESET           (0x0000302A)

/*=============================*/
struct __I2C_COMP_VERSION_REG
/*=============================*/
{
    volatile uint16_t BITFLD_IC_COMP_VERSION                   : 16;
};
#define IC_COMP_VERSION                       (0xFFFF)



#define I2C_COMP2_VERSION                    (0x500013FA)
#define I2C_COMP2_VERSION_RESET              (0x00003132)

/*=============================*/
struct __I2C_COMP2_VERSION
/*=============================*/
{
    volatile uint16_t BITFLD_IC_COMP2_VERSION                  : 16;
};
#define IC_COMP2_VERSION                      (0xFFFF)



#define I2C_COMP_TYPE_REG                    (0x500013FC)
#define I2C_COMP_TYPE_REG_RESET              (0x00000140)

/*=============================*/
struct __I2C_COMP_TYPE_REG
/*=============================*/
{
    volatile uint16_t BITFLD_IC_COMP_TYPE                      : 16;
};
#define IC_COMP_TYPE                          (0xFFFF)



#define I2C_COMP_TYPE2_REG                   (0x500013FE)
#define I2C_COMP_TYPE2_REG_RESET             (0x00004457)

/*=============================*/
struct __I2C_COMP_TYPE2_REG
/*=============================*/
{
    volatile uint16_t BITFLD_IC_COMP2_TYPE                     : 16;
};
#define IC_COMP2_TYPE                         (0xFFFF)



/*===========================================================================*/
/* memory map KBRD */
/*===========================================================================*/



#define GPIO_IRQ0_IN_SEL_REG                 (0x50001400) /* GPIO interrupt selection for GPIO_IRQ0 */
#define GPIO_IRQ0_IN_SEL_REG_RESET           (0x00000000)

/*=============================*/
struct __GPIO_IRQ0_IN_SEL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_KBRD_IRQ0_SEL                     : 4;
    volatile uint16_t                                          : 2;
};
#define KBRD_IRQ0_SEL                         (0x000F)



#define GPIO_IRQ1_IN_SEL_REG                 (0x50001402) /* GPIO interrupt selection for GPIO_IRQ1 */
#define GPIO_IRQ1_IN_SEL_REG_RESET           (0x00000000)

/*=============================*/
struct __GPIO_IRQ1_IN_SEL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_KBRD_IRQ1_SEL                     : 4;
    volatile uint16_t                                          : 2;
};
#define KBRD_IRQ1_SEL                         (0x000F)



#define GPIO_IRQ2_IN_SEL_REG                 (0x50001404) /* GPIO interrupt selection for GPIO_IRQ2 */
#define GPIO_IRQ2_IN_SEL_REG_RESET           (0x00000000)

/*=============================*/
struct __GPIO_IRQ2_IN_SEL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_KBRD_IRQ2_SEL                     : 4;
    volatile uint16_t                                          : 2;
};
#define KBRD_IRQ2_SEL                         (0x000F)



#define GPIO_IRQ3_IN_SEL_REG                 (0x50001406) /* GPIO interrupt selection for GPIO_IRQ3 */
#define GPIO_IRQ3_IN_SEL_REG_RESET           (0x00000000)

/*=============================*/
struct __GPIO_IRQ3_IN_SEL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_KBRD_IRQ3_SEL                     : 4;
    volatile uint16_t                                          : 2;
};
#define KBRD_IRQ3_SEL                         (0x000F)



#define GPIO_IRQ4_IN_SEL_REG                 (0x50001408) /* GPIO interrupt selection for GPIO_IRQ4 */
#define GPIO_IRQ4_IN_SEL_REG_RESET           (0x00000000)

/*=============================*/
struct __GPIO_IRQ4_IN_SEL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_KBRD_IRQ4_SEL                     : 4;
    volatile uint16_t                                          : 2;
};
#define KBRD_IRQ4_SEL                         (0x000F)



#define GPIO_DEBOUNCE_REG                    (0x5000140C) /* debounce counter value for GPIO inputs */
#define GPIO_DEBOUNCE_REG_RESET              (0x00000000)

/*=============================*/
struct __GPIO_DEBOUNCE_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DEB_VALUE                         : 6;
    volatile uint16_t BITFLD_DEB_ENABLE0                       : 1;
    volatile uint16_t BITFLD_DEB_ENABLE1                       : 1;
    volatile uint16_t BITFLD_DEB_ENABLE2                       : 1;
    volatile uint16_t BITFLD_DEB_ENABLE3                       : 1;
    volatile uint16_t BITFLD_DEB_ENABLE4                       : 1;
    volatile uint16_t BITFLD_DEB_ENABLE_KBRD                   : 1;
};
#define DEB_VALUE                             (0x003F)
#define DEB_ENABLE0                           (0x0040)
#define DEB_ENABLE1                           (0x0080)
#define DEB_ENABLE2                           (0x0100)
#define DEB_ENABLE3                           (0x0200)
#define DEB_ENABLE4                           (0x0400)
#define DEB_ENABLE_KBRD                       (0x0800)



#define GPIO_RESET_IRQ_REG                   (0x5000140E) /* GPIO interrupt reset register */
#define GPIO_RESET_IRQ_REG_RESET             (0x00000000)

/*=============================*/
struct __GPIO_RESET_IRQ_REG
/*=============================*/
{
    volatile uint16_t BITFLD_RESET_GPIO0_IRQ                   : 1;
    volatile uint16_t BITFLD_RESET_GPIO1_IRQ                   : 1;
    volatile uint16_t BITFLD_RESET_GPIO2_IRQ                   : 1;
    volatile uint16_t BITFLD_RESET_GPIO3_IRQ                   : 1;
    volatile uint16_t BITFLD_RESET_GPIO4_IRQ                   : 1;
    volatile uint16_t BITFLD_RESET_KBRD_IRQ                    : 1;
};
#define RESET_GPIO0_IRQ                       (0x0001)
#define RESET_GPIO1_IRQ                       (0x0002)
#define RESET_GPIO2_IRQ                       (0x0004)
#define RESET_GPIO3_IRQ                       (0x0008)
#define RESET_GPIO4_IRQ                       (0x0010)
#define RESET_KBRD_IRQ                        (0x0020)



#define GPIO_INT_LEVEL_CTRL_REG              (0x50001410) /* high or low level select for GPIO interrupts */
#define GPIO_INT_LEVEL_CTRL_REG_RESET        (0x00000000)

/*=============================*/
struct __GPIO_INT_LEVEL_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_INPUT_LEVEL0                      : 1;
    volatile uint16_t BITFLD_INPUT_LEVEL1                      : 1;
    volatile uint16_t BITFLD_INPUT_LEVEL2                      : 1;
    volatile uint16_t BITFLD_INPUT_LEVEL3                      : 1;
    volatile uint16_t BITFLD_INPUT_LEVEL4                      : 1;
    volatile uint16_t BITFLD_EDGE_LEVELn0                      : 1;
    volatile uint16_t BITFLD_EDGE_LEVELn1                      : 1;
    volatile uint16_t BITFLD_EDGE_LEVELn2                      : 1;
    volatile uint16_t BITFLD_EDGE_LEVELn3                      : 1;
    volatile uint16_t BITFLD_EDGE_LEVELn4                      : 1;
};
#define INPUT_LEVEL0                          (0x0001)
#define INPUT_LEVEL1                          (0x0002)
#define INPUT_LEVEL2                          (0x0004)
#define INPUT_LEVEL3                          (0x0008)
#define INPUT_LEVEL4                          (0x0010)
#define EDGE_LEVELn0                          (0x0020)
#define EDGE_LEVELn1                          (0x0040)
#define EDGE_LEVELn2                          (0x0080)
#define EDGE_LEVELn3                          (0x0100)
#define EDGE_LEVELn4                          (0x0200)



#define KBRD_IRQ_IN_SEL0_REG                 (0x50001412) /* GPIO interrupt selection for KBRD_IRQ for P0 */
#define KBRD_IRQ_IN_SEL0_REG_RESET           (0x00000000)

/*=============================*/
struct __KBRD_IRQ_IN_SEL0_REG
/*=============================*/
{
    volatile uint16_t BITFLD_KBRD_P00_EN                       : 1;
    volatile uint16_t BITFLD_KBRD_P01_EN                       : 1;
    volatile uint16_t BITFLD_KBRD_P02_EN                       : 1;
    volatile uint16_t BITFLD_KBRD_P03_EN                       : 1;
    volatile uint16_t BITFLD_KBRD_P04_EN                       : 1;
    volatile uint16_t BITFLD_KBRD_P05_EN                       : 1;
    volatile uint16_t BITFLD_KBRD_P06_EN                       : 1;
    volatile uint16_t BITFLD_KBRD_P07_EN                       : 1;
    volatile uint16_t BITFLD_KBRD_P08_EN                       : 1;
    volatile uint16_t BITFLD_KBRD_P09_EN                       : 1;
    volatile uint16_t BITFLD_KBRD_P10_EN                       : 1;
    volatile uint16_t BITFLD_KBRD_P11_EN                       : 1;
};
#define KBRD_P00_EN                           (0x0001)
#define KBRD_P01_EN                           (0x0002)
#define KBRD_P02_EN                           (0x0004)
#define KBRD_P03_EN                           (0x0008)
#define KBRD_P04_EN                           (0x0010)
#define KBRD_P05_EN                           (0x0020)
#define KBRD_P06_EN                           (0x0040)
#define KBRD_P07_EN                           (0x0080)
#define KBRD_P08_EN                           (0x0100)
#define KBRD_P09_EN                           (0x0200)
#define KBRD_P10_EN                           (0x0400)
#define KBRD_P11_EN                           (0x0800)



#define KBRD_CTRL_REG                        (0x50001414) /* GPIO Kbrd control register */
#define KBRD_CTRL_REG_RESET                  (0x00000000)

/*=============================*/
struct __KBRD_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_KEY_REPEAT                        : 6;
    volatile uint16_t BITFLD_KBRD_LEVEL                        : 1;
    volatile uint16_t BITFLD_KBRD_REL                          : 1;
};
#define KEY_REPEAT                            (0x003F)
#define KBRD_LEVEL                            (0x0040)
#define KBRD_REL                              (0x0080)



/*===========================================================================*/
/* memory map OTPC */
/*===========================================================================*/



#define OTPC_MODE_REG                        (0x07F40000) /* Mode register */
#define OTPC_MODE_REG_RESET                  (0x00000000)

/*=============================*/
struct __OTPC_MODE_REG
/*=============================*/
{
    volatile uint32_t BITFLD_OTPC_MODE_MODE                    : 3;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_OTPC_MODE_USE_TST_ROW             : 1;
    volatile uint32_t BITFLD_OTPC_MODE_HT_MARG_EN              : 1;
    volatile uint32_t BITFLD_OTPC_MODE_PRG_SEL                 : 2;
};
#define OTPC_MODE_MODE                        (0x0007)
#define OTPC_MODE_USE_TST_ROW                 (0x0010)
#define OTPC_MODE_HT_MARG_EN                  (0x0020)
#define OTPC_MODE_PRG_SEL                     (0x00C0)



#define OTPC_STAT_REG                        (0x07F40004) /* Status register */
#define OTPC_STAT_REG_RESET                  (0x00000007)

/*=============================*/
struct __OTPC_STAT_REG
/*=============================*/
{
    volatile uint32_t BITFLD_OTPC_STAT_PRDY                    : 1;
    volatile uint32_t BITFLD_OTPC_STAT_PBUF_EMPTY              : 1;
    volatile uint32_t BITFLD_OTPC_STAT_MRDY                    : 1;
};
#define OTPC_STAT_PRDY                        (0x0001)
#define OTPC_STAT_PBUF_EMPTY                  (0x0002)
#define OTPC_STAT_MRDY                        (0x0004)



#define OTPC_PADDR_REG                       (0x07F40008) /* The address of the word that will be programmed, when the PROG mode is used. */
#define OTPC_PADDR_REG_RESET                 (0x00000000)

/*=============================*/
struct __OTPC_PADDR_REG
/*=============================*/
{
    volatile uint32_t BITFLD_OTPC_PADDR                        : 13;
};
#define OTPC_PADDR                            (0x1FFF)



#define OTPC_PWORD_REG                       (0x07F4000C) /* The 32-bit word that will be programmed, when the PROG mode is used. */
#define OTPC_PWORD_REG_RESET                 (0x00000000)

/*=============================*/
struct __OTPC_PWORD_REG
/*=============================*/
{
    volatile uint32_t BITFLD_OTPC_PWORD                        : 32;
};
#define OTPC_PWORD                            (0xFFFFFFFF)



#define OTPC_TIM1_REG                        (0x07F40010) /* Various timing parameters of the OTP cell. */
#define OTPC_TIM1_REG_RESET                  (0x0999000F)

/*=============================*/
struct __OTPC_TIM1_REG
/*=============================*/
{
    volatile uint32_t BITFLD_OTPC_TIM1_CC_T_1US                : 7;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_OTPC_TIM1_CC_T_20NS               : 2;
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_OTPC_TIM1_CC_T_RD                 : 3;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_OTPC_TIM1_US_T_PL                 : 4;
    volatile uint32_t BITFLD_OTPC_TIM1_US_T_CS                 : 4;
    volatile uint32_t BITFLD_OTPC_TIM1_US_T_CSP                : 7;
};
#define OTPC_TIM1_CC_T_1US                    (0x007F)
#define OTPC_TIM1_CC_T_20NS                   (0x0300)
#define OTPC_TIM1_CC_T_RD                     (0x7000)
#define OTPC_TIM1_US_T_PL                     (0xF0000)
#define OTPC_TIM1_US_T_CS                     (0xF00000)
#define OTPC_TIM1_US_T_CSP                    (0x7F000000)



#define OTPC_TIM2_REG                        (0x07F40014) /* Various timing parameters of the OTP cell. */
#define OTPC_TIM2_REG_RESET                  (0xA4040409)

/*=============================*/
struct __OTPC_TIM2_REG
/*=============================*/
{
    volatile uint32_t BITFLD_OTPC_TIM2_US_T_PW                 : 5;
    volatile uint32_t BITFLD_OTPC_TIM2_US_T_PWI                : 3;
    volatile uint32_t BITFLD_OTPC_TIM2_US_T_PPR                : 7;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_OTPC_TIM2_US_T_PPS                : 5;
    volatile uint32_t BITFLD_OTPC_TIM2_US_T_VDS                : 3;
    volatile uint32_t BITFLD_OTPC_TIM2_US_T_PPH                : 5;
    volatile uint32_t BITFLD_OTPC_TIM2_US_T_SAS                : 2;
    volatile uint32_t BITFLD_OTPC_TIM2_US_ADD_CC_EN            : 1;
};
#define OTPC_TIM2_US_T_PW                     (0x001F)
#define OTPC_TIM2_US_T_PWI                    (0x00E0)
#define OTPC_TIM2_US_T_PPR                    (0x7F00)
#define OTPC_TIM2_US_T_PPS                    (0x1F0000)
#define OTPC_TIM2_US_T_VDS                    (0xE00000)
#define OTPC_TIM2_US_T_PPH                    (0x1F000000)
#define OTPC_TIM2_US_T_SAS                    (0x60000000)
#define OTPC_TIM2_US_ADD_CC_EN                (0x80000000)



#define OTPC_AHBADR_REG                      (0x07F40018) /* AHB master start address */
#define OTPC_AHBADR_REG_RESET                (0x00000000)

/*=============================*/
struct __OTPC_AHBADR_REG
/*=============================*/
{
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_OTPC_AHBADR                       : 14;
};
#define OTPC_AHBADR                           (0xFFFC)



#define OTPC_CELADR_REG                      (0x07F4001C) /* OTP cell start address */
#define OTPC_CELADR_REG_RESET                (0x00000000)

/*=============================*/
struct __OTPC_CELADR_REG
/*=============================*/
{
    volatile uint32_t BITFLD_OTPC_CELADR                       : 13;
};
#define OTPC_CELADR                           (0x1FFF)



#define OTPC_NWORDS_REG                      (0x07F40020) /* Number of words */
#define OTPC_NWORDS_REG_RESET                (0x00000000)

/*=============================*/
struct __OTPC_NWORDS_REG
/*=============================*/
{
    volatile uint32_t BITFLD_OTPC_NWORDS                       : 13;
};
#define OTPC_NWORDS                           (0x1FFF)



/*===========================================================================*/
/* memory map PATCH */
/*===========================================================================*/
//reserved only



/*===========================================================================*/
/* memory map QDEC */
/*===========================================================================*/



#define QDEC_CTRL_REG                        (0x50000200) /* Quad Decoder control register */
#define QDEC_CTRL_REG_RESET                  (0x00000011)

/*=============================*/
struct __QDEC_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_QDEC_IRQ_ENABLE                   : 1;
    volatile uint16_t BITFLD_QDEC_EVENT_CNT_CLR                : 1;
    volatile uint16_t BITFLD_QDEC_IRQ_STATUS                   : 1;
    volatile uint16_t BITFLD_QDEC_IRQ_THRES                    : 8;
};
#define QDEC_IRQ_ENABLE                       (0x0001)
#define QDEC_EVENT_CNT_CLR                    (0x0002)
#define QDEC_IRQ_STATUS                       (0x0004)
#define QDEC_IRQ_THRES                        (0x07F8)



#define QDEC_XCNT_REG                        (0x50000202) /* Counter value of the X Axis */
#define QDEC_XCNT_REG_RESET                  (0x00000000)

/*=============================*/
struct __QDEC_XCNT_REG
/*=============================*/
{
    volatile uint16_t BITFLD_QDEC_X_CNT                        : 16;
};
#define QDEC_X_CNT                            (0xFFFF)



#define QDEC_YCNT_REG                        (0x50000204) /* Counter value of the Y Axis */
#define QDEC_YCNT_REG_RESET                  (0x00000000)

/*=============================*/
struct __QDEC_YCNT_REG
/*=============================*/
{
    volatile uint16_t BITFLD_QDEC_Y_CNT                        : 16;
};
#define QDEC_Y_CNT                            (0xFFFF)



#define QDEC_CLOCKDIV_REG                    (0x50000206) /* Clock divider register */
#define QDEC_CLOCKDIV_REG_RESET              (0x000003E7)

/*=============================*/
struct __QDEC_CLOCKDIV_REG
/*=============================*/
{
    volatile uint16_t BITFLD_QDEC_CLOCKDIV                     : 10;
    volatile uint16_t BITFLD_QDEC_PRESCALER_EN                 : 1;
};
#define QDEC_CLOCKDIV                         (0x03FF)
#define QDEC_PRESCALER_EN                     (0x0400)



#define QDEC_CTRL2_REG                       (0x50000208) /* Quad Decoder port selection register */
#define QDEC_CTRL2_REG_RESET                 (0x00000ED1)

/*=============================*/
struct __QDEC_CTRL2_REG
/*=============================*/
{
    volatile uint16_t BITFLD_QDEC_CHX_PORT_SEL                 : 3;
    volatile uint16_t BITFLD_QDEC_CHY_PORT_SEL                 : 3;
    volatile uint16_t BITFLD_QDEC_CHZ_PORT_SEL                 : 3;
    volatile uint16_t BITFLD_QDEC_CHX_EVENT_MODE               : 1;
    volatile uint16_t BITFLD_QDEC_CHY_EVENT_MODE               : 1;
    volatile uint16_t BITFLD_QDEC_CHZ_EVENT_MODE               : 1;
};
#define QDEC_CHX_PORT_SEL                     (0x0007)
#define QDEC_CHY_PORT_SEL                     (0x0038)
#define QDEC_CHZ_PORT_SEL                     (0x01C0)
#define QDEC_CHX_EVENT_MODE                   (0x0200)
#define QDEC_CHY_EVENT_MODE                   (0x0400)
#define QDEC_CHZ_EVENT_MODE                   (0x0800)



#define QDEC_ZCNT_REG                        (0x5000020A) /* Counter value of the Z Axis */
#define QDEC_ZCNT_REG_RESET                  (0x00000000)

/*=============================*/
struct __QDEC_ZCNT_REG
/*=============================*/
{
    volatile uint16_t BITFLD_QDEC_Z_CNT                        : 16;
};
#define QDEC_Z_CNT                            (0xFFFF)



#define QDEC_EVENT_CNT_REG                   (0x5000020C) /* Event counter register */
#define QDEC_EVENT_CNT_REG_RESET             (0x00000000)

/*=============================*/
struct __QDEC_EVENT_CNT_REG
/*=============================*/
{
    volatile uint16_t BITFLD_QDEC_EVENT_CNT                    : 8;
};
#define QDEC_EVENT_CNT                        (0x00FF)



/*===========================================================================*/
/* memory map RFCU */
/*===========================================================================*/
//reserved only



/*===========================================================================*/
/* memory map RFCU_POWER */
/*===========================================================================*/
//reserved only



/*===========================================================================*/
/* memory map RFMON */
/*===========================================================================*/
//reserved only



/*===========================================================================*/
/* memory map rtc2632_00 */
/*===========================================================================*/



#define RTC_CONTROL_REG                      (0x50004100) /* RTC Control Register */
#define RTC_CONTROL_REG_RESET                (0x00000003)

/*=============================*/
struct __RTC_CONTROL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RTC_TIME_DISABLE                  : 1;
    volatile uint32_t BITFLD_RTC_CAL_DISABLE                   : 1;
};
#define RTC_TIME_DISABLE                      (0x0001)
#define RTC_CAL_DISABLE                       (0x0002)



#define RTC_HOUR_MODE_REG                    (0x50004104) /* RTC Hour Mode Register */
#define RTC_HOUR_MODE_REG_RESET              (0x00000000)

/*=============================*/
struct __RTC_HOUR_MODE_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RTC_HMS                           : 1;
};
#define RTC_HMS                               (0x0001)



#define RTC_TIME_REG                         (0x50004108) /* RTC Time Register */
#define RTC_TIME_REG_RESET                   (0x00000000)

/*=============================*/
struct __RTC_TIME_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RTC_TIME_H_U                      : 4;
    volatile uint32_t BITFLD_RTC_TIME_H_T                      : 4;
    volatile uint32_t BITFLD_RTC_TIME_S_U                      : 4;
    volatile uint32_t BITFLD_RTC_TIME_S_T                      : 3;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_RTC_TIME_M_U                      : 4;
    volatile uint32_t BITFLD_RTC_TIME_M_T                      : 3;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_RTC_TIME_HR_U                     : 4;
    volatile uint32_t BITFLD_RTC_TIME_HR_T                     : 2;
    volatile uint32_t BITFLD_RTC_TIME_PM                       : 1;
    volatile uint32_t BITFLD_RTC_TIME_CH                       : 1;
};
#define RTC_TIME_H_U                          (0x000F)
#define RTC_TIME_H_T                          (0x00F0)
#define RTC_TIME_S_U                          (0x0F00)
#define RTC_TIME_S_T                          (0x7000)
#define RTC_TIME_M_U                          (0xF0000)
#define RTC_TIME_M_T                          (0x700000)
#define RTC_TIME_HR_U                         (0xF000000)
#define RTC_TIME_HR_T                         (0x30000000)
#define RTC_TIME_PM                           (0x40000000)
#define RTC_TIME_CH                           (0x80000000)



#define RTC_CALENDAR_REG                     (0x5000410C) /* RTC Calendar Register */
#define RTC_CALENDAR_REG_RESET               (0x2000010F)

/*=============================*/
struct __RTC_CALENDAR_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RTC_DAY                           : 3;
    volatile uint32_t BITFLD_RTC_CAL_M_U                       : 4;
    volatile uint32_t BITFLD_RTC_CAL_M_T                       : 1;
    volatile uint32_t BITFLD_RTC_CAL_D_U                       : 4;
    volatile uint32_t BITFLD_RTC_CAL_D_T                       : 2;
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_RTC_CAL_Y_U                       : 4;
    volatile uint32_t BITFLD_RTC_CAL_Y_T                       : 4;
    volatile uint32_t BITFLD_RTC_CAL_C_U                       : 4;
    volatile uint32_t BITFLD_RTC_CAL_C_T                       : 2;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_RTC_CAL_CH                        : 1;
};
#define RTC_DAY                               (0x0007)
#define RTC_CAL_M_U                           (0x0078)
#define RTC_CAL_M_T                           (0x0080)
#define RTC_CAL_D_U                           (0x0F00)
#define RTC_CAL_D_T                           (0x3000)
#define RTC_CAL_Y_U                           (0xF0000)
#define RTC_CAL_Y_T                           (0xF00000)
#define RTC_CAL_C_U                           (0xF000000)
#define RTC_CAL_C_T                           (0x30000000)
#define RTC_CAL_CH                            (0x80000000)



#define RTC_TIME_ALARM_REG                   (0x50004110) /* RTC Time Alarm Register */
#define RTC_TIME_ALARM_REG_RESET             (0x00000000)

/*=============================*/
struct __RTC_TIME_ALARM_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RTC_TIME_H_U                      : 4;
    volatile uint32_t BITFLD_RTC_TIME_H_T                      : 4;
    volatile uint32_t BITFLD_RTC_TIME_S_U                      : 4;
    volatile uint32_t BITFLD_RTC_TIME_S_T                      : 3;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_RTC_TIME_M_U                      : 4;
    volatile uint32_t BITFLD_RTC_TIME_M_T                      : 3;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_RTC_TIME_HR_U                     : 4;
    volatile uint32_t BITFLD_RTC_TIME_HR_T                     : 2;
    volatile uint32_t BITFLD_RTC_TIME_PM                       : 1;
};
#define RTC_TIME_H_U                          (0x000F)
#define RTC_TIME_H_T                          (0x00F0)
#define RTC_TIME_S_U                          (0x0F00)
#define RTC_TIME_S_T                          (0x7000)
#define RTC_TIME_M_U                          (0xF0000)
#define RTC_TIME_M_T                          (0x700000)
#define RTC_TIME_HR_U                         (0xF000000)
#define RTC_TIME_HR_T                         (0x30000000)
#define RTC_TIME_PM                           (0x40000000)



#define RTC_CALENDAR_ALARM_REG               (0x50004114) /* RTC Calendar Alram Register */
#define RTC_CALENDAR_ALARM_REG_RESET         (0x00000000)

/*=============================*/
struct __RTC_CALENDAR_ALARM_REG
/*=============================*/
{
    volatile uint32_t                                          : 3;
    volatile uint32_t BITFLD_RTC_CAL_M_U                       : 4;
    volatile uint32_t BITFLD_RTC_CAL_M_T                       : 1;
    volatile uint32_t BITFLD_RTC_CAL_D_U                       : 4;
    volatile uint32_t BITFLD_RTC_CAL_D_T                       : 2;
};
#define RTC_CAL_M_U                           (0x0078)
#define RTC_CAL_M_T                           (0x0080)
#define RTC_CAL_D_U                           (0x0F00)
#define RTC_CAL_D_T                           (0x3000)



#define RTC_ALARM_ENABLE_REG                 (0x50004118) /* RTC Alarm Enable Register */
#define RTC_ALARM_ENABLE_REG_RESET           (0x00000000)

/*=============================*/
struct __RTC_ALARM_ENABLE_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RTC_ALARM_HOS_EN                  : 1;
    volatile uint32_t BITFLD_RTC_ALARM_SEC_EN                  : 1;
    volatile uint32_t BITFLD_RTC_ALARM_MIN_EN                  : 1;
    volatile uint32_t BITFLD_RTC_ALARM_HOUR_EN                 : 1;
    volatile uint32_t BITFLD_RTC_ALARM_DATE_EN                 : 1;
    volatile uint32_t BITFLD_RTC_ALARM_MNTH_EN                 : 1;
};
#define RTC_ALARM_HOS_EN                      (0x0001)
#define RTC_ALARM_SEC_EN                      (0x0002)
#define RTC_ALARM_MIN_EN                      (0x0004)
#define RTC_ALARM_HOUR_EN                     (0x0008)
#define RTC_ALARM_DATE_EN                     (0x0010)
#define RTC_ALARM_MNTH_EN                     (0x0020)



#define RTC_EVENT_FLAGS_REG                  (0x5000411C) /* RTC Event Flags Register */
#define RTC_EVENT_FLAGS_REG_RESET            (0x00000000)

/*=============================*/
struct __RTC_EVENT_FLAGS_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RTC_EVENT_HOS                     : 1;
    volatile uint32_t BITFLD_RTC_EVENT_SEC                     : 1;
    volatile uint32_t BITFLD_RTC_EVENT_MIN                     : 1;
    volatile uint32_t BITFLD_RTC_EVENT_HOUR                    : 1;
    volatile uint32_t BITFLD_RTC_EVENT_DATE                    : 1;
    volatile uint32_t BITFLD_RTC_EVENT_MNTH                    : 1;
    volatile uint32_t BITFLD_RTC_EVENT_ALRM                    : 1;
};
#define RTC_EVENT_HOS                         (0x0001)
#define RTC_EVENT_SEC                         (0x0002)
#define RTC_EVENT_MIN                         (0x0004)
#define RTC_EVENT_HOUR                        (0x0008)
#define RTC_EVENT_DATE                        (0x0010)
#define RTC_EVENT_MNTH                        (0x0020)
#define RTC_EVENT_ALRM                        (0x0040)



#define RTC_INTERRUPT_ENABLE_REG             (0x50004120) /* RTC Interrupt Enable Register */
#define RTC_INTERRUPT_ENABLE_REG_RESET       (0x00000000)

/*=============================*/
struct __RTC_INTERRUPT_ENABLE_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RTC_HOS_INT_EN                    : 1;
    volatile uint32_t BITFLD_RTC_SEC_INT_EN                    : 1;
    volatile uint32_t BITFLD_RTC_MIN_INT_EN                    : 1;
    volatile uint32_t BITFLD_RTC_HOUR_INT_EN                   : 1;
    volatile uint32_t BITFLD_RTC_DATE_INT_EN                   : 1;
    volatile uint32_t BITFLD_RTC_MNTH_INT_EN                   : 1;
    volatile uint32_t BITFLD_RTC_ALRM_INT_EN                   : 1;
};
#define RTC_HOS_INT_EN                        (0x0001)
#define RTC_SEC_INT_EN                        (0x0002)
#define RTC_MIN_INT_EN                        (0x0004)
#define RTC_HOUR_INT_EN                       (0x0008)
#define RTC_DATE_INT_EN                       (0x0010)
#define RTC_MNTH_INT_EN                       (0x0020)
#define RTC_ALRM_INT_EN                       (0x0040)



#define RTC_INTERRUPT_DISABLE_REG            (0x50004124) /* RTC Interrupt Disable Register */
#define RTC_INTERRUPT_DISABLE_REG_RESET      (0x00000000)

/*=============================*/
struct __RTC_INTERRUPT_DISABLE_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RTC_HOS_INT_DIS                   : 1;
    volatile uint32_t BITFLD_RTC_SEC_INT_DIS                   : 1;
    volatile uint32_t BITFLD_RTC_MIN_INT_DIS                   : 1;
    volatile uint32_t BITFLD_RTC_HOUR_INT_DIS                  : 1;
    volatile uint32_t BITFLD_RTC_DATE_INT_DIS                  : 1;
    volatile uint32_t BITFLD_RTC_MNTH_INT_DIS                  : 1;
    volatile uint32_t BITFLD_RTC_ALRM_INT_DIS                  : 1;
};
#define RTC_HOS_INT_DIS                       (0x0001)
#define RTC_SEC_INT_DIS                       (0x0002)
#define RTC_MIN_INT_DIS                       (0x0004)
#define RTC_HOUR_INT_DIS                      (0x0008)
#define RTC_DATE_INT_DIS                      (0x0010)
#define RTC_MNTH_INT_DIS                      (0x0020)
#define RTC_ALRM_INT_DIS                      (0x0040)



#define RTC_INTERRUPT_MASK_REG               (0x50004128) /* RTC Interrupt Mask Register */
#define RTC_INTERRUPT_MASK_REG_RESET         (0x0000007F)

/*=============================*/
struct __RTC_INTERRUPT_MASK_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RTC_HOS_INT_MSK                   : 1;
    volatile uint32_t BITFLD_RTC_SEC_INT_MSK                   : 1;
    volatile uint32_t BITFLD_RTC_MIN_INT_MSK                   : 1;
    volatile uint32_t BITFLD_RTC_HOUR_INT_MSK                  : 1;
    volatile uint32_t BITFLD_RTC_DATE_INT_MSK                  : 1;
    volatile uint32_t BITFLD_RTC_MNTH_INT_MSK                  : 1;
    volatile uint32_t BITFLD_RTC_ALRM_INT_MSK                  : 1;
};
#define RTC_HOS_INT_MSK                       (0x0001)
#define RTC_SEC_INT_MSK                       (0x0002)
#define RTC_MIN_INT_MSK                       (0x0004)
#define RTC_HOUR_INT_MSK                      (0x0008)
#define RTC_DATE_INT_MSK                      (0x0010)
#define RTC_MNTH_INT_MSK                      (0x0020)
#define RTC_ALRM_INT_MSK                      (0x0040)



#define RTC_STATUS_REG                       (0x5000412C) /* RTC Status Register */
#define RTC_STATUS_REG_RESET                 (0x0000000F)

/*=============================*/
struct __RTC_STATUS_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RTC_VALID_TIME                    : 1;
    volatile uint32_t BITFLD_RTC_VALID_CAL                     : 1;
    volatile uint32_t BITFLD_RTC_VALID_TIME_ALM                : 1;
    volatile uint32_t BITFLD_RTC_VALID_CAL_ALM                 : 1;
};
#define RTC_VALID_TIME                        (0x0001)
#define RTC_VALID_CAL                         (0x0002)
#define RTC_VALID_TIME_ALM                    (0x0004)
#define RTC_VALID_CAL_ALM                     (0x0008)



#define RTC_KEEP_RTC_REG                     (0x50004130) /* RTC Keep RTC Register */
#define RTC_KEEP_RTC_REG_RESET               (0x00000001)

/*=============================*/
struct __RTC_KEEP_RTC_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RTC_KEEP                          : 1;
};
#define RTC_KEEP                              (0x0001)



/*===========================================================================*/
/* memory map SPI */
/*===========================================================================*/



#define SPI_CTRL_REG                         (0x50001200) /* Spi control register */
#define SPI_CTRL_REG_RESET                   (0x00000000)

/*=============================*/
struct __SPI_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SPI_EN                            : 1;
    volatile uint16_t BITFLD_SPI_TX_EN                         : 1;
    volatile uint16_t BITFLD_SPI_RX_EN                         : 1;
    volatile uint16_t BITFLD_SPI_DMA_TX_EN                     : 1;
    volatile uint16_t BITFLD_SPI_DMA_RX_EN                     : 1;
    volatile uint16_t BITFLD_SPI_FIFO_RESET                    : 1;
    volatile uint16_t BITFLD_SPI_CAPTURE_AT_NEXT_EDGE          : 1;
    volatile uint16_t BITFLD_SPI_SWAP_BYTES                    : 1;
};
#define SPI_EN                                (0x0001)
#define SPI_TX_EN                             (0x0002)
#define SPI_RX_EN                             (0x0004)
#define SPI_DMA_TX_EN                         (0x0008)
#define SPI_DMA_RX_EN                         (0x0010)
#define SPI_FIFO_RESET                        (0x0020)
#define SPI_CAPTURE_AT_NEXT_EDGE              (0x0040)
#define SPI_SWAP_BYTES                        (0x0080)



#define SPI_CONFIG_REG                       (0x50001204) /* Spi control register */
#define SPI_CONFIG_REG_RESET                 (0x00000000)

/*=============================*/
struct __SPI_CONFIG_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SPI_MODE                          : 2;
    volatile uint16_t BITFLD_SPI_WORD_LENGTH                   : 5;
    volatile uint16_t BITFLD_SPI_SLAVE_EN                      : 1;
};
#define SPI_MODE                              (0x0003)
#define SPI_WORD_LENGTH                       (0x007C)
#define SPI_SLAVE_EN                          (0x0080)



#define SPI_CLOCK_REG                        (0x50001208) /* Spi clock register */
#define SPI_CLOCK_REG_RESET                  (0x00000000)

/*=============================*/
struct __SPI_CLOCK_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SPI_CLK_DIV                       : 7;
    volatile uint16_t BITFLD_SPI_MASTER_CLK_MODE               : 1;
};
#define SPI_CLK_DIV                           (0x007F)
#define SPI_MASTER_CLK_MODE                   (0x0080)



#define SPI_FIFO_CONFIG_REG                  (0x5000120C) /* Spi fifo configuration register */
#define SPI_FIFO_CONFIG_REG_RESET            (0x00000000)

/*=============================*/
struct __SPI_FIFO_CONFIG_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SPI_TX_TL                         : 4;
    volatile uint16_t BITFLD_SPI_RX_TL                         : 4;
};
#define SPI_TX_TL                             (0x000F)
#define SPI_RX_TL                             (0x00F0)



#define SPI_IRQ_MASK_REG                     (0x50001210) /* Spi interrupt mask register */
#define SPI_IRQ_MASK_REG_RESET               (0x00000000)

/*=============================*/
struct __SPI_IRQ_MASK_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SPI_IRQ_MASK_TX_EMPTY             : 1;
    volatile uint16_t BITFLD_SPI_IRQ_MASK_RX_FULL              : 1;
};
#define SPI_IRQ_MASK_TX_EMPTY                 (0x0001)
#define SPI_IRQ_MASK_RX_FULL                  (0x0002)



#define SPI_STATUS_REG                       (0x50001214) /* Spi status register */
#define SPI_STATUS_REG_RESET                 (0x00000001)

/*=============================*/
struct __SPI_STATUS_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SPI_STATUS_TX_EMPTY               : 1;
    volatile uint16_t BITFLD_SPI_STATUS_RX_FULL                : 1;
};
#define SPI_STATUS_TX_EMPTY                   (0x0001)
#define SPI_STATUS_RX_FULL                    (0x0002)



#define SPI_FIFO_STATUS_REG                  (0x50001218) /* SPI RX/TX fifo status register */
#define SPI_FIFO_STATUS_REG_RESET            (0x00001000)

/*=============================*/
struct __SPI_FIFO_STATUS_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SPI_RX_FIFO_LEVEL                 : 6;
    volatile uint16_t BITFLD_SPI_TX_FIFO_LEVEL                 : 6;
    volatile uint16_t BITFLD_SPI_STATUS_RX_EMPTY               : 1;
    volatile uint16_t BITFLD_SPI_STATUS_TX_FULL                : 1;
    volatile uint16_t BITFLD_SPI_RX_FIFO_OVFL                  : 1;
    volatile uint16_t BITFLD_SPI_TRANSACTION_ACTIVE            : 1;
};
#define SPI_RX_FIFO_LEVEL                     (0x003F)
#define SPI_TX_FIFO_LEVEL                     (0x0FC0)
#define SPI_STATUS_RX_EMPTY                   (0x1000)
#define SPI_STATUS_TX_FULL                    (0x2000)
#define SPI_RX_FIFO_OVFL                      (0x4000)
#define SPI_TRANSACTION_ACTIVE                (0x8000)



#define SPI_FIFO_READ_REG                    (0x5000121C) /* Spi RX fifo read register */
#define SPI_FIFO_READ_REG_RESET              (0x00000000)

/*=============================*/
struct __SPI_FIFO_READ_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SPI_FIFO_READ                     : 16;
};
#define SPI_FIFO_READ                         (0xFFFF)



#define SPI_FIFO_WRITE_REG                   (0x50001220) /* Spi TX fifo wtite register */
#define SPI_FIFO_WRITE_REG_RESET             (0x00000000)

/*=============================*/
struct __SPI_FIFO_WRITE_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SPI_FIFO_WRITE                    : 16;
};
#define SPI_FIFO_WRITE                        (0xFFFF)



#define SPI_CS_CONFIG_REG                    (0x50001224) /* Spi cs configuration register */
#define SPI_CS_CONFIG_REG_RESET              (0x00000000)

/*=============================*/
struct __SPI_CS_CONFIG_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SPI_CS_SELECT                     : 3;
};
#define SPI_CS_SELECT                         (0x0007)



#define SPI_FIFO_HIGH_REG                    (0x50001228) /* Spi TX/RX High 16bit word */
#define SPI_FIFO_HIGH_REG_RESET              (0x00000000)

/*=============================*/
struct __SPI_FIFO_HIGH_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SPI_FIFO_HIGH                     : 16;
};
#define SPI_FIFO_HIGH                         (0xFFFF)



#define SPI_TXBUFFER_FORCE_L_REG             (0x5000122C) /* SPI TX buffer force low value */
#define SPI_TXBUFFER_FORCE_L_REG_RESET       (0x00000000)

/*=============================*/
struct __SPI_TXBUFFER_FORCE_L_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SPI_TXBUFFER_FORCE_L              : 16;
};
#define SPI_TXBUFFER_FORCE_L                  (0xFFFF)



#define SPI_TXBUFFER_FORCE_H_REG             (0x50001230) /* SPI TX buffer force high value */
#define SPI_TXBUFFER_FORCE_H_REG_RESET       (0x00000000)

/*=============================*/
struct __SPI_TXBUFFER_FORCE_H_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SPI_TXBUFFER_FORCE_H              : 16;
};
#define SPI_TXBUFFER_FORCE_H                  (0xFFFF)



/*===========================================================================*/
/* memory map Timer+3PWM */
/*===========================================================================*/



#define TIMER0_CTRL_REG                      (0x50003400) /* Timer0 control register */
#define TIMER0_CTRL_REG_RESET                (0x00000000)

/*=============================*/
struct __TIMER0_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_TIM0_CTRL                         : 1;
    volatile uint16_t BITFLD_TIM0_CLK_SEL                      : 1;
    volatile uint16_t BITFLD_TIM0_CLK_DIV                      : 1;
    volatile uint16_t BITFLD_PWM_MODE                          : 1;
};
#define TIM0_CTRL                             (0x0001)
#define TIM0_CLK_SEL                          (0x0002)
#define TIM0_CLK_DIV                          (0x0004)
#define PWM_MODE                              (0x0008)



#define TIMER0_ON_REG                        (0x50003402) /* Timer0 on control register */
#define TIMER0_ON_REG_RESET                  (0x00000000)

/*=============================*/
struct __TIMER0_ON_REG
/*=============================*/
{
    volatile uint16_t BITFLD_TIM0_ON                           : 16;
};
#define TIM0_ON                               (0xFFFF)



#define TIMER0_RELOAD_M_REG                  (0x50003404) /* 16 bits reload value for Timer0 */
#define TIMER0_RELOAD_M_REG_RESET            (0x00000000)

/*=============================*/
struct __TIMER0_RELOAD_M_REG
/*=============================*/
{
    volatile uint16_t BITFLD_TIM0_M                            : 16;
};
#define TIM0_M                                (0xFFFF)



#define TIMER0_RELOAD_N_REG                  (0x50003406) /* 16 bits reload value for Timer0 */
#define TIMER0_RELOAD_N_REG_RESET            (0x00000000)

/*=============================*/
struct __TIMER0_RELOAD_N_REG
/*=============================*/
{
    volatile uint16_t BITFLD_TIM0_N                            : 16;
};
#define TIM0_N                                (0xFFFF)



#define TRIPLE_PWM_FREQUENCY                 (0x50003408) /* Frequency for PWM 2,3,4,5,6 and 7 */
#define TRIPLE_PWM_FREQUENCY_RESET           (0x00000000)

/*=============================*/
struct __TRIPLE_PWM_FREQUENCY
/*=============================*/
{
    volatile uint16_t BITFLD_PWM_FREQ                          : 14;
};
#define PWM_FREQ                              (0x3FFF)



#define PWM2_START_CYCLE                     (0x5000340A) /* Defines start Cycle for PWM2 */
#define PWM2_START_CYCLE_RESET               (0x00000000)

/*=============================*/
struct __PWM2_START_CYCLE
/*=============================*/
{
    volatile uint16_t BITFLD_START_CYCLE                       : 14;
};
#define START_CYCLE                           (0x3FFF)



#define PWM3_START_CYCLE                     (0x5000340C) /* Defines start Cycle for PWM3 */
#define PWM3_START_CYCLE_RESET               (0x00000000)

/*=============================*/
struct __PWM3_START_CYCLE
/*=============================*/
{
    volatile uint16_t BITFLD_START_CYCLE                       : 14;
};
#define START_CYCLE                           (0x3FFF)



#define PWM4_START_CYCLE                     (0x5000340E) /* Defines start Cycle for PWM4 */
#define PWM4_START_CYCLE_RESET               (0x00000000)

/*=============================*/
struct __PWM4_START_CYCLE
/*=============================*/
{
    volatile uint16_t BITFLD_START_CYCLE                       : 14;
};
#define START_CYCLE                           (0x3FFF)



#define PWM5_START_CYCLE                     (0x50003410) /* Defines start Cycle for PWM5 */
#define PWM5_START_CYCLE_RESET               (0x00000000)

/*=============================*/
struct __PWM5_START_CYCLE
/*=============================*/
{
    volatile uint16_t BITFLD_START_CYCLE                       : 14;
};
#define START_CYCLE                           (0x3FFF)



#define PWM6_START_CYCLE                     (0x50003412) /* Defines start Cycle for PWM6 */
#define PWM6_START_CYCLE_RESET               (0x00000000)

/*=============================*/
struct __PWM6_START_CYCLE
/*=============================*/
{
    volatile uint16_t BITFLD_START_CYCLE                       : 14;
};
#define START_CYCLE                           (0x3FFF)



#define PWM7_START_CYCLE                     (0x50003414) /* Defines start Cycle for PWM7 */
#define PWM7_START_CYCLE_RESET               (0x00000000)

/*=============================*/
struct __PWM7_START_CYCLE
/*=============================*/
{
    volatile uint16_t BITFLD_START_CYCLE                       : 14;
};
#define START_CYCLE                           (0x3FFF)



#define PWM2_END_CYCLE                       (0x50003416) /* Defines end Cycle for PWM2 */
#define PWM2_END_CYCLE_RESET                 (0x00000000)

/*=============================*/
struct __PWM2_END_CYCLE
/*=============================*/
{
    volatile uint16_t BITFLD_END_CYCLE                         : 14;
};
#define END_CYCLE                             (0x3FFF)



#define PWM3_END_CYCLE                       (0x50003418) /* Defines end Cycle for PWM3 */
#define PWM3_END_CYCLE_RESET                 (0x00000000)

/*=============================*/
struct __PWM3_END_CYCLE
/*=============================*/
{
    volatile uint16_t BITFLD_END_CYCLE                         : 14;
};
#define END_CYCLE                             (0x3FFF)



#define PWM4_END_CYCLE                       (0x5000341A) /* Defines end Cycle for PWM4 */
#define PWM4_END_CYCLE_RESET                 (0x00000000)

/*=============================*/
struct __PWM4_END_CYCLE
/*=============================*/
{
    volatile uint16_t BITFLD_END_CYCLE                         : 14;
};
#define END_CYCLE                             (0x3FFF)



#define PWM5_END_CYCLE                       (0x5000341C) /* Defines end Cycle for PWM5 */
#define PWM5_END_CYCLE_RESET                 (0x00000000)

/*=============================*/
struct __PWM5_END_CYCLE
/*=============================*/
{
    volatile uint16_t BITFLD_END_CYCLE                         : 14;
};
#define END_CYCLE                             (0x3FFF)



#define PWM6_END_CYCLE                       (0x5000341E) /* Defines end Cycle for PWM6 */
#define PWM6_END_CYCLE_RESET                 (0x00000000)

/*=============================*/
struct __PWM6_END_CYCLE
/*=============================*/
{
    volatile uint16_t BITFLD_END_CYCLE                         : 14;
};
#define END_CYCLE                             (0x3FFF)



#define PWM7_END_CYCLE                       (0x50003420) /* Defines end Cycle for PWM7 */
#define PWM7_END_CYCLE_RESET                 (0x00000000)

/*=============================*/
struct __PWM7_END_CYCLE
/*=============================*/
{
    volatile uint16_t BITFLD_END_CYCLE                         : 14;
};
#define END_CYCLE                             (0x3FFF)



#define TRIPLE_PWM_CTRL_REG                  (0x50003422) /* PWM 2,3,4,5,6,7 Control */
#define TRIPLE_PWM_CTRL_REG_RESET            (0x00000004)

/*=============================*/
struct __TRIPLE_PWM_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_TRIPLE_PWM_ENABLE                 : 1;
    volatile uint16_t BITFLD_SW_PAUSE_EN                       : 1;
    volatile uint16_t BITFLD_HW_PAUSE_EN                       : 1;
    volatile uint16_t BITFLD_TRIPLE_PWM_CLK_SEL                : 1;
};
#define TRIPLE_PWM_ENABLE                     (0x0001)
#define SW_PAUSE_EN                           (0x0002)
#define HW_PAUSE_EN                           (0x0004)
#define TRIPLE_PWM_CLK_SEL                    (0x0008)



/*===========================================================================*/
/* memory map Timer1 */
/*===========================================================================*/



#define TIMER1_CTRL_REG                      (0x50004000) /* Timer1 control register */
#define TIMER1_CTRL_REG_RESET                (0x00000000)

/*=============================*/
struct __TIMER1_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_TIMER1_RELOAD                     : 11;
    volatile uint32_t BITFLD_TIMER1_ENABLE                     : 1;
    volatile uint32_t BITFLD_TIMER1_COUNT_DOWN_EN              : 1;
    volatile uint32_t BITFLD_TIMER1_IRQ_EN                     : 1;
    volatile uint32_t BITFLD_TIMER1_FREE_RUN_MODE_EN           : 1;
    volatile uint32_t BITFLD_TIMER1_USE_SYS_CLK                : 1;
    volatile uint32_t BITFLD_TIMER1_CLK_EN                     : 1;
};
#define TIMER1_RELOAD                         (0x07FF)
#define TIMER1_ENABLE                         (0x0800)
#define TIMER1_COUNT_DOWN_EN                  (0x1000)
#define TIMER1_IRQ_EN                         (0x2000)
#define TIMER1_FREE_RUN_MODE_EN               (0x4000)
#define TIMER1_USE_SYS_CLK                    (0x8000)
#define TIMER1_CLK_EN                         (0x10000)



#define TIMER1_CAPTURE_REG                   (0x50004004) /* Timer1 Capture control register */
#define TIMER1_CAPTURE_REG_RESET             (0x00000000)

/*=============================*/
struct __TIMER1_CAPTURE_REG
/*=============================*/
{
    volatile uint32_t BITFLD_TIMER1_GPIO1_CONF                 : 4;
    volatile uint32_t BITFLD_TIMER1_IN1_EVENT_FALL_EN          : 1;
    volatile uint32_t BITFLD_TIMER1_IN1_COUNT_EN               : 1;
    volatile uint32_t BITFLD_TIMER1_IN1_IRQ_EN                 : 1;
    volatile uint32_t BITFLD_TIMER1_IN1_PERIOD_MAX             : 6;
    volatile uint32_t BITFLD_TIMER1_IN1_STAMP_TYPE             : 1;
    volatile uint32_t BITFLD_TIMER1_GPIO2_CONF                 : 4;
    volatile uint32_t BITFLD_TIMER1_IN2_EVENT_FALL_EN          : 1;
    volatile uint32_t BITFLD_TIMER1_IN2_COUNT_EN               : 1;
    volatile uint32_t BITFLD_TIMER1_IN2_IRQ_EN                 : 1;
    volatile uint32_t BITFLD_TIMER1_IN2_PERIOD_MAX             : 6;
    volatile uint32_t BITFLD_TIMER1_IN2_STAMP_TYPE             : 1;
};
#define TIMER1_GPIO1_CONF                     (0x000F)
#define TIMER1_IN1_EVENT_FALL_EN              (0x0010)
#define TIMER1_IN1_COUNT_EN                   (0x0020)
#define TIMER1_IN1_IRQ_EN                     (0x0040)
#define TIMER1_IN1_PERIOD_MAX                 (0x1F80)
#define TIMER1_IN1_STAMP_TYPE                 (0x2000)
#define TIMER1_GPIO2_CONF                     (0x3C000)
#define TIMER1_IN2_EVENT_FALL_EN              (0x40000)
#define TIMER1_IN2_COUNT_EN                   (0x80000)
#define TIMER1_IN2_IRQ_EN                     (0x100000)
#define TIMER1_IN2_PERIOD_MAX                 (0x7E00000)
#define TIMER1_IN2_STAMP_TYPE                 (0x8000000)



#define TIMER1_STATUS_REG                    (0x50004008) /* Timer1 counter value */
#define TIMER1_STATUS_REG_RESET              (0x00000000)

/*=============================*/
struct __TIMER1_STATUS_REG
/*=============================*/
{
    volatile uint32_t BITFLD_TIMER1_TIMER_VALUE                : 11;
    volatile uint32_t BITFLD_TIMER1_TIMER_EVENT                : 1;
    volatile uint32_t BITFLD_TIMER1_IN1_EVENT                  : 1;
    volatile uint32_t BITFLD_TIMER1_IN2_EVENT                  : 1;
    volatile uint32_t BITFLD_TIMER1_IN1_OVRFLW                 : 1;
    volatile uint32_t BITFLD_TIMER1_IN2_OVRFLW                 : 1;
};
#define TIMER1_TIMER_VALUE                    (0x07FF)
#define TIMER1_TIMER_EVENT                    (0x0800)
#define TIMER1_IN1_EVENT                      (0x1000)
#define TIMER1_IN2_EVENT                      (0x2000)
#define TIMER1_IN1_OVRFLW                     (0x4000)
#define TIMER1_IN2_OVRFLW                     (0x8000)



#define TIMER1_CAPCNT1_VALUE_REG             (0x5000400C) /* Timer1 value for event on GPIO1 */
#define TIMER1_CAPCNT1_VALUE_REG_RESET       (0x00000000)

/*=============================*/
struct __TIMER1_CAPCNT1_VALUE_REG
/*=============================*/
{
    volatile uint32_t BITFLD_TIMER1_CAPCNT1_VALUE              : 11;
    volatile uint32_t BITFLD_TIMER1_CAPCNT1_RTC_HIGH           : 11;
};
#define TIMER1_CAPCNT1_VALUE                  (0x07FF)
#define TIMER1_CAPCNT1_RTC_HIGH               (0x3FF800)



#define TIMER1_CAPCNT2_VALUE_REG             (0x50004010) /* Timer1 value for event on GPIO2 */
#define TIMER1_CAPCNT2_VALUE_REG_RESET       (0x00000000)

/*=============================*/
struct __TIMER1_CAPCNT2_VALUE_REG
/*=============================*/
{
    volatile uint32_t BITFLD_TIMER1_CAPCNT2_VALUE              : 11;
    volatile uint32_t BITFLD_TIMER1_CAPCNT2_RTC_HIGH           : 11;
};
#define TIMER1_CAPCNT2_VALUE                  (0x07FF)
#define TIMER1_CAPCNT2_RTC_HIGH               (0x3FF800)



#define TIMER1_CLR_EVENT_REG                 (0x50004014) /* Clear event register */
#define TIMER1_CLR_EVENT_REG_RESET           (0x00000000)

/*=============================*/
struct __TIMER1_CLR_EVENT_REG
/*=============================*/
{
    volatile uint32_t BITFLD_TIMER1_CLR_TIMER_EVENT            : 1;
    volatile uint32_t BITFLD_TIMER1_CLR_IN1_EVENT              : 1;
    volatile uint32_t BITFLD_TIMER1_CLR_IN2_EVENT              : 1;
};
#define TIMER1_CLR_TIMER_EVENT                (0x0001)
#define TIMER1_CLR_IN1_EVENT                  (0x0002)
#define TIMER1_CLR_IN2_EVENT                  (0x0004)



/*===========================================================================*/
/* memory map UART */
/*===========================================================================*/



#define UART_RBR_THR_DLL_REG                 (0x50001000) /* Receive Buffer Register/Transmit Holding Register/Divisor Latch Low */
#define UART_RBR_THR_DLL_REG_RESET           (0x00000000)

/*=============================*/
struct __UART_RBR_THR_DLL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_RBR_THR_DLL                       : 8;
};
#define RBR_THR_DLL                           (0x00FF)



#define UART_IER_DLH_REG                     (0x50001004) /* Interrupt Enable Register/Divisor Latch High */
#define UART_IER_DLH_REG_RESET               (0x00000000)

/*=============================*/
struct __UART_IER_DLH_REG
/*=============================*/
{
    volatile uint16_t BITFLD_ERBFI_dlh0                        : 1;
    volatile uint16_t BITFLD_ETBEI_dlh1                        : 1;
    volatile uint16_t BITFLD_ELSI_dhl2                         : 1;
    volatile uint16_t BITFLD_EDSSI_dlh3                        : 1;
    volatile uint16_t BITFLD_dlh6_4                            : 3;
    volatile uint16_t BITFLD_PTIME_dlh7                        : 1;
};
#define ERBFI_dlh0                            (0x0001)
#define ETBEI_dlh1                            (0x0002)
#define ELSI_dhl2                             (0x0004)
#define EDSSI_dlh3                            (0x0008)
#define dlh6_4                                (0x0070)
#define PTIME_dlh7                            (0x0080)



#define UART_IIR_FCR_REG                     (0x50001008) /* Interrupt Identification Register/FIFO Control Register */
#define UART_IIR_FCR_REG_RESET               (0x00000001)

/*=============================*/
struct __UART_IIR_FCR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_IID0_FIFOE                   : 1;
    volatile uint16_t BITFLD_UART_IID1_RFIFOE                  : 1;
    volatile uint16_t BITFLD_UART_IID2_XFIFOR                  : 1;
    volatile uint16_t BITFLD_UART_IID3_DMAM                    : 1;
    volatile uint16_t BITFLD_UART_TET                          : 2;
    volatile uint16_t BITFLD_UART_FIFOSE_RT                    : 2;
};
#define UART_IID0_FIFOE                       (0x0001)
#define UART_IID1_RFIFOE                      (0x0002)
#define UART_IID2_XFIFOR                      (0x0004)
#define UART_IID3_DMAM                        (0x0008)
#define UART_TET                              (0x0030)
#define UART_FIFOSE_RT                        (0x00C0)



#define UART_LCR_REG                         (0x5000100C) /* Line Control Register */
#define UART_LCR_REG_RESET                   (0x00000000)

/*=============================*/
struct __UART_LCR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_DLS                          : 2;
    volatile uint16_t BITFLD_UART_STOP                         : 1;
    volatile uint16_t BITFLD_UART_PEN                          : 1;
    volatile uint16_t BITFLD_UART_EPS                          : 1;
    volatile uint16_t                                          : 1;
    volatile uint16_t BITFLD_UART_BC                           : 1;
    volatile uint16_t BITFLD_UART_DLAB                         : 1;
};
#define UART_DLS                              (0x0003)
#define UART_STOP                             (0x0004)
#define UART_PEN                              (0x0008)
#define UART_EPS                              (0x0010)
#define UART_BC                               (0x0040)
#define UART_DLAB                             (0x0080)



#define UART_MCR_REG                         (0x50001010) /* Modem Control Register */
#define UART_MCR_REG_RESET                   (0x00000000)

/*=============================*/
struct __UART_MCR_REG
/*=============================*/
{
    volatile uint16_t                                          : 1;
    volatile uint16_t BITFLD_UART_RTS                          : 1;
    volatile uint16_t                                          : 1;
    volatile uint16_t                                          : 1;
    volatile uint16_t BITFLD_UART_LB                           : 1;
    volatile uint16_t BITFLD_UART_AFCE                         : 1;
    volatile uint16_t                                          : 1;
};
#define UART_RTS                              (0x0002)
#define UART_LB                               (0x0010)
#define UART_AFCE                             (0x0020)



#define UART_LSR_REG                         (0x50001014) /* Line Status Register */
#define UART_LSR_REG_RESET                   (0x00000060)

/*=============================*/
struct __UART_LSR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_DR                           : 1;
    volatile uint16_t BITFLD_UART_OE                           : 1;
    volatile uint16_t BITFLD_UART_PE                           : 1;
    volatile uint16_t BITFLD_UART_FE                           : 1;
    volatile uint16_t BITFLD_UART_BI                           : 1;
    volatile uint16_t BITFLD_UART_THRE                         : 1;
    volatile uint16_t BITFLD_UART_TEMT                         : 1;
    volatile uint16_t BITFLD_UART_RFE                          : 1;
};
#define UART_DR                               (0x0001)
#define UART_OE                               (0x0002)
#define UART_PE                               (0x0004)
#define UART_FE                               (0x0008)
#define UART_BI                               (0x0010)
#define UART_THRE                             (0x0020)
#define UART_TEMT                             (0x0040)
#define UART_RFE                              (0x0080)



#define UART_MSR_REG                         (0x50001018) /* Modem Status Register */
#define UART_MSR_REG_RESET                   (0x00000010)

/*=============================*/
struct __UART_MSR_REG
/*=============================*/
{
    volatile uint16_t                                          : 1;
    volatile uint16_t                                          : 3;
    volatile uint16_t BITFLD_UART_CTS                          : 1;
};
#define UART_CTS                              (0x0010)



#define UART_SCR_REG                         (0x5000101C) /* Scratchpad Register */
#define UART_SCR_REG_RESET                   (0x00000000)

/*=============================*/
struct __UART_SCR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_SCRATCH_PAD                  : 8;
};
#define UART_SCRATCH_PAD                      (0x00FF)



#define UART_SRBR_STHR0_REG                  (0x50001030) /* Shadow Receive/Transmit Buffer Register */
#define UART_SRBR_STHR0_REG_RESET            (0x00000000)

/*=============================*/
struct __UART_SRBR_STHR0_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART_SRBR_STHR1_REG                  (0x50001034) /* Shadow Receive/Transmit Buffer Register */
#define UART_SRBR_STHR1_REG_RESET            (0x00000000)

/*=============================*/
struct __UART_SRBR_STHR1_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART_SRBR_STHR2_REG                  (0x50001038) /* Shadow Receive/Transmit Buffer Register */
#define UART_SRBR_STHR2_REG_RESET            (0x00000000)

/*=============================*/
struct __UART_SRBR_STHR2_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART_SRBR_STHR3_REG                  (0x5000103C) /* Shadow Receive/Transmit Buffer Register */
#define UART_SRBR_STHR3_REG_RESET            (0x00000000)

/*=============================*/
struct __UART_SRBR_STHR3_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART_SRBR_STHR4_REG                  (0x50001040) /* Shadow Receive/Transmit Buffer Register */
#define UART_SRBR_STHR4_REG_RESET            (0x00000000)

/*=============================*/
struct __UART_SRBR_STHR4_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART_SRBR_STHR5_REG                  (0x50001044) /* Shadow Receive/Transmit Buffer Register */
#define UART_SRBR_STHR5_REG_RESET            (0x00000000)

/*=============================*/
struct __UART_SRBR_STHR5_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART_SRBR_STHR6_REG                  (0x50001048) /* Shadow Receive/Transmit Buffer Register */
#define UART_SRBR_STHR6_REG_RESET            (0x00000000)

/*=============================*/
struct __UART_SRBR_STHR6_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART_SRBR_STHR7_REG                  (0x5000104C) /* Shadow Receive/Transmit Buffer Register */
#define UART_SRBR_STHR7_REG_RESET            (0x00000000)

/*=============================*/
struct __UART_SRBR_STHR7_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART_SRBR_STHR8_REG                  (0x50001050) /* Shadow Receive/Transmit Buffer Register */
#define UART_SRBR_STHR8_REG_RESET            (0x00000000)

/*=============================*/
struct __UART_SRBR_STHR8_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART_SRBR_STHR9_REG                  (0x50001054) /* Shadow Receive/Transmit Buffer Register */
#define UART_SRBR_STHR9_REG_RESET            (0x00000000)

/*=============================*/
struct __UART_SRBR_STHR9_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART_SRBR_STHR10_REG                 (0x50001058) /* Shadow Receive/Transmit Buffer Register */
#define UART_SRBR_STHR10_REG_RESET           (0x00000000)

/*=============================*/
struct __UART_SRBR_STHR10_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART_SRBR_STHR11_REG                 (0x5000105C) /* Shadow Receive/Transmit Buffer Register */
#define UART_SRBR_STHR11_REG_RESET           (0x00000000)

/*=============================*/
struct __UART_SRBR_STHR11_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART_SRBR_STHR12_REG                 (0x50001060) /* Shadow Receive/Transmit Buffer Register */
#define UART_SRBR_STHR12_REG_RESET           (0x00000000)

/*=============================*/
struct __UART_SRBR_STHR12_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART_SRBR_STHR13_REG                 (0x50001064) /* Shadow Receive/Transmit Buffer Register */
#define UART_SRBR_STHR13_REG_RESET           (0x00000000)

/*=============================*/
struct __UART_SRBR_STHR13_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART_SRBR_STHR14_REG                 (0x50001068) /* Shadow Receive/Transmit Buffer Register */
#define UART_SRBR_STHR14_REG_RESET           (0x00000000)

/*=============================*/
struct __UART_SRBR_STHR14_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART_SRBR_STHR15_REG                 (0x5000106C) /* Shadow Receive/Transmit Buffer Register */
#define UART_SRBR_STHR15_REG_RESET           (0x00000000)

/*=============================*/
struct __UART_SRBR_STHR15_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART_FAR_REG                         (0x50001070) /* FIFO Access Register */
#define UART_FAR_REG_RESET                   (0x00000000)

/*=============================*/
struct __UART_FAR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_FAR                          : 1;
};
#define UART_FAR                              (0x0001)



#define UART_USR_REG                         (0x5000107C) /* UART Status Register */
#define UART_USR_REG_RESET                   (0x00000006)

/*=============================*/
struct __UART_USR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_BUSY                         : 1;
    volatile uint16_t BITFLD_UART_TFNF                         : 1;
    volatile uint16_t BITFLD_UART_TFE                          : 1;
    volatile uint16_t BITFLD_UART_RFNE                         : 1;
    volatile uint16_t BITFLD_UART_RFF                          : 1;
};
#define UART_BUSY                             (0x0001)
#define UART_TFNF                             (0x0002)
#define UART_TFE                              (0x0004)
#define UART_RFNE                             (0x0008)
#define UART_RFF                              (0x0010)



#define UART_TFL_REG                         (0x50001080) /* Transmit FIFO Level */
#define UART_TFL_REG_RESET                   (0x00000000)

/*=============================*/
struct __UART_TFL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_TRANSMIT_FIFO_LEVEL          : 5;
};
#define UART_TRANSMIT_FIFO_LEVEL              (0x001F)



#define UART_RFL_REG                         (0x50001084) /* Receive FIFO Level */
#define UART_RFL_REG_RESET                   (0x00000000)

/*=============================*/
struct __UART_RFL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_RECEIVE_FIFO_LEVEL           : 5;
};
#define UART_RECEIVE_FIFO_LEVEL               (0x001F)



#define UART_SRR_REG                         (0x50001088) /* Software Reset Register. */
#define UART_SRR_REG_RESET                   (0x00000000)

/*=============================*/
struct __UART_SRR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_UR                           : 1;
    volatile uint16_t BITFLD_UART_RFR                          : 1;
    volatile uint16_t BITFLD_UART_XFR                          : 1;
};
#define UART_UR                               (0x0001)
#define UART_RFR                              (0x0002)
#define UART_XFR                              (0x0004)



#define UART_SRTS_REG                        (0x5000108C) /* Shadow Request to Send */
#define UART_SRTS_REG_RESET                  (0x00000000)

/*=============================*/
struct __UART_SRTS_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_SHADOW_REQUEST_TO_SEND       : 1;
};
#define UART_SHADOW_REQUEST_TO_SEND           (0x0001)



#define UART_SBCR_REG                        (0x50001090) /* Shadow Break Control Register */
#define UART_SBCR_REG_RESET                  (0x00000000)

/*=============================*/
struct __UART_SBCR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_SHADOW_BREAK_CONTROL         : 1;
};
#define UART_SHADOW_BREAK_CONTROL             (0x0001)



#define UART_SDMAM_REG                       (0x50001094) /* Shadow DMA Mode */
#define UART_SDMAM_REG_RESET                 (0x00000000)

/*=============================*/
struct __UART_SDMAM_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_SHADOW_DMA_MODE              : 1;
};
#define UART_SHADOW_DMA_MODE                  (0x0001)



#define UART_SFE_REG                         (0x50001098) /* Shadow FIFO Enable */
#define UART_SFE_REG_RESET                   (0x00000000)

/*=============================*/
struct __UART_SFE_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_SHADOW_FIFO_ENABLE           : 1;
};
#define UART_SHADOW_FIFO_ENABLE               (0x0001)



#define UART_SRT_REG                         (0x5000109C) /* Shadow RCVR Trigger */
#define UART_SRT_REG_RESET                   (0x00000000)

/*=============================*/
struct __UART_SRT_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_SHADOW_RCVR_TRIGGER          : 2;
};
#define UART_SHADOW_RCVR_TRIGGER              (0x0003)



#define UART_STET_REG                        (0x500010A0) /* Shadow TX Empty Trigger */
#define UART_STET_REG_RESET                  (0x00000000)

/*=============================*/
struct __UART_STET_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_SHADOW_TX_EMPTY_TRIGGER      : 2;
};
#define UART_SHADOW_TX_EMPTY_TRIGGER          (0x0003)



#define UART_HTX_REG                         (0x500010A4) /* Halt TX */
#define UART_HTX_REG_RESET                   (0x00000000)

/*=============================*/
struct __UART_HTX_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_HALT_TX                      : 1;
};
#define UART_HALT_TX                          (0x0001)



#define UART_DMASA_REG                       (0x500010A8) /* DMA Software Acknowledge */
#define UART_DMASA_REG_RESET                 (0x00000000)

/*=============================*/
struct __UART_DMASA_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMASA                             : 1;
};
#define DMASA                                 (0x0001)



#define UART_DLF_REG                         (0x500010C0) /* Divisor Latch Fraction Register */
#define UART_DLF_REG_RESET                   (0x00000000)

/*=============================*/
struct __UART_DLF_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_DLF                          : 4;
};
#define UART_DLF                              (0x000F)



#define UART_UCV_REG                         (0x500010F8) /* Component Version */
#define UART_UCV_REG_RESET                   (0x0000352A)

/*=============================*/
struct __UART_UCV_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UCV                               : 16;
};
#define UCV                                   (0xFFFF)



#define UART_UCV_HIGH_REG                    (0x500010FA) /* Component Version */
#define UART_UCV_HIGH_REG_RESET              (0x00003331)

/*=============================*/
struct __UART_UCV_HIGH_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UCV                               : 16;
};
#define UCV                                   (0xFFFF)



#define UART_CTR_REG                         (0x500010FC) /* Component Type Register */
#define UART_CTR_REG_RESET                   (0x00000110)

/*=============================*/
struct __UART_CTR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_CTR                               : 16;
};
#define CTR                                   (0xFFFF)



#define UART_CTR_HIGH_REG                    (0x500010FE) /* Component Type Register */
#define UART_CTR_HIGH_REG_RESET              (0x00004457)

/*=============================*/
struct __UART_CTR_HIGH_REG
/*=============================*/
{
    volatile uint16_t BITFLD_CTR                               : 16;
};
#define CTR                                   (0xFFFF)



#define UART2_RBR_THR_DLL_REG                (0x50001100) /* Receive Buffer Register/Transmit Holding Register/Divisor Latch Low */
#define UART2_RBR_THR_DLL_REG_RESET          (0x00000000)

/*=============================*/
struct __UART2_RBR_THR_DLL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_RBR_THR_DLL                       : 8;
};
#define RBR_THR_DLL                           (0x00FF)



#define UART2_IER_DLH_REG                    (0x50001104) /* Interrupt Enable Register/Divisor Latch High */
#define UART2_IER_DLH_REG_RESET              (0x00000000)

/*=============================*/
struct __UART2_IER_DLH_REG
/*=============================*/
{
    volatile uint16_t BITFLD_ERBFI_dlh0                        : 1;
    volatile uint16_t BITFLD_ETBEI_dlh1                        : 1;
    volatile uint16_t BITFLD_ELSI_dhl2                         : 1;
    volatile uint16_t BITFLD_EDSSI_dlh3                        : 1;
    volatile uint16_t BITFLD_dlh6_4                            : 3;
    volatile uint16_t BITFLD_PTIME_dlh7                        : 1;
};
#define ERBFI_dlh0                            (0x0001)
#define ETBEI_dlh1                            (0x0002)
#define ELSI_dhl2                             (0x0004)
#define EDSSI_dlh3                            (0x0008)
#define dlh6_4                                (0x0070)
#define PTIME_dlh7                            (0x0080)



#define UART2_IIR_FCR_REG                    (0x50001108) /* Interrupt Identification Register/FIFO Control Register */
#define UART2_IIR_FCR_REG_RESET              (0x00000001)

/*=============================*/
struct __UART2_IIR_FCR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_IID0_FIFOE                   : 1;
    volatile uint16_t BITFLD_UART_IID1_RFIFOE                  : 1;
    volatile uint16_t BITFLD_UART_IID2_XFIFOR                  : 1;
    volatile uint16_t BITFLD_UART_IID3_DMAM                    : 1;
    volatile uint16_t BITFLD_UART_TET                          : 2;
    volatile uint16_t BITFLD_UART_FIFOSE_RT                    : 2;
};
#define UART_IID0_FIFOE                       (0x0001)
#define UART_IID1_RFIFOE                      (0x0002)
#define UART_IID2_XFIFOR                      (0x0004)
#define UART_IID3_DMAM                        (0x0008)
#define UART_TET                              (0x0030)
#define UART_FIFOSE_RT                        (0x00C0)



#define UART2_LCR_REG                        (0x5000110C) /* Line Control Register */
#define UART2_LCR_REG_RESET                  (0x00000000)

/*=============================*/
struct __UART2_LCR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_DLS                          : 2;
    volatile uint16_t BITFLD_UART_STOP                         : 1;
    volatile uint16_t BITFLD_UART_PEN                          : 1;
    volatile uint16_t BITFLD_UART_EPS                          : 1;
    volatile uint16_t                                          : 1;
    volatile uint16_t BITFLD_UART_BC                           : 1;
    volatile uint16_t BITFLD_UART_DLAB                         : 1;
};
#define UART_DLS                              (0x0003)
#define UART_STOP                             (0x0004)
#define UART_PEN                              (0x0008)
#define UART_EPS                              (0x0010)
#define UART_BC                               (0x0040)
#define UART_DLAB                             (0x0080)



#define UART2_MCR_REG                        (0x50001110) /* Modem Control Register */
#define UART2_MCR_REG_RESET                  (0x00000000)

/*=============================*/
struct __UART2_MCR_REG
/*=============================*/
{
    volatile uint16_t                                          : 4;
    volatile uint16_t BITFLD_UART_LB                           : 1;
};
#define UART_LB                               (0x0010)



#define UART2_LSR_REG                        (0x50001114) /* Line Status Register */
#define UART2_LSR_REG_RESET                  (0x00000060)

/*=============================*/
struct __UART2_LSR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_DR                           : 1;
    volatile uint16_t BITFLD_UART_OE                           : 1;
    volatile uint16_t BITFLD_UART_PE                           : 1;
    volatile uint16_t BITFLD_UART_FE                           : 1;
    volatile uint16_t BITFLD_UART_BI                           : 1;
    volatile uint16_t BITFLD_UART_THRE                         : 1;
    volatile uint16_t BITFLD_UART_TEMT                         : 1;
    volatile uint16_t BITFLD_UART_RFE                          : 1;
};
#define UART_DR                               (0x0001)
#define UART_OE                               (0x0002)
#define UART_PE                               (0x0004)
#define UART_FE                               (0x0008)
#define UART_BI                               (0x0010)
#define UART_THRE                             (0x0020)
#define UART_TEMT                             (0x0040)
#define UART_RFE                              (0x0080)



#define UART2_SCR_REG                        (0x5000111C) /* Scratchpad Register */
#define UART2_SCR_REG_RESET                  (0x00000000)

/*=============================*/
struct __UART2_SCR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_SCRATCH_PAD                  : 8;
};
#define UART_SCRATCH_PAD                      (0x00FF)



#define UART2_SRBR_STHR0_REG                 (0x50001130) /* Shadow Receive/Transmit Buffer Register */
#define UART2_SRBR_STHR0_REG_RESET           (0x00000000)

/*=============================*/
struct __UART2_SRBR_STHR0_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART2_SRBR_STHR1_REG                 (0x50001134) /* Shadow Receive/Transmit Buffer Register */
#define UART2_SRBR_STHR1_REG_RESET           (0x00000000)

/*=============================*/
struct __UART2_SRBR_STHR1_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART2_SRBR_STHR2_REG                 (0x50001138) /* Shadow Receive/Transmit Buffer Register */
#define UART2_SRBR_STHR2_REG_RESET           (0x00000000)

/*=============================*/
struct __UART2_SRBR_STHR2_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART2_SRBR_STHR3_REG                 (0x5000113C) /* Shadow Receive/Transmit Buffer Register */
#define UART2_SRBR_STHR3_REG_RESET           (0x00000000)

/*=============================*/
struct __UART2_SRBR_STHR3_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART2_SRBR_STHR4_REG                 (0x50001140) /* Shadow Receive/Transmit Buffer Register */
#define UART2_SRBR_STHR4_REG_RESET           (0x00000000)

/*=============================*/
struct __UART2_SRBR_STHR4_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART2_SRBR_STHR5_REG                 (0x50001144) /* Shadow Receive/Transmit Buffer Register */
#define UART2_SRBR_STHR5_REG_RESET           (0x00000000)

/*=============================*/
struct __UART2_SRBR_STHR5_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART2_SRBR_STHR6_REG                 (0x50001148) /* Shadow Receive/Transmit Buffer Register */
#define UART2_SRBR_STHR6_REG_RESET           (0x00000000)

/*=============================*/
struct __UART2_SRBR_STHR6_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART2_SRBR_STHR7_REG                 (0x5000114C) /* Shadow Receive/Transmit Buffer Register */
#define UART2_SRBR_STHR7_REG_RESET           (0x00000000)

/*=============================*/
struct __UART2_SRBR_STHR7_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART2_SRBR_STHR8_REG                 (0x50001150) /* Shadow Receive/Transmit Buffer Register */
#define UART2_SRBR_STHR8_REG_RESET           (0x00000000)

/*=============================*/
struct __UART2_SRBR_STHR8_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART2_SRBR_STHR9_REG                 (0x50001154) /* Shadow Receive/Transmit Buffer Register */
#define UART2_SRBR_STHR9_REG_RESET           (0x00000000)

/*=============================*/
struct __UART2_SRBR_STHR9_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART2_SRBR_STHR10_REG                (0x50001158) /* Shadow Receive/Transmit Buffer Register */
#define UART2_SRBR_STHR10_REG_RESET          (0x00000000)

/*=============================*/
struct __UART2_SRBR_STHR10_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART2_SRBR_STHR11_REG                (0x5000115C) /* Shadow Receive/Transmit Buffer Register */
#define UART2_SRBR_STHR11_REG_RESET          (0x00000000)

/*=============================*/
struct __UART2_SRBR_STHR11_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART2_SRBR_STHR12_REG                (0x50001160) /* Shadow Receive/Transmit Buffer Register */
#define UART2_SRBR_STHR12_REG_RESET          (0x00000000)

/*=============================*/
struct __UART2_SRBR_STHR12_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART2_SRBR_STHR13_REG                (0x50001164) /* Shadow Receive/Transmit Buffer Register */
#define UART2_SRBR_STHR13_REG_RESET          (0x00000000)

/*=============================*/
struct __UART2_SRBR_STHR13_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART2_SRBR_STHR14_REG                (0x50001168) /* Shadow Receive/Transmit Buffer Register */
#define UART2_SRBR_STHR14_REG_RESET          (0x00000000)

/*=============================*/
struct __UART2_SRBR_STHR14_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART2_SRBR_STHR15_REG                (0x5000116C) /* Shadow Receive/Transmit Buffer Register */
#define UART2_SRBR_STHR15_REG_RESET          (0x00000000)

/*=============================*/
struct __UART2_SRBR_STHR15_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SRBR_STHRx                        : 8;
};
#define SRBR_STHRx                            (0x00FF)



#define UART2_FAR_REG                        (0x50001170) /* FIFO Access Register */
#define UART2_FAR_REG_RESET                  (0x00000000)

/*=============================*/
struct __UART2_FAR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_FAR                          : 1;
};
#define UART_FAR                              (0x0001)



#define UART2_USR_REG                        (0x5000117C) /* UART Status Register */
#define UART2_USR_REG_RESET                  (0x00000006)

/*=============================*/
struct __UART2_USR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_BUSY                         : 1;
    volatile uint16_t BITFLD_UART_TFNF                         : 1;
    volatile uint16_t BITFLD_UART_TFE                          : 1;
    volatile uint16_t BITFLD_UART_RFNE                         : 1;
    volatile uint16_t BITFLD_UART_RFF                          : 1;
};
#define UART_BUSY                             (0x0001)
#define UART_TFNF                             (0x0002)
#define UART_TFE                              (0x0004)
#define UART_RFNE                             (0x0008)
#define UART_RFF                              (0x0010)



#define UART2_TFL_REG                        (0x50001180) /* Transmit FIFO Level */
#define UART2_TFL_REG_RESET                  (0x00000000)

/*=============================*/
struct __UART2_TFL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_TRANSMIT_FIFO_LEVEL          : 5;
};
#define UART_TRANSMIT_FIFO_LEVEL              (0x001F)



#define UART2_RFL_REG                        (0x50001184) /* Receive FIFO Level */
#define UART2_RFL_REG_RESET                  (0x00000000)

/*=============================*/
struct __UART2_RFL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_RECEIVE_FIFO_LEVEL           : 5;
};
#define UART_RECEIVE_FIFO_LEVEL               (0x001F)



#define UART2_SRR_REG                        (0x50001188) /* Software Reset Register. */
#define UART2_SRR_REG_RESET                  (0x00000000)

/*=============================*/
struct __UART2_SRR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_UR                           : 1;
    volatile uint16_t BITFLD_UART_RFR                          : 1;
    volatile uint16_t BITFLD_UART_XFR                          : 1;
};
#define UART_UR                               (0x0001)
#define UART_RFR                              (0x0002)
#define UART_XFR                              (0x0004)



#define UART2_SBCR_REG                       (0x50001190) /* Shadow Break Control Register */
#define UART2_SBCR_REG_RESET                 (0x00000000)

/*=============================*/
struct __UART2_SBCR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_SHADOW_BREAK_CONTROL         : 1;
};
#define UART_SHADOW_BREAK_CONTROL             (0x0001)



#define UART2_SDMAM_REG                      (0x50001194) /* Shadow DMA Mode */
#define UART2_SDMAM_REG_RESET                (0x00000000)

/*=============================*/
struct __UART2_SDMAM_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_SHADOW_DMA_MODE              : 1;
};
#define UART_SHADOW_DMA_MODE                  (0x0001)



#define UART2_SFE_REG                        (0x50001198) /* Shadow FIFO Enable */
#define UART2_SFE_REG_RESET                  (0x00000000)

/*=============================*/
struct __UART2_SFE_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_SHADOW_FIFO_ENABLE           : 1;
};
#define UART_SHADOW_FIFO_ENABLE               (0x0001)



#define UART2_SRT_REG                        (0x5000119C) /* Shadow RCVR Trigger */
#define UART2_SRT_REG_RESET                  (0x00000000)

/*=============================*/
struct __UART2_SRT_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_SHADOW_RCVR_TRIGGER          : 2;
};
#define UART_SHADOW_RCVR_TRIGGER              (0x0003)



#define UART2_STET_REG                       (0x500011A0) /* Shadow TX Empty Trigger */
#define UART2_STET_REG_RESET                 (0x00000000)

/*=============================*/
struct __UART2_STET_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_SHADOW_TX_EMPTY_TRIGGER      : 2;
};
#define UART_SHADOW_TX_EMPTY_TRIGGER          (0x0003)



#define UART2_HTX_REG                        (0x500011A4) /* Halt TX */
#define UART2_HTX_REG_RESET                  (0x00000000)

/*=============================*/
struct __UART2_HTX_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_HALT_TX                      : 1;
};
#define UART_HALT_TX                          (0x0001)



#define UART2_DMASA_REG                      (0x500011A8) /* DMA Software Acknowledge */
#define UART2_DMASA_REG_RESET                (0x00000000)

/*=============================*/
struct __UART2_DMASA_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DMASA                             : 1;
};
#define DMASA                                 (0x0001)



#define UART2_DLF_REG                        (0x500011C0) /* Divisor Latch Fraction Register */
#define UART2_DLF_REG_RESET                  (0x00000000)

/*=============================*/
struct __UART2_DLF_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UART_DLF                          : 4;
};
#define UART_DLF                              (0x000F)



#define UART2_UCV_REG                        (0x500011F8) /* Component Version */
#define UART2_UCV_REG_RESET                  (0x0000352A)

/*=============================*/
struct __UART2_UCV_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UCV                               : 16;
};
#define UCV                                   (0xFFFF)



#define UART2_UCV_HIGH_REG                   (0x500011FA) /* Component Version */
#define UART2_UCV_HIGH_REG_RESET             (0x00003331)

/*=============================*/
struct __UART2_UCV_HIGH_REG
/*=============================*/
{
    volatile uint16_t BITFLD_UCV                               : 16;
};
#define UCV                                   (0xFFFF)



#define UART2_CTR_REG                        (0x500011FC) /* Component Type Register */
#define UART2_CTR_REG_RESET                  (0x00000110)

/*=============================*/
struct __UART2_CTR_REG
/*=============================*/
{
    volatile uint16_t BITFLD_CTR                               : 16;
};
#define CTR                                   (0xFFFF)



#define UART2_CTR_HIGH_REG                   (0x500011FE) /* Component Type Register */
#define UART2_CTR_HIGH_REG_RESET             (0x00004457)

/*=============================*/
struct __UART2_CTR_HIGH_REG
/*=============================*/
{
    volatile uint16_t BITFLD_CTR                               : 16;
};
#define CTR                                   (0xFFFF)



/*===========================================================================*/
/* memory map Version */
/*===========================================================================*/



#define CHIP_ID1_REG                         (0x50003200) /* Chip identification register 1. */
#define CHIP_ID1_REG_RESET                   (0x00000032)

/*=============================*/
struct __CHIP_ID1_REG
/*=============================*/
{
    volatile uint16_t BITFLD_CHIP_ID1                          : 8;
};
#define CHIP_ID1                              (0x00FF)



#define CHIP_ID2_REG                         (0x50003204) /* Chip identification register 2. */
#define CHIP_ID2_REG_RESET                   (0x00000036)

/*=============================*/
struct __CHIP_ID2_REG
/*=============================*/
{
    volatile uint16_t BITFLD_CHIP_ID2                          : 8;
};
#define CHIP_ID2                              (0x00FF)



#define CHIP_ID3_REG                         (0x50003208) /* Chip identification register 3. */
#define CHIP_ID3_REG_RESET                   (0x00000033)

/*=============================*/
struct __CHIP_ID3_REG
/*=============================*/
{
    volatile uint16_t BITFLD_CHIP_ID3                          : 8;
};
#define CHIP_ID3                              (0x00FF)



#define CHIP_ID4_REG                         (0x5000320C) /* Chip identification register 4. */
#define CHIP_ID4_REG_RESET                   (0x00000032)

/*=============================*/
struct __CHIP_ID4_REG
/*=============================*/
{
    volatile uint16_t BITFLD_CHIP_ID4                          : 8;
};
#define CHIP_ID4                              (0x00FF)



#define CHIP_SWC_REG                         (0x50003210) /* Software compatibility register. */
#define CHIP_SWC_REG_RESET                   (0x00000000)

/*=============================*/
struct __CHIP_SWC_REG
/*=============================*/
{
    volatile uint16_t BITFLD_CHIP_SWC                          : 4;
};
#define CHIP_SWC                              (0x000F)



#define CHIP_REVISION_REG                    (0x50003214) /* Chip revision register. */
#define CHIP_REVISION_REG_RESET              (0x00000041)

/*=============================*/
struct __CHIP_REVISION_REG
/*=============================*/
{
    volatile uint16_t BITFLD_CHIP_REVISION                     : 8;
};
#define CHIP_REVISION                         (0x00FF)



#define CHIP_TEST1_REG                       (0x500032F8) /* Chip test register 1. */
#define CHIP_TEST1_REG_RESET                 (0x00000043)

/*=============================*/
struct __CHIP_TEST1_REG
/*=============================*/
{
    volatile uint16_t BITFLD_CHIP_LAYOUT_REVISION              : 8;
};
#define CHIP_LAYOUT_REVISION                  (0x00FF)



#define CHIP_TEST2_REG                       (0x500032FC) /* Chip test register 2. */
#define CHIP_TEST2_REG_RESET                 (0x00000000)

/*=============================*/
struct __CHIP_TEST2_REG
/*=============================*/
{
    volatile uint16_t BITFLD_CHIP_METAL_OPTION                 : 4;
};
#define CHIP_METAL_OPTION                     (0x000F)



/*===========================================================================*/
/* memory map WDOG */
/*===========================================================================*/



#define WATCHDOG_REG                         (0x50003100) /* Watchdog timer register. */
#define WATCHDOG_REG_RESET                   (0x000000FF)

/*=============================*/
struct __WATCHDOG_REG
/*=============================*/
{
    volatile uint16_t BITFLD_WDOG_VAL                          : 8;
    volatile uint16_t BITFLD_WDOG_VAL_NEG                      : 1;
    volatile uint16_t BITFLD_WDOG_WEN                          : 7;
};
#define WDOG_VAL                              (0x00FF)
#define WDOG_VAL_NEG                          (0x0100)
#define WDOG_WEN                              (0xFE00)



#define WATCHDOG_CTRL_REG                    (0x50003102) /* Watchdog control register. */
#define WATCHDOG_CTRL_REG_RESET              (0x00000000)

/*=============================*/
struct __WATCHDOG_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_NMI_RST                           : 1;
    volatile uint16_t                                          : 1;
};
#define NMI_RST                               (0x0001)



/*===========================================================================*/
/* memory map WKUP */
/*===========================================================================*/



#define WKUP_CTRL_REG                        (0x50000100) /* Control register for the wakeup counter */
#define WKUP_CTRL_REG_RESET                  (0x00000000)

/*=============================*/
struct __WKUP_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_WKUP_DEB_VALUE                    : 6;
    volatile uint16_t BITFLD_WKUP_SFT_KEYHIT                   : 1;
    volatile uint16_t BITFLD_WKUP_ENABLE_IRQ                   : 1;
    volatile uint16_t BITFLD_WKUP2_ENABLE_IRQ                  : 1;
};
#define WKUP_DEB_VALUE                        (0x003F)
#define WKUP_SFT_KEYHIT                       (0x0040)
#define WKUP_ENABLE_IRQ                       (0x0080)
#define WKUP2_ENABLE_IRQ                      (0x0100)



#define WKUP_COMPARE_REG                     (0x50000102) /* Number of events before wakeup interrupt */
#define WKUP_COMPARE_REG_RESET               (0x00000000)

/*=============================*/
struct __WKUP_COMPARE_REG
/*=============================*/
{
    volatile uint16_t BITFLD_WKUP_COMPARE                      : 8;
};
#define WKUP_COMPARE                          (0x00FF)



#define WKUP_IRQ_STATUS_REG                  (0x50000104) /* Reset wakeup interrupt */
#define WKUP_IRQ_STATUS_REG_RESET            (0x00000000)

/*=============================*/
struct __WKUP_IRQ_STATUS_REG
/*=============================*/
{
    volatile uint16_t BITFLD_WKUP_IRQ_STATUS                   : 1;
    volatile uint16_t BITFLD_WKUP2_IRQ_STATUS                  : 1;
    volatile uint16_t BITFLD_WKUP_CNTR_RST                     : 1;
    volatile uint16_t BITFLD_WKUP2_CNTR_RST                    : 1;
};
#define WKUP_IRQ_STATUS                       (0x0001)
#define WKUP2_IRQ_STATUS                      (0x0002)
#define WKUP_CNTR_RST                         (0x0004)
#define WKUP2_CNTR_RST                        (0x0008)



#define WKUP_COUNTER_REG                     (0x50000106) /* Actual number of events of the wakeup counter */
#define WKUP_COUNTER_REG_RESET               (0x00000000)

/*=============================*/
struct __WKUP_COUNTER_REG
/*=============================*/
{
    volatile uint16_t BITFLD_EVENT_VALUE                       : 8;
    volatile uint16_t BITFLD_EVENT2_VALUE                      : 8;
};
#define EVENT_VALUE                           (0x00FF)
#define EVENT2_VALUE                          (0xFF00)



#define WKUP_SELECT_GPIO_REG                 (0x50000108) /* Select which inputs from P0 port can trigger wkup counter */
#define WKUP_SELECT_GPIO_REG_RESET           (0x00000000)

/*=============================*/
struct __WKUP_SELECT_GPIO_REG
/*=============================*/
{
    volatile uint16_t BITFLD_WKUP_SELECT_GPIO                  : 12;
};
#define WKUP_SELECT_GPIO                      (0x0FFF)



#define WKUP2_SELECT_GPIO_REG                (0x5000010A) /* Select which inputs from P1 port can trigger wkup counter */
#define WKUP2_SELECT_GPIO_REG_RESET          (0x00000000)

/*=============================*/
struct __WKUP2_SELECT_GPIO_REG
/*=============================*/
{
    volatile uint16_t BITFLD_WKUP2_SELECT_GPIO                 : 12;
};
#define WKUP2_SELECT_GPIO                     (0x0FFF)



#define WKUP_POL_GPIO_REG                    (0x5000010C) /* Select the sensitivity polarity for each P0 input */
#define WKUP_POL_GPIO_REG_RESET              (0x00000000)

/*=============================*/
struct __WKUP_POL_GPIO_REG
/*=============================*/
{
    volatile uint16_t BITFLD_WKUP_POL_GPIO                     : 12;
};
#define WKUP_POL_GPIO                         (0x0FFF)



#define WKUP2_POL_GPIO_REG                   (0x5000010E) /* Select the sensitivity polarity for each P1 input */
#define WKUP2_POL_GPIO_REG_RESET             (0x00000000)

/*=============================*/
struct __WKUP2_POL_GPIO_REG
/*=============================*/
{
    volatile uint16_t BITFLD_WKUP2_POL_GPIO                    : 12;
};
#define WKUP2_POL_GPIO                        (0x0FFF)



/*===========================================================================*/
/* Test mode spec map */
/*===========================================================================*/



#define BLE_ADVCHMAP_REG                     (0x40000090) /* Advertising Channel Map */
#define BLE_ADVCHMAP_REG_RESET               (0x00000007)

/*=============================*/
struct __BLE_ADVCHMAP_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ADVCHMAP                          : 3;
};
#define ADVCHMAP                              (0x0007)



#define RF_ATTR_REG                          (0x40001000)
#define RF_ATTR_REG_RESET                    (0x0C000820)

/*=============================*/
struct __RF_ATTR_REG
/*=============================*/
{
    volatile uint32_t                                          : 3;
    volatile uint32_t BITFLD_IFF_POLARITY                      : 1;
    volatile uint32_t                                          : 1;
    volatile uint32_t                                          : 1;
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_RF_BIAS                           : 4;
    volatile uint32_t BITFLD_TIA_BIAS                          : 1;
    volatile uint32_t                                          : 11;
    volatile uint32_t BITFLD_PA_POWER_SETTING                  : 4;
};
#define IFF_POLARITY                          (0x0008)
#define RF_BIAS                               (0x0F00)
#define TIA_BIAS                              (0x1000)
#define PA_POWER_SETTING                      (0xF000000)



#define RF_RADIO_INIT_REG                    (0x40001004)
#define RF_RADIO_INIT_REG_RESET              (0x00000000)

/*=============================*/
struct __RF_RADIO_INIT_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RADIO_LDO_EN                      : 1;
    volatile uint32_t BITFLD_RADIO_LDO_EN_SEL                  : 1;
    volatile uint32_t BITFLD_RADIO_LDO_EN_WR                   : 1;
    volatile uint32_t BITFLD_ADPLLDIG_PWR_SW1_EN               : 1;
    volatile uint32_t BITFLD_ADPLLDIG_LDO_EN_SEL               : 1;
    volatile uint32_t BITFLD_ADPLLDIG_LDO_EN_WR                : 1;
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_ADPLLDIG_HRESET_N                 : 1;
    volatile uint32_t BITFLD_ADPLLDIG_HCLK_EN                  : 1;
    volatile uint32_t                                          : 6;
    volatile uint32_t BITFLD_RADIO_REGS_RDY                    : 1;
    volatile uint32_t BITFLD_ADPLLDIG_HCLK_DIS                 : 1;
    volatile uint32_t                                          : 6;
    volatile uint32_t BITFLD_RADIO_INIT_AUTOCLEAR              : 1;
};
#define RADIO_LDO_EN                          (0x0001)
#define RADIO_LDO_EN_SEL                      (0x0002)
#define RADIO_LDO_EN_WR                       (0x0004)
#define ADPLLDIG_PWR_SW1_EN                   (0x0008)
#define ADPLLDIG_LDO_EN_SEL                   (0x0010)
#define ADPLLDIG_LDO_EN_WR                    (0x0020)
#define ADPLLDIG_HRESET_N                     (0x0100)
#define ADPLLDIG_HCLK_EN                      (0x0200)
#define RADIO_REGS_RDY                        (0x10000)
#define ADPLLDIG_HCLK_DIS                     (0x20000)
#define RADIO_INIT_AUTOCLEAR                  (0x1000000)



#define RF_LDO_STATUS_REG                    (0x40001008)
#define RF_LDO_STATUS_REG_RESET              (0x00000000)

/*=============================*/
struct __RF_LDO_STATUS_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RADIO_LDO_EN_RD                   : 1;
    volatile uint32_t BITFLD_RADIO_LDO_ZERO_EN_RD              : 1;
    volatile uint32_t BITFLD_ADPLLDIG_LDO_EN_RD                : 1;
    volatile uint32_t BITFLD_ADPLLDIG_LDO_ZERO_EN_RD           : 1;
    volatile uint32_t BITFLD_ldo_dco_en_rd                     : 1;
    volatile uint32_t BITFLD_ldo_dtc_en_rd                     : 1;
    volatile uint32_t BITFLD_ldo_radio_vref_hold_rd            : 1;
    volatile uint32_t BITFLD_ldo_dco_vref_hold_rd              : 1;
    volatile uint32_t BITFLD_ldo_dtc_vref_hold_rd              : 1;
};
#define RADIO_LDO_EN_RD                       (0x0001)
#define RADIO_LDO_ZERO_EN_RD                  (0x0002)
#define ADPLLDIG_LDO_EN_RD                    (0x0004)
#define ADPLLDIG_LDO_ZERO_EN_RD               (0x0008)
#define ldo_dco_en_rd                         (0x0010)
#define ldo_dtc_en_rd                         (0x0020)
#define ldo_radio_vref_hold_rd                (0x0040)
#define ldo_dco_vref_hold_rd                  (0x0080)
#define ldo_dtc_vref_hold_rd                  (0x0100)



#define RF_ADPLLDIG_CTRL_REG                 (0x4000100C)
#define RF_ADPLLDIG_CTRL_REG_RESET           (0x00000010)

/*=============================*/
struct __RF_ADPLLDIG_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_OPENLOOP_RDY_SEL                  : 1;
    volatile uint32_t BITFLD_OPENLOOP_RDY_WR                   : 1;
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_PWR_SW_TIM_CTRL                   : 3;
};
#define OPENLOOP_RDY_SEL                      (0x0001)
#define OPENLOOP_RDY_WR                       (0x0002)
#define PWR_SW_TIM_CTRL                       (0x0070)



#define RF_AGC_EXT_LUT_REG                   (0x40001010)
#define RF_AGC_EXT_LUT_REG_RESET             (0x00000000)

/*=============================*/
struct __RF_AGC_EXT_LUT_REG
/*=============================*/
{
    volatile uint32_t BITFLD_AGC_EXT_LUT                       : 10;
};
#define AGC_EXT_LUT                           (0x03FF)



#define RF_CALSTATE_REG                      (0x40001014)
#define RF_CALSTATE_REG_RESET                (0x00000000)

/*=============================*/
struct __RF_CALSTATE_REG
/*=============================*/
{
    volatile uint32_t BITFLD_CALSTATE                          : 4;
};
#define CALSTATE                              (0x000F)



#define RF_SCAN_FEEDBACK_REG                 (0x40001018)
#define RF_SCAN_FEEDBACK_REG_RESET           (0x00000000)
//register RF_SCAN_FEEDBACK_REG found for which all fields are reserved, omitting.



#define RF_CAL_CTRL_REG                      (0x40001020)
#define RF_CAL_CTRL_REG_RESET                (0x00000000)

/*=============================*/
struct __RF_CAL_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SO_CAL                            : 1;
    volatile uint32_t BITFLD_EO_CAL                            : 1;
    volatile uint32_t BITFLD_RF_CAL_CTRL_SPARE                 : 1;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_DC_OFFSET_CAL_DIS                 : 1;
};
#define SO_CAL                                (0x0001)
#define EO_CAL                                (0x0002)
#define RF_CAL_CTRL_SPARE                     (0x0004)
#define DC_OFFSET_CAL_DIS                     (0x0010)



#define RF_IRQ_CTRL_REG                      (0x40001024)
#define RF_IRQ_CTRL_REG_RESET                (0x00000001)

/*=============================*/
struct __RF_IRQ_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_EO_CAL_CLEAR                      : 1;
};
#define EO_CAL_CLEAR                          (0x0001)



#define RF_ADCI_DC_OFFSET_REG                (0x40001028)
#define RF_ADCI_DC_OFFSET_REG_RESET          (0x00020100)

/*=============================*/
struct __RF_ADCI_DC_OFFSET_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ADC_OFFP_I_RD                     : 9;
    volatile uint32_t BITFLD_ADC_OFFN_I_RD                     : 9;
};
#define ADC_OFFP_I_RD                         (0x01FF)
#define ADC_OFFN_I_RD                         (0x3FE00)



#define RF_ADCQ_DC_OFFSET_REG                (0x4000102C)
#define RF_ADCQ_DC_OFFSET_REG_RESET          (0x00020100)

/*=============================*/
struct __RF_ADCQ_DC_OFFSET_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ADC_OFFP_Q_RD                     : 9;
    volatile uint32_t BITFLD_ADC_OFFN_Q_RD                     : 9;
};
#define ADC_OFFP_Q_RD                         (0x01FF)
#define ADC_OFFN_Q_RD                         (0x3FE00)



#define RF_SPARE_REG                         (0x40001030)
#define RF_SPARE_REG_RESET                   (0x00000000)

/*=============================*/
struct __RF_SPARE_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RF_SPARE_BITS                     : 16;
    volatile uint32_t BITFLD_RF_SPARE_BITS_HV                  : 8;
    volatile uint32_t BITFLD_RF_SPARE_IN                       : 4;
    volatile uint32_t BITFLD_RF_SPARE_IN_EN                    : 1;
};
#define RF_SPARE_BITS                         (0xFFFF)
#define RF_SPARE_BITS_HV                      (0xFF0000)
#define RF_SPARE_IN                           (0xF000000)
#define RF_SPARE_IN_EN                        (0x10000000)



#define RF_IFF_CTRL_REG                      (0x4000103C)
#define RF_IFF_CTRL_REG_RESET                (0x00000001)

/*=============================*/
struct __RF_IFF_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_IF_CAL_TRIM                       : 2;
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_IF_MUTE                           : 1;
    volatile uint32_t BITFLD_IFF_DCOC_DAC_DIS                  : 1;
    volatile uint32_t BITFLD_RF_IFF_CTRL_SPARE                 : 6;
    volatile uint32_t BITFLD_IFF_COMPLEX_DIS                   : 1;
    volatile uint32_t BITFLD_IFF_DCOC_DAC_REFCUR_CTRL          : 2;
};
#define IF_CAL_TRIM                           (0x0003)
#define IF_MUTE                               (0x0010)
#define IFF_DCOC_DAC_DIS                      (0x0020)
#define RF_IFF_CTRL_SPARE                     (0x0FC0)
#define IFF_COMPLEX_DIS                       (0x1000)
#define IFF_DCOC_DAC_REFCUR_CTRL              (0x6000)



#define RF_ADC_CTRL1_REG                     (0x40001040)
#define RF_ADC_CTRL1_REG_RESET               (0x00000000)

/*=============================*/
struct __RF_ADC_CTRL1_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ADC_DC_OFFSET_SEL                 : 1;
    volatile uint32_t                                          : 12;
    volatile uint32_t BITFLD_ADC_MUTE                          : 1;
    volatile uint32_t BITFLD_ADC_SIGN                          : 1;
};
#define ADC_DC_OFFSET_SEL                     (0x0001)
#define ADC_MUTE                              (0x2000)
#define ADC_SIGN                              (0x4000)



#define RF_ADC_CTRL2_REG                     (0x40001044)
#define RF_ADC_CTRL2_REG_RESET               (0x00000000)

/*=============================*/
struct __RF_ADC_CTRL2_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ADC_OFFP_I_WR                     : 9;
    volatile uint32_t BITFLD_ADC_OFFN_I_WR                     : 9;
};
#define ADC_OFFP_I_WR                         (0x01FF)
#define ADC_OFFN_I_WR                         (0x3FE00)



#define RF_ADC_CTRL3_REG                     (0x40001048)
#define RF_ADC_CTRL3_REG_RESET               (0x00000000)

/*=============================*/
struct __RF_ADC_CTRL3_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ADC_OFFP_Q_WR                     : 9;
    volatile uint32_t BITFLD_ADC_OFFN_Q_WR                     : 9;
};
#define ADC_OFFP_Q_WR                         (0x01FF)
#define ADC_OFFN_Q_WR                         (0x3FE00)



#define RF_PA_CTRL_REG                       (0x4000104C)
#define RF_PA_CTRL_REG_RESET                 (0x00000300)

/*=============================*/
struct __RF_PA_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_TRIM_DUTY_POS                     : 3;
    volatile uint32_t BITFLD_TRIM_DUTY_NEG                     : 3;
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_PA_RAMP_STEP_SPEED                : 2;
};
#define TRIM_DUTY_POS                         (0x0007)
#define TRIM_DUTY_NEG                         (0x0038)
#define PA_RAMP_STEP_SPEED                    (0x0300)



#define RF_LDO_VREF_SEL_REG                  (0x40001058)
#define RF_LDO_VREF_SEL_REG_RESET            (0x00000000)

/*=============================*/
struct __RF_LDO_VREF_SEL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RF_LDO_RADIO_VREF_SEL             : 1;
    volatile uint32_t BITFLD_RF_LDO_DTC_VREF_SEL               : 1;
    volatile uint32_t BITFLD_RF_LDO_DCO_VREF_SEL               : 1;
};
#define RF_LDO_RADIO_VREF_SEL                 (0x0001)
#define RF_LDO_DTC_VREF_SEL                   (0x0002)
#define RF_LDO_DCO_VREF_SEL                   (0x0004)



#define RF_MIXER_CTRL1_REG                   (0x40001064)
#define RF_MIXER_CTRL1_REG_RESET             (0x010F010F)

/*=============================*/
struct __RF_MIXER_CTRL1_REG
/*=============================*/
{
    volatile uint32_t BITFLD_MIXER_IP2_DAC_I_TRIM              : 9;
    volatile uint32_t                                          : 7;
    volatile uint32_t BITFLD_MIXER_IP2_DAC_Q_TRIM              : 9;
};
#define MIXER_IP2_DAC_I_TRIM                  (0x01FF)
#define MIXER_IP2_DAC_Q_TRIM                  (0x1FF0000)



#define RF_MIXER_CTRL2_REG                   (0x40001068)
#define RF_MIXER_CTRL2_REG_RESET             (0x00000000)

/*=============================*/
struct __RF_MIXER_CTRL2_REG
/*=============================*/
{
    volatile uint32_t BITFLD_MIX_CAL_CAP_WR_1M                 : 4;
    volatile uint32_t                                          : 4;
    volatile uint32_t BITFLD_MIX_CAL_CAP_WR_2M                 : 4;
    volatile uint32_t                                          : 4;
    volatile uint32_t BITFLD_MIX_CAL_SELECT                    : 1;
};
#define MIX_CAL_CAP_WR_1M                     (0x000F)
#define MIX_CAL_CAP_WR_2M                     (0x0F00)
#define MIX_CAL_SELECT                        (0x10000)



#define RF_IO_CTRL_REG                       (0x40001074)
#define RF_IO_CTRL_REG_RESET                 (0x00000100)

/*=============================*/
struct __RF_IO_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RFIO_TUNE_CAP_TRIM_RX             : 4;
    volatile uint32_t                                          : 4;
    volatile uint32_t BITFLD_RFIO_TUNE_CAP_TRIM_TX             : 4;
};
#define RFIO_TUNE_CAP_TRIM_RX                 (0x000F)
#define RFIO_TUNE_CAP_TRIM_TX                 (0x0F00)



#define RF_LNA_CTRL1_REG                     (0x40001078)
#define RF_LNA_CTRL1_REG_RESET               (0x01084210)

/*=============================*/
struct __RF_LNA_CTRL1_REG
/*=============================*/
{
    volatile uint32_t BITFLD_LNA_TRIM_GAIN0_HP                 : 5;
    volatile uint32_t BITFLD_LNA_TRIM_GAIN1_HP                 : 5;
    volatile uint32_t BITFLD_LNA_TRIM_GAIN2_HP                 : 5;
    volatile uint32_t BITFLD_LNA_TRIM_GAIN3_HP                 : 5;
    volatile uint32_t BITFLD_LNA_TRIM_GAIN4_HP                 : 5;
};
#define LNA_TRIM_GAIN0_HP                     (0x001F)
#define LNA_TRIM_GAIN1_HP                     (0x03E0)
#define LNA_TRIM_GAIN2_HP                     (0x7C00)
#define LNA_TRIM_GAIN3_HP                     (0xF8000)
#define LNA_TRIM_GAIN4_HP                     (0x1F00000)



#define RF_LNA_CTRL2_REG                     (0x4000107C)
#define RF_LNA_CTRL2_REG_RESET               (0x00D6B5AD)

/*=============================*/
struct __RF_LNA_CTRL2_REG
/*=============================*/
{
    volatile uint32_t BITFLD_LNA_TRIM_GAIN0_LP                 : 5;
    volatile uint32_t BITFLD_LNA_TRIM_GAIN1_LP                 : 5;
    volatile uint32_t BITFLD_LNA_TRIM_GAIN2_LP                 : 5;
    volatile uint32_t BITFLD_LNA_TRIM_GAIN3_LP                 : 5;
    volatile uint32_t BITFLD_LNA_TRIM_GAIN4_LP                 : 5;
};
#define LNA_TRIM_GAIN0_LP                     (0x001F)
#define LNA_TRIM_GAIN1_LP                     (0x03E0)
#define LNA_TRIM_GAIN2_LP                     (0x7C00)
#define LNA_TRIM_GAIN3_LP                     (0xF8000)
#define LNA_TRIM_GAIN4_LP                     (0x1F00000)



#define RF_LNA_CTRL3_REG                     (0x40001080)
#define RF_LNA_CTRL3_REG_RESET               (0x00111114)

/*=============================*/
struct __RF_LNA_CTRL3_REG
/*=============================*/
{
    volatile uint32_t BITFLD_LNA_TRIM_CASC                     : 3;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_LNA_MODE_GAIN0_LP                 : 2;
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_LNA_MODE_GAIN1_LP                 : 2;
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_LNA_MODE_GAIN2_LP                 : 2;
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_LNA_MODE_GAIN3_LP                 : 2;
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_LNA_MODE_GAIN4_LP                 : 2;
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_LNA_SPARE                         : 2;
};
#define LNA_TRIM_CASC                         (0x0007)
#define LNA_MODE_GAIN0_LP                     (0x0030)
#define LNA_MODE_GAIN1_LP                     (0x0300)
#define LNA_MODE_GAIN2_LP                     (0x3000)
#define LNA_MODE_GAIN3_LP                     (0x30000)
#define LNA_MODE_GAIN4_LP                     (0x300000)
#define LNA_SPARE                             (0x3000000)



#define RF_ADPLLDIG_RFMON_CTRL_REG           (0x400010A0)
#define RF_ADPLLDIG_RFMON_CTRL_REG_RESET     (0x00000001)

/*=============================*/
struct __RF_ADPLLDIG_RFMON_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ADPLLDIG_SYNC_CLK_INV             : 1;
    volatile uint32_t BITFLD_ADPLLDIG_RFMON_MUX_SEL            : 3;
    volatile uint32_t BITFLD_ADPLLDIG_RFMON_SPARE              : 4;
};
#define ADPLLDIG_SYNC_CLK_INV                 (0x0001)
#define ADPLLDIG_RFMON_MUX_SEL                (0x000E)
#define ADPLLDIG_RFMON_SPARE                  (0x00F0)



#define RF_RDP_CTRL_REG                      (0x400010A4)
#define RF_RDP_CTRL_REG_RESET                (0x00000000)

/*=============================*/
struct __RF_RDP_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RDP_RFCU_SEL                      : 1;
    volatile uint32_t BITFLD_RDP_MOD_SEL1                      : 1;
    volatile uint32_t BITFLD_RDP_MOD_SEL2                      : 2;
    volatile uint32_t BITFLD_RDP_MOD_RATE                      : 2;
};
#define RDP_RFCU_SEL                          (0x0001)
#define RDP_MOD_SEL1                          (0x0002)
#define RDP_MOD_SEL2                          (0x000C)
#define RDP_MOD_RATE                          (0x0030)



#define RF_RFCU_CTRL_REG                     (0x400010A8)
#define RF_RFCU_CTRL_REG_RESET               (0x00000001)

/*=============================*/
struct __RF_RFCU_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RF_RFCU_CLK_DIV                   : 1;
};
#define RF_RFCU_CLK_DIV                       (0x0001)



#define RF_OVERRULE_REG                      (0x400010AC)
#define RF_OVERRULE_REG_RESET                (0x00000000)

/*=============================*/
struct __RF_OVERRULE_REG
/*=============================*/
{
    volatile uint32_t BITFLD_TX_EN_OVR                         : 2;
    volatile uint32_t BITFLD_RX_EN_OVR                         : 2;
};
#define TX_EN_OVR                             (0x0003)
#define RX_EN_OVR                             (0x000C)



#define RF_DIAGIRQ_CTRL_REG                  (0x400010B0)
#define RF_DIAGIRQ_CTRL_REG_RESET            (0x00000000)

/*=============================*/
struct __RF_DIAGIRQ_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_DIAG_BUS0_IRQ_MASK                : 1;
    volatile uint32_t BITFLD_DIAG_BUS0_SEL                     : 2;
    volatile uint32_t BITFLD_DIAG_BUS0_BIT_SEL                 : 3;
    volatile uint32_t BITFLD_DIAG_BUS0_EDGE_SEL                : 1;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_DIAG_BUS1_IRQ_MASK                : 1;
    volatile uint32_t BITFLD_DIAG_BUS1_SEL                     : 2;
    volatile uint32_t BITFLD_DIAG_BUS1_BIT_SEL                 : 3;
    volatile uint32_t BITFLD_DIAG_BUS1_EDGE_SEL                : 1;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_DIAG_BUS2_IRQ_MASK                : 1;
    volatile uint32_t BITFLD_DIAG_BUS2_SEL                     : 2;
    volatile uint32_t BITFLD_DIAG_BUS2_BIT_SEL                 : 3;
    volatile uint32_t BITFLD_DIAG_BUS2_EDGE_SEL                : 1;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_DIAG_BUS3_IRQ_MASK                : 1;
    volatile uint32_t BITFLD_DIAG_BUS3_SEL                     : 2;
    volatile uint32_t BITFLD_DIAG_BUS3_BIT_SEL                 : 3;
    volatile uint32_t BITFLD_DIAG_BUS3_EDGE_SEL                : 1;
};
#define DIAG_BUS0_IRQ_MASK                    (0x0001)
#define DIAG_BUS0_SEL                         (0x0006)
#define DIAG_BUS0_BIT_SEL                     (0x0038)
#define DIAG_BUS0_EDGE_SEL                    (0x0040)
#define DIAG_BUS1_IRQ_MASK                    (0x0100)
#define DIAG_BUS1_SEL                         (0x0600)
#define DIAG_BUS1_BIT_SEL                     (0x3800)
#define DIAG_BUS1_EDGE_SEL                    (0x4000)
#define DIAG_BUS2_IRQ_MASK                    (0x10000)
#define DIAG_BUS2_SEL                         (0x60000)
#define DIAG_BUS2_BIT_SEL                     (0x380000)
#define DIAG_BUS2_EDGE_SEL                    (0x400000)
#define DIAG_BUS3_IRQ_MASK                    (0x1000000)
#define DIAG_BUS3_SEL                         (0x6000000)
#define DIAG_BUS3_BIT_SEL                     (0x38000000)
#define DIAG_BUS3_EDGE_SEL                    (0x40000000)



#define RF_DIAGIRQ_STAT_REG                  (0x400010B4)
#define RF_DIAGIRQ_STAT_REG_RESET            (0x00000000)

/*=============================*/
struct __RF_DIAGIRQ_STAT_REG
/*=============================*/
{
    volatile uint32_t BITFLD_DIAGIRQ_STAT                      : 4;
};
#define DIAGIRQ_STAT                          (0x000F)



#define RF_LDO_CTRL_REG                      (0x400010B8)
#define RF_LDO_CTRL_REG_RESET                (0x00190333)

/*=============================*/
struct __RF_LDO_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_LDO_RADIO_LEVEL                   : 3;
    volatile uint32_t BITFLD_LDO_RADIO_CONT_ENABLE             : 1;
    volatile uint32_t BITFLD_LDO_DTC_LEVEL                     : 3;
    volatile uint32_t BITFLD_LDO_DTC_CONT_ENABLE               : 1;
    volatile uint32_t BITFLD_LDO_DCO_LEVEL                     : 3;
    volatile uint32_t BITFLD_LDO_DCO_CONT_ENABLE               : 1;
    volatile uint32_t                                          : 4;
    volatile uint32_t BITFLD_LDO_VREF_SMPL_TIME                : 5;
    volatile uint32_t                                          : 3;
    volatile uint32_t BITFLD_LDO_RADIO_HOLD_OVR_VAL            : 1;
    volatile uint32_t BITFLD_LDO_RADIO_HOLD_OVR_EN             : 1;
    volatile uint32_t BITFLD_LDO_DTC_HOLD_OVR_VAL              : 1;
    volatile uint32_t BITFLD_LDO_DTC_HOLD_OVR_EN               : 1;
    volatile uint32_t BITFLD_LDO_DCO_HOLD_OVR_VAL              : 1;
    volatile uint32_t BITFLD_LDO_DCO_HOLD_OVR_EN               : 1;
};
#define LDO_RADIO_LEVEL                       (0x0007)
#define LDO_RADIO_CONT_ENABLE                 (0x0008)
#define LDO_DTC_LEVEL                         (0x0070)
#define LDO_DTC_CONT_ENABLE                   (0x0080)
#define LDO_DCO_LEVEL                         (0x0700)
#define LDO_DCO_CONT_ENABLE                   (0x0800)
#define LDO_VREF_SMPL_TIME                    (0x1F0000)
#define LDO_RADIO_HOLD_OVR_VAL                (0x1000000)
#define LDO_RADIO_HOLD_OVR_EN                 (0x2000000)
#define LDO_DTC_HOLD_OVR_VAL                  (0x4000000)
#define LDO_DTC_HOLD_OVR_EN                   (0x8000000)
#define LDO_DCO_HOLD_OVR_VAL                  (0x10000000)
#define LDO_DCO_HOLD_OVR_EN                   (0x20000000)



#define RF_ENABLE_CONFIG0_REG                (0x40001200)
#define RF_ENABLE_CONFIG0_REG_RESET          (0x00000083)

/*=============================*/
struct __RF_ENABLE_CONFIG0_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RFIO_LDO_EN_DCF_RX                : 5;
    volatile uint32_t BITFLD_RFIO_LDO_EN_DCF_TX                : 5;
};
#define RFIO_LDO_EN_DCF_RX                    (0x001F)
#define RFIO_LDO_EN_DCF_TX                    (0x03E0)



#define RF_ENABLE_CONFIG1_REG                (0x40001204)
#define RF_ENABLE_CONFIG1_REG_RESET          (0x00000083)

/*=============================*/
struct __RF_ENABLE_CONFIG1_REG
/*=============================*/
{
    volatile uint32_t BITFLD_PA_LDO_EN_DCF_RX                  : 5;
    volatile uint32_t BITFLD_PA_LDO_EN_DCF_TX                  : 5;
};
#define PA_LDO_EN_DCF_RX                      (0x001F)
#define PA_LDO_EN_DCF_TX                      (0x03E0)



#define RF_ENABLE_CONFIG2_REG                (0x40001208)
#define RF_ENABLE_CONFIG2_REG_RESET          (0x00000003)

/*=============================*/
struct __RF_ENABLE_CONFIG2_REG
/*=============================*/
{
    volatile uint32_t BITFLD_LNA_LDO_EN_DCF_RX                 : 5;
    volatile uint32_t BITFLD_LNA_LDO_EN_DCF_TX                 : 5;
};
#define LNA_LDO_EN_DCF_RX                     (0x001F)
#define LNA_LDO_EN_DCF_TX                     (0x03E0)



#define RF_ENABLE_CONFIG3_REG                (0x4000120C)
#define RF_ENABLE_CONFIG3_REG_RESET          (0x00000003)

/*=============================*/
struct __RF_ENABLE_CONFIG3_REG
/*=============================*/
{
    volatile uint32_t BITFLD_MIX_LDO_EN_DCF_RX                 : 5;
    volatile uint32_t BITFLD_MIX_LDO_EN_DCF_TX                 : 5;
};
#define MIX_LDO_EN_DCF_RX                     (0x001F)
#define MIX_LDO_EN_DCF_TX                     (0x03E0)



#define RF_ENABLE_CONFIG4_REG                (0x40001210)
#define RF_ENABLE_CONFIG4_REG_RESET          (0x00000003)

/*=============================*/
struct __RF_ENABLE_CONFIG4_REG
/*=============================*/
{
    volatile uint32_t BITFLD_IFF_LDO_EN_DCF_RX                 : 5;
    volatile uint32_t BITFLD_IFF_LDO_EN_DCF_TX                 : 5;
};
#define IFF_LDO_EN_DCF_RX                     (0x001F)
#define IFF_LDO_EN_DCF_TX                     (0x03E0)



#define RF_ENABLE_CONFIG5_REG                (0x40001214)
#define RF_ENABLE_CONFIG5_REG_RESET          (0x00000003)

/*=============================*/
struct __RF_ENABLE_CONFIG5_REG
/*=============================*/
{
    volatile uint32_t BITFLD_IFFADC_LDO_EN_DCF_RX              : 5;
    volatile uint32_t BITFLD_IFFADC_LDO_EN_DCF_TX              : 5;
};
#define IFFADC_LDO_EN_DCF_RX                  (0x001F)
#define IFFADC_LDO_EN_DCF_TX                  (0x03E0)



#define RF_ENABLE_CONFIG6_REG                (0x40001218)
#define RF_ENABLE_CONFIG6_REG_RESET          (0x00000083)

/*=============================*/
struct __RF_ENABLE_CONFIG6_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ADPLL_TDC_LDO_EN_DCF_RX           : 5;
    volatile uint32_t BITFLD_ADPLL_TDC_LDO_EN_DCF_TX           : 5;
};
#define ADPLL_TDC_LDO_EN_DCF_RX               (0x001F)
#define ADPLL_TDC_LDO_EN_DCF_TX               (0x03E0)



#define RF_ENABLE_CONFIG7_REG                (0x4000121C)
#define RF_ENABLE_CONFIG7_REG_RESET          (0x00000083)

/*=============================*/
struct __RF_ENABLE_CONFIG7_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ADPLL_DTC_LDO_EN_DCF_RX           : 5;
    volatile uint32_t BITFLD_ADPLL_DTC_LDO_EN_DCF_TX           : 5;
};
#define ADPLL_DTC_LDO_EN_DCF_RX               (0x001F)
#define ADPLL_DTC_LDO_EN_DCF_TX               (0x03E0)



#define RF_ENABLE_CONFIG8_REG                (0x40001220)
#define RF_ENABLE_CONFIG8_REG_RESET          (0x00000083)

/*=============================*/
struct __RF_ENABLE_CONFIG8_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ADPLL_DCO_LDO_EN_DCF_RX           : 5;
    volatile uint32_t BITFLD_ADPLL_DCO_LDO_EN_DCF_TX           : 5;
};
#define ADPLL_DCO_LDO_EN_DCF_RX               (0x001F)
#define ADPLL_DCO_LDO_EN_DCF_TX               (0x03E0)



#define RF_ENABLE_CONFIG9_REG                (0x40001224)
#define RF_ENABLE_CONFIG9_REG_RESET          (0x00000041)

/*=============================*/
struct __RF_ENABLE_CONFIG9_REG
/*=============================*/
{
    volatile uint32_t BITFLD_LDO_ZERO_EN_DCF_RX                : 5;
    volatile uint32_t BITFLD_LDO_ZERO_EN_DCF_TX                : 5;
};
#define LDO_ZERO_EN_DCF_RX                    (0x001F)
#define LDO_ZERO_EN_DCF_TX                    (0x03E0)



#define RF_ENABLE_CONFIG10_REG               (0x40001228)
#define RF_ENABLE_CONFIG10_REG_RESET         (0x00000001)

/*=============================*/
struct __RF_ENABLE_CONFIG10_REG
/*=============================*/
{
    volatile uint32_t BITFLD_LNA_LDO_ZERO_DCF_RX               : 5;
    volatile uint32_t BITFLD_LNA_LDO_ZERO_DCF_TX               : 5;
};
#define LNA_LDO_ZERO_DCF_RX                   (0x001F)
#define LNA_LDO_ZERO_DCF_TX                   (0x03E0)



#define RF_ENABLE_CONFIG11_REG               (0x4000122C)
#define RF_ENABLE_CONFIG11_REG_RESET         (0x000000C5)

/*=============================*/
struct __RF_ENABLE_CONFIG11_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ADPLLDIG_LDO_ACTIVERDY_DCF_RX     : 5;
    volatile uint32_t BITFLD_ADPLLDIG_LDO_ACTIVERDY_DCF_TX     : 5;
};
#define ADPLLDIG_LDO_ACTIVERDY_DCF_RX         (0x001F)
#define ADPLLDIG_LDO_ACTIVERDY_DCF_TX         (0x03E0)



#define RF_ENABLE_CONFIG12_REG               (0x40001230)
#define RF_ENABLE_CONFIG12_REG_RESET         (0x0000018B)

/*=============================*/
struct __RF_ENABLE_CONFIG12_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ADPLLDIG_LDO_LP_DCF_RX            : 5;
    volatile uint32_t BITFLD_ADPLLDIG_LDO_LP_DCF_TX            : 5;
};
#define ADPLLDIG_LDO_LP_DCF_RX                (0x001F)
#define ADPLLDIG_LDO_LP_DCF_TX                (0x03E0)



#define RF_ENABLE_CONFIG13_REG               (0x40001234)
#define RF_ENABLE_CONFIG13_REG_RESET         (0x0000000F)

/*=============================*/
struct __RF_ENABLE_CONFIG13_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RFIO_RX_EN_DCF_RX                 : 5;
    volatile uint32_t BITFLD_RFIO_RX_EN_DCF_TX                 : 5;
};
#define RFIO_RX_EN_DCF_RX                     (0x001F)
#define RFIO_RX_EN_DCF_TX                     (0x03E0)



#define RF_ENABLE_CONFIG14_REG               (0x40001238)
#define RF_ENABLE_CONFIG14_REG_RESET         (0x000001C0)

/*=============================*/
struct __RF_ENABLE_CONFIG14_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RFIO_TX_EN_DCF_RX                 : 5;
    volatile uint32_t BITFLD_RFIO_TX_EN_DCF_TX                 : 5;
};
#define RFIO_TX_EN_DCF_RX                     (0x001F)
#define RFIO_TX_EN_DCF_TX                     (0x03E0)



#define RF_ENABLE_CONFIG15_REG               (0x4000123C)
#define RF_ENABLE_CONFIG15_REG_RESET         (0x000001C0)

/*=============================*/
struct __RF_ENABLE_CONFIG15_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RFIO_TX_HARM_EN_DCF_RX            : 5;
    volatile uint32_t BITFLD_RFIO_TX_HARM_EN_DCF_TX            : 5;
};
#define RFIO_TX_HARM_EN_DCF_RX                (0x001F)
#define RFIO_TX_HARM_EN_DCF_TX                (0x03E0)



#define RF_ENABLE_CONFIG16_REG               (0x40001240)
#define RF_ENABLE_CONFIG16_REG_RESET         (0x0000008F)

/*=============================*/
struct __RF_ENABLE_CONFIG16_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RFIO_BIAS_EN_DCF_RX               : 5;
    volatile uint32_t BITFLD_RFIO_BIAS_EN_DCF_TX               : 5;
};
#define RFIO_BIAS_EN_DCF_RX                   (0x001F)
#define RFIO_BIAS_EN_DCF_TX                   (0x03E0)



#define RF_ENABLE_CONFIG17_REG               (0x40001244)
#define RF_ENABLE_CONFIG17_REG_RESET         (0x00000210)

/*=============================*/
struct __RF_ENABLE_CONFIG17_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RFIO_BIAS_SH_OPEN_DCF_RX          : 5;
    volatile uint32_t BITFLD_RFIO_BIAS_SH_OPEN_DCF_TX          : 5;
};
#define RFIO_BIAS_SH_OPEN_DCF_RX              (0x001F)
#define RFIO_BIAS_SH_OPEN_DCF_TX              (0x03E0)



#define RF_ENABLE_CONFIG18_REG               (0x40001248)
#define RF_ENABLE_CONFIG18_REG_RESET         (0x000001A0)

/*=============================*/
struct __RF_ENABLE_CONFIG18_REG
/*=============================*/
{
    volatile uint32_t BITFLD_PA_RAMP_EN_DCF_RX                 : 5;
    volatile uint32_t BITFLD_PA_RAMP_EN_DCF_TX                 : 5;
};
#define PA_RAMP_EN_DCF_RX                     (0x001F)
#define PA_RAMP_EN_DCF_TX                     (0x03E0)



#define RF_ENABLE_CONFIG19_REG               (0x4000124C)
#define RF_ENABLE_CONFIG19_REG_RESET         (0x000001C0)

/*=============================*/
struct __RF_ENABLE_CONFIG19_REG
/*=============================*/
{
    volatile uint32_t BITFLD_PA_EN_DCF_RX                      : 5;
    volatile uint32_t BITFLD_PA_EN_DCF_TX                      : 5;
};
#define PA_EN_DCF_RX                          (0x001F)
#define PA_EN_DCF_TX                          (0x03E0)



#define RF_ENABLE_CONFIG20_REG               (0x40001250)
#define RF_ENABLE_CONFIG20_REG_RESET         (0x0000000F)

/*=============================*/
struct __RF_ENABLE_CONFIG20_REG
/*=============================*/
{
    volatile uint32_t BITFLD_LNA_CORE_EN_DCF_RX                : 5;
    volatile uint32_t BITFLD_LNA_CORE_EN_DCF_TX                : 5;
};
#define LNA_CORE_EN_DCF_RX                    (0x001F)
#define LNA_CORE_EN_DCF_TX                    (0x03E0)



#define RF_ENABLE_CONFIG21_REG               (0x40001254)
#define RF_ENABLE_CONFIG21_REG_RESET         (0x0000000F)

/*=============================*/
struct __RF_ENABLE_CONFIG21_REG
/*=============================*/
{
    volatile uint32_t BITFLD_LNA_CGM_EN_DCF_RX                 : 5;
    volatile uint32_t BITFLD_LNA_CGM_EN_DCF_TX                 : 5;
};
#define LNA_CGM_EN_DCF_RX                     (0x001F)
#define LNA_CGM_EN_DCF_TX                     (0x03E0)



#define RF_ENABLE_CONFIG22_REG               (0x40001258)
#define RF_ENABLE_CONFIG22_REG_RESET         (0x0000000F)

/*=============================*/
struct __RF_ENABLE_CONFIG22_REG
/*=============================*/
{
    volatile uint32_t BITFLD_MIX_EN_DCF_RX                     : 5;
    volatile uint32_t BITFLD_MIX_EN_DCF_TX                     : 5;
};
#define MIX_EN_DCF_RX                         (0x001F)
#define MIX_EN_DCF_TX                         (0x03E0)



#define RF_ENABLE_CONFIG23_REG               (0x4000125C)
#define RF_ENABLE_CONFIG23_REG_RESET         (0x00000010)

/*=============================*/
struct __RF_ENABLE_CONFIG23_REG
/*=============================*/
{
    volatile uint32_t BITFLD_MIX_BIAS_SH_OPEN_DCF_RX           : 5;
    volatile uint32_t BITFLD_MIX_BIAS_SH_OPEN_DCF_TX           : 5;
};
#define MIX_BIAS_SH_OPEN_DCF_RX               (0x001F)
#define MIX_BIAS_SH_OPEN_DCF_TX               (0x03E0)



#define RF_ENABLE_CONFIG24_REG               (0x40001260)
#define RF_ENABLE_CONFIG24_REG_RESET         (0x0000000F)

/*=============================*/
struct __RF_ENABLE_CONFIG24_REG
/*=============================*/
{
    volatile uint32_t BITFLD_IFF_EN_DCF_RX                     : 5;
    volatile uint32_t BITFLD_IFF_EN_DCF_TX                     : 5;
};
#define IFF_EN_DCF_RX                         (0x001F)
#define IFF_EN_DCF_TX                         (0x03E0)



#define RF_ENABLE_CONFIG25_REG               (0x40001264)
#define RF_ENABLE_CONFIG25_REG_RESET         (0x00000010)

/*=============================*/
struct __RF_ENABLE_CONFIG25_REG
/*=============================*/
{
    volatile uint32_t BITFLD_IFF_BIAS_SH_OPEN_DCF_RX           : 5;
    volatile uint32_t BITFLD_IFF_BIAS_SH_OPEN_DCF_TX           : 5;
};
#define IFF_BIAS_SH_OPEN_DCF_RX               (0x001F)
#define IFF_BIAS_SH_OPEN_DCF_TX               (0x03E0)



#define RF_ENABLE_CONFIG26_REG               (0x40001268)
#define RF_ENABLE_CONFIG26_REG_RESET         (0x0000000F)

/*=============================*/
struct __RF_ENABLE_CONFIG26_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ADC_CLK_EN_DCF_RX                 : 5;
    volatile uint32_t BITFLD_ADC_CLK_EN_DCF_TX                 : 5;
};
#define ADC_CLK_EN_DCF_RX                     (0x001F)
#define ADC_CLK_EN_DCF_TX                     (0x03E0)



#define RF_ENABLE_CONFIG27_REG               (0x4000126C)
#define RF_ENABLE_CONFIG27_REG_RESET         (0x00000010)

/*=============================*/
struct __RF_ENABLE_CONFIG27_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ADC_EN_DCF_RX                     : 5;
    volatile uint32_t BITFLD_ADC_EN_DCF_TX                     : 5;
};
#define ADC_EN_DCF_RX                         (0x001F)
#define ADC_EN_DCF_TX                         (0x03E0)



#define RF_ENABLE_CONFIG28_REG               (0x40001270)
#define RF_ENABLE_CONFIG28_REG_RESET         (0x00000041)

/*=============================*/
struct __RF_ENABLE_CONFIG28_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ADPLL_DCO_EN_DCF_RX               : 5;
    volatile uint32_t BITFLD_ADPLL_DCO_EN_DCF_TX               : 5;
};
#define ADPLL_DCO_EN_DCF_RX                   (0x001F)
#define ADPLL_DCO_EN_DCF_TX                   (0x03E0)



#define RF_ENABLE_CONFIG29_REG               (0x40001274)
#define RF_ENABLE_CONFIG29_REG_RESET         (0x00000041)

/*=============================*/
struct __RF_ENABLE_CONFIG29_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ADPLL_CLK_EN_DCF_RX               : 5;
    volatile uint32_t BITFLD_ADPLL_CLK_EN_DCF_TX               : 5;
};
#define ADPLL_CLK_EN_DCF_RX                   (0x001F)
#define ADPLL_CLK_EN_DCF_TX                   (0x03E0)



#define RF_ENABLE_CONFIG30_REG               (0x40001278)
#define RF_ENABLE_CONFIG30_REG_RESET         (0x00000107)

/*=============================*/
struct __RF_ENABLE_CONFIG30_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ADPLLDIG_RST_DCF_RX               : 5;
    volatile uint32_t BITFLD_ADPLLDIG_RST_DCF_TX               : 5;
};
#define ADPLLDIG_RST_DCF_RX                   (0x001F)
#define ADPLLDIG_RST_DCF_TX                   (0x03E0)



#define RF_ENABLE_CONFIG31_REG               (0x4000127C)
#define RF_ENABLE_CONFIG31_REG_RESET         (0x00000149)

/*=============================*/
struct __RF_ENABLE_CONFIG31_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ADPLLDIG_EN_DCF_RX                : 5;
    volatile uint32_t BITFLD_ADPLLDIG_EN_DCF_TX                : 5;
};
#define ADPLLDIG_EN_DCF_RX                    (0x001F)
#define ADPLLDIG_EN_DCF_TX                    (0x03E0)



#define RF_ENABLE_CONFIG32_REG               (0x40001280)
#define RF_ENABLE_CONFIG32_REG_RESET         (0x00000001)

/*=============================*/
struct __RF_ENABLE_CONFIG32_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ADPLLDIG_RX_EN_DCF_RX             : 5;
    volatile uint32_t BITFLD_ADPLLDIG_RX_EN_DCF_TX             : 5;
};
#define ADPLLDIG_RX_EN_DCF_RX                 (0x001F)
#define ADPLLDIG_RX_EN_DCF_TX                 (0x03E0)



#define RF_ENABLE_CONFIG33_REG               (0x40001284)
#define RF_ENABLE_CONFIG33_REG_RESET         (0x000001E0)

/*=============================*/
struct __RF_ENABLE_CONFIG33_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ADPLLDIG_PAIN_EN_DCF_RX           : 5;
    volatile uint32_t BITFLD_ADPLLDIG_PAIN_EN_DCF_TX           : 5;
};
#define ADPLLDIG_PAIN_EN_DCF_RX               (0x001F)
#define ADPLLDIG_PAIN_EN_DCF_TX               (0x03E0)



#define RF_ENABLE_CONFIG34_REG               (0x40001288)
#define RF_ENABLE_CONFIG34_REG_RESET         (0x000001C0)

/*=============================*/
struct __RF_ENABLE_CONFIG34_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ADPLL_LOBUF_PA_EN_DCF_RX          : 5;
    volatile uint32_t BITFLD_ADPLL_LOBUF_PA_EN_DCF_TX          : 5;
};
#define ADPLL_LOBUF_PA_EN_DCF_RX              (0x001F)
#define ADPLL_LOBUF_PA_EN_DCF_TX              (0x03E0)



#define RF_ENABLE_CONFIG35_REG               (0x4000128C)
#define RF_ENABLE_CONFIG35_REG_RESET         (0x00000294)

/*=============================*/
struct __RF_ENABLE_CONFIG35_REG
/*=============================*/
{
    volatile uint32_t BITFLD_CAL_EN_DCF_RX                     : 5;
    volatile uint32_t BITFLD_CAL_EN_DCF_TX                     : 5;
};
#define CAL_EN_DCF_RX                         (0x001F)
#define CAL_EN_DCF_TX                         (0x03E0)



#define RF_ENABLE_CONFIG36_REG               (0x40001290)
#define RF_ENABLE_CONFIG36_REG_RESET         (0x00000011)

/*=============================*/
struct __RF_ENABLE_CONFIG36_REG
/*=============================*/
{
    volatile uint32_t BITFLD_DEM_EN_DCF_RX                     : 5;
    volatile uint32_t BITFLD_DEM_EN_DCF_TX                     : 5;
};
#define DEM_EN_DCF_RX                         (0x001F)
#define DEM_EN_DCF_TX                         (0x03E0)



#define RF_ENABLE_CONFIG37_REG               (0x40001294)
#define RF_ENABLE_CONFIG37_REG_RESET         (0x00000000)

/*=============================*/
struct __RF_ENABLE_CONFIG37_REG
/*=============================*/
{
    volatile uint32_t BITFLD_DEM_DC_PARCAL_EN_DCF_RX           : 5;
    volatile uint32_t BITFLD_SPARE_DEM_DC_PARCAL_DCF_TX        : 5;
};
#define DEM_DC_PARCAL_EN_DCF_RX               (0x001F)
#define SPARE_DEM_DC_PARCAL_DCF_TX            (0x03E0)



#define RF_ENABLE_CONFIG38_REG               (0x40001298)
#define RF_ENABLE_CONFIG38_REG_RESET         (0x00000011)

/*=============================*/
struct __RF_ENABLE_CONFIG38_REG
/*=============================*/
{
    volatile uint32_t BITFLD_DEM_AGC_UNFREEZE_EN_DCF_RX        : 5;
    volatile uint32_t BITFLD_SPARE_DEM_AGC_UNFREEZE_EN_DCF_TX  : 5;
};
#define DEM_AGC_UNFREEZE_EN_DCF_RX            (0x001F)
#define SPARE_DEM_AGC_UNFREEZE_EN_DCF_TX      (0x03E0)



#define RF_ENABLE_CONFIG39_REG               (0x4000129C)
#define RF_ENABLE_CONFIG39_REG_RESET         (0x00000013)

/*=============================*/
struct __RF_ENABLE_CONFIG39_REG
/*=============================*/
{
    volatile uint32_t BITFLD_DEM_SIGDETECT_EN_DCF_RX           : 5;
    volatile uint32_t BITFLD_SPARE_DEM_SIGDETECT_EN_DCF_TX     : 5;
};
#define DEM_SIGDETECT_EN_DCF_RX               (0x001F)
#define SPARE_DEM_SIGDETECT_EN_DCF_TX         (0x03E0)



#define RF_ENABLE_CONFIG40_REG               (0x400012A0)
#define RF_ENABLE_CONFIG40_REG_RESET         (0x00000253)

/*=============================*/
struct __RF_ENABLE_CONFIG40_REG
/*=============================*/
{
    volatile uint32_t BITFLD_PHY_RDY4BS_DCF_RX                 : 5;
    volatile uint32_t BITFLD_PHY_RDY4BS_DCF_TX                 : 5;
};
#define PHY_RDY4BS_DCF_RX                     (0x001F)
#define PHY_RDY4BS_DCF_TX                     (0x03E0)



#define RF_ENABLE_CONFIG41_REG               (0x400012A4)
#define RF_ENABLE_CONFIG41_REG_RESET         (0x000000C5)

/*=============================*/
struct __RF_ENABLE_CONFIG41_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ADPLL_RDY_FOR_DIV_DCF_RX          : 5;
    volatile uint32_t BITFLD_ADPLL_RDY_FOR_DIV_DCF_TX          : 5;
};
#define ADPLL_RDY_FOR_DIV_DCF_RX              (0x001F)
#define ADPLL_RDY_FOR_DIV_DCF_TX              (0x03E0)



#define RF_ENABLE_CONFIG42_REG               (0x400012A8)
#define RF_ENABLE_CONFIG42_REG_RESET         (0x00000000)

/*=============================*/
struct __RF_ENABLE_CONFIG42_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SPARE1_DCF_RX                     : 5;
    volatile uint32_t BITFLD_SPARE1_DCF_TX                     : 5;
};
#define SPARE1_DCF_RX                         (0x001F)
#define SPARE1_DCF_TX                         (0x03E0)



#define RF_ENABLE_CONFIG43_REG               (0x400012AC)
#define RF_ENABLE_CONFIG43_REG_RESET         (0x00000000)

/*=============================*/
struct __RF_ENABLE_CONFIG43_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SPARE2_DCF_RX                     : 5;
    volatile uint32_t BITFLD_SPARE2_DCF_TX                     : 5;
};
#define SPARE2_DCF_RX                         (0x001F)
#define SPARE2_DCF_TX                         (0x03E0)



#define RF_ENABLE_CONFIG44_REG               (0x400012B0)
#define RF_ENABLE_CONFIG44_REG_RESET         (0x00000000)

/*=============================*/
struct __RF_ENABLE_CONFIG44_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SPARE3_DCF_RX                     : 5;
    volatile uint32_t BITFLD_SPARE3_DCF_TX                     : 5;
};
#define SPARE3_DCF_RX                         (0x001F)
#define SPARE3_DCF_TX                         (0x03E0)



#define RF_ENABLE_CONFIG45_REG               (0x400012B4)
#define RF_ENABLE_CONFIG45_REG_RESET         (0x00000000)

/*=============================*/
struct __RF_ENABLE_CONFIG45_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SPARE4_DCF_RX                     : 5;
    volatile uint32_t BITFLD_SPARE4_DCF_TX                     : 5;
};
#define SPARE4_DCF_RX                         (0x001F)
#define SPARE4_DCF_TX                         (0x03E0)



#define RF_ENABLE_CONFIG46_REG               (0x400012B8)
#define RF_ENABLE_CONFIG46_REG_RESET         (0x00000000)

/*=============================*/
struct __RF_ENABLE_CONFIG46_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SPARE5_DCF_RX                     : 5;
    volatile uint32_t BITFLD_SPARE5_DCF_TX                     : 5;
};
#define SPARE5_DCF_RX                         (0x001F)
#define SPARE5_DCF_TX                         (0x03E0)



#define RF_CNTRL_TIMER_1_REG                 (0x40001300)
#define RF_CNTRL_TIMER_1_REG_RESET           (0x00000400)

/*=============================*/
struct __RF_CNTRL_TIMER_1_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_2_REG                 (0x40001304)
#define RF_CNTRL_TIMER_2_REG_RESET           (0x00000C00)

/*=============================*/
struct __RF_CNTRL_TIMER_2_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_3_REG                 (0x40001308)
#define RF_CNTRL_TIMER_3_REG_RESET           (0x00000408)

/*=============================*/
struct __RF_CNTRL_TIMER_3_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_4_REG                 (0x4000130C)
#define RF_CNTRL_TIMER_4_REG_RESET           (0x00000C08)

/*=============================*/
struct __RF_CNTRL_TIMER_4_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_5_REG                 (0x40001310)
#define RF_CNTRL_TIMER_5_REG_RESET           (0x00000212)

/*=============================*/
struct __RF_CNTRL_TIMER_5_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_6_REG                 (0x40001314)
#define RF_CNTRL_TIMER_6_REG_RESET           (0x00000A12)

/*=============================*/
struct __RF_CNTRL_TIMER_6_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_7_REG                 (0x40001318)
#define RF_CNTRL_TIMER_7_REG_RESET           (0x00000414)

/*=============================*/
struct __RF_CNTRL_TIMER_7_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_8_REG                 (0x4000131C)
#define RF_CNTRL_TIMER_8_REG_RESET           (0x00000C14)

/*=============================*/
struct __RF_CNTRL_TIMER_8_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_9_REG                 (0x40001320)
#define RF_CNTRL_TIMER_9_REG_RESET           (0x00000416)

/*=============================*/
struct __RF_CNTRL_TIMER_9_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_10_REG                (0x40001324)
#define RF_CNTRL_TIMER_10_REG_RESET          (0x00000C16)

/*=============================*/
struct __RF_CNTRL_TIMER_10_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_11_REG                (0x40001328)
#define RF_CNTRL_TIMER_11_REG_RESET          (0x0000081A)

/*=============================*/
struct __RF_CNTRL_TIMER_11_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_12_REG                (0x4000132C)
#define RF_CNTRL_TIMER_12_REG_RESET          (0x00000E1A)

/*=============================*/
struct __RF_CNTRL_TIMER_12_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_13_REG                (0x40001330)
#define RF_CNTRL_TIMER_13_REG_RESET          (0x00000220)

/*=============================*/
struct __RF_CNTRL_TIMER_13_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_14_REG                (0x40001334)
#define RF_CNTRL_TIMER_14_REG_RESET          (0x00000A20)

/*=============================*/
struct __RF_CNTRL_TIMER_14_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_15_REG                (0x40001338)
#define RF_CNTRL_TIMER_15_REG_RESET          (0x00000426)

/*=============================*/
struct __RF_CNTRL_TIMER_15_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_16_REG                (0x4000133C)
#define RF_CNTRL_TIMER_16_REG_RESET          (0x00000430)

/*=============================*/
struct __RF_CNTRL_TIMER_16_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_17_REG                (0x40001340)
#define RF_CNTRL_TIMER_17_REG_RESET          (0x00000837)

/*=============================*/
struct __RF_CNTRL_TIMER_17_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_18_REG                (0x40001344)
#define RF_CNTRL_TIMER_18_REG_RESET          (0x00000846)

/*=============================*/
struct __RF_CNTRL_TIMER_18_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_19_REG                (0x40001348)
#define RF_CNTRL_TIMER_19_REG_RESET          (0x00000850)

/*=============================*/
struct __RF_CNTRL_TIMER_19_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_20_REG                (0x4000134C)
#define RF_CNTRL_TIMER_20_REG_RESET          (0x0000125A)

/*=============================*/
struct __RF_CNTRL_TIMER_20_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_21_REG                (0x40001350)
#define RF_CNTRL_TIMER_21_REG_RESET          (0x00000000)

/*=============================*/
struct __RF_CNTRL_TIMER_21_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_22_REG                (0x40001354)
#define RF_CNTRL_TIMER_22_REG_RESET          (0x00000000)

/*=============================*/
struct __RF_CNTRL_TIMER_22_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_23_REG                (0x40001358)
#define RF_CNTRL_TIMER_23_REG_RESET          (0x00000000)

/*=============================*/
struct __RF_CNTRL_TIMER_23_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_24_REG                (0x4000135C)
#define RF_CNTRL_TIMER_24_REG_RESET          (0x00000000)

/*=============================*/
struct __RF_CNTRL_TIMER_24_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_25_REG                (0x40001360)
#define RF_CNTRL_TIMER_25_REG_RESET          (0x00000000)

/*=============================*/
struct __RF_CNTRL_TIMER_25_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_26_REG                (0x40001364)
#define RF_CNTRL_TIMER_26_REG_RESET          (0x00000000)

/*=============================*/
struct __RF_CNTRL_TIMER_26_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_27_REG                (0x40001368)
#define RF_CNTRL_TIMER_27_REG_RESET          (0x00000000)

/*=============================*/
struct __RF_CNTRL_TIMER_27_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_28_REG                (0x4000136C)
#define RF_CNTRL_TIMER_28_REG_RESET          (0x00000000)

/*=============================*/
struct __RF_CNTRL_TIMER_28_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_29_REG                (0x40001370)
#define RF_CNTRL_TIMER_29_REG_RESET          (0x00000000)

/*=============================*/
struct __RF_CNTRL_TIMER_29_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_30_REG                (0x40001374)
#define RF_CNTRL_TIMER_30_REG_RESET          (0x00000000)

/*=============================*/
struct __RF_CNTRL_TIMER_30_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_CNTRL_TIMER_31_REG                (0x40001378)
#define RF_CNTRL_TIMER_31_REG_RESET          (0x00000000)

/*=============================*/
struct __RF_CNTRL_TIMER_31_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SET_OFFSET                        : 8;
    volatile uint32_t BITFLD_RESET_OFFSET                      : 8;
};
#define SET_OFFSET                            (0x00FF)
#define RESET_OFFSET                          (0xFF00)



#define RF_ALWAYS_EN1_REG                    (0x40001380)
#define RF_ALWAYS_EN1_REG_RESET              (0x00000000)

/*=============================*/
struct __RF_ALWAYS_EN1_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ALW_EN_RFIO_LDO_EN                : 1;
    volatile uint32_t BITFLD_ALW_EN_PA_LDO_EN                  : 1;
    volatile uint32_t BITFLD_ALW_EN_LNA_LDO_EN                 : 1;
    volatile uint32_t BITFLD_ALW_EN_MIX_LDO_EN                 : 1;
    volatile uint32_t BITFLD_ALW_EN_IFF_LDO_EN                 : 1;
    volatile uint32_t BITFLD_ALW_EN_IFFADC_LDO_EN              : 1;
    volatile uint32_t BITFLD_ALW_EN_ADPLL_TDC_LDO_EN           : 1;
    volatile uint32_t BITFLD_ALW_EN_ADPLL_DTC_LDO_EN           : 1;
    volatile uint32_t BITFLD_ALW_EN_ADPLL_DCO_LDO_EN           : 1;
    volatile uint32_t BITFLD_ALW_EN_LDO_ZERO_EN                : 1;
    volatile uint32_t BITFLD_ALW_EN_LNA_LDO_ZERO               : 1;
    volatile uint32_t BITFLD_ALW_EN_ADPLLDIG_LDO_ACTIVERDY     : 1;
    volatile uint32_t BITFLD_ALW_EN_ADPLLDIG_LDO_LP            : 1;
    volatile uint32_t BITFLD_ALW_EN_RFIO_RX_EN                 : 1;
    volatile uint32_t BITFLD_ALW_EN_RFIO_TX_EN                 : 1;
    volatile uint32_t BITFLD_ALW_EN_RFIO_TX_HARM_EN            : 1;
    volatile uint32_t BITFLD_ALW_EN_RFIO_BIAS_EN               : 1;
    volatile uint32_t BITFLD_ALW_EN_RFIO_BIAS_SH_OPEN          : 1;
    volatile uint32_t BITFLD_ALW_EN_PA_RAMP_EN                 : 1;
    volatile uint32_t BITFLD_ALW_EN_PA_EN                      : 1;
    volatile uint32_t BITFLD_ALW_EN_LNA_CORE_EN                : 1;
    volatile uint32_t BITFLD_ALW_EN_LNA_CGM_EN                 : 1;
    volatile uint32_t BITFLD_ALW_EN_MIX_EN                     : 1;
    volatile uint32_t BITFLD_ALW_EN_MIX_BIAS_SH_OPEN           : 1;
    volatile uint32_t BITFLD_ALW_EN_IFF_EN                     : 1;
    volatile uint32_t BITFLD_ALW_EN_IFF_BIAS_SH_OPEN           : 1;
    volatile uint32_t BITFLD_ALW_EN_ADC_CLK_EN                 : 1;
    volatile uint32_t BITFLD_ALW_EN_ADC_EN                     : 1;
    volatile uint32_t BITFLD_ALW_EN_ADPLL_DCO_EN               : 1;
    volatile uint32_t BITFLD_ALW_EN_ADPLL_CLK_EN               : 1;
    volatile uint32_t BITFLD_ALW_EN_ADPLLDIG_RST               : 1;
    volatile uint32_t BITFLD_ALW_EN_ADPLLDIG_EN                : 1;
};
#define ALW_EN_RFIO_LDO_EN                    (0x0001)
#define ALW_EN_PA_LDO_EN                      (0x0002)
#define ALW_EN_LNA_LDO_EN                     (0x0004)
#define ALW_EN_MIX_LDO_EN                     (0x0008)
#define ALW_EN_IFF_LDO_EN                     (0x0010)
#define ALW_EN_IFFADC_LDO_EN                  (0x0020)
#define ALW_EN_ADPLL_TDC_LDO_EN               (0x0040)
#define ALW_EN_ADPLL_DTC_LDO_EN               (0x0080)
#define ALW_EN_ADPLL_DCO_LDO_EN               (0x0100)
#define ALW_EN_LDO_ZERO_EN                    (0x0200)
#define ALW_EN_LNA_LDO_ZERO                   (0x0400)
#define ALW_EN_ADPLLDIG_LDO_ACTIVERDY         (0x0800)
#define ALW_EN_ADPLLDIG_LDO_LP                (0x1000)
#define ALW_EN_RFIO_RX_EN                     (0x2000)
#define ALW_EN_RFIO_TX_EN                     (0x4000)
#define ALW_EN_RFIO_TX_HARM_EN                (0x8000)
#define ALW_EN_RFIO_BIAS_EN                   (0x10000)
#define ALW_EN_RFIO_BIAS_SH_OPEN              (0x20000)
#define ALW_EN_PA_RAMP_EN                     (0x40000)
#define ALW_EN_PA_EN                          (0x80000)
#define ALW_EN_LNA_CORE_EN                    (0x100000)
#define ALW_EN_LNA_CGM_EN                     (0x200000)
#define ALW_EN_MIX_EN                         (0x400000)
#define ALW_EN_MIX_BIAS_SH_OPEN               (0x800000)
#define ALW_EN_IFF_EN                         (0x1000000)
#define ALW_EN_IFF_BIAS_SH_OPEN               (0x2000000)
#define ALW_EN_ADC_CLK_EN                     (0x4000000)
#define ALW_EN_ADC_EN                         (0x8000000)
#define ALW_EN_ADPLL_DCO_EN                   (0x10000000)
#define ALW_EN_ADPLL_CLK_EN                   (0x20000000)
#define ALW_EN_ADPLLDIG_RST                   (0x40000000)
#define ALW_EN_ADPLLDIG_EN                    (0x80000000)



#define RF_ALWAYS_EN2_REG                    (0x40001384)
#define RF_ALWAYS_EN2_REG_RESET              (0x00000000)

/*=============================*/
struct __RF_ALWAYS_EN2_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ALW_EN_ADPLLDIG_RX_EN             : 1;
    volatile uint32_t BITFLD_ALW_EN_ADPLL_PAIN_EN              : 1;
    volatile uint32_t BITFLD_ALW_EN_ADPLL_LOBUF_PA_EN          : 1;
    volatile uint32_t BITFLD_ALW_EN_CAL_EN                     : 1;
    volatile uint32_t BITFLD_ALW_EN_DEM_EN                     : 1;
    volatile uint32_t BITFLD_ALW_EN_DEM_DC_PARCAL_EN           : 1;
    volatile uint32_t BITFLD_ALW_EN_DEM_AGC_UNFREEZE_EN        : 1;
    volatile uint32_t BITFLD_ALW_EN_DEM_SIGDETECT_EN           : 1;
    volatile uint32_t BITFLD_ALW_EN_PHY_RDY4BS                 : 1;
    volatile uint32_t BITFLD_ALW_EN_ADPLL_RDY_FOR_DIV          : 1;
    volatile uint32_t BITFLD_ALW_EN_SPARE1                     : 1;
    volatile uint32_t BITFLD_ALW_EN_SPARE2                     : 1;
    volatile uint32_t BITFLD_ALW_EN_SPARE3                     : 1;
    volatile uint32_t BITFLD_ALW_EN_SPARE4                     : 1;
    volatile uint32_t BITFLD_ALW_EN_SPARE5                     : 1;
};
#define ALW_EN_ADPLLDIG_RX_EN                 (0x0001)
#define ALW_EN_ADPLL_PAIN_EN                  (0x0002)
#define ALW_EN_ADPLL_LOBUF_PA_EN              (0x0004)
#define ALW_EN_CAL_EN                         (0x0008)
#define ALW_EN_DEM_EN                         (0x0010)
#define ALW_EN_DEM_DC_PARCAL_EN               (0x0020)
#define ALW_EN_DEM_AGC_UNFREEZE_EN            (0x0040)
#define ALW_EN_DEM_SIGDETECT_EN               (0x0080)
#define ALW_EN_PHY_RDY4BS                     (0x0100)
#define ALW_EN_ADPLL_RDY_FOR_DIV              (0x0200)
#define ALW_EN_SPARE1                         (0x0400)
#define ALW_EN_SPARE2                         (0x0800)
#define ALW_EN_SPARE3                         (0x1000)
#define ALW_EN_SPARE4                         (0x2000)
#define ALW_EN_SPARE5                         (0x4000)



#define RF_PORT_EN_REG                       (0x40001388)
#define RF_PORT_EN_REG_RESET                 (0x00000000)

/*=============================*/
struct __RF_PORT_EN_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RF_PORT0_RX                       : 1;
    volatile uint32_t BITFLD_RF_PORT0_TX                       : 1;
    volatile uint32_t BITFLD_RF_PORT1_RX                       : 1;
    volatile uint32_t BITFLD_RF_PORT1_TX                       : 1;
    volatile uint32_t BITFLD_RF_PORT2_RX                       : 1;
    volatile uint32_t BITFLD_RF_PORT2_TX                       : 1;
    volatile uint32_t BITFLD_RF_PORT3_RX                       : 1;
    volatile uint32_t BITFLD_RF_PORT3_TX                       : 1;
    volatile uint32_t BITFLD_RF_PORT4_RX                       : 1;
    volatile uint32_t BITFLD_RF_PORT4_TX                       : 1;
};
#define RF_PORT0_RX                           (0x0001)
#define RF_PORT0_TX                           (0x0002)
#define RF_PORT1_RX                           (0x0004)
#define RF_PORT1_TX                           (0x0008)
#define RF_PORT2_RX                           (0x0010)
#define RF_PORT2_TX                           (0x0020)
#define RF_PORT3_RX                           (0x0040)
#define RF_PORT3_TX                           (0x0080)
#define RF_PORT4_RX                           (0x0100)
#define RF_PORT4_TX                           (0x0200)



#define RF_PORT_POL_REG                      (0x4000138C)
#define RF_PORT_POL_REG_RESET                (0x00000000)

/*=============================*/
struct __RF_PORT_POL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RF_PORT0_POL                      : 1;
    volatile uint32_t BITFLD_RF_PORT1_POL                      : 1;
    volatile uint32_t BITFLD_RF_PORT2_POL                      : 1;
    volatile uint32_t BITFLD_RF_PORT3_POL                      : 1;
    volatile uint32_t BITFLD_RF_PORT4_POL                      : 1;
};
#define RF_PORT0_POL                          (0x0001)
#define RF_PORT1_POL                          (0x0002)
#define RF_PORT2_POL                          (0x0004)
#define RF_PORT3_POL                          (0x0008)
#define RF_PORT4_POL                          (0x0010)



#define RF_DEM_CTRL_REG                      (0x40002000)
#define RF_DEM_CTRL_REG_RESET                (0x00000003)

/*=============================*/
struct __RF_DEM_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_EQUAL_EN                          : 1;
    volatile uint32_t BITFLD_BLE_DDC_EN                        : 1;
    volatile uint32_t BITFLD_IQCORR_EN                         : 1;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_AGC_USE_GPIO_IN                   : 1;
    volatile uint32_t BITFLD_IQ_TO_GPIO_EN                     : 1;
};
#define EQUAL_EN                              (0x0001)
#define BLE_DDC_EN                            (0x0002)
#define IQCORR_EN                             (0x0004)
#define AGC_USE_GPIO_IN                       (0x0010)
#define IQ_TO_GPIO_EN                         (0x0020)



#define RF_AGC_LUT_0123_REG                  (0x40002004)
#define RF_AGC_LUT_0123_REG_RESET            (0x23030201)

/*=============================*/
struct __RF_AGC_LUT_0123_REG
/*=============================*/
{
    volatile uint32_t BITFLD_VGA2_GAIN0                        : 2;
    volatile uint32_t BITFLD_VGA1_GAIN0                        : 3;
    volatile uint32_t BITFLD_LNA_GAIN0                         : 3;
    volatile uint32_t BITFLD_VGA2_GAIN1                        : 2;
    volatile uint32_t BITFLD_VGA1_GAIN1                        : 3;
    volatile uint32_t BITFLD_LNA_GAIN1                         : 3;
    volatile uint32_t BITFLD_VGA2_GAIN2                        : 2;
    volatile uint32_t BITFLD_VGA1_GAIN2                        : 3;
    volatile uint32_t BITFLD_LNA_GAIN2                         : 3;
    volatile uint32_t BITFLD_VGA2_GAIN3                        : 2;
    volatile uint32_t BITFLD_VGA1_GAIN3                        : 3;
    volatile uint32_t BITFLD_LNA_GAIN3                         : 3;
};
#define VGA2_GAIN0                            (0x0003)
#define VGA1_GAIN0                            (0x001C)
#define LNA_GAIN0                             (0x00E0)
#define VGA2_GAIN1                            (0x0300)
#define VGA1_GAIN1                            (0x1C00)
#define LNA_GAIN1                             (0xE000)
#define VGA2_GAIN2                            (0x30000)
#define VGA1_GAIN2                            (0x1C0000)
#define LNA_GAIN2                             (0xE00000)
#define VGA2_GAIN3                            (0x3000000)
#define VGA1_GAIN3                            (0x1C000000)
#define LNA_GAIN3                             (0xE0000000)



#define RF_AGC_LUT_4567_REG                  (0x40002008)
#define RF_AGC_LUT_4567_REG_RESET            (0x332F2B27)

/*=============================*/
struct __RF_AGC_LUT_4567_REG
/*=============================*/
{
    volatile uint32_t BITFLD_VGA2_GAIN4                        : 2;
    volatile uint32_t BITFLD_VGA1_GAIN4                        : 3;
    volatile uint32_t BITFLD_LNA_GAIN4                         : 3;
    volatile uint32_t BITFLD_VGA2_GAIN5                        : 2;
    volatile uint32_t BITFLD_VGA1_GAIN5                        : 3;
    volatile uint32_t BITFLD_LNA_GAIN5                         : 3;
    volatile uint32_t BITFLD_VGA2_GAIN6                        : 2;
    volatile uint32_t BITFLD_VGA1_GAIN6                        : 3;
    volatile uint32_t BITFLD_LNA_GAIN6                         : 3;
    volatile uint32_t BITFLD_VGA2_GAIN7                        : 2;
    volatile uint32_t BITFLD_VGA1_GAIN7                        : 3;
    volatile uint32_t BITFLD_LNA_GAIN7                         : 3;
};
#define VGA2_GAIN4                            (0x0003)
#define VGA1_GAIN4                            (0x001C)
#define LNA_GAIN4                             (0x00E0)
#define VGA2_GAIN5                            (0x0300)
#define VGA1_GAIN5                            (0x1C00)
#define LNA_GAIN5                             (0xE000)
#define VGA2_GAIN6                            (0x30000)
#define VGA1_GAIN6                            (0x1C0000)
#define LNA_GAIN6                             (0xE00000)
#define VGA2_GAIN7                            (0x3000000)
#define VGA1_GAIN7                            (0x1C000000)
#define LNA_GAIN7                             (0xE0000000)



#define RF_AGC_LUT_89AB_REG                  (0x4000200C)
#define RF_AGC_LUT_89AB_REG_RESET            (0x77775737)

/*=============================*/
struct __RF_AGC_LUT_89AB_REG
/*=============================*/
{
    volatile uint32_t BITFLD_VGA2_GAIN8                        : 2;
    volatile uint32_t BITFLD_VGA1_GAIN8                        : 3;
    volatile uint32_t BITFLD_LNA_GAIN8                         : 3;
    volatile uint32_t BITFLD_VGA2_GAIN9                        : 2;
    volatile uint32_t BITFLD_VGA1_GAIN9                        : 3;
    volatile uint32_t BITFLD_LNA_GAIN9                         : 3;
    volatile uint32_t BITFLD_VGA2_GAIN10                       : 2;
    volatile uint32_t BITFLD_VGA1_GAIN10                       : 3;
    volatile uint32_t BITFLD_LNA_GAIN10                        : 3;
    volatile uint32_t BITFLD_VGA2_GAIN11                       : 2;
    volatile uint32_t BITFLD_VGA1_GAIN11                       : 3;
    volatile uint32_t BITFLD_LNA_GAIN11                        : 3;
};
#define VGA2_GAIN8                            (0x0003)
#define VGA1_GAIN8                            (0x001C)
#define LNA_GAIN8                             (0x00E0)
#define VGA2_GAIN9                            (0x0300)
#define VGA1_GAIN9                            (0x1C00)
#define LNA_GAIN9                             (0xE000)
#define VGA2_GAIN10                           (0x30000)
#define VGA1_GAIN10                           (0x1C0000)
#define LNA_GAIN10                            (0xE00000)
#define VGA2_GAIN11                           (0x3000000)
#define VGA1_GAIN11                           (0x1C000000)
#define LNA_GAIN11                            (0xE0000000)



#define RF_AGC_LUT_CDEF_REG                  (0x40002010)
#define RF_AGC_LUT_CDEF_REG_RESET            (0x01022243)

/*=============================*/
struct __RF_AGC_LUT_CDEF_REG
/*=============================*/
{
    volatile uint32_t BITFLD_VGA2_GAIN12                       : 2;
    volatile uint32_t BITFLD_VGA1_GAIN12                       : 3;
    volatile uint32_t BITFLD_LNA_GAIN12                        : 3;
    volatile uint32_t BITFLD_VGA2_GAIN13                       : 2;
    volatile uint32_t BITFLD_VGA1_GAIN13                       : 3;
    volatile uint32_t BITFLD_LNA_GAIN13                        : 3;
    volatile uint32_t BITFLD_VGA2_GAIN14                       : 2;
    volatile uint32_t BITFLD_VGA1_GAIN14                       : 3;
    volatile uint32_t BITFLD_LNA_GAIN14                        : 3;
    volatile uint32_t BITFLD_VGA2_GAIN15                       : 2;
    volatile uint32_t BITFLD_VGA1_GAIN15                       : 3;
    volatile uint32_t BITFLD_LNA_GAIN15                        : 3;
};
#define VGA2_GAIN12                           (0x0003)
#define VGA1_GAIN12                           (0x001C)
#define LNA_GAIN12                            (0x00E0)
#define VGA2_GAIN13                           (0x0300)
#define VGA1_GAIN13                           (0x1C00)
#define LNA_GAIN13                            (0xE000)
#define VGA2_GAIN14                           (0x30000)
#define VGA1_GAIN14                           (0x1C0000)
#define LNA_GAIN14                            (0xE00000)
#define VGA2_GAIN15                           (0x3000000)
#define VGA1_GAIN15                           (0x1C000000)
#define LNA_GAIN15                            (0xE0000000)



#define RF_AGC_CTRL1_REG                     (0x40002018)
#define RF_AGC_CTRL1_REG_RESET               (0x0056D50D)

/*=============================*/
struct __RF_AGC_CTRL1_REG
/*=============================*/
{
    volatile uint32_t BITFLD_AGC_TH_LOW                        : 7;
    volatile uint32_t BITFLD_AGC_TH_HIGH                       : 7;
    volatile uint32_t BITFLD_AGC_TH2_HIGH                      : 7;
    volatile uint32_t BITFLD_AGC_MODE                          : 2;
};
#define AGC_TH_LOW                            (0x007F)
#define AGC_TH_HIGH                           (0x3F80)
#define AGC_TH2_HIGH                          (0x1FC000)
#define AGC_MODE                              (0x600000)



#define RF_AGC_CTRL2_REG                     (0x4000201C)
#define RF_AGC_CTRL2_REG_RESET               (0x0040148D)

/*=============================*/
struct __RF_AGC_CTRL2_REG
/*=============================*/
{
    volatile uint32_t BITFLD_FASTAGC_EN                        : 1;
    volatile uint32_t BITFLD_FASTAGC_STEPS                     : 2;
    volatile uint32_t BITFLD_FASTAGC_WAIT                      : 2;
    volatile uint32_t BITFLD_AGCINC_WAIT                       : 2;
    volatile uint32_t BITFLD_AGCDEC_WAIT                       : 2;
    volatile uint32_t BITFLD_AGC_MAX_SETTING                   : 4;
    volatile uint32_t                                          : 4;
    volatile uint32_t BITFLD_AGCSETTING_SEL                    : 1;
    volatile uint32_t BITFLD_AGCSETTING_WR                     : 4;
    volatile uint32_t BITFLD_EN_FRZ_GAIN                       : 1;
};
#define FASTAGC_EN                            (0x0001)
#define FASTAGC_STEPS                         (0x0006)
#define FASTAGC_WAIT                          (0x0018)
#define AGCINC_WAIT                           (0x0060)
#define AGCDEC_WAIT                           (0x0180)
#define AGC_MAX_SETTING                       (0x1E00)
#define AGCSETTING_SEL                        (0x20000)
#define AGCSETTING_WR                         (0x3C0000)
#define EN_FRZ_GAIN                           (0x400000)



#define RF_AFC_CTRL_REG                      (0x40002020)
#define RF_AFC_CTRL_REG_RESET                (0x00000015)

/*=============================*/
struct __RF_AFC_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_AFC_MODE                          : 4;
    volatile uint32_t BITFLD_PAD_MODE                          : 2;
    volatile uint32_t BITFLD_APD_MODE                          : 3;
    volatile uint32_t BITFLD_AFC_SYNCF_DIRECT                  : 1;
};
#define AFC_MODE                              (0x000F)
#define PAD_MODE                              (0x0030)
#define APD_MODE                              (0x01C0)
#define AFC_SYNCF_DIRECT                      (0x0200)



#define RF_DC_OFFSET_CTRL1_REG               (0x40002024)
#define RF_DC_OFFSET_CTRL1_REG_RESET         (0x00020100)

/*=============================*/
struct __RF_DC_OFFSET_CTRL1_REG
/*=============================*/
{
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_DCOFFSET_I_WR                     : 8;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_DCOFFSET_Q_WR                     : 8;
};
#define DCOFFSET_I_WR                         (0x01FE)
#define DCOFFSET_Q_WR                         (0x3FC00)



#define RF_DC_OFFSET_CTRL2_REG               (0x40002028)
#define RF_DC_OFFSET_CTRL2_REG_RESET         (0x00F86696)

/*=============================*/
struct __RF_DC_OFFSET_CTRL2_REG
/*=============================*/
{
    volatile uint32_t BITFLD_DCOFFSET_SEL                      : 1;
    volatile uint32_t BITFLD_DCPARCAL_EN                       : 1;
    volatile uint32_t BITFLD_DCNSTEP                           : 3;
    volatile uint32_t BITFLD_DCFULLNGAIN                       : 3;
    volatile uint32_t BITFLD_DCPARCAL_INIT                     : 2;
    volatile uint32_t BITFLD_DCVGA1SCALE_EN                    : 1;
    volatile uint32_t BITFLD_DCPARNGAIN                        : 3;
    volatile uint32_t BITFLD_DCPAR_MULT_STEPS_EN               : 1;
    volatile uint32_t BITFLD_DCPAR_DCF_EN                      : 1;
    volatile uint32_t BITFLD_DCOC_RESULT_LNAGAIN0_LUT          : 2;
    volatile uint32_t BITFLD_DCOC_RESULT_LNAGAIN1_LUT          : 2;
    volatile uint32_t BITFLD_DCOC_RESULT_LNAGAIN2_LUT          : 2;
    volatile uint32_t BITFLD_DCOC_RESULT_LNAGAIN345_LUT        : 2;
};
#define DCOFFSET_SEL                          (0x0001)
#define DCPARCAL_EN                           (0x0002)
#define DCNSTEP                               (0x001C)
#define DCFULLNGAIN                           (0x00E0)
#define DCPARCAL_INIT                         (0x0300)
#define DCVGA1SCALE_EN                        (0x0400)
#define DCPARNGAIN                            (0x3800)
#define DCPAR_MULT_STEPS_EN                   (0x4000)
#define DCPAR_DCF_EN                          (0x8000)
#define DCOC_RESULT_LNAGAIN0_LUT              (0x30000)
#define DCOC_RESULT_LNAGAIN1_LUT              (0xC0000)
#define DCOC_RESULT_LNAGAIN2_LUT              (0x300000)
#define DCOC_RESULT_LNAGAIN345_LUT            (0xC00000)



#define RF_DC_OFFSET_CTRL3_REG               (0x4000202C)
#define RF_DC_OFFSET_CTRL3_REG_RESET         (0x0000DCE4)

/*=============================*/
struct __RF_DC_OFFSET_CTRL3_REG
/*=============================*/
{
    volatile uint32_t BITFLD_DCBETA_I                          : 8;
    volatile uint32_t BITFLD_DCBETA_Q                          : 8;
};
#define DCBETA_I                              (0x00FF)
#define DCBETA_Q                              (0xFF00)



#define RF_DC_OFFSET_CTRL4_REG               (0x40002030)
#define RF_DC_OFFSET_CTRL4_REG_RESET         (0x00009210)

/*=============================*/
struct __RF_DC_OFFSET_CTRL4_REG
/*=============================*/
{
    volatile uint32_t BITFLD_DCAGCSETTING_FULL0                : 4;
    volatile uint32_t BITFLD_DCAGCSETTING_FULL1                : 4;
    volatile uint32_t BITFLD_DCAGCSETTING_FULL2                : 4;
    volatile uint32_t BITFLD_DCAGCSETTING_FULL3                : 4;
};
#define DCAGCSETTING_FULL0                    (0x000F)
#define DCAGCSETTING_FULL1                    (0x00F0)
#define DCAGCSETTING_FULL2                    (0x0F00)
#define DCAGCSETTING_FULL3                    (0xF000)



#define RF_AGC_RESULT_REG                    (0x40002034)
#define RF_AGC_RESULT_REG_RESET              (0x00000000)

/*=============================*/
struct __RF_AGC_RESULT_REG
/*=============================*/
{
    volatile uint32_t BITFLD_AFC_RD                            : 8;
    volatile uint32_t BITFLD_AGCSETTING_RD                     : 4;
};
#define AFC_RD                                (0x00FF)
#define AGCSETTING_RD                         (0x0F00)



#define RF_RSSI_RESULT_REG                   (0x40002038)
#define RF_RSSI_RESULT_REG_RESET             (0x00000000)

/*=============================*/
struct __RF_RSSI_RESULT_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RSSI_LATCHED_RD                   : 10;
    volatile uint32_t BITFLD_RSSI_AVG_RD                       : 10;
};
#define RSSI_LATCHED_RD                       (0x03FF)
#define RSSI_AVG_RD                           (0xFFC00)



#define RF_DEM_ATTR_REG                      (0x4000203C)
#define RF_DEM_ATTR_REG_RESET                (0x00C4A18F)

/*=============================*/
struct __RF_DEM_ATTR_REG
/*=============================*/
{
    volatile uint32_t BITFLD_AFC_POLE1                         : 2;
    volatile uint32_t BITFLD_AFC_POLE2                         : 2;
    volatile uint32_t BITFLD_RXDATA_INV                        : 1;
    volatile uint32_t BITFLD_DEM_HSI_POL                       : 1;
    volatile uint32_t BITFLD_MATCH0101_TH                      : 4;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_AGC_SPEED8M_EN                    : 1;
    volatile uint32_t BITFLD_DCOC_SPEED8M_EN                   : 1;
    volatile uint32_t BITFLD_DCPOLE                            : 2;
    volatile uint32_t BITFLD_RSSI_TH                           : 6;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_RFADC_CLK_PHASE                   : 2;
    volatile uint32_t BITFLD_ADDR_TIMEOUT_X2                   : 1;
};
#define AFC_POLE1                             (0x0003)
#define AFC_POLE2                             (0x000C)
#define RXDATA_INV                            (0x0010)
#define DEM_HSI_POL                           (0x0020)
#define MATCH0101_TH                          (0x03C0)
#define AGC_SPEED8M_EN                        (0x0800)
#define DCOC_SPEED8M_EN                       (0x1000)
#define DCPOLE                                (0x6000)
#define RSSI_TH                               (0x1F8000)
#define RFADC_CLK_PHASE                       (0xC00000)
#define ADDR_TIMEOUT_X2                       (0x1000000)



#define RF_RSSI_COMP_CTRL_REG                (0x40002040)
#define RF_RSSI_COMP_CTRL_REG_RESET          (0x00088888)

/*=============================*/
struct __RF_RSSI_COMP_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RSSI_COMP0                        : 4;
    volatile uint32_t BITFLD_RSSI_COMP1                        : 4;
    volatile uint32_t BITFLD_RSSI_COMP2                        : 4;
    volatile uint32_t BITFLD_RSSI_COMP3                        : 4;
    volatile uint32_t BITFLD_RSSI_COMP4                        : 4;
};
#define RSSI_COMP0                            (0x000F)
#define RSSI_COMP1                            (0x00F0)
#define RSSI_COMP2                            (0x0F00)
#define RSSI_COMP3                            (0xF000)
#define RSSI_COMP4                            (0xF0000)



#define RF_DEM_TESTMODE_REG                  (0x40002044)
#define RF_DEM_TESTMODE_REG_RESET            (0x00000000)

/*=============================*/
struct __RF_DEM_TESTMODE_REG
/*=============================*/
{
    volatile uint32_t BITFLD_DEM_RFMON_SOURCE                  : 4;
    volatile uint32_t BITFLD_DEM_GPADC_MUX_SEL                 : 3;
    volatile uint32_t BITFLD_DEM_RFMON_TRIGGER                 : 2;
};
#define DEM_RFMON_SOURCE                      (0x000F)
#define DEM_GPADC_MUX_SEL                     (0x0070)
#define DEM_RFMON_TRIGGER                     (0x0180)



#define RF_DEM_IQCORRECT_REG                 (0x40002048)
#define RF_DEM_IQCORRECT_REG_RESET           (0x00000000)

/*=============================*/
struct __RF_DEM_IQCORRECT_REG
/*=============================*/
{
    volatile uint32_t BITFLD_IQCORR_BETA                       : 8;
    volatile uint32_t BITFLD_IQCORR_ALPHA                      : 8;
};
#define IQCORR_BETA                           (0x00FF)
#define IQCORR_ALPHA                          (0xFF00)



#define RF_PAD_CNT_CTRL_REG                  (0x4000204C)
#define RF_PAD_CNT_CTRL_REG_RESET            (0x00004000)

/*=============================*/
struct __RF_PAD_CNT_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_PAD_POS_LIMIT                     : 7;
    volatile uint32_t BITFLD_PAD_NEG_LIMIT                     : 7;
    volatile uint32_t BITFLD_PAD_CLEAR_COUNT                   : 1;
};
#define PAD_POS_LIMIT                         (0x007F)
#define PAD_NEG_LIMIT                         (0x3F80)
#define PAD_CLEAR_COUNT                       (0x4000)



#define RF_PAD_CNT_RESULT_REG                (0x40002050)
#define RF_PAD_CNT_RESULT_REG_RESET          (0x00000000)

/*=============================*/
struct __RF_PAD_CNT_RESULT_REG
/*=============================*/
{
    volatile uint32_t BITFLD_PAD_POS_CNT_RD                    : 8;
    volatile uint32_t BITFLD_PAD_NEG_CNT_RD                    : 8;
};
#define PAD_POS_CNT_RD                        (0x00FF)
#define PAD_NEG_CNT_RD                        (0xFF00)



#define RF_DC_OFFSET_RESULT_REG              (0x40002058)
#define RF_DC_OFFSET_RESULT_REG_RESET        (0x00000000)

/*=============================*/
struct __RF_DC_OFFSET_RESULT_REG
/*=============================*/
{
    volatile uint32_t BITFLD_DCOFFSET_I_RD                     : 9;
    volatile uint32_t BITFLD_DCOFFSET_Q_RD                     : 9;
};
#define DCOFFSET_I_RD                         (0x01FF)
#define DCOFFSET_Q_RD                         (0x3FE00)



#define RF_DC_OFFSET_FULL_RES_REG            (0x4000205C)
#define RF_DC_OFFSET_FULL_RES_REG_RESET      (0x00000000)

/*=============================*/
struct __RF_DC_OFFSET_FULL_RES_REG
/*=============================*/
{
    volatile uint32_t BITFLD_DCOFFSET_I_RD                     : 9;
    volatile uint32_t BITFLD_DCOFFSET_Q_RD                     : 9;
};
#define DCOFFSET_I_RD                         (0x01FF)
#define DCOFFSET_Q_RD                         (0x3FE00)



#define RF_DC_OFFSET_MPAR_RES0_REG           (0x40002060)
#define RF_DC_OFFSET_MPAR_RES0_REG_RESET     (0x00000000)

/*=============================*/
struct __RF_DC_OFFSET_MPAR_RES0_REG
/*=============================*/
{
    volatile uint32_t BITFLD_DCOFFSET_I_RD                     : 9;
    volatile uint32_t BITFLD_DCOFFSET_Q_RD                     : 9;
};
#define DCOFFSET_I_RD                         (0x01FF)
#define DCOFFSET_Q_RD                         (0x3FE00)



#define RF_DC_OFFSET_MPAR_RES1_REG           (0x40002064)
#define RF_DC_OFFSET_MPAR_RES1_REG_RESET     (0x00000000)

/*=============================*/
struct __RF_DC_OFFSET_MPAR_RES1_REG
/*=============================*/
{
    volatile uint32_t BITFLD_DCOFFSET_I_RD                     : 9;
    volatile uint32_t BITFLD_DCOFFSET_Q_RD                     : 9;
};
#define DCOFFSET_I_RD                         (0x01FF)
#define DCOFFSET_Q_RD                         (0x3FE00)



#define RF_DC_OFFSET_MPAR_RES2_REG           (0x40002068)
#define RF_DC_OFFSET_MPAR_RES2_REG_RESET     (0x00000000)

/*=============================*/
struct __RF_DC_OFFSET_MPAR_RES2_REG
/*=============================*/
{
    volatile uint32_t BITFLD_DCOFFSET_I_RD                     : 9;
    volatile uint32_t BITFLD_DCOFFSET_Q_RD                     : 9;
};
#define DCOFFSET_I_RD                         (0x01FF)
#define DCOFFSET_Q_RD                         (0x3FE00)



#define RF_DC_OFFSET_MPAR_RES3_REG           (0x4000206C)
#define RF_DC_OFFSET_MPAR_RES3_REG_RESET     (0x00000000)

/*=============================*/
struct __RF_DC_OFFSET_MPAR_RES3_REG
/*=============================*/
{
    volatile uint32_t BITFLD_DCOFFSET_I_RD                     : 9;
    volatile uint32_t BITFLD_DCOFFSET_Q_RD                     : 9;
};
#define DCOFFSET_I_RD                         (0x01FF)
#define DCOFFSET_Q_RD                         (0x3FE00)



#define ADPLL_ATTR_CTRL_REG                  (0x40003000)
#define ADPLL_ATTR_CTRL_REG_RESET            (0x00000003)

/*=============================*/
struct __ADPLL_ATTR_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_PWR_MODE_RX                       : 1;
    volatile uint32_t BITFLD_PWR_MODE_TX                       : 1;
};
#define PWR_MODE_RX                           (0x0001)
#define PWR_MODE_TX                           (0x0002)



#define ADPLL_CN_CTRL_REG                    (0x40003004)
#define ADPLL_CN_CTRL_REG_RESET              (0x09620100)

/*=============================*/
struct __ADPLL_CN_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_CN                                : 7;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_CS                                : 1;
    volatile uint32_t                                          : 6;
    volatile uint32_t BITFLD_SGN                               : 1;
    volatile uint32_t BITFLD_CH0                               : 13;
};
#define CN                                    (0x007F)
#define CS                                    (0x0100)
#define SGN                                   (0x8000)
#define CH0                                   (0x1FFF0000)



#define ADPLL_FIF_CTRL1_REG                  (0x40003008)
#define ADPLL_FIF_CTRL1_REG_RESET            (0x00000400)

/*=============================*/
struct __ADPLL_FIF_CTRL1_REG
/*=============================*/
{
    volatile uint32_t BITFLD_FIFRX_1M                          : 14;
};
#define FIFRX_1M                              (0x3FFF)



#define ADPLL_FIF_CTRL2_REG                  (0x4000300C)
#define ADPLL_FIF_CTRL2_REG_RESET            (0x00000000)

/*=============================*/
struct __ADPLL_FIF_CTRL2_REG
/*=============================*/
{
    volatile uint32_t BITFLD_FIFRX_OFFSET                      : 14;
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_FIFTX                             : 14;
};
#define FIFRX_OFFSET                          (0x3FFF)
#define FIFTX                                 (0x3FFF0000)



#define ADPLL_KDCO_CAL_CTRL1_REG             (0x40003010)
#define ADPLL_KDCO_CAL_CTRL1_REG_RESET       (0x00009B9B)

/*=============================*/
struct __ADPLL_KDCO_CAL_CTRL1_REG
/*=============================*/
{
    volatile uint32_t BITFLD_KDCOHFIC_1M                       : 8;
    volatile uint32_t BITFLD_KDCOLF_IN_1M                      : 8;
};
#define KDCOHFIC_1M                           (0x00FF)
#define KDCOLF_IN_1M                          (0xFF00)



#define ADPLL_KDCO_CAL_CTRL2_REG             (0x40003014)
#define ADPLL_KDCO_CAL_CTRL2_REG_RESET       (0x4C14000A)

/*=============================*/
struct __ADPLL_KDCO_CAL_CTRL2_REG
/*=============================*/
{
    volatile uint32_t BITFLD_KMOD_ALPHA_1M                     : 5;
    volatile uint32_t                                          : 1;
    volatile uint32_t                                          : 2;
    volatile uint32_t                                          : 8;
    volatile uint32_t BITFLD_KDCOCN_IC                         : 7;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_TKDCOCAL                          : 3;
    volatile uint32_t BITFLD_KDCOLFCALEN                       : 1;
    volatile uint32_t BITFLD_KDCOCALRX                         : 1;
    volatile uint32_t BITFLD_KDCOCALTX                         : 1;
    volatile uint32_t BITFLD_KDCOESTDEV                        : 2;
};
#define KMOD_ALPHA_1M                         (0x001F)
#define KDCOCN_IC                             (0x7F0000)
#define TKDCOCAL                              (0x7000000)
#define KDCOLFCALEN                           (0x8000000)
#define KDCOCALRX                             (0x10000000)
#define KDCOCALTX                             (0x20000000)
#define KDCOESTDEV                            (0xC0000000)



#define ADPLL_KDTCTDC_CAL_CTRL1_REG          (0x40003018)
#define ADPLL_KDTCTDC_CAL_CTRL1_REG_RESET    (0x8514429C)

/*=============================*/
struct __ADPLL_KDTCTDC_CAL_CTRL1_REG
/*=============================*/
{
    volatile uint32_t BITFLD_KDTC_ALPHA                        : 6;
    volatile uint32_t BITFLD_KTDC_IN                           : 9;
    volatile uint32_t BITFLD_KDTC_PIPELINE_BYPASS              : 1;
    volatile uint32_t BITFLD_KDTCCN_IC                         : 7;
    volatile uint32_t BITFLD_KDTCIC                            : 9;
};
#define KDTC_ALPHA                            (0x003F)
#define KTDC_IN                               (0x7FC0)
#define KDTC_PIPELINE_BYPASS                  (0x8000)
#define KDTCCN_IC                             (0x7F0000)
#define KDTCIC                                (0xFF800000)



#define ADPLL_KDTCTDC_CAL_CTRL2_REG          (0x4000301C)
#define ADPLL_KDTCTDC_CAL_CTRL2_REG_RESET    (0x00007F50)

/*=============================*/
struct __ADPLL_KDTCTDC_CAL_CTRL2_REG
/*=============================*/
{
    volatile uint32_t BITFLD_KDTCCALEN                         : 1;
    volatile uint32_t BITFLD_KDTCCALMOD                        : 1;
    volatile uint32_t BITFLD_KDTCCALMOD1P                      : 1;
    volatile uint32_t BITFLD_KDTCCAL_INV                       : 1;
    volatile uint32_t BITFLD_KDTCCALLG                         : 3;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_KTDCCALEN                         : 1;
    volatile uint32_t BITFLD_PHRDLY                            : 2;
    volatile uint32_t BITFLD_TKDTCCAL                          : 4;
    volatile uint32_t BITFLD_PHRDLY_EXTRA                      : 1;
};
#define KDTCCALEN                             (0x0001)
#define KDTCCALMOD                            (0x0002)
#define KDTCCALMOD1P                          (0x0004)
#define KDTCCAL_INV                           (0x0008)
#define KDTCCALLG                             (0x0070)
#define KTDCCALEN                             (0x0100)
#define PHRDLY                                (0x0600)
#define TKDTCCAL                              (0x7800)
#define PHRDLY_EXTRA                          (0x8000)



#define ADPLL_DCOAMP_CAL_CTRL_REG            (0x40003020)
#define ADPLL_DCOAMP_CAL_CTRL_REG_RESET      (0x77770011)

/*=============================*/
struct __ADPLL_DCOAMP_CAL_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_KCOARSE                           : 3;
    volatile uint32_t BITFLD_KMEDIUM                           : 3;
    volatile uint32_t BITFLD_AMPCALEN                          : 1;
    volatile uint32_t BITFLD_DCOAMPTM                          : 1;
    volatile uint32_t                                          : 8;
    volatile uint32_t BITFLD_DCOAMPIC_HP_RX                    : 4;
    volatile uint32_t BITFLD_DCOAMPIC_HP_TX                    : 4;
    volatile uint32_t BITFLD_DCOAMPIC_LP_RX                    : 4;
    volatile uint32_t BITFLD_DCOAMPIC_LP_TX                    : 4;
};
#define KCOARSE                               (0x0007)
#define KMEDIUM                               (0x0038)
#define AMPCALEN                              (0x0040)
#define DCOAMPTM                              (0x0080)
#define DCOAMPIC_HP_RX                        (0xF0000)
#define DCOAMPIC_HP_TX                        (0xF00000)
#define DCOAMPIC_LP_RX                        (0xF000000)
#define DCOAMPIC_LP_TX                        (0xF0000000)



#define ADPLL_TXMOD_CTRL_REG                 (0x40003024)
#define ADPLL_TXMOD_CTRL_REG_RESET           (0x00000000)

/*=============================*/
struct __ADPLL_TXMOD_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_BT_SEL                            : 1;
    volatile uint32_t BITFLD_TX_DATA_INV                       : 1;
    volatile uint32_t BITFLD_MOD_INDEX                         : 2;
    volatile uint32_t BITFLD_EO_PACKET_DIS                     : 1;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_TX_MODE                           : 2;
    volatile uint32_t BITFLD_INV_CKMODEXT                      : 1;
};
#define BT_SEL                                (0x0001)
#define TX_DATA_INV                           (0x0002)
#define MOD_INDEX                             (0x000C)
#define EO_PACKET_DIS                         (0x0010)
#define TX_MODE                               (0x00C0)
#define INV_CKMODEXT                          (0x0100)



#define ADPLL_SDMOD_CTRL_REG                 (0x40003028)
#define ADPLL_SDMOD_CTRL_REG_RESET           (0x00000039)

/*=============================*/
struct __ADPLL_SDMOD_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_SDMMODERX                         : 3;
    volatile uint32_t BITFLD_SDMMODETX                         : 3;
};
#define SDMMODERX                             (0x0007)
#define SDMMODETX                             (0x0038)



#define ADPLL_LF_CTRL1_REG                   (0x4000302C)
#define ADPLL_LF_CTRL1_REG_RESET             (0x0000818C)

/*=============================*/
struct __ADPLL_LF_CTRL1_REG
/*=============================*/
{
    volatile uint32_t BITFLD_FINETAU                           : 5;
    volatile uint32_t BITFLD_FINEK                             : 5;
    volatile uint32_t BITFLD_FINEKZ                            : 6;
};
#define FINETAU                               (0x001F)
#define FINEK                                 (0x03E0)
#define FINEKZ                                (0xFC00)



#define ADPLL_LF_CTRL2_REG                   (0x40003030)
#define ADPLL_LF_CTRL2_REG_RESET             (0x1CA2879E)

/*=============================*/
struct __ADPLL_LF_CTRL2_REG
/*=============================*/
{
    volatile uint32_t BITFLD_MODTAU_TUNE                       : 6;
    volatile uint32_t BITFLD_MODK_TUNE                         : 6;
    volatile uint32_t BITFLD_MODTAU                            : 6;
    volatile uint32_t BITFLD_MODK                              : 6;
    volatile uint32_t BITFLD_MODKZ                             : 6;
    volatile uint32_t BITFLD_RST_TAU_EN                        : 1;
};
#define MODTAU_TUNE                           (0x003F)
#define MODK_TUNE                             (0x0FC0)
#define MODTAU                                (0x3F000)
#define MODK                                  (0xFC0000)
#define MODKZ                                 (0x3F000000)
#define RST_TAU_EN                            (0x40000000)



#define ADPLL_ANA_CTRL_REG                   (0x40003034)
#define ADPLL_ANA_CTRL_REG_RESET             (0x0215807B)

/*=============================*/
struct __ADPLL_ANA_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_TDC_DTCIN_EN                      : 1;
    volatile uint32_t BITFLD_TDC_CKVIN_EN                      : 1;
    volatile uint32_t BITFLD_TDC_INV                           : 1;
    volatile uint32_t BITFLD_INV_CKTDC                         : 1;
    volatile uint32_t BITFLD_INV_CKPHV                         : 1;
    volatile uint32_t BITFLD_INV_CKDCOMOD                      : 1;
    volatile uint32_t BITFLD_EN_CKDCOMOD                       : 1;
    volatile uint32_t BITFLD_TGLDETEN                          : 1;
    volatile uint32_t BITFLD_DTCOFFSET                         : 7;
    volatile uint32_t BITFLD_DTC_EN                            : 1;
    volatile uint32_t BITFLD_TDC_OFFSET                        : 6;
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_VPASETTLE                         : 2;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_DTC_LDO_DMY                       : 2;
};
#define TDC_DTCIN_EN                          (0x0001)
#define TDC_CKVIN_EN                          (0x0002)
#define TDC_INV                               (0x0004)
#define INV_CKTDC                             (0x0008)
#define INV_CKPHV                             (0x0010)
#define INV_CKDCOMOD                          (0x0020)
#define EN_CKDCOMOD                           (0x0040)
#define TGLDETEN                              (0x0080)
#define DTCOFFSET                             (0x7F00)
#define DTC_EN                                (0x8000)
#define TDC_OFFSET                            (0x3F0000)
#define VPASETTLE                             (0x3000000)
#define DTC_LDO_DMY                           (0x18000000)



#define ADPLL_DIV_CTRL_REG                   (0x40003038)
#define ADPLL_DIV_CTRL_REG_RESET             (0x0198FF03)

/*=============================*/
struct __ADPLL_DIV_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_FBDIV_EN                          : 1;
    volatile uint32_t BITFLD_RXDIV_FB_EN_RX                    : 1;
    volatile uint32_t BITFLD_RXDIV_FB_EN_TX                    : 1;
    volatile uint32_t                                          : 5;
    volatile uint32_t BITFLD_RXDIV_TRIM                        : 9;
    volatile uint32_t BITFLD_TXDIV_TRIM                        : 9;
};
#define FBDIV_EN                              (0x0001)
#define RXDIV_FB_EN_RX                        (0x0002)
#define RXDIV_FB_EN_TX                        (0x0004)
#define RXDIV_TRIM                            (0x1FF00)
#define TXDIV_TRIM                            (0x3FE0000)



#define ADPLL_INIT_CTRL_REG                  (0x4000303C)
#define ADPLL_INIT_CTRL_REG_RESET            (0x00000005)

/*=============================*/
struct __ADPLL_INIT_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_DCOCOARSEIC                       : 4;
    volatile uint32_t BITFLD_DCOMEDIUMIC                       : 3;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_DCOFINEIC                         : 6;
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_DCOMODIC                          : 13;
};
#define DCOCOARSEIC                           (0x000F)
#define DCOMEDIUMIC                           (0x0070)
#define DCOFINEIC                             (0x3F00)
#define DCOMODIC                              (0x1FFF0000)



#define ADPLL_FSM_CTRL_REG                   (0x40003040)
#define ADPLL_FSM_CTRL_REG_RESET             (0x08F8AE84)

/*=============================*/
struct __ADPLL_FSM_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_TCOARSE                           : 4;
    volatile uint32_t BITFLD_TMEDIUM                           : 4;
    volatile uint32_t BITFLD_TFINE                             : 4;
    volatile uint32_t BITFLD_TMOD                              : 4;
    volatile uint32_t BITFLD_TPASETTLE                         : 4;
    volatile uint32_t BITFLD_TSETTLE                           : 4;
    volatile uint32_t BITFLD_TVPASETTLE                        : 6;
};
#define TCOARSE                               (0x000F)
#define TMEDIUM                               (0x00F0)
#define TFINE                                 (0x0F00)
#define TMOD                                  (0xF000)
#define TPASETTLE                             (0xF0000)
#define TSETTLE                               (0xF00000)
#define TVPASETTLE                            (0x3F000000)



#define ADPLL_MON_CTRL_REG                   (0x40003044)
#define ADPLL_MON_CTRL_REG_RESET             (0x00FC0F83)

/*=============================*/
struct __ADPLL_MON_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_TFREQMEAS                         : 5;
    volatile uint32_t BITFLD_TMREN                             : 1;
    volatile uint32_t BITFLD_ENRFMEAS                          : 1;
    volatile uint32_t BITFLD_RFMEAS_MODE                       : 1;
    volatile uint32_t BITFLD_HOLD_STATE                        : 4;
    volatile uint32_t                                          : 4;
    volatile uint32_t BITFLD_QUALMONMOD                        : 2;
    volatile uint32_t BITFLD_QUALMONWND                        : 6;
    volatile uint32_t BITFLD_QUALMONTRHLD                      : 6;
    volatile uint32_t BITFLD_QUALMONFRCEN                      : 1;
};
#define TFREQMEAS                             (0x001F)
#define TMREN                                 (0x0020)
#define ENRFMEAS                              (0x0040)
#define RFMEAS_MODE                           (0x0080)
#define HOLD_STATE                            (0x0F00)
#define QUALMONMOD                            (0x30000)
#define QUALMONWND                            (0xFC0000)
#define QUALMONTRHLD                          (0x3F000000)
#define QUALMONFRCEN                          (0x40000000)



#define ADPLL_MISC_CTRL_REG                  (0x40003048)
#define ADPLL_MISC_CTRL_REG_RESET            (0x000000DA)

/*=============================*/
struct __ADPLL_MISC_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_DLYFCWDT                          : 2;
    volatile uint32_t BITFLD_RESDLY                            : 2;
    volatile uint32_t BITFLD_MODDLY                            : 2;
    volatile uint32_t BITFLD_ENRESIDUE                         : 1;
    volatile uint32_t BITFLD_ENFCWMOD                          : 1;
    volatile uint32_t BITFLD_PHR_FRAC_PRESET_VAL               : 16;
};
#define DLYFCWDT                              (0x0003)
#define RESDLY                                (0x000C)
#define MODDLY                                (0x0030)
#define ENRESIDUE                             (0x0040)
#define ENFCWMOD                              (0x0080)
#define PHR_FRAC_PRESET_VAL                   (0xFFFF00)



#define ADPLL_OVERRULE_CTRL1_REG             (0x40003050)
#define ADPLL_OVERRULE_CTRL1_REG_RESET       (0x00000000)

/*=============================*/
struct __ADPLL_OVERRULE_CTRL1_REG
/*=============================*/
{
    volatile uint32_t BITFLD_OVR_ACTIVE_SEL                    : 1;
    volatile uint32_t BITFLD_OVR_ACTIVE_WR                     : 1;
    volatile uint32_t BITFLD_OVR_RXBIT_SEL                     : 1;
    volatile uint32_t BITFLD_OVR_RXBIT_WR                      : 1;
    volatile uint32_t BITFLD_OVR_ENPAIN_SEL                    : 1;
    volatile uint32_t BITFLD_OVR_ENPAIN_WR                     : 1;
    volatile uint32_t BITFLD_OVR_SRESETN_SEL                   : 1;
    volatile uint32_t BITFLD_OVR_SRESETN_WR                    : 1;
    volatile uint32_t BITFLD_OVR_VPAEN_SEL                     : 1;
    volatile uint32_t BITFLD_OVR_VPAEN_WR                      : 1;
    volatile uint32_t BITFLD_OVR_RDYFORDIV_SEL                 : 1;
    volatile uint32_t BITFLD_OVR_RDYFORDIV_WR                  : 1;
    volatile uint32_t BITFLD_OVR_DCOAMPHOLD_SEL                : 1;
    volatile uint32_t BITFLD_OVR_DCOAMPHOLD_WR                 : 1;
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_OVR_DCOAMP_SEL                    : 1;
    volatile uint32_t BITFLD_OVR_DCOAMP_WR                     : 4;
    volatile uint32_t                                          : 3;
    volatile uint32_t BITFLD_OVR_DTC_OH_SEL                    : 1;
    volatile uint32_t BITFLD_OVR_DTC_OH_WR                     : 7;
};
#define OVR_ACTIVE_SEL                        (0x0001)
#define OVR_ACTIVE_WR                         (0x0002)
#define OVR_RXBIT_SEL                         (0x0004)
#define OVR_RXBIT_WR                          (0x0008)
#define OVR_ENPAIN_SEL                        (0x0010)
#define OVR_ENPAIN_WR                         (0x0020)
#define OVR_SRESETN_SEL                       (0x0040)
#define OVR_SRESETN_WR                        (0x0080)
#define OVR_VPAEN_SEL                         (0x0100)
#define OVR_VPAEN_WR                          (0x0200)
#define OVR_RDYFORDIV_SEL                     (0x0400)
#define OVR_RDYFORDIV_WR                      (0x0800)
#define OVR_DCOAMPHOLD_SEL                    (0x1000)
#define OVR_DCOAMPHOLD_WR                     (0x2000)
#define OVR_DCOAMP_SEL                        (0x10000)
#define OVR_DCOAMP_WR                         (0x1E0000)
#define OVR_DTC_OH_SEL                        (0x1000000)
#define OVR_DTC_OH_WR                         (0xFE000000)



#define ADPLL_OVERRULE_CTRL2_REG             (0x40003054)
#define ADPLL_OVERRULE_CTRL2_REG_RESET       (0x00000000)

/*=============================*/
struct __ADPLL_OVERRULE_CTRL2_REG
/*=============================*/
{
    volatile uint32_t BITFLD_OVR_DCOCOARSE_SEL                 : 1;
    volatile uint32_t BITFLD_OVR_DCOCOARSE_WR                  : 4;
    volatile uint32_t                                          : 3;
    volatile uint32_t BITFLD_OVR_DCOMEDIUM_SEL                 : 1;
    volatile uint32_t BITFLD_OVR_DCOMEDIUM_WR                  : 3;
    volatile uint32_t                                          : 4;
    volatile uint32_t BITFLD_OVR_DCOFINE_SEL                   : 1;
    volatile uint32_t BITFLD_OVR_DCOFINE_WR                    : 6;
    volatile uint32_t BITFLD_OVR_DCOMOD_SEL                    : 1;
    volatile uint32_t BITFLD_OVR_DCOMOD_WR                     : 8;
};
#define OVR_DCOCOARSE_SEL                     (0x0001)
#define OVR_DCOCOARSE_WR                      (0x001E)
#define OVR_DCOMEDIUM_SEL                     (0x0100)
#define OVR_DCOMEDIUM_WR                      (0x0E00)
#define OVR_DCOFINE_SEL                       (0x10000)
#define OVR_DCOFINE_WR                        (0x7E0000)
#define OVR_DCOMOD_SEL                        (0x800000)
#define OVR_DCOMOD_WR                         (0xFF000000)



#define ADPLL_OVERRULE_CTRL3_REG             (0x40003058)
#define ADPLL_OVERRULE_CTRL3_REG_RESET       (0x00000000)

/*=============================*/
struct __ADPLL_OVERRULE_CTRL3_REG
/*=============================*/
{
    volatile uint32_t BITFLD_OVR_RXDIV_EN_SEL                  : 1;
    volatile uint32_t BITFLD_OVR_RXDIV_EN_WR                   : 1;
    volatile uint32_t BITFLD_OVR_TXDIV_EN_SEL                  : 1;
    volatile uint32_t BITFLD_OVR_TXDIV_EN_WR                   : 1;
    volatile uint32_t BITFLD_OVR_FBDIV_EN_SEL                  : 1;
    volatile uint32_t BITFLD_OVR_FBDIV_EN_WR                   : 1;
    volatile uint32_t BITFLD_OVR_RXDIV_FB_EN_SEL               : 1;
    volatile uint32_t BITFLD_OVR_RXDIV_FB_EN_WR                : 1;
};
#define OVR_RXDIV_EN_SEL                      (0x0001)
#define OVR_RXDIV_EN_WR                       (0x0002)
#define OVR_TXDIV_EN_SEL                      (0x0004)
#define OVR_TXDIV_EN_WR                       (0x0008)
#define OVR_FBDIV_EN_SEL                      (0x0010)
#define OVR_FBDIV_EN_WR                       (0x0020)
#define OVR_RXDIV_FB_EN_SEL                   (0x0040)
#define OVR_RXDIV_FB_EN_WR                    (0x0080)



#define ADPLL_RFPT_CTRL_REG                  (0x4000305C)
#define ADPLL_RFPT_CTRL_REG_RESET            (0x00000000)

/*=============================*/
struct __ADPLL_RFPT_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RFPT_MUX                          : 4;
    volatile uint32_t BITFLD_INV_CKRFPT                        : 1;
    volatile uint32_t BITFLD_RFPT_RATE                         : 1;
    volatile uint32_t                                          : 1;
};
#define RFPT_MUX                              (0x000F)
#define INV_CKRFPT                            (0x0010)
#define RFPT_RATE                             (0x0020)



#define ADPLL_ANATST_CTRL_REG                (0x40003060)
#define ADPLL_ANATST_CTRL_REG_RESET          (0x00000000)

/*=============================*/
struct __ADPLL_ANATST_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ANATSTEN                          : 16;
    volatile uint32_t BITFLD_ANATSTSPARE                       : 16;
};
#define ANATSTEN                              (0xFFFF)
#define ANATSTSPARE                           (0xFFFF0000)



#define ADPLL_ACC_CTRL_REG                   (0x40003064)
#define ADPLL_ACC_CTRL_REG_RESET             (0x8BF40BF4)

/*=============================*/
struct __ADPLL_ACC_CTRL_REG
/*=============================*/
{
    volatile uint32_t BITFLD_CLIP_MOD_TUNE_0_RX                : 13;
    volatile uint32_t                                          : 3;
    volatile uint32_t BITFLD_CLIP_MOD_TUNE_0_TX                : 13;
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_EN_CMF_AVG                        : 1;
};
#define CLIP_MOD_TUNE_0_RX                    (0x1FFF)
#define CLIP_MOD_TUNE_0_TX                    (0x1FFF0000)
#define EN_CMF_AVG                            (0x80000000)



#define ADPLL_FREQMEAS_RD_REG                (0x4000307C)
#define ADPLL_FREQMEAS_RD_REG_RESET          (0x21000000)

/*=============================*/
struct __ADPLL_FREQMEAS_RD_REG
/*=============================*/
{
    volatile uint32_t BITFLD_FREQDIFF                          : 23;
    volatile uint32_t BITFLD_PHVSA1                            : 1;
    volatile uint32_t BITFLD_PHVSA0                            : 1;
    volatile uint32_t BITFLD_TDCBUB                            : 1;
    volatile uint32_t BITFLD_QUALMONDET                        : 1;
    volatile uint32_t                                          : 1;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_MEASDONE_OUT                      : 1;
};
#define FREQDIFF                              (0x7FFFFF)
#define PHVSA1                                (0x800000)
#define PHVSA0                                (0x1000000)
#define TDCBUB                                (0x2000000)
#define QUALMONDET                            (0x4000000)
#define MEASDONE_OUT                          (0x20000000)



#define ADPLL_DCO_RD_REG                     (0x40003080)
#define ADPLL_DCO_RD_REG_RESET               (0x1C000007)

/*=============================*/
struct __ADPLL_DCO_RD_REG
/*=============================*/
{
    volatile uint32_t BITFLD_DCOCOARSE                         : 4;
    volatile uint32_t BITFLD_DCOMEDIUM                         : 3;
    volatile uint32_t BITFLD_DCOFINE                           : 6;
    volatile uint32_t BITFLD_DCOMOD                            : 13;
    volatile uint32_t BITFLD_DCOAMP                            : 4;
};
#define DCOCOARSE                             (0x000F)
#define DCOMEDIUM                             (0x0070)
#define DCOFINE                               (0x1F80)
#define DCOMOD                                (0x3FFE000)
#define DCOAMP                                (0x3C000000)



#define ADPLL_KDCO_RD_REG                    (0x40003084)
#define ADPLL_KDCO_RD_REG_RESET              (0x00000000)

/*=============================*/
struct __ADPLL_KDCO_RD_REG
/*=============================*/
{
    volatile uint32_t BITFLD_KDCO_HF_INT                       : 8;
    volatile uint32_t BITFLD_KDCO_HF_OUT                       : 8;
    volatile uint32_t BITFLD_KDCOCN                            : 7;
    volatile uint32_t BITFLD_CAL_KDCOCAL                       : 1;
};
#define KDCO_HF_INT                           (0x00FF)
#define KDCO_HF_OUT                           (0xFF00)
#define KDCOCN                                (0x7F0000)
#define CAL_KDCOCAL                           (0x800000)



#define ADPLL_KDTC_RD_REG                    (0x40003088)
#define ADPLL_KDTC_RD_REG_RESET              (0x00000000)

/*=============================*/
struct __ADPLL_KDTC_RD_REG
/*=============================*/
{
    volatile uint32_t BITFLD_KDTC_OUT                          : 9;
    volatile uint32_t BITFLD_KDTCCN                            : 7;
    volatile uint32_t BITFLD_KDTC_ALPHA_COMP                   : 9;
    volatile uint32_t BITFLD_CAL_KDTCCAL                       : 1;
};
#define KDTC_OUT                              (0x01FF)
#define KDTCCN                                (0xFE00)
#define KDTC_ALPHA_COMP                       (0x1FF0000)
#define CAL_KDTCCAL                           (0x2000000)



#define ADPLL_TUNESTATE_RD_REG               (0x4000308C) /*  */
#define ADPLL_TUNESTATE_RD_REG_RESET         (0x00000000)

/*=============================*/
struct __ADPLL_TUNESTATE_RD_REG
/*=============================*/
{
    volatile uint32_t BITFLD_TUNE_STATE                        : 4;
    volatile uint32_t BITFLD_TMRVAL                            : 10;
};
#define TUNE_STATE                            (0x000F)
#define TMRVAL                                (0x3FF0)



#define ADPLL_PLLFCWDT_RD_REG                (0x40003090)
#define ADPLL_PLLFCWDT_RD_REG_RESET          (0x00258800)

/*=============================*/
struct __ADPLL_PLLFCWDT_RD_REG
/*=============================*/
{
    volatile uint32_t BITFLD_PLLFCWDT                          : 23;
};
#define PLLFCWDT                              (0x7FFFFF)



#define ADPLL_ANATST_RD_REG                  (0x40003094)
#define ADPLL_ANATST_RD_REG_RESET            (0x00000000)

/*=============================*/
struct __ADPLL_ANATST_RD_REG
/*=============================*/
{
    volatile uint32_t BITFLD_ANATSTSPARE_IN                    : 16;
};
#define ANATSTSPARE_IN                        (0xFFFF)



#define PATCH_VALID_REG                      (0x40080000)
#define PATCH_VALID_REG_RESET                (0x00000000)

/*=============================*/
struct __PATCH_VALID_REG
/*=============================*/
{
    volatile uint32_t BITFLD_PATCH_VALID                       : 22;
};
#define PATCH_VALID                           (0x3FFFFF)



#define PATCH_ADDR0_REG                      (0x40080020)
#define PATCH_ADDR0_REG_RESET                (0x07F00000)

/*=============================*/
struct __PATCH_ADDR0_REG
/*=============================*/
{
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_C                      : 17;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_19                     : 1;
};
#define PATCH_ADDR_C                          (0x3FFFE)
#define PATCH_ADDR_19                         (0x80000)



#define PATCH_ADDR1_REG                      (0x40080028)
#define PATCH_ADDR1_REG_RESET                (0x07F00000)

/*=============================*/
struct __PATCH_ADDR1_REG
/*=============================*/
{
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_C                      : 17;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_19                     : 1;
};
#define PATCH_ADDR_C                          (0x3FFFE)
#define PATCH_ADDR_19                         (0x80000)



#define PATCH_ADDR2_REG                      (0x40080030)
#define PATCH_ADDR2_REG_RESET                (0x07F00000)

/*=============================*/
struct __PATCH_ADDR2_REG
/*=============================*/
{
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_C                      : 17;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_19                     : 1;
};
#define PATCH_ADDR_C                          (0x3FFFE)
#define PATCH_ADDR_19                         (0x80000)



#define PATCH_ADDR3_REG                      (0x40080038)
#define PATCH_ADDR3_REG_RESET                (0x07F00000)

/*=============================*/
struct __PATCH_ADDR3_REG
/*=============================*/
{
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_C                      : 17;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_19                     : 1;
};
#define PATCH_ADDR_C                          (0x3FFFE)
#define PATCH_ADDR_19                         (0x80000)



#define PATCH_ADDR4_REG                      (0x40080040)
#define PATCH_ADDR4_REG_RESET                (0x07F00000)

/*=============================*/
struct __PATCH_ADDR4_REG
/*=============================*/
{
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_C                      : 17;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_19                     : 1;
};
#define PATCH_ADDR_C                          (0x3FFFE)
#define PATCH_ADDR_19                         (0x80000)



#define PATCH_ADDR5_REG                      (0x40080048)
#define PATCH_ADDR5_REG_RESET                (0x07F00000)

/*=============================*/
struct __PATCH_ADDR5_REG
/*=============================*/
{
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_C                      : 17;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_19                     : 1;
};
#define PATCH_ADDR_C                          (0x3FFFE)
#define PATCH_ADDR_19                         (0x80000)



#define PATCH_ADDR6_REG                      (0x40080050)
#define PATCH_ADDR6_REG_RESET                (0x07F00000)

/*=============================*/
struct __PATCH_ADDR6_REG
/*=============================*/
{
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_C                      : 17;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_19                     : 1;
};
#define PATCH_ADDR_C                          (0x3FFFE)
#define PATCH_ADDR_19                         (0x80000)



#define PATCH_ADDR7_REG                      (0x40080058)
#define PATCH_ADDR7_REG_RESET                (0x07F00000)

/*=============================*/
struct __PATCH_ADDR7_REG
/*=============================*/
{
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_C                      : 17;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_19                     : 1;
};
#define PATCH_ADDR_C                          (0x3FFFE)
#define PATCH_ADDR_19                         (0x80000)



#define PATCH_ADDR8_REG                      (0x40080060)
#define PATCH_ADDR8_REG_RESET                (0x07F00000)

/*=============================*/
struct __PATCH_ADDR8_REG
/*=============================*/
{
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_C                      : 17;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_19                     : 1;
};
#define PATCH_ADDR_C                          (0x3FFFE)
#define PATCH_ADDR_19                         (0x80000)



#define PATCH_ADDR9_REG                      (0x40080068)
#define PATCH_ADDR9_REG_RESET                (0x07F00000)

/*=============================*/
struct __PATCH_ADDR9_REG
/*=============================*/
{
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_C                      : 17;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_19                     : 1;
};
#define PATCH_ADDR_C                          (0x3FFFE)
#define PATCH_ADDR_19                         (0x80000)



#define PATCH_ADDR10_REG                     (0x40080070)
#define PATCH_ADDR10_REG_RESET               (0x07F00000)

/*=============================*/
struct __PATCH_ADDR10_REG
/*=============================*/
{
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_C                      : 17;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_19                     : 1;
};
#define PATCH_ADDR_C                          (0x3FFFE)
#define PATCH_ADDR_19                         (0x80000)



#define PATCH_ADDR11_REG                     (0x40080078)
#define PATCH_ADDR11_REG_RESET               (0x07F00000)

/*=============================*/
struct __PATCH_ADDR11_REG
/*=============================*/
{
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_C                      : 17;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_19                     : 1;
};
#define PATCH_ADDR_C                          (0x3FFFE)
#define PATCH_ADDR_19                         (0x80000)



#define PATCH_ADDR12_REG                     (0x40080080)
#define PATCH_ADDR12_REG_RESET               (0x07F00000)

/*=============================*/
struct __PATCH_ADDR12_REG
/*=============================*/
{
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_C                      : 17;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_19                     : 1;
};
#define PATCH_ADDR_C                          (0x3FFFE)
#define PATCH_ADDR_19                         (0x80000)



#define PATCH_ADDR13_REG                     (0x40080088)
#define PATCH_ADDR13_REG_RESET               (0x07F00000)

/*=============================*/
struct __PATCH_ADDR13_REG
/*=============================*/
{
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_C                      : 17;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_19                     : 1;
};
#define PATCH_ADDR_C                          (0x3FFFE)
#define PATCH_ADDR_19                         (0x80000)



#define PATCH_ADDR14_REG                     (0x40080090)
#define PATCH_ADDR14_REG_RESET               (0x07F00000)

/*=============================*/
struct __PATCH_ADDR14_REG
/*=============================*/
{
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_C                      : 17;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_19                     : 1;
};
#define PATCH_ADDR_C                          (0x3FFFE)
#define PATCH_ADDR_19                         (0x80000)



#define PATCH_ADDR15_REG                     (0x40080098)
#define PATCH_ADDR15_REG_RESET               (0x07F00000)

/*=============================*/
struct __PATCH_ADDR15_REG
/*=============================*/
{
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_C                      : 17;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_19                     : 1;
};
#define PATCH_ADDR_C                          (0x3FFFE)
#define PATCH_ADDR_19                         (0x80000)



#define PATCH_ADDR16_REG                     (0x400800A0)
#define PATCH_ADDR16_REG_RESET               (0x07F00000)

/*=============================*/
struct __PATCH_ADDR16_REG
/*=============================*/
{
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_C                      : 17;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_19                     : 1;
};
#define PATCH_ADDR_C                          (0x3FFFE)
#define PATCH_ADDR_19                         (0x80000)



#define PATCH_ADDR17_REG                     (0x400800A8)
#define PATCH_ADDR17_REG_RESET               (0x07F00000)

/*=============================*/
struct __PATCH_ADDR17_REG
/*=============================*/
{
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_C                      : 17;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_19                     : 1;
};
#define PATCH_ADDR_C                          (0x3FFFE)
#define PATCH_ADDR_19                         (0x80000)



#define PATCH_ADDR18_REG                     (0x400800B0)
#define PATCH_ADDR18_REG_RESET               (0x07F00000)

/*=============================*/
struct __PATCH_ADDR18_REG
/*=============================*/
{
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_C                      : 17;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_19                     : 1;
};
#define PATCH_ADDR_C                          (0x3FFFE)
#define PATCH_ADDR_19                         (0x80000)



#define PATCH_ADDR19_REG                     (0x400800B8)
#define PATCH_ADDR19_REG_RESET               (0x07F00000)

/*=============================*/
struct __PATCH_ADDR19_REG
/*=============================*/
{
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_C                      : 17;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_19                     : 1;
};
#define PATCH_ADDR_C                          (0x3FFFE)
#define PATCH_ADDR_19                         (0x80000)



#define PATCH_ADDR20_REG                     (0x400800C0)
#define PATCH_ADDR20_REG_RESET               (0x07F00000)

/*=============================*/
struct __PATCH_ADDR20_REG
/*=============================*/
{
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_PATCH_ADDR_D                      : 16;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_19                     : 1;
};
#define PATCH_ADDR_D                          (0x3FFFC)
#define PATCH_ADDR_19                         (0x80000)



#define PATCH_DATA20_REG                     (0x400800C4)
#define PATCH_DATA20_REG_RESET               (0x00000000)

/*=============================*/
struct __PATCH_DATA20_REG
/*=============================*/
{
    volatile uint32_t BITFLD_PATCH_DATA                        : 32;
};
#define PATCH_DATA                            (0xFFFFFFFF)



#define PATCH_ADDR21_REG                     (0x400800C8)
#define PATCH_ADDR21_REG_RESET               (0x07F00000)

/*=============================*/
struct __PATCH_ADDR21_REG
/*=============================*/
{
    volatile uint32_t                                          : 2;
    volatile uint32_t BITFLD_PATCH_ADDR_D                      : 16;
    volatile uint32_t                                          : 1;
    volatile uint32_t BITFLD_PATCH_ADDR_19                     : 1;
};
#define PATCH_ADDR_D                          (0x3FFFC)
#define PATCH_ADDR_19                         (0x80000)



#define PATCH_DATA21_REG                     (0x400800CC)
#define PATCH_DATA21_REG_RESET               (0x00000000)

/*=============================*/
struct __PATCH_DATA21_REG
/*=============================*/
{
    volatile uint32_t BITFLD_PATCH_DATA                        : 32;
};
#define PATCH_DATA                            (0xFFFFFFFF)



#define CLK_XTAL32K_REG                      (0x50000022) /* 32 kHz XTAL oscillator register */
#define CLK_XTAL32K_REG_RESET                (0x0000002E)

/*=============================*/
struct __CLK_XTAL32K_REG
/*=============================*/
{
    volatile uint16_t BITFLD_XTAL32K_ENABLE                    : 1;
    volatile uint16_t BITFLD_XTAL32K_RBIAS                     : 2;
    volatile uint16_t BITFLD_XTAL32K_CUR                       : 4;
    volatile uint16_t BITFLD_XTAL32K_DISABLE_AMPREG            : 1;
    volatile uint16_t BITFLD_XTAL32K_XTAL1_BIAS_DISABLE        : 1;
};
#define XTAL32K_ENABLE                        (0x0001)
#define XTAL32K_RBIAS                         (0x0006)
#define XTAL32K_CUR                           (0x0078)
#define XTAL32K_DISABLE_AMPREG                (0x0080)
#define XTAL32K_XTAL1_BIAS_DISABLE            (0x0100)



#define ANA_STATUS_REG                       (0x5000002A) /* Status bit of analog (power management) circuits */
#define ANA_STATUS_REG_RESET                 (0x00000000)

/*=============================*/
struct __ANA_STATUS_REG
/*=============================*/
{
    volatile uint16_t BITFLD_LDO_CORE_OK                       : 1;
    volatile uint16_t BITFLD_LDO_LOW_OK                        : 1;
    volatile uint16_t BITFLD_DCDC_OK                           : 1;
    volatile uint16_t BITFLD_COMP_VBAT_HIGH_OK                 : 1;
    volatile uint16_t BITFLD_COMP_VBAT_HIGH_NOK                : 1;
    volatile uint16_t BITFLD_BANDGAP_OK                        : 1;
    volatile uint16_t BITFLD_POR_VBAT_LOW                      : 1;
    volatile uint16_t BITFLD_POR_VBAT_HIGH                     : 1;
    volatile uint16_t BITFLD_BOOST_SELECTED                    : 1;
    volatile uint16_t BITFLD_LDO_XTAL_OK                       : 1;
    volatile uint16_t BITFLD_LDO_GPADC_OK                      : 1;
    volatile uint16_t BITFLD_FORCE_RUNNING                     : 1;
    volatile uint16_t BITFLD_CLKLESS_WAKEUP_STAT               : 1;
};
#define LDO_CORE_OK                           (0x0001)
#define LDO_LOW_OK                            (0x0002)
#define DCDC_OK                               (0x0004)
#define COMP_VBAT_HIGH_OK                     (0x0008)
#define COMP_VBAT_HIGH_NOK                    (0x0010)
#define BANDGAP_OK                            (0x0020)
#define POR_VBAT_LOW                          (0x0040)
#define POR_VBAT_HIGH                         (0x0080)
#define BOOST_SELECTED                        (0x0100)
#define LDO_XTAL_OK                           (0x0200)
#define LDO_GPADC_OK                          (0x0400)
#define FORCE_RUNNING                         (0x0800)
#define CLKLESS_WAKEUP_STAT                   (0x1000)



#define XTALRDY_STAT_REG                     (0x50000036)
#define XTALRDY_STAT_REG_RESET               (0x00000000)

/*=============================*/
struct __XTALRDY_STAT_REG
/*=============================*/
{
    volatile uint16_t BITFLD_XTALRDY_STAT                      : 8;
};
#define XTALRDY_STAT                          (0x00FF)



#define XTAL32M_CTRL0_REG                    (0x50000038) /* Control bits for XTAL32M */
#define XTAL32M_CTRL0_REG_RESET              (0x00000015)

/*=============================*/
struct __XTAL32M_CTRL0_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DCBLOCK_ENABLE                    : 1;
    volatile uint16_t BITFLD_CORE_AMPL_REG_NULLBIAS            : 1;
    volatile uint16_t BITFLD_CORE_CUR_SET                      : 3;
    volatile uint16_t BITFLD_CORE_AMPL_TRIM                    : 3;
    volatile uint16_t BITFLD_XTAL32M_SPARE                     : 2;
};
#define DCBLOCK_ENABLE                        (0x0001)
#define CORE_AMPL_REG_NULLBIAS                (0x0002)
#define CORE_CUR_SET                          (0x001C)
#define CORE_AMPL_TRIM                        (0x00E0)
#define XTAL32M_SPARE                         (0x0300)



#define POWER_LEVEL_REG                      (0x50000054) /* Power management level and trim settings */
#define POWER_LEVEL_REG_RESET                (0x00001A3E)

/*=============================*/
struct __POWER_LEVEL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_LDO_CORE_LEVEL                    : 1;
    volatile uint16_t BITFLD_LDO_LOW_TRIM                      : 3;
    volatile uint16_t BITFLD_LDO_XTAL_TRIM                     : 3;
    volatile uint16_t BITFLD_LDO_CORE_RET_CUR_TRIM             : 2;
    volatile uint16_t BITFLD_DCDC_LEVEL                        : 2;
    volatile uint16_t BITFLD_DCDC_TRIM                         : 3;
};
#define LDO_CORE_LEVEL                        (0x0001)
#define LDO_LOW_TRIM                          (0x000E)
#define LDO_XTAL_TRIM                         (0x0070)
#define LDO_CORE_RET_CUR_TRIM                 (0x0180)
#define DCDC_LEVEL                            (0x0600)
#define DCDC_TRIM                             (0x3800)



#define DCDC_TEST1_REG                       (0x50000082)
#define DCDC_TEST1_REG_RESET                 (0x00000400)

/*=============================*/
struct __DCDC_TEST1_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DCDC_FORCE_IDLE                   : 1;
    volatile uint16_t BITFLD_DCDC_FORCE_TRIG                   : 1;
    volatile uint16_t BITFLD_DCDC_SW_TST                       : 2;
    volatile uint16_t BITFLD_DCDC_FORCE_COMP_CLK               : 1;
    volatile uint16_t BITFLD_DCDC_FORCE_COMP_TRIM              : 1;
    volatile uint16_t BITFLD_DCDC_FORCE_ILIM                   : 1;
    volatile uint16_t BITFLD_DCDC_COMP_CLK_VAL                 : 1;
    volatile uint16_t BITFLD_DCDC_ILIM_VAL                     : 4;
    volatile uint16_t BITFLD_DCDC_DIG_TST_SEL                  : 3;
};
#define DCDC_FORCE_IDLE                       (0x0001)
#define DCDC_FORCE_TRIG                       (0x0002)
#define DCDC_SW_TST                           (0x000C)
#define DCDC_FORCE_COMP_CLK                   (0x0010)
#define DCDC_FORCE_COMP_TRIM                  (0x0020)
#define DCDC_FORCE_ILIM                       (0x0040)
#define DCDC_COMP_CLK_VAL                     (0x0080)
#define DCDC_ILIM_VAL                         (0x0F00)
#define DCDC_DIG_TST_SEL                      (0x7000)



#define DCDC_TEST2_REG                       (0x50000084)
#define DCDC_TEST2_REG_RESET                 (0x00000000)

/*=============================*/
struct __DCDC_TEST2_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DCDC_COMP_TRIM_VAL                : 6;
};
#define DCDC_COMP_TRIM_VAL                    (0x003F)



#define DCDC_STATUS1_REG                     (0x50000086)
#define DCDC_STATUS1_REG_RESET               (0x00000048)

/*=============================*/
struct __DCDC_STATUS1_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DCDC_VDCDC_OK                     : 1;
    volatile uint16_t BITFLD_DCDC_ENABLED                      : 1;
    volatile uint16_t BITFLD_DCDC_STARTUP_COMPLETE             : 1;
    volatile uint16_t BITFLD_DCDC_BOOST_MODE                   : 1;
    volatile uint16_t BITFLD_DCDC_ILIM                         : 4;
    volatile uint16_t BITFLD_DCDC_VOUT_OK                      : 1;
    volatile uint16_t BITFLD_DCDC_VOUT_NOK                     : 1;
    volatile uint16_t BITFLD_DCDC_SW_STATE                     : 2;
    volatile uint16_t BITFLD_DCDC_FSM_STATE                    : 4;
};
#define DCDC_VDCDC_OK                         (0x0001)
#define DCDC_ENABLED                          (0x0002)
#define DCDC_STARTUP_COMPLETE                 (0x0004)
#define DCDC_BOOST_MODE                       (0x0008)
#define DCDC_ILIM                             (0x00F0)
#define DCDC_VOUT_OK                          (0x0100)
#define DCDC_VOUT_NOK                         (0x0200)
#define DCDC_SW_STATE                         (0x0C00)
#define DCDC_FSM_STATE                        (0xF000)



#define DCDC_STATUS2_REG                     (0x50000088)
#define DCDC_STATUS2_REG_RESET               (0x00000000)

/*=============================*/
struct __DCDC_STATUS2_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DCDC_COMP_N_CONT                  : 1;
    volatile uint16_t BITFLD_DCDC_COMP_N_DYN_N                 : 1;
    volatile uint16_t BITFLD_DCDC_COMP_N_DYN_P                 : 1;
    volatile uint16_t BITFLD_DCDC_COMP_P_CONT                  : 1;
    volatile uint16_t BITFLD_DCDC_COMP_P_DYN_N                 : 1;
    volatile uint16_t BITFLD_DCDC_COMP_P_DYN_P                 : 1;
    volatile uint16_t BITFLD_DCDC_TIMEOUT_NSW                  : 1;
    volatile uint16_t BITFLD_DCDC_TIMEOUT_PSW                  : 1;
    volatile uint16_t BITFLD_DCDC_COMP_TRIM                    : 6;
};
#define DCDC_COMP_N_CONT                      (0x0001)
#define DCDC_COMP_N_DYN_N                     (0x0002)
#define DCDC_COMP_N_DYN_P                     (0x0004)
#define DCDC_COMP_P_CONT                      (0x0008)
#define DCDC_COMP_P_DYN_N                     (0x0010)
#define DCDC_COMP_P_DYN_P                     (0x0020)
#define DCDC_TIMEOUT_NSW                      (0x0040)
#define DCDC_TIMEOUT_PSW                      (0x0080)
#define DCDC_COMP_TRIM                        (0x3F00)



#define POWER_AON_CTRL_REG                   (0x50000320) /*  */
#define POWER_AON_CTRL_REG_RESET             (0x00000008)

/*=============================*/
struct __POWER_AON_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_VBAT_HL_CONNECT_RES_CTRL          : 2;
    volatile uint16_t BITFLD_POR_VBAT_LOW_RST_MASK             : 1;
    volatile uint16_t BITFLD_POR_VBAT_HIGH_RST_MASK            : 1;
    volatile uint16_t BITFLD_RC32K_HIGH_SPEED_FORCE            : 1;
    volatile uint16_t BITFLD_RC32K_LOW_SPEED_FORCE             : 1;
    volatile uint16_t BITFLD_CHARGE_VBAT_DISABLE               : 1;
    volatile uint16_t BITFLD_BOOST_MODE_FORCE                  : 2;
    volatile uint16_t BITFLD_CMP_VCONT_SLP_DISABLE             : 1;
    volatile uint16_t BITFLD_LDO_RET_TRIM                      : 4;
    volatile uint16_t BITFLD_FORCE_RUNNING_COMP_DIS            : 1;
};
#define VBAT_HL_CONNECT_RES_CTRL              (0x0003)
#define POR_VBAT_LOW_RST_MASK                 (0x0004)
#define POR_VBAT_HIGH_RST_MASK                (0x0008)
#define RC32K_HIGH_SPEED_FORCE                (0x0010)
#define RC32K_LOW_SPEED_FORCE                 (0x0020)
#define CHARGE_VBAT_DISABLE                   (0x0040)
#define BOOST_MODE_FORCE                      (0x0180)
#define CMP_VCONT_SLP_DISABLE                 (0x0200)
#define LDO_RET_TRIM                          (0x3C00)
#define FORCE_RUNNING_COMP_DIS                (0x4000)



#define GP_DATA_REG                          (0x50000324) /*  */
#define GP_DATA_REG_RESET                    (0x00000000)

/*=============================*/
struct __GP_DATA_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SW_GP_DATA                        : 4;
    volatile uint16_t BITFLD_DISABLE_CLAMP_OVERRULE            : 1;
    volatile uint16_t BITFLD_FORCE_RCX_VREF                    : 1;
    volatile uint16_t BITFLD_FORCE_RCX_VDD                     : 1;
    volatile uint16_t BITFLD_P03_P04_FILT_DIS                  : 1;
};
#define SW_GP_DATA                            (0x000F)
#define DISABLE_CLAMP_OVERRULE                (0x0010)
#define FORCE_RCX_VREF                        (0x0020)
#define FORCE_RCX_VDD                         (0x0040)
#define P03_P04_FILT_DIS                      (0x0080)



#define TEST_VDD_REG                         (0x500003F0)
#define TEST_VDD_REG_RESET                   (0x00000000)

/*=============================*/
struct __TEST_VDD_REG
/*=============================*/
{
    volatile uint16_t BITFLD_TEST_VDD                          : 1;
    volatile uint16_t BITFLD_LDOS_DISABLE                      : 1;
};
#define TEST_VDD                              (0x0001)
#define LDOS_DISABLE                          (0x0002)



#define GP_ADC_CTRL_REG                      (0x50001500) /* General Purpose ADC Control Register */
#define GP_ADC_CTRL_REG_RESET                (0x00000000)

/*=============================*/
struct __GP_ADC_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_GP_ADC_EN                         : 1;
    volatile uint16_t BITFLD_GP_ADC_START                      : 1;
    volatile uint16_t BITFLD_GP_ADC_CONT                       : 1;
    volatile uint16_t BITFLD_GP_ADC_DMA_EN                     : 1;
    volatile uint16_t BITFLD_GP_ADC_INT                        : 1;
    volatile uint16_t BITFLD_GP_ADC_MINT                       : 1;
    volatile uint16_t BITFLD_GP_ADC_SE                         : 1;
    volatile uint16_t BITFLD_GP_ADC_MUTE                       : 1;
    volatile uint16_t BITFLD_GP_ADC_SIGN                       : 1;
    volatile uint16_t BITFLD_GP_ADC_CHOP                       : 1;
    volatile uint16_t BITFLD_GP_ADC_LDO_HOLD                   : 1;
    volatile uint16_t BITFLD_GP_ADC_OFFS_SH_GAIN_SEL           : 1;
    volatile uint16_t BITFLD_DIE_TEMP_EN                       : 1;
};
#define GP_ADC_EN                             (0x0001)
#define GP_ADC_START                          (0x0002)
#define GP_ADC_CONT                           (0x0004)
#define GP_ADC_DMA_EN                         (0x0008)
#define GP_ADC_INT                            (0x0010)
#define GP_ADC_MINT                           (0x0020)
#define GP_ADC_SE                             (0x0040)
#define GP_ADC_MUTE                           (0x0080)
#define GP_ADC_SIGN                           (0x0100)
#define GP_ADC_CHOP                           (0x0200)
#define GP_ADC_LDO_HOLD                       (0x0400)
#define GP_ADC_OFFS_SH_GAIN_SEL               (0x0800)
#define DIE_TEMP_EN                           (0x1000)



#define GP_ADC_SEL_REG                       (0x50001506) /* General Purpose ADC Input Selection Register */
#define GP_ADC_SEL_REG_RESET                 (0x00000000)

/*=============================*/
struct __GP_ADC_SEL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_GP_ADC_SEL_N                      : 3;
    volatile uint16_t BITFLD_GP_ADC_SEL_N_TST                  : 1;
    volatile uint16_t BITFLD_GP_ADC_SEL_P                      : 3;
    volatile uint16_t BITFLD_GP_ADC_SEL_P_TST                  : 1;
};
#define GP_ADC_SEL_N                          (0x0007)
#define GP_ADC_SEL_N_TST                      (0x0008)
#define GP_ADC_SEL_P                          (0x0070)
#define GP_ADC_SEL_P_TST                      (0x0080)



#define GP_ADC_PARAM_DIF_REG                 (0x5000151C)
#define GP_ADC_PARAM_DIF_REG_RESET           (0x00000000)
//register GP_ADC_PARAM_DIF_REG found for which all fields are reserved, omitting.



#define GP_ADC_PARAM_SE_REG                  (0x5000151E)
#define GP_ADC_PARAM_SE_REG_RESET            (0x00000000)
//register GP_ADC_PARAM_SE_REG found for which all fields are reserved, omitting.



#define SCAN_OBSERVE_REG                     (0x50003020)
#define SCAN_OBSERVE_REG_RESET               (0x00000000)

/*=============================*/
struct __SCAN_OBSERVE_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SCAN_FEEDBACK_MUX                 : 16;
};
#define SCAN_FEEDBACK_MUX                     (0xFFFF)



#define TEST_CTRL_REG                        (0x50003030)
#define TEST_CTRL_REG_RESET                  (0x00000000)

/*=============================*/
struct __TEST_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SHOW_CLOCKS                       : 1;
    volatile uint16_t BITFLD_SHOW_POWER                        : 1;
    volatile uint16_t BITFLD_SHOW_DCDC                         : 1;
    volatile uint16_t                                          : 1;
    volatile uint16_t BITFLD_XTAL32M_CAP_TEST_EN               : 1;
    volatile uint16_t BITFLD_LDO_CORE_CAP_BYPASS               : 1;
    volatile uint16_t BITFLD_LDO_CORE_DUMMY_LOAD_ENABLE        : 1;
    volatile uint16_t                                          : 2;
    volatile uint16_t BITFLD_CP_CAP_BIAS_TRIM                  : 2;
    volatile uint16_t BITFLD_ADPLL_SCAN_TEST_EN                : 1;
    volatile uint16_t BITFLD_ADPLL_SCAN_COMP_EN                : 1;
};
#define SHOW_CLOCKS                           (0x0001)
#define SHOW_POWER                            (0x0002)
#define SHOW_DCDC                             (0x0004)
#define XTAL32M_CAP_TEST_EN                   (0x0010)
#define LDO_CORE_CAP_BYPASS                   (0x0020)
#define LDO_CORE_DUMMY_LOAD_ENABLE            (0x0040)
#define CP_CAP_BIAS_TRIM                      (0x0600)
#define ADPLL_SCAN_TEST_EN                    (0x0800)
#define ADPLL_SCAN_COMP_EN                    (0x1000)



#define TEST_CTRL2_REG                       (0x50003032)
#define TEST_CTRL2_REG_RESET                 (0x00000000)

/*=============================*/
struct __TEST_CTRL2_REG
/*=============================*/
{
    volatile uint16_t BITFLD_ANA_TEST_OUT_SEL                  : 10;
    volatile uint16_t                                          : 1;
    volatile uint16_t BITFLD_ANA_TEST_OUT_TO_PIN               : 1;
    volatile uint16_t BITFLD_ANA_TEST_OUT_PARAM                : 4;
};
#define ANA_TEST_OUT_SEL                      (0x03FF)
#define ANA_TEST_OUT_TO_PIN                   (0x0800)
#define ANA_TEST_OUT_PARAM                    (0xF000)



#define TEST_CTRL3_REG                       (0x50003034)
#define TEST_CTRL3_REG_RESET                 (0x00000000)

/*=============================*/
struct __TEST_CTRL3_REG
/*=============================*/
{
    volatile uint16_t BITFLD_RF_TEST_OUT_SEL                   : 6;
    volatile uint16_t BITFLD_ENABLE_RFPT                       : 1;
    volatile uint16_t BITFLD_RF_TEST_OUT_PARAM                 : 6;
    volatile uint16_t BITFLD_RF_TEST_OUT_TO_PIN                : 1;
};
#define RF_TEST_OUT_SEL                       (0x003F)
#define ENABLE_RFPT                           (0x0040)
#define RF_TEST_OUT_PARAM                     (0x1F80)
#define RF_TEST_OUT_TO_PIN                    (0x2000)



#define TEST_CTRL4_REG                       (0x50003036)
#define TEST_CTRL4_REG_RESET                 (0x00000000)

/*=============================*/
struct __TEST_CTRL4_REG
/*=============================*/
{
    volatile uint16_t BITFLD_RF_TEST_IN_SEL                    : 4;
    volatile uint16_t                                          : 4;
    volatile uint16_t BITFLD_RF_TEST_IN_PARAM                  : 5;
    volatile uint16_t BITFLD_RF_TEST_IN_TO_PIN                 : 1;
};
#define RF_TEST_IN_SEL                        (0x000F)
#define RF_TEST_IN_PARAM                      (0x1F00)
#define RF_TEST_IN_TO_PIN                     (0x2000)



#define XTAL32M_TESTCTRL0_REG                (0x50003038)
#define XTAL32M_TESTCTRL0_REG_RESET          (0x00003400)

/*=============================*/
struct __XTAL32M_TESTCTRL0_REG
/*=============================*/
{
    volatile uint16_t BITFLD_SPIKE_FLT_DISABLE                 : 1;
    volatile uint16_t BITFLD_OSC_TRIM_OPEN_DISABLE             : 1;
    volatile uint16_t BITFLD_DIFFBUF_BYPASS                    : 1;
    volatile uint16_t BITFLD_DCBLOCK_LV_MODE                   : 1;
    volatile uint16_t BITFLD_CORE_XTAL_DISCHARGE               : 1;
    volatile uint16_t BITFLD_CORE_MAX_CURRENT                  : 1;
    volatile uint16_t BITFLD_CORE_I2V_TO_TESTBUS_10X           : 1;
    volatile uint16_t BITFLD_CORE_I2V_TO_TESTBUS               : 1;
    volatile uint16_t BITFLD_CORE_HOLD_AMP_REG_OVERRIDE        : 2;
    volatile uint16_t BITFLD_CORE_GM_CURRENT                   : 1;
    volatile uint16_t BITFLD_CORE_FREQ_TRIM_SW2_AMP            : 3;
    volatile uint16_t BITFLD_BIAS_SAH_HOLD_OVERRIDE            : 2;
};
#define SPIKE_FLT_DISABLE                     (0x0001)
#define OSC_TRIM_OPEN_DISABLE                 (0x0002)
#define DIFFBUF_BYPASS                        (0x0004)
#define DCBLOCK_LV_MODE                       (0x0008)
#define CORE_XTAL_DISCHARGE                   (0x0010)
#define CORE_MAX_CURRENT                      (0x0020)
#define CORE_I2V_TO_TESTBUS_10X               (0x0040)
#define CORE_I2V_TO_TESTBUS                   (0x0080)
#define CORE_HOLD_AMP_REG_OVERRIDE            (0x0300)
#define CORE_GM_CURRENT                       (0x0400)
#define CORE_FREQ_TRIM_SW2_AMP                (0x3800)
#define BIAS_SAH_HOLD_OVERRIDE                (0xC000)



#define XTAL32M_TESTCTRL1_REG                (0x5000303A)
#define XTAL32M_TESTCTRL1_REG_RESET          (0x00000000)

/*=============================*/
struct __XTAL32M_TESTCTRL1_REG
/*=============================*/
{
    volatile uint16_t BITFLD_DISABLE_TM_CLK                    : 1;
    volatile uint16_t BITFLD_LDO_VREF_HOLD_OVERRIDE            : 1;
    volatile uint16_t BITFLD_VARICAP_TEST_ENABLE               : 1;
    volatile uint16_t BITFLD_VARICAP_TEST_SEL_XTAL             : 1;
    volatile uint16_t BITFLD_PROG_VREF_SEL                     : 1;
    volatile uint16_t BITFLD_RFCLK_ADPLL_TO_GPIO               : 1;
    volatile uint16_t BITFLD_RFCLK_ADC_TO_GPIO                 : 1;
    volatile uint16_t BITFLD_RFCLK_SEL_ADPLL_ADC_TO_GPIO       : 1;
    volatile uint16_t BITFLD_OSC_TRIM_CAP_BIAS                 : 1;
};
#define DISABLE_TM_CLK                        (0x0001)
#define LDO_VREF_HOLD_OVERRIDE                (0x0002)
#define VARICAP_TEST_ENABLE                   (0x0004)
#define VARICAP_TEST_SEL_XTAL                 (0x0008)
#define PROG_VREF_SEL                         (0x0010)
#define RFCLK_ADPLL_TO_GPIO                   (0x0020)
#define RFCLK_ADC_TO_GPIO                     (0x0040)
#define RFCLK_SEL_ADPLL_ADC_TO_GPIO           (0x0080)
#define OSC_TRIM_CAP_BIAS                     (0x0100)



#define BIST_CTRL_REG                        (0x5000303C)
#define BIST_CTRL_REG_RESET                  (0x00000480)

/*=============================*/
struct __BIST_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_RAM_BIST_CONFIG                   : 2;
    volatile uint16_t BITFLD_ROMBIST_ENABLE                    : 1;
    volatile uint16_t BITFLD_SYSRAM12_BIST_ENABLE              : 1;
    volatile uint16_t                                          : 1;
    volatile uint16_t BITFLD_ROM_BIST_BUSY                     : 1;
    volatile uint16_t                                          : 1;
    volatile uint16_t BITFLD_SYSRAM3_BIST_FAIL                 : 1;
    volatile uint16_t BITFLD_SYSRAM3_BIST_BUSY                 : 1;
    volatile uint16_t                                          : 1;
    volatile uint16_t BITFLD_SYSRAM12_BIST_FAIL                : 1;
    volatile uint16_t BITFLD_SYSRAM12_BIST_BUSY                : 1;
    volatile uint16_t BITFLD_RAM_BIST_PATTERN                  : 2;
    volatile uint16_t BITFLD_SYSRAM3_BIST_ENABLE               : 1;
};
#define RAM_BIST_CONFIG                       (0x0003)
#define ROMBIST_ENABLE                        (0x0004)
#define SYSRAM12_BIST_ENABLE                  (0x0008)
#define ROM_BIST_BUSY                         (0x0020)
#define SYSRAM3_BIST_FAIL                     (0x0080)
#define SYSRAM3_BIST_BUSY                     (0x0100)
#define SYSRAM12_BIST_FAIL                    (0x0400)
#define SYSRAM12_BIST_BUSY                    (0x0800)
#define RAM_BIST_PATTERN                      (0x3000)
#define SYSRAM3_BIST_ENABLE                   (0x4000)



#define ROMBIST_RESULTL_REG                  (0x5000303E)
#define ROMBIST_RESULTL_REG_RESET            (0x00000000)

/*=============================*/
struct __ROMBIST_RESULTL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_ROMBIST_RESULTL                   : 16;
};
#define ROMBIST_RESULTL                       (0xFFFF)



#define ROMBIST_RESULTH_REG                  (0x50003040)
#define ROMBIST_RESULTH_REG_RESET            (0x00000000)

/*=============================*/
struct __ROMBIST_RESULTH_REG
/*=============================*/
{
    volatile uint16_t BITFLD_ROMBIST_RESULTH                   : 16;
};
#define ROMBIST_RESULTH                       (0xFFFF)



#define MEM_CTRL_REG                         (0x5000330C)
#define MEM_CTRL_REG_RESET                   (0x00000080)

/*=============================*/
struct __MEM_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_ROM_MARGIN_CTRL                   : 4;
    volatile uint16_t BITFLD_ROM_MARGIN_EN                     : 1;
    volatile uint16_t BITFLD_RAM_DST                           : 1;
    volatile uint16_t BITFLD_RAM_MARGIN                        : 2;
    volatile uint16_t BITFLD_ARB1_AHB_WR_BUFF                  : 1;
    volatile uint16_t BITFLD_ARB1_AHB2_WR_BUFF                 : 1;
    volatile uint16_t BITFLD_ARB2_AHB_WR_BUFF                  : 1;
    volatile uint16_t BITFLD_ARB2_AHB2_WR_BUFF                 : 1;
};
#define ROM_MARGIN_CTRL                       (0x000F)
#define ROM_MARGIN_EN                         (0x0010)
#define RAM_DST                               (0x0020)
#define RAM_MARGIN                            (0x00C0)
#define ARB1_AHB_WR_BUFF                      (0x0100)
#define ARB1_AHB2_WR_BUFF                     (0x0200)
#define ARB2_AHB_WR_BUFF                      (0x0400)
#define ARB2_AHB2_WR_BUFF                     (0x0800)



#define RFMON_CTRL_REG                       (0x50003500)
#define RFMON_CTRL_REG_RESET                 (0x00000000)

/*=============================*/
struct __RFMON_CTRL_REG
/*=============================*/
{
    volatile uint16_t BITFLD_RFMON_PACK_EN                     : 1;
    volatile uint16_t BITFLD_RFMON_CIRC_EN                     : 1;
};
#define RFMON_PACK_EN                         (0x0001)
#define RFMON_CIRC_EN                         (0x0002)



#define RFMON_ADDR_REG                       (0x50003504)
#define RFMON_ADDR_REG_RESET                 (0x00000000)

/*=============================*/
struct __RFMON_ADDR_REG
/*=============================*/
{
    volatile uint16_t                                          : 2;
    volatile uint16_t BITFLD_RFMON_ADDR                        : 14;
};
#define RFMON_ADDR                            (0xFFFC)



#define RFMON_LEN_REG                        (0x50003508)
#define RFMON_LEN_REG_RESET                  (0x00000000)

/*=============================*/
struct __RFMON_LEN_REG
/*=============================*/
{
    volatile uint16_t BITFLD_RFMON_LEN                         : 14;
};
#define RFMON_LEN                             (0x3FFF)



#define RFMON_STAT_REG                       (0x5000350C)
#define RFMON_STAT_REG_RESET                 (0x00000000)

/*=============================*/
struct __RFMON_STAT_REG
/*=============================*/
{
    volatile uint16_t BITFLD_RFMON_ACTIVE                      : 1;
    volatile uint16_t BITFLD_RFMON_OFLOW_STK                   : 1;
};
#define RFMON_ACTIVE                          (0x0001)
#define RFMON_OFLOW_STK                       (0x0002)



#define RFMON_CRV_ADDR_REG                   (0x50003510)
#define RFMON_CRV_ADDR_REG_RESET             (0x00000000)

/*=============================*/
struct __RFMON_CRV_ADDR_REG
/*=============================*/
{
    volatile uint16_t                                          : 2;
    volatile uint16_t BITFLD_RFMON_CRV_ADDR                    : 14;
};
#define RFMON_CRV_ADDR                        (0xFFFC)



#define RFMON_CRV_LEN_REG                    (0x50003514)
#define RFMON_CRV_LEN_REG_RESET              (0x00000000)

/*=============================*/
struct __RFMON_CRV_LEN_REG
/*=============================*/
{
    volatile uint16_t BITFLD_RFMON_CRV_LEN                     : 14;
};
#define RFMON_CRV_LEN                         (0x3FFF)



#define CLK_RTCDIV_REG                       (0x5000424C) /* Divisor for RTC 100Hz clock */
#define CLK_RTCDIV_REG_RESET                 (0x00051EA8)

/*=============================*/
struct __CLK_RTCDIV_REG
/*=============================*/
{
    volatile uint32_t BITFLD_RTC_DIV_FRAC                      : 10;
    volatile uint32_t BITFLD_RTC_DIV_INT                       : 9;
    volatile uint32_t BITFLD_RTC_DIV_DENOM                     : 1;
    volatile uint32_t BITFLD_RTC_DIV_ENABLE                    : 1;
    volatile uint32_t BITFLD_RTC_RESET_REQ                     : 1;
};
#define RTC_DIV_FRAC                          (0x03FF)
#define RTC_DIV_INT                           (0x7FC00)
#define RTC_DIV_DENOM                         (0x80000)
#define RTC_DIV_ENABLE                        (0x100000)
#define RTC_RESET_REQ                         (0x200000)
/*===========================================================================*/ 
/*===================== End of automatic generated code =====================*/ 
/*===========================================================================*/ 



/*===========================================================================*/ 
/*========================== Start of footer part ===========================*/ 
/*===========================================================================*/ 
/*----------------------------*/
/* Data access macros         */
/*----------------------------*/

#define SHIF16(a) ((a)&0x0001? 0:(a)&0x0002? 1:(a)&0x0004? 2:(a)&0x0008? 3: \
                   (a)&0x0010? 4:(a)&0x0020? 5:(a)&0x0040? 6:(a)&0x0080? 7: \
                   (a)&0x0100? 8:(a)&0x0200? 9:(a)&0x0400?10:(a)&0x0800?11: \
                   (a)&0x1000?12:(a)&0x2000?13:(a)&0x4000?14:           15)

#define SHIF32(a)((a)&0x00000001? 0:(a)&0x00000002? 1:(a)&0x00000004? 2:(a)&0x00000008? 3:\
                  (a)&0x00000010? 4:(a)&0x00000020? 5:(a)&0x00000040? 6:(a)&0x00000080? 7:\
                  (a)&0x00000100? 8:(a)&0x00000200? 9:(a)&0x00000400?10:(a)&0x00000800?11:\
                  (a)&0x00001000?12:(a)&0x00002000?13:(a)&0x00004000?14:(a)&0x00008000?15:\
                  (a)&0x00010000?16:(a)&0x00020000?17:(a)&0x00040000?18:(a)&0x00080000?19:\
                  (a)&0x00100000?20:(a)&0x00200000?21:(a)&0x00400000?22:(a)&0x00800000?23:\
                  (a)&0x01000000?24:(a)&0x02000000?25:(a)&0x04000000?26:(a)&0x08000000?27:\
                  (a)&0x10000000?28:(a)&0x20000000?29:(a)&0x40000000?30:               31)

#define SetWord8(a,d)  (* ( volatile uint8_t*) (a)=(d) )
#define SetWord16(a,d) (* ( volatile uint16_t*)(a)=(d) )
#define SetWord32(a,d) (* ( volatile uint32_t*)(a)=(d) )
#define SetWord64(a,d) (* ( volatile uint64_t*)(a)=(d) )

#define GetWord8(a)    (* ( volatile uint8_t*) (a) )
#define GetWord16(a)   (* ( volatile uint16_t*)(a) )
#define GetWord32(a)   (* ( volatile uint32_t*)(a) )
#define GetWord64(a)   (* ( volatile uint64_t*)(a) )

/* Aliases for backwards compatibility (only the Byte versions). */
#define SetByte(a,d) SetWord8((a),(d))
#define GetByte(a)   GetWord8((a))

#define SetBits16(a,f,d) ( SetWord16( (a), (GetWord16(a)&(~(uint16_t)(f))) | (((uint16_t)(d))<<SHIF16((f))) ))
#define SetBits32(a,f,d) ( SetWord32( (a), (GetWord32(a)&(~(uint32_t)(f))) | (((uint32_t)(d))<<SHIF32((f))) ))

// old-fashioned way. Allowed on APB-2 under the following conditions:
// * armcc is used (gcc for ARM seems to work as well?)
// * bitfields are marked with 'volatile' keyword and the correct word size
#define GetBits(a,f)    ( ((volatile struct __##a *)(a))->BITFLD_##f )
#define SetBits(a,f,d) (( ((volatile struct __##a *)(a))->BITFLD_##f )=(d) )

#define GetBits16(a,f) ( (GetWord16(a)&( (uint16_t)(f) )) >> SHIF16(f) )
#define GetBits32(a,f) ( (GetWord32(a)&( (uint32_t)(f) )) >> SHIF32(f) )

// Macro's used in the recommended_settings function
// All fields are combined into a single mask.
#define SetWordMasked16(a,m,d) SetWord16(a, (GetWord16(a)&~m) | (d&m))
#define SetWordMasked32(a,m,d) SetWord32(a, (GetWord32(a)&~m) | (d&m))


/*===========================================================================*/ 
/*=========================== End of footer part ============================*/ 
/*===========================================================================*/ 



// _DA14531_H_
#endif
