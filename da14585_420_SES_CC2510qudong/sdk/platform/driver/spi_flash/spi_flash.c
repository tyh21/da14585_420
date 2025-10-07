/**
 ****************************************************************************************
 *
 * @file spi_flash.c
 *
 * @brief SPI Flash driver for the Standard SPI Flash.
 *
 * Copyright (C) 2012-2021 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */

#include <stdio.h>
#include <string.h>
#include "spi_flash.h"
#if (USE_SPI_FLASH_EXTENSIONS)
#include "gpio.h"
#endif

// SPI Flash device parameters environment
static spi_flash_cfg_t spi_flash_cfg_env;

#if (USE_SPI_FLASH_EXTENSIONS)
#define SPI_FLASH_ENABLE_POWER_PIN()    do {                                                        \
                                                bool is_pin_enabled = spi_flash_enable_power_pin(); \
                                                ASSERT_WARNING(is_pin_enabled);                     \
                                        } while (0)
#else
#define SPI_FLASH_ENABLE_POWER_PIN()
#endif

/*
 * SPI Flash Helper functions
 ****************************************************************************************
 */
int8_t spi_flash_is_busy(void)
{
    if ((spi_flash_read_status_reg() & SPI_FLASH_SR_BUSY) == 0)
    {
        return SPI_FLASH_ERR_OK;
    }
    return SPI_FLASH_ERR_BUSY;
}


int8_t spi_flash_wait_till_ready(void)
{
    for (uint32_t status_read_cnt = 0; status_read_cnt < SPI_FLASH_WAIT; status_read_cnt++)
    {
        if ((spi_flash_read_status_reg() & SPI_FLASH_SR_BUSY) == 0)
        {
            return SPI_FLASH_ERR_OK;
        }
    }
    return SPI_FLASH_ERR_TIMEOUT;
}


/*
 * SPI Flash Configuration functions
 ****************************************************************************************
 */

int8_t spi_flash_enable(const spi_cfg_t *spi_cfg, const spi_flash_cfg_t *spi_flash_cfg)
{
    int8_t status = SPI_FLASH_ERR_OK;

    if (spi_flash_cfg == NULL)
    {
        return SPI_FLASH_ERR_UNKNOWN_FLASH_TYPE;
    }

    // Initialize the SPI block
    spi_initialize(spi_cfg);

    // Release the SPI flash memory from power down
    status = spi_flash_release_from_power_down();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Disable the SPI flash memory protection (unprotect all sectors)
    status = spi_flash_configure_memory_protection(SPI_FLASH_MEM_PROT_NONE);
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Store the given SPI flash memory configuration
    spi_flash_configure_env(spi_flash_cfg);

    return status;
}

int8_t spi_flash_enable_with_autodetect(const spi_cfg_t *spi_cfg, uint8_t *dev_id)
{
    int8_t status = SPI_FLASH_ERR_OK;

    // Initialize the SPI block
    spi_initialize(spi_cfg);

    // Release the SPI flash memory from power down
    status = spi_flash_release_from_power_down();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Disable the SPI flash memory protection (unprotect all sectors)
    status = spi_flash_configure_memory_protection(SPI_FLASH_MEM_PROT_NONE);
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Try to auto-detect the SPI flash memory
    status = spi_flash_auto_detect(dev_id);

    return status;
}

void spi_flash_configure_env(const spi_flash_cfg_t *spi_flash_cfg)
{
    // Copy device parameters to environment
    memcpy(&spi_flash_cfg_env, spi_flash_cfg, sizeof(spi_flash_cfg_t));
}

int8_t spi_flash_auto_detect(uint8_t *dev_id)
{
    int8_t status;
    // List of known SPI Flash devices
    const spi_flash_cfg_t known_spi_devs_list[] =
    {
        {W25X10CL_DEV_INDEX,    W25X10CL_JEDEC_ID,    W25X10CL_CHIP_SIZE},
        {W25X20CL_DEV_INDEX,    W25X20CL_JEDEC_ID,    W25X20CL_CHIP_SIZE},
        {AT25DX011_DEV_INDEX,   AT25DX011_JEDEC_ID,   AT25DX011_CHIP_SIZE},
        {MX25V1006E_DEV_INDEX,  MX25V1006E_JEDEC_ID,  MX25V1006E_CHIP_SIZE},
        {MX25R1035F_DEV_INDEX,  MX25R1035F_JEDEC_ID,  MX25R1035F_CHIP_SIZE},
        {MX25R2035F_DEV_INDEX,  MX25R2035F_JEDEC_ID,  MX25R2035F_CHIP_SIZE},
        {P25Q10U_DEV_INDEX,     P25Q10U_JEDEC_ID,     P25Q10U_CHIP_SIZE},
        {GD25WD20_DEV_INDEX,    GD25WD20_JEDEC_ID,    GD25WD20_CHIP_SIZE},
        {AT25DF021A_DEV_INDEX,  AT25DF021A_JEDEC_ID,  AT25DF021A_CHIP_SIZE},
        {AT25EU0021A_DEV_INDEX, AT25EU0021A_JEDEC_ID, AT25EU0021A_CHIP_SIZE},
        {AT25XE041D_DEV_INDEX,  AT25XE041D_JEDEC_ID,  AT25XE041D_CHIP_SIZE},
#if defined (__FPGA__)
        {MX25R8035F_DEV_INDEX,  MX25R8035F_JEDEC_ID,  MX25R8035F_CHIP_SIZE},
        {AT45DB081E_DEV_INDEX,  AT45DB081E_JEDEC_ID,  AT45DB081E_CHIP_SIZE},
#endif
    };

    uint32_t jedec_id;
    uint8_t supported_spi_flash_count;

    // Read JEDEC ID
    status = spi_flash_read_jedec_id(&jedec_id);
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    if ((jedec_id == 0x00000000) || (jedec_id == 0xFFFFFFFF))
    {
        // SPI flash device not connected
        return SPI_FLASH_ERR_AUTODETECT_ERROR;
    }

    // Calculate dynamically the number of supported devices
    supported_spi_flash_count = sizeof(known_spi_devs_list) / sizeof(known_spi_devs_list[0]);

    // Try to find the device in the known devices list
    for (uint8_t i = 0; i < supported_spi_flash_count; i++)
    {
        if (jedec_id == known_spi_devs_list[i].jedec_id)
        {
            spi_flash_configure_env(&known_spi_devs_list[i]);
            *dev_id = known_spi_devs_list[i].dev_index;
            return SPI_FLASH_ERR_OK;
        }
    }

    // SPI flash device not recognized
    return SPI_FLASH_ERR_NOT_DETECTED;
}


