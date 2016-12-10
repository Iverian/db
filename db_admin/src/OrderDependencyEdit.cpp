#include "OrderDependencyEdit.h"
#include "ui_OrderDependencyEdit.h"
#include "utility.h"

#include <QVBoxLayout>

OrderDependencyEdit::OrderDependencyEdit(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::OrderDependencyEdit)
{
    ui->setupUi(this);
}

OrderDependencyEdit::~OrderDependencyEdit() { delete ui; }

std::set<int> OrderDependencyEdit::edit(
    const std::set<int>& oldParentList, const std::map<QString, int>& operNames, QWidget* parent)
{
    std::set<int> retval;
    OrderDependencyEdit edit(parent);
    auto boxList = edit.setupList(operNames, oldParentList);
    if (edit.exec() == QDialog::Accepted)
        for (const auto &i : boxList)
            if (i->isChecked())
                retval.insert(operNames.at(i->text()));
    return retval;
}

QVector<QCheckBox*> OrderDependencyEdit::setupList(
    const std::map<QString, int>& operNames, const std::set<int>& parentList)
{
    QVector<QCheckBox*> retval;
    auto layout = new QVBoxLayout(this);
    auto operCount = operNames.size();
    retval.reserve(operCount);
    for (auto i = operNames.begin(); i != operNames.end(); ++i) {
        auto item = new QCheckBox(i->first, this);
        item->setChecked(contains(parentList, i->second));
        layout->addWidget(item);
        retval.push_back(item);
    }
    ui->buttonBox->setLayout(layout);
    return retval;
}
