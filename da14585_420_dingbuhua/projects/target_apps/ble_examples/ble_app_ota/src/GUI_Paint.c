/******************************************************************************
* | File      	:   GUI_Paint.c
* | Author      :   Waveshare electronics (Modified by Manus for paging)
* | Function    :	Achieve drawing: draw points, lines, boxes, circles and
*                   their size, solid dotted line, solid rectangle hollow
*                   rectangle, solid circle hollow circle.
* | Info        :
*   This version has been modified to support paged rendering to conserve RAM.
*----------------
* |	This version:   V3.2 (Paged)
* | Date        :   2025-09-28
* | Info        :
*   - Added page_buffer, current_page_y_start, current_page_buffer_size
*   - Modified Paint_NewImage to use internal page_buffer
*   - Modified Paint_SetPixel to only draw within the current page
*
******************************************************************************/
#include "GUI_Paint.h"
#include "EPD_2in13_V2.h" // <-- 引入这个文件来获取 EPD_WIDTH
#include "Debug.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h> //memset()
#include <math.h>

PAINT Paint;

// ===================================================================
// == 1. 引入分页所需的支持 (核心修改)
// ===================================================================
#define PAGE_HEIGHT 32 // 内存安全的分页高度，可以根据需要调整
#define MAX_PAGE_WIDTH_BYTES (EPD_2IN13_V2_WIDTH / 8)
#define MAX_PAGE_BUFFER_SIZE (MAX_PAGE_WIDTH_BYTES * PAGE_HEIGHT)

// 定义为全局可访问变量 (没有 static)，以便 display() 函数可以访问和设置
uint8_t page_buffer[MAX_PAGE_BUFFER_SIZE] __SECTION_ZERO("retention_mem_area0");
int current_page_y_start = 0;
uint32_t current_page_buffer_size = 0;


/******************************************************************************
function: Create Image
parameter:
    image   :   Pointer to the image cache
    width   :   The width of the picture
    Height  :   The height of the picture
    Color   :   Whether the picture is inverted
******************************************************************************/
// ===================================================================
// == 2. 改造 Paint_NewImage() 函数 (核心修改)
// ===================================================================
void Paint_NewImage(UWORD Width, UWORD Height, UWORD Rotate, UWORD Color) {
    Paint.Image = page_buffer;
    Paint.WidthMemory = Width;
    Paint.HeightMemory = Height;
    Paint.Color = Color;
    Paint.Scale = 2;
    Paint.WidthByte = (Width % 8 == 0) ? (Width / 8) : (Width / 8 + 1);
    Paint.HeightByte = Height;
    current_page_buffer_size = Paint.WidthByte * PAGE_HEIGHT;
    if (current_page_buffer_size > MAX_PAGE_BUFFER_SIZE) {
        current_page_buffer_size = MAX_PAGE_BUFFER_SIZE;
    }
    Paint.Rotate = Rotate;
    Paint.Mirror = MIRROR_NONE;
    if (Rotate == ROTATE_0 || Rotate == ROTATE_180) {
        Paint.Width = Width;
        Paint.Height = Height;
    } else {
        Paint.Width = Height;
        Paint.Height = Width;
    }
}


/******************************************************************************
function: Select Image
parameter:
    image : Pointer to the image cache
******************************************************************************/
void Paint_SelectImage(UBYTE *image) {
    Paint.Image = page_buffer;
}

/******************************************************************************
function: Select Image Rotate
parameter:
    Rotate : 0,90,180,270
******************************************************************************/
void Paint_SetRotate(UWORD Rotate) {
    if (Rotate == ROTATE_0 || Rotate == ROTATE_90 || Rotate == ROTATE_180 || Rotate == ROTATE_270) {
        Paint.Rotate = Rotate;
    } else {
        Debug("rotate = 0, 90, 180, 270\r\n");
    }
}

/******************************************************************************
function:	Select Image mirror
parameter:
    mirror   :Not mirror,Horizontal mirror,Vertical mirror,Origin mirror
******************************************************************************/
void Paint_SetMirroring(UBYTE mirror) {
    if (mirror == MIRROR_NONE || mirror == MIRROR_HORIZONTAL ||
        mirror == MIRROR_VERTICAL || mirror == MIRROR_ORIGIN) {
        Paint.Mirror = mirror;
    } else {
        Debug("mirror should be MIRROR_NONE, MIRROR_HORIZONTAL, \
        MIRROR_VERTICAL or MIRROR_ORIGIN\r\n");
    }
}