/*
 * SPI Flash power down functions
 ****************************************************************************************
 */

int8_t spi_flash_power_down(void)
{
    SPI_FLASH_ENABLE_POWER_PIN();

    // Check if SPI Flash is ready
    int8_t status = spi_flash_is_busy();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Send command
    spi_set_bitmode(SPI_MODE_8BIT);
    spi_transaction(SPI_FLASH_OP_DP);

    return SPI_FLASH_ERR_OK;
}

int8_t spi_flash_release_from_power_down(void)
{
    SPI_FLASH_ENABLE_POWER_PIN();

    // Toggle the CS# for at least 20ns to release from deep power down
    spi_cs_low();
    spi_cs_high();

    // Send command
    spi_set_bitmode(SPI_MODE_8BIT);
    spi_transaction(SPI_FLASH_OP_RDP);

    // Adesto/Dialog flashes may be in UDPD (ultra deep power down) mode.
    // They need 260 us maximum to wake up from this mode.
    // The loop below will provide roughly 300 us of delay.
#if (USE_SPI_FLASH_ADESTO_UDPD)
    const int wait_time_in_us = 300;
    const int repetitions = 2 * wait_time_in_us;
    for (volatile int i = 0; i < repetitions; i++);
#endif
    return SPI_FLASH_ERR_OK;
}

int8_t spi_flash_ultra_deep_power_down(void)
{
    SPI_FLASH_ENABLE_POWER_PIN();

    // Check if SPI Flash is ready
    int8_t status = spi_flash_is_busy();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Send command
    spi_set_bitmode(SPI_MODE_8BIT);
    spi_transaction(SPI_FLASH_OP_UDPD);

    return SPI_FLASH_ERR_OK;
}

/*
 * SPI Flash Status Register functions
 ****************************************************************************************
 */

uint16_t spi_flash_read_status_reg(void)
{
    SPI_FLASH_ENABLE_POWER_PIN();

    spi_set_bitmode(SPI_MODE_16BIT);

    return spi_transaction((uint16_t) (SPI_FLASH_OP_RDSR << 8));
}

/**
 ****************************************************************************************
 * @brief Issue a Write Enable Command.
 * @param[in] command       Command to send
 * @return Error code
 ****************************************************************************************
 */
static int8_t spi_flash_write_enable(uint8_t command)
{
    SPI_FLASH_ENABLE_POWER_PIN();

    // Check if SPI Flash is ready
    int8_t status = spi_flash_is_busy();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Send command
    spi_set_bitmode(SPI_MODE_8BIT);
    spi_transaction(command);

    // Wait until SPI Flash is ready
    status = spi_flash_wait_till_ready();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Check Status Register
    if ((spi_flash_read_status_reg() & SPI_FLASH_SR_WEL) ==  SPI_FLASH_SR_WEL)
    {
        return SPI_FLASH_ERR_OK;
    }

    return SPI_FLASH_ERR_WEL_ERROR;
}

int8_t spi_flash_set_write_enable(void)
{
    return spi_flash_write_enable(SPI_FLASH_OP_WREN);
}

int8_t spi_flash_write_enable_volatile(void)
{
    return spi_flash_write_enable(SPI_FLASH_OP_VWREN);
}

int8_t spi_flash_set_write_disable(void)
{
    SPI_FLASH_ENABLE_POWER_PIN();

    // Check if SPI Flash is ready
    int8_t status = spi_flash_is_busy();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Send command
    spi_set_bitmode(SPI_MODE_8BIT);
    spi_transaction(SPI_FLASH_OP_WRDI);

    // Wait until SPI Flash is ready
    status = spi_flash_wait_till_ready();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Check Status Register
    if ((spi_flash_read_status_reg() & SPI_FLASH_SR_WEL) == 0)
    {
        return SPI_FLASH_ERR_OK;
    }

    return SPI_FLASH_ERR_WEL_ERROR;
}

int8_t spi_flash_write_status_reg(uint8_t data)
{
    // Check if SPI Flash is ready
    int8_t status = spi_flash_is_busy();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Send command
    spi_set_bitmode(SPI_MODE_16BIT);
    spi_transaction((SPI_FLASH_OP_WRSR << 8) | data);

    // Wait until SPI Flash is ready
    spi_flash_wait_till_ready();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    return SPI_FLASH_ERR_OK;
}

