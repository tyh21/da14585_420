/**
 ****************************************************************************************
 *
 * @file user_custs1_impl.c
 *
 * @brief Peripheral project Custom1 Server implementation source code.
 *
 * Copyright (C) 2015-2019 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "gpio.h"
#include "app_api.h"
#include "app.h"
#include "prf_utils.h"
#include "uart_utils.h"
#include "custs1.h"
#include "custs1_task.h"
#include "user_custs1_def.h"
#include "user_custs1_impl.h"
#include "user_periph_setup.h"
#include "user_callback_config.h"
#include "ImageData.h"
#include "etime.h"
#include "crc32.h"
#include "app.h"
#include "app_bass.h"
#include "battery.h"
#include "user_ota.h"
#include "fonts.h"
#include "GUI_Paint.h"
#include "lunar.h"
#include "calendar_display.h"
#include "analog_clock.h"
#include "co_bt.h"
#include "ImageData.h"
#include "EPD_2in13_V2.h"
#include "arch.h"
#include "rwip.h"
#include "arch_system.h"

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */
#define APP_PERIPHERAL_CTRL_TIMER_DELAY 10
#define APP_PERIPHERAL_CTRL_TIMER_DELAY_MINUTES 6000
#define Time_To_Refresh 0

#define IMG_HEADER_SIGNATURE1 0x70
#define IMG_HEADER_SIGNATURE2 0x55
#define IMG_HEADER_VALID 0x55
#define IMG_HEADER_VALID 0x55
#define IMG_HEADER_ADDRESS 0x20000
#define LOGIC_WIDTH 400
#define LOGIC_HEIGHT 300
#define FULL_BUFFER_SIZE (LOGIC_WIDTH * LOGIC_HEIGHT / 8)


// 添加显示模式枚举
typedef enum {
    DISPLAY_MODE_TIME = 0,    // 时间显示模式
    DISPLAY_MODE_CALENDAR = 1, // 日历显示模式
    DISPLAY_MODE_CALENDAR_ANALOG = 2 // 日历显示模式（模拟时钟）
} display_mode_t;

// 添加全局变量来跟踪上次更新时间（用于判断是否需要强制重绘）
static uint32_t last_update_time __SECTION_ZERO("retention_mem_area0");
static uint8_t last_minute __SECTION_ZERO("retention_mem_area0");

/// Image header
typedef struct
{
    /// Signature
    uint8_t signature[2];
    /// Valid; set to STATUS_VALID_IMAGE at the end of the image update
    uint8_t validflag;
    /// ID to determine which image is the newest one
    uint8_t imageid;
    /// Image size
    uint32_t code_size;
    /// Image CRC
    uint32_t CRC;
} img_header_t;
img_header_t imgheader __SECTION_ZERO("retention_mem_area0");
ke_msg_id_t timer_used __SECTION_ZERO("retention_mem_area0");      //@RETENTION MEMORY
uint16_t indication_counter __SECTION_ZERO("retention_mem_area0"); //@RETENTION MEMORY
uint16_t non_db_val_counter __SECTION_ZERO("retention_mem_area0"); //@RETENTION MEMORY
#define epd_buffer_size (EPD_2IN13_V2_WIDTH * EPD_2IN13_V2_HEIGHT / 8)
//#define buffer_size (EPD_2IN13_V2_WIDTH * EPD_2IN13_V2_HEIGHT / 4)
uint32_t byte_pos __SECTION_ZERO("retention_mem_area0");
//uint8_t epd_buffer[buffer_size] __SECTION_ZERO("retention_mem_area0");
uint16_t index __SECTION_ZERO("retention_mem_area0");
uint8_t step __SECTION_ZERO("retention_mem_area0");
ke_msg_id_t timer_used_min __SECTION_ZERO("retention_mem_area0"); //@RETENTION MEMORY
uint32_t current_unix_time __SECTION_ZERO("retention_mem_area0");
uint8_t time_offset __SECTION_ZERO("retention_mem_area0");
uint16_t time_refresh_count __SECTION_ZERO("retention_mem_area0");
uint8_t isconnected __SECTION_ZERO("retention_mem_area0");
tm_t g_tm __SECTION_ZERO("retention_mem_area0");
uint8_t is_part __SECTION_ZERO("retention_mem_area0");
char buf[50];
uint8_t buf2[50];
void bls_att_pushNotifyData(uint16_t attHandle, uint8_t *p, uint8_t len);
void display(void);
void do_time_show(void);
uint8_t dev_id __SECTION_ZERO("retention_mem_area0");
static uint8_t full_image_buffer[FULL_BUFFER_SIZE];

static void spi_flash_peripheral_init(void)
{
    // Release the SPI flash memory from power down
    spi_flash_release_from_power_down();

    // Disable the SPI flash memory protection (unprotect all sectors)
    spi_flash_configure_memory_protection(SPI_FLASH_MEM_PROT_NONE);

    // Try to auto-detect the SPI flash memory
    spi_flash_auto_detect(&dev_id);
    EPD_CS_H;
}

// 定义图片尺寸和缓冲区大小
#define IMAGE_WIDTH  70
#define IMAGE_HEIGHT 70
#define IMAGE_BUFFER_SIZE ((IMAGE_WIDTH * IMAGE_HEIGHT + 7) / 8)
 // 定义图片缓冲区
UBYTE Image_Buffer[IMAGE_BUFFER_SIZE];
 // 声明在 image_data.c 中定义的图片数据
