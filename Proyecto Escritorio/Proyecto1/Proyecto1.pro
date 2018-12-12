#-------------------------------------------------
#
# Project created by QtCreator 2018-02-27T09:18:39
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Proyecto1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog1.cpp \
    mainwindow2.cpp \
    mainwindow3.cpp \
    mainwindow4.cpp \
    mainwindow5.cpp \
    mainwindow6.cpp \
    mainwindow7.cpp \
    mainwindow8.cpp \
    conector.cpp \
    hfondo.cpp

HEADERS  += mainwindow.h \
    dialog1.h \
    mainwindow2.h \
    mainwindow3.h \
    mainwindow4.h \
    mainwindow5.h \
    mainwindow6.h \
    mainwindow7.h \
    mainwindow8.h \
    conector.h \
    hfondo.h

FORMS    += mainwindow.ui \
    dialog1.ui \
    mainwindow2.ui \
    mainwindow3.ui \
    mainwindow4.ui \
    mainwindow5.ui \
    mainwindow6.ui \
    mainwindow7.ui \
    mainwindow8.ui

RESOURCES += \
    imagenes.qrc
