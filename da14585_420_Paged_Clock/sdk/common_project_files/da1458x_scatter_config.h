/**
 ****************************************************************************************
 *
 * @file da1458x_scatter_config.h
 *
 * @brief Common scatter file definition file.
 *
 * Copyright (C) 2014-2020 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */

#ifndef _DA1458X_SCATTER_CONFIG_H_
#define _DA1458X_SCATTER_CONFIG_H_

/******************************************
 * DO NOT ALTER
 ******************************************/

// Convert an even integer number to the next odd one
#ifdef ARM_SCATTERFILE
    #define EVEN_TO_NEXT_ODD_NUM(x)      ((x) OR 0x01)
#else
    #define EVEN_TO_NEXT_ODD_NUM(x)      ((x) | 0x01)
#endif

#if (CFG_MAX_CONNECTIONS <= CFG_CON)
    #define BLE_CONNECTION_MAX_USER     (CFG_MAX_CONNECTIONS)
#else
    #define BLE_CONNECTION_MAX_USER     (CFG_CON)
    #error "Config error: the number of supported connections is exceeded."
#endif

/******************************************
 * Calculation of MIN and MAX payloads to
 * be used in error checking during the
 * compilation stage.
 ******************************************/
#if !defined (ARM_SCATTERFILE)
    #if defined (CFG_PRODUCTION_TEST)
        #define MAX_PAYLOAD_LENGTH_BY_SPEC   (255)
        #define MIN_PAYLOAD_LENGTH_BY_SPEC   (37)
    #else
        #define MAX_PAYLOAD_LENGTH_BY_SPEC   (251)
        #define MIN_PAYLOAD_LENGTH_BY_SPEC   (27)
    #endif

    #if !((CFG_MAX_TX_PACKET_LENGTH >= MIN_PAYLOAD_LENGTH_BY_SPEC) && (CFG_MAX_TX_PACKET_LENGTH <= MAX_PAYLOAD_LENGTH_BY_SPEC))
        #error "Config error: invalid value for CFG_MAX_TX_PACKET_LENGTH."
    #endif
    #if !((CFG_MAX_RX_PACKET_LENGTH >= MIN_PAYLOAD_LENGTH_BY_SPEC) && (CFG_MAX_RX_PACKET_LENGTH <= MAX_PAYLOAD_LENGTH_BY_SPEC))
        #error "Config error: invalid value for CFG_MAX_RX_PACKET_LENGTH."
    #endif
#endif

/******************************************
 * Definition of values for compilation and
 * linking stage.
 ******************************************/

#define __SCT_CFG_MAX_TX_PACKET_LENGTH       EVEN_TO_NEXT_ODD_NUM(CFG_MAX_TX_PACKET_LENGTH)
#define __SCT_CFG_MAX_RX_PACKET_LENGTH       EVEN_TO_NEXT_ODD_NUM(CFG_MAX_RX_PACKET_LENGTH)

#define __SCT__EM_BLE_TX_BUFFER_COUNT       ( (CFG_CON * 3) + (CFG_CON + 3))
#define __SCT__REG_BLE_EM_TX_BUFFER_SIZE    (262)


#if (BLE_CONNECTION_MAX_USER == 1)
    #define __SCT_BLE_TX_DESC_DATA          (5)
#else
    #define __SCT_BLE_TX_DESC_DATA          (BLE_CONNECTION_MAX_USER * 3)
#endif
#define __SCT_BLE_TX_DESC_CNTL              (BLE_CONNECTION_MAX_USER)
#define __SCT_BLE_TX_DESC_ADV               (3)
#define __SCT_EM_BLE_TX_BUFFER_COUNT        (__SCT_BLE_TX_DESC_DATA + __SCT_BLE_TX_DESC_CNTL + __SCT_BLE_TX_DESC_ADV)
#define __SCT_REG_BLE_EM_TX_BUFFER_SIZE     (__SCT_CFG_MAX_TX_PACKET_LENGTH + 4 + 7) // user defined


