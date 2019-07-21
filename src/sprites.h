#ifndef SPRITES_H
#define SPRITES_H

#include <stdlib.h>
#include <stdint.h>

typedef struct Sprite{
  uint8_t *content;
  uint8_t width;
  uint8_t height;
} sprite;

uint16_t color_palette[16];

// Sprite declarations
sprite pacman;

#endif // SPRITES_H
