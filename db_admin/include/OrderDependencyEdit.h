#pragma once

#include <QCheckBox>
#include <QDialog>
#include <map>
#include <set>

#include "OrderEdit.h"

namespace Ui {
class OrderDependencyEdit;
}

class OrderDependencyEdit : public QDialog {
    Q_OBJECT
public:
    static std::set<int> edit(const std::set<int>& oldParentList,
        const std::map<QString, int>& operNames, QWidget* parent = Q_NULLPTR);
    ~OrderDependencyEdit();

private:
    explicit OrderDependencyEdit(QWidget* parent);
    QVector<QCheckBox*> setupList(
        const std::map<QString, int>& operNames, const std::set<int>& parentList);

    Ui::OrderDependencyEdit* ui;
};
