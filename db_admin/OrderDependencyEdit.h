#pragma once

#include <QCheckBox>
#include <QDialog>
#include <QSqlDatabase>

#include "OrderEdit.h"

namespace Ui {
class OrderDependencyEdit;
}

class OrderDependencyEdit : public QDialog {
    Q_OBJECT
public:
    static void edit(QWidget* parent, QVector<dependItem>& list, QSqlQuery operNames);
    ~OrderDependencyEdit();

private:
    explicit OrderDependencyEdit(QWidget* parent);
    QVector<QCheckBox*> setupList(QVector<dependItem>& list, QSqlQuery &operNames);

    Ui::OrderDependencyEdit* ui;
};
