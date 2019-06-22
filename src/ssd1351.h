/*
     Driver library for the SSD1351 OLED Display developed by Jaime Centeno(Gecko05)
                             https://github.com/Gecko05
     Designed to be of generic use under a Hardware Abstraction Layer
     fonts.c and fonts.h based on ssd1306-stm32HAL by Olivier Van den Eede(4ilo)
 */

#ifndef SSD1351_H
#define SSD1351_H

#include "myHAL.h"   // Library for SPI HAL
#include "stdbool.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "math.h"
#include <stdarg.h>
#include "fonts.h"

/*------- CONFIGURE THIS TO YOUR OWN HARDWARE AND HAL -------*/
// PC0 = RESET      PC1 = D/C#      PB0 = CS

#define RESET_PORT GPIOC
#define RESET_PIN GPIO_PIN_0
#define DC_PORT GPIOC
#define DC_PIN  GPIO_PIN_1
#define CS_PORT GPIOB
#define CS_PIN GPIO_PIN_0
#define SPI_TIMEOUT 1
#define OLED_128x128

/* Definitions for SPI functions */
#define SSD1351_SendBuffer(buffer, len) SPI_TXBuffer(buffer, len)
#define SSD1351_SendByte(data) SPI_TXByte(data)

/* Definitions for GPIO pin functions */
#define SSD1351_SetPin(PORT, PIN) GPIO_SetPin(PORT, PIN)
#define SSD1351_ClearPin(PORT, PIN) GPIO_ResetPin(PORT, PIN)

/* Definition for delay function */
#define SSD1351_DelayMs(x) HAL_Delay(x)
/*--------------------------------------------------*/

// Static definition for testing purposes on Ceedling
#ifdef TEST
    #define STATIC
#else
    #define STATIC  static
#endif // TEST

#ifdef OLED_128x128
#define DRAM_SIZE_8 32768
#define DRAM_SIZE_16 16384
#define COLUMNS 128
#define ROWS 128
#endif // OLED_128x128

typedef union DisplayRAM{
  uint8_t byte[DRAM_SIZE_8];
  uint16_t halfw[DRAM_SIZE_16];
} DRAM;

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

//           Some color definitions
#define COLOR_BLUE 0x00F8
#define COLOR_RED 0x1F00
#define COLOR_GREEN 0xE007
#define COLOR_BLACK 0x0000
#define COLOR_WHITE 0xFFFF

extern struct cursor SSD1351_cursor;

uint16_t SSD1351_get_rgb(uint8_t r, uint8_t g, uint8_t b);

void SSD1351_init(void);

void SSD1351_stop(void);

void SSD1351_turn_off(void);

void SSD1351_fill(uint16_t color);

void SSD1351_write_pixel(int16_t x, int16_t y, uint16_t color);

void SSD1351_update(void);

void SSD1351_update_area(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);

void SSD1351_draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);

void SSD1351_draw_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

void SSD1351_draw_filled_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

void SSD1351_draw_circle(uint16_t xc, uint16_t yc, uint16_t r, uint16_t color);

void SSD1351_draw_filled_circle(uint16_t xc, uint16_t yc, uint16_t r, uint16_t color);

void SSD1351_printf(uint16_t color, font_t font, const char *format, ...);

void SSD1351_set_cursor(uint8_t x, uint8_t y);

#endif //SSD1351_H