void spi_flash_read_config_reg(uint32_t *data)
{
    SPI_FLASH_ENABLE_POWER_PIN();

    // Set SPI bitmode to 32-bit
    spi_set_bitmode(SPI_MODE_32BIT);

    // Received data contain Config reg1 + Config reg2 + Config reg1 due to 32bit spi transaction
    *data = (spi_transaction((uint32_t) (SPI_FLASH_OP_RDCFGR << 24)) >> 8) & 0x0000FFFF;
}

int8_t spi_flash_write_status_config_reg(uint32_t data)
{
    int8_t status;
    SPI_FLASH_ENABLE_POWER_PIN();

    // Set Write Enable
    status = spi_flash_set_write_enable();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Wait until SPI Flash is ready
    spi_flash_wait_till_ready();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Send Command
    spi_set_bitmode(SPI_MODE_32BIT);
    spi_transaction((SPI_FLASH_OP_WRSR << 24) | (data & 0x00FFFFFF));

    return status;
}

void spi_flash_read_security_reg(uint32_t *data)
{
    SPI_FLASH_ENABLE_POWER_PIN();

    spi_set_bitmode(SPI_MODE_16BIT);
    *data = spi_transaction((uint32_t) (SPI_FLASH_OP_RDSCUR << 8));
}

/*
 * SPI Flash Power modes
 ****************************************************************************************
 */

void spi_flash_get_power_mode(uint32_t *data)
{
    SPI_FLASH_ENABLE_POWER_PIN();

    spi_flash_read_config_reg(data);
}

int8_t spi_flash_set_power_mode(uint8_t data)
{
    uint32_t tmp_data;

    // Read current status and config register values to avoid changing other settings
    spi_flash_read_config_reg(&tmp_data);
    tmp_data |= (uint32_t) (spi_flash_read_status_reg() << 16);
    tmp_data &= ~0xFF;
    tmp_data |= data;

    return spi_flash_write_status_config_reg(tmp_data);
}


/*
 * SPI Flash ID functions
 ****************************************************************************************
 */

int8_t spi_flash_read_rems_id(uint16_t *data)
{
    SPI_FLASH_ENABLE_POWER_PIN();

    // Check if SPI Flash is ready
    int8_t status = spi_flash_is_busy();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Send command
    spi_set_bitmode(SPI_MODE_16BIT);
    spi_cs_low();
    spi_access(SPI_FLASH_OP_REMS << 8);
    // Dummy SPI transaction to send (A23-A0)
    spi_access(0x0000);
    // SPI transaction to read Manufacturer Id & Device ID
    *data = spi_access(0x0000);

    spi_cs_high();

    return SPI_FLASH_ERR_OK;
}

int8_t spi_flash_read_unique_id(uint64_t *data)
{
    SPI_FLASH_ENABLE_POWER_PIN();

    // Check if SPI Flash is ready
    int8_t status = spi_flash_is_busy();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Send command
    spi_set_bitmode(SPI_MODE_8BIT);
    spi_cs_low();

    // Send Read Unique ID command
    spi_access(SPI_FLASH_OP_RUID);

    // Dummy transaction for the 4 dummy bytes
    spi_set_bitmode(SPI_MODE_32BIT);
    spi_access(0x0000);

    // Get the high part of unique id
    *data = ((uint64_t) spi_access(0x0000) << 32);
    // Get the low part of unique id
    *data |= (uint64_t) spi_access(0x0000);

    spi_cs_high();

    return SPI_FLASH_ERR_OK;
}

int8_t spi_flash_read_jedec_id(uint32_t *data)
{
    SPI_FLASH_ENABLE_POWER_PIN();

    // Check if SPI Flash is ready
    int8_t status = spi_flash_is_busy();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Send command
    spi_set_bitmode(SPI_MODE_8BIT);
    spi_cs_low();

    // Send Read Unique ID command
    spi_access(SPI_FLASH_OP_RDID);

    // Get the JEDEC ID
    *data =  ((uint8_t) spi_access(0x0000)) << 16;
    // Get device information byte 1
    *data |= ((uint8_t) spi_access(0x0000)) << 8;
    // Get device information byte 2
    *data |= ((uint8_t) spi_access(0x0000)) << 0;

    spi_cs_high();
    return SPI_FLASH_ERR_OK;
}


/*
 * SPI Flash memory protection functions
 ****************************************************************************************
 */

int8_t spi_flash_configure_memory_protection(uint8_t data)
{
    int8_t status = SPI_FLASH_ERR_OK;
#if USE_SPI_FLASH_MEM_PROTECT_USING_STATUS_REG1
    SPI_FLASH_ENABLE_POWER_PIN();

    // Check if SPI Flash is ready
    status = spi_flash_is_busy();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Send Write Enable instruction
    status = spi_flash_write_enable(SPI_FLASH_OP_WREN);
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    status = spi_flash_write_status_reg((spi_flash_read_status_reg() & (~SPI_FLASH_MEM_PROT_MASK)) |
                                        ((data) & (SPI_FLASH_MEM_PROT_MASK)));
#endif // USE_SPI_FLASH_MEM_PROTECT_USING_STATUS_REG1
    return status;
}


/*
 * SPI Flash Erase functions
 ****************************************************************************************
 */
