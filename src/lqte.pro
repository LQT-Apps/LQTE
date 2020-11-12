TEMPLATE = app
TARGET = lqte

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -O2

SOURCES += iohandler.cpp main.cpp main_window.cpp

HEADERS += iohandler.h main_window.h
