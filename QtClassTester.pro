#-------------------------------------------------
#
# Project created by QtCreator 2020-12-23T22:18:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtClassTester
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

include(./text/text.pri)

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui