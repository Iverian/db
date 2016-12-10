#include "SkillEdit.h"
#include "ui_SkillEdit.h"

SkillEdit::SkillEdit(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SkillEdit)
{
	ui->setupUi(this);
}

SkillEdit::~SkillEdit()
{
	delete ui;
}
