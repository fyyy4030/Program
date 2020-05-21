#-------------------------------------------------
#
# Project created by QtCreator 2020-05-08T15:48:12
#
#-------------------------------------------------

QT += core gui
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = reader
TEMPLATE = app


SOURCES += main.cpp\
        MainViewer.cpp \
    Kit.cpp \
    PDFkit.cpp \
    ThumbnailWidget.cpp \
    NaviViewer.cpp \
    ViewState.cpp \
    SingleContinuousState.cpp \
    ViewModel.cpp \
    IDocWidget.cpp \
    DocViewer.cpp \
    DocWidget.cpp \
    ChildViewer.cpp

HEADERS  += MainViewer.h \
    MultiViewer.h \
    IMainViewer.h \
    ReadDefine.h \
    Kit.h \
    PDFkit.h \
    IChildViewer.h \
    ThumbnailWidget.h \
    NaviViewer.h \
    ViewState.h \
    SingleContinuousState.h \
    ViewModel.h \
    IDocWidget.h \
    DocViewer.h \
    DocWidget.h \
    ChildViewer.h

RESOURCES += \
    resource.qrc

INCLUDEPATH += $$PWD/3rdparty/ubuntu/Poppler/Include
unix: PKGCONFIG += poppler-qt5
unix: CONFIG += c++11 link_pkgconfig
