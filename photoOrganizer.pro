#-------------------------------------------------
#
# Project created by QtCreator 2016-01-22T19:02:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = photoOrganizer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fileview.cpp \
    imageviewer.cpp

HEADERS  += mainwindow.h \
    fileview.h \
    imageviewer.h

FORMS    += mainwindow.ui
