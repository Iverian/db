#include "AddNewOperation.h"
#include "ui_AddNewOperation.h"

AddNewOperation::AddNewOperation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewOperation)
{
    ui->setupUi(this);
}

AddNewOperation::~AddNewOperation()
{
    delete ui;
}
