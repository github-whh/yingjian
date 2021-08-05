#include "oled_driver.h"

extern unsigned char ScreenBuffer[SCREEN_PAGE_NUM][SCREEN_COLUMN];

uint8_t OLED_Init_CMD[] =
    {
        0xAE, 0x00, 0x10, 0x40, 0xB0, 0x81, 0xFF, 0xA1, 0xA6, 0xA8,
        0x3F, 0xC8, 0xD3, 0x00, 0xD5, 0x80, 0xD8, 0x05, 0xD9, 0xF1,
        0xDA, 0x12, 0xDB, 0x30, 0x8D, 0x14, 0xAF, 0x20, 0x00};

void OLED_FILL(unsigned char BMP[]) {
  HAL_I2C_Mem_Write_DMA(&Scr12864_HI2C, OLED_ADDRESS, OLED_WriteData_Addr, I2C_MEMADD_SIZE_8BIT, BMP, 1024);
}

void OLED_Init(void) {
  HAL_I2C_Mem_Write_DMA(&Scr12864_HI2C, OLED_ADDRESS, OLED_WriteCom_Addr, I2C_MEMADD_SIZE_8BIT, OLED_Init_CMD, 29);

  OLED_CLS();
}

void OLED_CLS(void)  //清屏 全部发送0x00
{
  unsigned char m, n;
  for (m = 0; m < SCREEN_PAGE_NUM; m++) {
    for (n = 0; n < SCREEN_COLUMN; n++) {
      ScreenBuffer[m][n] = 0;
    }
  }

  HAL_I2C_Mem_Write_DMA(&Scr12864_HI2C, OLED_ADDRESS, OLED_WriteData_Addr, I2C_MEMADD_SIZE_8BIT, ScreenBuffer[0], 1024);
}