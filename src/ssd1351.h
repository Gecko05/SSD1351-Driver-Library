#ifndef SSD1351_H
#define SSD1351_H

#include "stm32l1xx_hal.h"
#include "stdbool.h"
#include "stdlib.h"
#include "stdio.h"

#ifdef TEST
    #define STATIC
#else /* ifdef TEST */
    #define STATIC  static
#endif /* ifdef TEST */

/*------- CONFIGURE THIS TO YOUR OWN HARDWARE -------*/
// PC0 = RESET      PC1 = D/C#      PB0 = CS

#define RESET_PORT GPIOC
#define RESET_PIN GPIO_PIN_0
#define DC_PORT GPIOC
#define DC_PIN  GPIO_PIN_1
#define CS_PORT GPIOB
#define CS_PIN GPIO_PIN_0
#define SPI_TIMEOUT 1

#define OLED_128x128

extern SPI_HandleTypeDef hspi2;
#define HSSD &hspi2
/*--------------------------------------------------*/

#ifdef OLED_128x128
#define RAM_SIZE 16384
#define COLUMNS 128
#define ROWS 128
#endif // OLED_128x128

//          SSD1351 Commands
#define SSD1351_CMD_SETCOLUMN       0x15
#define SSD1351_CMD_SETROW          0x75
#define SSD1351_CMD_WRITERAM        0x5C
#define SSD1351_CMD_READRAM         0x5D
#define SSD1351_CMD_SETREMAP        0xA0
#define SSD1351_CMD_STARTLINE       0xA1
#define SSD1351_CMD_DISPLAYOFFSET   0xA2
#define SSD1351_CMD_DISPLAYALLOFF   0xA4
#define SSD1351_CMD_DISPLAYALLON    0xA5
#define SSD1351_CMD_NORMALDISPLAY   0xA6
#define SSD1351_CMD_INVERTDISPLAY   0xA7
#define SSD1351_CMD_FUNCTIONSELECT  0xAB
#define SSD1351_CMD_DISPLAYOFF      0xAE
#define SSD1351_CMD_DISPLAYON       0xAF
#define SSD1351_CMD_PRECHARGE       0xB1
#define SSD1351_CMD_DISPLAYENHANCE  0xB2
#define SSD1351_CMD_CLOCKDIV        0xB3
#define SSD1351_CMD_SETVSL          0xB4
#define SSD1351_CMD_SETGPIO         0xB5
#define SSD1351_CMD_PRECHARGE2      0xB6
#define SSD1351_CMD_SETGRAY         0xB8
#define SSD1351_CMD_USELUT          0xB9
#define SSD1351_CMD_PRECHARGELEVEL  0xBB
#define SSD1351_CMD_VCOMH           0xBE
#define SSD1351_CMD_CONTRASTABC     0xC1
#define SSD1351_CMD_CONTRASTMASTER  0xC7
#define SSD1351_CMD_MUXRATIO        0xCA
#define SSD1351_CMD_COMMANDLOCK     0xFD
#define SSD1351_CMD_HORIZSCROLL     0x96
#define SSD1351_CMD_STOPSCROLL      0x9E
#define SSD1351_CMD_STARTSCROLL     0x9F

//           Colors
#define COLOR_RED 0x001F
#define COLOR_BLUE 0xF800
#define COLOR_GREEN 0x07E0
#define COLOR_BLACK 0x0000
#define COLOR_WHITE 0xFFFF

void init_SSD1351(void);

void stop_SSD1351(void);

void turn_off_SSD1351(void);

void fill_SSD1351(uint16_t color);

void write_pixel_SSD1351(int16_t x, int16_t y, uint16_t color);

void update_SSD1351(void);

void draw_line_SSD1351(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);

void draw_rect_SSD1351(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

void draw_filled_rect_SSD1351(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

#endif //SSD1351_H
