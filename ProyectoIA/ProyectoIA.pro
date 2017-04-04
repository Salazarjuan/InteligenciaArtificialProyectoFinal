#-------------------------------------------------
#
# Project created by QtCreator 2017-03-05T19:23:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -Wl,--stack,4000000
TARGET = ProyectoIA
TEMPLATE = app


SOURCES += main.cpp\
        mapa.cpp \
    nodo.cpp

HEADERS  += mapa.h \
    nodo.h

FORMS    += mapa.ui
