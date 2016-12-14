#pragma once

#include <QDialog>
#include <QPoint>
#include <set>

namespace Ui {
class StaffMemberEdit;
}

class StaffMemberEdit : public QDialog {
    Q_OBJECT

public:
    ~StaffMemberEdit();

private slots:
    void on_staffName_editingFinished();
	void on_skillView_customContextMenuRequested(QPoint pos);
	void on_act_addSkill_triggered();
	void on_act_delSkill_triggered();

private:
    explicit StaffMemberEdit(QWidget* parent = 0);

    std::set<QString> m_staffNames;
	std::map<int, QString> m_oprNames;

    Ui::StaffMemberEdit* ui;
};
