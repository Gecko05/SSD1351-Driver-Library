#ifndef SPRITES_H
#define SPRITES_H

#include <stdlib.h>
#include <stdint.h>

typedef struct Sprite{
  uint8_t *content;
  uint8_t width;
  uint8_t height;
} sprite;

uint8_t palette[16] = {
        0x0000, 0xFFFF, 0xFF00, 0x0FF0,
        0x00FF, 0xF00F, 0xFF00, 0x0FF0,
        0x00FF, 0xF00F, 0xFF00, 0x0FF0,
        0x00FF, 0xF00F, 0xFF00, 0x0FF0,
}

#endif // SPRITES_H