void Paint_SetScale(UBYTE scale) {
    if (scale == 2) {
        Paint.Scale = scale;
        Paint.WidthByte = (Paint.WidthMemory % 8 == 0) ? (Paint.WidthMemory / 8) : (Paint.WidthMemory / 8 + 1);
    } else if (scale == 4) {
        Paint.Scale = scale;
        Paint.WidthByte = (Paint.WidthMemory % 4 == 0) ? (Paint.WidthMemory / 4) : (Paint.WidthMemory / 4 + 1);
    } else if (scale == 7) {
        Paint.Scale = 7;
        Paint.WidthByte = (Paint.WidthMemory % 2 == 0) ? (Paint.WidthMemory / 2) : (Paint.WidthMemory / 2 + 1);
    } else {
        Debug("Set Scale Input parameter error\r\n");
        Debug("Scale Only support: 2 4 7\r\n");
    }
}

/******************************************************************************
function: Draw Pixels
parameter:
    Xpoint : At point X
    Ypoint : At point Y
    Color  : Painted colors
******************************************************************************/
// ===================================================================
// == 3. 改造 Paint_SetPixel() 函数 (核心修改)
// ===================================================================
void Paint_SetPixel(UWORD Xpoint, UWORD Ypoint, UWORD Color) {
    if (Xpoint > Paint.Width || Ypoint > Paint.Height) return;
    UWORD X, Y;
    switch (Paint.Rotate) {
        case 0: X = Xpoint; Y = Ypoint; break;
        case 90: X = Paint.WidthMemory - Ypoint - 1; Y = Xpoint; break;
        case 180: X = Paint.WidthMemory - Xpoint - 1; Y = Paint.HeightMemory - Ypoint - 1; break;
        case 270: X = Ypoint; Y = Paint.HeightMemory - Xpoint - 1; break;
        default: return;
    }
    switch (Paint.Mirror) {
        case MIRROR_NONE: break;
        case MIRROR_HORIZONTAL: X = Paint.WidthMemory - X - 1; break;
        case MIRROR_VERTICAL: Y = Paint.HeightMemory - Y - 1; break;
        case MIRROR_ORIGIN: X = Paint.WidthMemory - X - 1; Y = Paint.HeightMemory - Y - 1; break;
        default: return;
    }
    if (X > Paint.WidthMemory || Y > Paint.HeightMemory) return;

    if (Y >= current_page_y_start && Y < (current_page_y_start + PAGE_HEIGHT)) {
        int relative_y = Y - current_page_y_start;
        if (Paint.Scale == 2) {
            UDOUBLE Addr = X / 8 + relative_y * Paint.WidthByte;
            if (Addr >= current_page_buffer_size) return;
            if (Color == BLACK) Paint.Image[Addr] &= ~(0x80 >> (X % 8));
            else Paint.Image[Addr] |= (0x80 >> (X % 8));
        }
    }
}

/******************************************************************************
function: Clear the color of the picture
parameter:
    Color : Painted colors
******************************************************************************/
void Paint_Clear(UWORD Color) {
    // 不再逐像素调用，而是直接、高效地对 page_buffer 进行内存操作
    if (Color == WHITE) {
        memset(page_buffer, 0xFF, current_page_buffer_size);
    } else {
        memset(page_buffer, 0x00, current_page_buffer_size);
    }
}

/******************************************************************************
function: Clear the color of a window
parameter:
    Xstart : x starting point
    Ystart : Y starting point
    Xend   : x end point
    Yend   : y end point
    Color  : Painted colors
******************************************************************************/
void Paint_ClearWindows(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD Color) {
    // 计算窗口与当前页的交集，只在交集区域内循环
    UWORD Ystart_page = (Ystart > current_page_y_start) ? Ystart : current_page_y_start;
    UWORD Yend_page = (Yend < (current_page_y_start + PAGE_HEIGHT)) ? Yend : (current_page_y_start + PAGE_HEIGHT);

    // 如果交集为空，则直接返回，不做任何事
    if (Ystart_page >= Yend_page) {
        return;
    }

    // 只在有效的交集区域内进行逐像素绘制
    for (UWORD Y = Ystart_page; Y < Yend_page; Y++) {
        for (UWORD X = Xstart; X < Xend; X++) {
            Paint_SetPixel(X, Y, Color);
        }
    }
}


// ... (Paint_DrawPoint, Paint_DrawLine, Paint_DrawRectangle, etc. 保持完全不变) ...
// ... (因为它们都基于 Paint_SetPixel, 所以自动获得了分页能力) ...

