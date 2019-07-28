import color as clr

def eprint(file, string):
    file.write(string.encode('utf8'))

def convertsprites(spriteList):
    if spriteList == 0:
        return
    cfile = open("src/loaded_sprites.c", "wb")
    pfile = open("src/color_palette.c", "wb")
    sfile = open("src/loaded_sprites.h", "wb")
    c = 0
    eprint(cfile, '#include "loaded_sprites.h"\n\n')
    eprint(sfile, '#include "sprites.h"\n\n')
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
        eprint(cfile, 'uint8_t ' + sprite_name + '[] = {\n')
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
    sfile.close()
    pfile.close()
    return
