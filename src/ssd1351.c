#include "ssd1351.h"

/* Buffer to hold the Display RAM Data */
STATIC DRAM displayRAM;

#define DRAM_16 displayRAM.halfw
#define DRAM_8 displayRAM.byte


/**
  * @brief  Writes data to the SSD1351 OLED Display
  * @param  cmd: can be true to write a command
  * @param  data: pointer to the data buffer
  * @param  len: integer to specify data length
  * @retval None
  */
void SSD1351_write_command(uint8_t cmd){
  SSD1351_ClearPin(DC_PORT, DC_PIN);
  SSD1351_ClearPin(CS_PORT, CS_PIN);
  SSD1351_SendByte(cmd);
  SSD1351_SetPin(CS_PORT, CS_PIN);
}

void SSD1351_write_data(uint8_t data){
  SSD1351_SetPin(DC_PORT, DC_PIN);
  SSD1351_ClearPin(CS_PORT, CS_PIN);
  SSD1351_SendByte(data);
  SSD1351_SetPin(CS_PORT, CS_PIN);
}

void SSD1351_write_data_buffer(uint8_t *data, uint32_t len){
  SSD1351_SetPin(DC_PORT, DC_PIN);
  SSD1351_ClearPin(CS_PORT, CS_PIN);
  //HAL_SPI_Transmit(HSSD, data, len, SPI_TIMEOUT);
  SSD1351_SendBuffer(DRAM_8, DRAM_SIZE_8);
  SSD1351_SetPin(CS_PORT, CS_PIN);
}

/**
  * @brief  Initializes the SSD1351 OLED Display
  * @retval None
  */
void SSD1351_init(void){
  SSD1351_SetPin(RESET_PORT, RESET_PIN);
  SSD1351_DelayMs(500);
  SSD1351_ClearPin(RESET_PORT, RESET_PIN);
  SSD1351_DelayMs(500);
  SSD1351_SetPin(RESET_PORT, RESET_PIN);
  SSD1351_DelayMs(500);
  SSD1351_write_command(SSD1351_CMD_COMMANDLOCK);
  SSD1351_write_data(0x12);
  SSD1351_write_command(SSD1351_CMD_COMMANDLOCK);
  SSD1351_write_data(0xB1);

  SSD1351_write_command(SSD1351_CMD_DISPLAYOFF);
  SSD1351_write_command(SSD1351_CMD_CLOCKDIV);
  SSD1351_write_data(0xF1);
  SSD1351_write_command(SSD1351_CMD_MUXRATIO);
  SSD1351_write_data(127);
  SSD1351_DelayMs(600);

  SSD1351_write_command(SSD1351_CMD_SETREMAP);
  SSD1351_write_data(0x20);

  SSD1351_write_command(SSD1351_CMD_SETCOLUMN);
  SSD1351_write_data(0x00);
  SSD1351_write_data(0x7F);

  SSD1351_write_command(SSD1351_CMD_SETROW);
  SSD1351_write_data(0x00);
  SSD1351_write_data(0x7F);

  SSD1351_write_command(SSD1351_CMD_STARTLINE);
  SSD1351_write_data(0x00);

  SSD1351_write_command(SSD1351_CMD_DISPLAYOFFSET);
  SSD1351_write_data(0x00);

  SSD1351_write_command(SSD1351_CMD_SETGPIO);
  SSD1351_write_data(0x00);

  SSD1351_write_command(SSD1351_CMD_FUNCTIONSELECT);
  SSD1351_write_data(0x01);

  SSD1351_write_command(SSD1351_CMD_PRECHARGE);
  SSD1351_write_data(0x32);

  SSD1351_write_command(SSD1351_CMD_VCOMH);
  SSD1351_write_data(0x05);

  SSD1351_write_command(SSD1351_CMD_NORMALDISPLAY);

  SSD1351_write_command(SSD1351_CMD_CONTRASTABC);
  SSD1351_write_data(0x8A);                          // Color A: Blue
  SSD1351_write_data(0x51);                          // Color B: Green
  SSD1351_write_data(0x8A);                          // Color C: Red

  SSD1351_write_command(SSD1351_CMD_CONTRASTMASTER);
  SSD1351_write_data(0x0F);

  SSD1351_write_command(SSD1351_CMD_SETVSL);
  SSD1351_write_data(0xA0);
  SSD1351_write_data(0xB5);
  SSD1351_write_data(0x55);

  SSD1351_write_command(SSD1351_CMD_PRECHARGE2);
  SSD1351_write_data(0x01);

  SSD1351_write_command(SSD1351_CMD_DISPLAYON);
}

/**
  * @brief  Turns off the SSD1351 OLED Display
  * @retval None
  */
void SSD1351_stop(void){
  SSD1351_write_command(SSD1351_CMD_DISPLAYOFF);
}

/**
  * @brief  Turns off the SSD1351 OLED Display
  * @param  color: Unsigned int16 containing color code
  * @retval None
  */