/******************************************************************************
function: Draw Point(Xpoint, Ypoint) Fill the color
parameter:
    Xpoint		: The Xpoint coordinate of the point
    Ypoint		: The Ypoint coordinate of the point
    Color		: Painted color
    Dot_Pixel	: point size
    Dot_Style	: point Style
******************************************************************************/
void Paint_DrawPoint(UWORD Xpoint, UWORD Ypoint, UWORD Color,
                     DOT_PIXEL Dot_Pixel, DOT_STYLE Dot_Style) {
    if (Xpoint > Paint.Width || Ypoint > Paint.Height) {
        return;
    }
    int16_t XDir_Num, YDir_Num;
    if (Dot_Style == DOT_FILL_AROUND) {
        for (XDir_Num = 0; XDir_Num < 2 * Dot_Pixel - 1; XDir_Num++) {
            for (YDir_Num = 0; YDir_Num < 2 * Dot_Pixel - 1; YDir_Num++) {
                if (Xpoint + XDir_Num - Dot_Pixel < 0 || Ypoint + YDir_Num - Dot_Pixel < 0)
                    break;
                Paint_SetPixel(Xpoint + XDir_Num - Dot_Pixel, Ypoint + YDir_Num - Dot_Pixel, Color);
            }
        }
    } else {
        for (XDir_Num = 0; XDir_Num < Dot_Pixel; XDir_Num++) {
            for (YDir_Num = 0; YDir_Num < Dot_Pixel; YDir_Num++) {
                Paint_SetPixel(Xpoint + XDir_Num - 1, Ypoint + YDir_Num - 1, Color);
            }
        }
    }
}

/******************************************************************************
function: Draw a line of arbitrary slope
parameter:
    Xstart ：Starting Xpoint point coordinates
    Ystart ：Starting Xpoint point coordinates
    Xend   ：End point Xpoint coordinate
    Yend   ：End point Ypoint coordinate
    Color  ：The color of the line segment
    Line_width : Line width
    Line_Style: Solid and dotted lines
******************************************************************************/
void Paint_DrawLine(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend,
                    UWORD Color, DOT_PIXEL Line_width, LINE_STYLE Line_Style) {
    if (Xstart > Paint.Width || Ystart > Paint.Height ||
        Xend > Paint.Width || Yend > Paint.Height) {
        return;
    }
    UWORD Xpoint = Xstart;
    UWORD Ypoint = Ystart;
    int dx = (int) Xend - (int) Xstart >= 0 ? Xend - Xstart : Xstart - Xend;
    int dy = (int) Yend - (int) Ystart <= 0 ? Yend - Ystart : Ystart - Yend;
    int XAddway = Xstart < Xend ? 1 : -1;
    int YAddway = Ystart < Yend ? 1 : -1;
    int Esp = dx + dy;
    char Dotted_Len = 0;
    for (;;) {
        Dotted_Len++;
        if (Line_Style == LINE_STYLE_DOTTED && Dotted_Len % 3 == 0) {
            Paint_DrawPoint(Xpoint, Ypoint, IMAGE_BACKGROUND, Line_width, DOT_STYLE_DFT);
            Dotted_Len = 0;
        } else {
            Paint_DrawPoint(Xpoint, Ypoint, Color, Line_width, DOT_STYLE_DFT);
        }
        if (2 * Esp >= dy) {
            if (Xpoint == Xend) break;
            Esp += dy;
            Xpoint += XAddway;
        }
        if (2 * Esp <= dx) {
            if (Ypoint == Yend) break;
            Esp += dx;
            Ypoint += YAddway;
        }
    }
}
/******************************************************************************
function: Draw a rectangle
parameter:
    Xstart ：Rectangular  Starting Xpoint point coordinates
    Ystart ：Rectangular  Starting Xpoint point coordinates
    Xend   ：Rectangular  End point Xpoint coordinate
    Yend   ：Rectangular  End point Ypoint coordinate
    Color  ：The color of the Rectangular segment
    Line_width: Line width
    Draw_Fill : Whether to fill the inside of the rectangle
******************************************************************************/
void Paint_DrawRectangle(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend,
                         UWORD Color, DOT_PIXEL Line_width, DRAW_FILL Draw_Fill) {
    if (Xstart > Paint.Width || Ystart > Paint.Height ||
        Xend > Paint.Width || Yend > Paint.Height) {
        return;
    }
    if (Draw_Fill) {
        UWORD Ypoint;
        for (Ypoint = Ystart; Ypoint < Yend; Ypoint++) {
            Paint_DrawLine(Xstart, Ypoint, Xend, Ypoint, Color, Line_width, LINE_STYLE_SOLID);
        }
    } else {
        Paint_DrawLine(Xstart, Ystart, Xend, Ystart, Color, Line_width, LINE_STYLE_SOLID);
        Paint_DrawLine(Xstart, Ystart, Xstart, Yend, Color, Line_width, LINE_STYLE_SOLID);
        Paint_DrawLine(Xend, Yend, Xend, Ystart, Color, Line_width, LINE_STYLE_SOLID);
        Paint_DrawLine(Xend, Yend, Xstart, Yend, Color, Line_width, LINE_STYLE_SOLID);
    }
}

