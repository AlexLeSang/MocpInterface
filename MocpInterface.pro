#-------------------------------------------------
#
# Project created by QtCreator 2012-05-12T16:03:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MocpInterface
TEMPLATE = app


SOURCES += main.cpp\
        InterfaceWidget.cpp \
    MocpWatcher.cpp

HEADERS  += InterfaceWidget.hpp \
    MocpWatcher.hpp

FORMS    += InterfaceWidget.ui