void SSD1351_fill(uint16_t color){
  SSD1351_write_command(SSD1351_CMD_WRITERAM);
  for (int i = 0; i < DRAM_SIZE_16; i++){
    DRAM_16[i] = color;
  }
  //SSD1351_write_command(SSD1351_CMD_STOPSCROLL);
}

/**
  * @brief  Updates the screen RAM
  * @retval None
  */
void SSD1351_update(void){
  SSD1351_write_command(SSD1351_CMD_WRITERAM);
  SSD1351_write_data_buffer(DRAM_8, DRAM_SIZE_8);
}

/**
  * @brief  Updates a specific area within the display
  * @retval None
  */
/*void SSD1351_update_area(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1){
  SSD1351_write_command(SSD1351_CMD_SETCOLUMN);
  SSD1351_write_data(x0);
  SSD1351_write_data(y0);

  SSD1351_write_command(SSD1351_CMD_SETROW);
  SSD1351_write_data(x1);
  SSD1351_write_data(x0);

  int a0 = x0 + (y0 * 128);
  int a1 = x1 + (y1 * 128);

  SSD1351_write_command(SSD1351_CMD_WRITERAM);
  for (int i = a0; i < a1 * 2; i++){
    SSD1351_write_data(DRAM_8[i]);
  }

  // Back to default settings

  SSD1351_write_command(SSD1351_CMD_SETCOLUMN);
  SSD1351_write_data(x0);
  SSD1351_write_data(y0);

  SSD1351_write_command(SSD1351_CMD_SETROW);
  SSD1351_write_data(x1);
  SSD1351_write_data(x0);
}*/

/**
 * @brief Writes a pixel data to the screen RAM buffer
 * @param color: Unsigned int16 containing color code
 * @param x: Pixel's horizontal position
 * @param y: Pixel's vertical position
 * @retval None
 */
void SSD1351_write_pixel(int16_t x, int16_t y, uint16_t color){
  if ( x > 127 || y > 127 || x < 0 || y < 0){
    return;
  }
  int a = x + (y * 128);
  DRAM_16[a] = color;
}


/*  LINE DRAWING FUNCTIONS */

static void SSD1351_draw_line_low(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color){
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
      SSD1351_write_pixel(x, y, color);
      if (D > 0){
        y = y + yi;
        D = D - 2*dx;
      }
      D = D + 2*dy;
    }
  }
  else{
    for (int16_t x = x0; x >= x1; x--){
      SSD1351_write_pixel(x, y, color);
      if (D > 0){
        y = y + yi;
        D = D - 2*dx;
      }
      D = D + 2*dy;
    }
  }

}

static void SSD1351_draw_line_high(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color){
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
      SSD1351_write_pixel(x, y, color);
      if (D > 0){
        x = x + xi;
        D = D - 2*dy;
      }
      D = D + 2*dx;
    }
  }
  else{
    for (int16_t y = y0; y >= y1; y--){
      SSD1351_write_pixel(x, y, color);
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
void SSD1351_draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color){
  if (abs(y1 - y0) < abs(x1 - x0)){
    if (x0 > x1){
      SSD1351_draw_line_low(x1, y1, x0, y0, color);
    }
    else{
      SSD1351_draw_line_low(x0, y0, x1, y1, color);
    }
  }
  else{
    if (y0 > y1){
      SSD1351_draw_line_high(x1, y1, x0, y0, color);
    }
    else{
      SSD1351_draw_line_high(x0, y0, x1, y1, color);
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
void SSD1351_draw_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color){
  SSD1351_draw_line(x, y, x + w, y, color);
  SSD1351_draw_line(x + w, y, x + w, y + h, color);
  SSD1351_draw_line(x + w, y + h, x, y + h, color);
  SSD1351_draw_line(x, y + h, x, y, color);
}

/*
 * @brief Draws a filled rectangle with specified dimensions into display RAM
 * @param x0: starting x coordinate
 * @para y0: starting y coordinate
 * @param w: width of the rectangle
 * @oaram h: height of the rectangle
 * @oaram color: color for the border
 * @reval None
 */
void SSD1351_draw_filled_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color){
  for (int i = x; i < x + w; i++){
    for (int j = y; j < y + h; j++){
      SSD1351_write_pixel(i, j, color);
    }
  }
}

/*
 * @brief Converts from rgb to a single 16bit value
 * @param r: starting x coordinate
 * @para g: starting y coordinate
 * @param b: width of the rectangle
 * @reval 16bit value with the rgb color for display
 */
uint16_t SSD1351_get_rgb(uint8_t r, uint8_t g, uint8_t b){
  uint16_t rgb_color = 0;
  rgb_color |= ((r/8) << 8);
  rgb_color |= ((g/4) >> 3);
  rgb_color |= (((g/4) % 0x07) << 13);
  rgb_color |= ((b/8) << 3);
  return rgb_color;
}
