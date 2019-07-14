#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

class Window(QMainWindow):

    def __init__(self):
        super(Window, self).__init__()
        self.setWindowTitle("Color palette picker")
        self.palette_group()

    def palette_group(self):
        groupBox = QGroupBox()
        vbox = QGridLayout()
        self.pb_color1 = QPushButton("1")
        self.pb_color2 = QPushButton("2")
        self.pb_color3 = QPushButton("3")
        self.pb_color4 = QPushButton("4")
        self.pb_color5 = QPushButton("5")
        self.pb_color6 = QPushButton("6")
        self.pb_color7 = QPushButton("7")
        self.pb_color8 = QPushButton("8")
        self.pb_color9 = QPushButton("9")
        self.pb_color10 = QPushButton("10")
        self.pb_color11 = QPushButton("11")
        vbox.addWidget(self.pb_color1, 0, 0)
        vbox.addWidget(self.pb_color2, 0, 1)
        vbox.addWidget(self.pb_color3, 0, 2)
        vbox.addWidget(self.pb_color4, 0, 3)
        vbox.addWidget(self.pb_color5, 0, 4)
        vbox.addWidget(self.pb_color6, 0, 5)
        vbox.addWidget(self.pb_color7, 1, 0)
        vbox.addWidget(self.pb_color8, 1 ,1)
        vbox.addWidget(self.pb_color9, 1, 2)
        vbox.addWidget(self.pb_color10, 1, 3)
        vbox.addWidget(self.pb_color11, 1, 4)

        groupBox.setLayout(vbox)

        return groupBox

def main():
    app=QApplication(sys.argv)
    main=Window()
    main.show()
    sys.exit(app.exec_())

if __name__=='__main__':
    main()
