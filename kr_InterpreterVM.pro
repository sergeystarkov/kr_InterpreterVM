#-------------------------------------------------
#
# Project created by QtCreator 2016-10-18T15:37:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kr_InterpreterVM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    computer.cpp \
    interpreter.cpp \
    command.cpp \
    test.cpp

HEADERS  += mainwindow.h \
    command.h \
    computer.h \
    types.h \
    operation.h \
    interpreter.h \
    test.h

FORMS    += mainwindow.ui
