#include "SkillAdd.h"
#include "ui_SkillAdd.h"

#include <QAbstractButton>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>

SkillAdd::SkillAdd(const QMap<QString, int>& oprNames, QWidget* parent)
	: QDialog(parent)
	, m_oprNames(oprNames)
{
	ui->setupUi(this);
	ui->buttonBox(QDialogButtonBox::Ok)->setEnabled(false);
}

SkillAdd::~SkillAdd() { delete ui; }

void SkillAdd::on_radioButton_checked(int)
{
	ui->buttonBox(QDialogButtonBox::Ok)->setEnabled(true);
}

QButtonGroup* SkillAdd::setupList()
{
	auto buttonGroup = new QButtonGroup;
	auto layout = new QVBoxLayout(ui->buttonBox);
	for (const auto& i : m_oprNames)
		buttonGroup->addButton(new QRadioButton(i, ui->buttonBox));
	layout->addWidget(buttonGroup);
	return buttonGroup;
}

int SkillAdd::add(const QMap<QString, int>& oprNames, QWidget* parent)
{
	auto retval = -1;
	SkillAdd w(oprNames, parent);
	auto group = w.setupList();
	if (w.exec() == QDialog::Accepted)
		retval = oprNames[group->checkedButton()->text()];
	return retval;
}
