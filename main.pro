CONFIG += debug
TARGET = mypats
QT += widgets
HEADERS = MainWindow.h \
          Globals.h \
          State.h \
          Scene.h \
          PixmapItem.h \
          Deal.h \
          Rules.h
SOURCES = main.cc \
          State.cc \
          MainWindow.cc \
          Scene.cc \
          Deal.cc \
          Rules.cc
RESOURCES = main.qrc
