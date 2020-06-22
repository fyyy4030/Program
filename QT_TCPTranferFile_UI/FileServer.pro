#-------------------------------------------------
#
# Project created by QtCreator 2020-06-22T16:14:49
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FileServer
TEMPLATE = app


SOURCES += main.cpp\
        ServerWidget.cpp \
    ClientWidget.cpp

HEADERS  += ServerWidget.h \
    ClientWidget.h

FORMS    += ServerWidget.ui \
    ClientWidget.ui

CONFIG += C++11