#define __SCT_EM_BLE_RX_BUFFER_COUNT        (8)
#define __SCT__REG_BLE_EM_RX_BUFFER_SIZE    (262)
#define __SCT_REG_BLE_EM_RX_BUFFER_SIZE     (__SCT_CFG_MAX_RX_PACKET_LENGTH + 4 + 7) // user defined

#if defined (__DA14531__)
    #define __SCT_EM_BLE_TX_BUFFER_OFFSET   (0x0000033E)
#else
    #define __SCT_EM_BLE_TX_BUFFER_OFFSET   (0x0000050A)
#endif

#define __SCT__EM_BLE_RX_BUFFER_OFFSET  (__SCT_EM_BLE_TX_BUFFER_OFFSET + (__SCT__EM_BLE_TX_BUFFER_COUNT * __SCT__REG_BLE_EM_TX_BUFFER_SIZE))
#define __SCT_EM_BLE_RX_BUFFER_OFFSET   (__SCT_EM_BLE_TX_BUFFER_OFFSET + (__SCT_EM_BLE_TX_BUFFER_COUNT  * __SCT_REG_BLE_EM_TX_BUFFER_SIZE))

#define __SCT__EM_BLE_CNXADD_OFFSET     (__SCT__EM_BLE_RX_BUFFER_OFFSET + (__SCT_EM_BLE_RX_BUFFER_COUNT * __SCT__REG_BLE_EM_RX_BUFFER_SIZE))
#define __SCT_EM_BLE_CNXADD_OFFSET      (__SCT_EM_BLE_RX_BUFFER_OFFSET  + (__SCT_EM_BLE_RX_BUFFER_COUNT * __SCT_REG_BLE_EM_RX_BUFFER_SIZE))

#define __SCT_BD_ADDR_LEN       (6)
#define __SCT__EM_BLE_END       (__SCT__EM_BLE_CNXADD_OFFSET + __SCT_BD_ADDR_LEN)
#define __SCT_EM_BLE_END        (__SCT_EM_BLE_CNXADD_OFFSET  + __SCT_BD_ADDR_LEN)


#define __SCT_OFFSET_DIFF   (__SCT__EM_BLE_END - __SCT_EM_BLE_END)

#if defined (__DA14531__)
    #define __SCT_OLD_BLE_BASE  (0x07FC9C00) // 1K aligned
#else
    #define __SCT_OLD_BLE_BASE  (0x07FD4400) // 1K aligned
#endif


#ifdef ARM_SCATTERFILE
    #define __SCT_BLE_BASE      ((__SCT_OLD_BLE_BASE + __SCT_OFFSET_DIFF) AND (0xFFFFC00))
#else
    #define __SCT_BLE_BASE      ((__SCT_OLD_BLE_BASE + __SCT_OFFSET_DIFF) & (0xFFFFC00))
#endif


/*
 * Calculation of retained heap sizes
 ****************************************************************************************
 */

// Automatically calculated non retained heap size
#if (BLE_CONNECTION_MAX_USER == 1)
    #define __SCT_AUTO_HEAP_NON_RET_SIZE    1024
#else
    #define __SCT_AUTO_HEAP_NON_RET_SIZE    2048
#endif

// Automatically calculated ENV heap size (macros used by scatter file)
// Calculation formula is: ENV heap size = (sizeof(struct llc_env_tag)   + KE_HEAP_MEM_RESERVED +
//                                          sizeof(struct gapc_env_tag)  + KE_HEAP_MEM_RESERVED +
//                                          sizeof(struct gattc_env_tag) + KE_HEAP_MEM_RESERVED +
//                                          sizeof(struct l2cc_env_tag)  + KE_HEAP_MEM_RESERVED) *
//                                          BLE_CONNECTION_MAX_USER

#if defined (__DA14531__)
    #define __SCT_AUTO_HEAP_ENV_SIZE    (((244 + 4) + (248 + 4) + (148 + 4) + (28 + 4)) * BLE_CONNECTION_MAX_USER) // only for DA14531
