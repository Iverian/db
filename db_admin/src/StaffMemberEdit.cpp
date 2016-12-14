#include "StaffMemberEdit.h"
#include "ui_StaffMemberEdit.h"
#include "utility.h"

StaffMemberEdit::StaffMemberEdit(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::StaffMemberEdit)
{
    ui->setupUi(this);
}

StaffMemberEdit::~StaffMemberEdit() { delete ui; }

void StaffMemberEdit::on_staffName_editingFinished() {}

void StaffMemberEdit::on_skillView_customContextMenuRequested(QPoint pos)
{
    popupMenu(pos, ui->skillView->viewport(), {ui->act_addSkill, ui->act_delSkill}, this);
}

void StaffMemberEdit::on_act_addSkill_triggered() {}

void StaffMemberEdit::on_act_delSkill_triggered() {}
