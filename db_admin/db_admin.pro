#-------------------------------------------------
#
# Project created by QtCreator 2016-11-16T14:27:41
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = db_admin
TEMPLATE = app
CONFIG += c++14

SOURCES += main.cpp\
    MainWindow.cpp \
    OperationEdit.cpp \
    utility.cpp \
    OrderEdit.cpp \
    OrderDependencyEdit.cpp

HEADERS  += \
    MainWindow.h \
    databaseConnectionParams.h \
    OperationEdit.h \
    utility.h \
    OrderEdit.h \
    OrderDependencyEdit.h

FORMS    += \
    MainWindow.ui \
    OperationEdit.ui \
    OrderEdit.ui \
    OrderDependencyEdit.ui

RESOURCES += \
    mainwindowres.qrc
