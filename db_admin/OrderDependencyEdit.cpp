#include "OrderDependencyEdit.h"
#include "ui_OrderDependencyEdit.h"
#include "utility.h"

#include <QSqlQuery>
#include <QVBoxLayout>
#include <QVariant>

OrderDependencyEdit::OrderDependencyEdit(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::OrderDependencyEdit)
{
    ui->setupUi(this);
}

QVector<QCheckBox*> OrderDependencyEdit::setupList(QVector<dependItem>& list, QSqlQuery& operNames)
{
    QVector<QCheckBox*> retval;
    auto boxLayout = new QVBoxLayout(this);
    auto size = list.size();
    retval.reserve(size);
    operNames.next();
    for (auto i = 0; i != size; ++i) {
        auto item = new QCheckBox(operNames.value(1).toString(), this);
        item->setChecked(list.at(i).isParent);
        boxLayout->addWidget(item);
        retval.push_back(item);
        operNames.next();
    }
    ui->buttonBox->setLayout(boxLayout);
    return retval;
}

void OrderDependencyEdit::edit(QWidget* parent, QVector<dependItem>& list, QSqlQuery operNames)
{
    OrderDependencyEdit edit(parent);
    auto boxList = edit.setupList(list, operNames);
    if (edit.exec() == QDialog::Accepted)
        for (auto i = boxList.size(); i != -1; --i)
            list[i].isParent = boxList.at(i)->isChecked();
}

OrderDependencyEdit::~OrderDependencyEdit() { delete ui; }
