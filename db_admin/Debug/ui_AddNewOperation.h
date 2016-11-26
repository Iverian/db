/********************************************************************************
** Form generated from reading UI file 'AddNewOperation.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDNEWOPERATION_H
#define UI_ADDNEWOPERATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>

QT_BEGIN_NAMESPACE

class Ui_AddNewOperation
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit;
    QPlainTextEdit *plainTextEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AddNewOperation)
    {
        if (AddNewOperation->objectName().isEmpty())
            AddNewOperation->setObjectName(QStringLiteral("AddNewOperation"));
        AddNewOperation->resize(531, 402);
        AddNewOperation->setModal(true);
        gridLayout_2 = new QGridLayout(AddNewOperation);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lineEdit = new QLineEdit(AddNewOperation);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 0, 1, 1);

        plainTextEdit = new QPlainTextEdit(AddNewOperation);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        gridLayout->addWidget(plainTextEdit, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(AddNewOperation);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(AddNewOperation);
        QObject::connect(buttonBox, SIGNAL(accepted()), AddNewOperation, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AddNewOperation, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddNewOperation);
    } // setupUi

    void retranslateUi(QDialog *AddNewOperation)
    {
        AddNewOperation->setWindowTitle(QApplication::translate("AddNewOperation", "Dialog", 0));
        lineEdit->setPlaceholderText(QApplication::translate("AddNewOperation", "Operation name", 0));
        plainTextEdit->setPlaceholderText(QApplication::translate("AddNewOperation", "Operation description", 0));
    } // retranslateUi

};

namespace Ui {
    class AddNewOperation: public Ui_AddNewOperation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDNEWOPERATION_H
