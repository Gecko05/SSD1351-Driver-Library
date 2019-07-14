def encodecolor(colorhex):
    encoded = 0
    red = colorhex & 0xFF0000
    green = colorhex & 0x00FF00
    blue = colorhex & 0x0000FF
    encoded |= ((red/8) << 8;)
    encoded |= ((green/4) >> 3);
    encoded |= (((green/4) % 0x07) << 13);
    encoded |= ((blue/8) << 3);
    return encoded
