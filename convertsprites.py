import color as clr
import spriteconverter as sp
import sys
import os

try:
    os.remove("src/loaded_sprites.c")
    os.remove("src/color_palette.c")
    os.remove("src/loaded_palette.h")
except:
    print("One or more files weren't loaded")
sp.convertsprites(sys.argv)