int8_t spi_flash_page_erase(uint32_t page_address)
{
    SPI_FLASH_ENABLE_POWER_PIN();

    // Check if SPI Flash is ready
    int8_t status = spi_flash_is_busy();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Send Write Enable instruction
    status = spi_flash_write_enable(SPI_FLASH_OP_WREN);
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Send command
    spi_set_bitmode(SPI_MODE_32BIT);
    spi_transaction(((uint32_t) (SPI_FLASH_OP_PE) << 24) | page_address);

    return spi_flash_wait_till_ready();
}

int8_t spi_flash_block_erase(uint32_t address, spi_flash_op_t erase_op)
{
    SPI_FLASH_ENABLE_POWER_PIN();

    // Check if SPI Flash is ready
    int8_t status = spi_flash_is_busy();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Send Write Enable instruction
    status = spi_flash_write_enable(SPI_FLASH_OP_WREN);
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Send command
    spi_set_bitmode(SPI_MODE_32BIT);
    spi_transaction((erase_op << 24) | address);

    return spi_flash_wait_till_ready();
}

int8_t spi_flash_block_erase_no_wait(uint32_t address, spi_flash_op_t erase_op)
{
    SPI_FLASH_ENABLE_POWER_PIN();

    // Check if SPI Flash is ready
    int8_t status = spi_flash_is_busy();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Send Write Enable instruction
    status = spi_flash_write_enable(SPI_FLASH_OP_WREN);
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Send command
    spi_set_bitmode(SPI_MODE_32BIT);
    spi_transaction((erase_op << 24) | address);

    return SPI_FLASH_ERR_OK;
}

int8_t spi_flash_chip_erase(void)
{
    SPI_FLASH_ENABLE_POWER_PIN();

    // Check if SPI Flash is ready
    int8_t status = spi_flash_is_busy();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Send Write Enable instruction
    status = spi_flash_write_enable(SPI_FLASH_OP_WREN);
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Send command
    spi_set_bitmode(SPI_MODE_8BIT);
    spi_transaction(SPI_FLASH_OP_CE);

    return spi_flash_wait_till_ready();
}

int8_t spi_flash_chip_erase_forced(void)
{
    // Check if SPI Flash is ready
    int8_t status = spi_flash_is_busy();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Unprotect the whole memory to force chip erase
    status = spi_flash_configure_memory_protection(SPI_FLASH_MEM_PROT_NONE);
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    return spi_flash_chip_erase();
}

int8_t spi_flash_erase_fail(void)
{
    uint32_t security_reg_val;
    spi_flash_read_security_reg(&security_reg_val);
    if ((security_reg_val >> SPI_FLASH_SCR_EFAIL) & 0x01)
    {
        return SPI_FLASH_ERR_ERASE_ERROR;
    }
    return SPI_FLASH_ERR_OK;
}

/*
 * SPI Flash Program functions
 ****************************************************************************************
 */
int8_t spi_flash_page_program(uint8_t *wr_data_ptr, uint32_t address, uint16_t size)
{
    SPI_FLASH_ENABLE_POWER_PIN();

    // Check if SPI Flash is ready
    int8_t status = spi_flash_is_busy();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    uint16_t temp_size = size;

    // Send Write Enable instruction
    status = spi_flash_write_enable(SPI_FLASH_OP_WREN);
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Check for max page size
    if (temp_size > SPI_FLASH_PAGE_SIZE)
    {
        temp_size = SPI_FLASH_PAGE_SIZE;
    }

    // Send command
    spi_set_bitmode(SPI_MODE_32BIT);
    spi_cs_low();
    spi_access((SPI_FLASH_OP_PP << 24) | address);

    // Send data
    spi_set_bitmode(SPI_MODE_8BIT);
    while(temp_size > 0)
    {
        spi_access(*wr_data_ptr++);
        temp_size--;
    }

    spi_cs_high();

    return spi_flash_wait_till_ready();
}

int8_t spi_flash_page_program_buffer(uint8_t *wr_data_ptr, uint32_t address, uint16_t size)
{
    SPI_FLASH_ENABLE_POWER_PIN();

    // Check if SPI Flash is ready
    int8_t status = spi_flash_is_busy();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    uint16_t temp_size = size;

    // Send Write Enable instruction
    status = spi_flash_write_enable(SPI_FLASH_OP_WREN);
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Check for max page size
    if (temp_size > SPI_FLASH_PAGE_SIZE)
    {
        temp_size = SPI_FLASH_PAGE_SIZE;
    }

    // Send command
    spi_set_bitmode(SPI_MODE_32BIT);
    spi_cs_low();
    spi_access((SPI_FLASH_OP_PP << 24) | address);

    // Send data
    spi_set_bitmode(SPI_MODE_8BIT);
    spi_send(wr_data_ptr, temp_size, SPI_OP_BLOCKING);
    spi_cs_high();

    return spi_flash_wait_till_ready();
}

#if defined (CFG_SPI_DMA_SUPPORT)
int8_t spi_flash_page_program_dma(uint8_t *wr_data_ptr, uint32_t address, uint16_t size)
{
    SPI_FLASH_ENABLE_POWER_PIN();

    // Check if SPI Flash is ready
    int8_t status = spi_flash_is_busy();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    uint16_t temp_size = size;

    // Send Write Enable instruction
    status = spi_flash_write_enable(SPI_FLASH_OP_WREN);
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Check for max page size
    if (temp_size > SPI_FLASH_PAGE_SIZE)
    {
        temp_size = SPI_FLASH_PAGE_SIZE;
    }

    // Send command
    spi_set_bitmode(SPI_MODE_32BIT);
    spi_cs_low();
    spi_access((SPI_FLASH_OP_PP << 24) | address);

    // Send data
    spi_set_bitmode(SPI_MODE_8BIT);
    spi_send(wr_data_ptr, temp_size, SPI_OP_DMA);
    // Wait for DMA to finish
    spi_wait_dma_write_to_finish();
    spi_cs_high();

    return spi_flash_wait_till_ready();
}
#endif

