
#include "EPD_4in2.h"
#include "Debug.h"

const unsigned char EPD_4IN2_V2lut_full_update[] = {
        0x80, 0x60, 0x40, 0x00, 0x00, 0x00, 0x00,             //LUT0: BB:     VS 0 ~7
        0x10, 0x60, 0x20, 0x00, 0x00, 0x00, 0x00,             //LUT1: BW:     VS 0 ~7
        0x80, 0x60, 0x40, 0x00, 0x00, 0x00, 0x00,             //LUT2: WB:     VS 0 ~7
        0x10, 0x60, 0x20, 0x00, 0x00, 0x00, 0x00,             //LUT3: WW:     VS 0 ~7
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,             //LUT4: VCOM:   VS 0 ~7

        0x03, 0x03, 0x00, 0x00, 0x02,                       // TP0 A~D RP0
        0x09, 0x09, 0x00, 0x00, 0x02,                       // TP1 A~D RP1
        0x03, 0x03, 0x00, 0x00, 0x02,                       // TP2 A~D RP2
        0x00, 0x00, 0x00, 0x00, 0x00,                       // TP3 A~D RP3
        0x00, 0x00, 0x00, 0x00, 0x00,                       // TP4 A~D RP4
        0x00, 0x00, 0x00, 0x00, 0x00,                       // TP5 A~D RP5
        0x00, 0x00, 0x00, 0x00, 0x00,                       // TP6 A~D RP6

        0x15, 0x41, 0xA8, 0x32, 0x30, 0x0A,
};

const unsigned char EPD_4IN2_V2lut_partial_update[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,             //LUT0: BB:     VS 0 ~7
        0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,             //LUT1: BW:     VS 0 ~7
        0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,             //LUT2: WB:     VS 0 ~7
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,             //LUT3: WW:     VS 0 ~7
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,             //LUT4: VCOM:   VS 0 ~7

        0x0A, 0x00, 0x00, 0x00, 0x00,                       // TP0 A~D RP0
        0x00, 0x00, 0x00, 0x00, 0x00,                       // TP1 A~D RP1
        0x00, 0x00, 0x00, 0x00, 0x00,                       // TP2 A~D RP2
        0x00, 0x00, 0x00, 0x00, 0x00,                       // TP3 A~D RP3
        0x00, 0x00, 0x00, 0x00, 0x00,                       // TP4 A~D RP4
        0x00, 0x00, 0x00, 0x00, 0x00,                       // TP5 A~D RP5
        0x00, 0x00, 0x00, 0x00, 0x00,                       // TP6 A~D RP6

        0x15, 0x41, 0xA8, 0x32, 0x30, 0x0A,
};


void EPD_GPIO_init(void){
    //EPD_VCC ENABLE
    GPIO_ConfigurePin(GPIO_PORT_2, GPIO_PIN_3, OUTPUT, PID_GPIO, true);
    // GPIO_SetActive(GPIO_PORT_2, GPIO_PIN_3);
    // DEV_Delay_ms(10);
    GPIO_ConfigurePin(GPIO_PORT_2, GPIO_PIN_0, INPUT, PID_GPIO, false);
    GPIO_ConfigurePin(GPIO_PORT_2, GPIO_PIN_1, OUTPUT, PID_GPIO, true);
    GPIO_ConfigurePin(GPIO_PORT_0, GPIO_PIN_7, OUTPUT, PID_GPIO, true);
    GPIO_ConfigurePin(GPIO_PORT_0, GPIO_PIN_5, OUTPUT, PID_GPIO, false);
    // GPIO_ConfigurePin(GPIO_PORT_0, GPIO_PIN_3, OUTPUT, PID_GPIO, true);
    // GPIO_ConfigurePin(GPIO_PORT_2, GPIO_PIN_0, OUTPUT, PID_GPIO, false);
  
}

void DEV_SPI_WriteByte(uint8_t sdbyte)
{
    // uint8_t i;
    // for (i = 0; i < 8; i++)
    // {
    //     EPD_SCLK_L;
    //     if (sdbyte & 0x80)
    //     {
    //         EPD_SDI_H;
    //     }
    //     else
    //     {
    //         EPD_SDI_L;
    //     }
    //     sdbyte <<= 1;
    //     EPD_SCLK_H;
    // }
    // EPD_SCLK_L;
    spi_access(sdbyte);
}

