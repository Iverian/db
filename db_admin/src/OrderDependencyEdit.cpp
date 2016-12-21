#include "OrderDependencyEdit.h"
#include "ui_OrderDependencyEdit.h"
#include "utility.h"

OrderDependencyEdit::OrderDependencyEdit(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::OrderDependencyEdit)
{
    ui->setupUi(this);
}

OrderDependencyEdit::~OrderDependencyEdit() { delete ui; }

QSet<int> OrderDependencyEdit::edit(
    const QSet<int>& oldParentList, const QMap<QString, int>& operNames, QWidget* parent)
{
    QSet<int> retval;
    OrderDependencyEdit edit(parent);
    auto boxList = edit.setupList(operNames, oldParentList);
    if (edit.exec() == QDialog::Accepted)
        for (auto& i : boxList)
            if (i->isChecked())
                retval.insert(operNames.value(i->text()));
    return retval;
}

QList<QCheckBox*> OrderDependencyEdit::setupList(
    const QMap<QString, int>& operNames, const QSet<int>& parentList)
{
    QList<QCheckBox*> retval;
    auto layout = new QVBoxLayout(ui->groupBox);
    auto operCount = operNames.size();
    retval.reserve(operCount);
    for (auto i = operNames.begin(); i != operNames.end(); ++i) {
        auto item = new QCheckBox(i.key(), this);
        item->setChecked(contains(parentList, i.value()));
        layout->addWidget(item);
        retval.push_back(item);
    }
    ui->groupBox->setLayout(layout);
    return retval;
}