int8_t spi_flash_write_data(uint8_t *wr_data_ptr, uint32_t address,
                            uint32_t size, uint32_t *actual_size)
{
    int8_t status = SPI_FLASH_ERR_OK;
    uint32_t bytes_written;
    uint32_t feasible_size = size;
    uint32_t currentAddress = address;
    uint32_t currentEndOfPage = (currentAddress / SPI_FLASH_PAGE_SIZE + 1) * SPI_FLASH_PAGE_SIZE - 1;
    uint32_t bytes_left_to_send;

    spi_set_bitmode(SPI_MODE_8BIT);

    // Limit to the maximum count of bytes that can be written to the specific Flash
    if (size > spi_flash_cfg_env.chip_size - address)
    {
        feasible_size = spi_flash_cfg_env.chip_size - address;
    }

    bytes_left_to_send = feasible_size;
    bytes_written = 0;

    while (bytes_written < feasible_size)
    {
        // Limit the transaction to the upper limit of the current page
        if (currentAddress + bytes_left_to_send > currentEndOfPage)
        {
            bytes_left_to_send = currentEndOfPage - currentAddress + 1;
        }

        // Program page
        status = spi_flash_page_program(wr_data_ptr + bytes_written, currentAddress, bytes_left_to_send);
        if (status != SPI_FLASH_ERR_OK)
        {
            return status;
        }

        bytes_written += bytes_left_to_send;
        // Set address to point to the first memory position of the next page
        currentAddress = currentEndOfPage + 1;
        currentEndOfPage += SPI_FLASH_PAGE_SIZE;
        bytes_left_to_send = feasible_size - bytes_written;
    }
    *actual_size = bytes_written;
    return status;
}

int8_t spi_flash_write_data_buffer(uint8_t *wr_data_ptr, uint32_t address,
                                   uint32_t size, uint32_t *actual_size)
{
    int8_t status = SPI_FLASH_ERR_OK;
    uint32_t bytes_written;
    uint32_t feasible_size = size;
    uint32_t currentAddress = address;
    uint32_t currentEndOfPage = (currentAddress / SPI_FLASH_PAGE_SIZE + 1) * SPI_FLASH_PAGE_SIZE - 1;
    uint32_t bytes_left_to_send;

    spi_set_bitmode(SPI_MODE_8BIT);

    // Limit to the maximum count of bytes that can be written to the specific Flash
    if (size > spi_flash_cfg_env.chip_size - address)
    {
        feasible_size = spi_flash_cfg_env.chip_size - address;
    }

    bytes_left_to_send = feasible_size;
    bytes_written = 0;

    while (bytes_written < feasible_size)
    {
        // Limit the transaction to the upper limit of the current page
        if (currentAddress + bytes_left_to_send > currentEndOfPage)
        {
            bytes_left_to_send = currentEndOfPage - currentAddress + 1;
        }

        // Program page
        status = spi_flash_page_program_buffer(wr_data_ptr + bytes_written, currentAddress, bytes_left_to_send);
        if (status != SPI_FLASH_ERR_OK)
        {
            return status;
        }

        bytes_written += bytes_left_to_send;
        // Set address to point to the first memory position of the next page
        currentAddress = currentEndOfPage + 1;
        currentEndOfPage += SPI_FLASH_PAGE_SIZE;
        bytes_left_to_send = feasible_size - bytes_written;
    }
    *actual_size = bytes_written;
    return status;
}

#if defined (CFG_SPI_DMA_SUPPORT)
int8_t spi_flash_write_data_dma(uint8_t *wr_data_ptr, uint32_t address,
                                uint32_t size, uint32_t *actual_size)
{
    int8_t status = SPI_FLASH_ERR_OK;
    uint32_t bytes_written;
    uint32_t feasible_size = size;
    uint32_t currentAddress = address;
    uint32_t currentEndOfPage = (currentAddress / SPI_FLASH_PAGE_SIZE + 1) * SPI_FLASH_PAGE_SIZE - 1;
    uint32_t bytes_left_to_send;

    spi_set_bitmode(SPI_MODE_8BIT);

    // Limit to the maximum count of bytes that can be written to the specific Flash
    if (size > spi_flash_cfg_env.chip_size - address)
    {
        feasible_size = spi_flash_cfg_env.chip_size - address;
    }

    bytes_left_to_send = feasible_size;
    bytes_written = 0;

    while (bytes_written < feasible_size)
    {
        // Limit the transaction to the upper limit of the current page
        if (currentAddress + bytes_left_to_send > currentEndOfPage)
        {
            bytes_left_to_send = currentEndOfPage - currentAddress + 1;
        }

        // Program page
        status = spi_flash_page_program_dma(wr_data_ptr + bytes_written, currentAddress, bytes_left_to_send);
        if (status != SPI_FLASH_ERR_OK)
        {
            return status;
        }

        bytes_written += bytes_left_to_send;
        // Set address to point to the first memory position of the next page
        currentAddress = currentEndOfPage + 1;
        currentEndOfPage += SPI_FLASH_PAGE_SIZE;
        bytes_left_to_send = feasible_size - bytes_written;
    }
    *actual_size = bytes_written;
    return status;
}
#endif

