# Use this CLI tool to convert bitmap images to sprite files that the
# C library can use.

import sp
import sys
import os

def printHelp():
    print("usage: python3 ConvertSprites.py [spriteName1.bmp] ... [sprinteNameN.bmp]\
           \n-h    : print this help message and exit (also --help)\
           \n-p8   : extract tileset from a .p8 file\
           \n")

def printError():
    print("Argument error\n")

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
    elif sys.argv[1] == '-p8' and len(sys.argv) <= 3:
        sp.convertsprites(sys.argv, True) #It's a .p8 file
    else:
        printError()
else:
    sp.convertsprites(sys.argv, False)
