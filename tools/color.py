# This function can convert a hexadecimal color value
# to a format that the C library can understand.

def encodecolor(colorhex):
    encoded = 0
    blue = (colorhex & 0xFF0000) >> 16
    green = (colorhex & 0x00FF00) >> 8
    red = colorhex & 0x0000FF
    encoded |= (int(red/8) << 8)
    encoded |= (int(green/4) >> 3)
    encoded |= ((int(green/4) % 0x07) << 13)
    encoded |= (int(blue/8) << 3)
    return encoded
