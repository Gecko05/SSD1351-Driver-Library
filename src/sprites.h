/*$T src/sprites.h GC 1.150 2023-03-18 10:52:29 */


/*$6*/



#ifndef SPRITES_H
#define SPRITES_H

#include <stdlib.h>
#include <stdint.h>

typedef struct Sprite
{
	const uint8_t	*content;
	uint8_t			width;
	uint8_t			height;
} sprite;

extern sprite	sprite0;
#endif // SPRITES_H
