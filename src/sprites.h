#ifndef SPRITES_H
#define SPRITES_H

#include <stdlib.h>
    #include <stdint.h>

typedef struct Sprite{
  const uint8_t *content;    
  uint8_t width;
  uint8_t height;
} sprite;

sprite sprite0;
sprite sprite1;
sprite sprite2;

#endif // SPRITES_H