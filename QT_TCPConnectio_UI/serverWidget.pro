#-------------------------------------------------
#
# Project created by QtCreator 2020-06-22T10:28:16
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = serverWidget
TEMPLATE = app


SOURCES += main.cpp\
        ServerWidget.cpp \
    ClientWidget.cpp

HEADERS  += ServerWidget.h \
    ClientWidget.h

FORMS    += ServerWidget.ui \
    ClientWidget.ui

CONFIG += C++11