int8_t spi_flash_page_fill(uint8_t value, uint32_t address, uint16_t size)
{
    SPI_FLASH_ENABLE_POWER_PIN();

    // Check if SPI Flash is ready
    int8_t status = spi_flash_is_busy();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    uint16_t temp_size = size;

    // Send Write Enable instruction
    status = spi_flash_write_enable(SPI_FLASH_OP_WREN);
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Check for max page size
    if (temp_size > SPI_FLASH_PAGE_SIZE)
    {
        temp_size = SPI_FLASH_PAGE_SIZE;
    }

    // Send command
    spi_set_bitmode(SPI_MODE_32BIT);
    spi_cs_low();
    spi_access((SPI_FLASH_OP_PP << 24) | address);

    // Send data
    spi_set_bitmode(SPI_MODE_8BIT);
    while(temp_size > 0)
    {
        spi_access(value);
        temp_size--;
    }

    spi_cs_high();

    return spi_flash_wait_till_ready();
}

int8_t spi_flash_fill(uint8_t value, uint32_t address,
                      uint32_t size, uint32_t *actual_size)
{
    int8_t status;
    uint32_t bytes_written;
    uint32_t feasible_size = size;
    uint32_t currentAddress = address;
    uint32_t currentEndOfPage = (currentAddress / SPI_FLASH_PAGE_SIZE + 1) * SPI_FLASH_PAGE_SIZE - 1;
    uint32_t bytes_left_to_send;

    spi_set_bitmode(SPI_MODE_8BIT);

    // Limit to the maximum count of bytes that can be written to the specific Flash
    if (size > spi_flash_cfg_env.chip_size - address)
    {
        feasible_size = spi_flash_cfg_env.chip_size - address;
    }

    bytes_left_to_send = feasible_size;
    bytes_written = 0;

    while (bytes_written < feasible_size)
    {
        // Limit the transaction to the upper limit of the current page
        if (currentAddress + bytes_left_to_send > currentEndOfPage)
        {
            bytes_left_to_send = currentEndOfPage - currentAddress + 1;
        }
        // Program page
        status = spi_flash_page_fill(value, currentAddress, bytes_left_to_send);
        if (status != SPI_FLASH_ERR_OK)
        {
            return status;
        }
        bytes_written += bytes_left_to_send;
        // Set address to point to the first memory position of the next page
        currentAddress = currentEndOfPage + 1;
        currentEndOfPage += SPI_FLASH_PAGE_SIZE;
        bytes_left_to_send = feasible_size - bytes_written;
    }
    *actual_size = bytes_written;
    return SPI_FLASH_ERR_OK;
}

int8_t spi_flash_program_fail(void)
{
    uint32_t security_reg_val;
    spi_flash_read_security_reg(&security_reg_val);
    if ((security_reg_val >> SPI_FLASH_SCR_PFAIL) & 0x01)
    {
        return SPI_FLASH_ERR_PROG_ERROR;
    }
    return SPI_FLASH_ERR_OK;
}

/*
 * SPI Flash Read functions
 ****************************************************************************************
 */

int8_t spi_flash_read_data(uint8_t *rd_data_ptr, uint32_t address,
                           uint32_t size, uint32_t *actual_size)
{
    SPI_FLASH_ENABLE_POWER_PIN();

    // Check if SPI Flash is ready
    int8_t status = spi_flash_is_busy();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Check that all bytes to be read are located in a valid Flash memory address space
    if (size + address > spi_flash_cfg_env.chip_size)
    {
        *actual_size = spi_flash_cfg_env.chip_size - address;
    }
    else
    {
        *actual_size = size;
    }

    // Send Command
    spi_set_bitmode(SPI_MODE_32BIT);
    spi_cs_low();
    // Send sequencial read from memory Command
    spi_access((SPI_FLASH_OP_READ << 24) | address);

    spi_set_bitmode(SPI_MODE_8BIT);

    // Read data
    for (uint32_t i = 0; i < *actual_size; i++)
    {
        *rd_data_ptr++ = (uint8_t) spi_access(0x0000);
    }

    spi_cs_high();

    return SPI_FLASH_ERR_OK;
}

int8_t spi_flash_read_data_buffer(uint8_t *rd_data_ptr, uint32_t address,
                                  uint32_t size, uint32_t *actual_size)
{
    SPI_FLASH_ENABLE_POWER_PIN();

    // Check if SPI Flash is ready
    int8_t status = spi_flash_is_busy();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Check that all bytes to be read are located in a valid Flash memory address space
    if (size + address > spi_flash_cfg_env.chip_size)
    {
        *actual_size = spi_flash_cfg_env.chip_size - address;
    }
    else
    {
        *actual_size = size;
    }

    // Send Command
    spi_set_bitmode(SPI_MODE_32BIT);
    spi_cs_low();
    // Send sequencial read from memory Command
    spi_access((SPI_FLASH_OP_READ << 24) | address);

    spi_set_bitmode(SPI_MODE_8BIT);

    // Read data
    const uint16_t MAX_SPI_RECEIVE = 0xFFFF;

    for (int i = 0; i < *actual_size / MAX_SPI_RECEIVE; i++)
    {
        spi_receive(rd_data_ptr, MAX_SPI_RECEIVE, SPI_OP_BLOCKING);
        rd_data_ptr += MAX_SPI_RECEIVE;
    }

    uint16_t remaining_len = *actual_size % MAX_SPI_RECEIVE;

    if (remaining_len > 0)
    {
        spi_receive(rd_data_ptr, remaining_len, SPI_OP_BLOCKING);
    }

    spi_cs_high();

    return SPI_FLASH_ERR_OK;
}

