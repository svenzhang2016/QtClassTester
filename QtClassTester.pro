#-------------------------------------------------
#
# Project created by QtCreator 2020-12-23T22:18:36
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtClassTester
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

include(./text/text.pri)
include(./base/base.pri)
include(./thread/thread.pri)
include(./test/test.pri)

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