/******************************************************************************
function :	Software reset
parameter:
******************************************************************************/
static void EPD_4IN2_V2Reset(void)
{
    EPD_RST_H;
    DEV_Delay_ms(200);
    EPD_RST_L;
    DEV_Delay_ms(200);
    EPD_RST_H;
    DEV_Delay_ms(200);
}

/******************************************************************************
function :	send command
parameter:
     Reg : Command register
******************************************************************************/
void EPD_4IN2_V2SendCommand(UBYTE Reg)
{
    EPD_DC_L;
    EPD_CS_L;
    spi_access(Reg);
    EPD_CS_H;
}

/******************************************************************************
function :	send data
parameter:
    Data : Write data
******************************************************************************/
void EPD_4IN2_V2SendData(uint8_t sdbyte)
{
    EPD_DC_H;
    EPD_CS_L;
    spi_access(sdbyte);
    EPD_CS_H;
}

void EPD_SendDataBlock(const uint8_t* data, uint16_t len)    //ses专用
{
    // 遍历数据块中的每一个字节
    for (uint16_t i = 0; i < len; i++) {
        // 对于每一个字节，都完整地执行一次“发送数据”的标准流程
        
        // 1. 设置 DC 为高电平 (数据模式)
        EPD_DC_H;
        
        // 2. 拉低 CS，准备发送这一个字节
        EPD_CS_L;
        
        // 3. 调用底层的 spi_access 发送当前这一个字节
        spi_access(data[i]);
        
        // 4. 拉高 CS，结束这一个字节的发送
        EPD_CS_H;
    }
}

/******************************************************************************
* @brief  Waits for the e-Paper to become idle.
* @note   This is the corrected version for a real-time system. It includes
*         a call to wdg_reload() within the busy-wait loop to prevent the
*         Watchdog Timer from resetting the MCU during the long physical
*         refresh process of the e-paper display.
******************************************************************************/
void EPD_4IN2_V2ReadBusy(void)
{
    Debug("e-Paper busy\r\n");
    while(EPD_BUSY != 0) {      // 0: busy, 1: idle
        DEV_Delay_ms(100);
    }
    Debug("e-Paper busy release\r\n");
}

/******************************************************************************
function :	Turn On Display
parameter:
******************************************************************************/
 void EPD_4IN2_V2TurnOnDisplay(void)
{
    EPD_4IN2_V2SendCommand(0x12); // SES 的刷新命令
    DEV_Delay_ms(100);
    //EPD_4IN2_V2ReadBusy();
}

 void EPD_4IN2_V2TurnOnDisplay_RED(void)
{
    EPD_4IN2_V2SendCommand(0x22);
    EPD_4IN2_V2SendData(0xF7);
    EPD_4IN2_V2SendCommand(0x20);
    EPD_4IN2_V2ReadBusy();
}
/******************************************************************************
function :	Turn On Display
parameter:
******************************************************************************/
 void EPD_4IN2_V2TurnOnDisplayPart(void)
{
    EPD_4IN2_V2SendCommand(0x22);
    EPD_4IN2_V2SendData(0x04);
    EPD_4IN2_V2SendCommand(0x20);
    // EPD_4IN2_V2ReadBusy();
}