//extern const unsigned char custom_image[]; 
void DisplayCustomImage(void)
 {
    Paint_NewImage(full_image_buffer,IMAGE_WIDTH, IMAGE_HEIGHT, ROTATE_0, WHITE);
    // 3. 选择当前要操作的图像缓冲区
    Paint_SelectImage(Image_Buffer);
    Paint_Clear(WHITE); // 清空为白色背景
    Paint_DrawBitMap(gImage_heavy_rain_32);
    EPD_2IN13_V2_Display(Image_Buffer);
}
 

// 添加全局变量来存储当前显示模式
uint8_t current_display_mode __SECTION_ZERO("retention_mem_area0");  // = DISPLAY_MODE_TIME;

void do_time_show_diff(void)
{
// 定义图片绘制的坐标和尺寸
const UWORD img_x = 210; // 图片绘制的起始X坐标
const UWORD img_y = 30;  // 图片绘制的起始Y坐标
const UWORD img_w = 70;  // 图片宽度
const UWORD img_h = 70;  // 图片高度
Paint_NewImage(full_image_buffer,EPD_2IN13_V2_WIDTH, EPD_2IN13_V2_HEIGHT, 270, WHITE);
            //Paint_SelectImage(epd_buffer);
            Paint_SetMirroring(MIRROR_VERTICAL);
            Paint_Clear(WHITE);
            
            sprintf(buf, "%d-%02d-%02d", g_tm.tm_year + YEAR0, g_tm.tm_mon + 1, g_tm.tm_mday);                   //年月日
            EPD_DrawUTF8(5, 1, 1, buf, EPD_ASCII_11X16, EPD_FontUTF8_16x16, BLACK, WHITE);
            sprintf(buf, "星期%s", WEEKCN[g_tm.tm_wday]);                                                        //星期
            EPD_DrawUTF8(5 + 125, 1, 1, buf, EPD_ASCII_11X16, EPD_FontUTF8_16x16, BLACK, WHITE);
            if (g_tm.tm_hour<10){
                sprintf(buf, "%01d", g_tm.tm_hour);
                EPD_DrawUTF8(10, 20 + 2, 5, buf, EPD_40X80_TABLE, EPD_FontUTF8_24x24, BLACK, WHITE);
                EPD_DrawUTF8(10 + 86 - 50, 20 + 2, 5, ":", EPD_40X80_TABLE, EPD_FontUTF8_24x24, BLACK, WHITE);
                sprintf(buf, "%02d", g_tm.tm_min);
                EPD_DrawUTF8(10 + 86 + 20-30, 20 + 2, 5, buf, EPD_40X80_TABLE, EPD_FontUTF8_24x24, BLACK, WHITE); 
            }else {
               sprintf(buf, "%02d", g_tm.tm_hour);
                EPD_DrawUTF8(10, 20 + 2, 5, buf, EPD_40X80_TABLE, EPD_FontUTF8_24x24, BLACK, WHITE);
                EPD_DrawUTF8(10 + 86 - 10, 20 + 2, 5, ":", EPD_40X80_TABLE, EPD_FontUTF8_24x24, BLACK, WHITE);
                sprintf(buf, "%02d", g_tm.tm_min);
                EPD_DrawUTF8(10 + 86 + 20, 20 + 2, 5, buf, EPD_40X80_TABLE, EPD_FontUTF8_24x24, BLACK, WHITE); 
            }
             // 创建一个指针，用于指向要显示的图片数据
            const unsigned char* image_to_display = NULL;
                // 晚上休息时间 (22:00 - 06:59)
            if (g_tm.tm_hour<7||g_tm.tm_hour  >= 22 ) {
                image_to_display = gImage_Sleep;
                //sprintf(buf,"安心睡觉");                                             // = "安心睡眠";
            } else if (g_tm.tm_hour < 8) {                       // 上午工作/学习时间 (07:00 - 10:59)
                image_to_display = gImage_breakfast;}
                else if (g_tm.tm_hour < 11) {                       // 上午工作/学习时间 (07:00 - 10:59)
                image_to_display = gImage_Morning;
                //sprintf(buf, "星期%s", WEEKCN[g_tm.tm_wday]); 
            } else if (g_tm.tm_hour < 13) {
                image_to_display = gImage_Lunch;
                //sprintf(buf, "吃好喝好%s", WEEKCN[g_tm.tm_wday]); 
                } else if (g_tm.tm_hour < 14) {
                image_to_display = gImage_rest;
                //sprintf(buf, "吃好喝好%s", WEEKCN[g_tm.tm_wday]);   
						} else if (g_tm.tm_hour < 19) {
                image_to_display = gImage_Work;
                //sprintf(buf, "自由活动"); 
            } else if (g_tm.tm_hour < 20) {
                image_to_display = gImage_dinner;
                //sprintf(buf, "自由活动"); 
            } else {
                image_to_display = gImage_rest;
                //sprintf(buf, "星期%s", WEEKCN[g_tm.tm_wday]); 
            }
             // 如果找到了要显示的图片，就调用GUI函数绘制它
            if (image_to_display != NULL) {
            // 使用 Paint_DrawImage 函数将选定的图片绘制到屏幕缓冲区的指定位置
            // 参数：图片数据, X坐标, Y坐标, 宽度, 高度, 前景色, 背景色
            Paint_DrawImage(image_to_display, img_x, img_y, img_w, img_h, BLACK, WHITE);
            //EPD_DrawUTF8(200, 50, 0, buf, EPD_40X80_TABLE, EPD_FontUTF8_16x16, BLACK, WHITE);
             }
            // 获取并显示MAC地址后六位
            extern struct bd_addr dev_bdaddr;
            sprintf((char *)buf2, "MAC: %02X:%02X:%02X:%02X:%02X:%02X",
            dev_bdaddr.addr[5], dev_bdaddr.addr[4], dev_bdaddr.addr[3],
            dev_bdaddr.addr[2], dev_bdaddr.addr[1], dev_bdaddr.addr[0]);
            EPD_DrawUTF8(80, 128-14, 0, (const char *)buf2, EPD_ASCII_7X12, 0, BLACK, WHITE);
             // 获取并显示MAC地址后六位     
}

