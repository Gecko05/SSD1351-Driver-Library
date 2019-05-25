def convcolorhex():
    x = input("Hex number")
    xstr = x
    xl = [xstr[0:2], xstr[2:4], xstr[4:6]]
    print(xl)
    n_xl = [0,0,0]
    n_xl[0] = int(xl[0], 16) / 16
    n_xl[1] = int(xl[1], 16) / 8
    n_xl[2] = int(xl[2], 16) / 16
    for i in n_xl:
        print(hex(i), end="")

convcolorhex()
