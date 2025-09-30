/**
 ****************************************************************************************
 *
 * @file wkupct_quadec.c
 *
 * @brief Wakeup IRQ & Quadrature Decoder driver.
 *
 * Copyright (C) 2013-2020 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */

/* Important note: If, upon reception of interrupt from the wakeup controller or the quadrature
 *                  decoder, the system resumes from sleep mode and you wish to resume peripherals
 *                  functionality , it is necessary to include in your interrupt handler function(s)
 *                  - the ones you register using wkupct_register_callback() and/or
 *                  quad_decoder_register_callback() - the following lines:
 *
 *                  // Init System Power Domain blocks: GPIO, WD Timer, Sys Timer, etc.
 *                  // Power up and init Peripheral Power Domain blocks,
 *                  // and finally release the pad latches.
 *                  if(GetBits16(SYS_STAT_REG, PER_IS_DOWN))
 *                      periph_init();
 *
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include <stdio.h>
#include <stdint.h>
#include "datasheet.h"
#include "compiler.h"
#include "syscntl.h"
#include "wkupct_quadec.h"
#include "arch.h"

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */

#ifdef USE_ARCH_WKUPCT_DEB_TIME
extern uint16_t arch_wkupct_deb_time;
#endif

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

static quad_encoder_handler_function_t QUADDEC_callback         __SECTION_ZERO("retention_mem_area0"); // Quadrature decoder handler callback
static wakeup_handler_function_t WKUPCT_callback                __SECTION_ZERO("retention_mem_area0"); // Wakeup handler callback
#if defined (__DA14531__)
static wakeup_handler_function_t WKUPCT2_callback               __SECTION_ZERO("retention_mem_area0"); // Wakeup2 handler callback
#endif

#if defined (__DA14531_01__) && !defined (__EXCLUDE_ROM_WKUPCT_QUADEC__)
// Required DA14531-01 ROM symbols
extern void wkupct_enable_irq_ROM(uint32_t sel_pins, uint32_t pol_pins, uint16_t events_num, uint16_t deb_time);
extern void wkupct2_enable_irq_ROM(uint32_t sel_pins, uint32_t pol_pins, uint16_t events_num, uint16_t deb_time);
#endif // __EXCLUDE_ROM_WKUPCT_QUADEC__

/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
 */

#if !defined (__DA14531_01__) || defined (__EXCLUDE_ROM_WKUPCT_QUADEC__)
/**
 ****************************************************************************************
 * @brief Disable WKUP_QUADEC_IRQn only when Quadrature Decoder and Wakeup Controller
 * have unregistered from using it.
 * @return WKUPCT_QUADEC_ERR_OK, WKUPCT_QUADEC_ERR_RESERVED
 ****************************************************************************************
 */
static wkupct_quadec_error_t wkupct_quad_disable_IRQ(void)
{
#if defined (__DA14531__)
    if (((GetWord16(QDEC_CTRL_REG) & QDEC_IRQ_ENABLE) == 0) && ((GetWord16(WKUP_CTRL_REG) & WKUP_ENABLE_IRQ) == 0) && ((GetWord16(WKUP_CTRL_REG) & WKUP2_ENABLE_IRQ) == 0))
#else
    if (((GetWord16(QDEC_CTRL_REG) & QD_IRQ_MASK) == 0) && ((GetWord16(WKUP_CTRL_REG) & WKUP_ENABLE_IRQ) == 0))
#endif
    {
        NVIC_DisableIRQ(WKUP_QUADEC_IRQn);
        return WKUPCT_QUADEC_ERR_OK;
    }
    return WKUPCT_QUADEC_ERR_RESERVED;
}
#endif // __EXCLUDE_ROM_WKUPCT_QUADEC__

