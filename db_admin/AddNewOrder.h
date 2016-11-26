#ifndef ADDNEWORDER_H
#define ADDNEWORDER_H

#include <QDialog>

namespace Ui {
class AddNewOrder;
}

class AddNewOrder : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewOrder(QWidget *parent = 0);
    ~AddNewOrder();

private:
    Ui::AddNewOrder *ui;
};

#endif // ADDNEWORDER_H
