import color as clr
import spriteconverter as sp
import sys
import os

def printHelp():
    print("usage: python3 ConvertSprites.py [spriteName1.bmp] ... [sprinteNameN.bmp]\
           \n-h    : print this help message and exit (also --help)\n")

try:
    os.remove("src/loaded_sprites.c")
    os.remove("src/color_palette.c")
    os.remove("src/loaded_palette.h")
except:
    print("Loaded")
if sys.argv[1][0] == '-':
    if sys.argv[1][1] == 'h':
        printHelp()
    elif sys.argv[1] == '--help':
        printHelp()
else:
    sp.convertsprites(sys.argv)