#if !defined(__EXCLUDE_WKUP_QUADEC_HANDLER__)
#if !defined (__DA14531__)
void WKUP_QUADEC_Handler(void)
{
    int16_t x,y,z;

    // Restore clock
    syscntl_use_highest_amba_clocks();

    // Note: in case of simultaneous triggering of quadrature decoder and wakeup controller, the quadrature decoder interrupt will be handled.
    if (GetBits16(CLK_PER_REG, QUAD_ENABLE) && GetBits16(QDEC_CTRL_REG, QD_IRQ_STATUS) && GetBits16(QDEC_CTRL_REG, QD_IRQ_MASK))
    {                                               // The Quadrature Decoder clock is enabled & the Quadrature Decoder interrupt has triggered
                                                    // The Quadrature Decoder has been registered as interrupt source
        SetBits16(QDEC_CTRL_REG, QD_IRQ_CLR, 1);    // Write 1 to clear Quadrature Decoder interrupt
        SetBits16(QDEC_CTRL_REG, QD_IRQ_MASK, 0);   // Write 0 to mask the Quadrature Decoder interrupt
        if (QUADDEC_callback != NULL)               // Quadrature Decoder callback function has been registered by the application
        {
            x = quad_decoder_get_x_counter();
            y = quad_decoder_get_y_counter();
            z = quad_decoder_get_z_counter();
            QUADDEC_callback(x, y, z);
        }
    }
    else
    {
        // since the interrupt does not come from the Quadrature controller, it is from the wakeup controller
        if (GetBits16(CLK_PER_REG, WAKEUPCT_ENABLE) && GetBits16(WKUP_CTRL_REG, WKUP_ENABLE_IRQ))
        {
            SetWord16(WKUP_RESET_IRQ_REG, 1);               // Acknowledge it
            SetBits16(WKUP_CTRL_REG, WKUP_ENABLE_IRQ, 0);   // No more interrupts of this kind
            if (WKUPCT_callback != NULL)
            {
                WKUPCT_callback();
            }
        }
    }
    return;
}

#else

void WKUP_QUADEC_Handler(void)
{
    int16_t x,y,z;

    // Restore clock
    syscntl_use_highest_amba_clocks();

    if (GetBits16(CLK_PER_REG, QUAD_ENABLE) && ((GetWord16(QDEC_CTRL_REG) & (QDEC_IRQ_STATUS | QDEC_IRQ_ENABLE)) == (QDEC_IRQ_STATUS | QDEC_IRQ_ENABLE)))
    {
        SetBits16(QDEC_CTRL_REG, QDEC_IRQ_STATUS, 1);                       // Clear the interrupt
        SetBits16(QDEC_CTRL_REG, QDEC_IRQ_ENABLE, 0);                       // Write 0 to mask the Quadrature Decoder interrupt
        if (QUADDEC_callback != NULL)                                       // Quadrature Decoder callback function has been registered by the application
        {
            x = quad_decoder_get_x_counter();
            y = quad_decoder_get_y_counter();
            z = quad_decoder_get_z_counter();
            QUADDEC_callback(x, y, z);
        }
    }
    else if (GetBits16(CLK_PER_REG, WAKEUPCT_ENABLE) && GetBits16(WKUP_IRQ_STATUS_REG, WKUP_IRQ_STATUS) && GetBits16(WKUP_CTRL_REG, WKUP_ENABLE_IRQ))
    {
        SetWord16(WKUP_IRQ_STATUS_REG, WKUP_IRQ_STATUS);                    //Reset the interrupt
        SetBits16(WKUP_CTRL_REG, WKUP_ENABLE_IRQ, 0);                       // No more interrupts of this kind
        if (WKUPCT_callback != NULL)
        {
           WKUPCT_callback();
        }
    }
    else if (GetBits16(CLK_PER_REG, WAKEUPCT_ENABLE) && GetBits16(WKUP_IRQ_STATUS_REG, WKUP2_IRQ_STATUS) && GetBits16(WKUP_CTRL_REG, WKUP2_ENABLE_IRQ))
    {
        SetWord16(WKUP_IRQ_STATUS_REG, WKUP2_IRQ_STATUS);                   //Reset the interrupt
        SetBits16(WKUP_CTRL_REG, WKUP2_ENABLE_IRQ, 0);          // No more interrupts of this kind
        if (WKUPCT2_callback != NULL)
        {
           WKUPCT2_callback();
        }
    }
    else
    {   //ERROR (should never end-up here)
        //ASSERT_ERROR(0);
    }
    return;
}
#endif
#endif