#else
    #define __SCT_AUTO_HEAP_ENV_SIZE    (((200 + 4) + (244 + 4) + (128 + 4) + (28 + 4)) * BLE_CONNECTION_MAX_USER) // only for DA14585/586
#endif

// Automatically calculated DB heap size
#define __SCT_AUTO_HEAP_DB_SIZE     1024

// Automatically calculated MSG heap size
#define __SCT_AUTO_HEAP_MSG_SIZE    ( 256 * (BLE_CONNECTION_MAX_USER + 1)           \
                                        + 80 * BLE_CONNECTION_MAX_USER              \
                                        + 96 * (2 * BLE_CONNECTION_MAX_USER + 1)    \
                                      + 256 + 256 * BLE_CONNECTION_MAX_USER         \
                                    )

#define __SCT_ALIGN4_UP(len)        ((((len) + 3) / 4) * 4)
// Align up to a 4 byte boundary + RWIP_HEAP_HEADER
#define __SCT_CALC_HEAP_LEN(len)    (__SCT_ALIGN4_UP(len) + 12)

//
// Check user settings
//

/// Not retained heap
#ifndef NON_RET_HEAP_SZ
    #define __SCT_HEAP_NON_RET_SIZE      __SCT_CALC_HEAP_LEN( __SCT_AUTO_HEAP_NON_RET_SIZE )// in bytes
#else
    #define __SCT_HEAP_NON_RET_SIZE      __SCT_CALC_HEAP_LEN( NON_RET_HEAP_SZ )             // in bytes
#endif

/// Env Heap size
#ifndef ENV_HEAP_SZ
    #define __SCT_HEAP_ENV_SIZE         __SCT_CALC_HEAP_LEN( __SCT_AUTO_HEAP_ENV_SIZE ) // in bytes
#else
    #define __SCT_HEAP_ENV_SIZE         __SCT_CALC_HEAP_LEN( ENV_HEAP_SZ )              // in bytes
#endif

/// DB Heap size
#ifndef DB_HEAP_SZ
    #define __SCT_HEAP_DB_SIZE          __SCT_CALC_HEAP_LEN( __SCT_AUTO_HEAP_DB_SIZE )     // in bytes
#else
    #define __SCT_HEAP_DB_SIZE          __SCT_CALC_HEAP_LEN( DB_HEAP_SZ )                  // in bytes
#endif

/// Msg Heap size
#ifndef MSG_HEAP_SZ
    #define __SCT_HEAP_MSG_SIZE         __SCT_CALC_HEAP_LEN( __SCT_AUTO_HEAP_MSG_SIZE )  // in bytes
#else
    #define __SCT_HEAP_MSG_SIZE         __SCT_CALC_HEAP_LEN( MSG_HEAP_SZ )               // in bytes
#endif

// The total size of the retained heap memory
#define RET_HEAP_SIZE           ( __SCT_HEAP_ENV_SIZE + __SCT_HEAP_DB_SIZE + __SCT_HEAP_MSG_SIZE )

// Parameters to calculate the size of RET_DATA_UNINIT_RAND_STATE execution region (used by scatter file)
#if defined (__DA14531__)

    // sizeof(trng_state)
    #define RET_DATA_UNINIT_TRNG_STATE_SIZE         (4)

    // chacha20.c - sizeof(struct chacha20_state)
    //
    // Note: The variable must be placed in retained RAM area.
    //       The variable must belong to uninitialized RAM area due to
    //       the fact that it must hold its previous value when the system
    //       re-runs the Reset handler and the TRNG mechanism is not
    //       re-triggered.
    #define RET_DATA_UNINIT_CHACHA_STATE_SIZE       (8 + (4 * 4) + (16 * 4) + (1 + 7))

#endif // (__DA14531__)

// ROM data base address in RAM
#if defined (__DA14531__)
    #define ROM_DATA_BASE_ADDR      (0x07FCB900)
#else
    #define ROM_DATA_BASE_ADDR      (0x07FD7600)
#endif

#endif // _DA1458X_SCATTER_CONFIG_H_
