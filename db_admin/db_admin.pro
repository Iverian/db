#-------------------------------------------------
#
# Project created by QtCreator 2016-11-16T14:27:41
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = db_admin
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
    MainWindow.cpp \
    AddNewOperation.cpp \
    AddNewOrder.cpp

HEADERS  += \
    MainWindow.h \
    AddNewOperation.h \
    AddNewOrder.h

FORMS    += \
    AddNewOperation.ui \
    MainWindow.ui \
    AddNewOrder.ui
