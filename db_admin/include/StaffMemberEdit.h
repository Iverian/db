#pragma once

#include <QDialog>

namespace Ui {
class StaffMemberEdit;
}

class StaffMemberEdit : public QDialog {
	Q_OBJECT

public:
	explicit StaffMemberEdit(QWidget* parent = 0);
	~StaffMemberEdit();

private slots:
	void on_staffSkills_customContextMenuRequested(const QPoint& pos);
	void on_staffSkills_doubleClicked(const QModelIndex& index);
	void on_staffName_editingFinished();

private:
	Ui::StaffMemberEdit* ui;
};
