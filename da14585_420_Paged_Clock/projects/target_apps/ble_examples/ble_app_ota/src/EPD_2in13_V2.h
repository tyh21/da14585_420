
#ifndef _EPD_2IN13_V2_H_
#define _EPD_2IN13_V2_H_
#include "stdint.h"
#include "stdbool.h"
#include "gpio.h"
#include "systick.h"
#include "spi.h"
#include "user_periph_setup.h"
#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

// Display resolution
//#define EPD_2IN13_V2_WIDTH       128
//#define EPD_2IN13_V2_HEIGHT      296
#define EPD_2IN13_V2_WIDTH       400
#define EPD_2IN13_V2_HEIGHT      300

#define EPD_2IN13_V2_FULL			0
#define EPD_2IN13_V2_PART			1

/*
EPD_POWER  P23 H
    
BUSY              P20
RST                 P07
DC                  p05
CS                   P21
SCLK               P00
SDI                  P06

*/

// #define EPD_SCLK_H   GPIO_SetActive(GPIO_PORT_0, GPIO_PIN_1)
// #define EPD_SCLK_L   GPIO_SetInactive(GPIO_PORT_0, GPIO_PIN_1)
// #define EPD_SDI_H    GPIO_SetActive(GPIO_PORT_2, GPIO_PIN_0)
// #define EPD_SDI_L    GPIO_SetInactive(GPIO_PORT_2, GPIO_PIN_0)


#define EPD_SCLK_H   GPIO_SetActive(GPIO_PORT_0, GPIO_PIN_0)
#define EPD_SCLK_L   GPIO_SetInactive(GPIO_PORT_0, GPIO_PIN_0)
#define EPD_SDI_H    GPIO_SetActive(GPIO_PORT_0, GPIO_PIN_6)
#define EPD_SDI_L    GPIO_SetInactive(GPIO_PORT_0, GPIO_PIN_6)
#define EPD_DC_H     GPIO_SetActive(GPIO_PORT_0, GPIO_PIN_5)
#define EPD_DC_L     GPIO_SetInactive(GPIO_PORT_0, GPIO_PIN_5)
#define EPD_CS_H     GPIO_SetActive(GPIO_PORT_2, GPIO_PIN_1)      
#define EPD_CS_L     GPIO_SetInactive(GPIO_PORT_2, GPIO_PIN_1)    
#define EPD_RST_H    GPIO_SetActive(GPIO_PORT_0, GPIO_PIN_7) 
#define EPD_RST_L    GPIO_SetInactive(GPIO_PORT_0, GPIO_PIN_7)
#define EPD_BUSY     GPIO_GetPinStatus(GPIO_PORT_2,GPIO_PIN_0)
#define DEV_Delay_ms(ms)   systick_wait(ms*1000)

void EPD_GPIO_init(void);
void EPD_2IN13_V2_Init_RED(void);
void EPD_2IN13_V2_TurnOnDisplay_RED(void);
void EPD_2IN13_V2_Clear_RED(void);
void DEV_SPI_WriteByte(uint8_t sdbyte);
void EPD_2IN13_V2_Init(UBYTE Mode);
void EPD_2IN13_V2_Clear(void);
void EPD_2IN13_V2_Display(UBYTE *Image);
void EPD_2IN13_V2_DisplayPart(UBYTE *Image);
void EPD_2IN13_V2_DisplayPartBaseImage(UBYTE *Image);
void EPD_2IN13_V2_Sleep(void);
void EPD_2IN13_V2_TurnOnDisplayPart(void);
void EPD_2IN13_V2_TurnOnDisplay(void);
void EPD_DrawImage( const uint8_t *image, uint16_t x, uint16_t y, uint16_t w, uint16_t h,bool part );
void EPD_SetWindow(uint16_t x, uint8_t y_x8, uint16_t x_size, uint8_t y_size_x8);
void EPD_2IN13_V2_SendCommand(UBYTE Reg);
void EPD_2IN13_V2_SendData(UBYTE Data);
void EPD_Init_Pure_Weixue_Sequence(void);
void EPD_2IN13_V2_Init_Partial_Mode_Legacy(void);           //这个函数应该不起作用
void EPD_2IN13_V2_TurnOnDisplay_Partial_Legacy(void);       //这个函数应该不起作用
#endif
