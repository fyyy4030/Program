#-------------------------------------------------
#
# Project created by QtCreator 2020-06-28T09:14:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ThreadImage
TEMPLATE = app


SOURCES += main.cpp\
        Widget.cpp \
    myThread.cpp

HEADERS  += Widget.h \
    myThread.h

FORMS    += Widget.ui