void EPD_4IN2_V2Init_RED(void) {

    /* EPD hardware init start */
        EPD_4IN2_V2Reset();
    
        EPD_4IN2_V2ReadBusy();
        EPD_4IN2_V2SendCommand(0x12); // soft reset
        EPD_4IN2_V2ReadBusy();

        EPD_4IN2_V2SendCommand(0x74); //set analog block control
        EPD_4IN2_V2SendData(0x54);
        EPD_4IN2_V2SendCommand(0x7E); //set digital block control
        EPD_4IN2_V2SendData(0x3B);

        EPD_4IN2_V2SendCommand(0x01); //Driver output control
        EPD_4IN2_V2SendData(0xD3);
        EPD_4IN2_V2SendData(0x00);
        EPD_4IN2_V2SendData(0x00);

        EPD_4IN2_V2SendCommand(0x11); //data entry mode
        EPD_4IN2_V2SendData(0x03);

        EPD_4IN2_V2SendCommand(0x44); //set Ram-X address start/end position
        EPD_4IN2_V2SendData(0x00);
        EPD_4IN2_V2SendData(0x0C);    //0x0C-->(15+1)*8=128

        EPD_4IN2_V2SendCommand(0x45); //set Ram-Y address start/end position
        EPD_4IN2_V2SendData(0x00);   //0xF9-->(249+1)=250
        EPD_4IN2_V2SendData(0x00);
        EPD_4IN2_V2SendData(0xD3);
        EPD_4IN2_V2SendData(0x00);

        EPD_4IN2_V2SendCommand(0x3C); //BorderWavefrom
        EPD_4IN2_V2SendData(0x05);

        EPD_4IN2_V2SendCommand(0x18); // set built in temperature sensor
        EPD_4IN2_V2SendData(0x80); //	
        EPD_4IN2_V2SendCommand(0x4E);   // set RAM x address count to 0;
        EPD_4IN2_V2SendData(0x00);
        EPD_4IN2_V2SendCommand(0x4F);   // set RAM y address count to 0X127;
        EPD_4IN2_V2SendData(0x00);
        EPD_4IN2_V2SendData(0x00);
    
}
/**
 * @brief  设置EPD显示窗口位置和大小。
 * @param  x 显示窗口起始X位置。
 * @param  y_x8 显示窗口起始Y位置，设置1等于8像素。
 * @param  x_size 显示窗口X方向大小。
 * @param  y_size_x8 显示窗口Y方向大小，设置1等于8像素。
 * @note   指针已被自动设置至窗口的左上角。
 */
void EPD_SetWindow(uint16_t x, uint8_t y_x8, uint16_t x_size, uint8_t y_size_x8) {
   
    x = EPD_4IN2_V2HEIGHT - 1 - x;
    x_size = x - x_size + 1;          /* x_size已变为x结束地址 */
    y_size_x8 = y_size_x8 + y_x8 - 1; /* y_size已变为y结束地址 */

    EPD_4IN2_V2SendCommand(0x44); /* 设置X（短边）起始地址和结束地址，根据扫描方式不同，地址设置也不同 */
    EPD_4IN2_V2SendData(y_x8);
    EPD_4IN2_V2SendData(y_size_x8 & 0xFF);
    EPD_4IN2_V2SendCommand(0x45); /* 设置Y（长边）起始地址和结束地址，根据扫描方式不同，地址设置也不同 */
    EPD_4IN2_V2SendData(x & 0xFF);
    EPD_4IN2_V2SendData(0);
    EPD_4IN2_V2SendData(x_size & 0xFF);
    EPD_4IN2_V2SendData(0);

    EPD_4IN2_V2SendCommand(0x4E); /* 设置X（短边）地址计数器 */
    EPD_4IN2_V2SendData(y_x8);
    EPD_4IN2_V2SendCommand(0x4F); /* 设置Y（长边）地址计数器 */
    EPD_4IN2_V2SendData(x & 0xFF);
    EPD_4IN2_V2SendData(0);
}
/**
 * @brief  向EPD控制器发送指定大小的显示数据。
 * @param  data 要发送数据的指针。
 * @param  data_size 要发送数据的大小。
 */
void EPD_SendRAM(const uint8_t *data, uint16_t data_size)
{
    uint16_t i;
    EPD_4IN2_V2SendCommand(0x24);
    for(i=0;i<data_size;i++){
        EPD_4IN2_V2SendData(*(data+i));
    }
}

void EPD_SendOLDRAM(const uint8_t *data, uint16_t data_size)
{
    uint16_t i;
    EPD_4IN2_V2SendCommand(0x26);
    for(i=0;i<data_size;i++){
        EPD_4IN2_V2SendData(*(data+i));
    }
}
/**
 * @brief  清除EPD控制器指定区域显示RAM。
 * @note   执行完成后窗口会恢复至全屏幕。
 */
void EPD_ClearArea(uint16_t x, uint8_t y_x8, uint16_t x_size, uint8_t y_size_x8, uint8_t color)
{
    uint16_t i, data_size;

    data_size = x_size * (y_size_x8>>3);
    EPD_SetWindow(x, y_x8, x_size, y_size_x8>>3);
    EPD_4IN2_V2SendCommand(0x24);
    for (i = 0; i < data_size; i++)
    {
        EPD_4IN2_V2SendData(color);
    }
    EPD_SetWindow(0, 0, EPD_4IN2_V2HEIGHT, EPD_4IN2_V2WIDTH>>3);
}


