#pragma once

#include <QAbstractListModel>
#include <QDialog>
#include <QList>
#include <QMap>
#include <QPair>
#include <QPoint>
#include <QSet>
#include <QSqlDatabase>
#include <QStringList>


namespace Ui {
class StaffMemberEdit;
}
/*
class StaffSkillModel : public QAbstractListModel {
	Q_OBJECT
public:
	explicit StaffSkillModel(
		const QList<QPair<int, QString>>& data = QList<QPair<int, QString>>(),
		QWidget* parent = Q_NULLPTR);

private:
	QList<QPair<int, QString>> m_data;
};
*/

class StaffMemberEdit : public QDialog {
	Q_OBJECT

public:
	static void add(QSqlDatabase& db, QWidget* parent);
	static void edit(int id, QSqlDatabase& db, QWidget* parent);
	~StaffMemberEdit();

private slots:
	void on_staffName_editingFinished();
	void on_skillView_customContextMenuRequested(QPoint pos);
	void on_act_addSkill_triggered();
	void on_act_delSkill_triggered();

private:
	explicit StaffMemberEdit(int id, QSqlDatabase& db, QWidget* parent = Q_NULLPTR);
	QList<int> skills();
	void insertSkills(int id, const QSqlDatabase& db);

	int m_id;
	QSet<QString> m_staffNames;
	QMap<int, QString> m_oprNames;
	QSet<int> m_availNames;
	QStringList m_list;
	Ui::StaffMemberEdit* ui;
};
