#pragma once

#include <QDialog>
#include <QButtonGroup>
#include <QMap>

namespace Ui {
class SkillAdd;
}

class SkillAdd : public QDialog
{
	Q_OBJECT
public:
	static int add(const QMap<QString, int>& oprNames, QWidget* parent);
	~SkillAdd();
private slots:
	void radioButton_checked(int);
private:
	explicit SkillAdd(const QMap<QString, int>& oprNames, QWidget *parent = Q_NULLPTR);
	QButtonGroup* setupList();

	QMap<QString, int> m_oprNames;
	Ui::SkillAdd *ui;
};