void EPD_DrawImage( const uint8_t *image, uint16_t x, uint16_t y, uint16_t w, uint16_t h ,bool part)
{
    uint16_t i = 0;
    uint16_t size = w * h / 8;
    EPD_SetWindow(x, y, w, h / 8);
    EPD_4IN2_V2SendCommand(0x24);
    for (i = 0; i < size; i++)
    {
        EPD_4IN2_V2SendData(image[i]);
    }
    if (part)
    {
        EPD_4IN2_V2SendCommand(0x26);
        for (i = 0; i < size; i++)
        {
            EPD_4IN2_V2SendData(image[i]);
        }
    }
}


/******************************************************************************
function :	Clear screen
parameter:
******************************************************************************/
void EPD_4IN2_V2Clear(void)
{
    UWORD Width, Height;
    Width = (EPD_4IN2_V2WIDTH % 8 == 0) ? (EPD_4IN2_V2WIDTH / 8) : (EPD_4IN2_V2WIDTH / 8 + 1);
    Height = EPD_4IN2_V2HEIGHT;

    EPD_4IN2_V2SendCommand(0x10);
    for (UWORD j = 0; j < Height; j++) {
        for (UWORD i = 0; i < Width; i++) {
            EPD_4IN2_V2SendData(0xFF);
        }
    }

    EPD_4IN2_V2SendCommand(0x13);
    for (UWORD j = 0; j < Height; j++) {
        for (UWORD i = 0; i < Width; i++) {
            EPD_4IN2_V2SendData(0xFF);
        }
    }

    EPD_4IN2_V2TurnOnDisplay();
}

void EPD_4IN2_V2Clear_RED(void)
{
    UWORD Width, Height;
    Width = (EPD_4IN2_V2WIDTH % 8 == 0) ? (EPD_4IN2_V2WIDTH / 8) : (EPD_4IN2_V2WIDTH / 8 + 1);
    Height = EPD_4IN2_V2HEIGHT;

    EPD_4IN2_V2SendCommand(0x24);
    for (UWORD j = 0; j < Height; j++)
    {
        for (UWORD i = 0; i < Width; i++)
        {
            EPD_4IN2_V2SendData(0xff);
        }
    }
     EPD_4IN2_V2SendCommand(0x26);
    for (UWORD j = 0; j < Height; j++)
    {
        for (UWORD i = 0; i < Width; i++)
        {
            EPD_4IN2_V2SendData(0x00);
        }
    }
}

/******************************************************************************
function :	Sends the image buffer in RAM to e-Paper and displays
parameter:
******************************************************************************/
void EPD_4IN2_V2Display(UBYTE *Image)
{
    UWORD Width, Height;
    Width = (EPD_4IN2_V2WIDTH % 8 == 0) ? (EPD_4IN2_V2WIDTH / 8) : (EPD_4IN2_V2WIDTH / 8 + 1);
    Height = EPD_4IN2_V2HEIGHT;

    EPD_4IN2_V2SendCommand(0x10);
    for (UWORD j = 0; j < Height; j++) {
        for (UWORD i = 0; i < Width; i++) {
            EPD_4IN2_V2SendData(Image[i + j * Width]);
        }
    }

    EPD_4IN2_V2SendCommand(0x13);
    for (UWORD j = 0; j < Height; j++) {
        for (UWORD i = 0; i < Width; i++) {
            EPD_4IN2_V2SendData(Image[i + j * Width]);
        }
    }
    EPD_4IN2_V2TurnOnDisplay();
}

/******************************************************************************
function :	 The image of the previous frame must be uploaded, otherwise the
		         first few seconds will display an exception.
parameter:
******************************************************************************/
void EPD_4IN2_V2DisplayPartBaseImage(UBYTE *Image)
{
    UWORD Width, Height;
    Width = (EPD_4IN2_V2WIDTH % 8 == 0) ? (EPD_4IN2_V2WIDTH / 8) : (EPD_4IN2_V2WIDTH / 8 + 1);
    Height = EPD_4IN2_V2HEIGHT;

    UDOUBLE Addr = 0;
    EPD_4IN2_V2SendCommand(0x24);
    for (UWORD j = 0; j < Height; j++)
    {
        for (UWORD i = 0; i < Width; i++)
        {
            Addr = i + j * Width;
            EPD_4IN2_V2SendData(Image[Addr]);
        }
    }
    EPD_4IN2_V2SendCommand(0x26);
    for (UWORD j = 0; j < Height; j++)
    {
        for (UWORD i = 0; i < Width; i++)
        {
            Addr = i + j * Width;
            EPD_4IN2_V2SendData(Image[Addr]);
        }
    }
    //   EPD_4IN2_V2TurnOnDisplayPart();
    // EPD_4IN2_V2TurnOnDisplay();
}

