#pragma once

#include "helperTypes.h"

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

    static operation newOperation(QWidget* parent = Q_NULLPTR);
private:
    Ui::AddNewOperation *ui;
};
