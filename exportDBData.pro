QT += core sql
QT -= gui

CONFIG += c++11

TARGET = exportDBData
CONFIG += console
CONFIG -= app_bundle

DESTDIR = $$PWD/bin

TEMPLATE = app

SOURCES += main.cpp \
    DBUtil.cpp

HEADERS += \
    DBUtil.h
