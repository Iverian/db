#include "AddNewOrder.h"
#include "ui_AddNewOrder.h"

AddNewOrder::AddNewOrder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewOrder)
{
    ui->setupUi(this);
}

AddNewOrder::~AddNewOrder()
{
    delete ui;
}