/*
 *                                Wakeup Controller
 ****************************************************************************************
 */

#if defined (__DA14531_01__) && !defined (__EXCLUDE_ROM_WKUPCT_QUADEC__)
void wkupct_enable_irq(uint32_t sel_pins, uint32_t pol_pins, uint16_t events_num, uint16_t deb_time)
{
#ifdef USE_ARCH_WKUPCT_DEB_TIME
    arch_wkupct_deb_time = deb_time;                                 // Store value in retention memory
#endif
    wkupct_enable_irq_ROM(sel_pins, pol_pins, events_num, deb_time);
}
#else
void wkupct_enable_irq(uint32_t sel_pins, uint32_t pol_pins, uint16_t events_num, uint16_t deb_time)
{
#ifdef USE_ARCH_WKUPCT_DEB_TIME
    arch_wkupct_deb_time = deb_time;                                 // Store value in retention memory
#endif
    SetBits16(CLK_PER_REG, WAKEUPCT_ENABLE, 1);                      // Enable clock of Wakeup controller

#if defined (__DA14531__)
    ASSERT_WARNING(events_num > 0);
    SetWord16(WKUP_IRQ_STATUS_REG, WKUP_CNTR_RST);                   // Reset event counter
    SetBits16(WKUP_CTRL_REG, WKUP_DEB_VALUE, deb_time & 0x3F);       // Set debounce time
    SetWord16(WKUP_POL_GPIO_REG, pol_pins);                          // Set wakeup polarity
    SetWord16(WKUP_COMPARE_REG, ((events_num - 1) & 0xFF));          // Wait for events_num events and wakeup
    SetBits16(WKUP_CTRL_REG, WKUP_ENABLE_IRQ, 1);                    // Enable IRQ in Wakeup controller
    SetWord16(WKUP_SELECT_GPIO_REG, sel_pins);                       // Set wake up pin
#else
    SetWord16(WKUP_COMPARE_REG, (events_num & 0xFF));                // Wait for events_num events and wakeup

    for(uint8_t i = 0; i < 4; i++)
    {
        // Always write 8-bit value
        SetBits16(WKUP_POL_P0_REG + (2 * i), 0xFF , (pol_pins >> (8 * i)) & 0xFF);
        SetBits16(WKUP_SELECT_P0_REG + (2 * i), 0xFF , (sel_pins >> (8 * i)) & 0xFF);
    }

    // Set P28, P29 configuration
    SetBits16(WKUP_POL_P2_REG, (3 << 8), (pol_pins >> 14) & 3);
    SetBits16(WKUP_SELECT_P2_REG, (3 << 8), (sel_pins >> 14) & 3);

    SetWord16(WKUP_RESET_IRQ_REG, 1);                                 // Reset interrupt
    SetWord16(WKUP_RESET_CNTR_REG, 0);                                // Reset event counter
    SetBits16(WKUP_CTRL_REG, WKUP_DEB_VALUE, deb_time & 0x3F);        // Set debounce time
    SetBits16(WKUP_CTRL_REG, WKUP_ENABLE_IRQ, 1);                     // Enable IRQ in Wakeup controller
#endif

    NVIC_SetPriority(WKUP_QUADEC_IRQn, 2);                            // Set irq Priority to 2
    NVIC_EnableIRQ(WKUP_QUADEC_IRQn);
}
#endif // __EXCLUDE_ROM_WKUPCT_QUADEC__

