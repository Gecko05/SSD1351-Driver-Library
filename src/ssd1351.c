#include "ssd1351.h"

STATIC uint16_t displayRAM[RAM_SIZE];

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

void write_SSD1351DataBuffer(uint8_t *data, uint32_t len){
  HAL_GPIO_WritePin(DC_PORT, DC_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_RESET);
  HAL_SPI_Transmit(HSSD, data, len, SPI_TIMEOUT);
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
  write_SSD1351Command(SSD1351_CMD_COMMANDLOCK);
  write_SSD1351Data(0x12);
  write_SSD1351Command(SSD1351_CMD_COMMANDLOCK);
  write_SSD1351Data(0xB1);

  write_SSD1351Command(SSD1351_CMD_DISPLAYOFF);
  write_SSD1351Command(SSD1351_CMD_CLOCKDIV);
  write_SSD1351Data(0xF1);
  write_SSD1351Command(SSD1351_CMD_MUXRATIO);
  write_SSD1351Data(127);
  HAL_Delay(600);

  write_SSD1351Command(SSD1351_CMD_SETREMAP);
  write_SSD1351Data(0x20);
  //write_SSD1351Data(0x7F);
  write_SSD1351Command(SSD1351_CMD_SETROW);
  write_SSD1351Data(0x00);
  //write_SSD1351Data(0x7F);

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
  for (int i = 0; i < RAM_SIZE; i++){
    displayRAM[i] = color;
  }
  //write_SSD1351Command(SSD1351_CMD_STOPSCROLL);
}

/**
  * @brief  Updates the screen RAM
  * @retval None
  */
void update_SSD1351(void){
  write_SSD1351Command(SSD1351_CMD_WRITERAM);
  for(int i = 0; i < RAM_SIZE; i++){
    write_SSD1351Data((uint8_t)(displayRAM[i] >> 8));
    write_SSD1351Data((uint8_t)displayRAM[i]);
  }
}

/**
 * @brief Writes a pixel data to the screen RAM
 * @param color: Unsigned int16 containing color code
 * @param x: Pixel's horizontal position
 * @param y: Pixel's vertical position
 * @retval None
 */
void write_pixel_SSD1351(int16_t x, int16_t y, uint16_t color){
  if ( x > 127 || y > 127 || x < 0 || y < 0){
    return;
  }
  int a = x + (y * 128);
  displayRAM[a] = color;
}


/*  LINE DRAWING FUNCTIONS */

static void draw_line_low_SSD1351(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color){
  int16_t dx = x1 - x0;
  int16_t dy = y1 - y0;
  int16_t yi = 1;
  if (dy < 0){
    yi = -1;
    dy = -dy;
  }
  int16_t D = 2*dy - dx;
  int16_t y = y0;

  if (x0 < x1){
    for (int16_t x = x0; x <= x1; x++){
      write_pixel_SSD1351(x, y, color);
      if (D > 0){
        y = y + yi;
        D = D - 2*dx;
      }
      D = D + 2*dy;
    }
  }
  else{
    for (int16_t x = x0; x >= x1; x--){
      write_pixel_SSD1351(x, y, color);
      if (D > 0){
        y = y + yi;
        D = D - 2*dx;
      }
      D = D + 2*dy;
    }
  }

}

static void draw_line_high_SSD1351(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color){
  int16_t dx = x1 - x0;
  int16_t dy = y1 - y0;
  int16_t xi = 1;
  if (dx < 0){
    xi = -1;
    dx = -dx;
  }
  int16_t D = 2*dx - dy;
  int16_t x = x0;

  if ( y0 < y1){
    for (int16_t y = y0; y <= y1; y++){
      write_pixel_SSD1351(x, y, color);
      if (D > 0){
        x = x + xi;
        D = D - 2*dy;
      }
      D = D + 2*dx;
    }
  }
  else{
    for (int16_t y = y0; y >= y1; y--){
      write_pixel_SSD1351(x, y, color);
      if (D > 0){
        x = x + xi;
        D = D - 2*dy;
      }
      D = D + 2*dx;
    }
  }
}

/*
 * @brief Draws a line from specified parameters into display RAM
 * @param x0: starting x coordinate
 * @para y0: starting y coordinate
 * @param x1: ending x coordinate
 * @param y1: ending y coordinate
 * @color: color to use to draw the line
 * @reval None
 */
void draw_line_SSD1351(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color){
  if (abs(y1 - y0) < abs(x1 - x0)){
    if (x0 > x1){
      draw_line_low_SSD1351(x1, y1, x0, y0, color);
    }
    else{
      draw_line_low_SSD1351(x0, y0, x1, y1, color);
    }
  }
  else{
    if (y0 > y1){
      draw_line_high_SSD1351(x1, y1, x0, y0, color);
    }
    else{
      draw_line_high_SSD1351(x0, y0, x1, y1, color);
    }
  }
  return;
}

/*
 * @brief Draws a rectangle with specified dimensions into display RAM
 * @param x0: starting x coordinate
 * @para y0: starting y coordinate
 * @param w: width of the rectangle
 * @oaram h: height of the rectangle
 * @color: color for the border
 * @reval None
 */
void draw_rect_SSD1351(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color){
  draw_line_SSD1351(x, y, x + w, y, color);
  draw_line_SSD1351(x + w, y, x + w, y + h, color);
  draw_line_SSD1351(x + w, y + h, x, y + h, color);
  draw_line_SSD1351(x, y + h, x, y, color);
}

/*
 * @brief Draws a filled rectangle with specified dimensions into display RAM
 * @param x0: starting x coordinate
 * @para y0: starting y coordinate
 * @param w: width of the rectangle
 * @oaram h: height of the rectangle
 * @color: color for the border
 * @reval None
 */
void draw_filled_rect_SSD1351(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color){
  for (int i = x; i < x + w; i++){
    for (int j = y; j < y + h; j++){
      write_pixel_SSD1351(i, j, color);
    }
  }
}
