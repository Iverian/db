#pragma once

#include <QCheckBox>
#include <QDialog>
#include <map>
#include <set>
#include <vector>

#include "OrderEdit.h"

namespace Ui {
class OrderDependencyEdit;
}

class OrderDependencyEdit : public QDialog {
    Q_OBJECT
public:
    static QSet<int> edit(const QSet<int>& oldParentList, const QMap<QString, int>& operNames,
        QWidget* parent = Q_NULLPTR);
    ~OrderDependencyEdit();

private:
    explicit OrderDependencyEdit(QWidget* parent);
    QList<QCheckBox*> setupList(const QMap<QString, int>& operNames, const QSet<int>& parentList);

    Ui::OrderDependencyEdit* ui;
};
