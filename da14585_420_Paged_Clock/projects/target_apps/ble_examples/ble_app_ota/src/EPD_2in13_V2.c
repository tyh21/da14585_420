
#include "EPD_2in13_V2.h"
#include "Debug.h"

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
static void EPD_2IN13_V2_Reset(void)
{
    EPD_RST_L;
    DEV_Delay_ms(2);
    EPD_RST_H;
    DEV_Delay_ms(5);
}

/******************************************************************************
function :	send command
parameter:
     Reg : Command register
******************************************************************************/
void EPD_2IN13_V2_SendCommand(UBYTE Reg)
{
    EPD_DC_L;
    EPD_CS_L;
    DEV_SPI_WriteByte(Reg);
    EPD_CS_H;
}

/******************************************************************************
function :	send data
parameter:
    Data : Write data
******************************************************************************/
void EPD_2IN13_V2_SendData(UBYTE Data)
{
    EPD_DC_H;
    EPD_CS_L;
    DEV_SPI_WriteByte(Data);
    EPD_CS_H;
}
/******************************************************************************
* @brief  Waits for the e-Paper to become idle.
* @note   This is the corrected version for a real-time system. It includes
*         a call to wdg_reload() within the busy-wait loop to prevent the
*         Watchdog Timer from resetting the MCU during the long physical
*         refresh process of the e-paper display.
******************************************************************************/
void EPD_2IN13_V2_ReadBusy(void)
{
    Debug("e-Paper busy, starting to wait...\r\n");

    // EPD_BUSY 是一个宏，代表读取引脚状态，通常是 DEV_Digital_Read(EPD_BUSY_PIN)
    // 假设高电平(1)是忙，低电平(0)是空闲
    while(EPD_BUSY != 0) 
    { 
        // =================================================================
        // !! 在这个之前为空的循环体中，加入关键的“喂狗”操作 !!
        // =================================================================
        
        // 调用我们找到的看门狗重载函数，使用最常用的参数。
        // 这行代码会告诉看门狗：“程序没有死，只是在等一个慢速设备，请不要复位！”
        wdg_reload(WATCHDOG_DEFAULT_PERIOD);
				DEV_Delay_ms(500);
    }
    Debug("e-Paper busy release, wait finished.\r\n");
}

/******************************************************************************
function :	Turn On Display
parameter:
******************************************************************************/
 void EPD_2IN13_V2_TurnOnDisplay(void)
{
    // 步骤 1: 发送刷新指令序列
    EPD_2IN13_V2_SendCommand(0x22); // CMD_DISP_CTRL2
    EPD_2IN13_V2_SendData(0xF7);    // 使用0xF7，这是更完整的刷新参数
    EPD_2IN13_V2_SendCommand(0x20); // CMD_MASTER_ACTIVATE
    // 步骤 2: 【关键】长时间等待刷新完成
    // 这里的等待是导致蓝牙断开的直接原因！
    EPD_2IN13_V2_ReadBusy(); // 必须等待，否则刷新无法完成
    // 步骤 3: （可选但推荐）刷新后关闭电源
    // EPD_2IN13_V2_SendCommand(0x22);
    // EPD_2IN13_V2_SendData(0x83); // 对应 Update(0x83) power off
    // EPD_2IN13_V2_SendCommand(0x20);
}

 void EPD_2IN13_V2_TurnOnDisplay_RED(void)
{
    EPD_2IN13_V2_SendCommand(0x22);
    EPD_2IN13_V2_SendData(0xF7);
    EPD_2IN13_V2_SendCommand(0x20);
    EPD_2IN13_V2_ReadBusy();
}
/******************************************************************************
function :	Turn On Display
parameter:
******************************************************************************/
 void EPD_2IN13_V2_TurnOnDisplayPart(void)
{
    EPD_2IN13_V2_SendCommand(0x22);
    EPD_2IN13_V2_SendData(0x04);
    EPD_2IN13_V2_SendCommand(0x20);
    // EPD_2IN13_V2_ReadBusy();
}

