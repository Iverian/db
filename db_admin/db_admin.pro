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
    AddNewOperation.cpp \
    AddNewOrder.cpp \
    AddNewStaffMember.cpp \
    MainWindow.cpp

HEADERS  += \
    AddNewOperation.h \
    AddNewOrder.h \
    AddNewStaffMember.h \
    MainWindow.h \
    helperTypes.h \
    databaseConnectionParams.h

FORMS    += \
    AddNewOperation.ui \
    AddNewOrder.ui \
    AddNewStaffMember.ui \
    MainWindow.ui

RESOURCES += \
    mainwindowres.qrc
