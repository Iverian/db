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
	ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

SkillAdd::~SkillAdd() { delete ui; }

void SkillAdd::on_radioButton_checked(int)
{
	ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

QButtonGroup* SkillAdd::setupList()
{
	auto buttonGroup = new QButtonGroup;
	auto layout = new QVBoxLayout;
	for (auto i = m_oprNames.cbegin(); i != m_oprNames.cend(); ++i) {
		auto radio = new QRadioButton(i.key(), this);
		buttonGroup->addButton(radio);
		layout->addWidget(radio);
	}
	ui->skills->setLayout(layout);
	connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(on_radioButton_checked(int)));
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
