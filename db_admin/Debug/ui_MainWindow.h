/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actNewOperation;
    QAction *actNewOrder;
    QAction *actNewStaffMember;
    QAction *actEditOperation;
    QAction *actEditOrder;
    QAction *actEditStaffMember;
    QAction *actDeleteOperation;
    QAction *actDeleteOrder;
    QAction *actDeleteStaffMember;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *operations;
    QGridLayout *gridLayout_3;
    QListView *operNames;
    QPlainTextEdit *operDesc;
    QWidget *orders;
    QGridLayout *gridLayout_4;
    QListView *orderNames;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *orderDesc;
    QTreeView *orderAlgo;
    QWidget *staff;
    QGridLayout *gridLayout_5;
    QTableView *staffView;
    QWidget *stats;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget_2;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        actNewOperation = new QAction(MainWindow);
        actNewOperation->setObjectName(QStringLiteral("actNewOperation"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/MainWindowRes/new_oper.png"), QSize(), QIcon::Normal, QIcon::Off);
        actNewOperation->setIcon(icon);
        actNewOrder = new QAction(MainWindow);
        actNewOrder->setObjectName(QStringLiteral("actNewOrder"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/MainWindowRes/new_order.png"), QSize(), QIcon::Normal, QIcon::Off);
        actNewOrder->setIcon(icon1);
        actNewStaffMember = new QAction(MainWindow);
        actNewStaffMember->setObjectName(QStringLiteral("actNewStaffMember"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/MainWindowRes/new_staff.png"), QSize(), QIcon::Normal, QIcon::Off);
        actNewStaffMember->setIcon(icon2);
        actEditOperation = new QAction(MainWindow);
        actEditOperation->setObjectName(QStringLiteral("actEditOperation"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/MainWindowRes/edit_oper.png"), QSize(), QIcon::Normal, QIcon::Off);
        actEditOperation->setIcon(icon3);
        actEditOrder = new QAction(MainWindow);
        actEditOrder->setObjectName(QStringLiteral("actEditOrder"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/MainWindowRes/edit_order.png"), QSize(), QIcon::Normal, QIcon::Off);
        actEditOrder->setIcon(icon4);
        actEditStaffMember = new QAction(MainWindow);
        actEditStaffMember->setObjectName(QStringLiteral("actEditStaffMember"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/MainWindowRes/edit_staff.png"), QSize(), QIcon::Normal, QIcon::Off);
        actEditStaffMember->setIcon(icon5);
        actDeleteOperation = new QAction(MainWindow);
        actDeleteOperation->setObjectName(QStringLiteral("actDeleteOperation"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/MainWindowRes/delete_oper.png"), QSize(), QIcon::Normal, QIcon::Off);
        actDeleteOperation->setIcon(icon6);
        actDeleteOrder = new QAction(MainWindow);
        actDeleteOrder->setObjectName(QStringLiteral("actDeleteOrder"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/MainWindowRes/delete_order.png"), QSize(), QIcon::Normal, QIcon::Off);
        actDeleteOrder->setIcon(icon7);
        actDeleteStaffMember = new QAction(MainWindow);
        actDeleteStaffMember->setObjectName(QStringLiteral("actDeleteStaffMember"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/MainWindowRes/delete_staff.png"), QSize(), QIcon::Normal, QIcon::Off);
        actDeleteStaffMember->setIcon(icon8);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        operations = new QWidget();
        operations->setObjectName(QStringLiteral("operations"));
        gridLayout_3 = new QGridLayout(operations);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        operNames = new QListView(operations);
        operNames->setObjectName(QStringLiteral("operNames"));
        operNames->setContextMenuPolicy(Qt::CustomContextMenu);
        operNames->setEditTriggers(QAbstractItemView::NoEditTriggers);

        gridLayout_3->addWidget(operNames, 0, 0, 1, 1);

        operDesc = new QPlainTextEdit(operations);
        operDesc->setObjectName(QStringLiteral("operDesc"));
        operDesc->setReadOnly(true);

        gridLayout_3->addWidget(operDesc, 0, 1, 1, 1);

        tabWidget->addTab(operations, QString());
        orders = new QWidget();
        orders->setObjectName(QStringLiteral("orders"));
        gridLayout_4 = new QGridLayout(orders);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        orderNames = new QListView(orders);
        orderNames->setObjectName(QStringLiteral("orderNames"));
        orderNames->setContextMenuPolicy(Qt::CustomContextMenu);
        orderNames->setEditTriggers(QAbstractItemView::NoEditTriggers);

        gridLayout_4->addWidget(orderNames, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        orderDesc = new QPlainTextEdit(orders);
        orderDesc->setObjectName(QStringLiteral("orderDesc"));
        orderDesc->setReadOnly(true);

        verticalLayout->addWidget(orderDesc);

        orderAlgo = new QTreeView(orders);
        orderAlgo->setObjectName(QStringLiteral("orderAlgo"));
        orderAlgo->setEditTriggers(QAbstractItemView::NoEditTriggers);
        orderAlgo->setHeaderHidden(true);
        orderAlgo->header()->setVisible(false);

        verticalLayout->addWidget(orderAlgo);


        gridLayout_4->addLayout(verticalLayout, 0, 1, 1, 1);

        tabWidget->addTab(orders, QString());
        staff = new QWidget();
        staff->setObjectName(QStringLiteral("staff"));
        gridLayout_5 = new QGridLayout(staff);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        staffView = new QTableView(staff);
        staffView->setObjectName(QStringLiteral("staffView"));
        staffView->setContextMenuPolicy(Qt::CustomContextMenu);
        staffView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        gridLayout_5->addWidget(staffView, 0, 0, 1, 1);

        tabWidget->addTab(staff, QString());
        stats = new QWidget();
        stats->setObjectName(QStringLiteral("stats"));
        gridLayout_2 = new QGridLayout(stats);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tabWidget_2 = new QTabWidget(stats);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));

        gridLayout_2->addWidget(tabWidget_2, 0, 0, 1, 1);

        tabWidget->addTab(stats, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setMovable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actNewOperation);
        toolBar->addAction(actNewOrder);
        toolBar->addAction(actNewStaffMember);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actNewOperation->setText(QApplication::translate("MainWindow", "New operation", 0));
#ifndef QT_NO_TOOLTIP
        actNewOperation->setToolTip(QApplication::translate("MainWindow", "add new operation", 0));
#endif // QT_NO_TOOLTIP
        actNewOrder->setText(QApplication::translate("MainWindow", "New order", 0));
#ifndef QT_NO_TOOLTIP
        actNewOrder->setToolTip(QApplication::translate("MainWindow", "add new order", 0));
#endif // QT_NO_TOOLTIP
        actNewStaffMember->setText(QApplication::translate("MainWindow", "New staff member", 0));
#ifndef QT_NO_TOOLTIP
        actNewStaffMember->setToolTip(QApplication::translate("MainWindow", "add new staff member", 0));
#endif // QT_NO_TOOLTIP
        actEditOperation->setText(QApplication::translate("MainWindow", "Edit operation", 0));
#ifndef QT_NO_TOOLTIP
        actEditOperation->setToolTip(QApplication::translate("MainWindow", "edit selected opeartion", 0));
#endif // QT_NO_TOOLTIP
        actEditOrder->setText(QApplication::translate("MainWindow", "Edit order", 0));
#ifndef QT_NO_TOOLTIP
        actEditOrder->setToolTip(QApplication::translate("MainWindow", "edit selected order", 0));
#endif // QT_NO_TOOLTIP
        actEditStaffMember->setText(QApplication::translate("MainWindow", "Edit staff member", 0));
#ifndef QT_NO_TOOLTIP
        actEditStaffMember->setToolTip(QApplication::translate("MainWindow", "edit selected staff member", 0));
#endif // QT_NO_TOOLTIP
        actDeleteOperation->setText(QApplication::translate("MainWindow", "Delete operation", 0));
#ifndef QT_NO_TOOLTIP
        actDeleteOperation->setToolTip(QApplication::translate("MainWindow", "delete selected operation", 0));
#endif // QT_NO_TOOLTIP
        actDeleteOrder->setText(QApplication::translate("MainWindow", "Delete Order", 0));
#ifndef QT_NO_TOOLTIP
        actDeleteOrder->setToolTip(QApplication::translate("MainWindow", "delete selected order", 0));
#endif // QT_NO_TOOLTIP
        actDeleteStaffMember->setText(QApplication::translate("MainWindow", "Delete staff member", 0));
#ifndef QT_NO_TOOLTIP
        actDeleteStaffMember->setToolTip(QApplication::translate("MainWindow", "delete selected staff member", 0));
#endif // QT_NO_TOOLTIP
        operDesc->setPlaceholderText(QApplication::translate("MainWindow", "Selected operation description", 0));
        tabWidget->setTabText(tabWidget->indexOf(operations), QApplication::translate("MainWindow", "Operations", 0));
        orderDesc->setPlaceholderText(QApplication::translate("MainWindow", "Selected order description", 0));
        tabWidget->setTabText(tabWidget->indexOf(orders), QApplication::translate("MainWindow", "Orders", 0));
        tabWidget->setTabText(tabWidget->indexOf(staff), QApplication::translate("MainWindow", "Staff", 0));
        tabWidget->setTabText(tabWidget->indexOf(stats), QApplication::translate("MainWindow", "Stats", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
