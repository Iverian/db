#include "AddNewStaffMember.h"
#include "ui_AddNewStaffMember.h"

AddNewStaffMember::AddNewStaffMember(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewStaffMember)
{
    ui->setupUi(this);
}

AddNewStaffMember::~AddNewStaffMember()
{
    delete ui;
}
