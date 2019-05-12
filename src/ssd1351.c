#include "ssd1351.h"
#include "cmsis_os.h"

static uint16_t displayRAM[RAM_SIZE];

/**
  * @brief  Writes data to the SSD1351 OLED Display
  * @param  cmd: can be true to write a command
  * @param  data: pointer to the data buffer
  * @param  len: integer to specify data length
  * @retval None
  */
void write_SSD1351Command(uint8_t cmd){
  HAL_GPIO_WritePin(DC_PORT, DC_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_RESET);
  HAL_SPI_Transmit(HSSD, &(uint8_t){cmd}, 1, SPI_TIMEOUT);
  HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_SET);
}

void write_SSD1351Data(uint8_t data){
  HAL_GPIO_WritePin(DC_PORT, DC_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_RESET);
  HAL_SPI_Transmit(HSSD, &(uint8_t){data}, 1, SPI_TIMEOUT);
  HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_SET);
}

/**
  * @brief  Initializes the SSD1351 OLED Display
  * @retval None
  */
void init_SSD1351(void){
  HAL_GPIO_WritePin(RESET_PORT, RESET_PIN, GPIO_PIN_SET);
  HAL_Delay(500);
  HAL_GPIO_WritePin(RESET_PORT, RESET_PIN, GPIO_PIN_RESET);
  HAL_Delay(500);
  HAL_GPIO_WritePin(RESET_PORT, RESET_PIN, GPIO_PIN_SET);
  HAL_Delay(500);
  write_SSD1351Command(0xFD);
  write_SSD1351Data(0x12);
  write_SSD1351Command(0xFD);
  write_SSD1351Data(0xB1);

  write_SSD1351Command(0xAE);
  write_SSD1351Command(0xB3);
  write_SSD1351Command(0xF1);
  write_SSD1351Command(0xCA);
  write_SSD1351Data(127);
  HAL_Delay(600);

  write_SSD1351Command(SSD1351_CMD_SETREMAP);
  write_SSD1351Data(0x00);
  write_SSD1351Data(0x7F);
  write_SSD1351Command(SSD1351_CMD_SETROW);
  write_SSD1351Data(0x00);
  write_SSD1351Data(0x7F);

  write_SSD1351Command(SSD1351_CMD_STARTLINE);
  write_SSD1351Data(0x00);

  write_SSD1351Command(SSD1351_CMD_DISPLAYOFFSET);
  write_SSD1351Data(0x00);

  write_SSD1351Command(SSD1351_CMD_SETGPIO);
  write_SSD1351Data(0x00);

  write_SSD1351Command(SSD1351_CMD_FUNCTIONSELECT);
  write_SSD1351Data(0x01);

  write_SSD1351Command(SSD1351_CMD_PRECHARGE);
  write_SSD1351Data(0x32);

  write_SSD1351Command(SSD1351_CMD_VCOMH);
  write_SSD1351Data(0x05);

  write_SSD1351Command(SSD1351_CMD_NORMALDISPLAY);

  write_SSD1351Command(SSD1351_CMD_CONTRASTABC);
  write_SSD1351Data(0x8A);                          // Color A: Blue
  write_SSD1351Data(0x51);                          // Color B: Green
  write_SSD1351Data(0x8A);                          // Color C: Red

  write_SSD1351Command(SSD1351_CMD_CONTRASTMASTER);
  write_SSD1351Data(0x0F);

  write_SSD1351Command(SSD1351_CMD_SETVSL);
  write_SSD1351Data(0xA0);
  write_SSD1351Data(0xB5);
  write_SSD1351Data(0x55);

  write_SSD1351Command(SSD1351_CMD_PRECHARGE2);
  write_SSD1351Data(0x01);

  write_SSD1351Command(SSD1351_CMD_DISPLAYON);
}

/**
  * @brief  Turns off the SSD1351 OLED Display
  * @retval None
  */
void stop_SSD1351(void){
  write_SSD1351Command(SSD1351_CMD_DISPLAYOFF);
}

/**
  * @brief  Turns off the SSD1351 OLED Display
  * @param  color: Unsigned int16 containing color code
  * @retval None
  */
void fill_SSD1351(uint16_t color){
  write_SSD1351Command(SSD1351_CMD_WRITERAM);
  for (int c = 0; c < COLUMNS; c++){
    for (int r = 0; r < ROWS; r++){
      wirte_SSD1351Data(color);
    }
  }
  write_SSD1351Command(SSD1351_CMD_STOPSCROLL);
}