void EPD_4IN2_V2DisplayPart(UBYTE *Image)
{
    UWORD Width, Height;
    Width = (EPD_4IN2_V2WIDTH % 8 == 0) ? (EPD_4IN2_V2WIDTH / 8) : (EPD_4IN2_V2WIDTH / 8 + 1);
    Height = EPD_4IN2_V2HEIGHT;
    UDOUBLE Addr = 0;
     EPD_4IN2_V2SendCommand(0x24);
    for (UWORD j = 0; j < Height; j++)
    {
        for (UWORD i = 0; i < Width; i++)
        {
            Addr = i + j * Width;
            EPD_4IN2_V2SendData(Image[Addr]);
        }
    }
    EPD_4IN2_V2SendCommand(0x26);
    for (UWORD j = 0; j < Height; j++)
    {
        for (UWORD i = 0; i < Width; i++)
        {
            Addr = i + j * Width;
            EPD_4IN2_V2SendData(~Image[Addr]);
        }
    }

    // EPD_4IN2_V2SendCommand(0x26);
  
}

/******************************************************************************
function :	Enter sleep mode
parameter:
******************************************************************************/
void EPD_4IN2_V2Sleep(void)
{
    EPD_4IN2_V2SendCommand(0x02); // POWER_OFF
    EPD_4IN2_V2ReadBusy();
    EPD_4IN2_V2SendCommand(0x07); // DEEP_SLEEP
    EPD_4IN2_V2SendData(0XA5);
}
void EPD_Init(void)
{
    EPD_4IN2_V2Reset();

    EPD_4IN2_V2SendCommand(0x06); // BOOSTER_SOFT_START
    EPD_4IN2_V2SendData(0x17);
    EPD_4IN2_V2SendData(0x17);
    EPD_4IN2_V2SendData(0x17);
    
    EPD_4IN2_V2SendCommand(0x04); // POWER_ON
    EPD_4IN2_V2ReadBusy();
    
    EPD_4IN2_V2SendCommand(0x00); // PANEL_SETTING
    EPD_4IN2_V2SendData(0x0F);    // LUT from OTP
}

//void EPD_4IN2_V2Init_Partial_Mode_Legacy(void)
//{
//    // 我们不需要完整的 Reset 和 Init，只需要切换模式的关键指令

//    // 1. 设置VCOM电压 (来自旧驱动)
//    EPD_4IN2_V2SendCommand(0x2C);
//    EPD_4IN2_V2SendData(0x28); // 使用旧驱动中的值

//    EPD_4IN2_V2ReadBusy();

//    // 2. 【核心】加载局刷LUT (来自旧驱动)
//    // 注意：这里的 EPD_4IN2_V2lut_partial_update 数组必须存在于您的项目中！
//    EPD_4IN2_V2SendCommand(0x32);
//    for (int count = 0; count < 70; count++)
//    {
//        EPD_4IN2_V2SendData(EPD_4IN2_V2lut_partial_update[count]);
//    }

//    // 3. 发送神秘的 0x37 指令序列 (来自旧驱动)
//    EPD_4IN2_V2SendCommand(0x37);
//    EPD_4IN2_V2SendData(0x00);
//    EPD_4IN2_V2SendData(0x00);
//    EPD_4IN2_V2SendData(0x00);
//    EPD_4IN2_V2SendData(0x00);
//    EPD_4IN2_V2SendData(0x40);
//    EPD_4IN2_V2SendData(0x00);
//    EPD_4IN2_V2SendData(0x00);
//}

//void EPD_4IN2_V2TurnOnDisplay_Partial_Legacy(void)
//{
//    EPD_4IN2_V2SendCommand(0x22);
//    EPD_4IN2_V2SendData(0xC0); // <-- 使用旧驱动的参数
//    EPD_4IN2_V2SendCommand(0x20);
//    EPD_4IN2_V2ReadBusy();
//}
