import color as clr

def eprint(file, string):
    file.write(string.encode('utf8'))

def convertsprites(spriteList, picoType):
    if spriteList == 0:
        return
    cfile = open("src/sprites.c", "wb")
    pfile = open("src/color_palette.c", "wb")
    sfile = open("src/sprites.h", "wb")
    c = 0
    eprint(cfile, '#include "sprites.h"\n\n')
    eprint(sfile, '#ifndef SPRITES_H\n#define SPRITES_H\n\n#include <stdlib.h>\
                   \n#include <stdint.h>\n\ntypedef struct Sprite{\n  const uint8_t *content;\
                   \n  uint8_t width;\n  uint8_t height;\n} sprite;\n\n')
    eprint(pfile,'#include "color_palette.h"\n' + \
    'uint16_t color_palette[256] = {\n')
    palette = 0
    for bmp in spriteList:
        bmpF = open(bmp, "rb")
        data = bmpF.read()
        if data[:2] != b'BM':
            continue
        width = data[18]
        height = data[22]
        if width > 128 or height > 128:
            print("Sprite ",bmp," is too big to use\n")
            continue
        # Generate color palette
        if palette == 0:
            plt = []
            for i in range(0, 256):
                colord = data[(54 + i * 4) : (57 + i * 4)]
                colori = int.from_bytes(colord, "big", signed=False)
                enclr = clr.encodecolor(colori)
                plt.append(enclr)
            for i in plt:
                eprint(pfile,(str(i) + ", "))
            eprint(pfile,'\n};\n\n')
            offset = int.from_bytes(data[10:13], "little", signed=False)
            pfile.close()
            palette = 1
        else:
            print("palette already loaded")
        # Write sprites to sprite file "loaded_sprites.c"
        #print("Width: ",width, "Height: ", height, "Offset: ", offset)
        print("Writing data...")
        sprite_name = 'sprite' + str(c) + '_data'
        eprint(cfile, '// ' + bmp + '\n')
        eprint(cfile, 'const uint8_t ' + sprite_name + '[] = {\n')
        eprint(sfile, 'sprite ' + 'sprite' + str(c) + ';\n')
        for y in range(0, height):
            eprint(cfile,'        ')
            for x in range(0, width):
                eprint(cfile, str(data[offset + ((height - y - 1) * width) + x - 1]) + ', ')
            eprint(cfile, '\n')
        eprint(cfile, '};\n\n')
        eprint(cfile, 'sprite ' + 'sprite' + str(c) + ' = {\n  .width = ' + \
          str(width) + ',\n  .height = ' + str(height) \
          + ',\n  .content = ' + sprite_name + ',\n};\n\n')
        c = c + 1
    cfile.close()
    eprint(sfile, '\n#endif // SPRITES_H')
    sfile.close()
    pfile.close()
    return
