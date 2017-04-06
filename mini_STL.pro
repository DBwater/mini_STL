QT += core
QT -= gui

TARGET = mini_STL
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ministring.cpp
CONFIG += c++11

HEADERS += \
    minivector.h \
    ministring.h \
    minideque.h \
    miniqueue.h \
    ministack.h \
    minimap.h \
    miniset.h \
    minilist.h
