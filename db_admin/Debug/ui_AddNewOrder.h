/********************************************************************************
** Form generated from reading UI file 'AddNewOrder.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDNEWORDER_H
#define UI_ADDNEWORDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddNewOrder
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout_3;
    QLabel *label;
    QLineEdit *orderName;
    QPlainTextEdit *orderDesc;
    QWidget *page_2;
    QGridLayout *gridLayout_4;
    QLabel *label_2;
    QPushButton *addOper;
    QPushButton *removeOper;
    QTableView *tableView;

    void setupUi(QDialog *AddNewOrder)
    {
        if (AddNewOrder->objectName().isEmpty())
            AddNewOrder->setObjectName(QStringLiteral("AddNewOrder"));
        AddNewOrder->resize(556, 435);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AddNewOrder->sizePolicy().hasHeightForWidth());
        AddNewOrder->setSizePolicy(sizePolicy);
        AddNewOrder->setModal(true);
        gridLayout_2 = new QGridLayout(AddNewOrder);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        buttonBox = new QDialogButtonBox(AddNewOrder);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setEnabled(true);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 1);

        stackedWidget = new QStackedWidget(AddNewOrder);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        gridLayout_3 = new QGridLayout(page);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label = new QLabel(page);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        orderName = new QLineEdit(page);
        orderName->setObjectName(QStringLiteral("orderName"));

        gridLayout_3->addWidget(orderName, 1, 0, 1, 1);

        orderDesc = new QPlainTextEdit(page);
        orderDesc->setObjectName(QStringLiteral("orderDesc"));

        gridLayout_3->addWidget(orderDesc, 2, 0, 1, 1);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        gridLayout_4 = new QGridLayout(page_2);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label_2 = new QLabel(page_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_4->addWidget(label_2, 0, 0, 1, 2);

        addOper = new QPushButton(page_2);
        addOper->setObjectName(QStringLiteral("addOper"));

        gridLayout_4->addWidget(addOper, 1, 0, 1, 1);

        removeOper = new QPushButton(page_2);
        removeOper->setObjectName(QStringLiteral("removeOper"));

        gridLayout_4->addWidget(removeOper, 1, 1, 1, 1);

        tableView = new QTableView(page_2);
        tableView->setObjectName(QStringLiteral("tableView"));

        gridLayout_4->addWidget(tableView, 2, 0, 1, 2);

        stackedWidget->addWidget(page_2);

        gridLayout->addWidget(stackedWidget, 1, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(AddNewOrder);
        QObject::connect(buttonBox, SIGNAL(rejected()), AddNewOrder, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), AddNewOrder, SLOT(accept()));

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(AddNewOrder);
    } // setupUi

    void retranslateUi(QDialog *AddNewOrder)
    {
        AddNewOrder->setWindowTitle(QApplication::translate("AddNewOrder", "Dialog", 0));
        label->setText(QApplication::translate("AddNewOrder", "Step 1: add description", 0));
        orderName->setPlaceholderText(QApplication::translate("AddNewOrder", "Order title", 0));
        orderDesc->setPlaceholderText(QApplication::translate("AddNewOrder", "Order description", 0));
        label_2->setText(QApplication::translate("AddNewOrder", "Step 2: add algorithm", 0));
        addOper->setText(QApplication::translate("AddNewOrder", "Add operation", 0));
        removeOper->setText(QApplication::translate("AddNewOrder", "Remove operation", 0));
    } // retranslateUi

};

namespace Ui {
    class AddNewOrder: public Ui_AddNewOrder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDNEWORDER_H