#if defined (CFG_SPI_DMA_SUPPORT)
int8_t spi_flash_read_data_dma(uint8_t *rd_data_ptr, uint32_t address,
                               uint32_t size, uint32_t *actual_size)
{
    SPI_FLASH_ENABLE_POWER_PIN();

    // Check if SPI Flash is ready
    int8_t status = spi_flash_is_busy();
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }

    // Check that all bytes to be read are located in a valid Flash memory address space
    if (size + address > spi_flash_cfg_env.chip_size)
    {
        *actual_size = spi_flash_cfg_env.chip_size - address;
    }
    else
    {
        *actual_size = size;
    }

    // Send Command
    spi_set_bitmode(SPI_MODE_32BIT);
    spi_cs_low();
    // Send sequencial read from memory Command
    spi_access((SPI_FLASH_OP_READ << 24) | address);

    spi_set_bitmode(SPI_MODE_8BIT);

    const uint16_t MAX_SPI_RECEIVE = 0xFFFF;

    // Read data
    for (int i = 0; i < *actual_size / MAX_SPI_RECEIVE; i++)
    {
        spi_receive(rd_data_ptr, MAX_SPI_RECEIVE, SPI_OP_DMA);
        // Wait for DMA to finish
        spi_wait_dma_read_to_finish();
        rd_data_ptr += MAX_SPI_RECEIVE;
    }

    uint16_t remaining_len = *actual_size % MAX_SPI_RECEIVE;

    if (remaining_len > 0)
    {
        spi_receive(rd_data_ptr, remaining_len, SPI_OP_DMA);
        // Wait for DMA to finish
        spi_wait_dma_read_to_finish();
    }

    spi_cs_high();

    return SPI_FLASH_ERR_OK;
}
#endif

/*
 * SPI Flash Check Empty functions
 ****************************************************************************************
 */

int8_t spi_flash_is_page_empty(uint32_t page_address)
{
    int8_t status;
    uint32_t read_data[SPI_FLASH_PAGE_SIZE/4];
    uint32_t bytes_read;

    status = spi_flash_read_data((uint8_t *) read_data, page_address, SPI_FLASH_PAGE_SIZE, &bytes_read);
    if (status != SPI_FLASH_ERR_OK)
    {
        return status;
    }
    if (bytes_read != SPI_FLASH_PAGE_SIZE)
    {
        return SPI_FLASH_ERR_READ_ERROR;
    }

    // Check if all data are 0xFF
    for (uint16_t data_cnt = 0; data_cnt < SPI_FLASH_PAGE_SIZE/4; data_cnt++)
    {
        if (read_data[data_cnt] != (0xFFFFFFFF))
            return SPI_FLASH_ERR_NOT_ERASED;
    }

    return SPI_FLASH_ERR_OK;
}

int8_t spi_flash_is_sector_empty(uint32_t sector_address)
{
    int8_t status;

    for (uint16_t i = 0; i < (SPI_FLASH_SECTOR_SIZE / SPI_FLASH_PAGE_SIZE); i++)
    {
        status = spi_flash_is_page_empty((uint32_t)((sector_address & 0xFFFF00) + (i * SPI_FLASH_PAGE_SIZE)));
        if (status != SPI_FLASH_ERR_OK)
        {
            return status;
        }
    }
    return SPI_FLASH_ERR_OK;
}

int8_t spi_flash_is_empty(void)
{
    int8_t status;
    // Calculate the number of sectors
    uint16_t sector_num = (uint16_t) (spi_flash_cfg_env.chip_size / SPI_FLASH_SECTOR_SIZE);

    for (uint16_t i = 0; i < sector_num; i++)
    {
        status = spi_flash_is_sector_empty((uint32_t)(i * SPI_FLASH_SECTOR_SIZE));
        if (status != SPI_FLASH_ERR_OK)
        {
            return status;
        }
    }
    return SPI_FLASH_ERR_OK;
}

/*
 * SPI Flash DA14531 with FLASH_EXTENSIONS specific functions
 *
 * When the DA14531 is in boost mode and the external SPI flash memory is connected
 * to VBAT_H, the memory may not start-up correctly (it becomes no operational) due
 * to the fact that in boost mode the current limit of VBAT_H pin is 50uA. The SPI
 * flash memory supply voltage must be controlled from a dedicated GPIO.
 * Refer to UM-B-151 application note for further details.
 ****************************************************************************************
 */

#if (USE_SPI_FLASH_EXTENSIONS)

static bool is_power_pin_high   __SECTION_ZERO("retention_mem_area0");

static void wait_between_pin_mode_transitions(void)
{
    const int transition_delay_in_us = 100;  // 100 us of delay
    const int transition_delay_repetitions = 2 * transition_delay_in_us;
    // Pin mode transition delay. 200 repetitions are roughly 100us.
    for (volatile int i = 0; i < transition_delay_repetitions; i++);
}

