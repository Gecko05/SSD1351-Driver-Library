#ifndef SSD1351_H
#define SSD1351_H

#include "stm32l1xx_hal.h"
#include "stdbool.h"

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
#define SPI_TIMEOUT 100

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

void init_SSD1351(void);

void stop_SSD1351(void);

void turn_off_SSD1351(void);

void write_SSD1351Command(uint8_t data);

void write_SSD1351Data(uint8_t data);

void fill_SSD1351(uint16_t color);

void write_pixel_SSD1351(uint16_t color, uint8_t x, uint8_t y);

#endif //SSD1351_H