void EPD_2IN13_V2_Init_RED(void) {

    /* EPD hardware init start */
        EPD_2IN13_V2_Reset();
    
        EPD_2IN13_V2_ReadBusy();
        EPD_2IN13_V2_SendCommand(0x12); // soft reset
        EPD_2IN13_V2_ReadBusy();

        EPD_2IN13_V2_SendCommand(0x74); //set analog block control
        EPD_2IN13_V2_SendData(0x54);
        EPD_2IN13_V2_SendCommand(0x7E); //set digital block control
        EPD_2IN13_V2_SendData(0x3B);

        EPD_2IN13_V2_SendCommand(0x01); //Driver output control
        EPD_2IN13_V2_SendData(0xD3);
        EPD_2IN13_V2_SendData(0x00);
        EPD_2IN13_V2_SendData(0x00);

        EPD_2IN13_V2_SendCommand(0x11); //data entry mode
        EPD_2IN13_V2_SendData(0x03);

        EPD_2IN13_V2_SendCommand(0x44); //set Ram-X address start/end position
        EPD_2IN13_V2_SendData(0x00);
        EPD_2IN13_V2_SendData(0x0C);    //0x0C-->(15+1)*8=128

        EPD_2IN13_V2_SendCommand(0x45); //set Ram-Y address start/end position
        EPD_2IN13_V2_SendData(0x00);   //0xF9-->(249+1)=250
        EPD_2IN13_V2_SendData(0x00);
        EPD_2IN13_V2_SendData(0xD3);
        EPD_2IN13_V2_SendData(0x00);

        EPD_2IN13_V2_SendCommand(0x3C); //BorderWavefrom
        EPD_2IN13_V2_SendData(0x05);

        EPD_2IN13_V2_SendCommand(0x18); // set built in temperature sensor
        EPD_2IN13_V2_SendData(0x80); //	
        EPD_2IN13_V2_SendCommand(0x4E);   // set RAM x address count to 0;
        EPD_2IN13_V2_SendData(0x00);
        EPD_2IN13_V2_SendCommand(0x4F);   // set RAM y address count to 0X127;
        EPD_2IN13_V2_SendData(0x00);
        EPD_2IN13_V2_SendData(0x00);
    
}

/******************************************************************************
function :	Initialize the e-Paper register
parameter:
******************************************************************************/
void EPD_2IN13_V2_Init(UBYTE Mode)
{
    // 步骤 1: 硬件和软件复位 (保持不变)
    EPD_2IN13_V2_Reset();
    EPD_2IN13_V2_ReadBusy();
    EPD_2IN13_V2_SendCommand(0x12); // SW_RESET
    EPD_2IN13_V2_ReadBusy();

    // 步骤 2: 设置边框和温度传感器 (保持不变)
    EPD_2IN13_V2_SendCommand(0x3C); // CMD_BORDER_CTRL
    EPD_2IN13_V2_SendData(0x01);
    EPD_2IN13_V2_SendCommand(0x18); // CMD_TSENSOR_CTRL
    EPD_2IN13_V2_SendData(0x80);

    // =======================================================================
    // !! 步骤 3: 【最终修正】严格按照标准答案设置RAM !!
    // =======================================================================

    // Data Entry Mode (X-inc, Y-inc)
    EPD_2IN13_V2_SendCommand(0x11);
    EPD_2IN13_V2_SendData(0x03);

    // Set RAM X-address Start/End position (0 to 399)
    EPD_2IN13_V2_SendCommand(0x44);
    EPD_2IN13_V2_SendData(0x00);           // X-start = 0
    EPD_2IN13_V2_SendData(49);             // X-end = 49 (399 / 8)

    // Set RAM Y-address Start/End position (0 to 299)
    EPD_2IN13_V2_SendCommand(0x45);
    EPD_2IN13_V2_SendData(0x00);           // Y-start low = 0
    EPD_2IN13_V2_SendData(0x00);           // Y-start high = 0
    EPD_2IN13_V2_SendData(299 % 256);      // Y-end low = 43
    EPD_2IN13_V2_SendData(299 / 256);      // Y-end high = 1

    // Set RAM X address counter to 0
    EPD_2IN13_V2_SendCommand(0x4E);
    EPD_2IN13_V2_SendData(0x00);

    // Set RAM Y address counter to 0
    EPD_2IN13_V2_SendCommand(0x4F);
    EPD_2IN13_V2_SendData(0x00);
    EPD_2IN13_V2_SendData(0x00);
    
    // 等待所有操作完成
    EPD_2IN13_V2_ReadBusy();
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
   
    x = EPD_2IN13_V2_HEIGHT - 1 - x;
    x_size = x - x_size + 1;          /* x_size已变为x结束地址 */
    y_size_x8 = y_size_x8 + y_x8 - 1; /* y_size已变为y结束地址 */

    EPD_2IN13_V2_SendCommand(0x44); /* 设置X（短边）起始地址和结束地址，根据扫描方式不同，地址设置也不同 */
    EPD_2IN13_V2_SendData(y_x8);
    EPD_2IN13_V2_SendData(y_size_x8 & 0xFF);
    EPD_2IN13_V2_SendCommand(0x45); /* 设置Y（长边）起始地址和结束地址，根据扫描方式不同，地址设置也不同 */
    EPD_2IN13_V2_SendData(x & 0xFF);
    EPD_2IN13_V2_SendData(0);
    EPD_2IN13_V2_SendData(x_size & 0xFF);
    EPD_2IN13_V2_SendData(0);

    EPD_2IN13_V2_SendCommand(0x4E); /* 设置X（短边）地址计数器 */
    EPD_2IN13_V2_SendData(y_x8);
    EPD_2IN13_V2_SendCommand(0x4F); /* 设置Y（长边）地址计数器 */
    EPD_2IN13_V2_SendData(x & 0xFF);
    EPD_2IN13_V2_SendData(0);
}
/**
 * @brief  向EPD控制器发送指定大小的显示数据。
 * @param  data 要发送数据的指针。
 * @param  data_size 要发送数据的大小。
 */
