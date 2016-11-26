#pragma once

#include <QDialog>

namespace Ui {
class AddNewOperation;
}

class AddNewOperation : public QDialog
{
    Q_OBJECT
public:
    explicit AddNewOperation(QWidget *parent = 0);
    ~AddNewOperation();
private:
    Ui::AddNewOperation *ui;
};
