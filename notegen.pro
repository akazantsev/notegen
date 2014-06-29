#-------------------------------------------------
#
# Project created by QtCreator 2014-05-29T20:01:42
#
#-------------------------------------------------

QT       += core gui printsupport
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = notegen
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dottemplate.cpp \
    templateview.cpp \
    abstracttemplatemodel.cpp \
    doubleadjuster.cpp \
    doublespinbox.cpp

HEADERS  += mainwindow.h \
    dottemplate.h \
    templateview.h \
    abstracttemplatemodel.h \
    doubleadjuster.h \
    doublespinbox.h

FORMS    += \
    mainwindow.ui