void EPD_SendRAM(const uint8_t *data, uint16_t data_size)
{
    uint16_t i;
    EPD_2IN13_V2_SendCommand(0x24);
    for(i=0;i<data_size;i++){
        EPD_2IN13_V2_SendData(*(data+i));
    }
}

void EPD_SendOLDRAM(const uint8_t *data, uint16_t data_size)
{
    uint16_t i;
    EPD_2IN13_V2_SendCommand(0x26);
    for(i=0;i<data_size;i++){
        EPD_2IN13_V2_SendData(*(data+i));
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
    EPD_2IN13_V2_SendCommand(0x24);
    for (i = 0; i < data_size; i++)
    {
        EPD_2IN13_V2_SendData(color);
    }
    EPD_SetWindow(0, 0, EPD_2IN13_V2_HEIGHT, EPD_2IN13_V2_WIDTH>>3);
}


void EPD_DrawImage( const uint8_t *image, uint16_t x, uint16_t y, uint16_t w, uint16_t h ,bool part)
{
    uint16_t i = 0;
    uint16_t size = w * h / 8;
    EPD_SetWindow(x, y, w, h / 8);
    EPD_2IN13_V2_SendCommand(0x24);
    for (i = 0; i < size; i++)
    {
        EPD_2IN13_V2_SendData(image[i]);
    }
    if (part)
    {
        EPD_2IN13_V2_SendCommand(0x26);
        for (i = 0; i < size; i++)
        {
            EPD_2IN13_V2_SendData(image[i]);
        }
    }
}


/******************************************************************************
function :	Clear screen
parameter:
******************************************************************************/
void EPD_2IN13_V2_Clear(void)
{
    UWORD Width, Height;
    Width = (EPD_2IN13_V2_WIDTH % 8 == 0) ? (EPD_2IN13_V2_WIDTH / 8) : (EPD_2IN13_V2_WIDTH / 8 + 1);
    Height = EPD_2IN13_V2_HEIGHT;

    EPD_2IN13_V2_SendCommand(0x24);
    for (UWORD j = 0; j < Height; j++)
    {
        for (UWORD i = 0; i < Width; i++)
        {
            EPD_2IN13_V2_SendData(0xff);
        }
    }
     EPD_2IN13_V2_SendCommand(0x26);
    for (UWORD j = 0; j < Height; j++)
    {
        for (UWORD i = 0; i < Width; i++)
        {
            EPD_2IN13_V2_SendData(0xff);
        }
    }

    EPD_2IN13_V2_TurnOnDisplay();
}

void EPD_2IN13_V2_Clear_RED(void)
{
    UWORD Width, Height;
    Width = (EPD_2IN13_V2_WIDTH % 8 == 0) ? (EPD_2IN13_V2_WIDTH / 8) : (EPD_2IN13_V2_WIDTH / 8 + 1);
    Height = EPD_2IN13_V2_HEIGHT;

    EPD_2IN13_V2_SendCommand(0x24);
    for (UWORD j = 0; j < Height; j++)
    {
        for (UWORD i = 0; i < Width; i++)
        {
            EPD_2IN13_V2_SendData(0xff);
        }
    }
     EPD_2IN13_V2_SendCommand(0x26);
    for (UWORD j = 0; j < Height; j++)
    {
        for (UWORD i = 0; i < Width; i++)
        {
            EPD_2IN13_V2_SendData(0x00);
        }
    }
}

/******************************************************************************
function :	Sends the image buffer in RAM to e-Paper and displays
parameter:
******************************************************************************/
void EPD_2IN13_V2_Display(UBYTE *Image)
{
    UWORD Width, Height;
    Width = (EPD_2IN13_V2_WIDTH % 8 == 0) ? (EPD_2IN13_V2_WIDTH / 8) : (EPD_2IN13_V2_WIDTH / 8 + 1);
    Height = EPD_2IN13_V2_HEIGHT;

    EPD_2IN13_V2_SendCommand(0x24);
    for (UWORD j = 0; j < Height; j++)
    {
        for (UWORD i = 0; i < Width; i++)
        {
            EPD_2IN13_V2_SendData(Image[i + j * Width]);
        }
    }
    EPD_2IN13_V2_TurnOnDisplay();
}

/******************************************************************************
function :	 The image of the previous frame must be uploaded, otherwise the
		         first few seconds will display an exception.
parameter:
******************************************************************************/
void EPD_2IN13_V2_DisplayPartBaseImage(UBYTE *Image)
{
    UWORD Width, Height;
    Width = (EPD_2IN13_V2_WIDTH % 8 == 0) ? (EPD_2IN13_V2_WIDTH / 8) : (EPD_2IN13_V2_WIDTH / 8 + 1);
    Height = EPD_2IN13_V2_HEIGHT;

    UDOUBLE Addr = 0;
    EPD_2IN13_V2_SendCommand(0x24);
    for (UWORD j = 0; j < Height; j++)
    {
        for (UWORD i = 0; i < Width; i++)
        {
            Addr = i + j * Width;
            EPD_2IN13_V2_SendData(Image[Addr]);
        }
    }
    EPD_2IN13_V2_SendCommand(0x26);
    for (UWORD j = 0; j < Height; j++)
    {
        for (UWORD i = 0; i < Width; i++)
        {
            Addr = i + j * Width;
            EPD_2IN13_V2_SendData(Image[Addr]);
        }
    }
    //   EPD_2IN13_V2_TurnOnDisplayPart();
    // EPD_2IN13_V2_TurnOnDisplay();
}

void EPD_2IN13_V2_DisplayPart(UBYTE *Image)
{
    UWORD Width, Height;
    Width = (EPD_2IN13_V2_WIDTH % 8 == 0) ? (EPD_2IN13_V2_WIDTH / 8) : (EPD_2IN13_V2_WIDTH / 8 + 1);
    Height = EPD_2IN13_V2_HEIGHT;
    UDOUBLE Addr = 0;
     EPD_2IN13_V2_SendCommand(0x24);
    for (UWORD j = 0; j < Height; j++)
    {
        for (UWORD i = 0; i < Width; i++)
        {
            Addr = i + j * Width;
            EPD_2IN13_V2_SendData(Image[Addr]);
        }
    }
    EPD_2IN13_V2_SendCommand(0x26);
    for (UWORD j = 0; j < Height; j++)
    {
        for (UWORD i = 0; i < Width; i++)
        {
            Addr = i + j * Width;
            EPD_2IN13_V2_SendData(~Image[Addr]);
        }
    }

    // EPD_2IN13_V2_SendCommand(0x26);
  
}

/******************************************************************************
function :	Enter sleep mode
parameter:
******************************************************************************/
void EPD_2IN13_V2_Sleep(void)
{
    // EPD_2IN13_V2_SendCommand(0x22); //POWER OFF
    // EPD_2IN13_V2_SendData(0xC3);
    // EPD_2IN13_V2_SendCommand(0x20);

    EPD_2IN13_V2_SendCommand(0x10); //enter deep sleep
    EPD_2IN13_V2_SendData(0x01);
    // DEV_Delay_ms(100);
}

