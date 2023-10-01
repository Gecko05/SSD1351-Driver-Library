/*$T src/fonts.h GC 1.150 2023-03-18 10:52:42 */

/*Copyright (c) 2016 Olivier Van den Eede - ovde.be

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the “Software”), to deal in the Software without
restriction, including without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the 
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies 
or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
#ifndef SSD1351_FONTS_H
#define SSD1351_FONTS_H

#include <stdint.h>

#define small_font	& Font_7x10
#define med_font	& Font_11x18
#define big_font	& Font_16x26

// Structure for the font definition
typedef struct
{
	const uint8_t	width;	// Font width in pixels
	uint8_t			height; // Font height in pixels
	uint8_t			first;	// first glyph supported, 32 for ' '
	uint8_t			bits;	// Bits needed to hold each character data
	const void		*data;	// Pointer to data font data array
} font_t;

// Three sizes of fonts
extern font_t	Font_7x10;
extern font_t	Font_11x18;
extern font_t	Font_16x26;
#endif // SSD1351_FONTS_H
