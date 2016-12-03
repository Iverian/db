#pragma once

#include <QCheckBox>
#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class OrderDependencyEdit;
}

class MyCheckBox : public QCheckBox {
    Q_OBJECT
public:
    using QCheckBox::QCheckBox;
    int& id();
    const int& id() const;

private:
    int m_id;
};

class OrderDependencyEdit : public QDialog {
    Q_OBJECT
public:
    static void edit(QWidget* parent, QSqlDatabase& db, int orderId);
    ~OrderDependencyEdit();

private:
    explicit OrderDependencyEdit(QWidget* parent, int orderId, int operId);
    void setupList(const QSqlQuery& q);

    int m_operId;
    int m_orderId;
    Ui::OrderDependencyEdit* ui;
};
