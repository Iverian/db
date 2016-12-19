#include "StaffMemberEdit.h"
#include "SkillAdd.h"
#include "ui_StaffMemberEdit.h"
#include "utility.h"

#include <QPushButton>

StaffMemberEdit::StaffMemberEdit(int id, const QSet<QString>& staffNames,
	const QMap<int, QString>& oprNames, QWidget* parent)
	: QDialog(parent)
	, m_id(id)
	, m_staffNames(staffNames)
	, m_oprNames(oprNames)
	, m_availNames()
	, ui(new Ui::StaffMemberEdit)
{
	for (const auto i = oprNames.begin(); i != oprNames.end(); ++i)
		m_availNames.insert(i.key());
	ui->setupUi(this);
}

StaffMemberEdit::~StaffMemberEdit() { delete ui; }

void StaffMemberEdit::add(const QSqlDatabase& db, QWidget* parent) {}

void StaffMemberEdit::edit(int id, const QSqlDatabase& db, QWidget* parent) {}

void StaffMemberEdit::on_staffName_editingFinished()
{
	auto text = ui->staffName->text();
	ui->buttonBox->button(QDialogButtonBox::Ok)
		->setEnabled(!text.isEmpty() && !m_staffNames.contains(text));
}

void StaffMemberEdit::on_skillView_customContextMenuRequested(QPoint pos)
{
	popupMenu(
		pos, ui->skillView->viewport(), {ui->act_addSkill, ui->act_delSkill}, this);
}

void StaffMemberEdit::on_act_addSkill_triggered()
{
	QMap<QString, int> absolutelyUnnessesary;
	for (const auto i = m_oprNames.begin(); i != m_oprNames.end(); ++i)
		if (m_availNames.contains(i.key()))
			absolutelyUnnessesary.insert(i.value(), i.key());
	m_availNames.remove(SkillAdd::add(absolutelyUnnessary, this));
}

void StaffMemberEdit::on_act_delSkill_triggered()
{
	auto text = ui->skillView->currentIndex().data().toString();
	auto id = std::find_if(m_oprNames.cbegin(), m_oprNames.cend(),
		[&text](
			const QMap<int, QString>::const_iterator& i) { return i.value() == text; }).key();
}