#if defined (__DA14531__)
#if defined (__DA14531_01__) && !defined (__EXCLUDE_ROM_WKUPCT_QUADEC__)
void wkupct2_enable_irq(uint32_t sel_pins, uint32_t pol_pins, uint16_t events_num, uint16_t deb_time)
{
#ifdef USE_ARCH_WKUPCT_DEB_TIME
    arch_wkupct_deb_time = deb_time;                                   // Store value in retention memory
#endif
    wkupct2_enable_irq_ROM(sel_pins, pol_pins, events_num, deb_time);
}
#else
void wkupct2_enable_irq(uint32_t sel_pins, uint32_t pol_pins, uint16_t events_num, uint16_t deb_time)
{
#ifdef USE_ARCH_WKUPCT_DEB_TIME
    arch_wkupct_deb_time = deb_time;                                   // Store value in retention memory
#endif
    SetBits16(CLK_PER_REG, WAKEUPCT_ENABLE, 1);                        // Enable clock of Wakeup controller

    ASSERT_WARNING(events_num > 0);
    SetWord16(WKUP_IRQ_STATUS_REG, WKUP2_CNTR_RST);                    // Reset event counter
    SetBits16(WKUP_CTRL_REG, WKUP_DEB_VALUE, deb_time & 0x3F);         // Set debounce time
    SetWord16(WKUP2_POL_GPIO_REG, pol_pins);                           // Set wakeup polarity
    SetWord16(WKUP_COMPARE_REG, ((events_num - 1) & 0xFF));            // Wait for events_num events and wakeup
    SetBits16(WKUP_CTRL_REG, WKUP2_ENABLE_IRQ, 1);                     // Enable IRQ in Wakeup controller
    SetWord16(WKUP2_SELECT_GPIO_REG, sel_pins);                        // Set wake up pin

    NVIC_SetPriority(WKUP_QUADEC_IRQn, 2);                             // Set irq Priority to 2
    NVIC_EnableIRQ(WKUP_QUADEC_IRQn);
}
#endif // __EXCLUDE_ROM_WKUPCT_QUADEC__
#endif

#if !defined (__DA14531_01__) || defined (__EXCLUDE_ROM_WKUPCT_QUADEC__)
wkupct_quadec_error_t wkupct_disable_irq()
{
#if defined (__DA14531__)
    SetWord16(WKUP_IRQ_STATUS_REG, WKUP_IRQ_STATUS);                 // Reset the interrupt
#else
    SetWord16(WKUP_RESET_IRQ_REG, 1);                                // Reset the interrupt
#endif

    SetBits16(WKUP_CTRL_REG, WKUP_ENABLE_IRQ, 0);                    // Disable IRQ in Wakeup controller

    return wkupct_quad_disable_IRQ();
}

#if defined (__DA14531__)
wkupct_quadec_error_t wkupct2_disable_irq()
{
    SetWord16(WKUP_IRQ_STATUS_REG, WKUP2_IRQ_STATUS);                 // Reset the interrupt
    SetBits16(WKUP_CTRL_REG, WKUP2_ENABLE_IRQ, 0);                    // Disable IRQ in Wakeup controller

    return wkupct_quad_disable_IRQ();
}
#endif
#endif // __EXCLUDE_ROM_WKUPCT_QUADEC__

void wkupct_register_callback(wakeup_handler_function_t callback)
{
    WKUPCT_callback = callback;
}

#if defined (__DA14531__)
void wkupct2_register_callback(wakeup_handler_function_t callback)
{
    WKUPCT2_callback = callback;
}
#endif

/*
 *                                Quadrature Decoder
 ****************************************************************************************
 */

void quad_decoder_register_callback(quad_encoder_handler_function_t callback)
{
    QUADDEC_callback = callback;
}

