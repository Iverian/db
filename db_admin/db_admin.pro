#-------------------------------------------------
#
# Project created by QtCreator 2016-12-14T19:26:45
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = db_admin
TEMPLATE = app
CONFIG += c++11

INCLUDEPATH += include/

HEADERS += \
    include/databaseconnectionparams.h \
    include/MainWindow.h \
    include/OperationEdit.h \
    include/OrderDependencyEdit.h \
    include/OrderEdit.h \
    include/StaffMemberEdit.h \
    include/utility.h \
    include/AlgoModel.h \
    include/SkillAdd.h \
    include/OperationListModel.h \
    include/OrderListModel.h \
    include/StaffMemberModel.h

SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp \
    src/OperationEdit.cpp \
    src/OrderDependencyEdit.cpp \
    src/OrderEdit.cpp \
    src/StaffMemberEdit.cpp \
    src/utility.cpp \
    src/AlgoModel.cpp \
    src/SkillAdd.cpp \
    src/OperationListModel.cpp \
    src/OrderListModel.cpp \
    src/StaffMemberModel.cpp

RESOURCES += \
    mainwindowres.qrc

FORMS += \
    src/MainWindow.ui \
    src/OperationEdit.ui \
    src/OrderDependencyEdit.ui \
    src/OrderEdit.ui \
    src/StaffMemberEdit.ui \
    src/SkillAdd.ui
