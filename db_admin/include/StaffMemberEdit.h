#pragma once

#include <QDialog>
#include <QMap>
#include <QPoint>
#include <QSet>
#include <QSqlDatabase>

namespace Ui {
class StaffMemberEdit;
}

class StaffMemberEdit : public QDialog {
	Q_OBJECT

public:
	static void add(const QSqlDatabase& db, QWidget* parent);
	static void edit(int id, const QSqlDatabase& db, QWidget* parent);
	~StaffMemberEdit();

private slots:
	void on_staffName_editingFinished();
	void on_skillView_customContextMenuRequested(QPoint pos);
	void on_act_addSkill_triggered();
	void on_act_delSkill_triggered();

private:
	explicit StaffMemberEdit(int id, const QSet<QString>& staffName,
		const QMap<QString, int>& oprNames, QWidget* parent = Q_NULLPTR);

	int m_id;
	QSet<QString> m_staffNames;
	QMap<QString, int> m_oprNames;
	Ui::StaffMemberEdit* ui;
};
