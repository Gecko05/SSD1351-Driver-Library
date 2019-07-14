/*
 * Based on ssd1306-stm32HAL by Olivier Van den Eede(4ilo)
 */

#ifndef SSD1351_FONTS_H
#define SSD1351_FONTS_H

#include <stdint.h>

#define small_font Font_7x10
#define med_font Font_11x18
#define big_font Font_16x26

// Structure for the font definition
typedef struct {
	const uint8_t width;    // Font width in pixels
	uint8_t height;   // Font height in pixels
	const uint16_t *data; // Pointer to data font data array
} font_t;


// Three sizes of fonts
extern font_t Font_7x10;
extern font_t Font_11x18;
extern font_t Font_16x26;

#endif // SSD1351_FONTS_H