void do_time_show_diff_part(void) 
{
    char min_buf[3]; 
    // 重新选择图像缓冲区，但不需要重新初始化或清空整个缓冲区 
    //Paint_SelectImage(epd_buffer); 
    Paint_SetMirroring(MIRROR_VERTICAL); 

    // 根据小时数的位数，确定分钟数字的起始X坐标
    UWORD min_x_start;
    if (g_tm.tm_hour < 10) 
    {
        // 小时为一位数时，分钟的X坐标是 10 + 86 + 20 - 30 = 86
        min_x_start = 86;
    } else { 
        // 小时为两位数时，分钟的X坐标是 10 + 86 + 20 = 116
        min_x_start = 116;
    }

    // 分钟数字的Y坐标是 20 + 2 = 22
    UWORD min_y_start = 22;
    // 分钟数字的宽度是 2个字符 * 40像素/字符 = 80像素
    UWORD min_width = 80;
    // 分钟数字的高度是 80像素
    UWORD min_height = 80;

    // 擦除旧的分钟数字区域
    Paint_ClearWindows(min_x_start, min_y_start, min_x_start + min_width, min_y_start + min_height, WHITE); 

    // 重新绘制分钟数字 
    sprintf(min_buf, "%02d", g_tm.tm_min);
    EPD_DrawUTF8(min_x_start, min_y_start, 5, min_buf, EPD_40X80_TABLE, EPD_FontUTF8_24x24, BLACK, WHITE);
}

/**
 * @brief 修改后的显示更新函数，支持模拟时钟
 */