static bool enable_external_spi_flash_power_pin(void)
{
    bool was_pin_already_enabled = false;
#if (USE_SPI_FLASH_CAP_SLOW_CHARGE)
    // The pin may already be enabled when the function is called. In that case it is not necessary to
    // go through the pullup cycle again. Only if the pin is low.
    if (!is_power_pin_high)
    {
        GPIO_ConfigurePin(FLASH_GPIO_POWER_PORT, FLASH_GPIO_POWER_PIN, INPUT_PULLUP, PID_GPIO, true);
        wait_between_pin_mode_transitions();
    }
    else
    {
        was_pin_already_enabled = true;
    }
#endif
    GPIO_ConfigurePin(FLASH_GPIO_POWER_PORT, FLASH_GPIO_POWER_PIN, OUTPUT, PID_GPIO, true);
    is_power_pin_high = true;
    return was_pin_already_enabled;
}

static void disable_external_spi_flash_power_pin(void)
{
#if (USE_SPI_FLASH_CAP_SLOW_DISCHARGE)
    // The pin may already be disabled when the function is called. In that case it is not necessary to
    // go through the pulldown cycle again. Only if the pin is high.
    if (is_power_pin_high)
    {
        GPIO_ConfigurePin(FLASH_GPIO_POWER_PORT, FLASH_GPIO_POWER_PIN, INPUT_PULLDOWN, PID_GPIO, true);
        wait_between_pin_mode_transitions();
    }
#endif
    GPIO_ConfigurePin(FLASH_GPIO_POWER_PORT, FLASH_GPIO_POWER_PIN, OUTPUT, PID_GPIO, false);
    is_power_pin_high = false;
}

#endif // (USE_SPI_FLASH_EXTENSIONS)

bool spi_flash_enable_power_pin(void)
{
#if (USE_SPI_FLASH_EXTENSIONS)
    bool is_pin_already_enabled = enable_external_spi_flash_power_pin(); //This will configure the pin as well
    if (!is_pin_already_enabled)
    {
        // Flashes may need some time after power on to reach fully operational status
        // 1000 us of delay need roughly 2000 repetitions
        const int delay_in_us = 1000;
        const int repetitions = 2 * delay_in_us;
#if (USE_WDOG) || defined (__NON_BLE_EXAMPLE__)
        SetWord16(WATCHDOG_REG, WATCHDOG_REG_RESET);
#endif
        for (volatile int i = 0; i < repetitions; i++);
#if (USE_WDOG) || defined (__NON_BLE_EXAMPLE__)
        SetWord16(WATCHDOG_REG, WATCHDOG_REG_RESET);
#endif
    }
    return is_pin_already_enabled;
#else
    return true;
#endif
}

void spi_flash_disable_power_pin(void)
{
#if (USE_SPI_FLASH_EXTENSIONS)
    disable_external_spi_flash_power_pin();
#endif
}

bool spi_flash_get_power_pin_status(void)
{
#if (USE_SPI_FLASH_EXTENSIONS)
    return is_power_pin_high;
#else
    // Return a dummy value
    return false;
#endif
}

/*
 * SPI Flash DA14586 specific functions
 ****************************************************************************************
 */

#if defined (__DA14586__)
void power_down_da14586_flash(void)
{
    // Power up peripherals' power domain
    SetBits16(PMU_CTRL_REG, PERIPH_SLEEP, 0);
    while (!(GetWord16(SYS_STAT_REG) & PER_IS_UP));

    // Enable the pads
    SetBits16(SYS_CTRL_REG, PAD_LATCH_EN, 1);

    // Configure internal SPI Flash GPIOs
    GPIO_ConfigurePin(SPI_EN_PORT, SPI_EN_PIN, OUTPUT, PID_SPI_EN, true);
    GPIO_ConfigurePin(SPI_CLK_PORT, SPI_CLK_PIN, OUTPUT, PID_SPI_CLK, false);
    GPIO_ConfigurePin(SPI_DO_PORT, SPI_DO_PIN, OUTPUT, PID_SPI_DO, false);
    GPIO_ConfigurePin(SPI_DI_PORT, SPI_DI_PIN, INPUT, PID_SPI_DI, false);

    // Initialize SPI driver
    spi_cfg_t spi_flash_cfg = { .spi_ms = SPI_MS_MODE_MASTER,
                                .spi_cp = SPI_CP_MODE_0,
                                .spi_speed = SPI_SPEED_MODE_2MHz,
                                .spi_wsz = SPI_MODE_8BIT,
                                .spi_cs = SPI_CS_0,
                                .cs_pad.port = SPI_EN_PORT,
                                .cs_pad.pin = SPI_EN_PIN
                                };

    spi_initialize(&spi_flash_cfg);

    // Power up flash
    spi_flash_release_from_power_down();

    // Power down flash
    spi_flash_power_down();

    // Release SPI controller
    spi_release();

    // Release internal SPI Flash GPIOs
    GPIO_ConfigurePin(SPI_EN_PORT, SPI_EN_PIN, OUTPUT, PID_GPIO, true);
    GPIO_ConfigurePin(SPI_CLK_PORT, SPI_CLK_PIN, INPUT_PULLDOWN, PID_GPIO, false);
    GPIO_ConfigurePin(SPI_DO_PORT, SPI_DO_PIN, INPUT_PULLDOWN, PID_GPIO, false);
    GPIO_ConfigurePin(SPI_DI_PORT, SPI_DI_PIN, INPUT_PULLDOWN, PID_GPIO, false);
}
#endif