#if !defined (__DA14531_01__) || defined (__EXCLUDE_ROM_WKUPCT_QUADEC__)
void quad_decoder_init(const QUAD_DEC_INIT_PARAMS_t *quad_dec_init_params)
{
    // Enable the Quadrature clock
    SetBits16(CLK_PER_REG, QUAD_ENABLE, 1);

#if defined (__DA14531__)
    uint16_t reg;

    // Setup Quadrature Decoder pin assignment and event mode
    SetWord16(QDEC_CTRL2_REG, (uint16_t)quad_dec_init_params->chx_port_sel |
                              (uint16_t)quad_dec_init_params->chy_port_sel |
                              (uint16_t)quad_dec_init_params->chz_port_sel |
                              (uint16_t)quad_dec_init_params->chx_event_mode |
                              (uint16_t)quad_dec_init_params->chy_event_mode |
                              (uint16_t)quad_dec_init_params->chz_event_mode);

    // Clearing must be applied with slow clock. Otherwise the counters may count +1 because the input goes to 0 and then back to the GPIO state.
    SetWord16(QDEC_CLOCKDIV_REG, 0x3E7);

    reg = GetWord16(QDEC_CTRL2_REG);
    SetWord16(QDEC_CTRL2_REG, 0);
    SetWord16(QDEC_CTRL2_REG, reg);
#else
    // Setup Quadrature Decoder pin assignment
    SetWord16(QDEC_CTRL2_REG, (uint16_t)quad_dec_init_params->chx_port_sel | (uint16_t)quad_dec_init_params->chy_port_sel | (uint16_t)quad_dec_init_params->chz_port_sel);
#endif

    SetWord16(QDEC_CLOCKDIV_REG, quad_dec_init_params->qdec_clockdiv);
}

void quad_decoder_release(void)
{
    SetWord16(QDEC_CTRL2_REG, (uint16_t)QUAD_DEC_CHXA_NONE_AND_CHXB_NONE | (uint16_t)QUAD_DEC_CHYA_NONE_AND_CHYB_NONE | (uint16_t)QUAD_DEC_CHZA_NONE_AND_CHZB_NONE);

    quad_decoder_disable_irq(); //Note: Will disable the IRQ only if Wakeup sources 1 and 2 has also unregistered from using it.

    // Disable the Quadrature clock
    SetBits16(CLK_PER_REG, QUAD_ENABLE, 0);
}

void quad_decoder_enable_irq(uint8_t event_count)
{
#if defined (__DA14531__)
    SetBits16(QDEC_CTRL_REG, QDEC_IRQ_THRES, event_count);                 // Set event counter (this will trigger an IRQ after event_count + 1 events)
    SetBits16(QDEC_CTRL_REG, QDEC_IRQ_ENABLE, 1);                          // Interrupt not masked
#else
    SetBits16(QDEC_CTRL_REG, QD_IRQ_CLR, 1);                               // Clear any garbage
    SetBits16(QDEC_CTRL_REG, QD_IRQ_THRES, event_count);                   // Set event counter
    SetBits16(QDEC_CTRL_REG, QD_IRQ_MASK, 1);                              // Interrupt not masked
#endif
    NVIC_SetPriority(WKUP_QUADEC_IRQn, 2);                                 // Set irq Priority to 2
    NVIC_EnableIRQ(WKUP_QUADEC_IRQn);                                      // enable the WKUP_QUADEC_IRQn
}

wkupct_quadec_error_t quad_decoder_disable_irq(void)
{
#if defined (__DA14531__)
    SetBits16(QDEC_CTRL_REG, QDEC_IRQ_ENABLE,0);                           // Mask Quadrature Decoder IRQ
#else
    SetBits16(QDEC_CTRL_REG, QD_IRQ_CLR, 1);                               // Write 1 to clear Quadrature Decoder interrupt
    SetBits16(QDEC_CTRL_REG, QD_IRQ_MASK, 0);                              // Write 0 to mask the Quadrature Decoder interrupt
#endif

    return wkupct_quad_disable_IRQ();
}

#if defined (__DA14531__)
void quad_decoder_clear_irq(void)
{
    // Get value of peripheral clock
    uint8_t reg = GetBits16(CLK_PER_REG, QUAD_ENABLE);
    // Enable peripheral clock
    SetBits16(CLK_PER_REG, QUAD_ENABLE, 1);

    // Clear quadec pending interrupt - mask quadec interrupt
    SetWord16(QDEC_CTRL_REG, QDEC_IRQ_STATUS);

    // Set previous configured value of peripheral clock
    SetBits16(CLK_PER_REG, QUAD_ENABLE, reg);

    // Clear respective NVIC entry
    NVIC_ClearPendingIRQ(WKUP_QUADEC_IRQn);
}
#endif
#endif // __EXCLUDE_ROM_WKUPCT_QUADEC__