void do_display_update_with_analog_clock(void)
{
//    transformTime(current_unix_time, &g_tm);
//    
//    // 判断是否需要强制重绘
//    bool force_redraw = false;
//    
//    // 如果是第一次显示或者小时发生变化，强制重绘
//    if (last_update_time == 0 || 
//        (current_unix_time - last_update_time) > 3600 || // 超过1小时
//        g_tm.tm_min == 0) // 整点时刻
//    {
//        force_redraw = true;
//        last_update_time = current_unix_time;
//    }
//    
//    // 如果分钟发生变化，需要更新指针
//    bool minute_changed = (last_minute != g_tm.tm_min);
//    if (minute_changed)
//    {
//        last_minute = g_tm.tm_min;
//    }
//    
//    switch (current_display_mode)
//    {
//        case DISPLAY_MODE_TIME:
//            // 原有的时间显示逻辑
//            //do_time_show_diff();
//                if (force_redraw) {
//                do_time_show_diff(); // 全屏重绘 
//                } else if (minute_changed) {
//                do_time_show_diff(); // 全屏重绘 
//                //    do_time_show_diff_part(); // 局部刷新分钟数字 
//            }
//            break;
//            
//        case DISPLAY_MODE_CALENDAR:
//            // 原有的日历显示逻辑（数字时钟）
//            Paint_NewImage(EPD_2IN13_V2_WIDTH, EPD_2IN13_V2_HEIGHT, 270, WHITE);
//            //Paint_SelectImage(epd_buffer);
//            Paint_SetMirroring(MIRROR_VERTICAL);
//            draw_calendar_page(current_unix_time);
//            break;
//            
//        case DISPLAY_MODE_CALENDAR_ANALOG:
//            // 新的日历显示逻辑（模拟时钟）
//            Paint_NewImage(EPD_2IN13_V2_WIDTH, EPD_2IN13_V2_HEIGHT, 270, WHITE);
//            //Paint_SelectImage(epd_buffer);
//            Paint_SetMirroring(MIRROR_VERTICAL);
//            // 使用新的模拟时钟日历函数
//            draw_calendar_with_analog_clock(current_unix_time, force_redraw || minute_changed);
//            break;
//            
//        default:
//            // 默认使用时间显示
//            current_display_mode = DISPLAY_MODE_TIME;
//            do_display_update_with_analog_clock(); // 递归调用
//            return;
//    }
//    
//    // 添加电池电量显示（所有模式通用）
//    Paint_DrawRectangle(296 - 24, 6 + 2, 296 - 24 + 2, 8 + 2 + 2, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
//    Paint_DrawRectangle(296 - 22, 1 + 2, 295, 20 - 5 + 2, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
//    sprintf(buf, "%d", cur_batt_level);
//    if (cur_batt_level > 9 && cur_batt_level < 100)
//    {
//        sprintf(buf, " %d", cur_batt_level);
//    }
//    else if (cur_batt_level < 10)
//    {
//        sprintf(buf, "  %d", cur_batt_level);
//    }
//    EPD_DrawUTF8(296 - 23, 1 + 2, 0, buf, EPD_ASCII_7X12, 0, WHITE, BLACK);
//    
//    // 蓝牙连接状态指示
//    if (isconnected == 1)
//    {
//        EPD_DrawUTF8(296 - 10, 128-12, 0, "B", EPD_ASCII_7X12, 0, WHITE, BLACK);
//    }

//    if (g_tm.tm_min == 0)
//    {
//        is_part = 0;
//    }
//    step = 0;

		UWORD width = 400;
    UWORD height = 300;

    // 2. 暂时注释掉所有其他绘图代码
    /* ... */

    // 3. 只画四个角落的点
    Paint_SetPixel(0, 0, BLACK);                         // 左上角
    Paint_SetPixel(width - 1, 0, BLACK);                 // 右上角
    Paint_SetPixel(0, height - 1, BLACK);                // 左下角
    Paint_SetPixel(width - 1, height - 1, BLACK);        // 右下角
    
    // 4. 再画一条对角线，帮助我们看清方向
    Paint_DrawLine(0, 0, width - 10, height - 10, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
}
		

/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
 */
void do_img_save(void)
{
    uint32_t actual_size;
    if (imgheader.signature[0] == IMG_HEADER_SIGNATURE1 && imgheader.signature[1] == IMG_HEADER_SIGNATURE2 && imgheader.validflag != IMG_HEADER_VALID)
    {
        imgheader.validflag = IMG_HEADER_VALID;
        img_header_t *imgheadertmp;
        spi_flash_peripheral_init();

        uint8_t buf[20] = {0};
        int8_t status = spi_flash_read_data(buf, IMG_HEADER_ADDRESS, sizeof(img_header_t), &actual_size);
        arch_printf("status0:%d\n", status);
        imgheadertmp = (img_header_t *)buf;
        // if (imgheadertmp->CRC != imgheader.CRC)
        // {
        // status=spi_flash_block_erase(IMG_HEADER_ADDRESS, SPI_FLASH_OP_BE32);
        // arch_printf("status1:%d\n",status);
        // arch_printf("erase\n");
        // status=spi_flash_set_write_enable();
        // arch_printf("status4s:%d\n",status);
        // status=spi_flash_write_data((uint8_t *)&imgheader, IMG_HEADER_ADDRESS, sizeof(img_header_t), &actual_size);
        // arch_printf("status2:%d\n",status);
        // arch_printf("imgheader wr:%d\n", actual_size);
        // status=spi_flash_write_data(epd_buffer, IMG_HEADER_ADDRESS + sizeof(img_header_t), sizeof(epd_buffer), &actual_size);
        // arch_printf("status3:%d\n",status);
        // arch_printf("epd_buffer wr:%d size:%d\n", actual_size,sizeof(epd_buffer));
        // }
        spi_flash_ultra_deep_power_down();
    }
}

/**
 * @brief 修改后的分钟工作函数
 */
void do_min_work_with_analog_clock(void)
{
    timer_used_min = app_easy_timer(APP_PERIPHERAL_CTRL_TIMER_DELAY_MINUTES, do_min_work_with_analog_clock);
    current_unix_time += time_offset;
    time_offset = 60;
    
    arch_printf("current_unix_time:%d\n", current_unix_time);
    
    // 使用新的显示更新函数
    do_display_update_with_analog_clock();
    
    if (step == 0)
    {
        step = 1;
        display();
    }
}

//// 我们暂时不包含任何新的头文件

//void simple_clear_test(void)
//{
//    // ... (前面的代码不变) ...
//    EPD_2IN13_V2_Clear();

//    arch_printf("Waiting for EPD to become idle (with timeout)...\n");
//    
//    int timeout_counter = 0;
//    #define TEST_TIMEOUT 10000 

//    while(EPD_BUSY == 1 && timeout_counter < TEST_TIMEOUT) {
//        // ================== 关键修改：只保留事件调度 ==================
//        
//        // 1. 注释掉手动喂狗的代码
//        // SetWord16(WATCHDOG_REG, 0xC8); 

//        // 2. 短暂地处理系统事件 (包括蓝牙)
//        GLOBAL_INT_DISABLE();
//        rwip_schedule();
//        GLOBAL_INT_RESTORE();

//        // 3. 制造一个小延时
//        for (volatile int i = 0; i < 100; i++);

//        // ========================================================================

//        timeout_counter++;
//    }

//    if (timeout_counter >= TEST_TIMEOUT) {
//        arch_printf("!!! EPD Busy Timeout after %d loops !!!\n", timeout_counter);
//    } else {
//        arch_printf("EPD is idle after %d loops.\n", timeout_counter);
//    }

//    // ... (后面的代码不变) ...
//}

void my_app_on_db_init_complete(void)
{
    crc32_init(DEFAULT_POLY);
    arch_printf("crc32_init\n");
    CALLBACK_ARGS_0(user_default_app_operations.default_operation_adv)
    arch_printf("my_app_on_db_init_complete_modified\n");
    
    // 初始化显示模式为时间显示
    current_display_mode = DISPLAY_MODE_TIME;
    last_update_time = 0;
    last_minute = 255;
    
    //timer_used_min = app_easy_timer(100, do_min_work_with_analog_clock);
    spi_flash_peripheral_init();
    uint32_t actual_size;
    int8_t status = spi_flash_read_data((uint8_t *)&imgheader, IMG_HEADER_ADDRESS, sizeof(img_header_t), &actual_size);
    arch_printf("imgheader read:%d,status:%d", actual_size, status);
//    if (imgheader.signature[0] == IMG_HEADER_SIGNATURE1 && imgheader.signature[1] == IMG_HEADER_SIGNATURE2 && imgheader.validflag == IMG_HEADER_VALID)
//    {
//        spi_flash_read_data(epd_buffer, IMG_HEADER_ADDRESS + sizeof(img_header_t), sizeof(epd_buffer), &actual_size);
//        arch_printf("epd_buffer read:%d\n", actual_size);
//    }
    spi_flash_ultra_deep_power_down();
    cur_batt_level = 101;
    app_batt_lvl();
		// ================== 在这里调用测试函数 ==================
    // 为了防止干扰，可以先注释掉原来的定时器启动
    // timer_used_min = app_easy_timer(100, do_min_work_with_analog_clock);
    
    // 直接调用清屏测试
    //simple_clear_test();
    // ======================================================
}


void user_svc1_ctrl_wr_ind_handler(ke_msg_id_t const msgid,
                                   struct custs1_val_write_ind const *param,
                                   ke_task_id_t const dest_id,
                                   ke_task_id_t const src_id)
{
    uint8_t val = 0;
    memcpy(&val, &param->value[0], param->length);

    if (val != CUSTS1_CP_ADC_VAL1_DISABLE)
    {
        timer_used = app_easy_timer(APP_PERIPHERAL_CTRL_TIMER_DELAY, app_adcval1_timer_cb_handler);
    }
    else
    {
        if (timer_used != EASY_TIMER_INVALID_TIMER)
        {
            app_easy_timer_cancel(timer_used);
            timer_used = EASY_TIMER_INVALID_TIMER;
        }
    }
}

// 在 user_custs1_impl.c 中

void display(void)
{
    extern uint8_t page_buffer[];
    extern int current_page_y_start;
    extern uint32_t current_page_buffer_size;


    #define PAGE_HEIGHT 32

    // 这一次，我们需要一个全屏的缓冲区在RAM中
    // 这是一个巨大的赌注，我们赌DA14585的RAM在去掉其他所有消耗后，勉强能放下

    bool is_busy = true;

    switch (step)
    {
        case 0: is_busy = false; break;

        case 1: // 初始化
            arch_printf("Step 1: Back to Basics Init\n");
            EPD_GPIO_init();
            EPD_2IN13_V2_Init(0); // <-- 使用原版的、能刷黑白的 Init 函数
            step++;
            break;

//        case 2:
//Paint_NewImage(full_image_buffer, LOGIC_WIDTH, LOGIC_HEIGHT, 0, BLACK);
//do_display_update_with_analog_clock();
//step++;
//break;

//				// 在 RAM 中构建完整的图像
//            arch_printf("Step 2: Building full image in RAM...\n");
// // ================== 核心修改：手动创建大棋盘格 ==================
//            
//            // 1. 首先，将整个缓冲区填充为白色 (0xFF)
//            for (int i = 0; i < FULL_BUFFER_SIZE; i++) {
//                full_image_buffer[i] = 0xFF;
//            }

//            // 2. 接着，在 (0,0) 开始的 20x50 区域内绘制黑色 (0x00)
//            #define BLACK_BLOCK_WIDTH  20 // 矩形宽度
//            #define BLACK_BLOCK_HEIGHT 50 // 矩形高度

//            for (int y = 0; y < BLACK_BLOCK_HEIGHT; y++) { // 遍历 50 行
//                for (int x = 0; x < BLACK_BLOCK_WIDTH; x++) { // 遍历 20 列
//                    // 计算 (x, y) 像素对应的缓冲区索引和位掩码
//                    int byte_index = (y * (LOGIC_WIDTH / 8)) + (x / 8);
//                    int bit_index = 7 - (x % 8); // 假设高位在左

//                    // 检查索引是否越界
//                    if (byte_index < FULL_BUFFER_SIZE) {
//                        // 将对应位设置为 0，表示黑色
//                        full_image_buffer[byte_index] &= ~(1 << bit_index);
//                    }
//                }
//            }

//            step++;
//            break;

case 2: // 绘制黑块和字符串
    arch_printf("Step 2: Drawing block and string...\n");

    // 1. 初始化 Paint 库，将其与我们的全屏缓冲区关联
    //    这一步是调用任何 Paint 函数前所必需的。
    Paint.Image = full_image_buffer;
    Paint.Width = LOGIC_WIDTH;
    Paint.Height = LOGIC_HEIGHT;
    Paint.Rotate = ROTATE_0;
    Paint.Mirror = MIRROR_NONE;
    Paint.WidthByte = LOGIC_WIDTH / 8;
    Paint.HeightByte = LOGIC_HEIGHT;
    Paint.Scale = 2; // 黑白模式

    // 2. 清空整个缓冲区为白色
    Paint_Clear(WHITE); // WHITE 通常定义为 0xFF

    // 3. 绘制一个 20x50 的黑色矩形在原点 (0,0)
//    Paint_DrawRectangle(0, 0, 20, 50, BLACK, DOT_PIXEL_DFT, DRAW_FILL_FULL);

//    // 4. 在黑块旁边绘制字符串 "Hello, Manus!"
//    //    我们使用 EPD_DrawUTF8 函数和 EPD_ASCII_11X16 字体。
//    //    - 位置: x=30 (黑块右边), y=20
//    //    - 间距: 1 像素
//    //    - 字符串: "Hello, Manus!"
//    //    - ASCII字体: EPD_ASCII_11X16
//    //    - UTF8字体: NULL (因为我们只显示英文)
//    //    - 颜色: 黑色前景，透明背景
//    EPD_DrawUTF8(30, 20, 1, "Hello, Manus!", EPD_ASCII_11X16, NULL, BLACK, FONT_BACKGROUND);
//		EPD_DrawUTF8(300,260, 1, "No Way,Manus!", EPD_ASCII_11X16, NULL, BLACK, FONT_BACKGROUND);
//    
//    // 5. (可选) 绘制一个包含中文的字符串
//    //    我们使用 EPD_FontUTF8_24x24 字体来显示中文。
//    //    - 位置: x=30, y=60 (在第一行文字的下方)
    EPD_DrawUTF8(30, 60, 2, "你好，世界！", EPD_ASCII_11X16, EPD_FontUTF8_24x24, BLACK, FONT_BACKGROUND);

Paint_DrawRectangle(10, 10, 390, 290, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

    // 2. 在矩形内部，再画一个小一点的、填充的矩形，以验证填充功能
    Paint_DrawRectangle(50, 50, 150, 100, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);

    // 3. 在另一个角落，画一条线，验证画线功能
    Paint_DrawLine(380, 280, 200, 200, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

    // 4. 写一行字，验证文字功能
    EPD_DrawUTF8(160, 150, 1, "It works!", EPD_ASCII_11X16, NULL, BLACK, FONT_BACKGROUND);

    step++;
    break;

//case 2: // 绘制黑块和字符串 (颜色交换版)
//    arch_printf("Step 2: Drawing block and string (Colors inverted)...\n");

//    // 1. 初始化 Paint 库
//    Paint.Image = full_image_buffer;
//    Paint.Width = LOGIC_WIDTH;
//    Paint.Height = LOGIC_HEIGHT;
//    Paint.Rotate = ROTATE_0;
//    Paint.Mirror = MIRROR_NONE;
//    Paint.WidthByte = LOGIC_WIDTH / 8;
//    Paint.HeightByte = LOGIC_HEIGHT;
//    Paint.Scale = 2;

//    // 2. 清空整个缓冲区为黑色背景 (我们故意用 BLACK)
//    //    这样我们的白色内容就能显现出来。
//    Paint_Clear(BLACK); // <--- 用 BLACK 清屏，得到一个黑色背景

//    // 3. 绘制一个 20x50 的白色矩形
//    Paint_DrawRectangle(0, 0, 20, 50, WHITE, DOT_PIXEL_DFT, DRAW_FILL_FULL); // <--- 用 WHITE 画矩形

//    // 4. 绘制白色的字符串
//    //    注意最后一个参数 FONT_BACKGROUND，它表示背景透明，所以我们不需要交换它。
//    EPD_DrawUTF8(30, 20, 1, "Hello, Manus!", EPD_ASCII_11X16, NULL, WHITE, FONT_BACKGROUND); // <--- 用 WHITE 画文字
//    
//    EPD_DrawUTF8(30, 60, 2, "你好，世界！", EPD_ASCII_11X16, EPD_FontUTF8_24x24, WHITE, FONT_BACKGROUND); // <--- 用 WHITE 画文字

//    step++;
//    break;


        case 3: // 发送新数据缓冲区 (0x24)
            arch_printf("Step 3: Sending NEW buffer (0x24)...\n");
            EPD_2IN13_V2_SendCommand(0x24);
            for(int i=0; i < FULL_BUFFER_SIZE; i++) {
                EPD_2IN13_V2_SendData(full_image_buffer[i]);
            }
            step++;
            break;

        case 4: // 发送旧数据缓冲区 (0x26)
            arch_printf("Step 4: Sending OLD buffer (0x26)...\n");
            EPD_2IN13_V2_SendCommand(0x26);
            for(int i=0; i < FULL_BUFFER_SIZE; i++) {
                EPD_2IN13_V2_SendData(full_image_buffer[i]);
            }
            step++;
            break;

        case 5: /* 触发刷新 */ 
            arch_printf("Step 5: Turn On Display\n");
            EPD_2IN13_V2_TurnOnDisplay(); 
            step++; 
            break;
        case 6: /* 等待完成 */ 
            if (EPD_BUSY == 0) { step++; } 
            break;
        case 7: /* 休眠 */ 
            EPD_2IN13_V2_Sleep(); 
            step = 0; 
            is_busy = false; 
            break;

        default:
            step = 0;
            is_busy = false;
            break;
    }

    if (is_busy) {
        app_easy_timer(APP_PERIPHERAL_CTRL_TIMER_DELAY, display);
    }
}

void bls_att_pushNotifyData(uint16_t attHandle, uint8_t *p, uint8_t len)
{
    struct custs1_val_ntf_ind_req *req = KE_MSG_ALLOC_DYN(CUSTS1_VAL_NTF_REQ,
                                                          prf_get_task_from_id(TASK_ID_CUSTS1),
                                                          TASK_APP,
                                                          custs1_val_ntf_ind_req,
                                                          DEF_SVC1_ADC_VAL_1_CHAR_LEN);

    req->handle = attHandle;
    req->length = len;
    req->notification = true;
    memcpy(req->value, p, len);

    ke_msg_send(req);
}

void user_svc1_led_wr_ind_handler(ke_msg_id_t const msgid,
                                  struct custs1_val_write_ind const *param,
                                  ke_task_id_t const dest_id,
                                  ke_task_id_t const src_id)

	{
    const uint8_t *payload = param->value;
    uint16_t payload_len = param->length;
    uint8_t out_buffer[20] = {0};
    if (step != 0)
    {
        out_buffer[0] = 0x00;
        out_buffer[1] = 0x00;
        bls_att_pushNotifyData(SVC1_IDX_LED_STATE_VAL, out_buffer, 2);
        return;
    }
    switch (param->value[0])
    {
    // Clear EPD display.
    case 0x00:
        ASSERT_MIN_LEN(payload_len, 2);
        // memset(epd_buffer, payload[1], epd_buffer_size);
        // memset(epd_temp, payload[1], epd_buffer_size);

        return;
    // Push buffer to display.
    case 0x01:
        // EPD_Display(epd_buffer, epd_temp, epd_buffer_size, payload[1]);
        arch_printf("start EPD_Display\r\n");
//        imgheader.signature[0] = IMG_HEADER_SIGNATURE1;
//        imgheader.signature[1] = IMG_HEADER_SIGNATURE2;
//        imgheader.CRC = 0xFFFFFFFF;
//        imgheader.CRC = crc32(imgheader.CRC, epd_buffer, sizeof(epd_buffer));
//        imgheader.CRC ^= 0xFFFFFFFF;
//        imgheader.code_size = sizeof(epd_buffer);
//        imgheader.validflag = 0;
        step = 1;
// 直接调用我们新的 display 函数
        display(); 

//        app_easy_timer(APP_PERIPHERAL_CTRL_TIMER_DELAY, display);
        return;
    // Set byte_pos.
    case 0x02:
        ASSERT_MIN_LEN(payload_len, 3);
        byte_pos = payload[1] << 8 | payload[2];
        return;
    // Write data to image buffer.
    case 0x03:
        if ((payload[2] << 8 | payload[3]) + payload_len - 4 >= epd_buffer_size + 1)
        {
            out_buffer[0] = 0x00;
            out_buffer[1] = 0x00;
            bls_att_pushNotifyData(SVC1_IDX_LED_STATE_VAL, out_buffer, 2);
            return;
        }
        if (payload[1] == 0xff)
        {
//            memcpy(epd_buffer + (payload[2] << 8 | payload[3]), payload + 4, payload_len - 4);
// 可以添加一行打印，告诉我们这个功能被调用了但已被禁用
            arch_printf("Warning: Bluetooth data write (0x03) is disabled in paged mode.\n");
        }
        out_buffer[0] = payload_len >> 8;
        out_buffer[1] = payload_len & 0xff;
        bls_att_pushNotifyData(SVC1_IDX_LED_STATE_VAL, out_buffer, 2);
        return;
    case 0x04: // decode & display a TIFF image
        // param_update_request(1);
        return;
    case 0xAA:
        do_img_save();
        break;
    case 0xAB:
        platform_reset(RESET_NO_ERROR);
        break;
    case 0xE5:
        current_display_mode = DISPLAY_MODE_CALENDAR_ANALOG;
        do_display_update_with_analog_clock();
        if (step == 0)
        {
            step = 1;
            display();
        }
        break;
    default:
        return;
    }
}

/**
 * @brief 修改后的串口命令处理函数，添加模拟时钟模式切换
 */
void user_svc2_wr_ind_handler(ke_msg_id_t const msgid,
                              struct custs1_val_write_ind const *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    arch_printf("cmd HEX %d:", param->length);
    for (int i = 0; i < param->length; i++)
    {
        arch_printf("%02X", param->value[i]);
    }
    arch_printf("\r\n");
    
    if ((param->value[0] == 0xDD) && (param->length >= 5))
    {
        // 时间设置逻辑保持不变
        current_unix_time = (param->value[1] << 24) + (param->value[2] << 16) + (param->value[3] << 8) + (param->value[4] & 0xff);
        tm_t tm = {0};
        transformTime(current_unix_time, &tm);
        app_easy_timer_cancel(timer_used_min);
        time_offset = 60 - tm.tm_sec;
        timer_used_min = app_easy_timer(time_offset * 100, do_min_work_with_analog_clock);
        
        // 重置更新时间，强制重绘
        last_update_time = 0;
        
        arch_printf("%d-%02d-%02d %02d:%02d:%02d %d\n", tm.tm_year + YEAR0,
                    tm.tm_mon + 1,
                    tm.tm_mday,
                    tm.tm_hour,
                    tm.tm_min,
                    tm.tm_sec,
                    tm.tm_wday);
    }
    else if (param->value[0] == 0xAA)
    {
        platform_reset(RESET_NO_ERROR);
    }
    else if (param->value[0] == 0xAB)
    {
        // do_img_save();
    }
    else if (param->value[0] == 0xE2)
    {
        // 刷新当前显示模式
        last_update_time = 0; // 强制重绘
        do_display_update_with_analog_clock();
        is_part = 0;
        step = 1;
        display();
    }
    else if (param->value[0] == 0xE3)
    {
        // 切换到时间显示模式
        current_display_mode = DISPLAY_MODE_TIME;
        last_update_time = 0; // 强制重绘
        do_display_update_with_analog_clock();
        is_part = 0;
        step = 1;
        display();
        arch_printf("Switched to TIME display mode\n");
    }
    else if (param->value[0] == 0xE4)
    {
        // 切换到日历显示模式（数字时钟）
        current_display_mode = DISPLAY_MODE_CALENDAR;
        last_update_time = 0; // 强制重绘
        do_display_update_with_analog_clock();
        is_part = 0;
        step = 1;
        display();
        arch_printf("Switched to CALENDAR display mode\n");
    }
    else if (param->value[0] == 0xE5)
    {
        // 新增：切换到日历显示模式（模拟时钟）
        current_display_mode = DISPLAY_MODE_CALENDAR_ANALOG;
        last_update_time = 0; // 强制重绘
        do_display_update_with_analog_clock();
        is_part = 0;
        step = 1;
        display();
        arch_printf("Switched to CALENDAR ANALOG display mode\n");
    }
}


void user_svc1_long_val_cfg_ind_handler(ke_msg_id_t const msgid,
                                        struct custs1_val_write_ind const *param,
                                        ke_task_id_t const dest_id,
                                        ke_task_id_t const src_id)
{
    // Generate indication when the central subscribes to it
    // if (param->value[0])
    // {
    //     uint8_t conidx = KE_IDX_GET(src_id);

    //     struct custs1_val_ind_req *req = KE_MSG_ALLOC_DYN(CUSTS1_VAL_IND_REQ,
    //                                                       prf_get_task_from_id(TASK_ID_CUSTS1),
    //                                                       TASK_APP,
    //                                                       custs1_val_ind_req,
    //                                                       sizeof(indication_counter));

    //     req->conidx = app_env[conidx].conidx;
    //     req->handle = SVC1_IDX_INDICATEABLE_VAL;
    //     req->length = sizeof(indication_counter);
    //     req->value[0] = (indication_counter >> 8) & 0xFF;
    //     req->value[1] = indication_counter & 0xFF;

    //     indication_counter++;

    //     ke_msg_send(req);
    // }
}

void user_svc1_long_val_wr_ind_handler(ke_msg_id_t const msgid,
                                       struct custs1_val_write_ind const *param,
                                       ke_task_id_t const dest_id,
                                       ke_task_id_t const src_id)
{
}

void user_svc1_long_val_ntf_cfm_handler(ke_msg_id_t const msgid,
                                        struct custs1_val_write_ind const *param,
                                        ke_task_id_t const dest_id,
                                        ke_task_id_t const src_id)
{
}

void user_svc1_adc_val_1_cfg_ind_handler(ke_msg_id_t const msgid,
                                         struct custs1_val_write_ind const *param,
                                         ke_task_id_t const dest_id,
                                         ke_task_id_t const src_id)
{
}

void user_svc1_adc_val_1_ntf_cfm_handler(ke_msg_id_t const msgid,
                                         struct custs1_val_write_ind const *param,
                                         ke_task_id_t const dest_id,
                                         ke_task_id_t const src_id)
{
}

void user_svc1_button_cfg_ind_handler(ke_msg_id_t const msgid,
                                      struct custs1_val_write_ind const *param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id)
{
}

void user_svc1_button_ntf_cfm_handler(ke_msg_id_t const msgid,
                                      struct custs1_val_write_ind const *param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id)
{
}

void user_svc1_indicateable_cfg_ind_handler(ke_msg_id_t const msgid,
                                            struct custs1_val_write_ind const *param,
                                            ke_task_id_t const dest_id,
                                            ke_task_id_t const src_id)
{
}

void user_svc1_indicateable_ind_cfm_handler(ke_msg_id_t const msgid,
                                            struct custs1_val_write_ind const *param,
                                            ke_task_id_t const dest_id,
                                            ke_task_id_t const src_id)
{
}

void user_svc1_long_val_att_info_req_handler(ke_msg_id_t const msgid,
                                             struct custs1_att_info_req const *param,
                                             ke_task_id_t const dest_id,
                                             ke_task_id_t const src_id)
{
    struct custs1_att_info_rsp *rsp = KE_MSG_ALLOC(CUSTS1_ATT_INFO_RSP,
                                                   src_id,
                                                   dest_id,
                                                   custs1_att_info_rsp);
    // Provide the connection index.
    rsp->conidx = app_env[param->conidx].conidx;
    // Provide the attribute index.
    rsp->att_idx = param->att_idx;
    // Provide the current length of the attribute.
    rsp->length = 0;
    // Provide the ATT error code.
    rsp->status = ATT_ERR_NO_ERROR;

    ke_msg_send(rsp);
}

void user_svc1_rest_att_info_req_handler(ke_msg_id_t const msgid,
                                         struct custs1_att_info_req const *param,
                                         ke_task_id_t const dest_id,
                                         ke_task_id_t const src_id)
{
    struct custs1_att_info_rsp *rsp = KE_MSG_ALLOC(CUSTS1_ATT_INFO_RSP,
                                                   src_id,
                                                   dest_id,
                                                   custs1_att_info_rsp);
    // Provide the connection index.
    rsp->conidx = app_env[param->conidx].conidx;
    // Provide the attribute index.
    rsp->att_idx = param->att_idx;
    // Force current length to zero.
    rsp->length = 0;
    // Provide the ATT error code.
    rsp->status = ATT_ERR_WRITE_NOT_PERMITTED;

    ke_msg_send(rsp);
}

void app_adcval1_timer_cb_handler()
{
    // struct custs1_val_ntf_ind_req *req = KE_MSG_ALLOC_DYN(CUSTS1_VAL_NTF_REQ,
    //                                                       prf_get_task_from_id(TASK_ID_CUSTS1),
    //                                                       TASK_APP,
    //                                                       custs1_val_ntf_ind_req,
    //                                                       DEF_SVC1_ADC_VAL_1_CHAR_LEN);

    // // ADC value to be sampled
    // static uint16_t sample __SECTION_ZERO("retention_mem_area0");
    // sample = (sample <= 0xffff) ? (sample + 1) : 0;

    // // req->conhdl = app_env->conhdl;
    // req->handle = SVC1_IDX_ADC_VAL_1_VAL;
    // req->length = DEF_SVC1_ADC_VAL_1_CHAR_LEN;
    // req->notification = true;
    // memcpy(req->value, &sample, DEF_SVC1_ADC_VAL_1_CHAR_LEN);

    // ke_msg_send(req);

    if (ke_state_get(TASK_APP) == APP_CONNECTED)
    {
        // Set it once again until Stop command is received in Control Characteristic
        timer_used = app_easy_timer(APP_PERIPHERAL_CTRL_TIMER_DELAY, app_adcval1_timer_cb_handler);
    }
}

void user_svc3_read_non_db_val_handler(ke_msg_id_t const msgid,
                                       struct custs1_value_req_ind const *param,
                                       ke_task_id_t const dest_id,
                                       ke_task_id_t const src_id)
{
    // Increase value by one
    non_db_val_counter++;

    // struct custs1_value_req_rsp *rsp = KE_MSG_ALLOC_DYN(CUSTS1_VALUE_REQ_RSP,
    //                                                     prf_get_task_from_id(TASK_ID_CUSTS1),
    //                                                     TASK_APP,
    //                                                     custs1_value_req_rsp,
    //                                                     DEF_SVC3_READ_VAL_4_CHAR_LEN);

    // // Provide the connection index.
    // rsp->conidx = app_env[param->conidx].conidx;
    // // Provide the attribute index.
    // rsp->att_idx = param->att_idx;
    // // Force current length to zero.
    // rsp->length = sizeof(non_db_val_counter);
    // // Provide the ATT error code.
    // rsp->status = ATT_ERR_NO_ERROR;
    // // Copy value
    // memcpy(&rsp->value, &non_db_val_counter, rsp->length);
    // // Send message
    // ke_msg_send(rsp);
}