/******************************************************************************
function: Use the 8-point method to draw a circle of the
            specified size at the specified position->
parameter:
    X_Center  ：Center X coordinate
    Y_Center  ：Center Y coordinate
    Radius    ：circle Radius
    Color     ：The color of the ：circle segment
    Line_width: Line width
    Draw_Fill : Whether to fill the inside of the Circle
******************************************************************************/
void Paint_DrawCircle(UWORD X_Center, UWORD Y_Center, UWORD Radius,
                      UWORD Color, DOT_PIXEL Line_width, DRAW_FILL Draw_Fill) {
    if (X_Center > Paint.Width || Y_Center >= Paint.Height) {
        Debug("Paint_DrawCircle Input exceeds the normal display range\r\n");
        return;
    }

    int16_t XCurrent, YCurrent;
    XCurrent = 0;
    YCurrent = Radius;

    int16_t Esp = 3 - (Radius << 1);

    int16_t sCountY;
    if (Draw_Fill == DRAW_FILL_FULL) {
        while (XCurrent <= YCurrent) { 
            for (sCountY = XCurrent; sCountY <= YCurrent; sCountY++) {
                Paint_DrawPoint(X_Center + XCurrent, Y_Center + sCountY, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                Paint_DrawPoint(X_Center - XCurrent, Y_Center + sCountY, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                Paint_DrawPoint(X_Center - sCountY, Y_Center + XCurrent, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                Paint_DrawPoint(X_Center - sCountY, Y_Center - XCurrent, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                Paint_DrawPoint(X_Center - XCurrent, Y_Center - sCountY, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                Paint_DrawPoint(X_Center + XCurrent, Y_Center - sCountY, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                Paint_DrawPoint(X_Center + sCountY, Y_Center - XCurrent, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                Paint_DrawPoint(X_Center + sCountY, Y_Center + XCurrent, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT);
            }
            if (Esp < 0)
                Esp += 4 * XCurrent + 6;
            else {
                Esp += 10 + 4 * (XCurrent - YCurrent);
                YCurrent--;
            }
            XCurrent++;
        }
    } else { 
        while (XCurrent <= YCurrent) {
            Paint_DrawPoint(X_Center + XCurrent, Y_Center + YCurrent, Color, Line_width, DOT_STYLE_DFT);
            Paint_DrawPoint(X_Center - XCurrent, Y_Center + YCurrent, Color, Line_width, DOT_STYLE_DFT);
            Paint_DrawPoint(X_Center - YCurrent, Y_Center + XCurrent, Color, Line_width, DOT_STYLE_DFT);
            Paint_DrawPoint(X_Center - YCurrent, Y_Center - XCurrent, Color, Line_width, DOT_STYLE_DFT);
            Paint_DrawPoint(X_Center - XCurrent, Y_Center - YCurrent, Color, Line_width, DOT_STYLE_DFT);
            Paint_DrawPoint(X_Center + XCurrent, Y_Center - YCurrent, Color, Line_width, DOT_STYLE_DFT);
            Paint_DrawPoint(X_Center + YCurrent, Y_Center - XCurrent, Color, Line_width, DOT_STYLE_DFT);
            Paint_DrawPoint(X_Center + YCurrent, Y_Center + XCurrent, Color, Line_width, DOT_STYLE_DFT);

            if (Esp < 0)
                Esp += 4 * XCurrent + 6;
            else {
                Esp += 10 + 4 * (XCurrent - YCurrent);
                YCurrent--;
            }
            XCurrent++;
        }
    }
}

/******************************************************************************
function: Show English characters
parameter:
    Xpoint           ：X coordinate
    Ypoint           ：Y coordinate
    Acsii_Char       ：To display the English characters
    Font             ：A structure pointer that displays a character size
    Color_Foreground : Select the foreground color
    Color_Background : Select the background color
******************************************************************************/
void Paint_DrawChar(UWORD Xpoint, UWORD Ypoint, const char Acsii_Char,
                    sFONT *Font, UWORD Color_Foreground, UWORD Color_Background) {
    UWORD Page, Column;

    if (Xpoint > Paint.Width || Ypoint > Paint.Height) {
        Debug("Paint_DrawChar Input exceeds the normal display range\r\n");
        return;
    }

    uint32_t Char_Offset = (Acsii_Char - ' ') * Font->Height * (Font->Width / 8 + (Font->Width % 8 ? 1 : 0));
    const unsigned char *ptr = &Font->table[Char_Offset];

    for (Page = 0; Page < Font->Height; Page++) {
        for (Column = 0; Column < Font->Width; Column++) {

            if (FONT_BACKGROUND == Color_Background) { 
                if (*ptr & (0x80 >> (Column % 8)))
                    Paint_SetPixel(Xpoint + Column, Ypoint + Page, Color_Foreground);
            } else {
                if (*ptr & (0x80 >> (Column % 8))) {
                    Paint_SetPixel(Xpoint + Column, Ypoint + Page, Color_Foreground);
                } else {
                    Paint_SetPixel(Xpoint + Column, Ypoint + Page, Color_Background);
                }
            }
            if (Column % 8 == 7)
                ptr++;
        }
        if (Font->Width % 8 != 0)
            ptr++;
    }
}

/******************************************************************************
function:	Display monochrome bitmap
parameter:
    image_buffer ：A picture data converted to a bitmap
info:
    Use a computer to convert the image into a corresponding array,
    and then embed the array directly into Imagedata.cpp as a .c file.
******************************************************************************/
void Paint_DrawBitMap(const unsigned char *image_buffer) {
    UWORD x, y;
    UDOUBLE Addr = 0;

    for (y = 0; y < Paint.HeightByte; y++) {
        for (x = 0; x < Paint.WidthByte; x++) {//8 pixel =  1 byte
            Addr = x + y * Paint.WidthByte;
            Paint.Image[Addr] = (unsigned char) image_buffer[Addr];
        }
    }
}

/******************************************************************************
function:	Display image
parameter:
    image            ：Image start address
    xStart           : X starting coordinates
    yStart           : Y starting coordinates
    xEnd             ：Image width
    yEnd             : Image height
******************************************************************************/
void Paint_DrawImage(const unsigned char *image_buffer, UWORD xStart, UWORD yStart, UWORD W_Image, UWORD H_Image,UWORD Color_Foreground, UWORD Color_Background) {
    int j,q;
    for (j = 0; j < H_Image; j++) {
        for (q = 0; q < W_Image; q++) {
            if (FONT_BACKGROUND == Color_Background) { //this process is to speed up the scan
                if (*image_buffer & (0x80 >> (q % 8))) {
                    Paint_SetPixel(xStart  + q, yStart + j, Color_Foreground);
                    // Paint_DrawPoint(x + i, y + j, Color_Foreground, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                }
            } else {
                if (*image_buffer & (0x80 >> (q % 8))) {
                    Paint_SetPixel(xStart  + q, yStart + j, Color_Foreground);
                    // Paint_DrawPoint(x + i, y + j, Color_Foreground, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                } else {
                    Paint_SetPixel(xStart  + q, yStart + j, Color_Background);
                    // Paint_DrawPoint(x + i, y + j, Color_Background, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                }
            }
            if (q % 8 == 7) {
                image_buffer++;
            }
        }
        if (W_Image % 8 != 0) {
            image_buffer++;
        }
    }

}

// 示例：这里只保留 EPD_DrawUTF8 作为代表
void EPD_DrawUTF8(uint16_t x, uint8_t y, uint8_t gap, const char *str, const uint8_t *ascii_font, const uint8_t *utf8_font,
             UWORD Color_Foreground, UWORD Color_Background) {
    uint16_t i, utf8_size;
    uint16_t x_count, font_size;
    uint32_t unicode, unicode_temp;
    const uint8_t *ascii_base_addr;
    uint16_t j, q;
    uint16_t fontHeight, fontWidth;
    x_count = 0;
    while (*str != '\0') {
        if ((*str & 0x80) == 0x00) /* 普通ASCII字符 */
        {
            if (ascii_font != NULL) {

                font_size = ((ascii_font[1] % 8 == 0 ? 0 : 1)+(ascii_font[1] /8)) * ascii_font[2] ;
                fontWidth = ascii_font[1];
                fontHeight = ascii_font[2];
                ascii_base_addr = ascii_font + (*str - ascii_font[0]) * font_size + 4;
                if ((*str - ascii_font[0])>=0&&(ascii_base_addr + font_size <= ascii_font + 4 + font_size * ascii_font[3])) /* 限制数组范围 */
                {
                    for (j = 0; j < fontHeight; j++) {
                        for (q = 0; q < fontWidth; q++) {
                            if (FONT_BACKGROUND == Color_Background) { 
                                if (*ascii_base_addr & (0x80 >> (q % 8))) {
                                    Paint_SetPixel(x + x_count + q, y + j, Color_Foreground);
                                }
                            } else {
                                if (*ascii_base_addr & (0x80 >> (q % 8))) {
                                    Paint_SetPixel(x + x_count + q, y + j, Color_Foreground);
                                } else {
                                    Paint_SetPixel(x + x_count + q, y + j, Color_Background);
                                }
                            }
                            if (q % 8 == 7) {
                                ascii_base_addr++;
                            }
                        }
                        if (fontWidth % 8 != 0) {
                            ascii_base_addr++;
                        }
                    }

                }
                x_count += ascii_font[1] + gap;
            } else if (*str == ' ' && utf8_font != NULL) 
            {
                x_count += utf8_font[1] / 2 + gap;
            }
        } else if (utf8_font != NULL) /* UTF8字符 */
        {
            unicode = 0x000000;
            utf8_size = 0;
            for (i = 0; i < 5; i++) {
                if (*str & (0x80 >> i)) {
                    utf8_size += 1;
                } else {
                    break;
                }
            }
            switch (utf8_size) {
                case 2:
                    if (*(str + 1) != '\0') {
                        unicode = (*str & 0x1F) << 6;
                        str += 1;
                        unicode |= *str & 0x3F;
                    }
                    break;
                case 3:
                    if (*(str + 1) != '\0' && *(str + 2) != '\0') {
                        unicode = (*str & 0x0F) << 12;
                        str += 1;
                        unicode |= (*str & 0x3F) << 6;
                        str += 1;
                        unicode |= *str & 0x3F;
                    }
                    break;
                case 4:
                    if (*(str + 1) != '\0' && *(str + 2) != '\0' && *(str + 3) != '\0') {
                        unicode = (*str & 0x07) << 18;
                        str += 1;
                        unicode |= (*str & 0x3F) << 12;
                        str += 1;
                        unicode |= (*str & 0x3F) << 6;
                        str += 1;
                        unicode |= *str & 0x3F;
                    }
                    break;
            }
            if (unicode != 0) {
                font_size = ((utf8_font[1] % 8 == 0 ? 0 : 1)+(utf8_font[1] /8)) * utf8_font[2] ;
                fontWidth = utf8_font[1];
                fontHeight = utf8_font[2];
                for (i = 0; i < utf8_font[3]; i++) /* 限制数组范围 */
                {
                    unicode_temp = utf8_font[4 + (font_size + 3) * i] << 16;
                    unicode_temp |= utf8_font[5 + (font_size + 3) * i] << 8;
                    unicode_temp |= utf8_font[6 + (font_size + 3) * i];
                    if (unicode_temp == unicode) {
                        ascii_base_addr = utf8_font + 7 + (font_size + 3) * i;
                        for (j = 0; j <  fontHeight; j++) {
                            for (q = 0; q < fontWidth; q++) {
                                if (FONT_BACKGROUND == Color_Background) {
                                    if (*ascii_base_addr & (0x80 >> (q % 8))) {
                                        Paint_SetPixel(x + x_count + q, y + j, Color_Foreground);
                                    }
                                } else {
                                    if (*ascii_base_addr & (0x80 >> (q % 8))) {
                                        Paint_SetPixel(x + x_count + q, y + j, Color_Foreground);
                                    } else {
                                        Paint_SetPixel(x + x_count + q, y + j, Color_Background);
                                    }
                                }
                                if (q % 8 == 7) {
                                    ascii_base_addr++;
                                }
                            }
                            if (fontWidth % 8 != 0) {
                                ascii_base_addr++;
                            }
                        }
                        break;
                    }
                }
            }
            x_count += utf8_font[1] + gap;
        }
        str += 1;
    }
}
