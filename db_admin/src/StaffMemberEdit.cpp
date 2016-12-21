#include "StaffMemberEdit.h"
#include "SkillAdd.h"
#include "ui_StaffMemberEdit.h"
#include "utility.h"

#include <QPushButton>
#include <QStringListModel>
#include <algorithm>
#include <iterator>

StaffMemberEdit::StaffMemberEdit(int id, QSqlDatabase& db, QWidget* parent)
	: QDialog(parent)
	, m_id(id)
	, m_staffNames()
	, m_oprNames()
	, m_list()
	, ui(new Ui::StaffMemberEdit)
{
	ui->setupUi(this);
	auto staff = db.exec(id == -1 ? "SELECT Name FROM Staff"
								  : "SELECT Name FROM Staff WHERE Id <> %1;"_q.arg(id));
	auto names = db.exec("SELECT Id, Title FROM OperationTypes;");
	while (staff.next())
		m_staffNames.insert(staff.value(0).toString());
	while (names.next())
		m_oprNames.insert(names.value(0).toInt(), names.value(1).toString());
	for (auto i = m_oprNames.cbegin(); i != m_oprNames.cend(); ++i)
		m_availNames.insert(i.key());
	if (id != -1) {
		auto cur
			= db.exec("SELECT Id_operationType FROM Skills WHERE Id = %1;"_q.arg(id));
		while (cur.next()) {
			m_availNames.remove(cur.value(0).toInt());
			m_list.append(m_oprNames.find(cur.value(0).toInt()).value());
		}
		ui->skillView->setModel(new QStringListModel(m_list));
	}
}

QList<int> StaffMemberEdit::skills()
{
	QList<int> retval;
	for (auto i = m_oprNames.cbegin(); i != m_oprNames.cend(); ++i)
		if (!m_availNames.contains(i.key()))
			retval.append(i.key());
	return retval;
}

void StaffMemberEdit::insertSkills(int id, const QSqlDatabase& db)
{
	QString insertSkillsStr = "INSERT INTO Skills (Id_staff, Id_operationType) VALUES ";
	auto s = skills();
	for (auto i = s.cbegin(); i != s.cend(); ++i)
		insertSkillsStr
			+= "(%1,%2)%3"_q.arg(id).arg(*i).arg(std::next(i) == s.cend() ? ";" : ",");
	db.exec(insertSkillsStr);
}

StaffMemberEdit::~StaffMemberEdit() { delete ui; }

void StaffMemberEdit::add(QSqlDatabase& db, QWidget* parent)
{
	if (db.isOpen()) {
		db.transaction();
		StaffMemberEdit w(-1, db, parent);
		if (w.exec() == QDialog::Accepted) {
			db.exec(
				"INSERT INTO Staff (Name) VALUES ('%1');"_q.arg(w.ui->staffName->text()));
			auto idStaff
				= getFirstQueryVal<int>("SELECT last_value FROM staff_id_seq;", db);
			w.insertSkills(idStaff, db);
		}
		db.commit();
	}
}

void StaffMemberEdit::edit(int id, QSqlDatabase& db, QWidget* parent)
{
	if (db.isOpen()) {
		db.transaction();
		StaffMemberEdit w(id, db, parent);
		if (w.exec() == QDialog::Accepted) {
			db.exec("DELETE FROM Skills WHERE Id_staff = %1;"_q.arg(id));
			db.exec("UPDATE Staff SET Name = %1 WHERE Id_staff = %2;"_q
						.arg(w.ui->staffName->text())
						.arg(id));
			w.insertSkills(id, db);
		}
		db.commit();
	}
}

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
	for (auto i = m_oprNames.cbegin(); i != m_oprNames.cend(); ++i)
		if (m_availNames.contains(i.key()))
			absolutelyUnnessesary.insert(i.value(), i.key());
	auto id = SkillAdd::add(absolutelyUnnessesary, this);
	if (id != -1) {
		m_availNames.remove(id);
		m_list.append(m_oprNames.find(id).value());
		ui->skillView->setModel(new QStringListModel(m_list));
	}
}

void StaffMemberEdit::on_act_delSkill_triggered()
{
	auto text = ui->skillView->currentIndex().data().toString();
	auto id = std::find_if(
		m_oprNames.cbegin(), m_oprNames.cend(), [&text](const QString& i) {
			return i == text;
		}).key();
	m_availNames.insert(id);
	m_list.removeOne(text);
	ui->skillView->setModel(new QStringListModel(m_list));
}
