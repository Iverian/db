#include "OrderEdit.h"
#include "ui_OrderEdit.h"

OrderEdit::OrderEdit(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::OrderEdit)
{
    ui->setupUi(this);
}

OrderEdit::~OrderEdit()
{
    delete ui;
}
