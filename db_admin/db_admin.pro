#-------------------------------------------------
#
# Project created by QtCreator 2016-12-14T19:26:45
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = db_admin
TEMPLATE = app

INCLUDEPATH += include/

HEADERS += \
    include/databaseconnectionparams.h \
    include/MainWindow.h \
    include/OperationEdit.h \
    include/OrderDependencyEdit.h \
    include/OrderEdit.h \
    include/SkillEdit.h \
    include/StaffMemberEdit.h \
    include/utility.h \
    include/AlgoModel.h

SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp \
    src/OperationEdit.cpp \
    src/OrderDependencyEdit.cpp \
    src/OrderEdit.cpp \
    src/SkillEdit.cpp \
    src/StaffMemberEdit.cpp \
    src/utility.cpp \
    src/AlgoModel.cpp

RESOURCES += \
    mainwindowres.qrc

FORMS += \
    src/MainWindow.ui \
    src/OperationEdit.ui \
    src/OrderDependencyEdit.ui \
    src/OrderEdit.ui \
    src/SkillEdit.ui \
    src/StaffMemberEdit.ui
