#include "StaffMemberEdit.h"
#include "ui_StaffMemberEdit.h"

StaffMemberEdit::StaffMemberEdit(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::StaffMemberEdit)
{
	ui->setupUi(this);
}

StaffMemberEdit::~StaffMemberEdit()
{
	delete ui;
}

void StaffMemberEdit::on_staffSkills_customContextMenuRequested(const QPoint& pos)
{
}

void StaffMemberEdit::on_staffSkills_doubleClicked(const QModelIndex& index)
{
}

void StaffMemberEdit::on_staffName_editingFinished()
{

}
