/**
 ****************************************************************************************
 *
 * @file GCC/boot.h
 *
 * @brief Declarations of the linker-defined symbols for GNU C compiler (gcc).
 *
 * Copyright (C) 2018-2022 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */

#ifndef _BOOT_H_
#define _BOOT_H_

#include <stdint.h>

extern const uint32_t __ER_IROM3_BASE__[];
#define CODE_AREA_BASE      ((uint32_t)__ER_IROM3_BASE__)

extern const uint32_t __code_area_end__[];
#define CODE_AREA_END       ((uint32_t)__code_area_end__)
#define CODE_AREA_LENGTH    (CODE_AREA_END - CODE_AREA_BASE)

extern const uint32_t __retention_mem_area_uninit_start__[];
#define RET_MEM_BASE        ((uint32_t)__retention_mem_area_uninit_start__)

extern const uint32_t __heap_mem_area_not_ret_start__[];
#define NON_RET_HEAP_BASE   ((uint32_t)__heap_mem_area_not_ret_start__)

extern const uint32_t __heap_mem_area_not_ret_end__[];
#define NON_RET_HEAP_END   ((uint32_t)__heap_mem_area_not_ret_end__)
#define NON_RET_HEAP_LENGTH (NON_RET_HEAP_END - NON_RET_HEAP_BASE)

extern const uint32_t __db_heap_start__[];
#define DB_HEAP_BASE       ((uint32_t)__db_heap_start__)

extern const uint32_t __db_heap_end__[];
#define DB_HEAP_END        ((uint32_t)__db_heap_end__)
#define DB_HEAP_LENGTH     (DB_HEAP_END - DB_HEAP_BASE)

#endif // _BOOT_H_
