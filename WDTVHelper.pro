#-------------------------------------------------
#
# Project created by QtCreator 2012-11-18T15:55:35
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WDTVHelper
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mirrorsxmlhandler.cpp \
    seriesxmlhandler.cpp \
    netxmlhandler.cpp \
    mirror.cpp

HEADERS  += mainwindow.h \
    mirrorsxmlhandler.h \
    seriesxmlhandler.h \
    netxmlhandler.h \
    mirror.h

FORMS    += mainwindow.ui
