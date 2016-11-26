/********************************************************************************
** Form generated from reading UI file 'AddNewStaffMember.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDNEWSTAFFMEMBER_H
#define UI_ADDNEWSTAFFMEMBER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddNewStaffMember
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *firstName;
    QLineEdit *secondName;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QListView *listView;
    QVBoxLayout *verticalLayout;
    QPushButton *addSkill;
    QPushButton *removeSkill;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AddNewStaffMember)
    {
        if (AddNewStaffMember->objectName().isEmpty())
            AddNewStaffMember->setObjectName(QStringLiteral("AddNewStaffMember"));
        AddNewStaffMember->resize(504, 388);
        AddNewStaffMember->setModal(true);
        gridLayout = new QGridLayout(AddNewStaffMember);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        firstName = new QLineEdit(AddNewStaffMember);
        firstName->setObjectName(QStringLiteral("firstName"));

        verticalLayout_2->addWidget(firstName);

        secondName = new QLineEdit(AddNewStaffMember);
        secondName->setObjectName(QStringLiteral("secondName"));

        verticalLayout_2->addWidget(secondName);

        label = new QLabel(AddNewStaffMember);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_2->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        listView = new QListView(AddNewStaffMember);
        listView->setObjectName(QStringLiteral("listView"));

        horizontalLayout->addWidget(listView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        addSkill = new QPushButton(AddNewStaffMember);
        addSkill->setObjectName(QStringLiteral("addSkill"));

        verticalLayout->addWidget(addSkill);

        removeSkill = new QPushButton(AddNewStaffMember);
        removeSkill->setObjectName(QStringLiteral("removeSkill"));

        verticalLayout->addWidget(removeSkill);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(AddNewStaffMember);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);


        retranslateUi(AddNewStaffMember);
        QObject::connect(buttonBox, SIGNAL(accepted()), AddNewStaffMember, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AddNewStaffMember, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddNewStaffMember);
    } // setupUi

    void retranslateUi(QDialog *AddNewStaffMember)
    {
        AddNewStaffMember->setWindowTitle(QApplication::translate("AddNewStaffMember", "Dialog", 0));
        firstName->setPlaceholderText(QApplication::translate("AddNewStaffMember", "First name", 0));
        secondName->setPlaceholderText(QApplication::translate("AddNewStaffMember", "Second name", 0));
        label->setText(QApplication::translate("AddNewStaffMember", "Skills:", 0));
        addSkill->setText(QApplication::translate("AddNewStaffMember", "Add skill", 0));
        removeSkill->setText(QApplication::translate("AddNewStaffMember", "Remove skill", 0));
    } // retranslateUi

};

namespace Ui {
    class AddNewStaffMember: public Ui_AddNewStaffMember {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDNEWSTAFFMEMBER_H
